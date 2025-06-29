

def get_input() -> float :
    while(True):
        try:
            change = float(input("Change: $"))
            if change < 0:
                continue
            else:
                return change
        except ValueError or TypeError:
            continue


def Quaters(cents):
    quaters = cents / 25
    remaining_balance = cents % 25

    return int(quaters), remaining_balance

def Dimes(quaters):
    dimes = quaters / 10
    remaining_balance = quaters % 10

    return int(dimes), remaining_balance

def Nickels(dimes):
    nickels = dimes / 5
    remaining_balance = dimes % 5

    return int(nickels), remaining_balance

def Pennies(nickels):
    pennies = nickels / 1
    remaining_balance = nickels % 1

    return int(pennies), remaining_balance



def main():

    change = get_input()
    cents = change * 100

    quaters, quater_remBal = Quaters(int(cents))
    dimes, dime_remBal = Dimes(quater_remBal)
    nickels, nickel_remBal = Nickels(dime_remBal)
    pennies, pennies_remBal = Pennies(nickel_remBal)

    total_sum = quaters + dimes + nickels + pennies


    print(total_sum)


if __name__ == "__main__":

    main()
