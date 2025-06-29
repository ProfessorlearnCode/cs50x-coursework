#include<stdio.h>
#include<cs50.h>

int len(long CC_Number);
int LUHN1(long CC_Number, int length);
int LUHN2(int sum, long CC_Number, int length);
int checksum(int a, int b);
int checkLenDigits(long CC, int length);
// void CC_type(int final_sum, long CC_number, int length);

int main(void)
{
    long CC;
    do{
        CC = get_long("Number: ");
    } while (len(CC) < 10);

    if(checksum(LUHN1(CC, len(CC)), LUHN2(LUHN1(CC, len(CC)), CC, len(CC))) != 0)
    {
        checkLenDigits(CC, len(CC));
    }

}


int len(long CC_Number)
{
    int length = 0;
    while(CC_Number > 0)
    {
        length++;
        CC_Number /= 10;
    }
    return length;
}

int LUHN1(long CC_Number, int length)
{
    long last_digits = 0;
    long attached_digit = 0;
    long doubled_attached_digit = 0;
    int double_digit_Sum = 0;
    int sum = 0;

    while(length > 0)
    {
        last_digits = CC_Number % 100;
        attached_digit = last_digits / 10;
        length--;
        CC_Number = CC_Number / 100;

        doubled_attached_digit = attached_digit * 2;
        double_digit_Sum = (doubled_attached_digit % 10) + (doubled_attached_digit / 10);
        sum = double_digit_Sum + sum;
    }

    return sum;
}

int LUHN2(int sum, long CC_number, int length)
{
    long last_digit = 0;
    long attached_digit = 0;
    int Final_sum = 0;

    while(length > 0)
    {
        last_digit = CC_number % 10;
        length --;
        CC_number = CC_number / 100;

        Final_sum = Final_sum + last_digit;
    }
    Final_sum = sum + Final_sum;
    return Final_sum;
}


int checksum(int a, int b)
{
    int CHECKSUM = b;
    if (CHECKSUM % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    else
    {
        return CHECKSUM;
    }
}


int checkLenDigits(long CC, int length)
{
    while(CC > 100)
    {
        CC = CC / 10;
    }
    int initial_digits = (int) CC;

    if(length == 15)
    {
        if(initial_digits == 34 || initial_digits == 37)
        {
            printf("AMEX\n");
            return 15;
        }
        else{
            printf("INVALID\n");
            return 0;
        }
    }
    else if(length == 16 || length == 13)
    {
        if((initial_digits == 51 || initial_digits == 52 || initial_digits == 53 || initial_digits == 54 || initial_digits == 55) && length == 16)
        {
            printf("MASTERCARD\n");
            return 9;
        }
        else if (initial_digits / 10 == 4)
        {
            printf("VISA\n");
            return 4;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}


