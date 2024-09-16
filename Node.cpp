#include "Node.hpp";

void Node::addEdge(Node* neighbor, int distance)
{
    Edge newEdge;
    newEdge.neighbor = neighbor;
    newEdge.distance = distance;
    this->edges.push_back(newEdge);
}