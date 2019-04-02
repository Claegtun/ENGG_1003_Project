//>>>---------> Libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//>>>---------> Functions' prototypes
int length(char *x); //returns the length of string 'x'
int upperCase(char *x, int n); //modifies the lower case char. of string 'x' to upper case and requires length 'n'
int rotation(char *x, int r, int n); //rotates each alphabetical char. of string 'x' by 'r' and requires length 'n'

//>>>---------> Main
int main()
{
    const char trueText[200] = "hELLo, wOrlD!";
    char hiddenText[200];
    int r = 3; //'r' for rotation
    int n; //length
    
    printf("%s\n", trueText);
    
    strcpy(hiddenText, trueText);
    
    n = length(hiddenText);
    
    upperCase(hiddenText, n);
    
    printf("%s\n", hiddenText);
    
    rotation(hiddenText, r, n);
    
    printf("%s", hiddenText);
}

//>>>---------> Functions' denfinitions
int length(char *x) {
    int n = 0; //length
    while (x[n] != 0) {
        n++;
    }
    return n; //returns the number of chars including the \0
}

int upperCase(char *x, int n) {
    char l; //'l' for letter
    int f = 0; //'f' for flag
    for (int i = 0; i < n; i++) {
        l = x[i];
        if ((l >= 'a') && (l <= 'z')) {
            l -= 32;   
        }  
        x[i] = l;
    }  
    return f; //returns 1, if rotation occured at all; returns 0 otherwise
}

int rotation(char *x, int r, int n) {
    char l; //'l' for letter
    int il; //integer of 'l'
    int f = 0; //'f' for flag
    for (int i = 0; i < n; i++) {
        l = x[i];
        if ((l >= 'A') && (l <= 'Z')) {
            il = (int)l - 65;
            il = (il + r) % 26;
            l = (char)(il + 65);
            f = 1;
        }  
        x[i] = l;
    }    
    return f; //returns 1, if modification occured at all; returns 0 otherwise
}
