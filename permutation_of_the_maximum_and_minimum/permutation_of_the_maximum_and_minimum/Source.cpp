#include <iostream>
#include <stdexcept>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear();
    }

    void addToEnd(int value) {
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

void permutationMaxAndMin(LinkedList& list) {
    if (list.head == nullptr || list.head->next == nullptr) {
        return;
    }

    Node* maxNode = list.head;
    Node* minNode = list.head;
    Node* current = list.head;

    Node* prevMax = nullptr;
    Node* prevMin = nullptr;
    Node* prev = nullptr;



    while (current != nullptr) {
        if (current->data > maxNode->data) {
            maxNode = current;
            prevMax = prev;
        }
        if (current->data < minNode->data) {
            minNode = current;
            prevMin = prev;
        }
        prev = current;
        current = current->next;
    }

    if (maxNode == minNode) {
        return;
    }


    if (prevMax != nullptr) {
        prevMax->next = minNode;
    }
    if (prevMin != nullptr) {
        prevMin->next = maxNode;
    }

    Node* temp = maxNode->next;
    maxNode->next = minNode->next;
    minNode->next = temp;

    // if prev == nullptr
    if (list.head == maxNode) {
        list.head = minNode;
    }
    else if (list.head == minNode) {
        list.head = maxNode;
    }
}

int main() {
    LinkedList list1;
    list1.addToEnd(2);
    list1.addToEnd(5);
    list1.addToEnd(3);
    list1.addToEnd(1);

    cout << "Before: " << '\n';
    list1.print();

    permutationMaxAndMin(list1);
    cout << "Permutation list: ";
    list1.print();

    return 0;
}