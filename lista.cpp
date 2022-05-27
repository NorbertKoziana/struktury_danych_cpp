#include <iostream>

using namespace std;

class Node{ 
public:
    int dane;
    Node* next_node;//to bêdzie wskaŸnik typu Node do kolejnego Node-a
};

void printList(Node* n) {//z jakiegos powodu tutaj nie dzialamy na oryginalnych zmiennych tylko na kopiach nie wiem dlaczego
    while (n!=NULL) {
        cout << n->dane << endl;
        n = n->next_node;
    }
}


//lista jednokierunkowa
int main()
{
    //tworzymy 3 wskaŸniki
    Node* head = new Node;
    Node* second = new Node;
    Node* third = new Node;

    head->dane = 1;//tak¹ strz³ke u¿ywamy gdy dzia³amy na wskaznikach;
    second->dane = 2;
    third->dane = 3;
    head->next_node = second;//second juz jest wkaznikiem wiec nie uzywam * czy &
    second->next_node = third;
    third->next_node = NULL;
    printList(head);


}
