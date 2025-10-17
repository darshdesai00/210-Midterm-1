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

    // gos through the list and deletes the first node that has the given value
    void delete_val(int value) {
        // if the list is empty, nothing to delete
        if (!head) return;

        Node* temp = head;  // tart from the beginning of the list
        
        // move through the list until we find the node with the value we want
        while (temp && temp->data != value)
            temp = temp->next;

        // if we reached the end and didn’t find it, just stop here
        if (!temp) return; 

        // if there's a node before this one, link it to the node after
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;  // if deleting the first node, move head up

        // if there's a node after this one, link it back to the node before
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;  // if deleting the last node, move tail back

        delete temp;  // elete the node from memory
    }

    // deletes a node from a specific position in the list
    void delete_pos(int pos) {
        // if the list is empty, we can't delete anything
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        // if they want to delete the first node, just use pop_front
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;  // start at the first node
    
        // move forward through the list until we reach the given position
        for (int i = 1; i < pos; i++) {
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }

        // if we went too far and didn’t find the position
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        // if it's the last node in the list, just use pop_back
        if (!temp->next) {
            pop_back();
            return;
        }
    
        // connect the nodes before and after this one to skip it
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;

        delete temp;  // remove that node from memory
    }

    // push_back() - adds a new node at the END of the list
    void push_back(int v) {
        Node* newNode = new Node(v); // make a new node with given value

        // if list is empty, this is the first node
        if (!tail)
            head = tail = newNode;
        else {
            // connect new node after the current tail
            tail->next = newNode;
            newNode->prev = tail;

            // move tail pointer to the new node
            tail = newNode;
        }
    }
    
    // push_front() - adds a new node at the FRONT of the list
    void push_front(int v) {
        Node* newNode = new Node(v); // make a new node with given value

        // if list is empty, it becomes both head and tail
        if (!head)
            head = tail = newNode;
        else {
            // connect new node before the current head
            newNode->next = head;
            head->prev = newNode;

            // move head pointer to the new node
            head = newNode;
        }
    }
    
    // pop_front() - removes the first node in the list
    void pop_front() {
        // if list is empty, nothing to remove
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head; // keep track of the node being deleted

        // if there’s more than one node
        if (head->next) {
            head = head->next;   // move head pointer to the next node
            head->prev = nullptr; // new head has no previous node
        }
        else
            head = tail = nullptr; // if only one node, list becomes empty

        delete temp; // free memory of the old head node
    }

    // pop_back() - removes the last node in the list
    void pop_back() {
        // if list is empty, nothing to remove
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = tail; // keep track of the node being deleted

        // if there’s more than one node
        if (tail->prev) {
            tail = tail->prev;   // move tail pointer one node back
            tail->next = nullptr; // new tail has no next node
        }
        else
            head = tail = nullptr; // if only one node, list becomes empty

        delete temp; // free memory of the old tail node
    }

    // destructor - called automatically when the list is destroyed
    // goes through and deletes all remaining nodes to free memory
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;    // start at the first node
            head = head->next;    // move to the next node
            delete temp;          // delete the old one
        }
    }

    // print() - goes through the list and prints all node values
    void print() {
        Node* current = head;

        // if list is empty, say so
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }

        // loop through the list and print each value
        while (current) {
            cout << current->data << " ";
            current = current->next; // move to the next node
        }

        cout << endl; // new line after printing everything
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

    // every_other_element() - prints every other element (skips one each time)
    void every_other_element() {
        Node* current = head;
        bool skip = false; // alternates between printing and skipping
        cout << "Every other element: ";
        while (current) {
            if (!skip)
                cout << current->data << " ";
            skip = !skip; // flips between true/false each loop
            current = current->next;
        }
        cout << endl;
    }
};
 
    int main() {
    // create a list and add sample data using 5 values to the list using "pushback"
    DoublyLinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);

    cout << "Full list: "; // prints the entire list from front to back 
    list.print();

    cout << "Reverse list: "; // prints the entire list from back to front 
    list.print_reverse();

    cout << endl << "Testing every_other_element():" << endl; // shows "every_other_element()" outputs
    list.every_other_element();

    cout << endl << "Midterm finished successfully." << endl; // message for my own personal confirmation purposes 

    return 0;
}
