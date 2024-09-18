#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

//prototype Node for Edge struct
class Node;

struct Edge {
    int distance;
    Node* neighbor;    
};

class Node {
    private:
        char nodeLetter;
        std::vector<Edge> edges;
    public:
        Node(char nodeLetter) {this->nodeLetter = nodeLetter;};
        ~Node();

        char getNodeLetter() {return this->nodeLetter;};
        std::vector<Edge> getEdges() {return this->edges;};
        void addEdge(Node* neighbor, int distance);
        int getIndexOfNode(Node* neighbor);
};

#endif