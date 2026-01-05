#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

//Test sentences
const char* testSentences[] = {
    "VADER is smart, handsome, and funny.",
    "VADER is smart, handsome, and funny!",
    "VADER is very smart, handsome, and funny.",
    "VADER is VERY SMART, handsome, and FUNNY.",
    "VADER is VERY SMART, handsome, and FUNNY!!!",
    "VADER is VERY SMART, uber handsome, and FRIGGIN FUNNY!!!",
    "VADER is not smart, handsome, nor funny.",
    "At least it isn't a horrible book.",
    "The plot was good, but the characters are uncompelling and the dialog is not great.",
    "Make sure you :) or :D today!",
    "Not bad at all"
};


int main() {
    //Update worddata from vader_lexicon.txt
    int wordCount;
    WordData* lexicon = readLexiconFile("vader_lexicon.txt", &wordCount);

    //Memory allocation
    if (lexicon == NULL) {
        printf("Failed to load lexicon.\n");
        return 1;
    }

    //Run test cases
    printf("Sentiment Analysis Results:\n");
    for (int i = 0; i < sizeof(testSentences) / sizeof(testSentences[0]); i++) {
        float compoundScore, positiveScore, negativeScore, neutralScore;
        calculateSentimentScore(testSentences[i], lexicon, wordCount, &compoundScore, &positiveScore, &negativeScore, &neutralScore);
        printf("\n\nSentence: \"%s\"\n", testSentences[i]);
        printf("Compound Score: %.4f\n", compoundScore);
        printf("Positive Score: %.4f\n", positiveScore);
        printf("Negative Score: %.4f\n", negativeScore);
        printf("Neutral Score: %.4f\n", neutralScore);
    }    

    //Free allocated memory
    free(lexicon);
    return 0;
}