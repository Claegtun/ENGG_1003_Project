#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    const char trueText[200] = "Hello, World!";
    char hiddenText[200];
    char r; //'r' for rotation
    char l; //'l' for letter
    
    printf("%s\n", trueText);
    
    for (int i = 0; i < 200; i++) {
        hiddenText[i] = trueText[i];             
    }
    printf("%s", hiddenText);
}
