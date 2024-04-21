#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "resArr.cpp"

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

    Node* nodes = nullptr;
    int size; // Розмір графа

public: 
    Graph(int V, int** matrix, resArr startV, resArr finishV){
        int i, j;
        size = V;
        nodes = new Node[V];

        for (i = 0; i < V; i++){
            nodes[i].neighbors = new Node*[V]; // Ініціалізація масиву вказівників
            nodes[i].val = i;
            for (j = 0; j < startV.getCurr(); j++)
            {
                if(nodes[i].val == startV.getElem(j)-1){
                    nodes[i].role = 'S';
                }
            }
            for (j = 0; j < finishV.getCurr(); j++){
                if(nodes[i].val == finishV.getElem(j)-1){
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

    string printNodes(int V){
        Node node = nodes[V-1];
        string line = "";
        line += "Vertex " + to_string(V) + "(" + string(1, nodes[V-1].role) + ")" + ":";
        for(int i = 0; i < node.countNodes; i++){
         if(node.neighbors[i] != nullptr) { // Перевірка на нульовий вказівник
             line += " " + to_string(node.neighbors[i]->val + 1);
         }
        }
     line += ";";
     return line;
    }
};