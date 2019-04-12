//>>>---------> >>>---------> Libraries

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//>>>---------> >>>---------> Functions' prototypes

int length(char *x); 
    //returns the length of string 'x'
int upperCase(char *x, int n); 
    //modifies the lower case char. of string 'x' to upper case and requires length 'n'
    //returns 1, if any modification occured at all; returns 0 otherwise
int rotation(char *x, int r, int n); 
    //rotates each alphabetical char. of string 'x' by 'r' and requires length 'n'
    //returns 1, if any rotation occured at all; returns 0 otherwise
int substitution(char *x, char *y, int n); 
    //substitutes an element of string 'x' with the corresponding element of string 'y' and requires length 'n'
    //returns 1, if substitution occured at all; returns 0 otherwise
int decryptingAB(char *x, char *y); 
    //makes an alphabet 'y', for decrypting from the encrypting alphabet 'x' and requires length 'n'
    //returns 1, if any conversion occured at all; returns 0 otherwise
char mostCommon(char *x, int n); 
    //returns the most common upper-case Latin character
int omission(char *x, int n); 
    //omits any punctuation or non-Latin (nor upper-case) character at the end of a string 'x'
    //returns 1, if there was a non-Latin (nor upper-case) character at the end; returns 0 otherwise
int trial(char *x, int n); 
    //returns 1, if the string 'x' is contain in the list of common English words; 
    //returns 0 otherwise or if the file list.txt is empty; requries length 'n'

//>>>---------> >>>---------> Main

int main()
{
    //Declaration of variables
    char setting[1]; //the character defining the setting as a header 
    char word[1000]; //a word from the text
    char text[10000] = ""; //the text
    char rKey[2]; //the key for rotation; N.B. it must have two digits in the header, e.g. 3 = 03
    char sKey[26] = "QAZXSWEDCVFRTGBNHYUJMKIOLP"; //the key for substitution
    char AB[26]; //the encrytping alphabet
    char dAB[26]; //the decrypting alphabet
    char mC[6] = "ZETAOI"; //the first five most common letters in the Modern English language from http://letterfrequency.org/
    int r; //'r' for rotator, i.e. the integer of the rKey
    int n; //length
    int S; //the setting of the action
    char M; //the most common letter
    char B = ' '; //the best letter
    
    /* >>>--------->
      S: Action:
      0  rotational encryption
      1  rotational decryption with key 
      2  rotational decryption without key by frequency
      3  substitutional encryption with key
      4  substitutional decryption with key
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
    
    //Action i.e. the principal part of the code
    switch(S) {
        //Rotational encryption
        case 0:
            fscanf(input, "%2s", rKey); //getting the key
            r = atoi(rKey); //casting the key to an integer value
            printf("%d\n", r); //printing the key
            while (!feof(input)) {
                fscanf(input, "%s", word); //getting the next word i.e. string until space
                n = length(word);
                upperCase(word, n);
                rotation(word, r, n);
                printf("%s ", word); //printing the word followed by a space
            }
            break;
        //Rotational decryption with key
        case 1:
            fscanf(input, "%2s", rKey);
            r = atoi(rKey);
            printf("%d\n", r);
            iDoNotCareWhatTheySayAboutGOTO: //If thou dost not like GOTO, then avaunt thou!
            while (!feof(input)) {
                fscanf(input, "%s", word);
                n = length(word);
                upperCase(word, n);
                rotation(word, 26 - r, n); //rotating like case 0, but the rotator is the 26-r
                printf("%s ", word);   
            }
            break;
        //Rotational decryption without key by frequency
        case 2:
            //Flattening the text into one string
            while (!feof(input)) {
                fscanf(input, "%s", word);
                n = length(word);
                upperCase(word, n);
                strcat(text, word);
            }
            
            //Getting the most common letter from which
            n = length(text);
            M = mostCommon(text, n);
            printf("%c\n", M);
            
            //Trial for each common letter
            for (int i = 1; i < 6; i++) {
                fseek(input, 1, SEEK_SET); //beginning the cursor
                r = (int)(M - mC[i]); //the new rotator
                int w = 0; //'w' for the number of words
                int englishWords = 0; //the number of English words
                float englishness; //the percentage of English words in the text
                float highest; //the highest percentage yet
                while (!feof(input)) {
                    w++;
                    //Decryption by r
                    fscanf(input, "%s", word);
                    n = length(word);
                    upperCase(word, n);
                    rotation(word, 26 - r, n);  
                    //Omission of punctuation at the end
                    omission(word, n);
                    //Trial by spelling
                    englishWords += trial(word, n);
                }
                englishness = (float)englishWords / (float)w;
                if (englishness > highest) {
                    B = mC[i];
                    highest = englishness;
                }
                printf("%c %d %d %f %f %c\n", mC[i], w, englishWords, englishness, highest, B); //printing some statistics
                r = (int)(M - B);
            }
            fseek(input, 1, SEEK_SET); //beginning the cursor
            goto iDoNotCareWhatTheySayAboutGOTO; //All work and no spagetti code makes Jack a dull boy.
            break;
        //Substitutional encryption
        case 3: 
            fscanf(input, "%26s", sKey);
            printf("%s\n", sKey);
            strcpy(AB, sKey);
            while (!feof(input)) {
                fscanf(input, "%s", word);
                strcpy(text, word);
                n = length(text);
                upperCase(text, n);
                substitution(text, AB, n);    
                printf("%s ", text);  
            }
            break;
        //Substitutional decryption with key
        case 4:
            fscanf(input, "%26s", sKey);
            printf("%s\n", sKey);
            strcpy(AB, sKey);
            while (!feof(input)) {
                fscanf(input, "%s", word);
                strcpy(text, word);
                n = length(text);
                upperCase(text, n);
                decryptingAB(AB, dAB);
                substitution(text, dAB, n);    
                printf("%s ", text);  
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
    return f; 
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
    return f; 
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
    return f; 
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
    return f; 
}

char mostCommon(char *x, int n) {
    char l; //'l' for letter to be tested
    int f; //'f' for frequency of the letter
    int m = 0; //'m' for maximum frequency of a letter
    char M = 'A'; //letter, that has the maxmimum frequency 
    for (l = 'A'; l <= 'Z'; l++) {
        f = 0;
        for (int i = 0; i < n; i++) {
            if (x[i] == l) {
                f++;
            }        
        }
        if (f >= m) {
            m = f;
            M = l;
        }
    }
    return M;
}

int omission(char *x, int n) {
    char y[1000] = ""; //temporary string
    int f = 0; //'f' for flag
    if ((x[n-1] < 'A') || (x[n-1] > 'Z')) {
        strxfrm(y, x, n-1);
        strcpy(x, y);
        f = 1;
    }
    return f; 
}

int trial(char *x, int n) {
    FILE *list;
    list = fopen("list.txt", "r");
    if (list == NULL) { //this ends the program, if there is nothing in the file
        perror("fopen()");
        return 0;
    }
    
    fseek(list, 0, SEEK_SET);
    char entry[1000]; //an entry from the list
    while (!feof(list)) {
        fscanf(list, "%s", entry);
        upperCase(entry, length(entry));
        if (!strcmp(x, entry)) {
            int errors = 0; //the number of incorrect characters
            for (int i = 0; i < n; i++) {
                if (x[i] != entry[i])
                    errors++;
            }
            if (errors == 0) {
                return 1;
            }
        }
    }
    return 0;
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
