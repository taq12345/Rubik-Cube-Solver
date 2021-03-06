// Rubik's Cube.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <stack>
#include <string>
#include <fstream>

using namespace std;

#define BLUE			1
#define GREEN			2
#define RED				4
#define WHITE			15
#define YELLOW			14
#define BROWN			6

#define U				0
#define L				1
#define F				2
#define R				3
#define B				4
#define D				5

struct node {
	char *** cube;
	int level;
	int moveNum;
	node * parent;
	int score;
};

vector<node *> frontier;
vector<node *> explored;
vector<node *> scores;

void gotorc(char cstr, int r, int c, int color)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = c;
	dwCursorPosition.Y = r;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
	SetConsoleTextAttribute(hConsoleOutput, color);
	cout << cstr;
	SetConsoleTextAttribute(hConsoleOutput, WHITE);
}

char*** createCube()
{
	char colors[] = { 'W', 'G', 'R', 'B', 'O','Y' };
	//char cube[6][3][3];
	char *** cube = new char**[6];
	for (int i = 0; i < 6; i++)
	{
		cube[i] = new char*[3];
		for (int j = 0; j < 3; j++)
		{
			cube[i][j] = new char[3];
		}
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cube[i][j][k] = colors[i];
			}
		}
	}

	return cube;

}

void displayCube(char*** cube)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	for (int i = 0; i < 3; i++)
	{
		cout << "       ";
		for (int j = 0; j < 3; j++)
		{
			if (cube[0][i][j] == 'G')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			}
			else if (cube[0][i][j] == 'R')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
			}
			else if (cube[0][i][j] == 'B')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
			}
			else if (cube[0][i][j] == 'O')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BROWN);
			}
			else if (cube[0][i][j] == 'Y')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
			}
			else if (cube[0][i][j] == 'W')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			cout << cube[0][i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j < 5; j++)
		{

			for (int k = 0; k < 3; k++)
			{
				if (cube[j][i][k] == 'G')
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				}
				else if (cube[j][i][k] == 'R')
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
				}
				else if (cube[j][i][k] == 'B')
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
				}
				else if (cube[j][i][k] == 'O')
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BROWN);
				}
				else if (cube[j][i][k] == 'Y')
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
				}
				else if (cube[j][i][k] == 'W')
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				}
				cout << cube[j][i][k] << " ";
			}
			cout << " ";
		}
		cout << endl;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	for (int i = 0; i < 3; i++)
	{
		cout << "       ";
		for (int j = 0; j < 3; j++)
		{
			if (cube[5][i][j] == 'G')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			}
			else if (cube[5][i][j] == 'R')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
			}
			else if (cube[5][i][j] == 'B')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
			}
			else if (cube[5][i][j] == 'O')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BROWN);
			}
			else if (cube[5][i][j] == 'W')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			else if (cube[5][i][j] == 'Y')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
			}
			cout << cube[5][i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;


	//for (int i = 0; i < 6; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		for (int k = 0; k < 3; k++)
	//		{
	//			if (i == 0)
	//			{
	//				cout << "    ";
	//				cout << cube[i][j][k];
	//			}
	//			else if (i == 5)
	//			{
	//				cout << "    ";
	//				cout << cube[i][j][k];
	//			}
	//			else
	//			{
	//				cout << 
	//			}
	//			//gotorc(cube[i][j][k], j, k, 4);
	//			//cout << cube[i][j][k] << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
}

