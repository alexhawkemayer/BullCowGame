/* This is the console executable, that makes use of the BullCow class
This acts as the view in an MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once
#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame(){ Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() {
	const FString HIDDEN_WORD = "plant"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const {
	if (!IsIsogram(guess))
	{
		return EGuessStatus::not_isogram; 
	}
	else if (!IsLowercase(guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::not_lowercase; 
	}
	else if (guess.length() != MyHiddenWord.length())
	{
		return EGuessStatus::wrong_length; // if the guess length is wrong
	}
	else
	{
		return EGuessStatus::Ok;
	}
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 h{ 0 }; h < WordLength; ++h) 
	{
		// compare letters against the guess
		for (int32 g{ 0 }; g < WordLength; ++g) 
		{
			if (guess[g] == MyHiddenWord[h]) {
				if (h == g) { // if they're in the same place
					++BullCowCount.Bulls; // increment bulls
				}
				else {
					++BullCowCount.Cows; // increment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	} 
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
	}
	return true;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word)    // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { // if the letter is in the map
			return false; // we do NOT have an isogram
		} else {
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}

	return true; // for example in cases where /0 is entered
}
