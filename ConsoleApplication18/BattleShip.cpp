//Добавил выбор языка интерфейса. Из яязыков я добавил только Итальянский, Русский и Украинский .
#include <iostream>
#include <vector>
#include <locale.h>
using namespace std;

struct Ship
{
	int Length = 0;
	int Temp_Length = 0;
	vector<int> X;
	vector<int> Y;
	int Start_X = 0;
	int Start_Y = 0;
	bool Positioning = true; // true - vertical, false - horizontal
	bool Status = true; // true - alive, false - down
};

struct AI_Ship
{
	int Length = 0;
	int Temp_Length = 0;
	vector<int> X;
	vector<int> Y;
	int Start_X = 0;
	int Start_Y = 0;
	bool Positioning = true; // true - vertical, false - horizontal
	bool Status = true; // true - alive, false - down
};

bool Check_Placement(string gameboard[10][10], int& x, int& y, int& size, int& count, Ship ship[10], int& lang)
{
	
	string ans = "v";
	while (true)
	{
		if (size != 0)
		{ 
			if (lang == 1)
			{
				cout << "How will the ship position itself: vertically or horizontally (v or h) - ";
				cin >> ans;
			}
			else if (lang == 2)
			{
				setlocale(LC_ALL,"Italian");
				cout << "Come si posizionerà la nave: verticalmente o orizzontalmente (v or h)-";
				cin >> ans;
			}
			else if (lang == 3)
			{
				setlocale(LC_ALL, "Russian");
				cout << "Как будет расположен корабль: вертикально или горизонтально (v or h)- ";
				cin >> ans;
			}
			else if (lang == 4)
			{
				setlocale(LC_ALL, "Ukrainian");
				cout << "Як буде розташован корабель: вертикально чи горизонтально (v or h)-";
				cin >> ans;
			}
			
		}
		if (ans != "v" && ans != "h")
		{
			cout << "v or h" << endl;
		}
		else
		{
			// checking potential ship space
			if (ans == "v" && y + size < 10)
			{
				for (int i = 0; i < size + 1; i++)
				{
					if (gameboard[x][y + i] == "#")
					{
						return false;
					}
				}
				// checking adjacent squares
				if (x > 0)
				{
					// left
					for (int i = y; i < y + size + 1; i++)
					{
						if (gameboard[x - 1][i] == "#")
						{
							return false;
						}
					}
					// above
					if (y > 0)
					{
						if (gameboard[x - 1][y - 1] == "#")
						{
							return false;
						}
					}
				}
				if (y > 0)
				{
					if (gameboard[x][y - 1] == "#")
					{
						return false;
					}
					if (x < 9)
					{
						if (gameboard[x + 1][y - 1] == "#")
						{
							return false;
						}
					}
				}
				if (x < 9)
				{
					// right
					for (int i = y; i < y + size + 1; i++)
					{
						if (gameboard[x + 1][i] == "#")
						{
							return false;
						}
					}
					// below
					if (y + size < 9)
					{
						if (gameboard[x + 1][y + size + 1] == "#")
						{
							return false;
						}
						if (x > 0)
						{
							if (gameboard[x - 1][y + size + 1] == "#")
							{
								return false;
							}
						}
					}
				}
				if (y + size < 9)
				{
					if (gameboard[x][y + size + 1] == "#")
					{
						return false;
					}
				}
				for (int i = 0; i < size + 1; i++)
				{
					gameboard[x][y + i] = "#";
					ship[count].X.push_back(x);
					ship[count].Y.push_back(y + i);
				}
				ship[count].Length = size + 1;
				ship[count].Temp_Length = size + 1;
				ship[count].Start_X = x;
				ship[count].Start_Y = y;
				ship[count].Positioning = true;
				return true;
			}
			else if (ans == "h" && x + size < 10)
			{
				for (int i = 0; i < size + 1; i++)
				{
					if (gameboard[x + i][y] == "#")
					{
						return false;
					}
				}
				// checking adjacent squares
				if (y > 0)
				{
					// above
					for (int i = x; i < x + size + 1; i++)
					{
						if (gameboard[i][y - 1] == "#")
						{
							return false;
						}
					}
					// left
					if (x > 0)
					{
						if (gameboard[x - 1][y - 1] == "#")
						{
							return false;
						}
					}
					if (x + size < 9)
					{
						if (gameboard[x + size + 1][y - 1] == "#")
						{
							return false;
						}
					}
				}
				if (x > 0)
				{
					if (gameboard[x - 1][y] == "#")
					{
						return false;
					}
				}
				if (y < 9)
				{
					// below
					for (int i = x; i < x + size + 1; i++)
					{
						if (gameboard[i][y + 1] == "#")
						{
							return false;
						}
					}
					// right
					if (x + size < 9)
					{
						if (gameboard[x + size + 1][y + 1] == "#")
						{
							return false;
						}
					}
					if (x > 0)
					{
						if (gameboard[x - 1][y + 1] == "#")
						{
							return false;
						}
					}
				}
				if (x + size < 9)
				{
					if (gameboard[x + size + 1][y] == "#")
					{
						return false;
					}
				}
				// adding ship to the database
				for (int i = 0; i < size + 1; i++)
				{
					gameboard[x + i][y] = "#";
					ship[count].X.push_back(x + i);
					ship[count].Y.push_back(y);
				}
				ship[count].Length = size + 1;
				ship[count].Temp_Length = size + 1;
				ship[count].Start_X = x;
				ship[count].Start_Y = y;
				ship[count].Positioning = false;
				return true;
			}
			return false;
		}
	}
}

