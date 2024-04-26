#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "resArr.cpp"
#include "Linkedlist.cpp"

using namespace std;

class Graph{
    struct Node {
    public: 
        Node** neighbors;
        int countNodes;
        int val;
        char role;

        Node() : neighbors(nullptr), countNodes(0), val(0), role('N') {} 
    };

    int size; // Розмір графа

public: 
    Node* nodes = nullptr;

    Graph(int V, int** matrix, resArr startV, resArr finishV){
        int i, j;
        size = V;
        nodes = new Node[V];

        for (i = 0; i < V; i++){
            nodes[i].neighbors = new Node*[V]; // Ініціалізація масиву вказівників
            nodes[i].val = i+1;
            for (j = 0; j < startV.getCurr(); j++)
            {
                if(nodes[i].val == startV.getElem(j)){
                    nodes[i].role = 'S';
                }
            }
            for (j = 0; j < finishV.getCurr(); j++){
                if(nodes[i].val == finishV.getElem(j)){
                    nodes[i].role = 'F';
                }
            }
            nodes[i].countNodes = 0;
            for(int j = 0; j < V; j++){
                if(matrix[i][j]){
                    nodes[i].neighbors[nodes[i].countNodes] = new Node(); // Створення нового вузла
                    nodes[i].neighbors[nodes[i].countNodes]->val = j;
                    nodes[i].countNodes++;
                }
            }
        }
    }

    ~Graph() { // Видалення виділеної пам'яті
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < nodes[i].countNodes; j++) {
                delete nodes[i].neighbors[j];
            }
            delete[] nodes[i].neighbors;
        }
        delete[] nodes;
    }

    string printNodes(int numNode){
        Node node; 
        string line;

        line = "";
        line += "Vertex " + to_string(numNode) + "(" + string(1, nodes[numNode-1].role) + ")" + ":";

        if(nodes != nullptr){
            node = nodes[numNode-1];
        }

        for(int i = 0; i < node.countNodes; i++){
         if(node.neighbors[i] != nullptr) { 
             line += " " + to_string(node.neighbors[i]->val + 1);
         }
        }
     line += ";";
     return line;
    }

    void BFS(int numNode, int step = 0, Linkedlist* list = nullptr){
        Node node; 
        int i, t;
        string line;

        line = "";
        for (i = 0; i < step; i++)
        {
           line += " ";
        }
        if(nodes != nullptr){
            node = nodes[numNode-1];
        }
        line += to_string(node.val);
        cout << line <<endl; 

        if(list == nullptr){
            list = new Linkedlist();
        }

        list->addTail(numNode);
        list->printList();

        if(node.neighbors != nullptr && node.countNodes > 1){
            BFS(node.neighbors[1]->val + 1, ++step, list);
        } else if(node.neighbors != nullptr && node.role == 'S'){
            BFS(node.neighbors[0]->val + 1, ++step, list);
        } else if(node.neighbors != nullptr && node.role == 'N'){
            // while(node.countNodes >= list->lastTailPassage)
            // t = list->lastTailVal();
            // cout<<"last tail value "<< t <<endl;
            // node = nodes[t-1];
            // list->removedTail();
        }
    }
};