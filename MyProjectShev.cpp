#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
using namespace std;

int main()
{
	srand(time(0));
	rand();
	system("mode con cols=51 lines=31"); 
	MoveWindow(GetConsoleWindow(), 50, 50, 2000, 2000, true); 

	const int width = 50, height = 30; 
	const int max_length = 50; 
	int array_X[max_length];
	int array_Y[max_length]; 
	int length = 1; 
	array_X[0] = width / 2; 
	array_Y[0] = height / 2; 
	int dx = 1, dy = 0; 
	int X_apple; 
	int Y_apple; 
	do 
	{
		X_apple = rand() % (width - 2) + 1;
		Y_apple = rand() % (height - 2) + 1;
	} while (X_apple != array_X[length - 1] && Y_apple != array_Y[length - 1]);

	int sleep_time = 100; 

	char snake = '*'; 
	char apple = 'o'; 
	char head = 1; 
	COORD c; 
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO cci = { sizeof(cci), false }; 
	SetConsoleCursorInfo(h, &cci); 

	SetConsoleTextAttribute(h, 4);