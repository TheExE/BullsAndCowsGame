#include "FBullCowGame.h"



FBullCowGame::FBullCowGame()
{
	// Init Word map, all hidden words MUST be an isogram.
	TArray<FString> AvailableWords = {"dog", "wing", "plant", "planet"};
	MyMaxHiddenWordLenght = 0;
	MyMinHiddenWordLenght = INT32_MAX;
	for(auto& Word : AvailableWords)
	{
		/*
		 * Function generated from: https://mycurvefit.com/ to
		 * give a smooth number of tries increase as word lenght
		 * grows.
		 */
		const int32 WordLenght = Word.length();
		const int32 NumberOfTries = 28.63043 - 26.622199/
			(1.0 + pow(WordLenght/6.023672, 4.822943));
		FGuess Guess;
		Guess.HiddenWord = Word;
		Guess.NumberOfTriesToGuessIt = NumberOfTries;
		MyWordLenghtToGuess[WordLenght] = Guess;

		// Store min and max word lenght for future refenrece
		if(WordLenght > MyMaxHiddenWordLenght)
		{
			MyMaxHiddenWordLenght = WordLenght;
		}
		 
		if(WordLenght < MyMinHiddenWordLenght)
		{
			MyMinHiddenWordLenght = WordLenght;
		}
	}

	Reset();
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
	MyCurrentTry = 1;
	bIsGameWon = false;
}

int32 FBullCowGame::GetMaxNumberOfTries() const
{
	return MyWordLenghtToGuess.at(GetHiddenWordLenght()).NumberOfTriesToGuessIt;
}

int32 FBullCowGame::GetCurrentTries() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLenght() const
{
	return MyHiddenWordLength;
}

FString FBullCowGame::GetHiddenWord() const
{
	return MyWordLenghtToGuess.at(MyHiddenWordLength).HiddenWord;
}

void FBullCowGame::SetHiddenWordLenght(int32 HiddenWordLength)
{
	MyHiddenWordLength = HiddenWordLength;
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
	int32 WordLenght = MyHiddenWordLength; 
	FString HiddenWord = GetHiddenWord();

	// Loop through all letters in the hidden word
	for(int32 i = 0; i < WordLenght; i++)
	{
		// Loop through all letters in the guess
		for(int32 j = 0; j < WordLenght; j++)
		{
			// Compare letter against the hidden word
			if (HiddenWord[i] == Guess[j] && i == j)
			{
				// Letter match at right position
				BullCowCount.Bulls++;
			}
			else if(HiddenWord[i] == Guess[j])
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

bool FBullCowGame::SubmitHiddenWordLenght(int32 HiddenWordLenght)
{
	bool bIsTheLenghtValid = false;
	if(HiddenWordLenght >= MyMinHiddenWordLenght &&
		HiddenWordLenght <= MyMaxHiddenWordLenght)
	{
		SetHiddenWordLenght(HiddenWordLenght);
		bIsTheLenghtValid = true;
	}

	return bIsTheLenghtValid;
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
