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
int32 SubmitHiddenWordLength();

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
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;

	std::cout << "Can you guess " << BCGame.GetHiddenWordLenght();
	std::cout << " letter isogram I'am thinking of ?" << std::endl;
}

void PlayGame()
{
	// Starting a new game
	BCGame.Reset();

	// Sets the desired game difficulty
	int32 HiddenWordLength = SubmitHiddenWordLength();	

	int32 MaxTries = BCGame.GetMaxNumberOfTries();	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTries() <= MaxTries)
	{
		// Ask for guess
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
		std::cout << "\nTries: " << BCGame.GetCurrentTries() << " out of " 
		<< BCGame.GetMaxNumberOfTries() <<
			". Enter the guess: \n=>";

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
	std::cout << "Do you want to play again with same word? (y/n) \n=>";
	FText answer;
	std::getline(std::cin, answer);

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
		std::cout << "\n\nCongratulation you won the game !\n\n";
	}
	else
	{
		std::cout << "\n\nBetter luck next time !\n\n" << std::endl;
	}	
}

int32 SubmitHiddenWordLength()
{
	int32 WordLength = 0;	
	do
	{
		std::cout << "Please enter desired hidden word length (3, 4, 5 or 6)\n=>";
		std::cin >> WordLength;

		// Remove return character
		FString ReturnCharacter = "";
		std::getline(std::cin, ReturnCharacter);	
	
	} while(!BCGame.SubmitHiddenWordLenght(WordLength));
	
	return WordLength;
}