void V_Outline(string aiboard[10][10], AI_Ship ai_ship[10], int& count)
{
	int x = ai_ship[count].Start_X, y = ai_ship[count].Start_Y, size = ai_ship[count].Length;
	// checking adjacent squares
	if (x > 0)
	{
		// left
		for (int i = y; i < y + size; i++)
		{
			aiboard[x - 1][i] = "!";
		}
		// above
		if (y > 0)
		{
			aiboard[x - 1][y - 1] = "!";
		}
	}
	if (y > 0)
	{
		aiboard[x][y - 1] = "!";
		if (x < 9)
		{
			aiboard[x + 1][y - 1] = "!";
		}
	}
	if (x < 9)
	{
		// right
		for (int i = y; i < y + size; i++)
		{
			aiboard[x + 1][i] = "!";
		}
		// below
		if (y + size < 9)
		{
			aiboard[x + 1][y + size] = "!";
			if (x > 0)
			{
				aiboard[x - 1][y + size] = "!";
			}
		}
	}
	if (y + size < 9)
	{
		aiboard[x][y + size] = "!";
	}
}

void H_Outline(string aiboard[10][10], AI_Ship ai_ship[10], int& count)
{
	int x = ai_ship[count].Start_X, y = ai_ship[count].Start_Y, size = ai_ship[count].Length;
	// checking adjacent squares
	if (y > 0)
	{
		// above
		for (int i = x; i < x + size; i++)
		{
			aiboard[i][y - 1] = "!";
		}
		// left
		if (x > 0)
		{
			aiboard[x - 1][y - 1] = "!";
		}
		if (x + size - 1 < 9)
		{
			aiboard[x + size][y - 1] = "!";
		}
	}
	if (x > 0)
	{
		aiboard[x - 1][y] = "!";
	}
	if (y < 9)
	{
		// below
		for (int i = x; i < x + size; i++)
		{
			aiboard[i][y + 1] = "!";
		}
		// right
		if (x + size - 1 < 9)
		{
			aiboard[x + size][y + 1] = "!";
		}
		if (x > 0)
		{
			aiboard[x - 1][y + 1] = "!";
		}
	}
	if (x + size - 1 < 9)
	{
		aiboard[x + size][y] = "!";
	}
}

