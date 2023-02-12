#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main (int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key.\n");
        return 1;
    }
    int size = strlen(argv[1]);
    if (size!=26)
    {
       printf("Usage: ./substitution key.\n");
       return 1;
    }
    else if (size==26)
    {
        for (int i = 0; i < size; i++)
        {
            if (isdigit(argv[1][i]))
            {
                 printf("Usage: ./substitution key. Key Should Not Contain a Number\n");
                 return 1;
            }
            for (int j = i + 1; j < size - 1; j++)
            {
                if (argv[1][i] == argv[1][j])
                {
                     printf("Usage: ./substitution key. Key Should Contain no Duplicates.\n");
                     return 1;
                }
            }
        }
    }
    string answer = get_string("PlainText: ");
    int size2 = strlen(answer);
    char cipher[size2];

    for (int i = 0; i < size2; i++)
    {
        int n;
        if (isalpha(answer[i]))
        {
            if (isupper(answer[i]))
            {
                 n = answer[i] - 'A';
                if(islower(argv[1][n]))
                {
                    cipher[i] = argv[1][n] - 32;
                }
                else
                {
                    cipher[i] = argv[1][n];
                }
            }
            else if (islower(answer[i]))
            {
                n = answer[i] - 'a';
                if (isupper(argv[1][n]))
                {
                    cipher[i] = argv[1][n] + 32;
                }
                else
                {
                    cipher[i] = argv[1][n];
                }
            }
        }
        else
        {
            cipher[i] = answer[i];
        }
    }
    printf("ciphertext: %s\n", cipher);

}