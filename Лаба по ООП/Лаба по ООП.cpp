#include <iostream>
#include <conio.h>
#include <stdio.h>
#pragma warning(disable : 4996) //Отключение предупреждений

const int STR_LEN = 50; //максимальная длина строки
const int FN_LEN = 24; //максимальная длина имени файла
const int DIR = 1; //прямое направление отображения

const int BACK = -1; //обратное направление отображения

struct item

{
	
	char* key;
	item* next;

};

void AddItem(item*&, char*); 

item* CopyList(item*);

int DeleteItem(item*&, item*&);

int FindItem(item*, item*&, char*); 

void PrintList(item*, int);

void DeleteDblItems(item*); 

int CountItems(item*);

void SortList(item*&);

item* LinkLists(item*, item*);

item* SubtrLists(item*, item*);

item* CrossLists(item*, item*);

int SaveList(item*, FILE*); 

int OpenList(item*&, FILE*);

void Menu1();

void Menu2(item*&);

void Menu3(item*&, item*&);

int main(int argc, char* argv[])

{
	
	Menu1();
	return(0);

}


void DeleteList(item*& pFirst)

//Удаление всего списка

{

	while (pFirst != 0) DeleteItem(pFirst, pFirst);

}

void AddItem(item*& pFirst, char* Str)

//Добавление в начало списка нового элемента

{

	item* P = new item;

	P->key = new char[strlen(Str)]; // Выделяем память под char в элементе P 
	
	strcpy(P->key, Str);

	P->next = pFirst;
	
	pFirst = P;

}

item* CopyList(item* pFirst)

//Возвращает указатель на копию списка

{

	item* pNewFirst = 0; while (pFirst != 0)

	{

		AddItem(pNewFirst, pFirst->key); pFirst = pFirst->next;

	}

	return pNewFirst;

}

int FindItem(item* pFirst, item*& pResult, char* Str)

//Поиск элемента, равного строке Str //pResult - указатель на результат поиска //0 - элемент найден //1 - список пуст
//2 - элемент не найден

//pFirst может указывать на любой элемент с которого нужно начинать поиск

{

	if (pFirst == 0) return 1;

	pResult = pFirst;

	while (pResult != 0 && strcmp(pResult->key, Str) != 0) pResult = pResult->next;

	if (pResult == 0) return 2;

	return 0;

}

int DeleteItem(item*& pFirst, item*& pCur)

//Удаление элемента, на который указывает pCur //0 - удаление успешно //1 - список пуст

//2 - элемент не найден или не существует //если удаляемый элемент не первый,

//то pFirst может указывать на любой элемент перед pCur

{

	if (pFirst == 0) return 1; if (pCur == 0) return 2; item* P;

	//удаление первого элемента 
	if (pCur == pFirst)
	{

		P = pCur;

		pFirst = pFirst->next; pCur = pFirst;

		delete P; return 0;

	}

	//удаление из произвольного места

	P = pFirst;

	while (P->next != pCur)

	{

		P = P->next;

		if (P == 0) return 2;

	}

	P->next = pCur->next; 
	
	P = pCur;

	pCur = pCur->next; 
	
	delete P;

	return 0;

}

void PrintList(item* pFirst, int Direction)

//Вывод на экран всех элементов списка //Direction - выбор направления: //DIR - в прямом направлении //BACK - в обратном направлении
{

	if (Direction == BACK)

	{

		if (pFirst != 0)

		{

			PrintList(pFirst->next, BACK); puts(pFirst->key);

		}

	}

	else

	{

		while (pFirst != 0)

		{

			puts(pFirst->key); pFirst = pFirst->next;

		}
	}

}

void DeleteDblItems(item* pFirst)

//удаление повторяющихся элементов списка

{

	item* P2;

	for (; pFirst && pFirst->next; pFirst = pFirst->next) while (!FindItem(pFirst->next, P2, pFirst->key))

		DeleteItem(pFirst->next, P2);

}

int CountItems(item* pFirst)

//Возвращает количество элементов

{

	int i = 0;

	for (; pFirst; pFirst = pFirst->next) i++;

	return i;

}

void SortList(item*& pFirst)

//Сортировка списка по алфавиту

