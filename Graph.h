#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "GraphEntity.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

class Graph : public GraphEntity {
protected:
    map<string, Node*> nodeMap;   // STL map of node name -> Node pointer
    int nodeCount;
    int edgeCount;
    static int totalMemoryAllocations;   // track new/delete

public:
    Graph() : nodeCount(0), edgeCount(0) {}

    // Destructor - free all dynamically allocated nodes
    virtual ~Graph() {
        for (auto& pair : nodeMap) {
            delete pair.second;
        }
        nodeMap.clear();
    }

    // Add a location/node
    void addNode(const string& name) {
        if (nodeMap.find(name) != nodeMap.end()) {
            throw runtime_error("Location '" + name + "' already exists!");
        }
        nodeMap[name] = new Node(name);
        totalMemoryAllocations++;
        nodeCount++;
        cout << "  >> Location '" << name << "' added successfully.\n";
    }

    // Remove a node and all edges to it
    void removeNode(const string& name) {
        if (nodeMap.find(name) == nodeMap.end())
            throw runtime_error("Location '" + name + "' not found!");

        // Remove edges pointing to this node from all other nodes
        for (auto& pair : nodeMap) {
            if (pair.first != name)
                pair.second->removeNeighbor(name);
        }

        delete nodeMap[name];
        nodeMap.erase(name);
        nodeCount--;
        cout << "  >> Location '" << name << "' removed.\n";
    }

    // Add a road/edge (undirected)
    void addEdge(const string& src, const string& dest, int weight) {
        if (nodeMap.find(src) == nodeMap.end())
            throw runtime_error("Source '" + src + "' not found!");
        if (nodeMap.find(dest) == nodeMap.end())
            throw runtime_error("Destination '" + dest + "' not found!");
        if (weight <= 0)
            throw invalid_argument("Distance must be a positive number!");

        nodeMap[src]->addNeighbor(nodeMap[dest], weight);
        nodeMap[dest]->addNeighbor(nodeMap[src], weight);
        edgeCount++;
        cout << "  >> Road added: " << src << " <--> " << dest
             << " (Distance: " << weight << " km)\n";
    }

    // Remove an edge
    void removeEdge(const string& src, const string& dest) {
        if (nodeMap.find(src) == nodeMap.end() || nodeMap.find(dest) == nodeMap.end())
            throw runtime_error("One or both locations not found!");
        nodeMap[src]->removeNeighbor(dest);
        nodeMap[dest]->removeNeighbor(src);
        edgeCount--;
        cout << "  >> Road removed between " << src << " and " << dest << "\n";
    }

    Node* getNode(const string& name) {
        if (nodeMap.find(name) == nodeMap.end())
            throw runtime_error("Location '" + name + "' not found!");
        return nodeMap[name];
    }

    bool nodeExists(const string& name) const {
        return nodeMap.find(name) != nodeMap.end();
    }

    map<string, Node*>& getNodeMap() { return nodeMap; }

    int getNodeCount() const { return nodeCount; }
    int getEdgeCount() const { return edgeCount; }
    static int getAllocations() { return totalMemoryAllocations; }

    string getName() const override { return "Graph"; }

    void display() const override {
        if (nodeMap.empty()) {
            cout << "  Graph is empty!\n";
            return;
        }
        cout << "\n  ========= GRAPH ADJACENCY LIST =========\n";
        for (const auto& pair : nodeMap) {
            pair.second->display();
        }
        cout << "  Total Locations: " << nodeCount
             << " | Total Roads: " << edgeCount << "\n";
        cout << "  ========================================\n";
    }

    // Operator overloading: += to add a node by name
    Graph& operator+=(const string& nodeName) {
        addNode(nodeName);
        return *this;
    }

    // Operator overloading: display graph info
    friend ostream& operator<<(ostream& os, const Graph& g) {
        os << "Graph[Locations=" << g.nodeCount << ", Roads=" << g.edgeCount << "]";
        return os;
    }
};

int Graph::totalMemoryAllocations = 0;

#endif
