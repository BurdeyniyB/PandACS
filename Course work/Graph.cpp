#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
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

        Node() : neighbors(nullptr), countNodes(0), val(0), role('N') {}
    };

    int size, countStrarts, countFinishes;
    Node *nodes = nullptr;
    Linkedlist *finalLinkedList = nullptr;

public:
    Graph(int V, resArr startV, resArr finishV)
    {
        int i, j;
        size = V;
        countStrarts = startV.getCurr();
        countFinishes = finishV.getCurr();
        nodes = new Node[V];

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

    void addNeighbors(int node, int vertex){
        nodes[node].neighbors[nodes[node].countNodes] = new Node(); // Створення нового вузла
        nodes[node].neighbors[nodes[node].countNodes]->val = vertex;
        nodes[node].countNodes++;
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
                line += " " + to_string(node.neighbors[i]->val + 1);
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
                if (finalLinkedList != nullptr)
                {
                    if (finalLinkedList->countList() > list->countList())
                    {
                        finalLinkedList = list;
                        cout<<"Linkedlist is change"<<endl;
                    }
                }
                else
                {
                    finalLinkedList = list;
                }
                
                if (countFinishes == 1)
                {
                    cout << "BFS:";
                    finalLinkedList->printList();
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
};