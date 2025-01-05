#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    //  Counting the text grade
    float av_letters = (float) letters / (float) words * 100; // average number of letters per 100 words
    float av_sentences = (float)  sentences / (float)  words * 100; // average number of sentences per 100 words
    float index = 0.0588 * av_letters - 0.296 * av_sentences - 15.8; // Colema-liau

    if (index < 1)
    {
        printf("Before Grade 1\n");

    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %d\n", (int) round(index));

    }

}

int count_letters(string text)
{
    // Return the number of letters in text
    int num_letter = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            num_letter++;
        }
    }
    return num_letter;
}

int count_words(string text)
{
    // Return the number of words in text
    int num_words = 1;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            num_words++;
        }
    }
    return num_words;
}

int count_sentences(string text)
{
    // Return the number of sentences in text
    int num_sentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if ('.' == text[i] || '!' == text[i] || '?' == text[i])
        {
            num_sentences++;
        }
    }
    return num_sentences;
}
