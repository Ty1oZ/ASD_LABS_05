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

LinkedList mergeSortedLists(LinkedList& list1, LinkedList& list2) {
    LinkedList mergeList;
    Node* header1 = list1.head;
    Node* header2 = list2.head;

    while (header1 != nullptr || header2 != nullptr) {
        if (header1 == nullptr) {
            mergeList.addToEnd(header2->data);
            header2 = header2->next;
        }
        else if (header2 == nullptr) {
            mergeList.addToEnd(header1->data);
            header1 = header1->next;
        }
        else if (header1->data <= header2->data) {
            mergeList.addToEnd(header1->data);
            header1 = header1->next;
        }
        else {
            mergeList.addToEnd(header2->data);
            header2 = header2->next;
        }
    }

    return mergeList;

}


int main() {
    LinkedList list1;
    list1.addToEnd(1);
    list1.addToEnd(2);
    list1.addToEnd(3);
    list1.addToEnd(4);

    LinkedList list2;
    list2.addToEnd(5);
    list2.addToEnd(6);
    list2.addToEnd(7);
    list2.addToEnd(8);

    LinkedList mergeList = mergeSortedLists(list1, list2);
    cout << "Merged list: ";

    mergeList.print();

	return 0;
}  