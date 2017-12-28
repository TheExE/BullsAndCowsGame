#pragma once
#include <string>
#include <map>

using FString = std::string;
using int32 = int;

template<typename T, typename K>
using TMap = std::map<T, K>;

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
	~FBullCowGame();

	int32 GetMaxNumberOfTries() const;
	int32 GetCurrentTries() const;
	int32 GetHiddenWordLenght() const;
	FString GetCurrentWord() const;	
	bool IsGameWon() const;

	EWordValidity CheckGuessValidity(const FString& guess) const;
	void Reset();
	FBullCowCount SubmitValidGuess(FString Guess); 
	// TODO: Add method for incrementing the turn count

private:

	bool IsIsogram(const FString& word) const;
	bool IsWordLowercase(const FString& word) const;

	int32 MyMaxTries;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;
};

