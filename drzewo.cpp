#include <iostream>
#include <Windows.h>
using namespace std;

int* tablica = new int[16384];
bool* zapelniony = new bool[16384];//musze tutaj stworzyc taka zmienna poniewaz false/null jest domyslnie uznawany jako 0 a wiec gdy w tablicy tablica mam 0 to nie wiem czy to pusta miejsce w tabeli (NULL) czy zapisane 0; daje () aby wypelnic zerami
int rozmiar = 16384;

//usun liczbe i znajdowanie poprzednika i nastepnika do poprawienia

void dodajLiczbe(int liczba) {
	int i = 1;
	while (zapelniony[i] == true) {//zapelnione miejsce wiec ide w lewo lub prawo
		if (liczba < tablica[i]) {//idz w lewo
			i = i * 2;
		}
		else {//jak bedzie rowne to mozemy isc zarowno w lewo jak i w prawo byle tylko ciagle w ta sama strone isc;
			i = (i * 2) + 1;
		}
	}
	if (i <= rozmiar) {
		tablica[i] = liczba;
		zapelniony[i] = true;
	}
	else {
		"Za mala tablica.";
	}


}

int znajdzLiczbe(int liczba, bool wypisz) {//od drugiej zmiennej zalezy czy tylko zwroci czy rowniez wypisze
	for (int i = 1; i <= rozmiar; i++) {
		if (tablica[i] == liczba) {
			if (wypisz == true && zapelniony[i] == true) cout<<"Indeks szukanej liczby to:" << i << endl;//miejsce znalezienia liczby
			return i;
		}
	}
	cout << "Nie ma takiej liczby w drzewku" << endl;//tutaj wejdzie tylko jesli nic nie znajdzie
}

bool istniejeLiczba(int liczba) {//sprawdzam czy taka liczba istnieje w drzewku (np. w drzewku mam tylko liczbe 1 a chce usunac liczbe 4)
	for (int i = 1; i <= rozmiar; i++) {
		if (tablica[i] == liczba) {
			if (zapelniony[i] == true) return true;//miejsce znalezienia liczby
		}
	}
	return false;
}

int lewySyn(int i) {
	i = i * 2;
	return i;
}

int prawySyn(int i) {
	i = (i * 2) + 1;
	return i;
}

int znajdzMinLiczbe(int i, bool wypisz) {//i - od ktorej liczby zaczynamy (jak np. chcemy znalezc najmniejsza wartosc w konkretnej galezi)
	while (zapelniony[lewySyn(i)] != false) {
		i = i * 2;
	}
	if(wypisz) cout<<"Najmniejsza liczba z tablicy to: " << tablica[i] << endl;//wypisanie najnizszej wartosci
	return i;
}

int znajdzMaxLiczbe(int i, bool wypisz) {
	while (zapelniony[lewySyn(i)] != false) {
		i = (i * 2)+1;
	}
	if(wypisz) cout<<"Najwieksza liczba z tablicy to :" << tablica[i] << endl;//wypisanie najnizszej wartosci
	return i;
}

