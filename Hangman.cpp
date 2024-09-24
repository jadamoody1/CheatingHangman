//
// Created by Jada Moody on 4/28/24.
//

#include "Hangman.h"
#include <string>
using namespace std;

Hangman::Hangman(int WordLength, list<string> WordList) {
    this->WordLength = WordLength;
    this->NumberGuesses = 0;
    this->WordList = WordList;
    this->GuessedLetters = "";
    this->GameOver = false;


}

// SetWordLength() prompts the player to enter a word length and validates it against the available word list.
//If the entered length is invalid, the player is prompted to try again until a valid length is provided.
//Upon successfully setting the word length, the WordLength member variable is updated.

void Hangman::SetWordLength() {
    string input;
    int wordLength;
    bool checkLength;
    cout << "Enter a word length: ";
    while (!checkLength) {
        getline(cin, input);
        wordLength = stoi(input);
        checkLength = CheckWordLength(wordLength, WordList);
        if (!checkLength) {
            cout << "Invalid word length. Try again: ";
        }

    }
    WordLength = wordLength;

}


// SetGuesses prompts the player to enter the desired number of guesses.
//The input is validated and converted to an integer.
//The NumberGuesses member variable is then updated with the provided value.
void Hangman::SetGuesses() {

    string input1;
    int numberGuesses;
    cout << "Enter a number of guesses: ";
    getline(cin, input1);
    numberGuesses = stoi(input1);
    NumberGuesses = numberGuesses;
}


//CheckWordLength iterates through the provided word list to find if any words have the specified length.
//If a word of the specified length is found, it updates the WordLength member variable with the length
//and returns true. Otherwise, it returns false.
bool Hangman::CheckWordLength(int len, list<string> wordList) {
    for (string words: wordList) {
        if (words.length() == len) {
            WordLength = len;
            return true;
        }
    }
    return false;

}


//WordsRemaining filters the provided word list to include only words that have the specified length.
//It creates a new list (newWordList) and adds words from the original list (wordList) that match the specified length.
//Finally, it updates the WordList member variable with the filtered list.
void Hangman::WordsRemaining(int len, list<string> wordList) {
    list<string> newWordList;
    for (string words: wordList) {
        if (words.length() == len) {
            newWordList.push_back(words);
        }
    }
    WordList = newWordList;

}

//WordFamily constructs the word family, which represents the current state of the word being guessed.
//It takes a guessed letter and the original word, and optionally the current state of the word family.
//If the current state of the word family is provided, it updates it according to the guessed letter.
//If no current state is provided, it initializes the word family with dashes representing unguessed letters.
string Hangman::WordFamily(char letter, string word, string currentWordFamily) {
    string wordFamily;
    if (currentWordFamily != "") {
        for (int index = 0; index < word.length(); index++) {
            if (word[index] == letter) {
                currentWordFamily[index] = letter;
            }
        }
        wordFamily = currentWordFamily;
    }
    else {
        for (char character: word) {
            if (character != letter) {
                wordFamily.push_back('-');
            } else {
                wordFamily.push_back(letter);
            }
        }
    }
    return wordFamily;
}

//GamePlay handles the main gameplay loop of Hangman, where the player makes guesses to uncover the hidden word.
//It prompts the player for guesses and provides feedback on the current state of the game.
//The loop continues until the game is over (either the word is guessed correctly or the player runs out of guesses).

void Hangman::GamePlay(list<string>orignalList) {
    WordsRemaining(WordLength, WordList);
    string input2;
    cout << "Would you like to have a running total of the number of words remaining in the word list? ";
    getline(cin, input2);
    string currentWordFamily = "";
    string start = "";
        for(int i = 0; i < WordLength; i++) {
        start.push_back('-');
        }
        cout << start << endl;
    list<string>wordFamilies;
    while (!GameOver) {
        cout << NumberGuesses << " guesses left" << endl;
        cout << "Guesses made: " << GuessedLetters << endl;
        cout << endl;
        string start = "";
        string input;
        char guess;
        //checks if guess is a word or letter
        while (input.length() !=1 && input.length() != WordLength) {
            cout << "Guess a letter or word: ";
            getline(cin, input);
            while(!isalpha(input[0])) {
                cout << "Invalid input. Enter a letter or word: ";
                getline(cin, input);
            }
            if (input.length() == 1) {
                guess = input[0];
                while (GuessedLetters.find(guess) < GuessedLetters.length()) {
                    cout << "You've already guessed that letter try again: ";
                    getline(cin, input);
                    guess = input[0];
                }
            }
            else if (input.length() == WordLength && WordList.size() == 1) {
                if (input == WordList.front()) {
                    cout << "Congragulations! You won." << endl;
                    GameOver = true;
                    PlayAgain();
                }
                else {
                    cout << "Wrong guess!" << endl;
                    NumberGuesses = NumberGuesses - 1;
                }
            }
            GuessedLetters.push_back(guess);

        }

        map<string, list<string>> familyMap;
        //creates word families
        for (string words: WordList) {
            string wordfamily = WordFamily(guess, words, currentWordFamily);
            familyMap[wordfamily].push_back(words);
        }

        // find longest word family and set currentWordFamily to that value
        string longestFamily;
        int maxLength = 0;
        for (auto element : familyMap) {
            if (element.second.size() > maxLength) {
                longestFamily = element.first;
                maxLength = element.second.size();
            }
        }
        currentWordFamily = longestFamily;

        //Display Current State
        cout << "Current State: " << longestFamily << endl;
        if(input2 == "yes") {
            cout << "Remaining Words: " << familyMap[longestFamily].size()<< endl;

        }
        //updates guesses
        WordList = familyMap[longestFamily];
        if (longestFamily.find(guess) > longestFamily.length()) {
            NumberGuesses = NumberGuesses -1;
        }
        //ends game if user ran out of guesses, ask to play again
        if (NumberGuesses == 0 && longestFamily.find('-') < longestFamily.length()) {
            cout << "You're out of guesses. The word was: " << familyMap[longestFamily].front() << endl;
            GameOver = true;
            WordList = orignalList;
            PlayAgain();
        }

        if(longestFamily.find('-') > longestFamily.length() && NumberGuesses > 0) {
            cout<< "You guessed it! Congratulations! " << endl;
            PlayAgain();
        }


    }
}

    //PlayAgain prompts the player to decide whether they want to play the game again.
    //It reads the player's input and loops until a valid response ("yes" or "no") is provided.
    //If the player chooses to play again, the game state is reset and a new game is initiated.
    //If the player chooses not to play again, a farewell message is displayed.
    void Hangman::PlayAgain() {
        string input;
        cout << "Would you like to play again? ";
        getline(cin, input);
        while(input != "yes" && input != "no") {
            cout << "Invalid input. Type yes or no. ";
            getline(cin, input);
        }
        if (input == "yes") {
            GameOver = false;
            SetWordLength();
            SetGuesses();
            GuessedLetters ="";
            GamePlay(WordList);


        }
        else {
            cout << "Sad to see you go. Come back soon!";
        }

    }



