/* The game logic (no view code or direct user interaction)
The game is a simple word game based on Mastermind
*/
#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus {
	invalid_status,
	Ok,
	not_isogram,
	wrong_length,
	not_lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength();
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);

// ^^ please try and ignore this and focus on the interface above ^^
private: 
	// see constructor for initialization
	int32 MyCurrentTry{};
	FString MyHiddenWord;
	bool bGameIsWon;
	
	bool IsLowercase(FString) const;
	bool IsIsogram(FString) const;
};
