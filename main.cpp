#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "Node.hpp"

#define INF 0xffff

using namespace std;

Node* getNodeFromNodeLetter(vector<Node*> vector, char nodeLetter);
void dijkstrasAlgorithm(vector<Node*>unvisited, Node* beginning, Node* destination, vector<Node*> path);

int main() 
{
    // The map is the same one used in the explanation
    // It will look something like this:
    /*
         B--C
    A < || /||
         E--D
     */

    // definition of the map
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    Node* D = new Node('D');
    Node* E = new Node('E');

    //edges defined
    A->addEdge(B, 10);
    A->addEdge(E, 3);
    B->addEdge(C, 2);
    B->addEdge(E, 4);
    C->addEdge(D, 9);
    D->addEdge(C, 7);
    E->addEdge(B, 1);
    E->addEdge(C, 8);
    E->addEdge(D, 2);

    // print diagram of map
    cout << "     B--C" << endl << "A < || /||" << endl << "     E--D" << endl;

    //track unvisited Nodes
    vector<Node*> unvisited;
    unvisited.push_back(A);
    unvisited.push_back(B);
    unvisited.push_back(C);
    unvisited.push_back(D);
    unvisited.push_back(E);

    //ask user for beginning and destination nodes
    char beginningNodeLetter, destinationNodeLetter;

    cout << "Which Node should be the starting point" << endl;
    cin >> beginningNodeLetter;

    cout << "Which Node should be the final point" << endl;
    cin >> destinationNodeLetter;


    Node* beginning = getNodeFromNodeLetter(unvisited, toupper(beginningNodeLetter));
    Node* destination = getNodeFromNodeLetter(unvisited, toupper(destinationNodeLetter));
    vector<Node*> path;

    // run user nodes through algorithm
    dijkstrasAlgorithm(unvisited, beginning, destination, path);
}

Node* getNodeFromNodeLetter(vector<Node*> vector, char nodeLetter)
{
    for(Node* node : vector)
    {
        if(node->getNodeLetter() == nodeLetter)
        {
            return node;
        }
    }
    return nullptr;
}

int nodeToLetterIndex(Node* node)
{
    string map = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = 0; i < map.length(); i++)
    {
        if(node->getNodeLetter() == map.at(i))
        {
            return i;
        }
    }
    return -1;
}

void dijkstrasAlgorithm(vector<Node*> unvisited, Node* beginning, Node* destination, vector<Node*> path) 
{
    // Initialize distances to infinite
    int* distances = new int[unvisited.size()];
    unordered_map<Node*, Node*> previous;
    for (Node* node : unvisited) 
    {
        distances[nodeToLetterIndex(node)] = INF;
    }

    // set distance to starting node as 0
    distances[nodeToLetterIndex(beginning)] = 0;

    // loop until all nodes visited
    while (!unvisited.empty()) 
    {
        // move to node with the smallest distance
        Node* currNode = nullptr;
        int currMinDistance = INF;
        for (Node* node : unvisited) 
        {
            if (distances[nodeToLetterIndex(node)] < currMinDistance) 
            {
                currMinDistance = distances[nodeToLetterIndex(node)];
                currNode = node;
            }
        }

        // catch paths which are not possible
        if(currNode == nullptr)
        {
            cout << "No valid path from " << beginning->getNodeLetter() <<" to " << destination->getNodeLetter() << endl;
            return;
        }

        //stop iterating if destination node reached
        if (currNode == destination) 
        {
            break;
        }

        // Remove the currNode from unvisited
        unvisited.erase(remove(unvisited.begin(), unvisited.end(), currNode), unvisited.end());

        // Update distances to neighbors
        for (Edge edge : currNode->getEdges()) 
        {
            Node* neighbor = edge.neighbor;
            int newDist = distances[nodeToLetterIndex(currNode)] + edge.distance;
            if (newDist < distances[nodeToLetterIndex(neighbor)]) 
            {
                distances[nodeToLetterIndex(neighbor)] = newDist;
                previous[neighbor] = currNode;
            }
        }
    }

    // Output the shortest path
    cout << "Shortest path from " << beginning->getNodeLetter() << " to " << destination->getNodeLetter() << " is " << distances[nodeToLetterIndex(destination)] << endl;

    // Print the path
    for (Node* at = destination; at != nullptr; at = previous[at]) 
    {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (Node* node : path) 
    {
        cout << node->getNodeLetter() << " ";
    }
    cout << endl;

    delete[] distances;
}
