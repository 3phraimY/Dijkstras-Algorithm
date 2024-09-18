#include "Node.hpp"

void Node::addEdge(Node* neighbor, int distance)
{
    Edge newEdge;
    newEdge.neighbor = neighbor;
    newEdge.distance = distance;
    this->edges.push_back(newEdge);
}

int Node::getIndexOfNode(Node* neighbor)
{
    for(int i = 0; i < this->edges.size(); i++)
    {
        if(this->edges.at(i).neighbor == neighbor)
        {
            return i;
        }
    }
    return -1;
}