void moveFCW(char *** cube)
{
	char arr[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arr[j][2 - i] = cube[F][i][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cube[F][i][j] = arr[i][j];
		}
	}

	char tempU[3] = { cube[U][2][0], cube[U][2][1], cube[U][2][2] };
	char tempR[3] = { cube[R][0][0], cube[R][1][0], cube[R][2][0] };
	char tempD[3] = { cube[D][0][0], cube[D][0][1], cube[D][0][2] };
	char tempL[3] = { cube[L][0][2], cube[L][1][2], cube[L][2][2] };

	for (int i = 0; i < 3; i++)
	{
		cube[R][i][0] = tempU[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[D][0][2 - i] = tempR[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[L][i][2] = tempD[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[U][2][2 - i] = tempL[i];
	}
}
void moveLCW(char *** cube)
{
	char arr[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arr[j][2 - i] = cube[L][i][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cube[L][i][j] = arr[i][j];
		}
	}

	char tempU[3] = { cube[U][0][0], cube[U][1][0], cube[U][2][0] };
	char tempB[3] = { cube[B][0][2], cube[B][1][2], cube[B][2][2] };
	//char tempB[3] = { cube[B][0][0], cube[B][1][0], cube[B][2][0] };
	//char tempD[3] = { cube[D][0][0], cube[D][1][0], cube[D][2][0] };
	char tempD[3] = { cube[D][2][0], cube[D][1][0], cube[D][0][0] };
	char tempF[3] = { cube[F][0][0], cube[F][1][0], cube[F][2][0] };

	for (int i = 0; i < 3; i++)
	{
		cube[F][i][0] = tempU[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[D][2 - i][0] = tempF[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[B][i][2] = tempD[i];
		//cube[B][i][0] = tempD[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[U][i][0] = tempB[i];
	}
}
void moveRCW(char *** cube)
{
	char arr[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arr[j][2 - i] = cube[R][i][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cube[R][i][j] = arr[i][j];
		}
	}

	char tempU[3] = { cube[U][2][2], cube[U][1][2], cube[U][0][2] };
	char tempB[3] = { cube[B][0][0], cube[B][1][0], cube[B][2][0] };
	char tempD[3] = { cube[D][0][2], cube[D][1][2], cube[D][2][2] };
	char tempF[3] = { cube[F][0][2], cube[F][1][2], cube[F][2][2] };

	for (int i = 0; i < 3; i++)
	{
		cube[F][i][2] = tempD[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[D][i][2] = tempB[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[B][i][0] = tempU[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[U][2 - i][2] = tempF[i];
	}
}
void moveUCW(char *** cube)
{
	char arr[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arr[j][2 - i] = cube[U][i][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cube[U][i][j] = arr[i][j];
		}
	}

	char tempB[3] = { cube[B][0][0], cube[B][0][1], cube[B][0][2] };
	char tempF[3] = { cube[F][0][0], cube[F][0][1], cube[F][0][2] };
	char tempL[3] = { cube[L][0][0], cube[L][0][1], cube[L][0][2] };
	char tempR[3] = { cube[R][0][0], cube[R][0][1], cube[R][0][2] };

	for (int i = 0; i < 3; i++)
	{
		cube[R][0][i] = tempB[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[F][0][i] = tempR[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[B][0][i] = tempL[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[L][0][i] = tempF[i];
	}
}
void moveDCW(char *** cube)
{
	char arr[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arr[j][2 - i] = cube[D][i][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cube[D][i][j] = arr[i][j];
		}
	}

	char tempB[3] = { cube[B][2][0], cube[B][2][1], cube[B][2][2] };
	char tempF[3] = { cube[F][2][0], cube[F][2][1], cube[F][2][2] };
	char tempL[3] = { cube[L][2][0], cube[L][2][1], cube[L][2][2] };
	char tempR[3] = { cube[R][2][0], cube[R][2][1], cube[R][2][2] };

	for (int i = 0; i < 3; i++)
	{
		cube[F][2][i] = tempL[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[R][2][i] = tempF[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[B][2][i] = tempR[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[L][2][i] = tempB[i];
	}
}
void moveBCW(char *** cube)
{
	char arr[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arr[j][2 - i] = cube[B][i][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cube[B][i][j] = arr[i][j];
		}
	}

	char tempD[3] = { cube[D][2][0], cube[D][2][1], cube[D][2][2] };
	char tempU[3] = { cube[U][0][0], cube[U][0][1], cube[U][0][2] };
	char tempL[3] = { cube[L][0][0], cube[L][1][0], cube[L][2][0] };
	char tempR[3] = { cube[R][0][2], cube[R][1][2], cube[R][2][2] };

	for (int i = 0; i < 3; i++)
	{
		cube[R][i][2] = tempD[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[U][0][i] = tempR[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[L][i][0] = tempU[i];
	}
	for (int i = 0; i < 3; i++)
	{
		cube[D][2][i] = tempL[i];
	}
}

void moveFCCW(char *** cube)
{
	for (int i = 0; i < 3; i++)
	{
		moveFCW(cube);
	}
}
void moveLCCW(char *** cube)
{
	for (int i = 0; i < 3; i++)
	{
		moveLCW(cube);
	}
}
void moveRCCW(char *** cube)
{
	for (int i = 0; i < 3; i++)
	{
		moveRCW(cube);
	}
}
void moveUCCW(char *** cube)
{
	for (int i = 0; i < 3; i++)
	{
		moveUCW(cube);
	}
}
void moveDCCW(char *** cube)
{
	for (int i = 0; i < 3; i++)
	{
		moveDCW(cube);
	}
}
void moveBCCW(char *** cube)
{
	for (int i = 0; i < 3; i++)
	{
		moveBCW(cube);
	}
}
void move(int num, char *** cube)
{
	if (num == 0)
	{
		moveFCW(cube);
	}
	else if (num == 1)
	{
		moveLCW(cube);
	}
	else if (num == 2)
	{
		moveRCW(cube);
	}
	else if (num == 3)
	{
		moveUCW(cube);
	}
	else if (num == 4)
	{
		moveDCW(cube);
	}
	else if (num == 5)
	{
		moveBCW(cube);
	}
	else if (num == 6)
	{
		moveFCCW(cube);
	}
	else if (num == 7)
	{
		moveLCCW(cube);
	}
	else if (num == 8)
	{
		moveRCCW(cube);
	}
	else if (num == 9)
	{
		moveUCCW(cube);
	}
	else if (num == 10)
	{
		moveDCCW(cube);
	}
	else if (num == 11)
	{
		moveBCCW(cube);
	}
	else
	{
		return;
	}
}
string moveName(int num)
{
	if (num == 0)
	{
		return "FCW";
	}
	else if (num == 1)
	{
		return "LCW";
	}
	else if (num == 2)
	{
		return "RCW";
	}
	else if (num == 3)
	{
		return "UCW";
	}
	else if (num == 4)
	{
		return "DCW";
	}
	else if (num == 5)
	{
		return "BCW";
	}
	else if (num == 6)
	{
		return "FCCW";
	}
	else if (num == 7)
	{
		return "LCCW";
	}
	else if (num == 8)
	{
		return "RCCW";
	}
	else if (num == 9)
	{
		return "UCCW";
	}
	else if (num == 10)
	{
		return "DCCW";
	}
	else if (num == 11)
	{
		return "BCCW";
	}
	return "Unknown";
}

void scrambleCube(char***cube)
{
	srand(time(NULL));
	int random = rand();
	for (int i = 0; i < random; i++)
	{
		int rand2 = rand() % 7;
		if (rand2 == 0)
		{
			moveFCW(cube);
		}
		else if (rand2 == 1)
		{
			moveLCW(cube);
		}
		else if (rand2 == 2)
		{
			moveRCW(cube);
		}
		else if (rand2 == 3)
		{
			moveUCW(cube);
		}
		else if (rand2 == 4)
		{
			moveDCW(cube);
		}
		else
		{
			moveBCW(cube);
		}
	}

}
bool isGoal(char *** cube)
{
	for (int i = 0; i < 6; i++)
	{
		char check = cube[i][0][0];
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (cube[i][j][k] != check)
				{
					return false;
				}
			}
		}
	}
	return true;
}
bool isEqual(char *** cube1, char *** cube2)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (cube1[i][j][k] != cube2[i][j][k])
				{
					return false;
				}
			}
		}
	}
	return true;
}
bool existsInExplored(char *** cube)
{
	for (int i = 0; i < explored.size(); i++)
	{
		if (isEqual(explored[i]->cube, cube) == true)
		{
			return true;
		}
	}
	return false;
}
bool existsInFrontier(char *** cube)
{
	for (int i = 0; i < frontier.size(); i++)
	{
		if (isEqual(frontier[i]->cube, cube) == true)
		{
			return true;
		}
	}
	return false;
}
char *** copyCube(char *** cube)
{
	char *** tempCube = createCube();
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				tempCube[i][j][k] = cube[i][j][k];
			}
		}
	}
	return tempCube;
}
void displayMoves(node solved)
{
	while (solved.parent != nullptr)
	{
		cout << moveName(solved.moveNum) << endl;
		solved = *(solved.parent);
	}
}
int heuristic(char *** cube)
{
	char *** solved = createCube();
	int score = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (solved[i][j][k] == cube[i][j][k])
				{
					score++;
				}
			}
		}
	}
	return score;
}

int maximum(vector<node*> vect)
{
	int max = -1;
	int index = -1;
	for (int i = 0; i < vect.size(); i++)
	{
		if (vect[i]->score > max)
		{
			max = vect[i]->score;
			index = i;
		}
	}
	return index;
}
char *** inputToCube(string file)
{
	char c = '[';
	char *** cube = createCube();
	ifstream fin(file);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			fin >> c;
			while (c < 65 || c > 90)
			{
				fin >> c;
			}
			cube[0][i][j] = c;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j < 5; j++)
		{

			for (int k = 0; k < 3; k++)
			{
				fin >> c;
				while (c < 65 || c > 90)
				{
					fin >> c;
				}
				cube[j][i][k] = c;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			fin >> c;
			while (c < 65 || c > 90)
			{
				fin >> c;
			}
			cube[5][i][j] = c;
		}
	}

	return cube;
}

char *** idfsH(char *** cube)
{
	cout << "IDFS H" << endl;
	for (int bound = 0; bound < 20; bound++)
	{
		cout << bound << " BOUND " << endl; // 
											//Sleep(3000);
		int maxIndex;
		bool flag = 0;
		node * initial = new node;
		initial->level = 0;
		initial->cube = cube;
		initial->moveNum = -1;
		initial->parent = nullptr;
		initial->score = heuristic(initial->cube);
		//int childAdded = 0;
		frontier.push_back(initial);
		//explored.push_back(initial);
		while (frontier.size() != 0)
		{
			explored.push_back(frontier.back()); ///////////
												 //cout << "NODES EXPLORED: " << explored.size() << endl;


			if (isGoal(explored.back()->cube) == true)
			{
				//cout << "FOUND ! ! !  AT " << bound << " BOUND" << endl;	//
				//cout << moveName(frontier.back()->moveNum) << "  " << frontier[maxIndex]->score << endl; //
				displayCube(explored.back()->cube); //
				displayMoves(*explored.back());
				//cout << "NODES EXPLORED: " << explored.size() << endl;
				return explored.back()->cube;
			}

			//cout << moveName(frontier.back()->moveNum) << endl;
			//cout << "Move score: " << frontier[maxIndex]->score << endl; //
			//cout << "Frontier size: " << frontier.size() << endl;
			//displayCube(frontier.back()->cube); //

			frontier.pop_back();
			//frontier.pop_back();
			for (int i = 11; i >= 0; i--)
			{
				node * child = new node;
				child->cube = copyCube(explored.back()->cube);
				child->level = explored.back()->level + 1;
				child->parent = explored.back();
				if (child->level > bound)
				{
					//explored.clear();
					//bound++;
					flag = 1;
					break;
				}
				move(i, child->cube);
				if (!existsInExplored(child->cube) && !existsInFrontier(child->cube))
				{
					child->score = heuristic(child->cube);
					child->moveNum = i;
					if (child->score >= 0) // CHANGE TO 10 or less
					{
						scores.push_back(child);
					}
					/*if (child->score > 15)
					{
					frontier.push_back(child);
					}*/
				}
			}
			maxIndex = maximum(scores);
			for (int i = 0; i < scores.size(); i++)
			{
				if (i == maxIndex)
				{
				}
				else
				{
					frontier.push_back(scores[i]);
				}
			}
			if (flag != 1 && scores.size() >0)
			{
				frontier.push_back(scores[maxIndex]);
			}
			if (scores.size() > 0)
			{
				cout << scores.size() << endl;
			}
			scores.clear();
		}
		for (int i = 0; i < explored.size(); i++)
		{
			delete explored[i];
		}
		for (int i = 0; i < frontier.size(); i++)
		{
			delete frontier[i];
		}
		explored.clear();
	}
	return nullptr;
}
char *** idfs(char *** cube)
{
	cout << "IDFS " << endl;
	for (int bound = 0; bound < 20; bound++)
	{
		cout << bound << " BOUND " << endl; // 
											//Sleep(3000);

		node * initial = new node;
		initial->level = 0;
		initial->cube = cube;
		initial->moveNum = -1;
		initial->parent = nullptr;
		//initial->score = heuristic(initial->cube);
		int childAdded = 0;
		int j = 0;
		bool flag = 0;
		frontier.push_back(initial);
		//explored.push_back(initial);
		while (frontier.size() != 0)
		{
			//int maxIndex = maximum(frontier);
			explored.push_back(frontier.back()); ///////////
												 //cout << "NODES EXPLORED: " << explored.size() << endl;

			if (isGoal(explored.back()->cube) == true)
			{
				//cout << "FOUND ! ! !  AT " << bound << " BOUND" << endl;	//
				//cout << moveName(frontier.back()->moveNum) << "  " << frontier[maxIndex]->score << endl; //
				displayCube(explored.back()->cube); //
				displayMoves(*explored.back());
				//cout << "NODES EXPLORED: " << explored.size() << endl;
				return explored.back()->cube;
			}

			//cout << moveName(frontier.back()->moveNum) << endl;
			//cout << "Move score: " << frontier[maxIndex]->score << endl; //
			//cout << "Frontier size: " << frontier.size() << endl;
			//displayCube(frontier.back()->cube); //

			frontier.pop_back();
			//frontier.pop_back();
			for (int i = 11; i >= 0; i--)
			{
				node * child = new node;
				child->cube = copyCube(explored.back()->cube);
				child->level = explored.back()->level + 1;
				child->parent = explored.back();
				if (child->level > bound)
				{
					//explored.clear();
					//bound++;
					flag = 1;
					break;
				}
				move(i, child->cube);
				if (!existsInExplored(child->cube) && !existsInFrontier(child->cube))
				{
					//child->score = heuristic(child->cube);
					child->moveNum = i;
					frontier.push_back(child);
					childAdded++;
					/*if (child->score > 15)
					{
					frontier.push_back(child);
					}*/
				}
			}

			if (childAdded > 0 && flag != 1)
			{
				j++;
				cout << childAdded / (double)j << endl;
			}
			//childAdded = 0;

		}
		for (int i = 0; i < explored.size(); i++)
		{
			delete explored[i];
		}
		for (int i = 0; i < frontier.size(); i++)
		{
			delete frontier[i];
		}
		explored.clear();
	}
	return nullptr;
}
char *** greedy(char *** cube)
{
	cout << "GREEDY " << endl;
	node * initial = new node;
	initial->level = 0;
	initial->cube = cube;
	initial->moveNum = -1;
	initial->parent = nullptr;
	initial->score = heuristic(initial->cube);

	frontier.push_back(initial);
	int childAdded = 0;
	int j = 0;
	bool flag = 0;
	//explored.push_back(initial);
	while (frontier.size() != 0)
	{
		int maxIndex = maximum(frontier);
		explored.push_back(frontier[maxIndex]); ///////////

		if (isGoal(explored.back()->cube) == true)
		{
			cout << moveName(explored.back()->moveNum) << "  " << frontier[maxIndex]->score << endl; //
			displayCube(explored.back()->cube); //
			displayMoves(*explored.back());
			//cout << "NODES EXPLORED: " << explored.size() << endl;
			return frontier.back()->cube;
		}

		//cout << moveName(frontier.back()->moveNum) << endl;
		//cout << "Move score: " << frontier[maxIndex]->score << endl; //
		//cout << "Frontier size: " << frontier.size() << endl;
		//displayCube(frontier.back()->cube); //

		frontier.erase(frontier.begin() + maxIndex);
		//frontier.pop_back();
		for (int i = 11; i >= 0; i--)
		{
			node * child = new node;
			child->cube = copyCube(explored.back()->cube);
			child->level = explored.back()->level + 1;
			child->parent = explored.back();
			move(i, child->cube);
			if (!existsInExplored(child->cube) && !existsInFrontier(child->cube))
			{
				child->score = heuristic(child->cube);
				child->moveNum = i;
				//scores.push_back(child);
				if (child->score >= child->parent->score)
				{
					frontier.push_back(child);
					childAdded++;
				}
			}
		}
		j++;
		if (childAdded > 0)
		{
			cout << childAdded / (double)j << endl;
		}
		//childAdded = 0;

	}
	return nullptr;
}
char *** greedyLimit(char *** cube)
{
	cout << "GREEDY LIMIT" << endl;
	for (int bound = 0; bound < 1000; bound++)
	{
		cout << bound << " BOUND " << endl; // 
											//Sleep(3000);

		node * initial = new node;
		initial->level = 0;
		initial->cube = cube;
		initial->moveNum = -1;
		initial->parent = nullptr;
		initial->score = heuristic(initial->cube);

		frontier.push_back(initial);
		//explored.push_back(initial);
		while (frontier.size() != 0)
		{
			int maxIndex = maximum(frontier);
			explored.push_back(frontier[maxIndex]); ///////////
													//cout << "NODES EXPLORED: " << explored.size() << endl;


			if (isGoal(explored.back()->cube) == true)
			{
				//cout << "FOUND ! ! !  AT " << bound << " BOUND" << endl;	//
				//cout << moveName(frontier.back()->moveNum) << "  " << frontier[maxIndex]->score << endl; //
				displayCube(explored.back()->cube); //
				displayMoves(*explored.back());
				cout << "NODES EXPLORED: " << explored.size() << endl;
				return explored.back()->cube;
			}

			//cout << moveName(frontier.back()->moveNum) << endl;
			//cout << "Move score: " << frontier[maxIndex]->score << endl; //
			//cout << "Frontier size: " << frontier.size() << endl;
			//displayCube(frontier.back()->cube); //

			frontier.erase(frontier.begin() + maxIndex);
			//frontier.pop_back();
			for (int i = 11; i >= 0; i--)
			{
				node * child = new node;
				child->cube = copyCube(explored.back()->cube);
				child->level = explored.back()->level + 1;
				child->parent = explored.back();
				if (child->level > bound)
				{
					//explored.clear();
					//bound++;
					break;
				}
				move(i, child->cube);
				if (!existsInExplored(child->cube) && !existsInFrontier(child->cube))
				{
					child->score = heuristic(child->cube);
					child->moveNum = i;
					if (child->score >= child->parent->score) // CHANGE TO 10 or less
					{
						frontier.push_back(child);
					}
					/*if (child->score > 15)
					{
					frontier.push_back(child);
					}*/
				}
			}

		}
		for (int i = 0; i < explored.size(); i++)
		{
			delete explored[i];
		}
		for (int i = 0; i < frontier.size(); i++)
		{
			delete frontier[i];
		}
		explored.clear();
	}
	return nullptr;
}

int main()
{
	clock_t startTime = clock();
	//char *** cube = createCube();
	char *** cube = inputToCube("input.txt");
	moveFCCW(cube);
	//scrambleCube(cube);
	displayCube(cube);
	//greedy(cube);
	//greedyLimit(cube);
	//idfs(cube);
	//idfsH(cube);

	//moveFCW(cube1);
	moveFCCW(cube);
	//cout << isEqual(cube1, cube2) << endl;
	displayCube(cube);
	moveFCW(cube);
	displayCube(cube);
	cout << double(clock() - startTime) / (double)CLOCKS_PER_SEC << " seconds." << endl;
}

