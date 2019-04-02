//>>>---------> Libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//>>>---------> Functions' prototypes
int length(char *x);
int upperCase(char *x, int n);
int rotation(char *x, int r, int n);

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
    return n; //This returns the number of chars including the \0
}

int upperCase(char *x, int n) {
    char l; //'l' for letter
    for (int i = 0; i < n; i++) {
        l = x[i];
        if ((l >= 'a') && (l <= 'z')) {
            l -= 32;   
        }  
        x[i] = l;
    }  
    return 1;
}

int rotation(char *x, int r, int n) {
    char l; //'l' for letter
    int il; //integer of 'l'
    for (int i = 0; i < n; i++) {
        l = x[i];
        if ((l >= 'A') && (l <= 'Z')) {
            il = (int)l - 65;
            il = (il + r) % 26;
            l = (char)(il + 65);
        }  
        x[i] = l;
    }    
    return 1; //This modfies the string by rotation and returns 1 as a flag
}
