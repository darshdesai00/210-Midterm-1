#include <iostream>
using namespace std;
// Below are constants that were part of the intial starter code.
// The constants define min and max ranges for numbers and even list size.
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// The "DoublyLinkedList" class pretty much just stores integers 
// Nodes connected in both directions ("prev and next") pointers.
class DoublyLinkedList {
private:
    struct Node {
        int data; // integer value stored in the node
        Node* prev; // pointer to prev node
        Node* next; // pointer to next node
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; // stores the passed integr 
            prev = p; // assigns pointer to prev node 
            next = n; // assigns pointer to next node
        }
    };

    Node* head; // points to the 1st node in the list
    Node* tail; // points to the last node in the list

public:
    // constructor - starts with an empty list
    DoublyLinkedList() { 
        head = nullptr;   // no first node yet
        tail = nullptr;   // no last node yet
    }

    // insert_after() - inserts a new node after a given position
    void insert_after(int value, int position) {
        // check for invalid position
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value); // make a new node with given value

        // if list is empty, new node becomes both head and tail
        if (!head) {
            head = tail = newNode;
            return;
        }

        // start from head and move to the given position
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        // if position is past the end of the list
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // clean up unused node
            return;
        }

        // link the new node after the found node
        newNode->next = temp->next; // new node points to node after temp
        newNode->prev = temp;       // new node points back to temp

        // if temp was not the last node, connect next node's prev pointer
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // if temp was last, update tail

        // connect temp's next pointer to new node
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}