bool AI_Check_Placement(string aiboard[10][10], int& x, int& y, int& size, int& count, AI_Ship ai_ship[10])
{
	srand(time(0));
	bool b;
	b = rand() % 2 + 0;
	while (true)
	{
		// checking potential ship space
		if (b && y + size < 10)
		{
			for (int i = 0; i < size + 1; i++)
			{
				if (aiboard[x][y + i] == "#")
				{
					return false;
				}
			}
			// checking adjacent squares
			if (x > 0)
			{
				// left
				for (int i = y; i < y + size + 1; i++)
				{
					if (aiboard[x - 1][i] == "#")
					{
						return false;
					}
				}
				// above
				if (y > 0)
				{
					if (aiboard[x - 1][y - 1] == "#")
					{
						return false;
					}
				}
			}
			if (y > 0)
			{
				if (aiboard[x][y - 1] == "#")
				{
					return false;
				}
				if (x < 9)
				{
					if (aiboard[x + 1][y - 1] == "#")
					{
						return false;
					}
				}
			}
			if (x < 9)
			{
				// right
				for (int i = y; i < y + size + 1; i++)
				{
					if (aiboard[x + 1][i] == "#")
					{
						return false;
					}
				}
				// below
				if (y + size < 9)
				{
					if (aiboard[x + 1][y + size + 1] == "#")
					{
						return false;
					}
					if (x > 0)
					{
						if (aiboard[x - 1][y + size + 1] == "#")
						{
							return false;
						}
					}
				}
			}
			if (y + size < 9)
			{
				if (aiboard[x][y + size + 1] == "#")
				{
					return false;
				}
			}
			for (int i = 0; i < size + 1; i++)
			{
				aiboard[x][y + i] = "#";
				ai_ship[count].X.push_back(x);
				ai_ship[count].Y.push_back(y + i);
			}
			ai_ship[count].Length = size + 1;
			ai_ship[count].Temp_Length = size + 1;
			ai_ship[count].Start_X = x;
			ai_ship[count].Start_Y = y;
			ai_ship[count].Positioning = true;
			V_Outline(aiboard, ai_ship, count);
			return true;
		}
		else if (!b && x + size < 10)
		{
			for (int i = 0; i < size + 1; i++)
			{
				if (aiboard[x + i][y] == "#")
				{
					return false;
				}
			}
			// checking adjacent squares
			if (y > 0)
			{
				// above
				for (int i = x; i < x + size + 1; i++)
				{
					if (aiboard[i][y - 1] == "#")
					{
						return false;
					}
				}
				// left
				if (x > 0)
				{
					if (aiboard[x - 1][y - 1] == "#")
					{
						return false;
					}
				}
				if (x + size < 9)
				{
					if (aiboard[x + size + 1][y - 1] == "#")
					{
						return false;
					}
				}
			}
			if (x > 0)
			{
				if (aiboard[x - 1][y] == "#")
				{
					return false;
				}
			}
			if (y < 9)
			{
				// below
				for (int i = x; i < x + size + 1; i++)
				{
					if (aiboard[i][y + 1] == "#")
					{
						return false;
					}
				}
				// right
				if (x + size < 9)
				{
					if (aiboard[x + size + 1][y + 1] == "#")
					{
						return false;
					}
				}
				if (x > 0)
				{
					if (aiboard[x - 1][y + 1] == "#")
					{
						return false;
					}
				}
			}
			if (x + size < 9)
			{
				if (aiboard[x + size + 1][y] == "#")
				{
					return false;
				}
			}
			// adding ship to the database
			for (int i = 0; i < size + 1; i++)
			{
				aiboard[x + i][y] = "#";
				ai_ship[count].X.push_back(x + i);
				ai_ship[count].Y.push_back(y);
			}
			ai_ship[count].Length = size + 1;
			ai_ship[count].Temp_Length = size + 1;
			ai_ship[count].Start_X = x;
			ai_ship[count].Start_Y = y;
			ai_ship[count].Positioning = false;
			H_Outline(aiboard, ai_ship, count);
			return true;
		}
		return false;
	}
}

void Show(string gameboard[10][10])
{
	cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i << "|";
		for (int j = 0; j < 10; j++)
		{
			cout << gameboard[j][i] << "|";
		}
		cout << endl;
	}
}

