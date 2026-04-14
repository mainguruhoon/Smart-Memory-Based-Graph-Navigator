#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <set>
#include "PathFinder.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

class FileManager : public PathFinder {
public:

    // Save graph to file
    void saveGraph(const string& filename) {
        ofstream file(filename);
        if (!file.is_open())
            throw runtime_error("Could not open file: " + filename);

        // Write all node names
        file << "NODES " << nodeMap.size() << "\n";
        for (auto& pair : nodeMap) {
            file << pair.first << "\n";
        }

        // Write all edges (avoid duplicates using set)
        set<pair<string,string>> written;
        file << "EDGES\n";

        for (auto& pair : nodeMap) {
            Node* node = pair.second;
            for (int i = 0; i < node->getNeighborCount(); i++) {
                string src  = pair.first;
                string dest = node->getNeighbor(i)->getName();
                int    w    = node->getWeight(i);

                // Only write each edge once
                if (written.find({dest, src}) == written.end()) {
                    file << src << " " << dest << " " << w << "\n";
                    written.insert({src, dest});
                }
            }
        }

        file << "END\n";
        file.close();
        cout << "  >> Graph saved to '" << filename << "' successfully!\n";
        cout << "  >> Saved " << nodeMap.size() << " locations and "
             << edgeCount << " roads.\n";
    }

    // Load graph from file
    void loadGraph(const string& filename) {
        ifstream file(filename);
        if (!file.is_open())
            throw runtime_error("Could not open file: " + filename);

        // Clear existing graph
        for (auto& pair : nodeMap) delete pair.second;
        nodeMap.clear();
        nodeCount = 0;
        edgeCount = 0;

        string line, token;
        int nodeCountToLoad = 0;

        // Read NODES section
        file >> token >> nodeCountToLoad;
        file.ignore();

        for (int i = 0; i < nodeCountToLoad; i++) {
            getline(file, line);
            if (!line.empty()) {
                nodeMap[line] = new Node(line);
                nodeCount++;
            }
        }

        // Read EDGES section
        file >> token; // "EDGES"
        while (file >> token && token != "END") {
            string src = token, dest;
            int weight;
            file >> dest >> weight;

            if (nodeMap.find(src) != nodeMap.end() &&
                nodeMap.find(dest) != nodeMap.end()) {
                nodeMap[src]->addNeighbor(nodeMap[dest], weight);
                nodeMap[dest]->addNeighbor(nodeMap[src], weight);
                edgeCount++;
            }
        }

        file.close();
        cout << "  >> Graph loaded from '" << filename << "' successfully!\n";
        cout << "  >> Loaded " << nodeCount << " locations and "
             << edgeCount << " roads.\n";
    }

    // Load sample demo data
    void loadSampleData() {
        cout << "\n  Loading sample city graph...\n";
        try {
            addNode("Delhi");
            addNode("Varanasi");
            addNode("Chandigarh");
            addNode("Jaipur");
            addNode("Mumbai");
            addNode("Lucknow");
            addNode("Agra");
            addNode("Amritsar");
            addNode("Shimla");

            addEdge("Delhi", "Chandigarh", 250);
            addEdge("Varanasi", "Chandigarh", 748);
            addEdge("Delhi", "Jaipur", 280);
            addEdge("Delhi", "Lucknow", 555);
            addEdge("Delhi", "Agra", 200);
            addEdge("Chandigarh", "Amritsar", 230);
            addEdge("Chandigarh", "Shimla", 115);
            addEdge("Jaipur", "Mumbai", 1150);
            addEdge("Agra", "Lucknow", 335);
            addEdge("Mumbai", "Lucknow", 1400);

            cout << "  >> Sample data loaded!\n";
        } catch (exception& e) {
            cout << "  Note: " << e.what() << "\n";
        }
    }

    // Memory report
    void memoryReport() {
        cout << "\n  ===== MEMORY MANAGEMENT REPORT =====\n";
        cout << "  Active Node* pointers  : " << nodeMap.size() << "\n";
        cout << "  Total dynamic Node allocs: " << Graph::getAllocations() << "\n";
        cout << "  Each Node allocates    : 2 dynamic arrays (neighbors + weights)\n";
        cout << "  Destructor will free   : " << nodeMap.size() * 2 << " arrays\n";
        cout << "  Memory status          : TRACKED (no leaks)\n";
        cout << "  =====================================\n";
    }
};

#endif
