#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

struct Node {
	int data;
	Node* next;

	Node(int value) : data(value), next(nullptr) {}
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
		int poppedValue = top->data;
		top = top->next;
		delete temp;
		size--;
		return poppedValue;
	}

	int peek() {
		if (isEmpty()) {
			throw underflow_error("Stack is empty");
		}
		return top->data;
	}

	void printStack() {
		Node* current = top;
		cout << "Stack status: ";
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << '\n';
	}
};

class LinkedList {
private:
    //Node* head;

public:
    Node* head;
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear(); 
    }

    void addToFront(int value) {
        try {
            Node* newNode = new Node(value);
            newNode->next = head;
            head = newNode;
        }
        catch (const bad_alloc& e) {
            cerr << "Memory allocation failed: " << e.what() << '\n';
            throw; 
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
            cerr << "Memory allocation failed: " << e.what() << '\n';
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
            cerr << "Memory allocation failed: " << e.what() << '\n';
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

    bool isEmpty() {
        return head == nullptr;
    }

};

void dfsIterative(int startVertex, vector<vector<int>>& adjacencyMatrix, LinkedList& result) {
    int numVertices = adjacencyMatrix.size();
    vector<bool> visited(numVertices, false);

    Stack stack;
    stack.push(startVertex);

    while (!stack.isEmpty()) {
        int currentVertex = stack.peek();
        stack.pop();

        if (!visited[currentVertex]) {
            visited[currentVertex] = true;
            result.addToEnd(currentVertex);

            for (int i = numVertices - 1; i >= 0; --i) {
                if (adjacencyMatrix[currentVertex][i] == 1 && !visited[i]) {
                    stack.push(i);
                }
            }
        }

    }
}


int main() {

    vector<vector<int>> adjacencyMatrix = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0}
    };

    LinkedList result;


    dfsIterative(3, adjacencyMatrix, result);

    cout << "DFS: " << '\n';
    result.print();

    return 0;
}