/*
 * Game logic container for simple guess the word game
 * based on MasterMind.
 */

#pragma once

#include <string>
#include <map>
#include <vector>

// To make syntax Unreal friendly
using FString = std::string;
using int32 = int;

template<typename T, typename K>
using TMap = std::map<T, K>;

template<typename T>
using TArray = std::vector<T>;

struct FBullCowCount
{
	int32 Bulls;
	int32 Cows;

	FBullCowCount(int32 Bulls, int32 Cows)
	{
		this->Bulls = Bulls;
		this->Cows = Cows;
	}
};

struct FGuess
{
	FString HiddenWord;
	int32 NumberOfTriesToGuessIt;
};

enum class EWordValidity
{
	NOT_ISOGRAM,
	OK,
	IS_NOT_LOWERCASE,
	INVALID_LENGTH,	
	INVALID_CHARACTER
};

class FBullCowGame
{
public:
	FBullCowGame();

	int32 GetMaxNumberOfTries() const;
	int32 GetCurrentTries() const;
	int32 GetHiddenWordLenght() const;		
	bool IsGameWon() const;	

	void Reset();
	
	EWordValidity CheckGuessValidity(const FString& guess) const;	
	FBullCowCount SubmitValidGuess(FString Guess); 
	bool SubmitHiddenWordLenght(int32 HiddenWordLenght);

private:
	bool IsIsogram(const FString& word) const;
	bool IsWordLowercase(const FString& word) const;
	FString GetHiddenWord() const;

	void SetHiddenWordLenght(int32 HiddenWordLength);
		
	TMap<int32, FGuess> MyWordLenghtToGuess;	
	int32 MyHiddenWordLength;
	int32 MyCurrentTry;
	int32 MyMaxHiddenWordLenght;
	int32 MyMinHiddenWordLenght;
	bool bIsGameWon;
};

