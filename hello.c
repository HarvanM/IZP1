#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int searchForNumber(char firstChar){
    if (firstChar >= '0' && firstChar <= '9'){
        return 1; 
    }
    else {
        return 0;
    }
}
int printContact (int countBufferEntities, char buffer[100][100]){
    for(int i = 0; i < countBufferEntities; i++){
        //when we are on last two strings
        if(i == (countBufferEntities - 2)){
            printf("%s,",buffer[i]);
            printf(" %s\n",buffer[i + 1]);
            break;
        }
        //when printing name
        else{
            printf("%s ", buffer[i]);
        }
    }
    return 0;
}
int searchForMatch(char searchedString[100], int countSearchedString, char buffer[100][100], int countBufferEntities){
    int countLettersByNumbers = 4;
    char lettersByNumbers[10][4] = {
        {'+'},
        {'\n'},
        {'a','b','c'},
        {'d','e','f'},
        {'g','h','i'},
        {'j','k','l'},
        {'m','n','o'},
        {'p','q','r','s'},
        {'t','u','v'},
        {'w', 'x', 'y', 'z'}
    };
    int matchCount = 0;
    int searchedChar = 0;
    for (int bufferIndex = 0; bufferIndex < countBufferEntities; bufferIndex++){
        for (int i = 0; i < countSearchedString; i++){
            //if current char is character
            if(searchForNumber(buffer[bufferIndex][i]) == 0){
                //find match for every char represented by searched number
                for (int j = 0; j < countLettersByNumbers; j++){
                    //convert char number to int
                    searchedChar = searchedString[i] - '0';
                    if (lettersByNumbers[searchedChar][j] == tolower(buffer[bufferIndex][i])){
                            matchCount++;
                    } 
                }
            }
            //if current char is number
            if(searchForNumber(buffer[bufferIndex][i]) == 1){
                if (searchedString[i] == buffer[bufferIndex][i]){
                    matchCount++;
                }
            }
            //if there was no new match found, break
            if (matchCount == i){
                break;
            }
        }
        //if there is valid match
        if (matchCount == countSearchedString){
            return 1;
        }
        matchCount = 0;
    }
    return -1;
}
int main(int argc, char *argv[]){   
    char buffer[100][100];
    char searchedString[100];
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
            if (checkInput == 1 && countsearchedString < 100){
                searchedString[i] = argv[1][i];
                countsearchedString++;
            }
            // if argument is invalid, break
            if (checkInput == 0 || countsearchedString >= 100) {
                correctInput = -1;
            }
        }
    }
    int checkForEOF = 0;
    int lastWasNumber = 0;
    while(checkForEOF != EOF && correctInput != -1){
        int contactWasFound = 0;
        int countBufferEntities = 0;
        int checkForNumber = 0;
        //scan contact to buffer
        while (checkForNumber != 1 && correctInput != -1){
            if(countBufferEntities < 100){
                checkForEOF = scanf("%99s", buffer[countBufferEntities]);
                checkForNumber = searchForNumber(buffer[countBufferEntities][0]);
                countBufferEntities++;
            }
            //if there are too many inputs per line, break
            if(countBufferEntities >= 100){
                correctInput = -1;
            }
            //check if input list is correct
            if(checkForNumber == 0){
                lastWasNumber = 0;
            }
            if(lastWasNumber == 1 && checkForNumber == 1){
                correctInput = -1;
            }
        }
        if (checkForEOF != EOF && correctInput != -1){
            //search for match with argument
            if (checkForNumber == 1 && correctInput == 1 ){
                contactWasFound = searchForMatch(searchedString, countsearchedString, buffer, countBufferEntities);
                lastWasNumber = checkForNumber;
            }
            //print matched contact
            if (contactWasFound == 1 || correctInput == 0){
                printContact(countBufferEntities, buffer);
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



