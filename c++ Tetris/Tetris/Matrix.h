#pragma once
#include "Shape.h"

struct BestScores {
	int scores;
	int collectedRows;
	int time;
};

class Matrix
{
	friend class Shape;
private:
	BestScores score = { 0, 0 };
	BestScores bscore = { 0, 0 };
	int xsize = 20;
	int ysize = 25;
	int** matrix = nullptr;
	Shape shape;
	int startTime = 0;
	int matrixColor = 136;
	bool draw = false;
	int sleep = 150;
public:
	Matrix() = default;
	bool Draw();
	void collectRow();
	bool gameOver();
	void printOverlay();
	void save(const string& path = "saves/stat.dat");
	void read(const string& path = "saves/stat.dat");
};

bool Matrix::Draw()
{
	HANDLE Con = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!draw)
	{
		if (matrix != nullptr)
			delete[] matrix;
		matrix = new int* [xsize - 2];
		for (size_t i = 0; i < xsize - 2; i++)
		{
			matrix[i] = new int[ysize - 2]{ 0 };
		}
		startTime = time(0);
		draw = true;
		system("cls");
		for (size_t i = 0; i < ysize; i++)
		{
			if (i == 0 || i == ysize - 1) {
				SetConsoleTextAttribute(Con, matrixColor);
				for (size_t j = 0; j < xsize; j++)
				{
					cout << " ";
				}
			}
			else {
				SetConsoleTextAttribute(Con, matrixColor);
				cout << " ";
				SetConsoleTextAttribute(Con, 15);
				for (size_t j = 0; j < xsize - 2; j++)
				{
					cout << " ";
				}
				SetConsoleTextAttribute(Con, matrixColor);
				cout << " ";
			}
			SetConsoleTextAttribute(Con, 15);
			cout << endl;
		}
	}


	if (!shape.color) {
		sleep = 150;
		int color = rand() % 6;
		if (color != 0)
			color = 16 * color + color;
		else color = 17;

		switch (rand() % 7) {
		case 0:
		{
			shape = Shape(RectangleShape, ysize, color);
			break;
		}
		case 1:
		{
			shape = Shape(GShape, ysize, color);
			break;
		}
		case 2:
		{
			shape = Shape(rGShape, ysize, color);
			break;
		}
		case 3:
		{
			shape = Shape(SquareShape, ysize, color);
			break;
		}
		case 4:
		{
			shape = Shape(ZShape, ysize, color);
			break;
		}
		case 5:
		{
			shape = Shape(rZShape, ysize, color);
			break;
		}
		case 6:
		{
			shape = Shape(TriangleShape, ysize, color);
			break;
		}
		}

		for (size_t i = 0; i < 4; i++)
		{
			if (matrix[shape.coords[i].X][shape.coords[i].Y]) {
				if(!gameOver())
					draw = false;
				else
					return false;
			}
		}
	}

	shape.print();

	if (_kbhit())
		switch (char ch = _getch())
		{
		case 's': case 'S': case 80: {
			sleep = 5;
			break;
		}
		case 'Q': case 'q': {
			COORD* tmp = shape.rotate(1);
			for (size_t i = 0; i < 4; i++)
			{
				if (tmp[i].X + 2 <= 0 || tmp[i].X + 2 >= xsize || matrix[tmp[i].X + 1][tmp[i].Y + 1] != 0) {
					break;
				}
				if (i == 3) {
					SetConsoleTextAttribute(Con, 0);
					for (size_t j = 0; j < 4; j++)
					{
						gotoxy(shape.coords[j]);
						cout << " ";
					}
					SetConsoleTextAttribute(Con, shape.color);
					for (size_t j = 0; j < 4; j++)
					{
						gotoxy(tmp[j]);
						cout << " ";
						shape.coords[j] = tmp[j];
					}
				}
			}
			break;
		}
		case 'E': case 'e': {
			COORD* tmp = shape.rotate(0);
			for (size_t i = 0; i < 4; i++)
			{
				if (tmp[i].X + 2 <= 0 || tmp[i].X + 2 >= xsize || matrix[tmp[i].X + 1][tmp[i].Y + 1] != 0) {
					break;
				}
				if (i == 3) {
					SetConsoleTextAttribute(Con, 0);
					for (size_t j = 0; j < 4; j++)
					{
						gotoxy(shape.coords[j]);
						cout << " ";
					}
					SetConsoleTextAttribute(Con, shape.color);
					for (size_t j = 0; j < 4; j++)
					{
						gotoxy(tmp[j]);
						cout << " ";
						shape.coords[j] = tmp[j];
					}
				}
			}
			break;
		}
		case 'D': case 'd': case 77: {
			for (size_t i = 0; i < 4; i++)
			{
				if(shape.coords[i].X + 2 >= xsize || matrix[shape.coords[i].X][shape.coords[i].Y - 1] ) {
					break;
				}
				if (i == 3) {
					SetConsoleTextAttribute(Con, 0);
					for (size_t j = 0; j < 4; j++)
					{
						gotoxy(shape.coords[j]);
						cout << " ";
						shape.coords[j].X += 1;
					}
					SetConsoleTextAttribute(Con, shape.color);
					for (size_t j = 0; j < 4; j++)
					{
						gotoxy(shape.coords[j].X, shape.coords[j].Y);
						cout << " ";
					}
				}
			}
			break;
		}
		case 'A': case 'a': case 75: {
			for (size_t i = 0; i < 4; i++)
			{
				if (shape.coords[i].X - 1 == 0 || matrix[shape.coords[i].X - 2][shape.coords[i].Y - 1]) {
					break;
				}
				if (i == 3) {
					SetConsoleTextAttribute(Con, 0);
					for (size_t i = 0; i < 4; i++)
					{
						gotoxy(shape.coords[i]);
						cout << " ";
						shape.coords[i].X -= 1;
					}
					SetConsoleTextAttribute(Con, shape.color);
					for (size_t j = 0; j < 4; j++)
					{
						gotoxy(shape.coords[j].X, shape.coords[j].Y);
						cout << " ";
					}
				}
			}

			break;
		}
		}

	for (size_t i = 0; i < 4; i++)
	{
		if (matrix[shape.coords[i].X - 1][shape.coords[i].Y])
		{
			for (size_t j = 0; j < 4; j++)
				matrix[shape.coords[j].X - 1][shape.coords[j].Y - 1] = shape.color;
			shape.color = 0;
			score.scores += 1;
			break;
		}
	}
	if (shape.move()) {
		for (size_t i = 0; i < 4; i++) {
			matrix[shape.coords[i].X - 1][shape.coords[i].Y - 1] = shape.color;
		}
		shape.color = 0;
		score.scores += 1;
	}
	collectRow();
	printOverlay();
	gotoxy(xsize, ysize - 1);
	Sleep(sleep);
	return true;
}

