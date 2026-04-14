#ifndef NODE_H
#define NODE_H

#include "GraphEntity.h"
class GraphEntity; 
#include <iostream>
#include <string>
using namespace std;

class Node : public GraphEntity {
private:
    string name;
    Node** neighbors;      // raw pointer array to neighbor nodes
    int* weights;          // dynamic weight array
    int neighborCount;
    int capacity;

public:
    // Constructor - dynamic memory allocation
    Node(string n) : name(n), neighborCount(0), capacity(50) {
        neighbors = new Node*[capacity];
        weights   = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            neighbors[i] = nullptr;
            weights[i]   = 0;
        }
    }

    // Destructor - proper memory cleanup
    ~Node() {
        delete[] neighbors;
        delete[] weights;
    }

    // Copy constructor (deep copy)
    Node(const Node& other) : name(other.name),
                               neighborCount(other.neighborCount),
                               capacity(other.capacity) {
        neighbors = new Node*[capacity];
        weights   = new int[capacity];
        for (int i = 0; i < neighborCount; i++) {
            neighbors[i] = other.neighbors[i];
            weights[i]   = other.weights[i];
        }
    }

    void addNeighbor(Node* neighbor, int weight) {
        if (neighborCount < capacity) {
            neighbors[neighborCount] = neighbor;
            weights[neighborCount]   = weight;
            neighborCount++;
        }
    }

    void removeNeighbor(const string& neighborName) {
        for (int i = 0; i < neighborCount; i++) {
            if (neighbors[i]->getName() == neighborName) {
                for (int j = i; j < neighborCount - 1; j++) {
                    neighbors[j] = neighbors[j + 1];
                    weights[j]   = weights[j + 1];
                }
                neighborCount--;
                return;
            }
        }
    }

    // Getters
    string getName() const override { return name; }
    int getNeighborCount() const { return neighborCount; }
    Node* getNeighbor(int i) const { return neighbors[i]; }
    int getWeight(int i) const { return weights[i]; }

    int getWeightTo(const string& neighborName) const {
        for (int i = 0; i < neighborCount; i++) {
            if (neighbors[i]->getName() == neighborName)
                return weights[i];
        }
        return -1;
    }

    bool hasNeighbor(const string& neighborName) const {
        for (int i = 0; i < neighborCount; i++) {
            if (neighbors[i]->getName() == neighborName)
                return true;
        }
        return false;
    }

    // Operator overloading for display
    friend ostream& operator<<(ostream& os, const Node& node) {
        os << "[" << node.name << "]";
        return os;
    }

    void display() const override {
        cout << "  Location: " << name << " | Connected to: ";
        if (neighborCount == 0) {
            cout << "None";
        } else {
            for (int i = 0; i < neighborCount; i++) {
                cout << neighbors[i]->getName() << "(dist:" << weights[i] << ")";
                if (i < neighborCount - 1) cout << ", ";
            }
        }
        cout << endl;
    }
};

#endif
