#include "FBullCowGame.h"



FBullCowGame::FBullCowGame()
{
	Reset();
}


FBullCowGame::~FBullCowGame()
{
}

EWordValidity FBullCowGame::CheckGuessValidity(const FString& guess) const
{
	EWordValidity result = EWordValidity::OK;

	if (!IsIsogram(guess))
	{
		result = EWordValidity::NOT_ISOGRAM;
	}
	else if (!IsWordLowercase(guess))
	{
		result = EWordValidity::IS_NOT_LOWERCASE;
	}
	else if (guess.length() != GetHiddenWordLenght())
	{
		result = EWordValidity::INVALID_LENGTH;
	}

	return result;
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bIsGameWon = false;
}

int32 FBullCowGame::GetMaxNumberOfTries() const
{
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTries() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLenght() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bIsGameWon;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{	
	MyCurrentTry++;
	FBullCowCount BullCowCount(0, 0);

	// Assumes both words are same lenght
	int32 WordLenght = MyHiddenWord.length(); 

	// Loop through all letters in the hidden word
	for(int32 i = 0; i < WordLenght; i++)
	{
		// Loop through all letters in the guess
		for(int32 j = 0; j < WordLenght; j++)
		{
			// Compare letter against the hidden word
			if (MyHiddenWord[i] == Guess[j] && i == j)
			{
				// Letter match at right position
				BullCowCount.Bulls++;
			}
			else if(MyHiddenWord[i] == Guess[j])
			{
				// Letters match at wrong position
				BullCowCount.Cows++;
			}
		}
	}
	
	// If all the characters of word is bulls then we won the game
	if(BullCowCount.Bulls == WordLenght)
	{
		bIsGameWon = true;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(const FString& word) const
{
	bool bIsIsogram = true;
	TMap<char, bool> charactersSeen;
	for (auto letter : word)
	{
		letter = tolower(letter);
		if(!charactersSeen[letter])
		{
			// Characters has not previously been seen
			charactersSeen[letter] = true;
		}
		else
		{
			bIsIsogram = false;
			break;
		}
	}

	return bIsIsogram;
}

bool FBullCowGame::IsWordLowercase(const FString& word) const
{
	for (const auto& Letter : word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}

	return true;
}
