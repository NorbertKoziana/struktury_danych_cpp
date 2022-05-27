#include <iostream>
#include <windows.h>
using namespace std;

int rozmiar = 0;// pisze tutaj a nie w mainie aby wszystkie funkcje mia³y dostêp do tej zmiennej; taka jakby zmienna globalna
int max_rozmiar=5;
int glowa = 0, ogon;//glowa to pierwsze zajete miejsce a ogon to pierwsze wolne miejsce na koncu

int* kolejka = new int[max_rozmiar];



void wyswietlMenu();

void wyswietlKolejke() {
	for (int i = glowa; i < glowa + rozmiar; i++) {//wyswietli rozmiar elementow zaczynajac od glowy
		cout << " " << kolejka[i%5];
	}
	cout << endl;
}

void push_front() {
	if (rozmiar < max_rozmiar) {
		cout << "Podaj liczbe ktora sie ma dodac na poczatku:";
		glowa--;//glowa u nas oznacza indeks poczatku ciagu a my chcemy dodac przed ciag i zmienic miejsce glowy
		if (glowa < 0) glowa = glowa + 5;//na zasadzie dzialania pierscienia; tutaj dajemy +5 zamiast modulo no bo ten trick z modulo nie za bardzo dziala dla ujemnych liczb tzn -1+5=4 a -1%5=-1
		cin >> kolejka[glowa];
		rozmiar++;
	}
	else {
		cout << "Za maly rozmiar kolejki" << endl;
		Sleep(2000);
	}

	wyswietlMenu();
}

void pop_front() {
	if (rozmiar > 0) {
		cout << "Podaj liczbe ktora sie ma usunac na poczatku:";
		kolejka[glowa] = NULL;
		rozmiar--;
		glowa++;
		if (glowa > 4) glowa = glowa % 5;//jesli glowa byl ostatni elemnt to niech glow¹ zostanie pierwszy element
	}
	else {
		cout << "Nie ma czego usuwac" << endl;
		Sleep(2000);
	}

	wyswietlMenu();
}

void push_back() {
	if (rozmiar < max_rozmiar) {
		ogon = glowa + rozmiar;
		if (ogon > 4) ogon = ogon % 5;
		cout << "Podaj liczbe ktora sie ma dodac na koncu:";
		cin >> kolejka[ogon];
		rozmiar++;

	}
	else {
		cout << "Za maly rozmiar kolejki" << endl;
		Sleep(2000);
	}

	wyswietlMenu();
}

void pop_back() {
	if (rozmiar > 0) {
		ogon = glowa + rozmiar;
		if (ogon > 4) ogon = ogon % 5;
		cout << "Podaj liczbe ktora sie ma usunac na koncu:";
		if (ogon - 1 < 0) kolejka[ogon - 1 + 5] = NULL;
		else kolejka[ogon - 1] = NULL;
		rozmiar--;
	}
	else {
		cout << "Nie ma czego usuwac" << endl;
		Sleep(2000);
	}

	wyswietlMenu();
}

void size() {
	cout << rozmiar;
	Sleep(2000);
	wyswietlMenu();
}

void empty() {
	if (rozmiar == 0) cout << "TRUE";
	else cout << "FALSE";
	Sleep(2000);
	wyswietlMenu();
}
void wyswietlMenu() {
	int wybor;
	system("cls");
	cout << "_________________" << endl;
	cout << "ZAWARTOSC Kolejki:" << endl;
	wyswietlKolejke();
	cout << "-----------------" << endl;
	cout << "Dostepne komendy:" << endl;
	cout << "1) push_front" << endl;
	cout << "2) pop_front" << endl;
	cout << "3) push_back" << endl;
	cout << "4) pop_back" << endl;
	cout << "5) size()" << endl;
	cout << "6) empty()" << endl;
	cin >> wybor;
	switch (wybor) {
		case 1: {
			push_front();
			break;
		}
		case 2: {
			pop_front();
			break;
		}
		case 3: {
			push_back();
			break;
		}
		case 4: {
			pop_back();
			break;
		}
		case 5: {
			size();
			break;
		}
		case 6: {
			empty();
			break;
		}
	}
}

int main() {
	
	

	//w sumie to wyszlo mi takie polaczenie kolejki i stosu; mozemy sobie w sumie wybrac czy nasz kontener ma dzialac na zasadzie FIFO czy LIFO
	wyswietlMenu();
	
	delete[] kolejka;
	return 0;
	}

