#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
};

void printTaskDescription() {
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "***UZDUOTIES APRASYMAS***" << endl;
    cout << "Sukurti vienkrypti ciklini sarasa, realizuojant elemento iterpimo, pasalinimo " << endl;
    cout << "spausdinimo bei paieskos funkcijas. Perkelti to sąrašo visus elementus į dvejetainį medį." << endl;
    cout << "Atspausdinti visus dvejetainio medžio elementus." << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
}

int getChoice() {
    cout << "\nCHOOSE AN OPTION: " << endl;
    cout << "1 - insert an element" << endl;
    cout << "2 - delete an element" << endl;
    cout << "3 - find an element" << endl;
    cout << "4 - print the list" << endl;
    cout << "5 - move all elements to binary tree" << endl;
    cout << "6 - print the binary tree" << endl;
    cout << "7 - leave the program" << endl;
    cout << "\nEnter your choice: ";
    int choice;
    cin >> choice;
    while(cin.fail()) {
        cout << "\nThere was no such choice.";
        cin.clear();
        cin.ignore(256,'\n');
        cout << "\nEnter choice from meniu above (1-7): ";
        cin >> choice;
    }
    return choice;
}

int getSize() {
    cout << "Enter the size of your list: ";
    int size;
    cin >> size;
    return size;
}

Node* createList(int size) {
    Node *head = new Node();
    Node *tail = head;
    
    for ( int x = 1; x <= size; x++) {
        cout << "Enter a number: ";
        int number;
        cin >> number;
        if (x == 1) {
            head->data = number;
        } else {
            Node *current = new Node();
            current->data = number;
            tail->next = current;
            tail = tail->next;
            tail->next = head;
        }
    }
    return head;
}

void printList(Node *head) {
    Node *current = head;
    cout << "[";
    bool shouldContinue = true;
    while (shouldContinue) {
        if (current->next != head) {
            cout << current->data << ", ";
            current = current->next;
        } else {
            cout << current->data << "]" << endl;
            shouldContinue = false;
        }
    }
}

Node* insertElement(Node *head) {
    cout << "Enter wanted position for new element (starting position is 0): ";
    int position;
    cin >> position;
    cout << "Enter new element: ";
    int newValue;
    cin >> newValue;

    if (position == 0) {
        Node *newNode = new Node();
        newNode->data = newValue;
        Node *last = head;
        while (last->next != head) {
            last = last->next;
        }
        last->next = newNode;
        newNode->next = head;
        return newNode;
    }

    Node *current = head;
    for (int x = 0; x != position - 1; x++) {
        current = current->next;
    }
    Node *newNode = new Node();
    newNode->data = newValue;
    Node *temporary = current->next;
    current->next = newNode;
    newNode->next = temporary;
    return head;
}

Node* deleteElement(Node *head) {
    cout << "Enter position of the element to be deleted: ";
    int position;
    cin >> position;

    Node *current = head;

    if (position == 0) {
        Node *removable = head;
        while (current->next != head) {
            current = current->next;
        }
        head = head->next;
        current->next = head;
        removable->next = NULL;
        free(removable);
    } else {
        for (int x = 0; x != position - 1; x++) {
            current = current->next;
        }
            Node *removable = current->next;
            current->next = current->next->next;
            removable->next = NULL;
            free(removable);
    }
    return head;
}

void findElement(Node *head) {
    cout << "Enter value of an element you want to find: ";
    int elementToFind;
    cin >> elementToFind;

    Node *current = head;

    bool shouldContinue = true;
    while (shouldContinue) {
        if (current->data == elementToFind) {
            cout << "*Element '" << elementToFind << "' was found in your list*" << endl;
            shouldContinue = false;
        } else if (current->next == head && current->data != elementToFind) {
            cout << "*Element '" << elementToFind << "' was NOT found in your list*" << endl;
            shouldContinue = false;
        } else {
            current = current->next;
        }
    }
}

struct Tree {
    int data;
    Tree *left;
    Tree *right;
};

Tree* insertRoot(int data) {
    Tree *root = new Tree();
    root->data = data;
    return root;
}

Tree* insertBranch(Tree *root, int element) {
    if (root == NULL) {
        return insertRoot(element);
    } else if (element > root->data) {
        root->right = insertBranch(root->right, element);
    } else if (element < root->data) {
        root->left = insertBranch(root->left, element);
    }
    return root;
}

void printTree(Tree *root) {
    if (root != NULL) {
        printTree(root->left);
        cout << " " << root->data;
        printTree(root->right);
    }
}

int main() {
    printTaskDescription();
    cout << "***WELCOME TO SIMONA'S LIST CREATOR***" << endl;
    cout << "\n*Start by creating a list*\n" << endl;
    int size = getSize();
    Node *head = createList(size);
    cout << "\n*You have created your list*\n" << endl;

    Tree *root;

    bool shouldContinue = true;
    while (shouldContinue) {
        int choice = getChoice();

        if (choice == 1) {
            cout << "\n*You have chosen to insert an element*\n" << endl;
            head = insertElement(head);
            cout << "\n*You have inserted an element into your list*\n" << endl;
        } else if (choice == 2) {
            cout << "\n*You have chosen to delete an element*\n" << endl;
            head = deleteElement(head);
            cout << "\n*You have deleted an element from your list*\n" << endl;
        } else if (choice == 3) {
            cout << "\n*You have chosen to find an element*\n" << endl;
            findElement(head);
        } else if (choice == 4) {
            cout << "\n*You have chosen to print the list*\n" << endl;
            cout << "This is your list: ";
            printList(head);
        } else if (choice == 5) {
            cout << "\n*You have chosen to move all elements to binary tree*\n" << endl;

            root = insertRoot(head->data);

            Node *current = head->next;
            bool shouldContinue2 = true;
            while (shouldContinue2) {
                insertBranch(root, current->data);
                current = current->next;
                if (current == head) {
                    shouldContinue2 = false;
                }
            }
            cout << "\n*You have moved all elements to binary tree*\n" << endl;
        } else if (choice == 6) {
            cout << "\n*You have chosen to print the binary tree*\n" << endl;
            cout << "This is your binary tree: ";
            printTree(root);
            cout << endl;
        } else if (choice == 7) {
            cout << "\n*You have chosen to leave the program*\n" << endl;
            cout << "Thank you for using my program.\nSee you next time!" << endl;
            shouldContinue = false;
        } else {
            cout << "There was no such choice.\nPlease, check your input and try again." << endl;
        }
    }
    return 0;
}