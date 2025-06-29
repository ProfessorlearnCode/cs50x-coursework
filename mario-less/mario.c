#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get the number of the size of the pyramid
    int size;
    do
    {
        size = get_int("Height: ");
    }
    while (size < 1);

    // Print the number of columns
    //          0; 0 < 5   ; 1
    //          1; 1 < 5   ; 2
    //          2; 2 < 5   ; 3
    //          3; 3 < 5   ; 4
    //          4; 4 < 5   ; 5  --> False | Loop end
    for (int i = 0; i < size; i++)
    {
        // Print the number of rows
        //          0; 0 <  4      ; 1  --> Print
        //          1; 1 <  4      ; 2
        //          2; 2 <  4      ; 3
        //          4; 4 <  4      ; 4  --> False | Loop end
        for (int j = i; j < size - 1; j++)
        {
            // Print the whitespace
            printf(" ");
        }

        // Print the #
        //           0; 0 < 1    ; 1
        //           1; 1 < 2    ; 2
        //           2; 2 < 3    ; 3
        //           3; 3 < 4    ; 4
        //           4; 4 < 4    ; 4    --> False | Loop end
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
