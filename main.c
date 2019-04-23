//>>>---------> >>>---------> Libraries <---------<<< <---------<<<

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//>>>---------> >>>---------> Functions' prototypes <---------<<< <---------<<<

int upperCase(char *x);  
int rotation(char *x, int r); 
int substitution(char *x, char *y); 
int decryptingAB(char *x, char *y); 
char letter(char *x); 
int omission(char *x); 
int trial(char *x, FILE *f);
int bigram(char *x, char *y);
int trigram(char *x, char *y);
int frequency(char *x, char y);
char consecutive(char *x);

//>>>---------> >>>---------> Main <---------<<< <---------<<<

int main()
{
    //Declaration of variables
    char setting[1]; //the character defining the setting as a header 
    char word[1000]; //a word from the text
    char text[10000] = ""; //the text
    char buffer[1000]; //temporary data
    char rKey[2]; //the key for rotation; N.B. it must have two digits in the header, e.g. 3 = 03
    char sKey[26] = "QAZXSWEDCVFRTGBNHYUJMKIOLP"; //the key for substitution
    char AB[26] = "__________________________"; //the encrytping alphabet
    char dAB[26]; //the decrypting alphabet
    char mC[6] = " ETAOI"; //the first five most common letters in the Modern English language from http://letterfrequency.org/
    char mB[] = "THHEINERANREONATENNDTIESORTEOFEDISITALARSTNTTOSECODERAETSAEMRO"; //the first four most common bigrams in the Modern English language from https://blogs.sas.com/content/iml/2014/09/26/bigrams.html
    char mR[5] = " SETF"; //the first four most common repeated letters in the Modern English language from https://en.wikipedia.org/wiki/Frequency_analysis
    int r; //'r' for rotator, i.e. the integer of the rKey
    int n; //length
    int S; //the setting of the action
    char cL; //the most common letter
    char B = ' '; //the best letter
    int line; //the number of characters in a line
    char cBg[2]; //the most common bigram
    char cTg[3]; //the most common trigram
    int p0, p1; //'p' for position
    int e; //'e' for the number of entries
    char alpha; //the beginning character utilised for a FOR-loop in case-5
    char zeta; //utilised in case-5; the character, that worked for the previous word
    int w; //the number of words
    int iW0, iW1; //the number of incomplete words, i.e. with an '_'
    char cC; //the most common consecutive letter
    
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
                n = strlen(word);
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
                n = strlen(word);
                upperCase(word);
                strcat(text, word);
            }
            //Getting the most common letter from which
            n = strlen(text);
            cL = letter(text);
            //Printing relevant data
            printf("Rotational decrytion without key\n"); fprintf(output, "Rotational decrytion without key\n");
            printf("Most common letter found: %c\n", cL); fprintf(output, "Most common letter found: %c\n", cL);
            printf("Character tested:   Words:  English* words:  Englishness:\n"); 
            fprintf(output, "Character tested:   Words:  English* words:  Englishness:\n");
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
                    n = strlen(word);
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
                n = strlen(word);
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
                n = strlen(word);
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
                n = strlen(word);
                upperCase(word);
                strcat(text, word);
                //strcat(text, " ");
            }
            //Getting statistics
            n = strlen(text);
            cL = letter(text);//getting the most common letter
            bigram(text, cBg); //getting the most common bigram
            trigram(text, cTg); //getting the most common trigram
            cC = consecutive(text); 
            printf("Most common letter found: %c\nMost common bigram: %s\nMost common trigram: %s\nMost common repetition: %c\n", cL, cBg, cTg, cC);
            //Making an alphabet
            if (!strncmp(cTg, cBg, 2)) {
                if ((cTg[2] == cL) || (cTg[0] == cL)) {
                    AB[(int)cTg[0]-65] = 'T';
                    AB[(int)cTg[1]-65] = 'H';
                    AB[(int)cTg[2]-65] = 'E';
                } else {
                    AB[(int)cTg[0]-65] = 'I';
                    AB[(int)cTg[1]-65] = 'N';
                    AB[(int)cTg[2]-65] = 'G';
                } 
            } else if ((cTg[1] == cBg[0]) && (cTg[2] == cBg[1])) {
                AB[(int)cTg[0]-65] = 'T';
                AB[(int)cTg[1]-65] = 'H';
                AB[(int)cTg[2]-65] = 'E';  
            } else if ((cTg[2] == cL) || (cTg[0] == cL)) {
                AB[(int)cTg[0]-65] = 'E';
                AB[(int)cTg[1]-65] = 'N';
                AB[(int)cTg[2]-65] = 'T'; 
            } else {
                AB[(int)cTg[0]-65] = 'A';
                AB[(int)cTg[1]-65] = 'N';
                AB[(int)cTg[2]-65] = 'D'; 
            }
            if (cBg[1] == cL) {
                AB[(int)cL-65] = 'E';
            } 
            if (cBg[0] == cL) {
                AB[(int)cBg[0]-65] = 'T';
                AB[(int)cBg[1]-65] = 'H';
            }
            printf("Beginning alphabet: %s\n", AB);
            //Filling in the text
            iW0 = 1; iW1 = 0; 
            while (iW0 != iW1) {
                iW0 = iW1;
                iW1 = 0;
                fseek(input, 1, SEEK_SET);
                line = 0;
                w = 0;
                while (!feof(input)) {
                    w++;
                    fscanf(input, "%s", word);
                    n = strlen(word);
                    upperCase(word);
                    strcpy(buffer, word);
                    substitution(buffer, AB);   
                    //printf("%s ", buffer);
                    //Ending the line by at most 100 characters
                    line += n;
                    if (line >= 100) {
                        //printf("\n");
                        line = 0;
                    }
                    omission(buffer);
                    p0 = (int)(strchr(buffer, '_') - buffer);
                    p1 = (int)(strrchr(buffer, '_') - buffer);
                    if ((frequency(buffer, '_') > 0) && (strlen(buffer) != 1)) {
                        iW1++;
                        if (frequency(buffer, '_') == 1) {
                            char buffer1[100];
                            char buffer2[100];
                            char entry[100];
                            e = 0;
                            fseek(list, 0, SEEK_SET);
                            while (!feof(list)) {
                                fscanf(list, "%s", entry);
                                upperCase(entry);
                                if (strlen(entry) == strlen(buffer)) {
                                    strcpy(buffer1, entry);
                                    entry[p0] = '_';  
                                    if (!strcmp(buffer, entry)) {
                                        if (frequency(AB, buffer1[p0]) == 0) {
                                            e++;
                                            strcpy(buffer2, buffer1);
                                        }
                                    }   
                                }
                            }
                            if (e == 1) {
                                AB[(int)word[p0]-65] = buffer2[p0];          
                            }
                        }
                        else if (frequency(buffer, '_') == 2) {
                            char buffer1[100];
                            char buffer2[100];
                            char entry[100];
                            e = 0;
                            fseek(list, 0, SEEK_SET);
                            while (!feof(list)) {
                                fscanf(list, "%s", entry);
                                upperCase(entry);
                                if (strlen(entry) == strlen(buffer)) {
                                    strcpy(buffer1, entry);
                                    entry[p0] = '_'; 
                                    entry[p1] = '_';
                                    if (!strcmp(buffer, entry)) {
                                        if ((frequency(AB, buffer1[p0]) == 0) && (frequency(AB, buffer1[p1]) == 0)) {
                                            e++;
                                            strcpy(buffer2, buffer1);
                                        }
                                    }   
                                }
                            }
                            if (e == 1) {
                                AB[(int)word[p0]-65] = buffer2[p0];   
                                AB[(int)word[p1]-65] = buffer2[p1];
                            }   
                        }
                    }
                }  
            }
            fseek(input, 1, SEEK_SET);
            printf("Decrypted text:\n"); fprintf(output, "Decrypted text:\n");
            while (!feof(input)) {
                fscanf(input, "%s", word);
                n = strlen(word);
                upperCase(word);
                decryptingAB(AB, dAB);
                substitution(word, AB);    
                printf("%s ", word); fprintf(output, "%s ", word);
                //Ending the line by at most 100 characters
                line += n;
                if (line >= 100) {
                    printf("\n"); fprintf(output, "\n");
                    line = 0;
                }
            }
            printf("\nNumber of total words: %d\nNumber of incomplete words: %d\nSuccess: %f%\nFinal alphabet: %s\n", w, iW1, (float)(w-iW1)/(float)w*100, AB);
            break;
        case 7:
            printf("EASTER EGG\n");
            int ploughman = 0;
            arrow:
            printf("All work and no spaghetti code makes Jack a dull boy\n"); //EASTER EGG
            ploughman++;
            if (ploughman != 9) 
                goto arrow; //who says, that one can not make a while loop using GOTO?
        default:
            printf("Invalid S");
    }   
}


