#include <iostream>
#include <vector>

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

void dfs(int currentVertex, vector<vector<int>>& adjacencyMatrix, vector<bool>& visited, LinkedList& result) {
    visited[currentVertex] = true;
    result.addToEnd(currentVertex);

    for (int i = 0; i < adjacencyMatrix[currentVertex].size(); ++i) {
        if (adjacencyMatrix[currentVertex][i] == 1 && !visited[i]) {
            dfs(i, adjacencyMatrix, visited, result);
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

    int numVertices = adjacencyMatrix.size(); 
    vector<bool> visited(numVertices, false); 
    LinkedList result; 

   
    dfs(3, adjacencyMatrix, visited, result);

   
    cout << "DFS: " << '\n';
    result.print();

    return 0;
}