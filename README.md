# Word Length Analyzer
A C program that reads a text file with words and provides analytics based on the word lengths. It provides the following data:

* The number of words in the file
* The shortest word
* The longest word
* The first word
* The last word
* The cumulative length of all words
* The word's class if in Finnish

NOTE: The program is designed only to work with Finnish words and their classes. The original text file to analyze is lost and the program is not functional without it. This code is provided for showcase only.

## Usage
1. Clone the repository.
2. Compile the program using the Makefile provided by running the following command in the directory where the Makefile is located:
```bash
make
```
3. Run the program with the text file as an argument:
```bash
./word_length_analyzer
```