//>>>---------> >>>---------> Functions' denfinitions

/* Inputs: the string 'x' (any length) to be modified
 * Return value: returns 1, if any modification occured at all; returns 0, if otherwise
 * Description: modifies a string, so that every lower case Latin letter is transformed in upper-case
 */
int upperCase(char *x) {
    char l; //'l' for letter
    int f = 0; //'f' for flag
    int n = strlen(x);
    for (int i = 0; i < n; i++) {
        l = x[i];
        if ((l >= 'a') && (l <= 'z')) {
            l -= 32;   
        }  
        x[i] = l;
    }  
    return f; 
}

/* Inputs: the string 'x' to be modified, the rotator 'r' (int), which is the integer rotation occurs by
 * Return value: returns 1, if any rotation occured at all; returns 0, if otherwise
 * Description: rotates every upper-case Latin letter in a string by an integer
 */
int rotation(char *x, int r) {
    char l; //'l' for letter
    int il; //integer of 'l'
    int f = 0; //'f' for flag
    int n = strlen(x);
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

/* Inputs: the string 'x' to be modified, the substitutional alphabet 'y' as a string a.k.a the key
 * Return value: returns 1, if substitution occured at all; returns 0, if otherwise
 * Description: encrypts the string by an alphabet; namely, it substitutes every upper-case Latin letter with the corresponding letter in the alphabet
 */
int substitution(char *x, char *y) {
    char l; //'l' for letter
    int il; //integer of 'l'
    int f = 0; //'f' for flag
    int n = strlen(x);
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

/* Inputs: the alphabet 'y' as a string; N.B. the string 'x' can be any string with at least 26 elements
 * N.B. the string 'y' must be the same length as the string 'x'
 * Outputs: the converted alphabet 'x' as a string
 * Return value: returns 1, if any conversion occured at all; returns 0, if otherwise 
 * Description: converts an substitutional alphabet used for encryption into an alphabet for decryption; namely, it makes an alphabet by alternating the pairs;
 * e.g. A:K -> K:A
 */
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

/* Inputs: the string 'x' to be searched within
 * Return value: returns the most common upper-case Latin letter; the default letter is 'A'
 * Description: finds the most common upper-case Latin letter in the string; if two characters are equally the most common, then the highest (later in the 
 * alphabet) is chosen; ignores other characters, e.g. lower-case, punctuation
 */
char letter(char *x) {
    char l; //'l' for letter to be tested
    int f; //'f' for frequency of the letter
    int m = 0; //'m' for maximum frequency of a letter
    char cL = 'A'; //the letter, that has the maxmimum frequency 
    int n = strlen(x);
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

/* Inputs: the string 'x' to be modified
 * Return value: returns 1, if a character was omitted at the end; returns 0, if otherwise
 * Description: omits any non-Latin non-upper-case character (except '_') at the end of the string
 */
int omission(char *x) {
    char y[1000] = ""; //temporary string
    int f = 0; //'f' for flag
    int n = strlen(x);
    if (((x[n-1] < 'A') || (x[n-1] > 'Z')) && (x[n-1] != '_')) {
        //'_' is not included, so that it can be utilised for the substitutional decryption withou key
        strxfrm(y, x, n-1);
        strcpy(x, y);
        f = 1;
    }
    return f; 
}

/* Inputs: the string 'x' to be tested, the file 'f', which has a list of words 
 * Return value: returns 1, if the string 'x' is contain in the list of common English words
 * Description: tests, whether the string is in the file or not
 */
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

/* Inputs: the string 'x' to be search within, N.B. the string 'y' can be any string with at least 2 elements
 * Outputs: the resultant bigram 'y' as a string
 * Return value: returns the number of bigrams, that were considered, i.e. tested against the previous most common bigram
 * Description: modifies the string 'y' to contain the most common upper-case bigram (i.e. pair of letters) found in the string 'x'; ; if two bigram are 
 * equally the most common, then the highest (later in the alphabet) is chosen;
 */
int bigram(char *x, char *y) {
    char l0, l1; //'l' for letter to be tested
    int f; //'f' for frequency of the letter
    int i = 0; //the number of assignments, N.B. this is not to be confused with 'i' in the third FOR-loop, which is in a different scope
    int m = 0; //'m' for maximum frequency of a letter
    int n; n = strlen(x);
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

/* Inputs: the string 'x' to be search within, N.B. the string 'y' can be any string with at least 3 elements
 * Outputs: the resultant trigram 'y' as a string
 * Return value: returns the number of trigrams, that were considered, i.e. tested against the previous most common trigram
 * Description: modifies the string 'y' to contain the most common upper-case trigram (i.e. pair of letters) found in the string 'x'; ; if two trigram are 
 * equally the most common, then the highest (later in the alphabet) is chosen;
 */
int trigram(char *x, char *y) {
    char l0, l1, l2; //'l' for letter to be tested
    int f; //'f' for frequency of the letter
    int i = 0; //the number of assignments, N.B. this is not to be confused with 'i' in the third FOR-loop, which is in a different scope
    int m = 0; //'m' for maximum frequency of a letter
    int n = strlen(x);
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

/* Inputs: the string 'x' to be search within, the character 'y' to be sought for
 * Return value: returns the frequency
 * Description: calculates the frequency of a character in a string
 */
int frequency(char *x, char y) {
    int f = 0; //'f' for frequency
    int n = strlen(x);
    for (int i = 0; i < n; i++) {
        if (x[i] == y)
            f++;
    }
    return f;    
}

/* Inputs: the string 'x' to be search within
 * Return value: the character, that is repeated the most
 * Description: finds the most common consecutively repeated upper-case Latin letter 
 */
char consecutive(char *x) {
    char l; //'l' for letter to be tested
    char c = '@'; //'c' for the character being tested; '@' is the default, if there was no most common consecutive letter
    int f; //'f' for frequency of the letter
    int m = 0; //'m' for maximum frequency of a letter
    int n; n = strlen(x);
    for (l = 'A'; l <= 'Z'; l++) {
        f = 0;
        for (int i = 0; i < n-1; i++) {
            if ((x[i] == l) && (x[i+1] == l)) {
                f++;
            }        
        }
        if (f > m) {
            m = f;
            c = l;
        }    
    }
    return c;
}










                                                                                                             
                                    
                                                                                                                                                    
