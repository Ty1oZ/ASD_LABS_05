#include <iostream>
#include <stdexcept>
using namespace std;

struct Node {
	int value;
	Node* next;

	Node(int value) : value(value), next(nullptr) {}
};

class Stack {
private:
	Node* top;
	int size;

public:
	Stack() : top(nullptr), size(0) {}

	~Stack() {
		while (!isEmpty()) {
			pop();
		}
	}

	bool isEmpty() {
		return top == nullptr;
	}

	int getSize() {
		return size;
	}

	void push(int value) {
		Node* newNode = new Node(value);
		newNode->next = top;
		top = newNode;
		size++;
	}

	int pop() {
		if (isEmpty()) {
			throw underflow_error("Attempt to delete from an empty stack");
		}
		Node* temp = top;
		int poppedValue = top->value;
		top = top->next;
		delete temp;
		size--;
		return poppedValue;
	}

	int peek() {
		if (isEmpty()) {
			throw underflow_error("Stack is empty");
		}
		return top->value;
	}

	void printStack() {
		Node* current = top;
		cout << "Stack status: ";
		while (current != nullptr) {
			cout << current->value << " ";
			current = current->next;
		}
		cout << '\n';
	}
};

int main() {
	Stack stack;

	
	int elements[] = { 15, 25, 35, 45, 55 };
	int n = sizeof(elements) / sizeof(elements[0]);

	for (int i = 0; i < n; ++i) {
		stack.push(elements[i]);
		stack.printStack(); 
	}

	
	cout << "Delete elements:" << endl;
	while (!stack.isEmpty()) {
		cout << "Deleted: " << stack.pop() << endl;
		stack.printStack(); 
	}

	return 0;
}