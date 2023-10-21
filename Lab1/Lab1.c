#include <stdio.h>          // Get 100 scores in all open cases and hidden cases with 6 and 4 scores per case respectively.
#include <string.h>
#include <stdbool.h>

bool notzero(int number[], int length);
int findnewlength(int number[]);
int whichbigger(int number1[], int number2[], int length1, int length2);  // 1 = number1 is bigger than or equal to number2.
                                                                          // 2 = number2 is bigger than number1.
void findgcd(int number1[], int number2[], int length1, int length2);

int main()
{
    int i, j;
    int length1, length2;
    char string1[256], string2[256];
    scanf("%s %s", string1, string2);
    if (strcmp(string1, string2)==0) {  // If a = b, printf a and return 0.
        printf("%s\n", string1);
        return 0;
    }
    length1 = strlen(string1);
    length2 = strlen(string2);
    int number1[256] = {0}, number2[256] = {0};
    for (i=length1-1 ; i>=0 ; i--)  
        for (j=0 ; j<10 ; j++)
            if (string1[i]==48+j)
                number1[length1-i-1] = j;
    for (i=length2-1 ; i>=0 ; i--)
        for (j=0 ; j<10 ; j++)
            if (string2[i]==48+j)
                number2[length2-i-1] = j;
    findgcd (number1, number2, length1, length2);
    return 0;
}

bool notzero(int number[], int length)
{
    int i;
    for (i=0 ; i<length ; i++)
        if (number[i]!=0)  // If there is a digit is not zero, which represent that the number is not zero, thus return true (the number is not zero).
            return true;
    return false;
}

int findnewlength(int number[])
{
    int i;
    for (i=255 ; i>=0 ; i--)
        if (number[i]!=0)
            return i + 1;
}

int whichbigger(int number1[], int number2[], int length1, int length2)
{
    int i;
    if (length1>length2)
        return 1;
    else if (length2>length1)
        return 2;
    else
        for (i=length1-1 ; i>=0 ; i--) {  // The length1 and length2 are equal, thus there is no difference using i = length1-1 or length2-1.
            if (number1[i]>number2[i])
                return 1;
            else if (number2[i]>number1[i])
                return 2;
        }
    return 1; // number1 and number2 are equal, thus there is no difference returning 1 or 2
              // because number1 - number2 or number2 - number1 = 0.
}

void findgcd(int number1[], int number2[], int length1, int length2)
{
    int i, j;
    int answer[256] = {0}, binary[256] = {0};  // Use binary[256] instead of unsigned long long binary to avoid if a = 2^100 and b = 2^101
                                               // and gcd = 2^100.
    binary[0] = 1;
    while (notzero(number1, length1) && notzero(number2, length2)) {  // Find the final answer using the algorithm on lab1's PDF.
        if (number1[0]%2==0 && number2[0]%2==0) {
            for (i=length1-1 ; i>=0 ; i--) {
                if (number1[i]%2==1)
                    number1[i-1] += 10;
                number1[i] /= 2;
            }
            for (i=length2-1 ; i>=0 ; i--) {
                if (number2[i]%2==1)
                    number2[i-1] += 10;
                number2[i] /= 2;
            }
            for (i=0 ; i<256 ; i++)
                binary[i] *= 2;
            for (i=0 ; i<256 ; i++)
                if (binary[i]>=10) {
                    binary[i+1] += binary[i] / 10;
                    binary[i] %=10 ;
                }  
        }
        else if (number1[0]%2==0) {
            for (i=length1-1 ; i>=0 ; i--) {
                if (number1[i]%2==1)
                    number1[i-1] += 10;
                number1[i] /= 2;
            }
        }
        else if (number2[0]%2==0) {
            for (i=length2-1 ; i>=0 ; i--) {
                if (number2[i]%2==1)
                    number2[i-1] += 10;
                number2[i] /= 2;
            }
        }
        length1 = findnewlength(number1);
        length2 = findnewlength(number2);
        if (whichbigger(number1, number2, length1, length2)==1) {
            for (i=0 ; i<length1 ; i++) {
                    if (number1[i]>=number2[i])
                        number1[i] -= number2[i];
                    else if (number1[i]<number2[i]) {
                        number1[i] = 10 - number2[i] + number1[i];
                        number1[i+1] --;
                    }
            }
        }
        else if (whichbigger(number1, number2, length1, length2)==2) {
            for (i=0 ; i<length2 ; i++) {
                    if (number2[i]>=number1[i])
                        number2[i] -= number1[i];
                    else if (number2[i]<number1[i]) {
                        number2[i] = 10 - number1[i] + number2[i];
                        number2[i+1] --;
                    }
            }
        }
    } 
    if (whichbigger(number1, number2, length1, length2)==1) {  // Calculate the final answer using the algorithm on lab1's PDF.
        for (i=0 ; i<length1 ; i++)
            for (j=0 ; j<256 ; j++)
                answer[i+j] += number1[i] * binary[j];
        for (i=0 ; i<256 ; i++)
            if (answer[i]>=10) {
                answer[i+1] += answer[i] / 10;
                answer[i] %= 10;
            }
    }
    else if (whichbigger(number1, number2, length1, length2)==2) {
        for (i=0 ; i<length2 ; i++)
            for (j=0 ; j<256 ; j++)
                answer[i+j] += number2[i] * binary[j];
        for (i=0 ; i<256 ; i++)
            if (answer[i]>=10) {
                answer[i+1] += answer[i] / 10;
                answer[i] %= 10;
            }
    }
    length1 = findnewlength(answer);
    for (i=length1-1 ; i>=0 ; i--)
            printf("%d", answer[i]);
    printf("\n");
}
