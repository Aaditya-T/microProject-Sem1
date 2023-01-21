//make a calculator where input is taken as string and then the expression are evaluated
#include <stdio.h>
#include <stdlib.h> //for atoi()
#include <ctype.h> //for isdigit()
#include <math.h>

int tokenize(char *exp);
int eval1(int numTokens);
int eval2(int numTokens);
int eval3(int numTokens);
int factorial(int n);

typedef struct token
{
    char type;
    int value;
} token;

token tokens[100];

void main()
{
    char exp[100];
    int numTokens, result;
    printf("Enter the expression: ");
    gets(exp);
    puts("Tokenzing the expression...");
    numTokens = tokenize(exp);
    printf("Number of tokens: %d", numTokens);
    printf("\nArranging the tokens...\n");
    numTokens = eval1(numTokens);
    printf("\nNumber of tokens: %d\n", numTokens);
    numTokens = eval2(numTokens);
    printf("\nNumber of tokens: %d\n", numTokens);
    numTokens = eval3(numTokens);
    printf("\nNumber of tokens: %d\n", numTokens);
    puts("=============");
    printf("| Result: %d |\n", tokens[0].value);
    puts("=============");
}

int tokenize(char *ptr) {
    int i = 0,numBracks=0;
    char *endptr;  //pointer to the end of the string

    while(*ptr != '\0') {
        //check if the character is a digit, if yes then convert it to integer and store it in the array
        if(isdigit(*ptr)) {
            //use strtol to convert a string of characters to a long integer
            tokens[i].type = 'n';
            tokens[i].value = strtod(ptr, &endptr); //convert the string to a long integer
            ptr = endptr; //move the pointer to the end of the string
        } else if(*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/' || *ptr == '^' || *ptr == '!' || *ptr == '%' || *ptr == '(' || *ptr == ')') {
            tokens[i].type = 'o';
            tokens[i].value = *ptr;
            ptr++;
            if (*ptr == '(')
                numBracks++;
        } else if (*ptr == ' ') {
            //skip the spaces
            ptr++;  
        } else {
            printf("Invalid character: %c", *ptr);
            exit(0);
        }
            //increment the index of the array
            i++;
        }
    //if numBracks >1, exit
    if (numBracks > 1)
    {
        puts("Multiple brackets not supported!");
        exit(0);
    }

    return i;
}

int eval1(int numTokens) 
{
    //evaluate the '^' and '!' operators first
    int i,j,brackStart=0,brackEnd,numTempTokens=0;
    token temp[100];
    
    //Detect the parenthesis
    for (i=0;i<numTokens;i++)
    {
        if (tokens[i].value == '(')
        {
            brackStart = i;
        }
        else if (tokens[i].value == ')')
        {
            brackEnd = i;
            break;
        }
    }

    if (brackStart != 0)
    {    
        //place the tokens inside of the parenthesis in a temporary array
        for (i=brackStart+1,j=0;i<brackEnd;i++,j++)
        {
            temp[j].value = tokens[i].value;
            temp[j].type = tokens[i].type;
            numTempTokens++;
        }

        //evaluate the temporary array
        for (i=0;i<numTempTokens;i++)
        {
            if (temp[i].value == '!')
            {
                temp[i-1].value = factorial(temp[i-1].value);
                for (j=i;j<numTempTokens-1;j++)
                {
                    temp[j].value = temp[j+1].value;
                    temp[j].type = temp[j+1].type;
                }
                numTempTokens = numTempTokens - 1;
                i--;
            } else if (temp[i].value == '^')
            {
                temp[i-1].value = pow(temp[i-1].value,temp[i+1].value);
                for (j=i;j<numTempTokens-2;j++)
                {
                    temp[j].value = temp[j+2].value;
                    temp[j].type = temp[j+2].type;
                }
                numTempTokens = numTempTokens - 2;
                i--;
            }
        }

        for (i=0;i<numTempTokens;i++)
        {
            if (temp[i].value == '*')
            {
                temp[i-1].value = temp[i-1].value * temp[i+1].value;
                for (j=i;j<numTempTokens-2;j++)
                {
                    temp[j].value = temp[j+2].value;
                    temp[j].type = temp[j+2].type;
                }
                numTempTokens = numTempTokens - 2;
                i--;
            }
            else if (temp[i].value == '/')
            {
                temp[i-1].value = temp[i-1].value / temp[i+1].value;
                for (j=i;j<numTempTokens-2;j++)
                {
                    temp[j].value = temp[j+2].value;
                    temp[j].type = temp[j+2].type;
                }
                numTempTokens = numTempTokens - 2;
                i--;
            }
            else if (temp[i].value == '%')
            {
                temp[i-1].value = temp[i-1].value % temp[i+1].value;
                for (j=i;j<numTempTokens-2;j++)
                {
                    temp[j].value = temp[j+2].value;
                    temp[j].type = temp[j+2].type;
                }
                numTempTokens = numTempTokens - 2;
                i--;
            }
        }

        for (i=0;i<numTempTokens;i++)
        {
            if (temp[i].value == '+')
            {
                temp[i-1].value = temp[i-1].value + temp[i+1].value;
                for (j=i;j<numTempTokens-2;j++)
                {
                    temp[j].value = temp[j+2].value;
                    temp[j].type = temp[j+2].type;
                }
                numTempTokens = numTempTokens - 2;
                i--;
            } else if (temp[i].value == '-')
            {
                temp[i-1].value = temp[i-1].value - temp[i+1].value;
                for (j=i;j<numTempTokens-2;j++)
                {
                    temp[j].value = temp[j+2].value;
                    temp[j].type = temp[j+2].type;
                }
                numTempTokens = numTempTokens - 2;
                i--;
            }
        }

        tokens[brackStart].value = temp[0].value;
        tokens[brackStart].type = temp[0].type;

        for (i=brackStart+1,j=brackEnd + 1;i<numTokens;i++,j++)
        {
            tokens[i].value = tokens[j].value;
            tokens[i].type = tokens[j].type;
        }
        numTokens = numTokens - (brackEnd - brackStart);
    }

    for (i=0;i<numTokens;i++)
    {
        if (tokens[i].value == '^')
        {
            tokens[i-1].value = pow(tokens[i-1].value,tokens[i+1].value); //calculate the power, store it in the left operand
            for (j=i;j<numTokens-2;j++) //shift the array to the left by 2, to remove the operator and the right operand
            {
                tokens[j].value = tokens[j+2].value; 
                tokens[j].type = tokens[j+2].type; 
            }
            numTokens = numTokens - 2;
            i--; //decrement the index, to check the same index again, because the array is shifted to the left by 2
        }
        else if (tokens[i].value == '!')
        {
            tokens[i-1].value = factorial(tokens[i-1].value);
            for (j=i;j<numTokens-1;j++) // shift the array to the left by 1, to remove the `!` op
            {
                tokens[j].value = tokens[j+1].value;
                tokens[j].type = tokens[j+1].type;
            }
            numTokens = numTokens - 1;
            i--;
        }
    }

    //print the tokens
    for (i=0;i<numTokens;i++)
    {
        if (tokens[i].type == 'n')
            printf("%d ",tokens[i].value);
        else
            printf("%c ",tokens[i].value);
    }
    
    return numTokens;
}

