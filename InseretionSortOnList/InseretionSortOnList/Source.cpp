#include <iostream>
#include <stdexcept>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    //Node* head;

public:
    Node* head;
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear(); // Освобождаем память перед удалением объекта
    }

    void addToFront(int value) {
        try {
            Node* newNode = new Node(value);
            newNode->next = head;
            head = newNode;
        }
        catch (const bad_alloc& e) {
            cerr << "Memory allocation failed: " << e.what() << endl;
            throw; // Передаем исключение дальше
        }
    }

    void addToEnd(int value) {
        try {
            Node* newNode = new Node(value);
            if (head == nullptr) {
                head = newNode;
            }
            else {
                Node* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
        catch (const bad_alloc& e) {
            cerr << "Memory allocation failed: " << e.what() << endl;
            throw;
        }
    }

    void addAfter(Node* prevNode, int value) {
        if (prevNode == nullptr) {
            return;
        }
        try {
            Node* newNode = new Node(value);
            newNode->next = prevNode->next;
            prevNode->next = newNode;
        }
        catch (const bad_alloc& e) {
            cerr << "Memory allocation failed: " << e.what() << endl;
            throw;
        }
    }

    void remove(int value) {
        if (head == nullptr) {
            return;
        }

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }

        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    Node* find(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULLPTR" << '\n';
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};


Node* sortedInsert(Node* sorted, Node* newNode) {
    if (sorted == nullptr || newNode->data < sorted->data) {
        newNode->next = sorted;
        return newNode;
    }

    Node* current = sorted;
    while (current->next != nullptr && current->next->data < newNode->data) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    return sorted;
}

void insertionSort(LinkedList& list) {
    if (list.head == nullptr || list.head->next == nullptr) {
        return;
    }

    Node* sorted = nullptr; // starting sorted list
    Node* current = list.head;

    while (current != nullptr) {
        Node* nextNode = current->next;
        sorted = sortedInsert(sorted, current);
        current = nextNode;
    }

    list.head = sorted;
}



int main() {
    LinkedList list1;
    list1.addToEnd(4);
    list1.addToEnd(14);
    list1.addToEnd(18);
    list1.addToEnd(5);
    list1.addToEnd(6);
    list1.addToEnd(325);
    list1.addToEnd(7);
    list1.addToEnd(5);
    list1.addToEnd(3);
    list1.addToEnd(1);

    cout << "List before sorted: " << '\n';
    list1.print();

    insertionSort(list1);

    cout << "List after sorted: " << '\n';
    list1.print(); // Исправленная строка

    return 0;
}