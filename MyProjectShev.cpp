#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
using namespace std;

int main()
{
	srand(time(0)); // запуск генератора случайных чисел
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
	do // цикл ставит координаты яблока случанйм образом - но чтобы они не совпадали со "змейкой"
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
	CONSOLE_CURSOR_INFO cci = { sizeof(cci), false }; // создание параметров на отображение курсора
	SetConsoleCursorInfo(h, &cci);

	SetConsoleTextAttribute(h, 5); // установка цвета, которым рисуется рамка поля
	for (int y = 0; y < height; y++) // двойной цикл на отрисовку рамки
	{
		for (int x = 0; x < width; x++)
		{
			char s;
			if (x == 0 && y == 0)
				s = 218;
			else if (x == 0 && y == height - 1)
				s = 192;
			else if (y == 0 && x == width - 1)
				s = 191;
			else if (y == height - 1 && x == width - 1)
				s = 217;
			else if (y == 0 || y == height - 1)
				s = 196;
			else if (x == 0 || x == width - 1)
				s = 179;
			else s = ' ';
			putchar(s);
		}
		cout << endl;
	}
	c.X = X_apple; // связываем объект координат с позициями "яблока"
	c.Y = Y_apple;
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, 12); // устанавливаем красный цвет для отрисовки "яблока"
	putchar(apple);

	c.X = array_X[0];
	c.Y = array_Y[0];
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, 10);
	putchar(head);

	bool flag = true; // переменная для управления ходом цикла
	do // цикл игры
	{
		Sleep(sleep_time);

		if (_kbhit()) // проверяем, была ли нажата какая-либо клавиша и запускаем её обработку в случае True
		{
			int k = _getch();
			if (k == 0 || k == 224)
				k = _getch();
			switch (k)
			{
			case 80:
				dy = 1;
				dx = 0;
				break;
			case 72:
				dy = -1;
				dx = 0;
				break;
			case 75:
				dy = 0;
				dx = -1;
				break;
			case 77:
				dy = 0;
				dx = 1;
				break;
			case 27:
				flag = false;
				break;
			}
		}
		int X = array_X[length - 1] + dx; // определяем значение абсциссы головы "змейки" после смещения
		int Y = array_Y[length - 1] + dy;
		if (X == 0 || X == width - 1 || Y == 0 || Y == height - 1)
		{
			flag = false;
		}
		else if (X == X_apple && Y == Y_apple) // проверка на достижение "яблока"
		{
			c.X = array_X[length - 1];
			c.Y = array_Y[length - 1];
			SetConsoleCursorPosition(h, c);
			putchar(snake);

			length++;
			c.X = array_X[length - 1] = X;
			c.Y = array_Y[length - 1] = Y;
			SetConsoleCursorPosition(h, c);
			putchar(head);

			if (length == max_length) // проверка, достигла ли длина "змейки" своего максимального значения
			{
				break;
			}

			int i;
			do
			{
				X_apple = rand() % (width - 2) + 1;
				Y_apple = rand() % (height - 2) + 1;
				i = 0;
				for (; i < length; i++)
					if (X_apple == array_X[i] && Y_apple == array_Y[i])
						break;
			} while (i < length);
			c.X = X_apple;
			c.Y = Y_apple;
			SetConsoleCursorPosition(h, c);
			SetConsoleTextAttribute(h, 12);
			putchar(apple);
			SetConsoleTextAttribute(h, 10);
		}
		else // случай, когда голова "змейки" оказалась на новой пустой позиции
		{
			c.X = array_X[0];
			c.Y = array_Y[0];
			SetConsoleCursorPosition(h, c); 
			putchar(' '); 

			if (length > 1) // если длина змейки больше
			{
				c.X = array_X[length - 1]; 
				c.Y = array_Y[length - 1];
				SetConsoleCursorPosition(h, c);  
				putchar(snake); 
			}

			for (int i = 0; i < length - 1; i++) // запускаем цикл свдига координат звеньев "змейки"
			{
				array_X[i] = array_X[i + 1]; 
				array_Y[i] = array_Y[i + 1];
			}

			c.X = array_X[length - 1] = X; // устанавливаем новую позицию головы "змейки"
			c.Y = array_Y[length - 1] = Y;
			SetConsoleCursorPosition(h, c); 
			putchar(head); 
		}
	
		} while (flag); // выходим из цикла, если сброшена управляющая переменная
		system("cls");
		cout << "GAME OVER\n";
		system("pause");
	
}