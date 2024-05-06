#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
#include "resArr.cpp"
#include "Linkedlist.cpp"

using namespace std;

class Graph
{
private:
    struct Node
    {
    public:
        Node **neighbors;
        int countNodes;
        int val;
        char role;
        int weight;
        int length;
        float chanceSurvive;
        int obstacle;

        Node() : neighbors(nullptr), countNodes(0), val(0), role('N'), weight(0), length(numeric_limits<int>::max()), chanceSurvive(1), obstacle(0) {}
    };

    int size, countStrarts, countFinishes, countObstacle;
    Node *nodes = nullptr;
    Linkedlist* finalLinkedListBFS = nullptr;
    Linkedlist** LinkedListsDFS = nullptr; 
    resArr* trackListsDFS = nullptr;
    resArr* trackListDijkstra = nullptr;

public:
    Graph(int V, resArr startV, resArr finishV, resArr obstacleV)
    {
        int i, j;
        size = V;
        countStrarts = startV.getCurr();
        countFinishes = finishV.getCurr();
        countObstacle = obstacleV.getCurr();
        nodes = new Node[V];
        LinkedListsDFS = new Linkedlist*[1];
        LinkedListsDFS[0] = new Linkedlist();
        trackListDijkstra = new resArr();

        for (i = 0; i < V; i++)
        {
            nodes[i].neighbors = new Node *[V]; // Ініціалізація масиву вказівників
            nodes[i].val = i + 1;
            for (j = 0; j < countStrarts; j++)
            {
                if (nodes[i].val == startV.getElem(j))
                {
                    nodes[i].role = 'S';
                }
            }
            for (j = 0; j < countFinishes; j++)
            {
                if (nodes[i].val == finishV.getElem(j))
                {
                    nodes[i].role = 'F';
                }
            }
            for (j = 0; j < countObstacle; j++)
            {
                if (nodes[i].val == obstacleV.getElem(j))
                {
                    nodes[i].role = 'O';
                }
            }
            nodes[i].countNodes = 0;
        }
    }

