from cs50 import get_float

while True:
    cash = round(get_float("Change owed: ") * 100)
    if cash > 0:
        break

coins = [25, 10, 5, 1]


# loop only 4 times -> big O(4) )
def calc(cash, coins):

    count = 0

    for i in coins:
        coins = cash // i
        cash = cash - (coins * i)
        count += coins

    print(count)


calc(cash, coins)
