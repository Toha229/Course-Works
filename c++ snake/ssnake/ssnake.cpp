#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;

COORD fruit{};
int maxLength = 20;
int GameStartTime;
int sLength = 1;
int score = 0;
short delay = 250;
int sizex = 40, sizey = 20;
COORD* body;
char directionS = 'u';
std::string path = "records.txt";
bool exitGame = 1;

struct bestScore {
	int score;
	int time;
	void print() {
		cout << "Your Best: " << score;
		cout << "\ttime: " << time << endl;
	}
};


void gotoxy(COORD p) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
void gotoxy(int x, int y) {
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void fruitSummon() {
	bool flag = 1;
	while (flag) {
		fruit.X = rand() % (sizex - 2) + 1;
		fruit.Y = rand() % (sizey - 2) + 1;
		for (size_t i = 0; i < sLength; i++)
		{
			if (fruit.X == body[i].X && fruit.Y == body[i].Y) {
				break;
			}
			else {
				flag = 0;
			}
		}
	}
	gotoxy(fruit.X, fruit.Y);
	cout << char(4);
}

void mapPrint() {
	system("cls");
	for (size_t i = 0; i < sizex; i++)
	{
		if (i == 0) {
			cout << char(201);
		}
		else if (i == sizex - 1) {
			cout << char(187);
		}
		else
			cout << char(205);
	}
	for (size_t i = 0; i < sizey - 2; i++)
	{
		cout << "\n" << char(186);
		for (size_t i = 0; i < sizex - 2; i++)
		{
			cout << " ";
		}
		cout << char(186);

	}
	cout << endl;
	for (size_t i = 0; i < sizex; i++)
	{
		if (i == 0) {
			cout << char(200);
		}
		else if (i == sizex - 1) {
			cout << char(188);
		}
		else
			cout << char(205);
	}
	fruitSummon();
}


void gameInterface() {
	int timer = time(0) - GameStartTime;
	cout << "score = " << score << "\tplay time = " << timer << endl;

}

void startGame() {
	body = new COORD[maxLength];
	sLength = 5;
	delay = 250;
	score = 0;
	directionS = 'u';
	GameStartTime = time(0);
	for (size_t i = 0; i < maxLength; i++)
	{
		if (i <= sLength) {
			body[i].X = sizex / 2;
			body[i].Y = sizey / 2 + i;
		}
		else body[i] = { -1, -1 };
	}
	mapPrint();
	for (size_t i = 0; i < sLength; i++)
	{
		gotoxy(body[i]);
		if (i == 0) {
			cout << "0";
		}
		else {
			cout << "o";
		}
	}
	gotoxy({ 0, 21 });
}

void printBest() {
	system("cls");
	bestScore best;

	ifstream file;
	file.open(path);
	if (file.is_open()) {
		file.read((char*)&best, sizeof(best));
		best.print();
	}
	else {
		cout << "You haven't scores:(";
	}
	file.close();
	_getch();
	
}

void menuPrint() {
	system("cls");
	system("color 07");
	cout << "\tStart Game\n";
	cout << "\tYour Score\n";
	cout << "\tExit\n";
	gotoxy(0, 5);
}

void menu() {
	int selected = 0;
	gotoxy(1, 0);
	cout << ">";
	gotoxy(0, 5);
	while (true) {
		switch (_getch()) {
		case 'W': case 'w': case 72: {
			if (selected != 0) {
				gotoxy(1, selected);
				cout << " ";
				selected--;

			}
			break;
		}
		case 's': case 'S': case 80: {
			if (selected < 3) {
				gotoxy(1, selected);
				cout << " ";
				selected++;

			}
			break;
		}
		case 13: {
			switch (selected) {
			case 0: {
				startGame();
				return;
			}
			case 1: {
				printBest();
				menuPrint();
				break;
			}
			case 2: {
				exitGame = 0;
				return;
			}
			}
			break;
		}
		}
		gotoxy(1, selected);
		cout << ">";
		gotoxy(0, 5);
	}
}

void gameOver() {
	system("color 0c");
	cout << "\t GAME OVER\n";
	bestScore best{ 0, 0 };
	ifstream file;
	file.open(path);
	if (file.is_open()) {
		file.read((char*)&best, sizeof(best));
	}
	if (score > best.score) {
		best.score = score;
		best.time = time(0) - GameStartTime;
		cout << "\tNew Best!\n";
	}
	else {
		best.print();
	}
	file.close();
	ofstream File;
	File.open(path);
	if (File.is_open()) {
		File.write((char*)&best, sizeof(best));
	}
	else cout << "Error! File not found!\n";
	File.close();

	_getch();
	delete[] body;
	menuPrint();
	menu();
}



void GameLogic() {
	bool flag = 1;
	for (size_t i = 4; i <= sLength; i++)
	{
		COORD tmp = body[i];
		COORD tmph = body[0];
		if (body[0].Y == body[i].Y && body[0].X == body[i].X)
			flag = 0;
	}
	if (body[0].Y != 0 && body[0].X != 0 && body[0].Y != sizey - 1 && body[0].X != sizex - 1 && flag) {
		if (fruit.X == body[0].X && fruit.Y == body[0].Y) {
			if (sLength <= maxLength) {
				sLength++;
			}
			score++;
			fruitSummon();
			if (delay > 50) {
				delay -= 10;
			}
		}
	}
	else {
		gameOver();
	}
}

void move() {
	for (size_t i = sLength; i > 0; i--)
	{
		body[i] = body[i - 1];
	}

	if (directionS == 'u')
		body[0].Y -= 1;
	if (directionS == 'd')
		body[0].Y += 1;
	if (directionS == 'l')
		body[0].X -= 1;
	if (directionS == 'r')
		body[0].X += 1;
	GameLogic();


	gotoxy(body[sLength]);
	cout << " ";
	gotoxy(body[0]);
	cout << "0";
	gotoxy(body[1]);
	cout << "o";
	gotoxy({ 0, 21 });
}

int main()
{
	srand(time(0));
	menuPrint();
	menu();
	while (exitGame) {
		if (_kbhit()) {
			switch (_getch()) {
			case 'W': case 'w': case 72: {
				if (
					directionS != 'd') {

					directionS = 'u';
				}
				break;
			}
			case 's': case 'S': case 80: {
				if (
					directionS != 'u') {

					directionS = 'd';
				}
				break;
			}
			case 'D': case 'd': case 77: {
				if (
					directionS != 'l') {

					directionS = 'r';
				}
				break;
			}
			case 'A': case 'a': case 75: {
				if (
					directionS != 'r') {

					directionS = 'l';
				}
				break;
			}
			}
		}
		gameInterface();
		move();
		Sleep(delay);
	}
}