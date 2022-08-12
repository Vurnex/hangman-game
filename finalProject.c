#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define charSIZE 100

void gameFunction(char*, FILE *inFile);
void resultsFile(FILE *inFile);

void cls() {

	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
		return 0;
}

int main()
{
	cls();
	printf("\nProgram that operates as a hangman game. You will enter a nickname to be stored alongside your score in the scoreboard.");
	printf("\nLine 117 is where the game master can enter or edit the words to be randomly chosen in the game.\n");

	int menuOption;
	char nickName[charSIZE];
	FILE *inFile;
	char welcomeMsg[] = "\nThank you for playing the Hangman Game!   \n";
	char *msgPtr;

	msgPtr = welcomeMsg;

	printf("\n1-- Begin Game\n");
	printf("\n2-- View Scores\n");
	printf("\n3-- Exit Program\n\n: ");
	scanf("%d", &menuOption);

	if (menuOption == 1)
	{
		while (getchar() != '\n')
		{
			printf("\nYou must press enter in order continue.\n");
			getchar();
		}			
		
		cls();

		for (int i = 0; i < strlen(welcomeMsg); i++)
		{
			printf("%c", *(msgPtr + i));
		}
		
		printf("\nEnter a nickname with no spaces: ");
		fgets(nickName, charSIZE, stdin);

		while ((*nickName == ' ') || (*nickName == '\t') || (*nickName == '\n'))
		{
			printf("\nYou must enter a name with no spaces.\n");
			printf("\nEnter a nickname: ");
			fgets(nickName, charSIZE, stdin);
		}

		for(int i = 0, j = 0; i < strlen(nickName); i++)
		{
			nickName[i-j] = nickName[i];
			if(nickName[i] == ' ')
			{
				j++;
			}
		}

		printf("\nYour nickname is: %s", nickName);

		printf("\nPress enter or return to continue... ");

		while (getchar() != '\n')
		{
			printf("\nYou must press enter in order continue.\n");
			getchar();
		}			

		cls();	

		gameFunction(nickName, inFile);

	}
	else if (menuOption == 2)
	{
		cls();
		resultsFile(inFile);
	}
	else if (menuOption == 3)
	{
		exit(1);
	}
	else if (menuOption != 1 || menuOption != 2 || menuOption != 3)
	{
		printf("\nPlease enter a number only between 1 - 3\n");			
		printf("\nPress enter or return to continue...\n");
		getchar();
		while (getchar() != '\n')
		{
			getchar();
		}			
		cls();
		main();
	}

	return 0;
	
}

