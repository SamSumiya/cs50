#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
// set chars and sentences to 0 and words to 1
// if any char is between 'a' to 'z' or 'A' to 'Z', char will increment by one
// if char encounters ' ', it will increment by one and in case of the last word which does not end with ' '
// I will add one to the words count by in the calculation
// if char encounters . or ! or ?, sentence will increment by one
    int chars = 0;
    int words = 0;
    int sentences = 0;

// use get_string to prompt user to enter a string of chars
    string text = get_string("Input: \n");

// use for loop to iterate through the entire string and make the stopping point at the \0 which is where the string stops

    for (int i = 0; text[i] != '\0'; i++)
    {

// make sure that I confine the chars within uppercase and lowercase alphabets
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
// incremnet chars
            chars++;
        }
// when the char encounters ' ', increment words by one
        else if (text[i] == ' ')
        {
            words++;
        }
// when the char encounters . or ! or ?, increment sentences by one
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }


// index = 0.0588 * L - 0.296 * S - 15.8
// Here, L is the average number of letters per 100 words in the text, 
// and S is the average number of sentences per 100 words in the text.
 
// convert the index to float so I can get more accurate number
// as the description says, use the float words / all the chars and float sentences / chars to get the average number
// since the last word will not be counted, I have to add one to words to make the count corret
    float index = 0.0588 * (100 * (float)chars / (float)(words + 1)) - 0.296 * (100 * (float)sentences / (float)(words + 1)) - 15.8;  
// convert the float number to an integer number 
    int idx = (int) round(index);
// use a boolean expression to get the right answer
// the range will be between 1 and 15
    if (idx >= 1 && idx < 16) 
    {
// use the already rounded idx to print out the grade X 
        printf("Grade %i\n", idx); 
    }
    else if (idx >= 16) 
    {
// follow the instruction
        printf("Grade 16+\n"); 
    }
    else 
    {
// follow the instruction
        printf("Before Grade 1\n");
    }
    
}