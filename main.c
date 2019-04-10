//>>>---------> >>>---------> Libraries

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//>>>---------> >>>---------> Functions' prototypes

//One should see definitions for returning flags
int length(char *x); //returns the length of string 'x'
int upperCase(char *x, int n); //modifies the lower case char. of string 'x' to upper case and requires length 'n'
int rotation(char *x, int r, int n); //rotates each alphabetical char. of string 'x' by 'r' and requires length 'n'
int substitution(char *x, char *y, int n); //substitutes an element of string 'x' with the corresponding element of string 'y' and requires length 'n'
int decryptingAB(char *x, char *y); //makes an alphabet, i.e. 'y', for decrypting from the encrypting alphabet, i.e. 'x' and requires length 'n'


//>>>---------> >>>---------> Main

int main()
{
    //Declaration of variables
    char setting[1]; //the character defining the setting as a header 
    char text0[1000]; //"SUBMARINES TO DOCK AT ANTWERP AT TWENTY HUNDRED HOURS OVER";
    char text1[1000] = ""; //the modifying string for the text
    char rKey[2]; //the key for rotation; N.B. it must have two digits in the header, e.g. 3 = 03
    char sKey[26] = "QAZXSWEDCVFRTGBNHYUJMKIOLP"; //the key for substitution
    char AB[26]; //the encrytping alphabet
    char dAB[26]; //the decrypting alphabet
    int r; //'r' for rotator, i.e. the integer of the rKey
    int n; //length
    int S; //the setting of the action
    /*S: Action:
      0  rotational encryption
      1  rotational decryption with key 
      2  rotational decryption without key by frequency of 'T'
      3  substitutional encryption with known key
      4  substitutional decryption with known key
    */
    
    //Beginning of files
    FILE *input;
    input = fopen("input.txt", "r");
    if (input == NULL) { //this ends the program, if there is nothing in the file
        perror("fopen()");
        return 0;
    }
    
    //Finding the setting
    fscanf(input, "%1s", setting);
    S = atoi(setting);
    printf("%d\n", S);
    
    //Encrpytion
    switch(S) {
        case 0:
            fscanf(input, "%2s", rKey);
            r = atoi(rKey);
            printf("%d\n", r);
            while (!feof(input)) {
                fscanf(input, "%s", text0);
                strcpy(text1, text0);
                n = length(text1);
                upperCase(text1, n);
                rotation(text1, r, n);
                printf("%s ", text1);   
            }
            break;
        case 1:
            fscanf(input, "%2s", rKey);
            r = atoi(rKey);
            printf("%d\n", r);
            while (!feof(input)) {
                fscanf(input, "%s", text0);
                strcpy(text1, text0);
                n = length(text1);
                upperCase(text1, n);
                rotation(text1, 26 - r, n);
                printf("%s ", text1);   
            }
            break;
        case 2:
            fscanf(input, "%2s", rKey);
            r = atoi(rKey);
            printf("%d\n", r);
            while (!feof(input)) {
                fscanf(input, "%s", text0);
                n = length(text0);
                upperCase(text0, n);
                strcat(text1, text0);
            }
            printf("%s\n", text1);
            
            n = length(text1);
            char l; //'l' for letter to be tested
            int f; //'f' for frequency of the letter
            int m = 0; //'m' for maximum frequency of a letter
            char M = 'A'; //letter, that has the maxmimum frequency 
            for (l = 'A'; l <= 'Z'; l++) {
                f = 0;
                for (int i = 0; i < n; i++) {
                    if (text1[i] == l) {
                        f++;
                    }        
                }
                if (f >= m) {
                    m = f;
                    M = l;
                }
            }
            printf("%c\n", M);
            break;
        case 3: 
            fscanf(input, "%26s", sKey);
            printf("%s\n", sKey);
            strcpy(AB, sKey);
            while (!feof(input)) {
                fscanf(input, "%s", text0);
                strcpy(text1, text0);
                n = length(text1);
                upperCase(text1, n);
                substitution(text1, AB, n);    
                printf("%s ", text1);  
            }
            break;
        case 4:
            fscanf(input, "%26s", sKey);
            printf("%s\n", sKey);
            strcpy(AB, sKey);
            while (!feof(input)) {
                fscanf(input, "%s", text0);
                strcpy(text1, text0);
                n = length(text1);
                upperCase(text1, n);
                decryptingAB(AB, dAB);
                substitution(text1, dAB, n);    
                printf("%s ", text1);  
            }
            break;
        default:
            printf("Invalid S");
    }   
}


//>>>---------> >>>---------> Functions' denfinitions

int length(char *x) {
    int n = 0; //length
    while (x[n] != 0) {
        n++;
    }
    return n; //returns the number of char.
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
    return f; //returns 1, if any modification occured at all; returns 0 otherwise
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
    return f; //returns 1, if any rotation occured at all; returns 0 otherwise
}

int substitution(char *x, char *y, int n) {
    char l; //'l' for letter
    int il; //integer of 'l'
    int f = 0; //'f' for flag
    for (int i = 0; i < n; i++) {
        l = x[i];
        if ((l >= 'A') && (l <= 'Z')) {
            il = (int)l - 65;
            l = y[il];
            f = 1;
        }  
        x[i] = l;
    } 
    return f; //returns 1, if substitution occured at all; returns 0 otherwise
}

int decryptingAB(char *x, char *y) {
    char l; //'l' for letter
    int il; //integer of 'l'
    int f = 0; //'f' for flag
    for (int i = 0; i < 26; i++) {
        l = x[i];
        if ((l >= 'A') && (l <= 'Z')) {
            il = (int)l - 65;
            y[il] = (char)(i + 65);
            f = 1;
        }
    }
    return f; //returns 1, if any conversion occured at all; returns 0 otherwise
}
















/*
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * Verification of uniqueness
 *      ________
 *     /  ____  \
 *    / /      \ \                         =========
 *   | |        | |=======================|  _   _  |}
 *   | |        | |=======================| |_| |_| |}
 *    \ \ ____ / /                        |+ _ + _ +|
 *     \________/                         | | | | | |
 *                                        |_| |_| |_| 
 * 
 * - Clayton John Carlon 2019
 * 
 *  
 */
