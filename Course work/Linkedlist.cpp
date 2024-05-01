#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class Linkedlist {
    class Node {
    public: 
        Node* next = nullptr;
        int val;
        int passage;
    };
    Node* root = nullptr;
public:
    void addTail(int val) {
        if (root == nullptr) {
            root = new Node();
            root->val = val;
            root->passage = 1;
        }
        else {
            Node* n = root;
            while (n->next) {
                n = n->next;
            }
            n->next = new Node;
            n->next->val = val;
            n->next->passage = 1;
        }
    }
    void addHead(int val) {
        if (root == nullptr) {
            root = new Node();
            root->val = val;
            root->passage = 1;
        }
        else {
            Node* newRoot = new Node();
            newRoot->val = val;
            newRoot->passage = 1;
            newRoot->next = root; 
            root = newRoot; 
        }
    }
    int removeHead() {
        if (!root) {
            cout << "Not found"<<endl;
            return -1;
        }
        else {
            int val= root->val;
            Node* oldRoot = root;
            root = root->next;
            delete oldRoot;
            return val;
        }
    }

 void removedTail(){
    if (root != nullptr) {
        if (root->next == nullptr) { 
            delete root;
            root = nullptr;
            return;
        }

        Node* n = root;
        while (n->next->next) { 
            n = n->next;
        }
        delete n->next; 
        n->next = nullptr; 
    }
}


    int lastTailVal(){
        if(root != nullptr){
         Node* n = root;
         while (n->next) {
            n = n->next;
         }
         return n->val;
        }
        return -1;
    }

    int lastTailPassage(){
        if(root != nullptr){
         Node* n = root;
         while (n->next) {
            n = n->next;
         }
         return n->passage;
        }
        return -1;
    }

    void lastTailPlus(){
        if(root != nullptr){
         Node* n = root;
         while (n->next) {
            n = n->next;
         }
         n->passage++;
        }
    }

    void printList(){
    if (root != nullptr) {
        Node* n = root;
        while (n->next) {
            cout << n->val << "->";
            n = n->next;
        }
        cout<< n->val<<";"<<endl;
     }
    }

    int countList(){
        if(root != nullptr){
         int count = 1;
         Node* n = root;
         while (n->next) {
            count++;
            n = n->next;
         }
         return count;
        }
        return -1;
    }
};