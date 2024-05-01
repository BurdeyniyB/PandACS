#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Graph.cpp"
#include "resArr.cpp"

using namespace std;

const int ROWS = 15;
const int COLS = 15;

void showMaze(const string filename);
void showVertexesInfo(Graph* graph);
void readRelationshipFromFile(Graph* graph, const string filename); // Pass matrix by reference
void readNodesFromFile(resArr& startV, resArr& finishV, const string filename);
void BFS(Graph* graph);

int main() {
    string relationshipFileName, roleFileName, mazeFileName;
    resArr startV, finishV;
    Graph* graph;
    
    relationshipFileName = "Database/relationship.txt";
    roleFileName = "Database/role.txt";
    mazeFileName = "Database/maze.txt";
    
    showMaze(mazeFileName);
    readNodesFromFile(startV, finishV, roleFileName);

    graph = new Graph(ROWS, startV, finishV);
    readRelationshipFromFile(graph, relationshipFileName);
    showVertexesInfo(graph);
    BFS(graph);

    delete graph;
    return 0;
}

void readRelationshipFromFile(Graph* graph, const string filename) {
    ifstream file(filename);
    string line;
    char role;
    int node, vertex, s, f;

    if (file.is_open()) {
        getline(file, line);
        while(getline(file, line)){
            istringstream iss(line);
            while(iss >> node){
                iss.ignore(3);
                while(iss){
                 iss >> vertex;
                 graph->addNeighbors(node-1, vertex-1);
                 iss.ignore();
                }
            } 
        }
        file.close();
    } else {
        cerr << "Не вдалося відкрити файл для читання." << endl;
    }
}

void readNodesFromFile(resArr& startV, resArr& finishV, const string filename) {
    ifstream file(filename);
    string line, role;
    int value;

    if (file.is_open()) {
        while(getline(file, line)){
            istringstream iss(line);
            iss >> role;
            iss.ignore(3); 
            while (iss)
            {
                iss >> value;
                if (role == "S") {
                    startV.addElem(value);
                } else if (role == "F") {
                    finishV.addElem(value);
                }
                iss.ignore();
            }
        }
        file.close();
    } else {
        cerr << "Не вдалося відкрити файл для читання." << endl;
    }
}

void showMaze(const string filename){
    ifstream file(filename);
    string line, maze;
        if (file.is_open()) {
        while(getline(file, line)){
            cout << line << endl;
        }
        file.close();
    } else {
        cerr << "Не вдалося відкрити файл для читання." << endl;
    }
    cout<<endl;
}

void showVertexesInfo(Graph* graph){
    for(int i = 1; i <= ROWS; i++){
        cout << graph->printNodes(i) << endl;
    }
    cout<<endl;
}

void BFS(Graph* graph){
    cout << "-------BFS start-------"<<endl;
    graph->BFS(1);
    cout << "-------BFS finish-------"<<endl;
}