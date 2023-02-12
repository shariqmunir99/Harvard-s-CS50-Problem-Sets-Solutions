#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string s);

int main(int argc, string argv[])
{

    if (argc < 2 || argc > 2 || only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]);
    string answer  = get_string("Plain Text: ");
    const int size = strlen(answer);
    char cipher[size];
    for (int i = 0; i < strlen(answer); i++)
    {
        int n;
        char temp = answer[i];
        if (isalpha(temp))
        {
            if (isupper(temp))
            {
                n = answer[i] - 'A';
                temp = (n + key) % 26;
                temp += 'A';

            }
            else if (islower(temp))
            {
                n = answer[i] - 'a';
                temp = (n + key) % 26;
                temp += 'a';
            }
        }
        cipher[i] = temp;

    }
    printf("ciphertext: %s\n", cipher);
}

bool only_digits(string s)
{
    bool flag = true;
    for(int i = 0; i < strlen(s); i++)
    {
        if(isdigit(s[i]))
        {
            flag = false;
        }
        else
        {
            flag = true;
        }
    }
    return flag;
}
