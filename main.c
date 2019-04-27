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
//>>>---------> >>>---------> Main <---------<<< <---------<<<
int main()
{
    //Declaration of variables
    char setting[1]; //the character defining the setting as a header 
    int S; //the setting of the action
    char word[100]; //a word from the text
    char text[10000] = ""; //the text
    //Temporary data
    char buffer[100]; 
    char buffer1[100];
    char buffer2[100];
    char entry[100]; //the entry from a dictionary
    char rKey[2]; //the key for rotation; N.B. it must have two digits in the header, e.g. 3 = 03
    int r; //'r' for rotator, i.e. the integer of the rKey
    char sKey[26];
    char AB[26] = "__________________________"; //the encrytping alphabet; this must be initialised as all underscores for substitutional decryption without key
    char dAB[26]; //the decrypting alphabet
    //the following data is from: http://practicalcryptography.com/cryptanalysis/letter-frequencies-various-languages/english-letter-frequencies/
    //this website was also helpful: https://www3.nd.edu/~busiforc/handouts/cryptography/cryptography%20hints.html 
    char mC[] = "ETAOI"; //the first five most common letters in the Modern English language
    int n; //length
    char cL; //the most common letter
    char B = ' '; //the best letter
    int w; //'w' for the number of words
    int englishWords = 0; //the number of English words
    float englishness; //the percentage of English words in the text
    float highest; //the highest percentage yet
    char cBg[2]; //the most common bigram
    char cTg[3]; //the most common trigram
    int line; //the number of characters in a line
    int p0, p1; //'p' for position
    int e; //'e' for the number of entries
    int iW0, iW1; //the number of incomplete words, i.e. with an '_' 
    /* >>>--------->
      S: Action:
      0  rotational encryption
      1  rotational decryption with key 
      2  rotational decryption without key
      3  substitutional encryption with key
      4  substitutional decryption with key
      5  substitutional decryption without key
    */
    //Beginning of files
    FILE *input; //the 'input' file has the necessary data and the text to be either encrypted on decrypted
    input = fopen("input.txt", "r");
    if (input == NULL) { //this ends the program, if there is nothing in the file
        perror("fopen()");
        return 0;
    }
    FILE *output; //the 'output' file has the necessary data and either the encrypted or decrypted text
    output = fopen("output.txt", "w");
    FILE *list; //the 'list' file is the English dictionary to be utilised; it must have either spaces or new-lines to sperate entries
    list = fopen("list.txt", "r");
    if (list == NULL) { //this ends the program, if there is nothing in the file
        perror("fopen()");
        return 0;
    }  
    //The above is printed in both the console and the 'output' file.
    //N.B. that all printings will be in both.
    printf("The first character must be one of the numbers representing 'S' for the following settings; it then must be followed by any additional data.\nThe cipher follows then after.\n");
    printf("S: Action:\t\t\t\t\tNotes:\n"); fprintf(output, "S: Action:\t\t\t\t\t\t\t\t\tNotes:\n"); //N.B. that '\t' makes a tab-space; these are to align the columns.
    printf("0  Rotational encryption\t\t\tFollowed by the key in two-digits\n"); fprintf(output, "0  Rotational encryption\t\t\t\t\tFollowed by the key in two-digits\n");
    printf("1  Rotational decryption with key\t\tFollowed by the key in two-digits\n"); fprintf(output, "1  Rotational decryption with key\t\t\tFollowed by the key in two-digits\n");
    printf("2  Rotational decryption without key\t\tNothing is to follow except the cipher\n"); fprintf(output, "2  Rotational decryption without key\t\tNothing is to follow except the cipher\n");
    printf("3  Substitutional encryption with key\t\tFollowed by 26-characters being the key\n"); fprintf(output, "3  Substitutional encryption with key\t\tFollowed by 26-characters being the key\n");
    printf("4  Substitutional decryption with key\t\tFollowed by 26-characters being the key\n"); fprintf(output, "4  Substitutional decryption with key\t\tFollowed by 26-characters being the key\n");
    printf("5  Substitutional decryption without key\tNothing is to follow except the cipher\n"); fprintf(output, "5  Substitutional decryption without key\tNothing is to follow except the cipher\n");
    printf(">>>--------->\n"); fprintf(output, ">>>--------->\n");//divider
    //Finding the setting
    fscanf(input, "%1s", setting); //reading the chosen setting
    S = atoi(setting); //casting the setting to an integer value
    printf("Setting: %d i.e. ", S); fprintf(output, "Setting: %d i.e. ", S); //printing the chosen setting
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
            printf(">>>--------->\n"); fprintf(output, ">>>--------->\n");//divider
            printf("Encrypted text:\n"); fprintf(output, "Encrypted text:\n");
            line = 0; //resetting the count of characters for a new line
            while (!feof(input)) {
                fscanf(input, "%s", word); //getting the next word i.e. string until space
                n = strlen(word); //getting the length of the word
                upperCase(word); //converting all lower-case to upper-case
                rotation(word, r); //rotating every Latin letter by the integer value of the key
                printf("%s ", word); fprintf(output, "%s ", word); //printing the word followed by a space for the next word
                //Ending the line by at most 100 characters
                line += n + 1; //'line' is the total number of characters including spaces on a line
                if (line >= 100) { //if the line has at most 100 characters, then a new line is begun and the number is reset to 0
                    printf("\n"); fprintf(output, "\n");
                    line = 0;
                }
            } //this loops repeats encrypting, and printing each word until the end of the file has been reached
            break;
        //Rotational decryption with key <---------<<< <---------<<<
        case 1:
            fscanf(input, "%2s", rKey); //getting the key
            r = 26 - atoi(rKey); //casting the key to an integer value; the rotator for decryption is the key subtracted from 26
            //Printing relevant data
            printf("Rotational decrytion with key\n"); fprintf(output, "Rotational decrytion with key\n");
            printf("Key: %s\n", rKey); fprintf(output, "Key: %s\n", rKey);
            printf("Rotator: %d\n", r); fprintf(output, "Rotator: %d\n", r);
            printf(">>>--------->\n"); fprintf(output, ">>>--------->\n");//divider
            printf("Decrypted text:\n"); fprintf(output, "Decrypted text:\n");
            /* The following then decrypts the text with the key. This section is similar to encryption in case 0, but a 'decrypting' alphabet is created.*/
            line = 0; //resetting the count of characters for a new line
            while (!feof(input)) {
                fscanf(input, "%s", word); //getting the next word i.e. string until space
                n = strlen(word); //getting the length of the word
                upperCase(word); //converting all lower-case to upper-case
                rotation(word, r); //rotating every Latin letter by the integer value of the key
                printf("%s ", word); fprintf(output, "%s ", word); //printing the word followed by a space for the next word
                //Ending the line by at most 100 characters
                line += n + 1; //'line' is the total number of characters including spaces on a line
                if (line >= 100) { //if the line has at most 100 characters, then a new line is begun and the number is reset to 0
                    printf("\n"); fprintf(output, "\n");
                    line = 0;
                }
            } //this loops repeats encrypting, and printing each word until the end of the file has been reached
            break;
        //Rotational decryption without key by frequency <---------<<< <---------<<<
        case 2:
            //Flattening the text into one string, i.e. omitting spaces, so that the letter() function can easily search for the most common letter
            //This is discarded later and not utilised in the actual decryption.
            while (!feof(input)) {
                fscanf(input, "%s", word); //getting the next word until the space
                n = strlen(word);
                upperCase(word); //Lower-cases are also converted to upper-case.
                strcat(text, word); //concatenating this word, i.e. adding it on, to the string 'text', which is all the strings combined
            }    
            n = strlen(text); //getting the length of the flatten text
            cL = letter(text); //getting the most common letter from which
            //Printing relevant data
            printf("Rotational decrytion without key\n"); fprintf(output, "Rotational decrytion without key\n");
            printf("Most common letter found: %c\n", cL); fprintf(output, "Most common letter found: %c\n", cL);
            //Printing the header for the statistics
            printf("Character tested:   Words:  English* words:  Englishness (%%):\n"); 
            fprintf(output, "Character tested:   Words:  English* words:  Englishness (%%):\n");
            //Trial for each common letter
            //Each predicted letter is tested as giving the key by how many English words are found with it.
            //The FOR-loop goes through all the possible most common letters; e.g. the most common letter found might represent a 'T', i.e. the second most 
            //...common in the English corpus.
            for (int i = 0; i < strlen(mC); i++) {
                fseek(input, 1, SEEK_SET); //beginning the cursor at the beginning
                r = (int)(cL - mC[i]); //the new rotator from the most common encrypted letter found and the predicted letter
                w = 0; englishWords = 0; //reseting the word-count
                //Decryption of the text with this prediction
                while (!feof(input)) {
                    w++; //increment of the word-count
                    fscanf(input, "%s", word); //getting the next word
                    n = strlen(word);
                    upperCase(word);
                    rotation(word, 26 - r); //decryption by r
                    omission(word); //omission of punctuation at the end
                    englishWords += trial(word, list); //trial by spelling, i.e. if the word is in the list, then the count of English words increases
                }
                //Calculating the highest percentage of Englishness
                englishness = (float)englishWords / (float)w;
                if (englishness > highest) { //If the current percentage is higher than the previous one, then it takes over as the highest.
                    B = mC[i];
                    highest = englishness;
                }
                printf("%c\t\t    %d\t    %d\t\t     %f\n", mC[i], w, englishWords, englishness * 100); 
                fprintf(output, "%c\t\t\t\t    %d\t    %d\t\t\t     %f\n", mC[i], w, englishWords, englishness * 100); //printing some statistics
            }
            //With the chosen key by the above testing with the highest percentage, the text is then fully decrypted.
            fseek(input, 1, SEEK_SET); //beginning the cursor
            r = 26 - (int)(cL - B); //A rotator for decryption is made by the difference between the most common letter found and the predicted corresponding letter
            printf("*detected by list.txt\n"); fprintf(output, "*detected by list.txt\n");
            printf("Chosen letter and rotator by freuqency: %c %d\n", B, r); fprintf(output, "Chosen letter and rotator by freuqency: %c %d\n", B, r);
            printf(">>>--------->\n"); fprintf(output, ">>>--------->\n");//divider
            printf("Decrypted text:\n"); fprintf(output, "Decrypted text:\n");
            /* The following then decrypts with rotator 'r' from the finding above. This section is exactly similar to the decryption in case 1.*/
            line = 0; //resetting the count of characters for a new line
            while (!feof(input)) {
                fscanf(input, "%s", word); //getting the next word i.e. string until space
                n = strlen(word); //getting the length of the word
                upperCase(word); //converting all lower-case to upper-case
                rotation(word, r); //rotating every Latin letter by the integer value of the key
                printf("%s ", word); fprintf(output, "%s ", word); //printing the word followed by a space for the next word
                //Ending the line by at most 100 characters
                line += n + 1; //'line' is the total number of characters including spaces on a line
                if (line >= 100) { //if the line has at most 100 characters, then a new line is begun and the number is reset to 0
                    printf("\n"); fprintf(output, "\n");
                    line = 0;
                }
            } //this loops repeats encrypting, and printing each word until the end of the file has been reached
            break;
        //Substitutional encryption <---------<<< <---------<<<
        case 3: 
            fscanf(input, "%26s", sKey); //getting the key as string of 26 characters
            strcpy(AB, sKey); //copying, the key to another string 'AB' for naming purposes
            //Printing relevant data
            printf("Substitutional encrytion\n"); fprintf(output, "Substitutional encrytion\n");
            printf("Key: %s\n", sKey); fprintf(output, "Key: %s\n", sKey);
            printf(">>>--------->\n"); fprintf(output, ">>>--------->\n");//divider
            printf("Encrypted text:\n"); fprintf(output, "Encrypted text:\n");
            //The following gets a word, converts to upper-case, encrypts it with the key, and then prints it.
            while (!feof(input)) {
                fscanf(input, "%s", word); //getting the word until the space
                n = strlen(word); //getting the length of the word
                upperCase(word); //converting all lower-case to upper-case
                substitution(word, AB); //every Latin letter is substituted with the corresponding letter in the alphabet.
                printf("%s ", word); fprintf(output, "%s ", word); //printing the word followed by a space for the next word
                //Ending the line by at most 100 characters as explained above
                line += n + 1;
                if (line >= 100) {
                    printf("\n"); fprintf(output, "\n");
                    line = 0;
                }
            }
            break;
        //Substitutional decryption with key <---------<<< <---------<<<
        case 4:
            fscanf(input, "%26s", sKey); //getting the key
            strcpy(AB, sKey); //copying, the key to another string 'AB' for naming purposes
            //Printing relevant data
            printf("Substitutional decrytion with key\n"); fprintf(output, "Substitutional decrytion with key\n");
            printf("Key: %s\n", sKey); fprintf(output, "Key: %s\n", sKey);
            printf(">>>--------->\n"); fprintf(output, ">>>--------->\n");//divider
            printf("Decrypted text:\n"); fprintf(output, "Decrypted text:\n");
            while (!feof(input)) {
                fscanf(input, "%s", word); //getting the word until the space
                n = strlen(word); //getting the length of the word
                upperCase(word); //converting all lower-case to upper-case
                decryptingAB(AB, dAB); //the alphabet 'AB' is converted to an alphabet for decryption; refer to the function decryptingAB() for more.
                substitution(word, dAB); //every Latin letter is substituted with the corresponding letter in the alphabet.
                printf("%s ", word); fprintf(output, "%s ", word); //printing the word followed by a space for the next word
                //Ending the line by at most 100 characters as explained above
                line += n + 1;
                if (line >= 100) {
                    printf("\n"); fprintf(output, "\n");
                    line = 0;
                }
            }
            break;
        case 5:
            //Printing relevant data
            printf("Substitutional decrytion without key\n"); fprintf(output, "Substitutional decrytion without key\n");
            //Flattening the text into one string, i.e. omitting spaces, so that the letter() function can easily search for the most common letter
            //This is discarded later and not utilised in the actual decryption.
            while (!feof(input)) {
                fscanf(input, "%s", word); //getting the next word until the space
                n = strlen(word);
                upperCase(word); //Lower-cases are also converted to upper-case.
                strcat(text, word); //concatenating this word, i.e. adding it on, to the string 'text', which is all the strings combined
            }  
            //Getting statistics
            n = strlen(text);
            cL = letter(text);//getting the most common letter
            bigram(text, cBg); //getting the most common bigram
            trigram(text, cTg); //getting the most common trigram
            printf("Most common letter found: %c\nMost common bigram: %s\nMost common trigram: %s\nMost common repetition: %c\n", cL, cBg, cTg, cC);
            fprintf(output, "Most common letter found: %c\nMost common bigram: %s\nMost common trigram: %s\nMost common repetition: %c\n", cL, cBg, cTg, cC);
            //Making an alphabet by prediction
            /* The following predictions is from: http://practicalcryptography.com/cryptanalysis/letter-frequencies-various-languages/english-letter-frequencies/; 
            this website was also helpful: https://www3.nd.edu/~busiforc/handouts/cryptography/cryptography%20hints.html
            The five most common bigrams: TH, HE, IN, ER, AN
            The five most common trigrams: THE, AND, ING, ENT, ION*/
            /* If the most common bigram and trigram share the same first two letter, then the most common trigram is either 'THE' or 'ING', since, both 'TH' 
            and 'IN' can be the most common bigram.*/
            if (!strncmp(cTg, cBg, 2)) {
                /* If the most common letter is either the first or third letter of the trigram, then the most common trigram is 'THE', since 'I' is less 
                common than 'E' or 'T'. If otherwise, then by probability, the most common trigram, that has a common bigram, is 'ING'.*/
                if ((cTg[2] == cL) || (cTg[0] == cL)) { 
                    AB[(int)cTg[0]-65] = 'T';
                    AB[(int)cTg[1]-65] = 'H';
                    AB[(int)cTg[2]-65] = 'E';
                } else {
                    AB[(int)cTg[0]-65] = 'I';
                    AB[(int)cTg[1]-65] = 'N';
                    AB[(int)cTg[2]-65] = 'G';
                } 
            } 
            /* If the most common bigram and trigram share the same last two letters, then the most common trigram is most likely 'THE' again, since 'HE' is a 
            common bigram.*/
            else if ((cTg[1] == cBg[0]) && (cTg[2] == cBg[1])) {
                AB[(int)cTg[0]-65] = 'T';
                AB[(int)cTg[1]-65] = 'H';
                AB[(int)cTg[2]-65] = 'E';  
            }
            /* If the foresaid is not true, and the most common letter is either the first or third letter of the most common trigram, then the most common
            trigram is not 'THE' and the only trigram, that fulfils the condition and is not 'THE', is 'ENT'*/
            else if ((cTg[2] == cL) || (cTg[0] == cL)) {
                AB[(int)cTg[0]-65] = 'E';
                AB[(int)cTg[1]-65] = 'N';
                AB[(int)cTg[2]-65] = 'T'; 
            } 
            /* If the forsaid is not true, then the most common trigram is most likely not 'ENT' and the remaining common trigram is 'AND'.*/
            else {
                AB[(int)cTg[0]-65] = 'A';
                AB[(int)cTg[1]-65] = 'N';
                AB[(int)cTg[2]-65] = 'D'; 
            }
            /* If in any case, the most common letter if the second letter of the most common bigram, then the bigram is most likely 'HE', since it is the 
            only common bigram, that has a common letter as the second letter.*/
            if (cBg[1] == cL) {
                AB[(int)cBg[0]-65] = 'H';
                AB[(int)cBg[1]-65] = 'E';
            } 
            printf("Beginning alphabet: %s\n", AB); fprintf(output, "Beginning alphabet: %s\n", AB);
            /* With these bare bones of the alphabet, the cipher is decrypted, any unknown letters are left with an underscore, i.e. '_'; e.g. it may look 
            like "_E___T____N_______________". With words, that have at most two missing letters, any obvious words are filled in and the alphabet is updated. 
            E.g. 'TH_T' has only one possibile solution, which is 'THAT'; so, the letter for 'A' is known. The first WHILE-loop repeats this process, until no 
            more letters can be updated.*/
            iW0 = 1; iW1 = 0; //this initial inequality begins the loop. 'iW0' is the old count for incomplete words, whilst 'iW1' is the current.
            //if the current count of incomplete words is equal to the previous one, then now new letter has been found and the loop ends.
            while (iW0 != iW1) {
                iW0 = iW1;
                iW1 = 0; //reseting the count
                fseek(input, 1, SEEK_SET); //reseting the cursor at the beginning of the 'input' file
                w = 0; //the total word-count
                while (!feof(input)) {
                    w++; //the increment of the word-count
                    fscanf(input, "%s", word); //getting the next word in the 'input' file
                    n = strlen(word);
                    upperCase(word); //converting all lower-case to upper-case
                    strcpy(buffer, word); //copying th word into a temporary string
                    substitution(buffer, AB); //decrypting the temporary string, i.e. 'buffer' by the current alphabet; N.B. it will most likely have underscores
                    //This condition is to just test, if there is an underscore at all.
                    if (frequency(buffer, '_') > 0)
                        iW1++; //the increment for the count of incomplete words                    
                    omission(buffer); //omitting any punctuation at the end of the string
                    p0 = (int)(strchr(buffer, '_') - buffer); //the position of the first underscore
                    p1 = (int)(strrchr(buffer, '_') - buffer); //the position of the second underscore; N.B. if there is only one, then they will be equal
                    //If there is one missing letter, i.e. underscore in the decrypted word, i.e. the string 'buffer', then the following occurs.
                    //Another condition is, that it is not a single letter word, since the list has single letters like 'b' as possible 'words'.
                    if ((frequency(buffer, '_') == 1) && (strlen(buffer) != 1)) {
                        e = 0; //the number of possible entries
                        fseek(list, 0, SEEK_SET); //reseting the cursor for the 'list' file
                        //The following WHILE-loop goes through every entry.
                        while (!feof(list)) {
                            fscanf(list, "%s", entry); //getting the entry from the 'list' file
                            upperCase(entry); //convert the entry upper-case
                            //If the entry is the same length as the word from above, then the following occurs.
                            if (strlen(entry) == strlen(buffer)) {
                                strcpy(buffer1, entry); //The string 'buffer1' keeps a temporary copy of the entry.
                                /*The entry's letter, that is in the same position as the underscore in the decrypted word, i.e. the string 'buffer', is made 
                                as an underscore.*/
                                entry[p0] = '_'; 
                                /* By this way, if this modified entry is equal to the decrypted word, then we know, that there is a matching possible entry.
                                E.g. if the decrypted word is 'TH_T', and one of the scanned entries is 'THAT', then when the 'A' is substituted for an 
                                underscore, one can know, that 'THAT' is a possible solution for 'TH_T'. N.B. that strcmp() returns a 0, if the two strings are
                                equal, hence the '!'.*/
                                if (!strcmp(buffer, entry)) {
                                    /* This condition is to eliminate any entry, that has a letter already in the substitutional alphabet, i.e. AB.*/
                                    if (frequency(AB, buffer1[p0]) == 0) { 
                                        e++; //Thus, the count for possible entries is increased.
                                        strcpy(buffer2, buffer1); //The entry, that worked, is kept in a temporary variable, i.e. copied to another string.
                                    }
                                }   
                            }
                        }
                        /* The above loop goes through every entry in the list and counts, if it is a possible solution to the decrypted word with the current
                        substitutional alphabet. If there is only one possible entry, then there is only one possible letter, that fills the underscore.*/
                        if (e == 1) {
                            /* The corresponding letter in the substitutional alphabet, i.e. at the same location as the word's letter at the position of the 
                            underscore is made to be the letter in the letter in original entry, i.e. the string 'buffer2', at the position of the underscore.
                            E.g. if 'THAT' was the only entry for 'TH_T', which is the decryption of 'KYUK', then letter in AB in 'U' position is made to be 
                            'K', i.e. U:K.*/
                            AB[(int)word[p0]-65] = buffer2[p0];          
                        }
                    }
                    //If there two missing letters, i.e. underscores in the decrypted word, i.e. the string 'buffer', then the following occurs.
                    //Another condition is, that it is not a double letter word, since it is already known, that there are many possible double letter words.
                    //The following is very similar to the above algorithm, but with two underscores. 
                    else if ((frequency(buffer, '_') == 2) && (strlen(buffer) != 2)) {
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
            /* Once the above WHILE-loop ends, i.e. no more new letters can be updated to the substitutional alphabet, then the cipher is fully decrypted with
            this final alphabet as in susbtitutional decryption with key in case 4.*/
            fseek(input, 1, SEEK_SET);
            line = 0; //reseting the count of characters for making a new-line
            printf(">>>--------->\n"); fprintf(output, ">>>--------->\n");//divider
            printf("Decrypted text:\n"); fprintf(output, "Decrypted text:\n");
            while (!feof(input)) {
                fscanf(input, "%s", word);
                n = strlen(word);
                upperCase(word);
                substitution(word, AB); //N.B. However, AB is already constructed above in a way, that it is the decrypting alphabet.
                printf("%s ", word); fprintf(output, "%s ", word);
                //Ending the line by at most 100 characters
                line += n;
                if (line >= 100) {
                    printf("\n"); fprintf(output, "\n");
                    line = 0;
                }
            }
            //The relevant statistics are printed:
            printf("\n>>>--------->\n"); fprintf(output, "\n>>>--------->\n");//divider
            printf("Number of total words: %d\n", w); fprintf(output, "Number of total words: %d\n", w);
            printf("Number of incomplete words: %d\n", iW1); fprintf(output, "Number of incomplete words: %d\n", iW1);
            printf("Success: %f%\n", (float)(w - iW1)/(float)w * 100); fprintf(output, "Success: %f%\n", (float)(w - iW1)/(float)w * 100);//the percentage of complete words to the total
            printf("Final alphabet: %s\n", AB); fprintf(output, "Final alphabet: %s\n", AB);
            /* This method relies purely on certainties and not guessing. If a letter in an entry perfectly correpsonds to a missing letter in the 
            decrypted form, with no other possible letters, then it is certain, that that letter is the one to update to the substitutional alphabet.
            Disclaimer: this method relies on common frequencies in English, like 'TH' as a common bigram. Generally, the bigger the cipher, the more chances
            of success. Some words, that are not in the list, e.g. fictitious proper nouns, and have a less common letter, e.g. 'Z', may return as incomplete. 
            This is why the 'success' of the decryption is given and the underscores are kept.*/
            break;
        case 7:
            printf("EASTER EGG\n");
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
    int n; n = strlen(x); //'n' for length
    //The FOR-loop goes through every character, i.e. element of the string 'x'. This character is 'x[i]', and the integer 'i' is between 0, and 'n'.
    for (int i = 0; i < n; i++) {
        l = x[i]; //'l' is the variable of the character.
        if ((l >= 'a') && (l <= 'z')) {
            /* If the character is a lower-case Latin letter, i.e. with 97 = 'a', and 122 ='z', then 32 is subtracted from it, since the set of upper-case 
            Latin letters is 32 less than the set of lower-case Latin letters.*/
            l -= 32; 
            x[i] = l; //The original element in the string 'x' is altered to the new upper-case letter.
        }   
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
    int n; n = strlen(x); //'n' for length
    //The FOR-loop goes through every character, i.e. element of the string 'x'. This character is 'x[i]', and the integer 'i' is between 0, and 'n'.
    for (int i = 0; i < n; i++) {
        l = x[i]; //'l' is the variable of the character.
        if ((l >= 'A') && (l <= 'Z')) {
            /* If the letter is an upper-case Latin letter, then the integer-identifier is applied by the formula given in the Assignment-Outline, 
            i.e. e(m) = (m + k) mod 26.*/
            il = (int)l - 65; //getting the integer-identifier, e.g. A:0, B:1, ..., Z:25. N.B. the character literal must be casted to an integer firstly.
            il = (il + r) % 26; //rotating the integer by the formula.
            l = (char)(il + 65); //converting the integer-identifier back to the character's value.
            f = 1; //The flag is updated.
        }  
        x[i] = l; //The original element in the string 'x' is altered to the new upper-case letter.
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
    int n; n = strlen(x); //'n' for length
    for (int i = 0; i < n; i++) {
        l = x[i];
        if ((l >= 'A') && (l <= 'Z')) {
            il = (int)l - 65;
            l = y[il];
            f = 1;
        }  
        x[i] = l; //The original element in the string 'x' is altered to the new upper-case letter.
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
    int n; n = strlen(x); //'n' for length
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
    int n; n = strlen(x); //'n' for length
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
    int n; n = strlen(x); //'n' for length
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
    int n; n = strlen(x); //'n' for length
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
    int n; n = strlen(x); //'n' for length
    for (int i = 0; i < n; i++) {
        if (x[i] == y)
            f++;
    }
    return f;    
}











                                                                                                             
                                    
                                                                                                                                                    