int znajdzPoprzednikNastepnik(int liczba, bool poprzednik, bool wypisz) {//poprzednik = true to szukamy poprzednika a jesli false to nastepnika; wypisz = true wypisujemy wynik;
	int i;
	bool istnieje = istniejeLiczba(liczba);
	if (istnieje) i = znajdzLiczbe(liczba, 0);
	else {//jesli liczba nie istnieje
		cout << "Podana liczba nie znajduje sie w drzewku" << endl;
		return 0;//cos musze zwrocic
	}
	int ojciec = i / 2;
	if (poprzednik) {//szukamy poprzednika
		if (zapelniony[lewySyn(i)] != NULL) {//jesli mamy lewego syna to najwieksza wartosc w tej galezi jest poprzednikiem
			if (wypisz) cout << "Poprzednik podanej liczby to: " << tablica[znajdzMaxLiczbe(lewySyn(i), 0)] << endl;//wyswietlam liczbe
			return znajdzMaxLiczbe(lewySyn(i), 0);//zwracam indeks
		}
		else {//gdy nie mamy lewgo syna to szukamy ojca ktory ma nasza galaz po prawej stronie
			while (ojciec >= 1) {//jesli mamy tylko 1 element o i=1 oraz ojciec =0 czyli ten while sie nie wykona
				if (i == prawySyn(ojciec)) {//jesli tablica[i] jest prawym synem ojca to ojciec jest poprzednikiem
					if(wypisz) cout << "Poprzednik podanej liczby to: " << tablica[ojciec] << endl;
					return tablica[ojciec];
				}
				i = ojciec;//jesli if nie zadziala to sprawdzamy kolejna pare wyzej czyli syn staje sie ojcem;
				ojciec /= 2;
			}
			cout << "Ta liczba nie ma poprzednika" << endl;//jesli petla sie skonczy i if nigdy nie wejdzie to znaczy ze doszlismy do korzenia i nie ma nastepnika czyli wyswietlamy -
		}
	}else {//szukamy nastepnika
		if (zapelniony[prawySyn(i)] != NULL) {//mamy prawego syna wiec najmniejsza wartosc w tej galezi bedzie nastepnikiem
			if(wypisz) cout << "Nastepnik podanej liczby to: " << tablica[znajdzMinLiczbe(prawySyn(i), 0)] << endl;
			return znajdzMinLiczbe(prawySyn(i), 0);
		}
		else {//gdy nie mamy prawego syna to szukamy ojca ktory ma nasza galaz po lewej stronie
			while (ojciec >= 1) {
				if (i == lewySyn(ojciec)) {//jesli poprzedni element czyli 
					if(wypisz) cout << "Nastepnik podanej liczby to: " << tablica[ojciec] << endl;
					return tablica[ojciec];
				}
				i = ojciec;//jesli if nie zadziala to sprawdzamy kolejna pare wyzej czyli syn staje sie ojcem;
				ojciec /= 2;
			}
			cout << "Podana liczba nie ma nastepnika" << endl;//jesli petla sie skonczy i if nigdy nie wejdzie to znaczy ze doszlismy do korzenia i nie ma nastepnika czyli wyswietlamy -
		}
	}
}

void usunLiczbe(int liczba) {
	int i;
	bool istnieje = istniejeLiczba(liczba);
	if (istnieje) i = znajdzLiczbe(liczba, 0);
	else {//jesli liczba nie isteje
		cout << "Taka liczba nie istnieje" << endl;
		Sleep(3000);
		return;
	}
	//usuniecie liczby
	int potomek = 0;
	if (zapelniony[lewySyn(i)] != NULL) potomek++;

	if (zapelniony[prawySyn(i)] != NULL) potomek++;
	switch (potomek) {
	case 0: {
		tablica[i] = NULL;
		zapelniony[i] = false;
		break;
	}
	case 1: {
		if (tablica[i * 2] != NULL) {
			tablica[i] = tablica[i * 2];
			tablica[i * 2] = NULL;
			zapelniony[i * 2] = false;
		}
		else {
			tablica[i] = tablica[(i * 2) + 1];
			tablica[(i * 2) + 1] = NULL;
			zapelniony[(i * 2) + 1] = false;
		}
		break;
	}
	case 2: {//gdy sa 2 dzieci to wtedy ta liczba napewno ma nastepnik i poprzednik wiec przenosimy w usuwane miejsce nastepnik(z poprzednikiem chyba by tez zadzialalo; nastepnik nie ma dziecka wiec nastepnik po prostu usuwamy)
		tablica[i] = tablica[znajdzPoprzednikNastepnik(tablica[i], 0, 0)];
		tablica[znajdzPoprzednikNastepnik(tablica[i], 0, 0)] = NULL;
		zapelniony[znajdzPoprzednikNastepnik(tablica[i], 0, 0)] = false;
		break;
	}
	}

}


/*Preorder, Inorder, Postorder*/
void Preorder(int i); void Inorder(int i); void Postorder(int i);

void sprawdzLewo(int i, int typ) {//schodze nizej na lewo; jesli jest puiste to nic nie robie; jesli jest cos to wywoluje funkcje
	i = i * 2;
	if (zapelniony[i] == false) return;
	if (typ == 0) Preorder(i);
	else if (typ == 1) Inorder(i);
	else if (typ == 2) Postorder(i);
}

