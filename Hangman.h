//
// Created by Jada Moody on 4/28/24.
//

#ifndef ASSIGNMENT6_HANGMAN_H
#define ASSIGNMENT6_HANGMAN_H

#include <string>
#include <list>
#include <iostream>
#include <map>

using namespace std;

class Hangman {
private:

    string GuessedLetters;
    int WordLength;
    bool GameOver;

public:

    //CONSTRUCTOR

    Hangman(int WordLength, list<string> WordList);
    list<string> WordList;
    int NumberGuesses;
    void SetWordLength();
    string WordFamily(char letter, string word, string currentWordFamily);
    bool CheckWordLength(int WordLength, list<string> WordList);
    void SetGuesses();
    void WordsRemaining (int WordLength, list<string> WordList);
    void GamePlay(list<string>originalList);
    void PlayAgain();



};


#endif //ASSIGNMENT6_HANGMAN_H
