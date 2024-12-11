#include <iostream>
#include <vector>
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
	Node* tail;

	LinkedList() : head(nullptr), tail(nullptr) {}

	~LinkedList() {
		clear();
	}

	void addToEnd(int value) {
		Node* newNode = new Node(value);
		if (head == nullptr) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
	}

	int removeFromFront() {
		if (head == nullptr) {
			throw underflow_error("Attempt to remove from an empty list");
		}
		Node* temp = head;
		int removedValue = head->data;
		head = head->next;
		if (head == nullptr) {
			tail = nullptr;
		}
		delete temp;
		return removedValue;
	}

	bool isEmpty() {
		return head == nullptr;
	}

	void clear() {
		while (!isEmpty()) {
			removeFromFront();
		}
	}

	void print() {
		Node* current = head;
		while (current != nullptr) {
			cout << current->data << " -> ";
			current = current->next;
		}
		cout << "NULLPTR " << '\n';
	}
};

void BFSIterative(int startVertex, vector<vector<int>>& adjacencyMatrix, LinkedList& result) {
	int numVertex = adjacencyMatrix.size();
	vector<bool> visited(numVertex, false);

	LinkedList queue;
	queue.addToEnd(startVertex);
	visited[startVertex] = true;
	
	while (!queue.isEmpty()) {
		int currentVertex = queue.removeFromFront();
		result.addToEnd(currentVertex);

		for (int i = 0; i < numVertex; ++i) {
			if (adjacencyMatrix[currentVertex][i] == 1 && !visited[i]) {
				queue.addToEnd(i);
				visited[i] = true;
			}
		}
	}
}

int main() {
	
	vector<vector<int>> adjacencyMatrix = {
		{0, 1, 0, 0, 1}, // 0
		{1, 0, 1, 1, 0}, // 1
		{0, 1, 0, 0, 0}, // 2
		{0, 1, 0, 0, 1}, // 3
		{1, 0, 0, 1, 0}  // 4
	};

	LinkedList result;

	BFSIterative(3, adjacencyMatrix, result);

	cout << "BFS result: " << endl;
	result.print();

	return 0;
}