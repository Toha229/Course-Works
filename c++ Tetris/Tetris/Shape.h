#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <windows.h>
using std::endl;
using std::string;
using std::cout;
using std::pair;
using std::ifstream;
using std::ofstream;


void gotoxy(COORD p) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
void gotoxy(int x, int y) {
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}


enum ShapeType { RectangleShape, GShape, rGShape, SquareShape, ZShape, rZShape, TriangleShape };


class Shape
{
	friend class Matrix;
private:
	COORD coords[4];
	int color;
	int r;
	ShapeType type;
public:
	Shape() { color = 0; }
	Shape(const ShapeType& type, const short& matrixSize, const int& color);
	void print();
	COORD* rotate(bool revers);
	bool move();
};

Shape::Shape(const ShapeType& type, const short& matrixSize, const int& color)
	:type(type), color(color)
{
	int rnd = rand();
	if (type == RectangleShape) {
		if (rnd % 2 == 0) {
			r = 0;
			coords[0] = { matrixSize / 2 - 1, 1 };
			coords[1] = { matrixSize / 2, 1 };
			coords[2] = { matrixSize / 2 + 1, 1 };
			coords[3] = { matrixSize / 2 + 2, 1 };
		}
		else
		{
			r = 90;
			coords[0] = { matrixSize / 2, 1 };
			coords[1] = { matrixSize / 2, 2 };
			coords[2] = { matrixSize / 2, 3 };
			coords[3] = { matrixSize / 2, 4 };
		}
	}


	if (type == GShape) {
		if (rnd % 4 == 0) {
			r = 0;
			coords[0] = { matrixSize / 2, 1 };
			coords[1] = { matrixSize / 2 + 1, 1 };
			coords[2] = { matrixSize / 2, 2 };
			coords[3] = { matrixSize / 2, 3 };
		}
		else if (rnd % 4 == 1)
		{
			r = 90;
			coords[0] = { matrixSize / 2 - 1, 1 };
			coords[1] = { matrixSize / 2, 1 };
			coords[2] = { matrixSize / 2 + 1, 1 };
			coords[3] = { matrixSize / 2 + 1, 2 };
		}
		else if (rnd % 4 == 2)
		{
			r = 180;
			coords[0] = { matrixSize / 2, 1 };
			coords[1] = { matrixSize / 2, 2 };
			coords[2] = { matrixSize / 2, 3 };
			coords[3] = { matrixSize / 2 - 1, 3 };
		}
		else if (rnd % 4 == 3)
		{
			r = 270;
			coords[0] = { matrixSize / 2 - 1, 1 };
			coords[1] = { matrixSize / 2 - 1, 2 };
			coords[2] = { matrixSize / 2, 2 };
			coords[3] = { matrixSize / 2 + 1, 2 };
		}
	}


	if (type == rGShape) {
		if (rnd % 4 == 0) {
			r = 0;
			coords[0] = { matrixSize / 2 - 1, 1 };
			coords[1] = { matrixSize / 2, 1 };
			coords[2] = { matrixSize / 2, 2 };
			coords[3] = { matrixSize / 2, 3 };
		}
		else if (rnd % 4 == 1)
		{
			r = 90;
			coords[0] = { matrixSize / 2 + 1, 1 };
			coords[1] = { matrixSize / 2 - 1, 2 };
			coords[2] = { matrixSize / 2, 2 };
			coords[3] = { matrixSize / 2 + 1, 2 };
		}
		else if (rnd % 4 == 2)
		{
			r = 180;
			coords[0] = { matrixSize / 2, 1 };
			coords[1] = { matrixSize / 2, 2 };
			coords[2] = { matrixSize / 2, 3 };
			coords[3] = { matrixSize / 2 + 1, 3 };
		}
		else if (rnd % 4 == 3)
		{
			r = 270;
			coords[0] = { matrixSize / 2 - 1, 1 };
			coords[1] = { matrixSize / 2, 1 };
			coords[2] = { matrixSize / 2 + 1, 1 };
			coords[3] = { matrixSize / 2 - 1, 2 };
		}
	}


	if (type == SquareShape) {
		r = 0;
		coords[0] = { matrixSize / 2, 1 };
		coords[1] = { matrixSize / 2 + 1, 1 };
		coords[2] = { matrixSize / 2, 2 };
		coords[3] = { matrixSize / 2 + 1, 2 };
	}


	if (type == ZShape) {
		if (rnd % 2 == 0) {
			r = 0;
			coords[0] = { matrixSize / 2, 1 };
			coords[1] = { matrixSize / 2 - 1, 1 };
			coords[2] = { matrixSize / 2, 2 };
			coords[3] = { matrixSize / 2 + 1, 2 };
		}
		else
		{
			r = 90;
			coords[0] = { matrixSize / 2 + 1, 1 };
			coords[1] = { matrixSize / 2, 2 };
			coords[2] = { matrixSize / 2 + 1, 2 };
			coords[3] = { matrixSize / 2, 3 };
		}
	}


	if (type == rZShape) {
		if (rnd % 2 == 0) {
			r = 0;
			coords[0] = { matrixSize / 2, 1 };
			coords[1] = { matrixSize / 2 + 1, 1 };
			coords[2] = { matrixSize / 2, 2 };
			coords[3] = { matrixSize / 2 - 1, 2 };
		}
		else
		{
			r = 90;
			coords[0] = { matrixSize / 2, 1 };
			coords[1] = { matrixSize / 2, 2 };
			coords[2] = { matrixSize / 2 + 1, 2 };
			coords[3] = { matrixSize / 2 + 1, 3 };
		}
	}


	if (type == TriangleShape) {
		if (rnd % 4 == 0) {
			r = 0;
			coords[0] = { matrixSize / 2, 1 };
			coords[1] = { matrixSize / 2 - 1, 2 };
			coords[2] = { matrixSize / 2, 2 };
			coords[3] = { matrixSize / 2 + 1, 2 };
		}
		else if (rnd % 4 == 1)
		{
			r = 90;
			coords[0] = { matrixSize / 2, 1 };
			coords[1] = { matrixSize / 2, 2 };
			coords[2] = { matrixSize / 2 + 1, 2 };
			coords[3] = { matrixSize / 2, 3 };
		}
		else if (rnd % 4 == 2)
		{
			r = 180;
			coords[0] = { matrixSize / 2 - 1, 1 };
			coords[1] = { matrixSize / 2, 1 };
			coords[2] = { matrixSize / 2 + 1, 1 };
			coords[3] = { matrixSize / 2, 2 };
		}
		else if (rnd % 4 == 3)
		{
			r = 270;
			coords[0] = { matrixSize / 2, 1 };
			coords[1] = { matrixSize / 2 - 1, 2 };
			coords[2] = { matrixSize / 2, 2 };
			coords[3] = { matrixSize / 2, 3 };
		}
	}
}

