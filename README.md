## Vader Sentiment Analysis Tool


## Project Overview

This project implements a simplified version of the VADER (Valence Aware Dictionary and sEntiment Reasoner) sentiment analysis model in C, designed to analyze sentences and output compound, positive, negative, and neutral sentiment scores. The implementation closely mirrors the behavior of the Python VADER library and includes handling for linguistic nuances such as negations, intensifiers, ALL-CAPS emphasis, and exclamation marks.


## Features

Lexicon-based sentiment scoring using vader_lexicon.txt

Handles:

- Positive and negative intensifiers

- Negation across sentences

- ALL-CAPS emphasis

- Exclamation mark amplification

Outputs compound, positive, negative, and neutral sentiment scores

Results compared against the official Python VADER library


## Result Comparison with Python Library

| Sentence                                                                 | Compound (C Model) | Compound (Python VADER) |
|--------------------------------------------------------------------------|--------------------|--------------------------|
| VADER is smart, handsome, and funny.                                     | 0.8316             | 0.8316                   |
| VADER is smart, handsome, and funny!                                     | 0.8539             | 0.8439                   |
| VADER is very smart, handsome, and funny.                                | 0.8518             | 0.8545                   |
| VADER is VERY SMART, handsome, and FUNNY.                                | 0.9139             | 0.9227                   |
| VADER is VERY SMART, handsome, and FUNNY!!!                              | 0.9452             | 0.9342                   |
| VADER is VERY SMART, uber handsome, and FRIGGIN FUNNY!!!                 | 0.9452             | 0.9469                   |
| VADER is not smart, handsome, nor funny.                                 | -0.5994            | -0.7424                  |
| At least it isn’t a horrible book.                                       | 0.3071             | 0.4310                   |
| The plot was good, but the characters are uncompelling and not great.    | -0.1406            | -0.7042                  |
| Make sure you :) or :D today!                                            | 0.8225             | 0.8633                   |
| Not bad at all                                                           | 0.3071             | 0.4310                   |



## How to Compile and Run

make

./sentiment
