#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string s = get_string("Text: ");
    float letters = 0;
    float words = 1;
    float sentences = 0;
    float letters_average;
    float sentence_average;
    int grade;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i]==' ')
        {
            words++;
        }
        else if (s[i] == '!' || s[i] == '?' || s[i] == '.')
        {
            sentences++;
        }
        else if (((s[i] >= 'A') && (s[i] <= 'Z')) || ((s[i] >= 'a') && (s[i] <= 'z')))
        {
            letters++;
        }
    }
    letters_average = (letters) / (words) * 100;
    sentence_average = (sentences) / (words) * 100;
    //printf("Words: %f Sentences: %f Letters: %f Let_Avg: %f Sent_Avg: %f\n",words,sentences,letters,letters_average,sentence_average);
    grade = round((0.0588 * letters_average) - (0.296 * sentence_average) - (15.8));
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
    return 0;

}