void Report(AI_Ship ai_ship[10], int& lang)
{
	int count = 1;
	for (int i = 0; i < 10; i++)
	{
		if (ai_ship[i].Status)
		{
			if (ai_ship[i].Length == 4)
			{
				if(lang==1)
				{
					cout << count << " - Carrier" << endl;
				}
				else if (lang == 2)
				{
					cout << count << " - Portaerei" << endl;
				}
				else if (lang == 3)
				{
					setlocale(LC_ALL, "Russian");
					cout << count << "-Авианосец" << endl;
				}
				else if (lang = 4)
				{
					setlocale(LC_ALL, "Ukrainian");
					cout << count << "-Авіаносець" << endl;
				}

			}
			else if (ai_ship[i].Length == 3)
			{
				if (lang == 1)
				{
					cout << count << " - Battleship" << endl;
				}
				else if (lang == 2)
				{
					cout << count << " - Corazzata" << endl;
				}
				else if (lang == 3)
				{
					setlocale(LC_ALL, "Russian");
					cout << count << "-Линкор" << endl;
				}
				else if (lang = 4)
				{
					setlocale(LC_ALL, "Ukrainian");
					cout << count << "-Лінкор" << endl;
				}
			}
			else if (ai_ship[i].Length == 2)
			{
				if (lang == 1)
				{
					cout << count << " - Destroyer" << endl;
				}
				else if (lang == 2)
				{
					cout << count << " - Distruttore" << endl;
				}
				else if (lang == 3)
				{
					setlocale(LC_ALL, "Russian");
					cout << count << "-Эсминец" << endl;
				}
				else if (lang = 4)
				{
					setlocale(LC_ALL, "Ukrainian");
					cout << count << "-Есмінець" << endl;
				}
			}
			else if (ai_ship[i].Length == 1)
			{
				if (lang == 1)
				{
					cout << count << " -Submarin " << endl;
				}
				else if (lang == 2)
				{
					cout << count << " -Sottomarino" << endl;
				}
				else if (lang == 3)
				{
					setlocale(LC_ALL, "Russian");
					cout << count << "-Подводная лодка" << endl;
				}
				else if (lang = 4)
				{
					setlocale(LC_ALL, "Ukrainian");
					cout << count << "-Підводний човен" << endl;
				}
			}
			count++;
		}
	}
}

void AI_Place_Ships(string aiboard[10][10], AI_Ship ai_ship[10], int& lang)
{
	srand(time(0));
	int four = 1, three = 2, two = 3, one = 4, x = 0, y = 0, size = 3, count = 0;
	while (true)
	{
		x = rand() % 9 + 0;
		y = rand() % 9 + 0;
		if (aiboard[x][y] != "#" && aiboard[x][y] != "!")
		{
			if (AI_Check_Placement(aiboard, x, y, size, count, ai_ship))
			{
				four--;
				count++;
			}
			if (four == 0) { break; }
		}
	}
	size = 2;
	while (true)
	{
		x = rand() % 9 + 0;
		y = rand() % 9 + 0;
		if (aiboard[x][y] != "#" && aiboard[x][y] != "!")
		{
			if (AI_Check_Placement(aiboard, x, y, size, count, ai_ship))
			{
				three--;
				count++;
			}
			if (three == 0) { break; }
		}
	}
	size = 1;
	while (true)
	{
		x = rand() % 9 + 0;
		y = rand() % 9 + 0;
		if (aiboard[x][y] != "#" && aiboard[x][y] != "!")
		{
			if (AI_Check_Placement(aiboard, x, y, size, count, ai_ship))
			{
				two--;
				count++;
			}
			if (two == 0) { break; }
		}
	}
	size = 0;
	while (true)
	{
		x = rand() % 9 + 0;
		y = rand() % 9 + 0;
		if (aiboard[x][y] != "#" && aiboard[x][y] != "!")
		{
			if (AI_Check_Placement(aiboard, x, y, size, count, ai_ship))
			{
				one--;
				count++;
			}
			if (one == 0) { break; }
		}
	}
}

