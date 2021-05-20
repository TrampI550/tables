#include "sorttab.h"
#include <string>
#include <sstream>
#include <fstream>
typedef std::string Key;
int** tMark = NULL;
Key* tKey = NULL;
int tDataCount = 0, MemSize = 10;
TScanTable pTab(100);
int TypeGenNumbers()
{
	int Type;
	std::cout << "Select the type of filling:\n 1. From the file.txt \n 2. From the random machine\n ";
	do
	{
		std::cin >> Type;
		if (Type == 1)
		{
			std::cout << "Select the type of table:\n 1. Scan Table \n 2. Sort Table\n 3. Tree Table" << std::endl;
			do
			{
				std::cin >> Type;
				if (Type == 1)
					return 1;
				else if (Type == 2)
					return 2;
				else if (Type == 3)
					return 3;
				else std::cout << "Wrong number, try again" << std::endl;
			} while (1);
		}
		if (Type == 2)
		{
			std::cout << "Select the type of table:\n 1. Scan Table \n 2. Sort Table\n 3. Tree Table" << std::endl;
			do
			{
				std::cin >> Type;
				if (Type == 1)
					return 4;
				else if (Type == 2)
					return 5;
				else if (Type == 3)
					return 6;
				else std::cout << "Wrong number, try again" << std::endl;
			} while (1);
		}
		std::cout << "Wrong number, try again"<<std::endl;
	} while (1);
}
void del()
{
	delete[] tKey;
	for (int i = 0; i < 5; i++)
		delete tMark[i];
	delete[] tMark;
}
void gFile()/////////////////////// еще сорт табл
{
	std::ifstream file("C:\\Users\\tramp\\source\\repos\\try1\\input.txt");
	if (file.is_open())
	{
		std::string line1;
		while (std::getline(file, line1))
			tDataCount++;
		/////
		file.clear();
		file.seekg(0, std::ios::beg);
		/////
		MemSize = tDataCount + 10;
		tMark = new int* [MemSize];
		tKey = new std::string[MemSize];
		for (int l = 0; l < MemSize; l++)
			tMark[l] = new int[5];
		std::cout << "File is opened" << std::endl;
		std::string line2;
		for (int k = 0; std::getline(file, line2); k++)
		{
			std::istringstream iss(line2);
			std::string token;
			for (int i=0;std::getline(iss, token, '|');i++)
			{
				if (i == 0) tKey[k] = token;
				if ((i >= 1) && (i <= 5))
					tMark[k][i-1] = std::stoi(token); //перевод string в int
			}
			//tDataCount++;
		}
		for (int i = 0; i < tDataCount; i++)
		{
			pTab.InsRecord(tKey[i], tMark[i]);
		}
		file.close();
	}
	else std::cout << "Opening error"<<std::endl;
}
void KeyEnt()
{
	tKey[0] = "Sasha Sablin";
	tKey[1] = "Kolya Beloy";
	tKey[2] = "Triptis Castle";
	tKey[3] = "Alex Lionev";
	tKey[4] = "Mixa Vaneev";
	for (int i = 5; i < tDataCount; i++)
		tKey[i] = rand() % 57 + 65;
}
void generator(void)/////////////////////// еще сорт табл
{
	std::cout << "Enter records amount" << std::endl;
	std::cin >> tDataCount;
	MemSize = tDataCount + 10;
	tMark = new int* [MemSize];
	tKey = new std::string[MemSize];
	for (int i = 0; i < tDataCount; i++)
	{
		tMark[i] = new int[5];
		for (int j = 0; j < 5; j++)
			tMark[i][j] = rand() % 4 + 2;
	}
	KeyEnt();
	int* mr;
	for (int i = 0; i < tDataCount; i++)
	{
		pTab.InsRecord(tKey[i], tMark[i]);
		mr = pTab.FindRecord(tKey[i]);
		std::cout << tKey[i] << "  ";
		for (int j = 0; j < 5; j++)
			std::cout << mr[j] << " ";
		std::cout << std::endl;
	}
}
void mainmenu(void)
{
	Key key;
	int delta;
	do
	{
		std::cout << "select option\n" << "0 - Exit\n"
			<< "1 - Insert record\n" << "2 - Find record\n"
			<< "3 - Delete record\n" << "4 - Print table\n";
		std::cin >> delta;
		system("cls");
		if (delta != 0 && delta != 4)
		{
			std::cout << "Enter a key\n";
			std::cin.ignore();
			std::getline(std::cin, key);
		}
		switch (delta)
		{
		case 0: break;
		case 1:
		{
			if (!pTab.IsFull()&&(!pTab.FindRecord(key)))
			{
					std::cout << "Insert key marks (4)" << std::endl;
					for (int j = 0; j < 5; j++)
						std::cin >> tMark[tDataCount][j];
					pTab.InsRecord(key, tMark[tDataCount]);
					tDataCount++;
					std::cout << "Record added" << std::endl;
			}
			else std::cout << "Insert Error: Table is full\n";
		}break;
		case 2:
		{
			int* mr;
			mr = pTab.FindRecord(key);
			if (mr != NULL)
			{
				std::cout << key << std::endl;
				for (int j = 0; j < 5; j++)
					std::cout << mr[j] << " ";
			}
			else std::cout << "Record is not found" << std::endl;
		}break;
		case 3:
		{
			if (pTab.FindRecord(key))
			{
				pTab.DelRecord(key);
				std::cout << "Record Deleted" << std::endl;
				tDataCount--;
			}
		}break;
		case 4:
		{
			std::cout << pTab << std::endl;
		}break;
		default: std::cout << "Wrong number, try again" << std::endl; delta = 1;
		}
	} 	while (delta);
}
void menu(void)
{
	int Type = TypeGenNumbers();
	if (Type == 4)
	{
		generator();
		mainmenu();
	}
	else if (Type == 1)
	{
		gFile();
		mainmenu();
	}
}
int main()
{
	std::srand(time(NULL));
	menu();
	del();//освобождение памяти для временных tKey и tMark
	return 0;
}