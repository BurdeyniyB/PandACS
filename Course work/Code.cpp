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
void readNodesFromFile(resArr& startV, resArr& finishV, resArr& obstacleV, const string filename);
void BFS(Graph* graph);
void DFS(Graph* graph);
void dijkstra(Graph* graph);

int main() {
    string relationshipFileName, roleFileName, mazeFileName;
    resArr startV, finishV, obstacleV;
    Graph* graph;
    
    relationshipFileName = "Database/relationship.txt";
    roleFileName = "Database/role.txt";
    mazeFileName = "Database/maze.txt";
    
    showMaze(mazeFileName);
    readNodesFromFile(startV, finishV, obstacleV, roleFileName);

    graph = new Graph(ROWS, startV, finishV, obstacleV);
    readRelationshipFromFile(graph, relationshipFileName);
    showVertexesInfo(graph);
    BFS(graph);
    DFS(graph);
    dijkstra(graph);

    delete graph;
    return 0;
}

void readRelationshipFromFile(Graph* graph, const string filename) {
    ifstream file(filename);
    string line;
    char role;
    int node, vertex, vertexWeight;

    if (file.is_open()) {
        getline(file, line);
        while(getline(file, line)){
            istringstream iss(line);
            while(iss >> node){
                iss.ignore(3);
                while(iss){
                 iss >> vertex;
                 iss.ignore(1);
                 iss >> vertexWeight;
                 iss.ignore(2);
                 graph->addNeighbors(node-1, vertex-1, vertexWeight);
                 iss.ignore();
                }
            } 
        }
        file.close();
    } else {
        cerr << "Не вдалося відкрити файл для читання." << endl;
    }
}

void readNodesFromFile(resArr& startV, resArr& finishV, resArr& obstacleV, const string filename) {
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
                } else if (role == "O") {
                    obstacleV.addElem(value);
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
    for(int i = 0; i < ROWS; i++){
        int numNode = graph->isStart(i);
        if(numNode){
            graph->BFS(numNode);
        }
    }
    cout << "-------BFS finish-------"<<endl;
}

void DFS(Graph* graph){ 
    cout<< "-------DFS start-------"<<endl;
    for(int i = 0; i < ROWS; i++){
        int numNode = graph->isStart(i);
        if(numNode){
            graph->DFS(numNode);
        }
    }
    cout << "-------DFS finish-------"<<endl;
}

void dijkstra(Graph* graph){
    int choise;
    cout<< "-------dijkstra start-------"<<endl;
    cout<<"choise task:\n1.only distance\n2.chance survive\n3.without obstacles"<<endl;
    cin >> choise;
    switch (choise)
    {
    case 1:
        cout<< "-------only distance start-------"<<endl;
        graph->dijkstra();
        graph->printFinishLength();
        cout<< "-------only distance finish-------"<<endl;
        break;
    case 2:
        cout<< "-------chance survive start-------"<<endl;
        graph->dijkstra(1, 0);
        graph->printFinishLength(1, 0);
        cout<< "-------chance survive finish-------"<<endl;
        break;
    case 3:
        cout<< "-------without obstacles start-------"<<endl;
        graph->dijkstra(0, 1);
        graph->printFinishLength(0, 1);
        cout<< "-------without obstacles finish-------"<<endl;
        break;
    default:
        break;
    }
    cout << "-------dijkstra finish-------"<<endl;
}