void Place_Ships(string gameboard[10][10], Ship ship[10], int& lang)
{
	int four = 1, three = 2, two = 3, one = 4, x = 0, y = 0, size = 3, count = 0;
	string ans;
	while (true)
	{
		if (lang == 1)
		{
			cout << "Enter the coordinates of the first point where ship starts (ship will expand down or to the right):" << endl;
		}
		else if(lang==2)
		{
			setlocale(LC_ALL, "Italian");
			cout << "Inserisci le coordinate del primo punto di partenza della nave (la nave si espanderà verso il basso o verso destra):" << endl;
		}
		else if (lang == 3)
		{
			setlocale(LC_ALL, "Russian");
			cout << "Введите координаты первой точки старта корабля (корабль расширится вниз или вправо)" << endl;
		}
		else if (lang == 4)
		{
			setlocale(LC_ALL, "Ukrainian");
			cout << "Введіть координати першої точки, звідки починається корабель (корабель буде розгортатися вниз або праворуч)" << endl;
		}
		cout << "X - "; cin >> x;
		cout << "Y - "; cin >> y;


		if (Check_Placement(gameboard, x, y, size, count, ship,lang))
		{
			four--;
			count++;
			Show(gameboard);
		}
		else 
		{
			if (lang == 1)
			{
				cout << "Incorrect starting point" << endl;
			}
			else if (lang == 2)
			{
				cout << "Punto di partenza errato" << endl;
			}
			else if (lang == 3)
			{
				setlocale(LC_ALL, "Russian");
				cout << "Неправильная отправная точка" << endl;
			}
			else if (lang == 4)
			{
				setlocale(LC_ALL, "Ukrainian");
				cout << "Неправильна початкова точка" << endl;
			}
	    }
		if (four == 0) 
		{ 
			break; 
		}
	}
	size = 2;


	while (true)
	{
		if (lang == 1)
		{
			cout << "Enter the coordinates of the first point where ship starts (ship will expand down or to the right):" << endl;
		}
		else if (lang == 2)
		{
			setlocale(LC_ALL, "Italian");
			cout << "Inserisci le coordinate del primo punto di partenza della nave (la nave si espanderà verso il basso o verso destra):" << endl;
		}
		else if (lang == 3)
		{
			setlocale(LC_ALL, "Russian");
			cout << "Введите координаты первой точки старта корабля (корабль расширится вниз или вправо)" << endl;
		}
		else if (lang == 4)
		{
			setlocale(LC_ALL, "Ukrainian");
			cout << "Введіть координати першої точки, звідки починається корабель (корабель буде розгортатися вниз або праворуч)" << endl;
		}
		cout << "X - "; cin >> x;
		cout << "Y - "; cin >> y;

		if (Check_Placement(gameboard, x, y, size, count, ship,lang))
		{
			three--;
			count++;
			Show(gameboard);
		}
		else
		{
			if (lang == 1)
			{
				cout << "Incorrect starting point" << endl;
			}
			else if (lang == 2)
			{
				cout << "Punto di partenza errato" << endl;
			}
			else if (lang == 3)
			{
				setlocale(LC_ALL, "Russian");
				cout << "Неправильная отправная точка" << endl;
			}
			else if (lang == 4)
			{
				setlocale(LC_ALL, "Ukrainian");
				cout << "Неправильна початкова точка" << endl;
			}
		}
		if (three == 0) { break; }
	}
	size = 1;


	while (true)
	{
		if (lang == 1)
		{
			cout << "Enter the coordinates of the first point where ship starts (ship will expand down or to the right):" << endl;
		}
		else if (lang == 2)
		{
			setlocale(LC_ALL, "Italian");
			cout << "Inserisci le coordinate del primo punto di partenza della nave (la nave si espanderà verso il basso o verso destra):" << endl;
		}
		else if (lang == 3)
		{
			setlocale(LC_ALL, "Russian");
			cout << "Введите координаты первой точки старта корабля (корабль расширится вниз или вправо)" << endl;
		}
		else if (lang == 4)
		{
			setlocale(LC_ALL, "Ukrainian");
			cout << "Введіть координати першої точки, звідки починається корабель (корабель буде розгортатися вниз або праворуч)" << endl;
		}
		cout << "X - "; cin >> x;
		cout << "Y - "; cin >> y;

		if (Check_Placement(gameboard, x, y, size, count, ship,lang))
		{
			two--;
			count++;
			Show(gameboard);
		}
		else {
			if (lang == 1)
			{
				cout << "Incorrect starting point" << endl;
			}
			else if (lang == 2)
			{
				cout << "Punto di partenza errato" << endl;
			}
			else if (lang == 3)
			{
				setlocale(LC_ALL, "Russian");
				cout << "Неправильная отправная точка" << endl;
			}
			else if (lang == 4)
			{
				setlocale(LC_ALL, "Ukrainian");
				cout << "Неправильна початкова точка" << endl;
			}
		}
		if (two == 0) { break; }
	}
	size = 0;


	while (true)
	{
		if (lang == 1)
		{
			cout << "Enter the coordinates of the first point where ship starts (ship will expand down or to the right):" << endl;
		}
		else if (lang == 2)
		{
			setlocale(LC_ALL, "Italian");
			cout << "Inserisci le coordinate del primo punto di partenza della nave (la nave si espanderà verso il basso o verso destra):" << endl;
		}
		else if (lang == 3)
		{
			setlocale(LC_ALL, "Russian");
			cout << "Введите координаты первой точки старта корабля (корабль расширится вниз или вправо)" << endl;
		}
		else if (lang == 4)
		{
			setlocale(LC_ALL, "Ukrainian");
			cout << "Введіть координати першої точки, звідки починається корабель (корабель буде розгортатися вниз або праворуч)" << endl;
		}
		cout << "X - "; cin >> x;
		cout << "Y - "; cin >> y;

		if (Check_Placement(gameboard, x, y, size, count, ship,lang))
		{
			one--;
			count++;
			Show(gameboard);
		}
		else {
			if (lang == 1)
			{
				cout << "Incorrect starting point" << endl;
			}
			else if (lang == 2)
			{
				cout << "Punto di partenza errato" << endl;
			}
			else if (lang == 3)
			{
				setlocale(LC_ALL, "Russian");
				cout << "Неправильная отправная точка" << endl;
			}
			else if (lang == 4)
			{
				setlocale(LC_ALL, "Ukrainian");
				cout << "Неправильна початкова точка" << endl;
			}
		}
		if (one == 0) { break; }
	}
	if (lang == 1)
	{
		cout << "All ships successfully placed" << endl;
	}
	else if (lang == 2)
	{
		cout << "Tutte le navi piazzate con successo" << endl;
	}
	else if (lang == 3)
	{
		setlocale(LC_ALL, "Russian");
		cout << "Все корабли были успешно размещены" << endl;
	}
	else if (lang == 4)
	{
		setlocale(LC_ALL, "Ukrainian");
		cout << "Усі кораблі були успішно розміщені" << endl;
	}
}

