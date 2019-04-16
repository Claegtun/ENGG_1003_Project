//>>>---------> >>>---------> Libraries <---------<<< <---------<<<

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//>>>---------> >>>---------> Functions' prototypes <---------<<< <---------<<<

int length(char *x); 
    //returns the length of string 'x'
int upperCase(char *x); 
    //modifies the lower case char. of string 'x' to upper case
    //returns 1, if any modification occured at all; returns 0 otherwise
int rotation(char *x, int r); 
    //rotates each alphabetical char. of string 'x' by 'r'
    //returns 1, if any rotation occured at all; returns 0 otherwise
int substitution(char *x, char *y); 
    //substitutes an element of string 'x' with the corresponding element of string 'y'
    //returns 1, if substitution occured at all; returns 0 otherwise
int decryptingAB(char *x, char *y); 
    //makes an alphabet 'y', for decrypting from the encrypting alphabet 'x'
    //returns 1, if any conversion occured at all; returns 0 otherwise
char letter(char *x); 
    //returns the most common upper-case Latin character
int omission(char *x); 
    //omits any punctuation (except '_') or non-Latin (nor upper-case) character at the end of a string 'x'
    //returns 1, if there was a non-Latin (nor upper-case) character at the end; returns 0 otherwise
int trial(char *x, FILE *f); 
    //returns 1, if the string 'x' is contain in the list of common English words; 
    //returns 0 otherwise or if the file list.txt is empty
int bigram(char *x, char *y);
    //modifies the 'y' string to contain the most common bigram (i.e. pair of letters) from the 'x'
    //returns the number of bigrams, that were considered
int trigram(char *x, char *y);
    //modifies the 'y' string to contain the most common trigram (i.e. pair of letters) from the 'x'
    //returns the number of trigrams, that were considered
int frequency(char *x, char y);
    //returns the frequency of the character 'y' in the string 'x'

//>>>---------> >>>---------> Main <---------<<< <---------<<<