void sprawdzPrawo(int i, int typ) {//schodze nizej na prawo; jesli jest puiste to nic nie robie; jesli jest cos to wywoluje funkcje
	i = (i * 2) + 1;
	if (zapelniony[i] == false) return;
	if (typ == 0) Preorder(i);
	else if (typ == 1) Inorder(i);
	else if (typ == 2) Postorder(i);
}

void Preorder(int i) {
	cout << tablica[i] << " ";
	sprawdzLewo(i, 0);
	sprawdzPrawo(i, 0);
}

void Inorder(int i) {
	sprawdzLewo(i, 1);
	cout << tablica[i] << " ";
	sprawdzPrawo(i, 1);
}

void Postorder(int i) {
	sprawdzLewo(i, 2);
	sprawdzPrawo(i, 2);
	cout << tablica[i] << " ";
}

void wyzerujTablice() {
	//wypelnienie tablicy NULL-ami
	for (int i = 0; i <= rozmiar; i++) {
		tablica[i] = NULL;
		zapelniony[i] = false;
	}
}

void menu() {
	cout << "------------------------------" << endl;
	cout << "SYMULATOR DRZEWKA BINARNEGO" << endl;
	cout << "------------------------------" << endl;

	int wiel_p = 1, wiel = 1;
	for (int i = 1; i < 16; i++) {
		if (zapelniony[i] == true) cout << "Tablica [" << i << "]" << " = " << tablica[i] << "   ";
		else cout << "Tablica [" << i << "]" << " = NULL" << "   ";
		wiel--;
		if (wiel == 0) {
			cout << endl;
			wiel_p = wiel_p * 2;
			wiel = wiel_p;
		}
	}
	cout << endl;
	cout << "OPCJE DO WYBORU:" << endl;
	cout << "I *liczba typu int* - dodanie liczby" << endl;
	cout << "D *liczba typu int* - usuniecie pierwszej napotkanej liczby" << endl;
	cout << "S *liczba typu int* - wyszukanie pierwszej napotkanej liczby" << endl;
	cout << "X 0 - znalezienie najmniejsze liczby w drzewku" << endl;
	cout << "X 1 - znalezienie najwiekszej liczby w drzewku" << endl;
	cout << "N *liczba typu int* - znalezienie nastepnika pierwszej napotkanej liczby w drzewku" << endl;
	cout << "P *liczba typu int* - znalezienie poprzednika pierwszej napotkanej liczby w drzewku" << endl;
	cout << "R 0 - wypisanie liczb z dzrzewka za pomoca algorytmu Inorder" << endl;
	cout << "R 1 - wypisanie liczb z dzrzewka za pomoca algorytmu Preorder" << endl;
	cout << "R 2 - wypisanie liczb z dzrzewka za pomoca algorytmu Postorder" << endl<<endl;
	cout << "Wybieram: _ _\b\b\b";
	int  liczba;
	char komenda;

	cin >> komenda >> liczba;
	switch (komenda) {
		case 'I': {//dodanie liczby
			dodajLiczbe(liczba);
			break;
		}
		case 'D': {//usuniecie liczby
			usunLiczbe(liczba);
			break;
		}
		case 'S': {//wyszukanie liczby
			znajdzLiczbe(liczba, 1);
			Sleep(3000);
			break;
		}
		case 'X': {
			if (liczba == 0) znajdzMinLiczbe(1, 1);
			if (liczba == 1) znajdzMaxLiczbe(1, 1);
			Sleep(3000);
			break;
		}
		case 'N': {//znalezienie nastepnika
			znajdzPoprzednikNastepnik(liczba, 0, 1);
			Sleep(3000);
			break;
		}
		case 'P': {//znalezienie poprzednika
			znajdzPoprzednikNastepnik(liczba, 1, 1);
			Sleep(3000);
			break;
		}
		case 'R': {
			switch (liczba) {
			case 0: {
				Inorder(1);
				cout << endl;
				Sleep(3000);
				break;
			}
			case 1: {
				Preorder(1);
				cout << endl;
				Sleep(3000);
				break;
			}
			case 2: {
				Postorder(1);
				cout << endl;
				Sleep(3000);
				break;
			}
			}
			break;
		}
		default: {
			cout << "Zla komenda!" << endl;
			break;
		}
	}
	system("cls");
	komenda = NULL;
	liczba = NULL;
	menu();
}
int main() {
	wyzerujTablice();
	menu();
		

	

	return 0;
}