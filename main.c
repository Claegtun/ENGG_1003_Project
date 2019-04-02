//>>>---------> Libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//>>>---------> Functions' prototypes
//One should see definitions for returning flags
int length(char *x); //returns the length of string 'x'
int upperCase(char *x, int n); //modifies the lower case char. of string 'x' to upper case and requires length 'n'
int rotation(char *x, int r, int n); //rotates each alphabetical char. of string 'x' by 'r' and requires length 'n'

//>>>---------> Main o-{=========- (sword)
int main()
{
    char text0[200] = "KHOOR, ZRUOG!";
    char text1[200];
    int r = 3; //'r' for rotation
    int n; //length
    int S = 1; 
    /*S: Action:
      0  rotational encryption
      1  rotational decryption */
    
    //Encrpytion
    switch(S) {
        case 0:
            printf("%s\n", text0);
            strcpy(text1, text0);
            n = length(text1);
            upperCase(text1, n);
            printf("%s\n", text1);
            rotation(text1, r, n);
            printf("%s", text1);   
            break;
        case 1:
            printf("%s\n", text0);
            strcpy(text1, text0);
            n = length(text1);
            upperCase(text1, n);
            printf("%s\n", text1);
            rotation(text1, 26 - r, n);
            printf("%s", text1);
            break;
        default:
            printf("Invalid S");
    }
    
    
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