int main()
{
    //Declaration of variables
    char setting[1]; //the character defining the setting as a header 
    char word[1000]; //a word from the text
    char text[10000] = ""; //the text
    char rKey[2]; //the key for rotation; N.B. it must have two digits in the header, e.g. 3 = 03
    char sKey[26] = "QAZXSWEDCVFRTGBNHYUJMKIOLP"; //the key for substitution
    char AB[26] = "__________________________"; //the encrytping alphabet
    char dAB[26]; //the decrypting alphabet
    char mC[6] = " ETAOI"; //the first five most common letters in the Modern English language from http://letterfrequency.org/
    char mB[9] = " THERON"; //the first four most common bigrams in the Modern English language from https://en.wikipedia.org/wiki/Frequency_analysis
    char mR[5] = " SETF"; //the first four most common repeated letters in the Modern English language from https://en.wikipedia.org/wiki/Frequency_analysis
    int r; //'r' for rotator, i.e. the integer of the rKey
    int n; //length
    int S; //the setting of the action
    char cL; //the most common letter
    char B = ' '; //the best letter
    int line; //the number of characters in a line
    char cBg[2]; //the most common bigram
    char cTg[3]; //the most common trigram
    
    /* >>>--------->
      S: Action:
      0  rotational encryption
      1  rotational decryption with key 
      2  rotational decryption without key
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
    FILE *output;
    output = fopen("output.txt", "w");
    
    FILE *list;
    list = fopen("list.txt", "r");
    if (list == NULL) { //this ends the program, if there is nothing in the file
        perror("fopen()");
        return 0;
    }
    
 
    FILE *buffer;
    buffer = fopen("buffer.txt", "w+");
    
    //Finding the setting
    fscanf(input, "%1s", setting);
    S = atoi(setting);
    printf("Setting: %d i.e. ", S); fprintf(output, "Setting: %d i.e. ", S);
    //Action i.e. the principal part of the code
    switch(S) {
        //Rotational encryption <---------<<< <---------<<<
        case 0:
            fscanf(input, "%2s", rKey); //getting the key
            r = atoi(rKey); //casting the key to an integer value
            //Printing relevant data
            printf("Rotational encrytion\n"); fprintf(output, "Rotational encrytion\n");
            printf("Key: %s\n", rKey); fprintf(output, "Key: %s\n", rKey);
            printf("Rotator: %d\n", r); fprintf(output, "Rotator: %d\n", r);
            printf("Encrypted text:\n"); fprintf(output, "Encrypted text:\n");
            iDoNotCareWhatTheySayAboutGOTO: //If thou dost not like GOTO, then avaunt thou!
            line = 0;
            while (!feof(input)) {
                fscanf(input, "%s", word); //getting the next word i.e. string until space
                if (feof(input))
                    break; //This condition break was added, for that the last word kept being repeated; this be a temporary solution
                n = length(word);
                upperCase(word);
                rotation(word, r);
                printf("%s ", word); fprintf(output, "%s ", word); //printing the word followed by a space
                //Ending the line by at most 100 characters
                line += n;
                if (line >= 100) {
                    printf("\n"); fprintf(output, "\n");
                    line = 0;
                }
            }
            break;
        //Rotational decryption with key <---------<<< <---------<<<
        case 1:
            fscanf(input, "%2s", rKey);
            r = 26 - atoi(rKey);
            //Printing relevant data
            printf("Rotational decrytion with key\n"); fprintf(output, "Rotational decrytion with key\n");
            printf("Key: %s\n", rKey); fprintf(output, "Key: %s\n", rKey);
            printf("Rotator: %d\n", r); fprintf(output, "Rotator: %d\n", r);
            printf("Decrypted text:\n"); fprintf(output, "Decrypted text:\n");
            goto iDoNotCareWhatTheySayAboutGOTO; //All work and no spagetti code makes Jack a dull boy.
            break;
        //Rotational decryption without key by frequency <---------<<< <---------<<<
        case 2:
            //Flattening the text into one string
            while (!feof(input)) {
                fscanf(input, "%s", word);
                n = length(word);
                upperCase(word);
                strcat(text, word);
            }
            //Getting the most common letter from which
            n = length(text);
            cL = letter(text);
            //Printing relevant data
            printf("Rotational decrytion without key\n"); fprintf(output, "Rotational decrytion without key\n");
            printf("Most common letter found: %c\n", cL); fprintf(output, "Most common letter found: %c\n", cL);
            printf("Character tested:   Words:  English* words:  Englishness:\n"); fprintf(output, "Character tested:   Words:  English* words:  Englishness:\n");
            //Trial for each common letter
            for (int i = 1; i < 6; i++) {
                fseek(input, 1, SEEK_SET); //beginning the cursor
                r = (int)(cL - mC[i]); //the new rotator
                int w = 0; //'w' for the number of words
                int englishWords = 0; //the number of English words
                float englishness; //the percentage of English words in the text
                float highest; //the highest percentage yet
                while (!feof(input)) {
                    w++;
                    //Decryption by r
                    fscanf(input, "%s", word); //getting the next word
                    n = length(word);
                    upperCase(word);
                    rotation(word, 26 - r);  
                    //Omission of punctuation at the end
                    omission(word);
                    //Trial by spelling
                    englishWords += trial(word, list);
                }
                englishness = (float)englishWords / (float)w;
                if (englishness > highest) {
                    B = mC[i];
                    highest = englishness;
                }
                printf("%c\t\t    %d\t    %d\t\t     %f\n", mC[i], w, englishWords, englishness); 
                fprintf(output, "%c\t\t\t\t    %d\t    %d\t\t\t     %f\n", mC[i], w, englishWords, englishness); //printing some statistics
            }
            fseek(input, 1, SEEK_SET); //beginning the cursor
            r = 26 - (int)(cL - B);
            printf("*detected by list.txt\n"); fprintf(output, "*detected by list.txt\n");
            printf("Chosen letter and rotator by freuqency: %c %d\n", B, r); fprintf(output, "Chosen letter and rotator by freuqency: %c %d\n", B, r);
            printf("Decrypted text:\n"); fprintf(output, "Decrypted text:\n");
            goto iDoNotCareWhatTheySayAboutGOTO; //I still do not care
            break;
        //Substitutional encryption <---------<<< <---------<<<
        case 3: 
            fscanf(input, "%26s", sKey);
            strcpy(AB, sKey);
            //Printing relevant data
            printf("Substitutional encrytion\n"); fprintf(output, "Substitutional encrytion\n");
            printf("Key: %s\n", sKey); fprintf(output, "Key: %s\n", sKey);
            printf("Encrypted text:\n"); fprintf(output, "Encrypted text:\n");
            while (!feof(input)) {
                fscanf(input, "%s", word);
                n = length(word);
                upperCase(word);
                substitution(word, AB);    
                printf("%s ", word); fprintf(output, "%s ", word);
                //Ending the line by at most 100 characters
                line += n;
                if (line >= 100) {
                    printf("\n"); fprintf(output, "\n");
                    line = 0;
                }
            }
            break;
        //Substitutional decryption with key <---------<<< <---------<<<
        case 4:
            fscanf(input, "%26s", sKey);
            strcpy(AB, sKey);
            //Printing relevant data
            printf("Substitutional decrytion with key\n"); fprintf(output, "Substitutional decrytion with key\n");
            printf("Key: %s\n", sKey); fprintf(output, "Key: %s\n", sKey);
            printf("Decrypted text:\n"); fprintf(output, "Decrypted text:\n");
            while (!feof(input)) {
                fscanf(input, "%s", word);
                n = length(word);
                upperCase(word);
                decryptingAB(AB, dAB);
                substitution(word, dAB);    
                printf("%s ", word); fprintf(output, "%s ", word);
                //Ending the line by at most 100 characters
                line += n;
                if (line >= 100) {
                    printf("\n"); fprintf(output, "\n");
                    line = 0;
                }
            }
            break;
        case 5:
            //Printing relevant data
            printf("Substitutional decrytion without key\n");
            //Flattening the text into one string
            while (!feof(input)) {
                fscanf(input, "%s", word);
                n = length(word);
                upperCase(word);
                strcat(text, word);
            }
            //Getting the most common letter from which
            n = length(text);
            cL = letter(text);
            //Getting the most common bigram from which
            line = bigram(text, cBg);
            //Getting the most common trigram from which
            trigram(text, cTg);
            printf("%c %s %s\n", cL, cBg, cTg);
            //Making an alphabet
            if (!strncmp(cTg, cBg, 2)) {
                AB[(int)cTg[0]-65] = 'T';
                AB[(int)cTg[1]-65] = 'H';
                AB[(int)cTg[2]-65] = 'E';
            } 
            if (cBg[2] == cL) {
                AB[(int)cL-65] = 'E';    
            } 
            if (cBg[0] == cL) {
                AB[(int)cL-65] = 'T';    
            } 
            //Filling in the text
            fseek(input, 1, SEEK_SET);
            while (!feof(input)) {
                fscanf(input, "%s", word);
                n = length(word);
                upperCase(word);
                decryptingAB(AB, dAB);
                substitution(word, AB);   
                printf("%s ", word);
                //Ending the line by at most 100 characters
                line += n;
                if (line >= 100) {
                    printf("\n");
                    line = 0;
                }
                omission(word);
                fseek(list, 0, SEEK_SET);
                char entry[1000]; //an entry from the list
                while (!feof(list)) {
                    fscanf(list, "%s", entry);
                    upperCase(entry);
                    if (length(word) == length(entry)) {
                        if (frequency(word, '_') == 1) {
                            n = strcspn(word, "_");
                            for (char c = 'A'; c <= 'Z'; c++) {
                                word[n] = c;
                            }
                            printf("%s ", word);
                        }    
                    } 
                }
            }
            
            break;
        case 7:
            printf("EASTER EGG\n");
            int ploughman = 0;
            arrow:
            printf("All work and no spaghetti code makes Jack a dull boy\n"); //EASTER EGG
            ploughman++;
            if (ploughman != 9) 
                goto arrow; //who says, that one can not make a while loop using GOTO?
            printf("%d", frequency("ggafg''./gg2gaf2 5ga236ygyg", 'g')); //testing frequency()
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

int upperCase(char *x) {
    char l; //'l' for letter
    int f = 0; //'f' for flag
    int n = length(x);
    for (int i = 0; i < n; i++) {
        l = x[i];
        if ((l >= 'a') && (l <= 'z')) {
            l -= 32;   
        }  
        x[i] = l;
    }  
    return f; 
}

int rotation(char *x, int r) {
    char l; //'l' for letter
    int il; //integer of 'l'
    int f = 0; //'f' for flag
    int n = length(x);
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

int substitution(char *x, char *y) {
    char l; //'l' for letter
    int il; //integer of 'l'
    int f = 0; //'f' for flag
    int n = length(x);
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

char letter(char *x) {
    char l; //'l' for letter to be tested
    int f; //'f' for frequency of the letter
    int m = 0; //'m' for maximum frequency of a letter
    char cL = 'A'; //the letter, that has the maxmimum frequency 
    int n = length(x);
    for (l = 'A'; l <= 'Z'; l++) {
        f = 0;
        for (int i = 0; i < n; i++) {
            if (x[i] == l) {
                f++;
            }        
        }
        if (f >= m) {
            m = f;
            cL = l;
        }
    }
    return cL;
}

int omission(char *x) {
    char y[1000] = ""; //temporary string
    int f = 0; //'f' for flag
    int n = length(x);
    if (((x[n-1] < 'A') || (x[n-1] > 'Z')) && (x[n-1] != '_')) {
        //'_' is not included, so that it can be utilised for the substitutional decryption withou key
        strxfrm(y, x, n-1);
        strcpy(x, y);
        f = 1;
    }
    return f; 
}

int trial(char *x, FILE *f) {
    fseek(f, 0, SEEK_SET);
    char entry[1000]; //an entry from the list
    while (!feof(f)) {
        fscanf(f, "%s", entry);
        upperCase(entry);
        if (!strcmp(x, entry)) {
           return 1;
        }
    }
    return 0;
}

int bigram(char *x, char *y) {
    char l0, l1; //'l' for letter to be tested
    int f; //'f' for frequency of the letter
    int i = 0; //the number of assignments, N.B. this is not to be confused with 'i' in the third FOR-loop, which is in a different scope
    int m = 0; //'m' for maximum frequency of a letter
    int n; n = length(x);
    for (l0 = 'A'; l0 <= 'Z'; l0++) {
        for (l1 = 'A'; l1 <= 'Z'; l1++) {
            f = 0;
            for (int i = 0; i < n-1; i++) {
                if ((x[i] == l0) && (x[i+1] == l1)) {
                    f++;
                }        
            }
            if (f > m) {
                m = f;
                y[0] = l0; y[1] = l1;
                i++;
            }    
        }
    }
    return i;
}

int trigram(char *x, char *y) {
    char l0, l1, l2; //'l' for letter to be tested
    int f; //'f' for frequency of the letter
    int i = 0; //the number of assignments, N.B. this is not to be confused with 'i' in the third FOR-loop, which is in a different scope
    int m = 0; //'m' for maximum frequency of a letter
    int n = length(x);
    for (l0 = 'A'; l0 <= 'Z'; l0++) {
        for (l1 = 'A'; l1 <= 'Z'; l1++) {
            for (l2 = 'A'; l2 <= 'Z'; l2++) {
                f = 0;
                for (int i = 0; i < n-2; i++) {
                    if ((x[i] == l0) && (x[i+1] == l1) && (x[i+2] == l2)) {
                        f++;
                    }        
                }
                if (f > m) {
                    m = f;
                    y[0] = l0; y[1] = l1; y[2] = l2;
                    i++;
                }   
            }     
        }
    }
    return i;
}

int frequency(char *x, char y) {
    int f = 0; //'f' for frequency
    int n = length(x);
    for (int i = 0; i < n; i++) {
        if (x[i] == y)
            f++;
    }
    return f;    
}











                                                                                                             
                                    
                                                                                                                                                    
