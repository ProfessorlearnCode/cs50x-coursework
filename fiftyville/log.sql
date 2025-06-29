-- Keep a log of any SQL queries you execute as you solve the mystery.

/*
    - CRIME: Stolen Duck
    - LOCATION: Humphery St on 28th july 2023
        - 2 Crimes were committed (Theft 10.15 | Littering 16.36)
        - Interviews with 3 witnesses mentions 'bakery' for theft but no witness for littering
            - People interviewed on the day of theft: Jose, Eugene1, Barbara, Ruth, Eugene2, Raymond, Lily
                - Ruth mentions; within '10 mins' of theft, thief got into a car (in the 'Bakery Parking lot') and drove away
                  consider the security footage and check which car left at that time?
                - Eugene2 mentions; Did not know the name but recognizable, earlier this morning before arriving at the bakery
                  He was walking by the ATM on "Leggett Street" and saw thief 'withdrawing some money'
                - Raymond mentions; As thief leaves the bakery, they call someone for less than 1 min and Thief mentions in the call
                  that they plan to take the 'earliest flight tomorrow' out of fiftyville and asked the other person to buy the ticket

        - ATM transaction logs
            - Witness Claim; Earlier the morning of the robbery, thief withdrew money at ATM in Leggett Street
                - 8 people withdrew money: Luca, Kenny❌, Taylor❌, Bruce❌, Brooke❌, Iman, Benista, Diana

        - Checking Bakery logs
            - Witness Claim; Within 10 mins of the theft, thief got into the car in Bakery parking lot and drive away
                - Check for the cars that left within that time frame
                - There were 9 people who exited from the lot at the time of theft : Vanessa❌, Bruce❌, Barry, Luca, Sofia❌, Iman, Diana, Kelsey, Taylor
                - Finding MATCHES: Bruce, Luca, Iman, Diana, Taylor

        - Calling logs
            - 9 people called on the day of theft lasting less than 1 min: Sofia, Kelsey, Bruce, Taylor, Diana, Carina, Kenny, Benista
                - Sofia(Jack), Kelsey(larry), Bruce(Robin), Kelsey(Melissa), Taylor(James), Diana(Philip), Carina(Jacqueline), Kenny(Doris), Benista(Anna)
                - Finding MATCHES: Bruce, Taylor, Diana

        - Out of bakery log
            - Witness Claim; As leaving the bakery, thief calls the accomplice for less than a min and plans to leave fiftyville as soon as possible
                - Check for earliest flight out of fiftyville






    - Thief?
        - Made an ATM withdrawal made earlier the morning of the theft
        - Went to parking lot and drove away
        - (Possibility) ATM withdrawal (Leggett Street)|---------*Robbery*---------|Car Drive-away (Bakery Parking lot)
    - Accomplice?
        - Booked tickets for getting out of Fiftyville on the earliest flight

    - Escape City?
        - NYC
*/



-- Crime Reports in the specified time
SELECT id, street, description FROM crime_scene_reports
    WHERE day = 28 AND month = 7 AND year = 2023;

    -- Crime Happened on Humphrey Street
    SELECT id, street, description FROM crime_scene_reports
    WHERE day = 28 AND month = 7 AND year = 2023 AND street = 'Humphrey Street';

-- Interviews conducted on the day of theft => People Names
SELECT id, name FROM interviews
    WHERE day = 28 AND month = 7 AND year = 2023;

    -- Ruth interview Transcript
    SELECT name, transcript FROM interviews
        WHERE id = 161;

    -- Eugene2 interview Transcript
    SELECT name, transcript FROM interviews
        WHERE id = 162;

    -- Raymond interview Transcript
    SELECT name, transcript FROM interviews
        WHERE id = 163;

------------------------------------------------------------------------------------------------------------------------------------

-- ATM Transactions record retrieval on the day of theft => IDs, accno, type, amount
SELECT id, account_number, atm_location, transaction_type, amount FROM atm_transactions
    WHERE day = 28 AND month = 7 AND year = 2023 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
ORDER BY id ASC;

    -- People who withdrew money on the day of theft from Leggett street
    SELECT p.id, p.name, p.license_plate, p.phone_number,p.passport_number,
        b.account_number,
        a.id, a.atm_location
        FROM atm_transactions a JOIN bank_accounts b
        ON a.account_number = b.account_number JOIN people p
        ON p.id = b.person_id
        WHERE a.day = 28 AND a.month = 7 AND a.year = 2023 AND a.atm_location = 'Leggett Street' AND a.transaction_type = 'withdraw'
    ORDER BY a.id ASC;

