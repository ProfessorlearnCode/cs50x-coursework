#include<stdio.h>
#include<cs50.h>

int main(void)
{
    int n;
    while(true){
        n = get_int("Height: ");
        if(n > 8){
            continue;
        }
        if(n < 1){
            continue;
        }
        else{
            break;
        }
    }


    for(int i = 0; i < n; i++)
    {
        for(int j = i; j < n - 1; j++)
        {
            printf(" ");
        }
        for(int k = 0; k < i + 1; k++){
            printf("#");
        }
        printf("  ");
        for(int a = 0; a < i + 1;  a++){
            printf("#");
        }

        printf("\n");
    }


}
