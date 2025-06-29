#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

int CLI_check_KEY(int count, string vector);
int STRING_TO_INT_CHECK(string arguments);
bool alphaNumeric_check(string vector);
string Caeser_substitution(int key, string message);
bool Numeric_check(string vector);




int main(int argc, string argv[])
{
    /*
        - Checking number of inputs
        - Checking whether the input is num or not
        - Checking for any alphanumeric data
    */

    // argc = 2;
    // argv[1] = "15";
    int count = argc;
    string argument = argv[1];
    int key = CLI_check_KEY(argc, argument);
    if(key == 0)
    {
        return 1;
    }

    // taking plain-text input
    string plaintext = get_string("Plaintext:  ");


    /*
        Rotation of alphabets if it touches they boundary
    */

    string ciphertext = Caeser_substitution(key, plaintext);
    printf("Ciphertext: %s\n", ciphertext);


    return 0;
}


string Caeser_substitution(int key, string message)
{
    int value = 0;
    int new_answer = 0;
    int rotation = 0;
    int final_rotation = 0;

    /*
    Assume that, we have key = 15 and character = 'H' (72)
    So we do?

    char 'H' - 'A' = ANSWER
    72 - 65 = 7

    key + ANSWER = NEW_ANS
    15 + 7 = 22

    NEW_ANS % 'A' = FINAL_ROTATION
    22 mod 26 = 22

    ASCII code for the rotated value
    65 + 22 = 87

    */




    for(int i = 0; i < strlen(message); i++)
    {
        if (!Numeric_check(message))
        {
            // For Capital letters
            if(65 <= message[i] && message[i] <= 90)
            {
                value = message[i] - 65;
                new_answer = key + value;
                rotation = new_answer % 26;
                final_rotation = rotation + 65;
                message[i] = (char) final_rotation;
            }

            // For Small letters
            if(97 <= message[i] && message[i] <= 122)
            {
                value = (int) message[i] - 97;
                new_answer = key + value;
                rotation = new_answer % 26;
                final_rotation = rotation + 97;
                message[i] = (char) final_rotation;
            }
            else
            {
                continue;
            }
        }
        else
        {
            break;
        }
    }

    return message;

}





bool Numeric_check(string vector)
{
    for(int i = 0; i < strlen(vector); i++)
    {
        if(isdigit(vector[i]))
        {
            return true;
        }
        else
        {
            continue;
        }
    }

    return false;
}
bool alphaNumeric_check(string vector)
{
    for(int i = 0; i < strlen(vector); i++)
    {
        if(isalpha(vector[i]))
        {
            return true;
        }
        else
        {
            continue;
        }
    }

    return false;
}



int CLI_check_KEY(int count, string vector)
{
        if(count > 2 || count == 1)
    {
        printf("Usage: ./caesar key\n");
        return 0;
    }

    int Key = STRING_TO_INT_CHECK(vector);

    if(Key == 0)
    {
        printf("Usage: ./caesar key\n");
        return 0;
    }

    return Key;
}

int STRING_TO_INT_CHECK(string arguments)
{
    if (alphaNumeric_check(arguments))
    {
        return 0;
    }
    else
    {
        int caeser_key = (int) atoi(arguments);
        printf("Caeser Key: %i\n", caeser_key);
        return caeser_key;
    }

}