void gameFunction(char *nickName, FILE *inFile)
{
	srand(time(NULL));

	//here the game master can enter 6 words to be randomly chosen for the game
	char guessWords[][16] = { 	"break",
								"void",
								"struct",
								"continue",
								"union",
								"quarantine"
	};
	
	printf("\n*For testing* The word bank to be randomly chosen from is:\n");

	for (int i = 0; i < strlen(guessWords[i]); i++)	//for testing the array, can be removed
	{
		printf("\n%s ", guessWords[i]);
	}

	printf("\n\nPress enter or return to begin the game... ");

	while (getchar() != '\n') //for pausing the loops
	{
		printf("\nYou must press enter in order continue.\n");
		getchar();
	}			

	cls();	
	
	int randIndex = rand() % 6;

	int numbLives = 5;
	int totalPoints = 0;
	int wrongGuess = 0;
	int letterAccu = 0;

	int wordLength = strlen(guessWords[randIndex]);

	int guessedLetter[16] = {0, 0, 0, 0, 0, 0, 0, 0};

	int userQuit = 0;

	int loopIndex = 0;

	char guessLetters[16];
	char letterGuessed;

	while (totalPoints < wordLength)
	{

		if (totalPoints < 0)
		{
			totalPoints = 0;
		}

		//for testing the program, can be commented out/removed
		printf("\nChosen Word: %s | Index Number: %d | Word Length: %d\n", guessWords[randIndex], randIndex, wordLength);
		printf("\nNote: The above is for testing the game. It can be removed or commented out on line 170 for a serious game.\n");
		printf("\nIf you would like to end the game early, enter quit.");

		printf("\n------------------------------------------------------\n");
		printf("\n|New Turn|\n\nCurrent Player: %s\nHangman Word: ", nickName);
		for (loopIndex = 0; loopIndex < wordLength; loopIndex++)
		{
			if(guessedLetter[loopIndex] == 1)
			{
				printf("%c", guessWords[randIndex][loopIndex]);
			}
			else
			{
				printf("-");		
			}
			if (letterGuessed == guessWords[randIndex][loopIndex])
			{
				guessedLetter[loopIndex] = 1;
			}
		}

		printf("\n");			

		printf("\nLives left: %d\n", numbLives);
		printf("\nTotal Points: %d\n", totalPoints);
		printf("\nCurrent letter number: %d\n", letterAccu);
		printf("\nEnter a letter to be guessed: ");
		fgets(guessLetters, 16, stdin);

		if (strncmp(guessLetters, "quit", 4) == 0)
		{
			userQuit = 1;
			break;
		}

		letterGuessed = guessLetters[0];

		printf("\nLetter entered: %c", letterGuessed);

		wrongGuess = totalPoints;

		for (loopIndex = 0; loopIndex < wordLength; loopIndex++)
		{
			if(guessedLetter[loopIndex] == 1)
			{
				continue;
			}
			if (letterGuessed == guessWords[randIndex][loopIndex])
			{
				guessedLetter[loopIndex] = 1;
				totalPoints++;
				letterAccu++;


			}
		}

		if (wrongGuess == totalPoints)
		{
			numbLives--;
			totalPoints--;
			printf("\n-------------------------------\n");	
			printf("\nSorry, wrong guess!\n");
			printf("\n-------------------------------\n");	
			printf("\nPress enter or return to continue... ");
			getchar();
			cls();

			if (numbLives == 0)
			{
				break;
			}

		}
		else
		{ 
			printf("\n-------------------------------\n");	
			printf("\nCorrect guess!\n");
			printf("\n-------------------------------\n");	
			printf("\nPress enter or return to continue... ");
			getchar();
			cls();
		}

		cls();

	if (letterAccu == wordLength)
	{
		break; 
	}
	
	}

	if (userQuit == 1)
	{
		cls();
		printf("\n-------------------------------\n");
		printf("\nYou have quit the game. The chosen word was: %s\n", guessWords[randIndex]);
		printf("\nYou scored: %d\n", totalPoints);
		printf("\n-------------------------------\n");
		printf("\nPress enter or return to return to the main menu... ");
		getchar();
		cls();
	}
	else if (numbLives == 0)
	{
		if (totalPoints < 0)
		{
			totalPoints = 0;
		}

		printf("\n---------------------------------------------------------\n");
		printf("\nSorry, you lose. The chosen word was: %s\n", guessWords[randIndex]);
		printf("\nYou scored: %d\n", totalPoints);
		printf("\n---------------------------------------------------------\n");
		printf("\nPress enter or return to return to the main menu... ");
		getchar();
		cls();
	}
	else
	{
		printf("\n---------------------------------------------------------\n");
		printf("\nCongratulations, you've won! The chosen word was: %s\n",guessWords[randIndex]);
		printf("\nYou scored: %d\n", totalPoints);
		printf("\n---------------------------------------------------------\n");
		printf("\nPress enter or return to return to the main menu... ");
		getchar();
		cls();

	}

	inFile = fopen("results.txt", "a+");
	
	fprintf(inFile, "%s\t%d\n", nickName, totalPoints);
	
	fclose(inFile);

	main();

  return;
}

struct scores
{
	char dispName[charSIZE];	
	int dispScore;

} displayScores;

void resultsFile(FILE *inFile)
{

	struct scores displayScores;

	inFile = fopen("results.txt", "r");

	if (inFile == NULL)
	{
		printf("\n---------------------------------------------------------\n");
		printf("\nNo scores to display yet!\n");
		printf("\n---------------------------------------------------------\n");
		
		printf("\nPress enter or return to return to the main menu... ");
		getchar();
		while (getchar() != '\n')
		{
			getchar();
		}
		cls();
		main();
	}
	printf("\n---------------------------------------------------------\n");
	printf("\nAll scores\n");
	printf("\n---------------------------------------------------------\n");

	while (fscanf(inFile, "%s\r%d", displayScores.dispName, &displayScores.dispScore) != EOF)
	{
		printf("\nNickname: %s | Score: %d", displayScores.dispName, displayScores.dispScore);
		printf("\n\n---------------------------------------------------------\n");
	}

	fclose(inFile);

	printf("\nPress enter or return to return to the main menu... ");
	
	getchar();
	while (getchar() != '\n')
	{
		getchar();
	}

	cls();
	main();

}
