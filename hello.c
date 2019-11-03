#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define STRLENGTH 101
int searchForNumber(char firstChar){
    if (firstChar >= '0' && firstChar <= '9'){
        return 1; //number
    }
    else if(firstChar == '+'){
        return 2; //special case of +
    }
    else {
        return 0; //char
    }
}
int printContact (int entryStringCount, char entries[STRLENGTH][STRLENGTH]){
    for(int i = 0; i < entryStringCount; i++){
        //when we are on last two strings
        if(i == (entryStringCount - 2)){
            printf("%s,",entries[i]);
            printf(" %s\n",entries[i + 1]);
            break;
        }
        else{
            printf("%s ", entries[i]);
        }
    }
    return 0;
}
int searchForMatch(char searchedString[STRLENGTH], int countSearchedString, char entries[STRLENGTH][STRLENGTH], int entryStringCount){
    const int countLettersByNumbers = 4;
    char lettersByNumbers[10][4] = {
        {'+'}, //0
        {'\n'}, //1
        {'a','b','c'}, //2
        {'d','e','f'}, //3
        {'g','h','i'}, //4
        {'j','k','l'}, //5
        {'m','n','o'}, //6
        {'p','q','r','s'}, //7
        {'t','u','v'}, //8
        {'w', 'x', 'y', 'z'} //9
    };
    
    int searchedChar = 0;
    int isNumber = 0;
    for (int entryIndex = 0; entryIndex < entryStringCount; entryIndex++){
        int matchCount = 0;
        int strLenght = strlen(entries[entryIndex]);
        for (int i = 0; i < strLenght; i++){
            isNumber = searchForNumber(entries[entryIndex][i]);
            //if current char is character
            if (isNumber == 0 || isNumber == 2){
                //find match for every char represented by searched number
                for (int j = 0; j < countLettersByNumbers; j++){
                    //convert char number to int
                    searchedChar = searchedString[matchCount] - '0';
                    if (lettersByNumbers[searchedChar][j] == tolower(entries[entryIndex][i])){
                        matchCount++;
                    }
                }
            }
            //if current char is number
            if(isNumber == 1){
                if (searchedString[matchCount] == entries[entryIndex][i]){
                    matchCount++;
                }
            }
             //if there is valid match
            if (matchCount == countSearchedString){
            return 1;
            }
        }
    }
    return -1;
}
int main(int argc, char *argv[]){   
    char entries[STRLENGTH][STRLENGTH];
    char searchedString[STRLENGTH];
    int countsearchedString = 0;
    int countMatchedContacts = 0;
    int correctInput = 0;
    int checkInput = 0;
    //Checks for correct input
    if (argc == 1){
        correctInput = 0; //no valid arguments, print everything
    }
    else if (argc == 2){
        correctInput = 1; //one valid argument, continue
    }
    else {
        correctInput = -1; //too many arguments, break
    }
    //copy argument for search
    if (correctInput == 1){
        for(int i = 0; argv[1][i] != '\0';i++){
            checkInput = searchForNumber(argv[1][i]);
            // if argument is valid
            if (checkInput == 1 && countsearchedString < STRLENGTH){
                searchedString[i] = argv[1][i];
                countsearchedString++;
            }
            // if argument is invalid, break
            if (checkInput == 0 || countsearchedString >= STRLENGTH) {
                correctInput = -1;
            }
        }
    }
    int checkForEOF = 0;
    int lastWasNumber = 0;
    while(checkForEOF != EOF && correctInput != -1){
        int contactWasFound = 0;
        int entryStringCount = 0;
        int checkForNumber = 0;
        //scan contact to entry
        while (checkForNumber == 0 && correctInput != -1){
            if(entryStringCount < STRLENGTH){
                checkForEOF = scanf("%100s", entries[entryStringCount]);
                checkForNumber = searchForNumber(entries[entryStringCount][0]);
                entryStringCount++;
            }
            //if there are too many inputs per line, break
            if(entryStringCount >= STRLENGTH){
                correctInput = -1;
            }
            //check if input list is correct
            if(checkForNumber == 0){
                lastWasNumber = 0;
            }
            if(lastWasNumber == 1 && (checkForNumber == 1 || checkForNumber == 2)){
                correctInput = -1;
            }
        }
        if (checkForEOF != EOF && correctInput != -1){
            //search for match with argument
            if ((checkForNumber == 1 || checkForNumber == 2) && correctInput == 1 ){
                contactWasFound = searchForMatch(searchedString, countsearchedString, entries, entryStringCount);
                lastWasNumber = checkForNumber;
            }
            //print matched contact
            if (contactWasFound == 1 || correctInput == 0){
                printContact(entryStringCount, entries);
                countMatchedContacts++;
            }
        }
    }
    //bad states
    if(countMatchedContacts == 0 && correctInput != -1){
        fprintf(stderr, "Not found\n");     
    }
    if(correctInput == -1){
        fprintf(stderr, "Wrong Input\n");
    }
    return 0;
}