inline void Shape::print()
{
	HANDLE Con = GetStdHandle(STD_OUTPUT_HANDLE);
	for (size_t i = 0; i < 4; i++)
	{
		if (coords[i].Y - 1 != 0) {
			for (size_t j = 0; j < 4; j++)
			{
				if (coords[i].X == coords[j].X && coords[i].Y - 1 == coords[j].Y)
				{
					j = 4;
					continue;
				}
				if (j == 3) {
					gotoxy(coords[i].X, coords[i].Y - 1);
					SetConsoleTextAttribute(Con, 0);
					cout << " ";
				}
			}
		}
	}
	for (size_t i = 0; i < 4; i++)
	{
		if (coords[i].Y != 0) {
			gotoxy(coords[i]);
			SetConsoleTextAttribute(Con, color);
			cout << " ";
		}
	}
	SetConsoleTextAttribute(Con, 15);
	gotoxy(31, 30);
}

COORD* Shape::rotate(bool revers)
{
	COORD* tmpcoords = new COORD[4];
	for (size_t i = 0; i < 4; i++)
	{
		tmpcoords[i] = coords[i];
	}


	size_t i;
	if (revers)
		i = 0;
	else
		i = 2;
	for (; i < 3; i++)
	{
		if (type == RectangleShape) {
			if (r == 90) {
				r = 0;
				tmpcoords[0].X--;
				tmpcoords[0].Y++;
				tmpcoords[2].X++;
				tmpcoords[2].Y--;
				tmpcoords[3].X += 2;
				tmpcoords[3].Y -= 2;
			}
			else
			{
				r = 90;

				tmpcoords[0].X++;
				tmpcoords[0].Y--;
				tmpcoords[2].X--;
				tmpcoords[2].Y++;
				tmpcoords[3].X -= 2;
				tmpcoords[3].Y += 2;
			}
		}
		if (type == GShape) {
			if (r == 270) {
				r = 0;

				tmpcoords[0].X += 1;
				tmpcoords[1].X += 2;
				tmpcoords[1].Y -= 1;
				tmpcoords[3].X -= 1;
				tmpcoords[3].Y += 1;
			}
			else if (r == 0)
			{
				r = 90;

				tmpcoords[0].X -= 1;
				tmpcoords[0].Y += 1;
				tmpcoords[1].X -= 1;
				tmpcoords[1].Y += 1;
				tmpcoords[2].X += 1;
				tmpcoords[3].X += 1;
			}
			else if (r == 90)
			{
				r = 180;

				tmpcoords[0].X += 1;
				tmpcoords[0].Y -= 1;
				tmpcoords[2].X -= 1;
				tmpcoords[2].Y += 1;
				tmpcoords[3].X -= 2;
			}
			else if (r == 180)
			{
				r = 270;

				tmpcoords[0].X -= 1;
				tmpcoords[0].Y += 1;
				tmpcoords[1].X -= 1;
				tmpcoords[1].Y += 1;
				tmpcoords[3].X += 2;
			}
		}
		if (type == rGShape) {
			if (r == 270) {
				r = 0;

				tmpcoords[0].Y -= 1;
				tmpcoords[1].Y -= 1;
				tmpcoords[2].X -= 1;
				tmpcoords[3].X += 1;
			}
			else if (r == 0)
			{
				r = 90;

				tmpcoords[0].X += 2;
				tmpcoords[1].X -= 1;
				tmpcoords[1].Y += 1;
				tmpcoords[3].X += 1;
				tmpcoords[3].Y -= 1;
			}
			else if (r == 90)
			{
				r = 180;

				tmpcoords[0].X -= 1;
				tmpcoords[1].X += 1;
				tmpcoords[2].Y += 1;
				tmpcoords[3].Y += 1;
			}
			else if (r == 180)
			{
				r = 270;

				tmpcoords[0].X -= 1;
				tmpcoords[0].Y += 1;
				tmpcoords[2].X += 1;
				tmpcoords[2].Y -= 1;
				tmpcoords[3].X -= 2;
			}
		}
		if (type == ZShape) {
			if (r == 90) {
				r = 0;

				tmpcoords[1].Y -= 1;
				tmpcoords[3].X += 2;
				tmpcoords[3].Y -= 1;
			}
			else
			{
				r = 90;

				tmpcoords[1].Y += 1;
				tmpcoords[3].X -= 2;
				tmpcoords[3].Y += 1;
			}
		}
		if (type == rZShape) {
			if (r == 90) {
				r = 0;

				tmpcoords[1].X += 1;
				tmpcoords[1].Y -= 1;
				tmpcoords[2].X -= 1;
				tmpcoords[3].X -= 2;
				tmpcoords[3].Y -= 1;
			}
			else
			{
				r = 90;

				tmpcoords[1].X -= 1;
				tmpcoords[1].Y += 1;
				tmpcoords[2].X += 1;
				tmpcoords[3].X += 2;
				tmpcoords[3].Y += 1;
			}
		}
		if (type == TriangleShape) {
			if (r == 270) {
				r = 0;

				tmpcoords[3].X += 1;
				tmpcoords[3].Y -= 1;
			}
			else if (r == 0)
			{
				r = 90;

				tmpcoords[1].X += 1;
				tmpcoords[2].X += 1;
				tmpcoords[3].X -= 1;
				tmpcoords[3].Y += 1;
			}
			else if (r == 90)
			{
				r = 180;

				tmpcoords[0].X -= 1;
				tmpcoords[0].Y += 1;
			}
			else if (r == 180)
			{
				r = 270;

				tmpcoords[0].X += 1;
				tmpcoords[0].Y -= 1;
				tmpcoords[1].X -= 1;
				tmpcoords[2].X -= 1;
			}
		}
	}

	return tmpcoords;

}

inline bool Shape::move()
{
	for (size_t i = 0; i < 4; i++)
	{
		if (color == 0 && coords[i].Y == 28)
			return true;
	}
	for (size_t i = 0; i < 4; i++)
		coords[i].Y++;
	return false;
}
