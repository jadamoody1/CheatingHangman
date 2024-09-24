<h1>Cheating Hangman</h1>


<h2>Description</h2>
<p>This project implements a "Cheating Hangman" game where the computer bends the rules of traditional Hangman to ensure it has a strong advantage over the human player. Using a strategy that dynamically adjusts the possible word choices as the game progresses, the computer doesn't commit to a secret word until it forces the player into an inevitable loss.</p>


<b>How It Works:</b>

- The player chooses a word length and the computer generates a list of possible words of that length from a dictionary.
- For each letter the player guesses, the computer categorizes the remaining words into "word families" based on the pattern of that letter's occurrences.
- The computer selects the largest word family, maximizing the number of possible words, and updates the game accordingly. This tactic allows the computer to minimize the information revealed and maintain an advantage.
- The game ends when either the player guesses the word or runs out of guesses. If the player runs out of guesses, the computer reveals one of the remaining words.
<br />


<h2>Languages and Utilities Used</h2>

- <b>C ++</b> 
