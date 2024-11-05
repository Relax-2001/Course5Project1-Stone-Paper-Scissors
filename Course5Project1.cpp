#include <iostream>

using namespace std;


enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

struct stGameResults
{
	short HowManyRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner Winner;
	string WinnerName = "";
};

struct stRoundInfo
{
	
	short Round = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName = "";

};

int RandomNumber(int From, int To)
{

	int RandomNum = rand() % (To - From + 1) + From;

	return RandomNum;
}

void ClearScreen()
{
	system("cls");
	system("color 0F");
}

short HowManyRounds()
{

	short HowManyRounds = 1;
	
	do
	{
		cout << "How many rounds do you want to play [1 To 10] ? \n";
		cin >> HowManyRounds;

	} while (HowManyRounds < 1 || HowManyRounds > 10);

	return HowManyRounds;

}

enGameChoice ReadPlayerChoice()
{

	short Choice = 0;

	do
	{

		cout << "[1] Stone , [2] Paper , [3] Scissors \n";
		cin >> Choice;

	} while (Choice < 1 || Choice > 3);

	return (enGameChoice) Choice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice) RandomNumber(1, 3);
}

enWinner WhoWonTheRound (stRoundInfo RoundInfo)
{
	
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.Player1Choice)
	{
	
	case(enGameChoice::Stone):
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	case(enGameChoice::Paper):
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	case(enGameChoice::Scissors):
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}
	
	return enWinner::Player1;

}

string WinnerName(enWinner Winner)
{

	string ArrWinnerName[3] = {"Player1" , "Computer" , "Draw"};
	return ArrWinnerName[Winner - 1];

}

string ChoiceName(enGameChoice Choice)
{
	string ArrChoiceName[3]{"Stone" , "Paper" , "Scissors"};
	return ArrChoiceName[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case(enWinner::Player1):
		system("color 2F");
		break;
	case(enWinner::Computer):
			system("color 4F");
			cout << "\a";
			break;
	default:
		system("color 6F");
		break;
	}
}

void PrintRoundInfo(stRoundInfo RoundInfo)
{

	cout << "\n\n---- Round [" << RoundInfo.Round << "] ----\n\n";
	cout << "Player1 choice   :" << ChoiceName(RoundInfo.Player1Choice) << "\n";
	cout << "Computer choice  :" << ChoiceName(RoundInfo.ComputerChoice) << "\n";
	cout << "Winner name      :" << RoundInfo.WinnerName << "\n\n";

	SetWinnerScreenColor(RoundInfo.Winner);

}

enWinner WhoWonTheGame(stGameResults GameResults)
{
	if (GameResults.Player1WinTimes > GameResults.ComputerWinTimes)
	{
		return enWinner::Player1;
	}
	else if (GameResults.ComputerWinTimes > GameResults.Player1WinTimes)
	{
		return enWinner::Computer;
	}
	else
	{
		return enWinner::Draw;
	}
}

stGameResults FillGameResults(short HowManyRounds , short Player1WinTimes , short ComputerWinTimes , short DrawTimes)
{
	stGameResults GameResults;
	GameResults.HowManyRounds = HowManyRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.Winner = WhoWonTheGame(GameResults);
	GameResults.WinnerName = WinnerName(GameResults.Winner);

	return GameResults;

}

string Tabs(short HowManyTabs)
{
	string T = "";

	for (int i = 1 ; i <= HowManyTabs ; i++)
	{
		T += "\t";
	}
	return T;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "________________________\n";
	cout << Tabs(2) << "    ++++GameOver++++    \n";
	cout << Tabs(2) << "________________________\n";
}

void ShowGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "      Rounds["<<GameResults.HowManyRounds<<"]        \n\n";
	cout << Tabs(2) << "Player 1Win Times    : " << GameResults.Player1WinTimes << "\n";
	cout << Tabs(2) << "Computer win times   : " << GameResults.ComputerWinTimes << "\n";
	cout << Tabs(2) << "Draw times           : " << GameResults.DrawTimes << "\n";
	cout << Tabs(2) << "Winner name          : " << GameResults.WinnerName << "\n\n";

	SetWinnerScreenColor(GameResults.Winner);

}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;

	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short Round = 1 ; Round <= HowManyRounds ; Round++)
	{

		RoundInfo.Round = Round;
		RoundInfo.Player1Choice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		// increase Win/Draw Counters
		if (RoundInfo.Winner == enWinner::Player1)
		{
			Player1WinTimes++;
		}
		else if (RoundInfo.Winner == enWinner::Computer)
		{
			ComputerWinTimes++;
		}
		else
		{
			DrawTimes++;
		}

		PrintRoundInfo(RoundInfo);

	}

	return FillGameResults( HowManyRounds , Player1WinTimes , ComputerWinTimes , DrawTimes);

}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ClearScreen();
		stGameResults GameResults = PlayGame(HowManyRounds());
		ShowGameOverScreen();
		ShowGameResults(GameResults);

		cout << "Do you want to play again [Y] , [N] ? \n";
		cin >> PlayAgain;


	} while (PlayAgain == 'Y' || PlayAgain == 'y');
	
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

}

