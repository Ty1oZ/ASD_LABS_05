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
        cout << "NULL" << endl;
    }
};

class Stack {
public:
    Node* top;

    Stack() : top(nullptr) {}

    ~Stack() {
        clear();
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (top == nullptr) {
            throw underflow_error("Attempt to pop from an empty stack");
        }
        Node* temp = top;
        int poppedValue = top->data;
        top = top->next;
        delete temp;
        return poppedValue;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

bool hasCycleUtil(int vertex, const vector<vector<int>>& adjacencyList, vector<bool>& visited, vector<bool>& recStack) {
    if (!visited[vertex]) {
        visited[vertex] = true;
        recStack[vertex] = true;

        for (int adjVertex : adjacencyList[vertex]) {
            if (!visited[adjVertex] && hasCycleUtil(adjVertex, adjacencyList, visited, recStack)) {
                return true;
            }
            else if (recStack[adjVertex]) {
                return true;
            }
        }
    }
    recStack[vertex] = false;
    return false;
}

bool hasCycle(const vector<vector<int>>& adjacencyList) {
    int numVertices = adjacencyList.size();
    vector<bool> visited(numVertices, false);
    vector<bool> recStack(numVertices, false);

    for (int i = 0; i < numVertices; i++) {
        if (hasCycleUtil(i, adjacencyList, visited, recStack)) {
            return true;
        }
    }
    return false;
}

void DFS(int vertex, const vector<vector<int>>& adjacencyList, vector<bool>& visited, Stack& stack) {
    visited[vertex] = true;

    for (int adjVertex : adjacencyList[vertex]) {
        if (!visited[adjVertex]) {
            DFS(adjVertex, adjacencyList, visited, stack);
        }
    }

    stack.push(vertex);
}

void topologicalSort(const vector<vector<int>>& adjacencyList, LinkedList& result) {
    if (hasCycle(adjacencyList)) {
        throw runtime_error("Graph contains a cycle. Topological sort not possible.");
    }

    int numVertices = adjacencyList.size();
    vector<bool> visited(numVertices, false);
    Stack stack;

    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            DFS(i, adjacencyList, visited, stack);
        }
    }

    while (!stack.isEmpty()) {
        result.addToEnd(stack.pop());
    }
}

int main() {
#include <vector>

    vector<vector<int>> adjacencyList = {
        {1, 2},    // 0 ->  1  2
        {3, 4},    // 1 ->  3  4
        {5},       // 2 ->  5
        {6},       // 3 ->  6
        {6},       // 4 ->  6
        {7},       // 5 ->  7
        {8},       // 6 ->  8
        {8},       // 7 ->  8
        {9},       // 8 ->  9
        {}         // 9 
    };

    LinkedList result;
    try {
        topologicalSort(adjacencyList, result);
        cout << "Topological Sort result: " << endl;
        result.print();
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}