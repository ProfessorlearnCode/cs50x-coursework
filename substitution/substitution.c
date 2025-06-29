#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>


int Validate_key(string key);
void Substitute_Cipher(string key, string plaintext);

int main(int argc, string argv[])
{
    /*
    1. Get CLI input from the user (D)
        - CLI input should not be > 2

    2. Validate the key (D)
        - Ensure the length of Key - 26
            - Use strlen to find the length of the key
        - No numbers/special characters in the Key
            - After finding the len, loop through the key to find any digits or spch
        - No duplicate alphabets in the key
            - Pick the character from the string
            - Loop through the string
            - Count the character, if greater than 1
            - Return 1

    3. Get Plaintext (D)

    4. Substitute Cipher
        - Cipher is case insensitive
        - Determine which Key char, Plaintext maps to
            - Make a hash-string
            - Find the index of the character of the plain-text using the hash-string
            - Use that index to find the character from the key
            - assign it in cipher-text
        - Map the alphabets wrt to its nature (if a islower then map lower substitute)
        - Do not map special characters

    5. Print Cipher
    */

   if(argc > 2 || argc == 1)
   {
        printf("Usage: ./substitution key\n");
        return 1;
   }

   int Key_validation = Validate_key(argv[1]);
   if (Key_validation == 1)
   {
        return 1;
   }

   string plaintext = get_string("Plaintext: ");
   Substitute_Cipher(argv[1], plaintext);


}



int Validate_key(string key)
{
    // Validating Length
    int key_length = strlen(key);
    if (key_length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;    // --> Symbolizes error
    }

    // Validating Digits and Special Characters
    for(int i = 0; i < key_length; i++)
    {
        int ASCII_value = (int) key[i];

        if ((ASCII_value >= 65 && ASCII_value <= 90) || (ASCII_value >= 97 && ASCII_value <= 122))
        {
            continue;
        }
        else
        {
            printf("Key must only contain alphabetical letters\n");
            return 1;    // --> Symbolizes error
        }
    }

    // Validating Duplicating Values
    int count = 0;
    for(int i = 0; i < key_length; i++)
    {
        for(int j = 0; j < key_length; j++)
        {
            if(tolower(key[i]) == tolower(key[j]))
            {
                count++;
            }
            else
            {
                continue;
            }
        }
    }
    if (count > 26)
    {
        printf("Keys must not contain duplicating letters.\n");
        return 1;   // --> Symbolizes Error
    }

    return 0;   // --> Valid
}



void Substitute_Cipher(string key, string plaintext)
{
    string hash_string = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int length_key = strlen(key);
    int length_plaintext = strlen(plaintext);

    string cipher_string = malloc((1 * length_plaintext) + 1);

    for(int i = 0; i < length_plaintext; i++)
    {
        for(int j = 0; j < length_key; j++)
        {
            if(isdigit(plaintext[i]))
            {
                cipher_string[i] = plaintext[i];
            }
            else if(islower(plaintext[i]))
            {
                if (plaintext[i] == tolower(hash_string[j]))
                {
                    cipher_string[i] = tolower(key[j]);
                }

                else
                {
                    continue;
                }

            }
            else if(isupper(plaintext[i]))
            {
                if (plaintext[i] == toupper(hash_string[j]))
                {
                    cipher_string[i] = toupper(key[j]);
                }
                else
                {
                    continue;
                }
            }
            else
            {
                cipher_string[i] = plaintext[i];
            }
        }
    }

    printf("ciphertext: %s\n", cipher_string);
}





















