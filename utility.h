#ifndef UTILITY_H
#define UTILITY_H

//Structure storing setiment data
typedef struct {
    char word[50];  //lexicon word
    float value;   //sentiment value associated
} WordData;

//Reads the lexicon file and loads each word's data into an array of WordData
WordData* readLexiconFile(const char* filename, int* wordCount);

//Checks if a word is a positive intensifier
int isIntensifier(const char* word);

//Checks if a word is a negative intensifier
int isNegativeIntensifier(const char* word);

//Checks if a word is a negator
int isNegator(const char* word);

//Checks if a word is all caps
int isAllCaps(const char* word);

//Counts the number of exclamation marks in a sentence
int countExclamationMarks(const char* word);

//Removes exclamation marks from the end of the word
void removeExclamation(char* word);

//Converts a word into lowercase
void toLowerCase(char* str);

//Calculates the sentiment score of a sentence
void calculateSentimentScore(const char* sentence, WordData* lexicon, int wordCount, float *compound, float *positive, float *negative, float *neutral);

#endif 

