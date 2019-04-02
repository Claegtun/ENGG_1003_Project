#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int count(char *x);

int main()
{
    
    const char trueText[200] = "HELLO, WORLD!";
    char hiddenText[200];
    char r; //'r' for rotation
    char l; //'l' for letter
    
    printf("%s\n", trueText);
    
    for (int i = 0; i < 200; i++) {
        hiddenText[i] = trueText[i];   
    }
    printf("%d", count(hiddenText));
}

int count(char *x) {
    int n = 0;
    while (x[n] != 0) {
        n++;
    }
    return n - 1;
}