------------------------------------------------------------------------------------------------------------------------------------

-- Bakery Security log to reveal the identity of drive-away car
SELECT * FROM bakery_security_logs
    WHERE day = 28 AND hour BETWEEN 9 AND 11;

    -- To determine which car exited on the speified timeframe (10 mins)
    SELECT license_plate, hour, minute, activity FROM bakery_security_logs
        WHERE day = 28 AND hour = 10 AND activity = 'exit' AND minute BETWEEN 10 AND 35;


-- Determining the people who left the lot at the time of theft
SELECT p.name, p.phone_number,
       bk.license_plate, bk.hour, bk.minute FROM people p JOIN bakery_security_logs bk
       ON p.license_plate = bk.license_plate
       WHERE bk.day = 28 AND bk.hour = 10 AND bk.activity = 'exit' AND bk.minute BETWEEN 10 AND 35;

------------------------------------------------------------------------------------------------------------------------------------

-- Phone Calls made on the day of the theft => id, caller, receiver, duration
SELECT id, caller, receiver, duration FROM phone_calls
    WHERE year = 2023 AND month = 7 AND day = 28;


-- Determining the people who called at the day of theft lasting less than a min
    -- Callers
    SELECT p.name, p.phone_number, p.license_plate, p.passport_number,
        ph.receiver, ph.day, ph.duration
        FROM people p JOIN phone_calls ph
        ON ph.caller = p.phone_number
        WHERE ph.year = 2023 AND ph.month = 7 AND ph.day = 28 AND ph.duration < 60
    ORDER BY p.name;

    -- Receivers
    SELECT p.name, p.phone_number, p.license_plate, p.passport_number,
        ph.caller, ph.day, ph.duration
        FROM people p JOIN phone_calls ph
        ON ph.receiver = p.phone_number
        WHERE ph.year = 2023 AND ph.month = 7 AND ph.day = 28 AND ph.duration < 60;

------------------------------------------------------------------------------------------------------------------------------------

SELECT p.name, p.license_plate, p.phone_number,
       pass.flight_id
       FROM people p JOIN passengers pass
       ON p.passport_number = pass.passport_number
       WHERE p.name in (
            SELECT p.name
                FROM people p JOIN phone_calls ph
                ON ph.caller = p.phone_number
                WHERE ph.year = 2023 AND ph.month = 7 AND ph.day = 28 AND ph.duration < 60
       )
ORDER BY p.name;




SELECT p.name,
       pass.flight_id,
       f.origin_airport_id, f.destination_airport_id, f.hour, f.minute, f.day,
       a.city
       FROM people p JOIN passengers pass
       ON p.passport_number = pass.passport_number JOIN flights f
       ON f.id = pass.flight_id JOIN airports a
       ON f.origin_airport_id = a.id
       WHERE p.name in (
            SELECT p.name
                FROM people p JOIN phone_calls ph
                ON ph.caller = p.phone_number
                WHERE ph.year = 2023 AND ph.month = 7 AND ph.day = 28 AND ph.duration < 60
       ) AND f.day BETWEEN 28 AND 29

ORDER BY f.day;


------------------------------------------------------------------------------------------------------------------------------------


SELECT * from phone_calls
    WHERE caller = '(826) 555-1652';

SELECT * from phone_calls
    WHERE caller = '(829) 555-5269';


SELECT * from bakery_security_logs
    WHERE license_plate = '30G67EN';

SELECT p.name,
       pass.flight_id,
       f.origin_airport_id, f.destination_airport_id, f.hour, f.minute, f.day,
       a.city
       FROM people p JOIN passengers pass
       ON p.passport_number = pass.passport_number JOIN flights f
       ON f.id = pass.flight_id JOIN airports a
       ON f.origin_airport_id = a.id
       WHERE p.name in (
            SELECT p.name
            FROM atm_transactions a JOIN bank_accounts b
            ON a.account_number = b.account_number JOIN people p
            ON p.id = b.person_id
            WHERE a.day = 28 AND a.month = 7 AND a.year = 2023 AND a.atm_location = 'Leggett Street' AND a.transaction_type = 'withdraw'
       ) AND f.day BETWEEN 28 AND 29
ORDER BY f.day;