inline void Matrix::collectRow()
{
	HANDLE Con = GetStdHandle(STD_OUTPUT_HANDLE);
	for (size_t i = 0; i < ysize - 2; i++)
	{
		//for (size_t j = i; j < 4; j++)
		//{
		//	if (shape.coords[i].Y == shape.coords[j].Y)
		//		break;
		//}
		for (size_t j = 0; j < xsize - 2; j++)
		{
			if (matrix[j][i] == 0) {
				break;
			}
			if (j == xsize - 3) {
				for (size_t k = i; k > 0; k--)
				{
					for (size_t q = 0; q < xsize - 2; q++)
					{
						matrix[q][k] = matrix[q][k - 1];
						gotoxy(q + 1, k + 1);
						SetConsoleTextAttribute(Con, matrix[q][k]);
						cout << " ";
					}
				}
				for (size_t q = 0; q < xsize - 2; q++)
				{
					matrix[q][0] = 0;
					gotoxy(q + 1, 1);
					SetConsoleTextAttribute(Con, matrix[q][0]);
					cout << " ";
				}
				score.collectedRows++;
				break;
			}
		}
	}
}

inline bool Matrix::gameOver()
{
	HANDLE Con = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Con, 15);
	read();
	gotoxy(80, 15);
	cout << "Game Over!";
	if (bscore.scores < score.scores) {
		bscore.scores = score.scores;
		bscore.collectedRows = score.collectedRows;
		bscore.time = score.time;
		save();
	}
	gotoxy(80, 16);
	cout << "Your best scores: " << bscore.scores;
	gotoxy(80, 17);
	cout << "best colected rows: " << bscore.collectedRows;
	gotoxy(50, 18);
	cout << "Press q to exit. Press other key to restart.";

	gotoxy(0, ysize + 1);
	switch (char ch = _getch()) {
	case 'q': case 'Q': {
		return true;
	}
	default: {
		return false;
	}
	}
}

inline void Matrix::printOverlay()
{
	HANDLE Con = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Con, 15);
	gotoxy(80, 12);
	cout << "Scores: " << score.scores;
	gotoxy(80, 13);
	cout << "Colected rows: " << score.collectedRows;
	gotoxy(80, 14);
	score.time = time(0) - startTime;
	cout << "Time: " << score.time;
}

inline void Matrix::save(const string& path)
{
		ofstream file(path, std::ios_base::binary);
		if(file.is_open())
			file.write((char*)(&bscore), sizeof(&bscore));
		file.close();
}

void Matrix::read(const string& path)
{
	ifstream file(path, std::ios_base::binary);
	if (file.is_open())
		file.read((char*)(&bscore), sizeof(&bscore));
	file.close();
}