void Player_Fire(string gameboard[10][10], string aiboard[10][10], string aiboard_playerpov[10][10], Ship ship[10], AI_Ship ai_ship[10],int& lang)
{
	int x, y, down = 11, count = 0;
	bool shotvalue = false;
	// player's move
	while (true)
	{

		if (lang == 1)
		{
			cout << "Enter firing coordinates:" << endl;
		}
		else if (lang == 2)
		{
			cout << "Inserisci le coordinate di sparo:" << endl;
		}
		else if (lang == 3)
		{
			setlocale(LC_ALL, "Russian");
			cout << "Введите координаты для стрельбы:" << endl;
		}
		else if (lang == 4)
		{
			setlocale(LC_ALL, "Ukrainian");
			cout << "Введіть координати для пострілу: " << endl;
		}

		cout << "X - "; cin >> x;
		cout << "Y - "; cin >> y;
		if (x < 10 && y < 10) 
		{ 
			break; 
		}
		else 
		{ 
			if (lang == 1)
			{
				cout << "Inappropriate coordinates" << endl;
			}
			else if (lang == 2) 
			{
				cout << "Coordinate inadeguate" << endl;
			}
			else if (lang == 3)
			{
				setlocale(LC_ALL, "Russian");
				cout << "Неверные координаты" << endl;
			}
			else if (lang == 4)
			{
				setlocale(LC_ALL, "Ukrainian");
				cout << "Невідповідні координати" << endl;
			}
		}
	}
	if (aiboard[x][y] == "#")
	{
		for (int i = 0; i < 10; i++)
		{
			if (ai_ship[i].Status)
			{
				for (int j = 0; j < ai_ship[i].Temp_Length; j++)
				{
					if (x == ai_ship[i].X[j] && y == ai_ship[i].Y[j])
					{
						aiboard_playerpov[x][y] = "X";
						aiboard[x][y] = "X";
						ai_ship[i].X.erase(ai_ship[i].X.begin() + j);
						ai_ship[i].Y.erase(ai_ship[i].Y.begin() + j);
						if (ai_ship[i].X.empty())
						{
							ai_ship[i].Status = false;
							down = i;
						}
						else { shotvalue = true; }
						ai_ship[i].Temp_Length--;
						break;
					}
				}
			}
			if (shotvalue || down != 11) { break; }
		}
		if (shotvalue) 
		{
			cout << "You damaged an enemy's ship" << endl; 
		    shotvalue = false; 
		}
		else if (down != 11)
		{
			if (ai_ship[down].Length == 4)
			{
				if (lang == 1) 
				{
					cout << "You have sunk an enemy's Carrier. Well done!" << endl;
				}
				else if (lang == 2)
				{
					cout << "Hai affondato la Portaerei di un nemico. Ben fatto!" << endl;
				}
				else if (lang == 3)
				{
					setlocale(LC_ALL, "Russian");
					cout << "Вы потопили Авианосец противника. Отличная работа!" << endl;
				}
				else if (lang == 4)
				{
					setlocale(LC_ALL, "Ukrainian");
					cout << "Ви потопили Авіаносець противника. Чудова робота!" << endl;
				}
			}
			else if (ai_ship[down].Length == 3)
			{
				if (lang == 1)
				{
					cout << "You have sunk an enemy's Battleship.Well done!" << endl;
				}
				else if (lang == 2)
				{
					cout << "Hai affondato la Corazzata di un nemico. Ben fatto!" << endl;
				}
				else if (lang == 3)
				{
					setlocale(LC_ALL, "Russian");
					cout << "Вы потопили Линкор противника. Отличная работа!" << endl;
				}
				else if (lang == 4)
				{
					setlocale(LC_ALL, "Ukrainian");
					cout << "Ви потопили Лінкор противника. Чудова робота!" << endl;
				}
			}
			else if (ai_ship[down].Length == 2)
			{
				if (lang == 1)
				{
					cout << "You have sunk an enemy's Destroyer.Well done!" << endl;
				}
				else if (lang == 2)
				{
					cout << "Hai affondato la Distruttore di un nemico. Ben fatto!" << endl;
				}
				else if (lang == 3)
				{
					setlocale(LC_ALL, "Russian");
					cout << "Вы потопили Эсминец противника. Отличная работа!" << endl;
				}
				else if (lang == 4)
				{
					setlocale(LC_ALL, "Ukrainian");
					cout << "Ви потопили лінкор противника. Чудова робота!" << endl;
				}
			}
			else if (ai_ship[down].Length == 1)
			{
				if (lang == 1)
				{
					cout << "You have sunk an enemy's Submarine.Well done!" << endl;
				}
				else if (lang == 2)
				{
					cout << "Hai affondato la Sottomarino di un nemico. Ben fatto!" << endl;
				}
				else if (lang == 3)
				{
					setlocale(LC_ALL, "Russian");
					cout << "Вы потопили Подводную лодку противника. Отличная работа!" << endl;
				}
				else if (lang == 4)
				{
					setlocale(LC_ALL, "Ukrainian");
					cout << "Ви потопили Підводний човен противника. Чудова робота!" << endl;
				}
			}
			if (ai_ship[down].Positioning)
			{
				count = down;
				V_Outline(aiboard_playerpov, ai_ship, count);
			}
			else
			{
				count = down;
				H_Outline(aiboard_playerpov, ai_ship, count);
			}
			down = 11;
		}
		else 
        { 
		        if (lang == 1)
				{
					cout << "You have wasted your shot by firing at the spot that was targeted before" << endl;
				}
				else if (lang == 2)
				{
					cout << "Hai sprecato il tuo colpo sparando nel punto che era stato preso di mira prima" << endl;
				}
				else if (lang == 3)
				{
					setlocale(LC_ALL, "Russian");
					cout << "Вы потратили свой выстрел впустую, выстрелив в точку, которая была выбрана ранее." << endl;
				}
				else if (lang == 4)
				{
					setlocale(LC_ALL, "Ukrainian");
					cout << "Ви втратили свій постріл, стріляючи в точку, яка була націлена раніше" << endl;
				}
        }
	}
	else if (aiboard_playerpov[x][y] == "*" || aiboard_playerpov[x][y] == "X") 
    {
	            if (lang == 1)
				{
					cout << "You have wasted your shot by firing at the spot that was targeted before" << endl;
				}
				else if (lang == 2)
				{
					cout << "Hai sprecato il tuo colpo sparando nel punto che era stato preso di mira prima" << endl;
				}
				else if (lang == 3)
				{
					setlocale(LC_ALL, "Russian");
					cout << "Вы потратили свой выстрел впустую, выстрелив в точку, которая была выбрана ранее." << endl;
				}
				else if (lang == 4)
				{
					setlocale(LC_ALL, "Ukrainian");
					cout << "Ви втратили свій постріл, стріляючи в точку, яка була націлена раніше" << endl;
				}
    }
	else 
    { 
	   aiboard_playerpov[x][y] = "*"; 
	   if (lang == 1)
	   {
		   cout << "You missed" << endl;
	   }
	   else if (lang == 2)
	   {
		   cout << "Ti sei perso" << endl;
	   }
	   else if (lang == 3)
	   {
		   setlocale(LC_ALL, "Russian");
		   cout << "Вы промахнулись" << endl;
	   }
	   else if (lang == 4)
	   {
		   setlocale(LC_ALL, "Ukrainian");
		   cout << "Ви промахнулися" << endl;
	   }
    }
}


