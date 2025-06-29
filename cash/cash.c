#include<stdio.h>
#include<cs50.h>

int User_change(void);
int calculate_quaters(int change);
int calculate_dimes(int change);
int calculate_nickels(int change);
int calculate_pennies(int change);

int main (void)
{
    int owed_change = User_change();

    // Quaters
    int no_of_quaters = calculate_quaters(owed_change);
    printf("No of Quaters: %d\n", no_of_quaters);
    owed_change = owed_change - (25 * no_of_quaters);


    // Dimes
    int no_of_dimes = calculate_dimes(owed_change);
    printf("No of dimes: %d\n", no_of_dimes);
    owed_change = owed_change - (10 * no_of_dimes);


    // Nickels
    int no_of_nickels = calculate_nickels(owed_change);
    printf("No of nickels: %d\n", no_of_nickels);
    owed_change = owed_change - (5 * no_of_nickels);



    // Pennies
    int no_of_pennies = calculate_pennies(owed_change);
    printf("No of Pennies: %d\n", no_of_pennies);
    owed_change = owed_change - (1 * no_of_pennies);



    // Sum of all the coins
    int sum = no_of_pennies + no_of_nickels + no_of_dimes + no_of_quaters;
    printf("Change Owed: %d\n", sum);
}






int User_change(void)
{
    int c;
    while(true){
        c = get_int("Change Owed? ");
        if (c < 0)
        {
            continue;
        }
        else
        {
            return c;
        }
    }

}



int calculate_quaters(int change)
{
    int no_of_quaters = 0;
    while(change >= 25)
    {
        no_of_quaters ++;
        change -= 25;
    }
    return no_of_quaters;
}

int calculate_dimes(int change)
{
    int no_of_dimes = 0;
    while(change >= 10)
    {
        no_of_dimes++;
        change -= 10;
    }
    return no_of_dimes;
}

int calculate_nickels(int change)
{
    int no_of_nickels = 0;
    while(change >= 5)
    {
        no_of_nickels++;
        change -= 5;
    }
    return no_of_nickels;
}

int calculate_pennies(int change)
{
    int no_of_pennies = 0;
    while(change >= 1)
    {
        no_of_pennies++;
        change -= 1;
    }
    return no_of_pennies;
}