{

	//пустой или из 1 элемента

	if (pFirst == 0 || pFirst->next == 0) return;

	//сортируем по алгортиму выбора, //пропуская первый элемент

	item* pNew = 0;

	item* P;

	item* pMin;

	item* pPrev; //предшествующий минимальному элементу

	while (pFirst->next != 0)

	{

		P = pFirst->next; pPrev = pFirst; while (P->next != 0)

		{

			if (strcmp(pPrev->next->key, P->next->key) < 0) pPrev = P;

			P = P->next;

		}

		P = pPrev;

		pMin = pPrev->next; P->next = P->next->next; pMin->next = pNew;

		pNew = pMin;

	}

	//теперь ставим первый элемент на нужное место //по методу вставки

	pFirst->next = pNew; P = pFirst;

	if (strcmp(pFirst->key, pFirst->next->key) < 0) return; //pFirst - минимальный

	do

		P = P->next;

	while (P->next != 0 && strcmp(P->next->key, pFirst->key) < 0); pPrev = P->next; //pPrev в качестве промежуточной переменной

	P->next = pFirst; pFirst->next = pPrev; pFirst = pNew;

}

item* LinkLists(item* pFirst1, item* pFirst2) //Объединение списков

{

	item* pCFirst1 = CopyList(pFirst1); 
	item* pCFirst2 = CopyList(pFirst2);
	item* pCLast1 = pCFirst1;
	if (pCLast1 != 0)

	{

		while (pCLast1->next != 0)

		pCLast1 = pCLast1->next; //доходим до конца списка 
		pCLast1->next = pCFirst2; //связываем списки

	}

	else

		pCFirst1 = pCFirst2; 

		return pCFirst1;

}

item* SubtrLists(item* pFirst1, item* pFirst2)

//Возвращает указатель на результат вычитания списка pFirst2 из списка pFirst1

{

	item* pNewFirst = 0; item* P2;

	for (; pFirst1; pFirst1 = pFirst1->next)

		//если текущий элемент не найден во втором списке //то добавляем его в новый список

		if (FindItem(pFirst2, P2, pFirst1->key) != 0) AddItem(pNewFirst, pFirst1->key);

	return pNewFirst;

}

item* CrossLists(item* pFirst1, item* pFirst2)

//Возвращает указатель на результат вычитания списка pFirst2 из списка pFirst1

{

	item* pNewFirst = 0; item* P2;

	for (; pFirst1; pFirst1 = pFirst1->next)

		//если текущий элемент найден во втором списке //то добавляем его в новый список

		if (FindItem(pFirst2, P2, pFirst1->key) == 0) AddItem(pNewFirst, pFirst1->key);

	return pNewFirst;

}

int SaveList(item* pFirst, FILE* F)

//Сохранение списка в файл

{

	if (F == 0) return 1; while (pFirst != 0)

	{

		fputs(pFirst->key, F); fputc('\n', F);

		pFirst = pFirst->next;

	}

	fputc('\0', F); return 0;

}

int OpenList(item*& pFirst, FILE* F)

//загрузка списка из файла

{

	if (F == 0) return 1;

	//буфер максимально допустимой длины
	char strBuf[STR_LEN];

	int i;

	//считываем первую строку,

	//чтобы впоследствии не потерять указатель pFirst 

	pFirst = new item;

	//через буфер, чтобы не выделять лишнюю память в списке 
	fgets(strBuf, STR_LEN, F);

	strBuf[strlen(strBuf) - 1] = '\0';
	
	
	pFirst->key = new char[strlen(strBuf)];

	strcpy(pFirst->key, strBuf);
	
	item* P = pFirst;

	P->next = 0;

	//считываем остальные строки 
	for(;;)

	{

		if (*(fgets(strBuf, STR_LEN, F)) == '\0') return 0; strBuf[strlen(strBuf) - 1] = '\0';

		P->next = new item; P = P->next;

		P->key = new char[strlen(strBuf)]; strcpy(P->key, strBuf);

		P->next = 0;

	}

	return 0;

}

void Menu1()
{

	const char* MENU_1 =
		"______\n\n  1 - New list\n \ 2 - Open list\n \ Esc - Exit\n";


	char Key;

	char FileName[FN_LEN]; item* pL1;

	FILE* F;

	for (;;)

	{

		system("cls"); 

		puts(MENU_1);
		
		pL1 = 0;

		Key = getch(); 

		switch (Key)
		{

		case '1':

		{

			Menu2(pL1); break;

		}

		case '2':

		{

			system("cls");

			printf("Enter the name of file: \n");

			gets_s(FileName);

			F = fopen(FileName, "r"); if (!F)

			{

				printf("Error open file");
				
				getch();

				break;

			}

			OpenList(pL1, F);

			fclose(F);
			
			Menu2(pL1); 
			
			break;

		}

		case 27:

		{

			return;

		}

		default:

		{
			system("cls");

			printf("Wrong instruction\n\nPress any key");
			
			getch();

			break;

		}

		}

	}

}

