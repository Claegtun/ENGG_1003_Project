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
int substitution(char *x, char *y, int n); //substitutes an element of string 'x' with the corresponding element of string 'y'

//>>>---------> Main
int main()
{
    const char text0[200] = "SUBMARINES TO DOCK AT ANTWERP AT TWENTY HUNDRED HOURS OVER";//"SUBMARINES TO DOCK AT ANTWERP AT TWENTY HUNDRED HOURS OVER";
    char text1[200];//the modifying string for the text
    const char key[26] = "QAZXSWEDCVFRTGBNHYUJMKIOLP";
    char AB[26]; //the modifying string for the key
    int r = 3; //'r' for rotater; N.B. it is overwritten, when S=2
    int n; //length
    int S = 3; 
    /*S: Action:
      0  rotational encryption
      1  rotational decryption with key 
      2  rotational decryption without key by frequency of 'T'
      3  substitutional encryption with known key
      4  substitutional decryption with known key*/
    
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
            rotation(text1, 26 - r, n); //the rotater is the key subtracted from 26
            printf("%s", text1);
            break;
        case 2:
            printf("%s\n", text0);
            strcpy(text1, text0);
            n = length(text1);
            upperCase(text1, n);
            printf("%s\n", text1);
            
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
            
            r = M - 'T';
            rotation(text1, 26 - r, n); //the rotater is the key subtracted from 26
            printf("%s", text1);
            break;
        case 3: 
            strcpy(AB, key);
            printf("%s\n", text0);
            strcpy(text1, text0);
            n = length(text1);
            upperCase(text1, n);
            printf("%s\n", text1);
            substitution(text1, AB, n);    
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
    return f; //returns 1, if modification occured at all; returns 0 otherwise
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
