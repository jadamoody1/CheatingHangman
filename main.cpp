#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Hangman.h"

// Created by Jada Moody
using namespace std;

int main() {
    string line;
    ifstream myfile;
    list<string> wordList;
    myfile.open("dictionary.txt");

    // open file and put lines in list
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            wordList.push_back(line);
        }

    }

        // initialize variables for checking wordlength
        string input;
        int wordLength;
        bool checkLength;
        Hangman cheatingHangman(wordLength, wordList); // create Hangman object with wordlength and wordList
        cheatingHangman.WordList = wordList; //set objects WordList to the list of words

        // prompt user for word length and check word length
        cout << "Enter a word length: ";
        while (!checkLength) {
            getline(cin, input);
            wordLength = stoi(input);  //convert input to integer
            checkLength = cheatingHangman.CheckWordLength(wordLength, wordList);
            if (!checkLength) {
                cout << "Invalid word length. Try again: ";
            }

        }


        string input1;
        int numberGuesses;
        // Prompt user for how many guesses
        cout << "Enter a number of guesses: ";
        getline(cin, input1);
        numberGuesses = stoi(input1); // convert input1 to integer
        // set objects NumberGuesses to numberGuesses
        cheatingHangman.NumberGuesses = numberGuesses;
        // start the game with original list of words to reset list for new game
        cheatingHangman.GamePlay(wordList);


    myfile.close();





}