void Menu2(item*& pL1)

{

	const char* MENU_2 = "______\n\n \ 1 - Save list\t\t 7 - Change print direction\n \ 2 - Add item\t\t 8 - Link with other list\n \ 	3 - Find item\t\t 9 - Cross with other list\n \ 4 - Count items\t 0 - Subtract other list\n \	5 - Sort list\t\t Esc - Close list\n \ 6 - Delete double items\n";

		item * pL2; 

		item* pL3; 

		item* pCur;

	char Key, FileName[FN_LEN], strBuf[STR_LEN]; int Direction = DIR;

	FILE* F;

	for (;;)

	{

		system("cls"); PrintList(pL1, Direction); puts(MENU_2);

		Key = getch(); 

		switch (Key)

		{

		case '1':

		{

			system("cls");

			printf("Enter the name of file: \n"); gets_s(FileName);

			if (!(F = fopen(FileName, "w")))

			{

				printf("Error open file\n\nPress any key");
				
				getch();

				break;

			}

			SaveList(pL1, F); 

			fclose(F);

			break;

		}

		case '2':

		{

			system("cls");

			printf("Enter the string: \n");

			gets_s(strBuf);

			AddItem(pL1, strBuf);

			break;

		}

		case '3':

		{

			system("cls");

			printf("Enter the string: \n"); 

			gets_s(strBuf);

			switch (FindItem(pL1, pCur, strBuf))

			{

			case 1:

			{
				system("cls");

				printf("Empty list\n\nPress any key");

				getch();

				break;

			}

			case 2:

			{

				system("cls");

				printf("No such item\n\nPress any key"); 

				getch();

				break;

			}

			default:

				Menu3(pL1, pCur);

			}

			break;

		}

		case '4':
		{

			system("cls");

			printf("%i items\n\nPress any key", CountItems(pL1));

			getch();

			break;

		}

		case '5':

		{

			SortList(pL1); break;

		}

		case '6':

		{

			DeleteDblItems(pL1); break;

		}

		case '7':

		{

			Direction = -(Direction); break;

		}

		case '8':

		{

			system("cls");

			printf("Enter the name of file: \n"); gets_s(FileName);

			F = fopen(FileName, "r"); 

			if (!F)
			{

				printf("Error open file\n\nPress any key");

				getch();

				break;

			}

			OpenList(pL2, F);
			fclose(F);

			pL3 = LinkLists(pL1, pL2); DeleteList(pL2); Menu2(pL3);

			break;

		}

		case '9':

		{

			system("cls");

			printf("Enter the name of file: \n"); gets_s(FileName);

			F = fopen(FileName, "r"); if (!F)

			{

				printf("Error open file\n\nPress any key");

				getch();

				break;

			}

			OpenList(pL2, F); fclose(F);

			pL3 = CrossLists(pL1, pL2); DeleteList(pL2); Menu2(pL3);

			break;

		}

		case '0':

		{

			system("cls");

			printf("Enter the name of file: \n"); gets_s(FileName);

			F = fopen(FileName, "r"); if (!F)

			{

				printf("Error open file\n\nPress any key"); getch();

				break;

			}

			OpenList(pL2, F); fclose(F);

			pL3 = SubtrLists(pL1, pL2); DeleteList(pL2); Menu2(pL3);

			break;

		}

		case 27:

		{

			DeleteList(pL1); return;

		}

		default:

		{

			system("cls");

			printf("Wrong instruction\n\nPress any key"); getch();

			break;

		}

}

}

}

void Menu3(item*& pL1, item*& pCur)

{

	const char* MENU_3 = "______\n\n \	1 - Delete item\n \ Esc - Back\n";

		char Key;

	for (;;)

	{

		system("cls"); puts(pCur->key); puts(MENU_3); Key = getch(); switch (Key)

		{

		case '1':

		{

			DeleteItem(pL1, pCur); return;

		}
		case 27:

		{

			return;

		}

		default:

		{

			system("cls");

			printf("Wrong instruction\n\nPress any key"); getch();

			break;

		}

		}

	}

}