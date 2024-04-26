#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>
#include "Graph.cpp"
#include "resArr.cpp"

using namespace std;

const int ROWS = 15;
const int COLS = 15;

void showMaze(const string filename);
void showVertexesInfo(Graph* graph);
void readMatrixFromFile(int**& matrix, const string filename); // Pass matrix by reference
void readNodesFromFile(resArr& startV, resArr& finishV, const string filename);
void initialDynamicMatrix(int**& matrix); // Pass matrix by reference
void deleteDynamicMatrix(int**& matrix); // Pass matrix by reference
void BFS(Graph* graph);

int main() {
    int** relationshipMatrix = nullptr; // Initialize pointers to nullptr
    string relationshipFileName, roleFileName, mazeFileName;
    resArr startV, finishV;
    Graph* graph;

    initialDynamicMatrix(relationshipMatrix);

    relationshipFileName = "Database/relationship.txt";
    roleFileName = "Database/role.txt";
    mazeFileName = "Database/maze.txt";
    
    showMaze(mazeFileName);
    readMatrixFromFile(relationshipMatrix, relationshipFileName);
    readNodesFromFile(startV, finishV, roleFileName);

    graph = new Graph(ROWS, relationshipMatrix, startV, finishV);
    showVertexesInfo(graph);
    BFS(graph);

    delete graph;
    deleteDynamicMatrix(relationshipMatrix);
    return 0;
}

void initialDynamicMatrix(int**& matrix){
    matrix = new int*[ROWS];
    for (int i = 0; i < ROWS; ++i) {
        matrix[i] = new int[COLS];
        for (int j = 0; j < COLS; ++j) {
            matrix[i][j] = 0; // Заповнення кожного елемента матриці значенням 0
        }
    }
}
void deleteDynamicMatrix(int**& matrix){
    for (int i = 0; i < ROWS; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr; // Reset pointer to nullptr after deallocation
}

void readMatrixFromFile(int**& matrix, const string filename) {
    ifstream file(filename);
    string line;
    char role;
    int node, vertex, s, f;
    resArr* vertexes;

    if (file.is_open()) {
        getline(file, line);
        while(getline(file, line)){
            vertexes = new resArr();
            istringstream iss(line);
            while(iss >> node){
                iss.ignore(3);
                while(iss){
                 iss >> vertex;
                 vertexes->addElem(vertex);
                 iss.ignore();
                }

                for(int i = 0; i < vertexes->getCurr(); i++){
                 matrix[node-1][vertexes->getElem(i)-1] = 1;
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