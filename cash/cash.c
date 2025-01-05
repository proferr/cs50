#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Prompt the user for change owed, in cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // Calculate quarters
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate dimes
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate nickels
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate pennies
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum and print coins
    int coins = quarters + dimes + nickels + pennies;
    printf("%i\n", coins);
}

int calculate_quarters(int cents)
{
    return cents / 25;
}

int calculate_dimes(int cents)
{
    return cents / 10;
}

int calculate_nickels(int cents)
{
    return cents / 5;
}

int calculate_pennies(int cents)
{
    return cents;
}
