-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Discover interviews
SELECT * FROM crime_scene_reports
WHERE year = 2023 AND month = 07 AND day = 28 AND street = 'Humphrey Street';

-- List interviews to analyse
SELECT * FROM interviews
WHERE year = 2023 AND month = 07 AND day = 28;

-- List ATM Transactions in date AND location indicated in the interviews
SELECT * FROM atm_transactions
WHERE year = 2023 AND month = 07 AND day = 28 AND atm_location = 'Leggett Street';

-- List ATM Transactions in date AND location indicated in the interviews and discover the people names
SELECT people.name, people.phone_number, people.passport_number, people.license_plate
FROM atm_transactions JOIN bank_accounts
ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE atm_transactions.year = 2023
AND atm_transactions.month = 07 AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw'
ORDER BY people.name;

-- List Security logs and discover who is present in the bakery parking lot to verify with ATM transaction information
SELECT people.name, people.phone_number, people.passport_number, people.license_plate
FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year = 2023
AND bakery_security_logs.month = 07
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15
AND bakery_security_logs.minute <= 25
ORDER BY people.name;

-- After verify data from ATM transactions and security logs (First list of suspects)
SELECT people.name, people.phone_number, phone_calls.duration, phone_calls.receiver, people.passport_number
FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE caller IN ("(367) 555-5533", "(770) 555-1861", "(829) 555-5269", "(389) 555-5198")
AND phone_calls.year = 2023
AND phone_calls.month = 07
AND phone_calls.day = 28
AND phone_calls.duration <= 60
ORDER BY people.name;

-- Select first flight day after stolen to discover where the thief scape to
SELECT flights.id, flights.origin_airport_id, flights.destination_airport_id, airports.city
FROM flights JOIN airports
ON flights.origin_airport_id = airports.id
WHERE year = 2023
AND month = 07
AND day = 29
AND origin_airport_id = 8
ORDER BY hour;

-- Select passangers from flight and discover who is the thief
SELECT flights.id, passengers.passport_number
FROM flights JOIN passengers
ON flights.id = passengers.flight_id
WHERE flight_id = 36
ORDER BY passport_number;

-- Discover thief accomplice from the number called before theft
SELECT * FROM people WHERE phone_number = '(375) 555-8161';
