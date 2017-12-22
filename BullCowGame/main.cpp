#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool ShouldRunTheGameAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main()
{
	bool bPlayeAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		bPlayeAgain = ShouldRunTheGameAgain();

	} while (bPlayeAgain);

	return 0;
}

void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun game !" << std::endl;
	std::cout << "Can you guess " << BCGame.GetHiddenWordLenght();
	std::cout << " letter isogram I'am thinking of ?" << std::endl;
}

void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxNumberOfTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTries() <= MaxTries)
	{
		// Ask for guess
		std::cout << "Number of tries: " << BCGame.GetCurrentTries() <<
			" Enter the guess: " << std::endl;

		const FText Guess = GetValidGuess();

		// Inform player about their guess
		std::cout << "Your guess: " << Guess << std::endl;

		const FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls: " << BullCowCount.Bulls << " Cows: " << BullCowCount.Cows
			<< std::endl;
	}
}

FText GetValidGuess()
{
	bool bIsGuessValid = false;
	FText Guess = "";

	while (!bIsGuessValid)
	{
		std::getline(std::cin, Guess);
		EWordValidity Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EWordValidity::OK:
			bIsGuessValid = true;
			break;

		case EWordValidity::NOT_ISOGRAM:
			std::cout << "Entered word is not an isogram !" << std::endl;
			break;

		case EWordValidity::IS_NOT_LOWERCASE:
			std::cout << "Entered word is not all lowercase !" << std::endl;
			break;

		case EWordValidity::INVALID_LENGTH:
			std::cout << "Entered word is not " << BCGame.GetHiddenWordLenght() 
			<< " letters long !" << std::endl;
			break;

		case EWordValidity::INVALID_CHARACTER:
			std::cout << "Entered word contains invalid characters !" << std::endl;
			break;
		}
	}

	return Guess;
}

bool ShouldRunTheGameAgain()
{	
	std::cout << "Do you want to play again with same word? (y/n) " << std::endl;
	FText answer;
	std::cin >> answer;

	return answer[0] == 'y' || answer[0] == 'Y';
}
/*
 * Summarize the game
 * reesults based on
 * player result - won or loss.
 */
void PrintGameSummary()
{
	if(BCGame.IsGameWon())
	{
		std::cout << "Congratulation you won the game !" << std::endl;
	}
	else
	{
		std::cout << "Better luck next time !" << std::endl;
	}	
}
