#include <stdio.h>
#include <stdlib.h>

//Program with strings implemented in C style, accepting some constant number of names, and putting them into an array
//allocating only amount of memory necessary for characters storage.

int main() {

        int n=10; //constant number of input names

        char* allNames[n]; //array of pointers to names
        char *str;

        char input_letter;

        for(int t=0;t<n;t++) {

            int i = 0;
            str= (char *) malloc(1 * sizeof(char));

            while (input_letter = getc(stdin), input_letter != '\n') { //reads input line
                str[i] = input_letter;
                i++;
                realloc(str, (i+1) * sizeof(char));   //reallocates memory while adding characters
            }
            str[i] = '\0';
            allNames[t]=str;  //saves pointer to single name in an array
        }

        //names display loop
        for(int t=0;t<n;t++){
            int i=0;
            while(*(allNames[t]+i)!='\0'){
                printf("%c", *(allNames[t]+i));
                i++;
            }
            printf("\n");
        }

        //memory deallocation
        for(int t=0;t<n;t++){
            free(allNames[t]);
        }

        return 0;
}
