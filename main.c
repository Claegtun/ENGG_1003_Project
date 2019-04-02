#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int count(char *x);

int main()
{
    
    const char trueText[200] = "HELLO, WORLD!";
    char hiddenText[200];
    char r; //'r' for rotation
    char l; //'l' for letter
    int n;
    
    printf("%s\n", trueText);
    
    strcpy(hiddenText, trueText);
    n = count(hiddenText);
}

int count(char *x) {
    int n = 0;
    while (x[n] != 0) {
        n++;
    }
    return n - 1;
}
