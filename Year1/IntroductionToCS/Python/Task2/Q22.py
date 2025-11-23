import random

"""
Hangman Game Module
-------------------

This module implements a simple console-based Hangman game. It supports splitting a
'$'-delimited string into words, selecting a random secret word, updating guess results,
and running the full gameplay loop until the user wins or runs out of attempts.

Functions:
    • split_words(): Splits input string into a list of words.
    • choose_secret_word(): Selects a random word from a list.
    • get_guess_result(): Updates the displayed word based on a guessed letter.
    • play_hangman(): Runs the interactive Hangman game.

The game is played via console input and displays progress to the user.
"""

def split_words(game_words):
    words = []
    current_word = ""
    for char in game_words:
        if char != "$":
            current_word += char
        elif current_word:
            words.append(current_word)
            current_word = ""
    if current_word:
        words.append(current_word)
    return words



def choose_secret_word(words_list):
    return random.choice(words_list)

def get_guess_result(secret_word, guess_letter, currunt_word):
    for i in range(len(secret_word)):
        if secret_word[i] == guess_letter.lower():
            currunt_word[i] = guess_letter.lower()
    return currunt_word

def play_hangman(game_words):
    print("Welcome to Hangman Game!")
    secret_word = choose_secret_word(split_words(game_words))
    attempts = int(input("Enter number of attempts: "))
    word_length = len(secret_word)
    print(f"The word has {word_length} letters. You have {attempts} attempts.")
    guessed_letters = []
    # print("now we had")
    display_word = ["_"] * word_length
    while attempts > 0:
        print(" ".join(display_word))
        guess = input("Guess a letter: ")
        if guess in guessed_letters:
            print("You already guessed that letter.")
            continue

        guessed_letters.append(guess)

        if guess in secret_word:
            display_word = get_guess_result(secret_word, guess, display_word)
        else:
            attempts -= 1
            print(f"Wrong guess! Attempts remaining: {attempts}")

        if display_word == list(secret_word):
            print("Congratulations! You guessed the word:", secret_word)
            break

    if attempts == 0:
        print("Sorry, you've run out of attempts. The word was:", secret_word)