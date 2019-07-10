/* This is the console executable that makes use of the BullCow class
This acts as the view in an MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"
#pragma once

// to make syntax Unreal Friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void intro();
void play_game();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// the entrypoint for the application
int main() {
	bool play_again{false};
	do {
		// introduce the game
		intro();
		play_game();
		play_again = AskToPlayAgain();
	} while (play_again);

	std::cout << std::endl;
	return 0;
}

void intro() {
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {           ___ " << std::endl;
	std::cout << "          (o o)          (o o)" << std::endl;
	std::cout << "   /-------\\ /            \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O              O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |                |------|  * " << std::endl;
	std::cout << "    ^      ^                ^      ^ " << std::endl;

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();;
	std::cout << " letter isogram I'm thinking of?\n";
	return;
}

FText GetValidGuess() {// loop continually until the user gives a valid guess
	FText guess{};
	EGuessStatus status = EGuessStatus::invalid_status;
	do {
		//get a guess from the player
		int32 current_try = BCGame.GetCurrentTry();
		std::cout << "Try " << current_try << " of " << BCGame.GetMaxTries();
		std::cout << " Enter your guess: ";
		std::getline(std::cin, guess);

		status = BCGame.CheckGuessValidity(guess);
		switch (status)
		{
		case EGuessStatus::wrong_length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::not_lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		case EGuessStatus::not_isogram:
			std::cout << "Please enter an isogram (a word without repeating letters).\n\n";
			break;
		default:
			// assuming the guess is valid
			break;
		}
	} while (status != EGuessStatus::Ok); // keep looping until we get no errors
	
	return guess;
}

// plays a single game to completion
void play_game() {
	BCGame.Reset();
	int32 max_tries = BCGame.GetMaxTries();

	// loop for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= max_tries) { 
		FText guess = GetValidGuess();

		// Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";



	}
	PrintGameSummary();
	return;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText response{};
	std::getline(std::cin, response);

	std::cout << std::boolalpha;
	return (response[0] == 'y') || (response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Game Over.\n";
	}
}
