#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h> //for sqrt function

//Reads the lexicon file and loads each word's data into an array of WordData
WordData* readLexiconFile(const char* filename, int* wordCount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    int capacity = 500;  // Initial allocation size
    WordData* lexicon = (WordData*)malloc(capacity * sizeof(WordData));
    if (lexicon == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    char line[200];  //initialize line
    *wordCount = 0;  //initialize word count

    while (fgets(line, sizeof(line), file)) {
        //Using sscanf to parse the line
        if (sscanf(line, "%s\t%f\t%*f", lexicon[*wordCount].word, &lexicon[*wordCount].value) == 2) {
            (*wordCount)++;  //one more word stored
        }       

        //Expand lexicon array if capacity is reached
        if (*wordCount >= capacity) {
            capacity *= 2;
            WordData* temp = (WordData*)realloc(lexicon, capacity * sizeof(WordData));
            if (temp == NULL) {
                perror("Memory reallocation failed");
                free(lexicon);
                fclose(file);
                return NULL;
            }
            lexicon = temp;
        }
    }
    fclose(file);
    return lexicon;
}
    
 
//Checks if a word is positive intensifier - returns 1 if true
int isIntensifier(const char* word) {
    const char* intensifiers[] = {"very", "extremely", "really", "absolutely", "totally"};
    int numIntensifiers = sizeof(intensifiers) / sizeof(intensifiers[0]);
    for (int i = 0; i < numIntensifiers; i++) {
        if (strcmp(word, intensifiers[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

//Checks if a word is negative intensifier - returns 1 if true
int isNegativeIntensifier(const char* word) {
    const char* negativeIntensifiers[] = {"barely", "hardly", "scarcely", "somewhat", "slightly"};
    int numNegativeIntensifiers = sizeof(negativeIntensifiers) / sizeof(negativeIntensifiers[0]);
    for (int i = 0; i < numNegativeIntensifiers; i++) {
        if (strcmp(word, negativeIntensifiers[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

//Checks if a word is a negator - returns 1 if true
int isNegator(const char* word) {
    const char* negators[] = {"not", "isn't", "wasn't", "shouldn't", "won't", "cannot", "can't", "nor", "neither", "without"};
    int numNegators = sizeof(negators) / sizeof(negators[0]);
    for (int i = 0; i < numNegators; i++) {
        if (strcmp(word, negators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

//Checks if a word is all caps - returns 1 if true
int isAllCaps(const char* word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isupper(word[i])) {
            return 0;
        }
    }
    return 1;
}

//Counts the number of exclamation marks in a sentence - returns count
int countExclamationMarks(const char* word) {
    int count = 0;
    int length = strlen(word);

    //Start from the last character and count exclamation marks
    for (int i = length - 1; i >= 0; i--) {
        if (word[i] == '!') {
            count++;
        } else {
            break;  //Stop counting if we encounter a non-exclamation mark
        }
    }

    return count;
}

//Removes punctuation marks from the end of the word - modifies pointer
void removeExclamation(char* word) {
    int len = strlen(word);
    int i = len - 1;

    while (i >= 0 && word[i] == '!') {
        word[i] = '\0';  //switch exclamatiion with end of the string
        i--;
    }
}

//Coverts a word into lowercase so it could be recognized in different scenerios - modifies pointer
void toLowerCase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}


//Calculates the sentiment score of a sentence
void calculateSentimentScore(const char* sentence, WordData* lexicon, int wordCount, float *compound, float *positive, float *negative, float *neutral) {
    //Establish variables
    float totalScore = 0.0;
    int sentimentWordCount = 0;

    //bonus portion variables
    float posScore =0.0;
    float negScore = 0.0;
    float neuScore = 0.0;

    //Copy sentence
    char sentenceCopy[256];
    strncpy(sentenceCopy, sentence, sizeof(sentenceCopy) - 1);
    sentenceCopy[sizeof(sentenceCopy) - 1] = '\0';

    char* word = strtok(sentenceCopy, " ,.");

    float negatenextword = 1.0f;
    int exclamationCount = 0; // counts exclamation marks
    float nextwordboost = 1.0f;

    while (word != NULL) {
        neuScore += 1; //count each variables as neutral till proved otherwise

        //Check for exclamation marks before removing punctuation marks
        exclamationCount = countExclamationMarks(word);

        //Remove exclamation marks
        removeExclamation(word); 


        char originalword[50];
        strncpy(originalword, word, sizeof(originalword) - 1);
        originalword[sizeof(originalword) - 1] = '\0';

        toLowerCase(word);

        float wordScore = 0.0;
        int found = 0;

        //Checks if word is in lexicon
        for (int i = 0; i < wordCount; i++) {
            if (strcmp(lexicon[i].word, word) == 0 || strcmp(lexicon[i].word, originalword) == 0) {
                wordScore = lexicon[i].value;
                found = 1;
                break;
            }
        }

        if (found) { // ignoring non-lexicon words
            //adjust score if word is all caps
            if (isAllCaps(originalword)) {
                wordScore *= 1.5;  //all caps boost
            }

            //Account for exclamation marks
            if(exclamationCount>0){ // added a if loop to save time from doing extra calculation
                wordScore *= 0.292*exclamationCount + 1; 
            }    
                

            //Accounting for previous words boost
            wordScore *= nextwordboost;
            nextwordboost=1;

            wordScore *= negatenextword;

            totalScore += wordScore;
            sentimentWordCount++;


            //use final version of the sentiment score of the word to adjust positive,negative, neutral scores -- bonus
            if(wordScore > 0){
                posScore += wordScore +1 ; //1 is added because neutral is stored as 1 instead of 0
                neuScore -=1;
            }
            else if (wordScore < 0){
                negScore += abs(wordScore) +1; //1 is added because neutral is stored as 1 instead of 0
                neuScore -=1;
            }

        } 
        //check if next word should be negated -- negation in my code affects every word that comes after it in the sentence
        else if (isNegator(word)) {
            negatenextword = -0.5;
        }
        //check if the next word should be intensified
        else if(isIntensifier(word) || isNegativeIntensifier(word)) {
            // Set the multiplier based on the type of word (intensifier, negative intensifier, or negator)
            if (isIntensifier(word)) {
                nextwordboost = 0.293;
            } else if (isNegativeIntensifier(word)) {
                nextwordboost = -0.293;
            }

            // Apply ALLCAPS boost to the next word if the current word is in ALL CAPS
            if (isAllCaps(originalword)) {
                nextwordboost *= 1.5;  // Apply ALLCAPS boost
            }

            // Apply the exclamation mark boost to the multiplier (exponentially)
            if (exclamationCount > 0) {
                nextwordboost *= 0.292*exclamationCount+ 1; // Boost per exclamation mark
            }
            nextwordboost=1+nextwordboost;

        }

        //Move to the next word
        word = strtok(NULL, " ,.");
    }


    //Calculate compound score
    *compound = totalScore / (sqrt(totalScore * totalScore + 15));

    //Calculate positive, negative, neutral scores - bonus portion
    float total = posScore + neuScore + negScore;
    *positive = posScore / total;
    *negative = negScore / total;
    *neutral = neuScore / total;

}