import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Index route: Modify networth calculation and ensure correct data types
@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # Fetch stock information
    row = db.execute("SELECT stock, shares, price FROM buy WHERE user_id = ?", user_id)
    username = db.execute("SELECT username FROM users WHERE id = ?", user_id)[0]["username"]
    current_balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Initialize networth as 0
    networth = 0

    for stock_price in row:
        temp_dict = lookup(stock_price['stock'])

        if stock_price["stock"]:
            # Update the stock price in the database
            db.execute("UPDATE buy SET price = ? WHERE user_id = ? AND stock = ?",
                       temp_dict["price"], user_id, temp_dict['symbol'])
            stock_price["price"] = temp_dict["price"]

            # Calculate the total worth of the stock holding (price * shares)
            stock_worth = stock_price['price'] * stock_price['shares']
            networth += stock_worth  # Accumulate the networth
        else:
            break

    # Round the balance and networth for display purposes
    current_balance = round(current_balance, 2)
    networth = round(networth, 2)

    return render_template("index.html", username=username, current_balance=current_balance, networth=networth, row=row)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":

        # Retrieve form data
        user_id = session["user_id"]
        symbol = request.form.get("symbol")
        shares_input = request.form.get("shares")

        # Validate symbol input
        if not symbol:
            return apology("must provide symbol", 400)

        # Check if symbol is valid
        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        # Validate shares input
        try:
            shares = int(shares_input)
            if shares <= 0:
                return apology("shares must be a positive integer", 400)
        except ValueError:
            return apology("shares must be a positive integer", 400)

        # Get current stock price and calculate total cost (round to 2 decimal places)
        unit_price = round(stock["price"], 2)
        total_cost = round(shares * unit_price, 2)

        # Get the user's current balance
        current_balance = round(db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"], 2)

        # Check if the user can afford the purchase
        if total_cost > current_balance:
            return apology("Insufficient funds", 402)

        # Update stock ownership or insert new stock if it doesn't exist
        check = db.execute("SELECT stock FROM buy WHERE user_id = ? AND stock = ?", user_id, symbol)
        if not check:
            # Insert new stock into the `buy` table
            db.execute("INSERT INTO buy (stock, price, time, user_id, shares) VALUES (?, ?, ?, ?, ?)",
                        symbol, unit_price, datetime.now(), user_id, shares)
        else:
            # Update existing stock by adding the new shares
            db.execute("UPDATE buy SET shares = shares + ? WHERE user_id = ? AND stock = ?", shares, user_id, symbol)

        # Insert the transaction into the history table
        db.execute("INSERT INTO history (stock, price, time, user_id, shares, status) VALUES (?, ?, ?, ?, ?, ?)",
                   symbol, unit_price, datetime.now(), user_id, shares, "buy")

        # Update user's cash balance (rounding to 2 decimal places)
        new_balance = round(current_balance - total_cost, 2)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, user_id)

        # Redirect to the home page
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions_db = db.execute(
        "SELECT stock, price, time, shares, status FROM history WHERE user_id = ? ORDER BY time DESC",
        user_id
    )
    print(transactions_db)
    return render_template("history.html", transactions=transactions_db)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/login")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must provide symbol", 400)

        # Look up the stock price
        stock = lookup(symbol)

        if not stock:
            return apology("invalid symbol", 400)

        # Redirect to the result page using GET method, passing stock symbol and price
        return redirect(f"/quote_result?symbol={stock['symbol']}&price={stock['price']}")

    # Render the form for a GET request
    return render_template("quote.html")


@app.route("/quote_result")
@login_required
def quote_result():
    """Show the stock quote result."""
    symbol = request.args.get("symbol")
    price = float(request.args.get("price"))
    print(symbol, price)
    # Ensure price is formatted as a string or number, not None
    if not symbol or not price:
        return apology("stock information is missing", 400)

    # Render the result page
    return render_template("stocks.html", symbol=symbol, price=price)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        username = request.form.get("username")
        session["username"] = username
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)
        if not password or confirmation != password:
            return apology("Error while setting password", 400)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                       username, generate_password_hash(password))
        except ValueError:
            return apology("User already exists", 400)

        return redirect("/login")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Retrieve form data
        user_id = session["user_id"]
        symbol = request.form.get("symbol").upper()  # Ensure symbol is in uppercase
        shares_input = request.form.get("shares")

        # Validate symbol input
        if not symbol:
            return apology("must provide stock symbol", 400)

        # Check if symbol exists and is valid
        stock = lookup(symbol)
        if not stock:
            return apology("invalid stock symbol", 400)

        # Validate shares input
        try:
            shares = int(shares_input)
            if shares <= 0:
                return apology("shares must be a positive integer", 400)
        except ValueError:
            return apology("shares must be a positive integer", 400)

        # Check if user owns enough shares of the stock
        rows = db.execute("SELECT SUM(shares) as total_shares FROM buy WHERE user_id = ? AND stock = ?", user_id, symbol)
        if not rows or not rows[0]["total_shares"]:
            return apology("you do not own any shares of this stock", 400)

        owned_shares = rows[0]["total_shares"]

        if owned_shares < shares:
            return apology("not enough shares to sell", 400)

        # Calculate profit from selling shares
        stock_price = stock["price"]
        total_profit = round(shares * stock_price, 2)

        # Update the database: reduce or remove shares from the `buy` table
        if shares == owned_shares:
            # Delete the record if all shares are sold
            db.execute("DELETE FROM buy WHERE user_id = ? AND stock = ?", user_id, symbol)
        else:
            # Otherwise, just update the share count
            db.execute("UPDATE buy SET shares = shares - ? WHERE user_id = ? AND stock = ?", shares, user_id, symbol)

        # Insert the transaction into the history table
        db.execute("INSERT INTO history (stock, price, time, user_id, shares, status) VALUES (?, ?, ?, ?, ?, ?)",
                   symbol, stock_price, datetime.now(), user_id, shares, "sell")

        # Update the user's cash balance
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_profit, user_id)

        # Redirect to the home page
        return redirect("/")

    else:
        # Get all stocks the user owns for the select menu
        user_id = session["user_id"]
        stocks = db.execute("SELECT stock FROM buy WHERE user_id = ? GROUP BY stock", user_id)
        return render_template("sell.html", symbols=[stock['stock'] for stock in stocks])