    ~Graph()
    { // Видалення виділеної пам'яті
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < nodes[i].countNodes; j++)
            {
                delete nodes[i].neighbors[j];
            }
            delete[] nodes[i].neighbors;
        }
        delete[] nodes;
    }

    void addNeighbors(int node, int vertex, int vertexWeight = 0){
        nodes[node].neighbors[nodes[node].countNodes] = new Node(); // Створення нового вузла
        nodes[node].neighbors[nodes[node].countNodes]->val = vertex;
        nodes[node].neighbors[nodes[node].countNodes]->weight = vertexWeight;
        nodes[node].length = nodes[node].role == 'S' ? 0 : numeric_limits<int>::max();
        nodes[node].countNodes++;
    }

    int isStart(int i){
        if(nodes[i].role == 'S'){
            return nodes[i].val;
        }
        return 0;
    }

    string printNodes(int numNode)
    {
        Node node;
        string line;

        line = "";
        line += "Vertex " + to_string(numNode) + "(" + string(1, nodes[numNode - 1].role) + ")" + ":";

        if (nodes != nullptr)
        {
            node = nodes[numNode - 1];
        }

        for (int i = 0; i < node.countNodes; i++)
        {
            if (node.neighbors[i] != nullptr)
            {
                line += " " + to_string(node.neighbors[i]->val + 1) + "(" +to_string(node.neighbors[i]->weight) + ")";
            }
        }
        line += ";";
        return line;
    }

    void BFS(int numNode, int step = 0, Linkedlist *list = nullptr)
    {
        Node node;
        int i, t, p;
        string line;

        line = "";
        for (i = 0; i < step; i++)
        {
            line += " ";
        }
        if (nodes != nullptr)
        {
            node = nodes[numNode - 1];
            line += to_string(node.val);
            cout << line << endl;

            if (list == nullptr)
            {
                list = new Linkedlist();
            }

            list->addTail(numNode);
            list->printList();

            if (node.neighbors != nullptr && node.countNodes > 1)
            {
                int p = list->lastTailPassage();
                BFS(node.neighbors[p]->val + 1, ++step, list);
            }
            else if (node.neighbors != nullptr && node.role == 'S')
            {
                BFS(node.neighbors[0]->val + 1, ++step, list);
            }
            else if (node.neighbors != nullptr && node.role == 'N')
            {
                while (node.countNodes <= 2 || node.countNodes <= list->lastTailPassage())
                {
                    t = list->lastTailVal();
                    node = nodes[t - 1];
                    list->removedTail();
                    list->printList();
                    node = nodes[list->lastTailVal() - 1];
                    step--;
                }
                list->lastTailPlus();
                BFS(node.neighbors[list->lastTailPassage()]->val + 1, step, list);
            }
            else if (node.neighbors != nullptr && node.role == 'F')
            {  
                if (finalLinkedListBFS != nullptr) {
                    if (finalLinkedListBFS->countList() > list->countList()) {
                    delete finalLinkedListBFS;
                    finalLinkedListBFS = new Linkedlist(*list);
                    cout << "Linkedlist has been changed" << endl;
                    }
                } else {
                    finalLinkedListBFS = new Linkedlist(*list);
            }

                if (countFinishes == 1)
                {
                    cout << "BFS:";
                    finalLinkedListBFS->printList();
                }
                else
                {
                    countFinishes--;
                    while (node.countNodes <= 2 || node.countNodes <= list->lastTailPassage())
                    {
                        t = list->lastTailVal();
                        node = nodes[t - 1];
                        list->removedTail();
                        list->printList();
                        node = nodes[list->lastTailVal() - 1];
                        step--;
                    }
                    list->lastTailPlus();
                    BFS(node.neighbors[list->lastTailPassage()]->val + 1, step, list);
                }
            }
        }
    }

    void DFS(int numNode, int step = 0, int currList = 0, int countLists = 1, int minCurrList = 0){
        Node node;
        int i, t, lastPassage;
        string line;

        line = "";
        if (nodes != nullptr)
        {
            node = nodes[numNode-1];
            line += to_string(node.val);
            cout << line << endl;

            if(LinkedListsDFS == nullptr){
                LinkedListsDFS = new Linkedlist*[1];
                LinkedListsDFS[0] = new Linkedlist();

            } else{
                if(node.neighbors != nullptr){
                    if(currList >= countLists){
                        if(trackListsDFS != nullptr){
                            int currTrack = 0;
                            currList = 0;
                            while(currList!=1){
                                currList = currList >= countLists ? 0 : currList; 
                                if(!trackListsDFS->checkElem(currTrack)){
                                    currList++;
                                }
                                currTrack++;
                            }
                        }
                        else{
                            currList = minCurrList;
                        }
                    }
                    lastPassage = LinkedListsDFS[currList]->lastTailPassage();
                    int p;
                    if(node.countNodes == 2){
                        if((countLists-minCurrList)>1){
                            t = 1;
                        }
                        p = node.neighbors[lastPassage]->val;
                        node = nodes[p];
                    } else if(node.role == 'S'){
                        LinkedListsDFS[currList]->addTail(node.val);
                        p = node.neighbors[0]->val;
                        node = nodes[p];
                        
                    } else if(node.countNodes > 2){
                        if(lastPassage == 1){
                            t = 1;
                            Linkedlist** lists;
                            lists = new Linkedlist*[countLists+1];
                            for(int i = 0; i < countLists; i++){
                                lists[i] = new Linkedlist(*LinkedListsDFS[i]);
                                lists[i]->lastTailPlus();
                            }
                            lists[countLists] = new Linkedlist(*LinkedListsDFS[countLists-1]);
                            lists[countLists]->lastTailPlus();
                            countLists++;
                            LinkedListsDFS = lists;
                            p = node.neighbors[lastPassage]->val;
                            node = nodes[p];
                        } else{
                            t = 1;
                            p = node.neighbors[lastPassage]->val;
                            node = nodes[p];
                        }
                    } else if(node.countNodes == 1 && node.role != 'S'){
                        t = 2;
                        if(trackListsDFS != nullptr){
                            int c = trackListsDFS->getCurr();
                            if(c == countLists){
                             int min = LinkedListsDFS[0]->countList();
                             for (int i = 1; i < countLists; i++)
                             {
                                 min = min > LinkedListsDFS[i]->countList();
                             }
                             cout<<"DFS:";
                             LinkedListsDFS[min]->printList();
                             return;
                            }
                        }
                    }
                }
            }

            if(t != 2){
            LinkedListsDFS[currList]->addTail(node.val);
            cout << "(" << currList << ")";
            LinkedListsDFS[currList]->printList();
            } else{
                t = 1;
                if(trackListsDFS == nullptr){
                    trackListsDFS = new resArr();
                }
                trackListsDFS->addElem(currList);
                minCurrList++;
            }
            cout<<"All lists"<<endl;
            for(int i = 0; i < countLists; i++){
                cout << "(" << i << ")";
                LinkedListsDFS[i]->printList();
            }
            if(t == 1){
                t = 0;
                int c;
                c = currList+1;
                if(c >= countLists || (trackListsDFS != nullptr && trackListsDFS->checkElem(c))){
                    if(trackListsDFS != nullptr){
                        int currTrack = 0;
                        c = 0;
                        while(c!=1){
                            c = c >= countLists ? 0 : c; 
                            if(!trackListsDFS->checkElem(currTrack)){
                                c++;
                            }
                            currTrack++;
                        }
                    }
                    else{
                        c = minCurrList;
                    }
                }
                numNode = LinkedListsDFS[c]->lastTailVal();
            } else{
                numNode = LinkedListsDFS[currList]->lastTailVal();
            }
            DFS(numNode, ++step, ++currList, countLists, minCurrList);
        }
    }
 
    void dijkstra(int chanceSurvive = 0, int withoutObstacles = 0){
        Node node;
        int i, ind;
        int min = numeric_limits<int>::max();
        int nodeIndex = -1;
        for (i = 0; i < size; i++)
        {
            if(min > nodes[i].length){
                if(trackListDijkstra->checkElem(nodes[i].val) != 1){
                    min = nodes[i].length;
                    node = nodes[i];
                    nodeIndex = i;
                    break;
                }
            }
        }
        cout<<"min("<<nodeIndex+1<<")= "<<min<<endl;
        for(i = 0; i < node.countNodes; i++){
            if(node.neighbors[i]->length > node.length + node.neighbors[i]->weight){
                int n = node.neighbors[i]->val;
                nodes[n].length = node.length + node.neighbors[i]->weight;
                if(chanceSurvive){
                    nodes[n].chanceSurvive = node.chanceSurvive;
                    if(nodes[n].role == 'O'){
                        float l = node.chanceSurvive * ((10-node.neighbors[i]->weight)/10.);
                        nodes[n].chanceSurvive = l;
                    }
                }
                if(withoutObstacles){
                    nodes[n].obstacle = node.obstacle;
                    if(nodes[n].role == 'O'){
                        nodes[n].obstacle = 1;
                    }
                }
            }
        }
        int n = nodes[nodeIndex].val;
        trackListDijkstra->addElem(n);
        for(i = 0; i < size; i++){
            if(nodes[i].length >= numeric_limits<int>::max()){
                dijkstra(chanceSurvive, withoutObstacles);
            }
        }
    }

    void printFinishLength(int chanceSurvive = 0, int withoutObstacles = 0){
        int i;
        for(i = 0; i < size; i++){
            if(nodes[i].role == 'F'){
                if(chanceSurvive){
                    cout<<"finish "<<nodes[i].val<<" has a nearest distance: "<<nodes[i].length<<", chance survive: "<<nodes[i].chanceSurvive<<endl;
                }else if(withoutObstacles) {
                    if(!nodes[i].obstacle){
                        cout<<"finish "<<nodes[i].val<<" has a nearest distance: "<<nodes[i].length<<endl;
                    }
                }else{
                    cout<<"finish "<<nodes[i].val<<" has a nearest distance: "<<nodes[i].length<<endl;
                }
            }
        }
    }
};