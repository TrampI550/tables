#include "sorttab.h"
#include <string>
#include <sstream>
#include <fstream>
typedef std::string Key;
int tDataCount = 5, MemSize = tDataCount + 10;
TScanTable tTab(MemSize);
TSortTable sTab(MemSize);
//TScanTable* tTab = NULL;
//TSortTable* sTab = NULL;
int** tMark = NULL;
Key* tKey= NULL;
void del(void)
{
	//delete[] tTab;
	//delete[] sTab;
	delete[] tKey;
	for (int i = 0; i < 5; i++)
		delete tMark[i];
	delete[] tMark;
}
void gFile(void)
{
	std::ifstream file("‪‪C:/Users/tramp/source/repos/try1/input.txt",std::ios::in);
	if (file.is_open())
	{
		//MemSize = tDataCount + 10;
		//tTab = new TScanTable[MemSize];
		tMark = new int* [MemSize];
		tKey = new std::string[MemSize];
		std::cout << "Файл открыт." << std::endl;
		std::string line;
		for (int k = 0; std::getline(file, line); k++)
		{
			tMark[k] = new int[5];
			std::istringstream iss(line);
			std::string token;
			for (int i = 0; std::getline(iss, token, '\t');i++)
			{
				if (i == 0) tKey[k] = token;
				if ((i >= 1)&&(i<=5)) 
					tMark[k][i] = atoi(token.c_str());//перевод string в int
			}
		}
		//int* mr;
		for (int i = 0; i < tDataCount; i++)
		{
			tTab./*->*/InsRecord(tKey[i], tMark[i]);
			//mr = tTab->FindRecord(tKey[i]);
			//std::cout << tKey[i] << "  ";
			//for (int j = 0; j < 5; j++)
			//	std::cout << mr[j] << " ";
			//std::cout << std::endl;
		}
		file.close();
	}
	else std::cout << "Opening error"<<std::endl;
}
void generator(void)
{
	//MemSize = tDataCount + 10;
	//tTab = new TScanTable[MemSize];
	//sTab = new TSortTable[MemSize];
	tMark = new int* [MemSize];
	tKey = new std::string[MemSize];
	for (int i = 0; i < tDataCount; i++)
	{
		tMark[i] = new int[5];
		for (int j = 0; j < 5; j++)
			tMark[i][j] = rand() % 4 + 2;
	}
	tKey[0] = "Sasha Sablin";	tKey[1] = "Kolya Beloy";	tKey[2] = "Triptis Castle";	tKey[3] = "Alex Lionev";	tKey[4] = "Mixa Vaneev";
	/////////вывод + ввод в таблицу
	int* mr;
	for (int i = 0; i < tDataCount; i++)
	{
		tTab./*->*/InsRecord(tKey[i], tMark[i]);
		mr = tTab./*->*/FindRecord(tKey[i]);
		std::cout << tKey[i] << "  ";
		for (int j = 0; j < 5; j++)
			std::cout << mr[j] << " ";
		std::cout << std::endl;
	}
	sTab = tTab;
}
void menu(void)
{
	std::string key;
	int delta;
	do
	{
		std::cout << "select option" << std::endl << "0 - Exit" << std::endl
			<< "1 - Insert record" << std::endl << "2 - Find record" << std::endl
			<< "3 - Delete record" << std::endl << "4 - Print table" << std::endl;
		std::cin >> delta;
		system("cls");
		if (delta != 0 && delta != 4)
		{
			std::cout << "Enter a key" << std::endl;
			std::cin.ignore();
			std::getline(std::cin, key);
		}
		switch (delta)
		{
		case 0: break;
		case 1:
		{
			if (!sTab./*->*/IsFull())
			{
				tMark[tDataCount] = new int[5];
				std::cout << "Insert key marks (4)" << std::endl;
				for (int j = 0; j < 5; j++)
					std::cin >> tMark[tDataCount][j];
				sTab./*->*/InsRecord(key, tMark[tDataCount]);
				tDataCount++;
				std::cout << "Record added" << std::endl;
			}
			else std::cout << "Insert Error: Table is full";
		}break;
		case 2:
		{
			int* mr;
			mr = sTab./*->*/FindRecord(key);
			if (mr != NULL)
				for (int j = 0; j < 5; j++)
					std::cout << mr[j] << " ";
			else std::cout << "Record is not found" << std::endl;
		}break;
		case 3:
		{
			sTab./*->*/DelRecord(key);
			std::cout << "Record Deleted" << std::endl;
			tDataCount--;
		}break;
		case 4:
		{
			//std::cout << /***/tTab << std::endl;
			std::cout << /***/sTab << std::endl;
		}break;
		default: std::cout << "Wrong number, try again" << std::endl; delta = 1;
		}
	} 	while (delta);
}
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	std::srand(time(NULL));
	generator();
	//gFile();
	menu();
	del();
	return 0;
}