int eval2(int numTokens)
{
    //evaluate the '*' and '/' and '%' operators
    int i,j;

    for (i=0;i<numTokens;i++)
    {
        if (tokens[i].value == '*')
        {
            tokens[i-1].value = tokens[i-1].value * tokens[i+1].value;
            for (j=i;j<numTokens-2;j++)
            {
                tokens[j].value = tokens[j+2].value;
                tokens[j].type = tokens[j+2].type;
            }
            numTokens = numTokens - 2;
            i--;
        }
        else if (tokens[i].value == '/')
        {
            tokens[i-1].value = tokens[i-1].value / tokens[i+1].value;
            for (j=i;j<numTokens-2;j++)
            {
                tokens[j].value = tokens[j+2].value;
                tokens[j].type = tokens[j+2].type;
            }
            numTokens = numTokens - 2;
            i--;
        }
        else if (tokens[i].value == '%')
        {
            tokens[i-1].value = tokens[i-1].value % tokens[i+1].value;
            for (j=i;j<numTokens-2;j++)
            {
                tokens[j].value = tokens[j+2].value;
                tokens[j].type = tokens[j+2].type;
            }
            numTokens = numTokens - 2;
            i--;
        }
    }
    //print the array
    for (i=0;i<numTokens;i++)
    {
        if (tokens[i].type == 'n')
            printf("%d ",tokens[i].value);
        else
            printf("%c ",tokens[i].value);
    }

    return numTokens;
}

int eval3(int numTokens)
{
    //evaluate the '+' and '-' operators
    int i,j;

    for (i=0;i<numTokens;i++)
    {
        if (tokens[i].value == '+')
        {
            tokens[i-1].value = tokens[i-1].value + tokens[i+1].value;
            for (j=i;j<numTokens-2;j++)
            {
                tokens[j].value = tokens[j+2].value;
                tokens[j].type = tokens[j+2].type;
            }
            numTokens = numTokens - 2;
            i--;
        }
        else if (tokens[i].value == '-')
        {
            tokens[i-1].value = tokens[i-1].value - tokens[i+1].value;
            for (j=i;j<numTokens-2;j++)
            {
                tokens[j].value = tokens[j+2].value;
                tokens[j].type = tokens[j+2].type;
            }
            numTokens = numTokens - 2;
            i--;
        }
    }
    //print the array
    for (i=0;i<numTokens;i++)
    {
        if (tokens[i].type == 'n')
            printf("%d ",tokens[i].value);
        else
            printf("%c ",tokens[i].value);
    }

    return numTokens;
}

int factorial(int n)
{
    int i,fact=1;
    for (i=1;i<=n;i++)
        fact = fact * i;
    return fact;
}
