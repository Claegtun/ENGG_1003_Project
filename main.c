//>>>---------> Libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//>>>---------> Functions' prototypes
int length(char *x);


//>>>---------> Main
int main()
{
    
    const char trueText[200] = "HELLO, WORLD!";
    char hiddenText[200];
    char r = 3; //'r' for rotation
    char l; //'l' for letter
    int il; //integer of 'l'
    int n;
    
    printf("%s\n", trueText);
    
    strcpy(hiddenText, trueText);
    n = length(hiddenText);
    
    for (int i = 0; i < n; i++) {
        l = hiddenText[i];
        if ((l >= 'A') && (l <= 'Z')) {
            il = (int)l - 65;
            il = (il + 3) % 26;
            l = (char)(il + 65);
        }  
        hiddenText[i] = l;
    }
    
    printf("%s", hiddenText);
}

//>>>---------> Functions' denfinitions
int length(char *x) {
    int n = 0;
    while (x[n] != 0) {
        n++;
    }
    return n; //It returns the number of chars including the \0
}
