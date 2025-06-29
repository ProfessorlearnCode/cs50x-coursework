#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>

// Making a Hash set to determine the key value pair
const char CHARACTER_ARRAY[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const int  VALUE_ARRAY[26]     = { 1,   3,	 3,   2,   1,	4, 	 2,	  4,   1,	8,	 5,	  1,   3, 	1,	 1,   3,   10,	1, 	 1,	  1,   1, 	4,	 4,   8,   4,	10};

int Word_hash(string word);
int Hash_lookup(char character);

int main (void)
{
    string user1, user2;
    user1 = get_string("Player 1: ");
    user2 = get_string("Player 2: ");
    int hash_value1 = Word_hash(user1);
    int hash_value2 = Word_hash(user2);

    // Comparison
    if (hash_value1 > hash_value2)
    {
        printf("Player 1 Wins!\n");
    }
    else if (hash_value1 < hash_value2)
    {
        printf("Player 2 Wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}


int Hash_lookup(char character)
{
    //This function returns the value for the character from the hash table
    // This loop matches the value of the character and on the same index returns the value
    for (int i = 0; i <= 26; i++)
    {
        if(character == CHARACTER_ARRAY[i])
        {
            return VALUE_ARRAY[i];
        }
        else
        {
            continue;
        }
    }
    printf("Value Not Found!\n");
    return 0;
}



int Word_hash(string word)
{
    int sum = 0;

    // Prepares the values for hash lookup
    for(int i = 0; i < strlen(word); i++)
    {
        sum += Hash_lookup(tolower(word[i]));
    }
    return sum;
}
