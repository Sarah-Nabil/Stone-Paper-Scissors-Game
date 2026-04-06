#include <iostream>
#include<cstdlib>
using namespace std;
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, NoWinner = 3 };
struct StSingleRoundInfo
{
	int RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;

};
struct stGameResults
{

	int GameRounds;
	int PlayerWinTimes;
	int ComputerWinTimes;
	int DrawTimes;
	enWinner FinalWinner;
	string FinallWinnerName;

};
short RandomNumber(int From, int To)
{
	short randNumber = rand() % (To - From + 1) + From;
	return randNumber;

}
int ReadHowManyRounds()
{
	int Rounds;
	cout << "Enter how many rounds do you want to play ? ";
	cin >> Rounds;
	return Rounds;
}
enGameChoice ReadPlayerChoice()
{
	int Choice;
	cout << "\nPlease enter your choice ? [1]:Stone , [2]:Paper , [3]:Scissors ? ";
	cin >> Choice;
	return enGameChoice(Choice);
}
enGameChoice GetComputerChoice()
{
	return enGameChoice(RandomNumber(1, 3));

}

enWinner WhoWonTheRound(StSingleRoundInfo SingleRound)
{
	if (SingleRound.PlayerChoice == SingleRound.ComputerChoice)
	{
		return enWinner::NoWinner;
	}

	switch (SingleRound.PlayerChoice)
	{

	case enGameChoice::Stone:
	{
		if (SingleRound.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;

		}
		break;
	}
	case enGameChoice::Paper:
	{

		if (SingleRound.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;

		}
		break;
	}

	case enGameChoice::Scissors:
	{
		if (SingleRound.ComputerChoice == enGameChoice::Stone)
		{

			return enWinner::Player;
		}
		break;
	}

	}
	return enWinner::Player;

}
string WinnerName(enWinner Winner)
{

	string arrWinnerName[3] = { "Player","Computer","No Winner" };

	return arrWinnerName[Winner - 1];


}
string ChoiceName(enGameChoice GameChoice)
{
	string arrChoiceName[3] = { "Stone","Paper","Scissors" };

	string Choice = arrChoiceName[GameChoice - 1];
	return Choice;


}
void SetScreenColor(enWinner Winner)
{
	switch (Winner)
	{

	case enWinner::Player:
	{
		system("color 2F");
		break;
	}
	case enWinner::Computer:
	{
		system("color 4F");
		break;
	}
	case enWinner::NoWinner:
	{
		system("color 6F");
		break;
	}

	}

}
string Tabs(int NumberOfTabes)
{
	string t = "";
	for (int i = 1; i <= NumberOfTabes; i++)
	{
		t = t + "\t";
		cout << t;
	}

	return t;

}
void PrintEverySingleRound(StSingleRoundInfo SingleRound)
{
	cout << "\n-----------Round [ " << SingleRound.RoundNumber << " ] --------\n";
	cout << "\nRound Number    : " << SingleRound.RoundNumber;
	cout << "\nPlayer Choice   : " << ChoiceName(SingleRound.PlayerChoice);
	cout << "\nComputer Choice : " << ChoiceName(SingleRound.ComputerChoice);
	cout << "\nRound Winner    : " << SingleRound.WinnerName;
	cout << "\n----------------------------------\n\n";
	SetScreenColor(SingleRound.Winner);

}
enWinner FinallWinnerInGame(int PlayerWinTimes, int ComputerWinTimes)
{

	if (PlayerWinTimes > ComputerWinTimes)
	{
		return enWinner::Player;
	}
	else if (ComputerWinTimes > PlayerWinTimes)
	{
		return enWinner::Computer;
	}
	else
	{
		return enWinner::NoWinner;
	}
}
stGameResults FillGameResults(int Rounds, int PlayerWinTimes, int ComputerWinTimes, int DrawTimes)
{
	stGameResults GamResults;

	GamResults.GameRounds = Rounds;
	GamResults.PlayerWinTimes = PlayerWinTimes;
	GamResults.ComputerWinTimes = ComputerWinTimes;
	GamResults.DrawTimes = DrawTimes;
	GamResults.FinalWinner = FinallWinnerInGame(PlayerWinTimes, ComputerWinTimes);
	GamResults.FinallWinnerName = WinnerName(GamResults.FinalWinner);

	return GamResults;
}
stGameResults PlayRounds(int Rounds)
{
	StSingleRoundInfo SingleRound;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (int i = 1; i <= Rounds; i++)
	{
		cout << "\nRound [ " << i << " ] begines : ";


		SingleRound.RoundNumber = i;
		SingleRound.PlayerChoice = ReadPlayerChoice();
		SingleRound.ComputerChoice = GetComputerChoice();
		SingleRound.Winner = WhoWonTheRound(SingleRound);
		SingleRound.WinnerName = WinnerName(SingleRound.Winner);

		if (SingleRound.Winner == enWinner::Player)
		{
			PlayerWinTimes++;
		}
		else if (SingleRound.Winner == enWinner::Computer)
		{
			ComputerWinTimes++;
		}
		else
		{
			DrawTimes++;
		}

		PrintEverySingleRound(SingleRound);
	}

	return FillGameResults(Rounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);

}
void ShowGameOverScreen()
{
	cout << Tabs(2) << "---------------------------------------------\n";
	cout << Tabs(2) << "         +++ Game Over +++ \n       ";
	cout << Tabs(2) << "---------------------------------------------\n\n";

}
void ShowFinallGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "--------------------------------------\n";
	cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player Win Times   : " << GameResults.PlayerWinTimes << endl;
	cout << Tabs(2) << "Computer Win Times : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw Times         : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Finall Winner      : " << GameResults.FinallWinnerName << endl;
	cout << Tabs(2) << "---------------------------------------\n\n";
}
void ResetScreen()
{
	system("cls");
	system("color 0F");

}
void StartGame()
{
	char Answer = 'y';

	do
	{

		ResetScreen();

		int Rounds = ReadHowManyRounds();
		stGameResults GameResults = PlayRounds(Rounds);
		ShowGameOverScreen();
		ShowFinallGameResults(GameResults);





		cout << "\nDo you want to play again ? y/n ? ";
		cin >> Answer;

	} while (Answer == 'Y' || Answer == 'y');

}
int main()
{
	srand((unsigned)time(NULL));

	StartGame();
	return 0;
}