int main()
{

	srand(time(0));
	
	int choice = 0;
	int ask = 0;
	int lang=0;
	bool job = 1;
	bool work = 1;
	bool win = true;
	string gameboard[10][10], aiboard[10][10], aiboard_playerpov[10][10];
	fill(&gameboard[0][0], &gameboard[0][0] + 100, '.');
	copy(&gameboard[0][0], &gameboard[0][0] + 100, &aiboard[0][0]);
	copy(&gameboard[0][0], &gameboard[0][0] + 100, &aiboard_playerpov[0][0]);
	Ship ship[10];
	
	while (work)
	{
		while (job)
		{
			cout << "Hello user!Before we go to menu please choose language which you prefer to use: \n1-English\t2-Italian\n3-Russian\t4-Ukrainian";
			cout << "\nIf you want exit from  program enter-0\nChoice: ";
			cin >> lang;

			switch (lang)
			{
			case 1:

				cout << "\n\tWelcome to Sea battle game!! ";
				cout << "\n\t\t1-PvP game mode\n\t\t2-PvE game mode\n\t\t3-Exit";
				cin >> choice;

				switch (choice)
				{
				case 1:
					break;
				case 2:
					break;
				case 3:
					job = 0;
					work = 0;
					break;
				default:
					cout << "Unknown command";
					break;
				}
				break;

			case 2:
				setlocale(LC_ALL, "Italian");
				cout << "\n\tBenvenuto nel gioco di battaglie naval!! ";
				cout << "\n\t\t1-PvP modalità di gioco\n\t\t2-PvE modalità di gioco\n\t\t3-Uscita";
				cin >> choice;

				switch (choice)
				{
				case 1:
					break;
				case 2:
					break;
				case 3:
					job = 0;
					work = 0;
					break;
				default:
					cout << "\nComando sconosciuto";
					break;
				}
				break;

			case 3:

				setlocale(LC_ALL, "Russian");
				cout << "\n\tДобро пожаловать в игру Морской бой!!";
				cout << "\n\t\t1-PvP режим \n\t\t2-PvE режим\n\t\t3-Выйти";
				cin >> choice;

				switch (choice)
				{
				case 1:
					
					break;
				case 2:
					break;
				case 3:
					job = 0;
					work = 0;
					break;
				default:
					cout << "\nКоманда не существует";
					break;
				}
				break;

			case 4:

				setlocale(LC_ALL, "Ukrainian");
				cout << "\n\tВітаємо у грі Морський бій!!";
				cout << "\n\t\t1-PvP режим \n\t\t2-PvE режим\n\t\t3-Вийти";
				cin >> choice;

				switch (choice)
				{
				case 1:
					break;
				case 2:
					break;
				case 3:
					job = 0;
					work = 0;
					break;
				default:
					cout << "\nКоманда не існує";
					break;
				}
				break;

			case 0:
				job = 0;
				work = 0;
				break;
			default:
				cout << "\nUnknown command";
				break;
			}
		}
		
	}
}