
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 
#include <ctype.h> 
 
#define MAX_WORDS 10 
#define MAX_WORD_LENGTH 20 
 
// Array of predefined words for the game 
const char *wordList[MAX_WORDS] = { 
    "programming", 
    "hangman", 
    "computer", 
    "software", 
    "algorithm", 
    "developer", 
    "challenge", 
    "language", 
    "creative", 
    "coding" 
}; 
 
// Function to select a random word from the list 
const char *selectRandomWord() { 
    srand(time(NULL)); 
    return wordList[rand() % MAX_WORDS]; 
} 
 
// Function to initialize the guessed word with underscores 
void initializeGuessedWord(char *guessedWord, const char *word) { 
    int length = strlen(word); 
    for (int i = 0; i < length; i++) { 
        guessedWord[i] = '_'; 
    } 
    guessedWord[length] = '\0'; 
} 
 
// Function to display the current state of the guessed word 
void displayGuessedWord(const char *guessedWord) { 
    printf("Current Word: %s\n", guessedWord); 
} 
 
// Function to check if the guessed word is complete 
int isWordComplete(const char *guessedWord) { 
    return strchr(guessedWord, '_') == NULL; 
} 
 
// Function to update the guessed word based on the guessed letter 
void updateGuessedWord(char *guessedWord, const char *word, char guessedLetter) { 
    int length = strlen(word); 
    for (int i = 0; i < length; i++) { 
        if (word[i] == guessedLetter) { 
            guessedWord[i] = guessedLetter; 
        } 
    } 
} 
 
int main() { 
    const char *selectedWord = selectRandomWord(); 
    char guessedWord[MAX_WORD_LENGTH]; 
    initializeGuessedWord(guessedWord, selectedWord); 
 
    int attempts = 6; // Number of allowed incorrect attempts 
    char guessedLetters[MAX_WORD_LENGTH]; // Array to store guessed letters 
    int numGuessedLetters = 0; 
 
    printf("Welcome to Hangman!\n"); 
 
    while (attempts > 0 && !isWordComplete(guessedWord)) { 
        displayGuessedWord(guessedWord); 
 
        printf("Attempts left: %d\n", attempts); 
        printf("Guessed letters: "); 
        for (int i = 0; i < numGuessedLetters; i++) { 
            printf("%c ", guessedLetters[i]); 
        } 
        printf("\n"); 
 
        printf("Enter a letter: "); 
        char guess; 
        scanf(" %c", &guess); 
 
        // Check if the guessed letter is already guessed 
        int alreadyGuessed = 0; 
        for (int i = 0; i < numGuessedLetters; i++) { 
            if (guessedLetters[i] == guess) { 
                alreadyGuessed = 1; 
                break; 
            } 
        } 
 
        if (alreadyGuessed) { 
            printf("You already guessed the letter '%c'. Try again.\n", guess); 
            continue; 
        } 
 
        guessedLetters[numGuessedLetters++] = guess; 
 
        // Check if the guessed letter is in the word 
        if (strchr(selectedWord, guess) != NULL) { 
            printf("Good guess!\n"); 
            updateGuessedWord(guessedWord, selectedWord, guess); 
        } else { 
            printf("Incorrect guess. Try again.\n"); 
            attempts--; 
        } 
    } 
 
    if (isWordComplete(guessedWord)) { 
        printf("Congratulations! You guessed the word: %s\n", selectedWord); 
    } else { 
        printf("Sorry! You ran out of attempts. The correct word was: %s\n", selectedWord); 
    } 
 
    return 0; 
}