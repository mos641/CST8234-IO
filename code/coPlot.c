/******************************************************************************************
*Filename:           coPlot.c
*Version:            1
*Course:             C Language CST8234
*Assignment Name:    Lab 04: To demonstrate command of I/O
*Purpose:            Demonstrate command of I/O by taking various commands from the user
******************************************************************************************/

#include "header.h"

/******************************************************************************************
*Function name:              main
*Purpose:                    Main function for the program calls other functions and runs command of I/O
*Function In parameters:     None
*Function Out parameters:    An integer for function success
*Version:                    1
*Author:                     mos
******************************************************************************************/
int main()
{
    char input[50];
    char *command;
    char *option1;
    char *option2;
    int bitOp;
    int op1;
    int op2;

    srand(time(NULL));

    /* loop until exit */
    do
    {
        /* ask for input */
        printf("> Please enter a command to run.\n");
        fgets(input, 50, stdin);

        /* get the first portion of input as teh command, following ones as options */
        command = strtok(input, " ");
        if (command != NULL)
        {
            option1 = strtok(NULL, " ");
        }
        if (option1 != NULL)
        {
            option2 = strtok(NULL, " ");
        }

        /* validate input */
        if (option1 == NULL)
        {
            command[strcspn(command, "\n")] = 0;
            /* check if command is exit or random, otherwise print error */
            if (strcmp(command, "exit") == 0)
            {
                printf("Good Bye!\n");
            }
            else if (strcmp(command, "random") == 0)
            {
                /* call function */
                randomSentence();
            }
            else
            {
                printf("Invalid Command. Try again. >%s<\n", input);
            }
        }
        else if (option2 == NULL)
        {
            option1[strcspn(option1, "\n")] = 0;
            /* check if command is reverse then print reversed, or print error */
            if (strcmp(command, "reverse") == 0)
            {
                reverse(option1);
            }
            else
            {
                printf("Invalid command. Try again. >%s<\n", input);
            }
        }
        else
        {
            /* check for bit command, set int for function */
            if (strcmp(command, "bit_or") == 0)
            {
                bitOp = 1;
            }
            else if (strcmp(command, "bit_and") == 0)
            {
                bitOp = 2;
            }
            else if (strcmp(command, "bit_xor") == 0)
            {
                bitOp = 3;
            }
            else if (strcmp(command, "bit_shift_left") == 0)
            {
                bitOp = 4;
            }
            else if (strcmp(command, "bit_shift_right") == 0)
            {
                bitOp = 5;
            }
            else
            {
                printf("Invalid command, try again. >%s<\n", input);
                bitOp = -1;
            }

            /* confirm valid operands */
            if (bitOp != -1)
            {
                op1 = atoi(option1);
                op2 = atoi(option2);
                if (op1 == 0 || op2 == 0)
                {
                    if (op1 == 0 && option1[0] == 48 && option1[1] == '\0')
                    {
                        /* option 1 was inputted as 0 */
                    }
                    else
                    {
                        printf("Invalid integer number, try again.");
                        bitOp = -1;
                    }

                    if (bitOp != -1 && op2 == 0 && option2[0] == 48 && option2[1] == '\0')
                    {
                        /* option 2 was inputted as 0 */
                    }
                    else
                    {
                        printf("Invalid integer number, try again.");
                        bitOp = -1;
                    }
                }
            }

            if (bitOp != -1)
            {
                /* call function for operation */
                bitOperation(op1, op2, bitOp);
            }
        }

    } while (strcmp(command, "exit") != 0);

    return EXIT_SUCCESS;
}

/******************************************************************************************
*Function name:              reverse
*Purpose:                    Reverses a supplied string and prints it to the console
*Function In parameters:     A string to reverse
*Function Out parameters:    None
*Version:                    1
*Author:                     mos
******************************************************************************************/
void reverse(char *str)
{
    int length;
    char *revStr;
    int i;

    /* get the length for looping */
    length = strlen(str);

    /* allocate memory for string */
    revStr = calloc(length, sizeof(char));
    if (revStr == NULL)
    {
        printf("Error - could not allocate memory for reversed string \n");
        return;
    }

    /* loop through string and assign each character in reverse */
    for (i = 0; i < length; i++)
    {
        revStr[i] = str[length - i - 1];
    }

    printf("%s\n", revStr);

    /* free memory */
    free(revStr);
}

/******************************************************************************************
*Function name:              bitOperation
*Purpose:                    Performs a specified bitwise operation and prints the result
*Function In parameters:     Two numbers to operate with, and a number for operation type
*Function Out parameters:    None
*Version:                    1
*Author:                     mos
******************************************************************************************/
void bitOperation(int num1, int num2, int op)
{

    switch (op)
    {
    case 1:
        /* bit or */
        printf("%d\n", num1 | num2);
        break;
    case 2:
        /* bit and */
        printf("%d\n", num1 & num2);
        break;
    case 3:
        /* bit xor */
        printf("%d\n", num1 ^ num2);
        break;
    case 4:
        /* bit shift left */
        printf("%d\n", num1 << num2);
        break;
    case 5:
        /* bit shift right */
        printf("%d\n", num1 >> num2);
        break;
    }
}

/******************************************************************************************
*Function name:              randomSentence
*Purpose:                    Generates a sentence of random words and prints to the screen
*Function In parameters:     None
*Function Out parameters:    None
*Version:                    1
*Author:                     mos
******************************************************************************************/
void randomSentence()
{
    char *article[] = {"the", "a", "one", "about", "some", "any"};
    char *noun[] = {"men", "women", "dog", "town", "pen", "mouse", "car"};
    char *verb[] = {"wrote", "barked", "ran", "walked", "clicked"};
    char *preposition[] = {"to", "from", "at", "over", "under", "on"};
    char *sentence[6];
    int i;
    char upper[7];
    char period = ' ';

    /* create 20 sentences based on words picked by a randomly generated number */
    for (i = 0; i < 20; i++)
    {
        /* if its the last sentence, make the first letter a capital and end with a period, set each word in sentence to random word from arrays */
        if (i == 19)
        {
            strcpy(upper, article[rand() % 6]);
            upper[0] = toupper(upper[0]);
            sentence[0] = upper;
            period = '.';
        }
        else
        {
            sentence[0] = article[rand() % 6];
        }
        sentence[1] = noun[rand() % 7];
        sentence[2] = verb[rand() % 5];
        sentence[3] = preposition[rand() % 6];
        sentence[4] = article[rand() % 6];
        sentence[5] = noun[rand() % 7];

        /* print the sentence */
        printf("%s %s %s %s %s %s%c\n", sentence[0], sentence[1], sentence[2], sentence[3], sentence[4], sentence[5], period);
    }
}