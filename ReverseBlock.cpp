#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void push_back(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = tail = newNode;
            return;
        }

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void print() const {
        Node* current = head;

        while (current != nullptr) {
            cout << current->data;

            if (current->next != nullptr)
                cout << " <-> ";

            current = current->next;
        }

        cout << endl;
    }

    void printBackward() const {
        Node* current = tail;

        while (current != nullptr) {
            cout << current->data;

            if (current->prev != nullptr)
                cout << " <-> ";

            current = current->prev;
        }

        cout << endl;
    }

    void reverseInGroups(int k) {
        if(k <= 1) return;
        Node* a = head;
        Node* b = head;
        for(int i = 1; i < k && b != nullptr; i++, b = b->next);
        while(a != nullptr && b != nullptr){
            Node* siguiente = b->next;
            Node* anterior = a->prev;
            Node* actual = a;
            while(actual != siguiente){
                Node* temp = actual->next;
                actual->next = actual->prev;
                actual->prev = temp;
                actual = temp;
            }
            if(anterior != nullptr) anterior->next = b;
            else head = b;
            b->prev = anterior;
            a->next = siguiente;
            if(siguiente != nullptr) siguiente->prev = a;
            else tail = a;
            a = siguiente;
            b = a;
            for(int i = 1; i < k && b != nullptr; i++, b = b->next);
        }
    }
};

void runTest(int id, int n, int k, const string& expected) {
    DoublyLinkedList list;

    for (int i = 1; i <= n; i++)
        list.push_back(i);

    cout << "===== TEST " << id << " (n = " << n << ", K = " << k << ") =====" << endl;

    cout << "Original:    ";
    list.print();

    list.reverseInGroups(k);

    cout << "Resultado:   ";
    list.print();

    cout << "Esperado:    " << expected << endl;

    cout << "Hacia atras: ";
    list.printBackward();

    cout << endl;
}

int main() {

    runTest(1, 8, 3, "3 <-> 2 <-> 1 <-> 6 <-> 5 <-> 4 <-> 7 <-> 8");
    runTest(2, 6, 2, "2 <-> 1 <-> 4 <-> 3 <-> 6 <-> 5");
    runTest(3, 5, 3, "3 <-> 2 <-> 1 <-> 4 <-> 5");
    runTest(4, 5, 10, "1 <-> 2 <-> 3 <-> 4 <-> 5");
    runTest(5, 5, 1, "1 <-> 2 <-> 3 <-> 4 <-> 5");
    runTest(6, 6, 6, "6 <-> 5 <-> 4 <-> 3 <-> 2 <-> 1");

    return 0;
}
