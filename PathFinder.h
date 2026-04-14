#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "Graph.h"
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <climits>
#include <algorithm>
#include <chrono>
#include <iomanip>
using namespace std;

class PathFinder : public Graph {
private:
    // Helper: reconstruct path from parent map
    vector<string> reconstructPath(map<string, string>& parent,
                                   const string& src,
                                   const string& dest) {
        vector<string> path;
        string current = dest;
        while (current != src) {
            path.push_back(current);
            if (parent.find(current) == parent.end()) return {};
            current = parent[current];
        }
        path.push_back(src);
        reverse(path.begin(), path.end());
        return path;
    }

    // Helper: print path nicely
    void printPath(const vector<string>& path, int totalDist) {
        if (path.empty()) {
            cout << "  No path found!\n";
            return;
        }
        cout << "  Path: ";
        for (int i = 0; i < (int)path.size(); i++) {
            cout << path[i];
            if (i < (int)path.size() - 1) cout << " --> ";
        }
        cout << "\n  Total Distance: " << totalDist << " km\n";
    }

    // Backtracking helper: find all paths
    void findAllPathsHelper(const string& current,
                            const string& dest,
                            vector<string>& currentPath,
                            set<string>& visited,
                            vector<pair<vector<string>, int>>& allPaths,
                            int currentDist) {
        if (current == dest) {
            allPaths.push_back({currentPath, currentDist});
            return;
        }
        Node* node = nodeMap[current];
        for (int i = 0; i < node->getNeighborCount(); i++) {
            string neighborName = node->getNeighbor(i)->getName();
            int weight = node->getWeight(i);
            if (visited.find(neighborName) == visited.end()) {
                visited.insert(neighborName);
                currentPath.push_back(neighborName);
                findAllPathsHelper(neighborName, dest, currentPath,
                                   visited, allPaths, currentDist + weight);
                currentPath.pop_back();
                visited.erase(neighborName);
            }
        }
    }

public:

    // ============================================================
    // 1. DIJKSTRA'S ALGORITHM (Greedy + Graph)
    // ============================================================
    void dijkstra(const string& src, const string& dest) {
        cout << "\n  [DIJKSTRA'S ALGORITHM - Shortest Path]\n";
        cout << "  From: " << src << " --> To: " << dest << "\n\n";

        if (!nodeExists(src) || !nodeExists(dest))
            throw runtime_error("One or both locations not found!");

        auto start = chrono::high_resolution_clock::now();

        // min-heap: {distance, nodeName}
        priority_queue<pair<int,string>,
                       vector<pair<int,string>>,
                       greater<pair<int,string>>> pq;

        map<string, int>    dist;
        map<string, string> parent;
        map<string, bool>   visited;

        // Initialize distances to infinity
        for (auto& p : nodeMap) {
            dist[p.first]    = INT_MAX;
            visited[p.first] = false;
        }

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            if (u == dest) break;

            Node* node = nodeMap[u];
            for (int i = 0; i < node->getNeighborCount(); i++) {
                string v      = node->getNeighbor(i)->getName();
                int    weight = node->getWeight(i);

                if (dist[u] + weight < dist[v]) {
                    dist[v]   = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

        vector<string> path = reconstructPath(parent, src, dest);
        printPath(path, dist[dest] == INT_MAX ? -1 : dist[dest]);
        cout << "  Time Taken: " << duration.count() << " microseconds\n";
    }

    // ============================================================
    // 2. BFS TRAVERSAL (Graph Algorithm)
    // ============================================================
    void bfs(const string& src) {
        cout << "\n  [BFS TRAVERSAL - Level-wise from: " << src << "]\n\n";

        if (!nodeExists(src))
            throw runtime_error("Location '" + src + "' not found!");

        auto start = chrono::high_resolution_clock::now();

        map<string, bool> visited;
        map<string, int>  level;
        queue<string>     q;

        for (auto& p : nodeMap) visited[p.first] = false;

        visited[src] = true;
        level[src]   = 0;
        q.push(src);

        cout << "  Level | Location\n";
        cout << "  ------|---------\n";

        while (!q.empty()) {
            string u = q.front(); q.pop();
            cout << "    " << setw(3) << level[u] << "  | " << u << "\n";

            Node* node = nodeMap[u];
            for (int i = 0; i < node->getNeighborCount(); i++) {
                string v = node->getNeighbor(i)->getName();
                if (!visited[v]) {
                    visited[v] = true;
                    level[v]   = level[u] + 1;
                    q.push(v);
                }
            }
        }

        auto end = chrono::high_resolution_clock::now();
        cout << "  Time: "
             << chrono::duration_cast<chrono::microseconds>(end - start).count()
             << " microseconds\n";
    }

    // ============================================================
    // 3. DFS TRAVERSAL (Graph + Backtracking)
    // ============================================================
    void dfsHelper(const string& u, map<string, bool>& visited, int depth) {
        visited[u] = true;
        cout << "  ";
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << "|-- " << u << "\n";

        Node* node = nodeMap[u];
        for (int i = 0; i < node->getNeighborCount(); i++) {
            string v = node->getNeighbor(i)->getName();
            if (!visited[v]) {
                dfsHelper(v, visited, depth + 1);
            }
        }
    }

    void dfs(const string& src) {
        cout << "\n  [DFS TRAVERSAL - Deep-first from: " << src << "]\n\n";

        if (!nodeExists(src))
            throw runtime_error("Location '" + src + "' not found!");

        auto start = chrono::high_resolution_clock::now();

        map<string, bool> visited;
        for (auto& p : nodeMap) visited[p.first] = false;

        dfsHelper(src, visited, 0);

        auto end = chrono::high_resolution_clock::now();
        cout << "\n  Time: "
             << chrono::duration_cast<chrono::microseconds>(end - start).count()
             << " microseconds\n";
    }

    // ============================================================
    // 4. FIND ALL PATHS - BACKTRACKING
    // ============================================================
    void findAllPaths(const string& src, const string& dest) {
        cout << "\n  [BACKTRACKING - All Paths from "
             << src << " to " << dest << "]\n\n";

        if (!nodeExists(src) || !nodeExists(dest))
            throw runtime_error("One or both locations not found!");

        auto start = chrono::high_resolution_clock::now();

        vector<pair<vector<string>, int>> allPaths;
        vector<string> currentPath = {src};
        set<string>    visited     = {src};

        findAllPathsHelper(src, dest, currentPath, visited, allPaths, 0);

        if (allPaths.empty()) {
            cout << "  No paths found between " << src << " and " << dest << "!\n";
            return;
        }

        // Sort by distance
        sort(allPaths.begin(), allPaths.end(),
             [](auto& a, auto& b) { return a.second < b.second; });

        cout << "  Found " << allPaths.size() << " path(s):\n\n";
        for (int i = 0; i < (int)allPaths.size(); i++) {
            cout << "  Path " << i + 1 << " (Distance: "
                 << allPaths[i].second << " km): ";
            for (int j = 0; j < (int)allPaths[i].first.size(); j++) {
                cout << allPaths[i].first[j];
                if (j < (int)allPaths[i].first.size() - 1) cout << " -> ";
            }
            cout << "\n";
        }

        auto end = chrono::high_resolution_clock::now();
        cout << "\n  Time: "
             << chrono::duration_cast<chrono::microseconds>(end - start).count()
             << " microseconds\n";
    }

    // ============================================================
    // 5. PRIM'S MINIMUM SPANNING TREE (Greedy)
    // ============================================================
    void primsMST() {
        cout << "\n  [PRIM'S ALGORITHM - Minimum Spanning Tree]\n\n";

        if (nodeMap.empty())
            throw runtime_error("Graph is empty!");

        auto start = chrono::high_resolution_clock::now();

        map<string, bool> inMST;
        map<string, int>  key;
        map<string, string> parent;

        for (auto& p : nodeMap) {
            inMST[p.first] = false;
            key[p.first]   = INT_MAX;
        }

        // Start from first node
        string startNode = nodeMap.begin()->first;
        key[startNode]   = 0;

        int totalCost = 0;
        int edgesAdded = 0;

        cout << "  Edge Added              | Distance\n";
        cout << "  ------------------------|---------\n";

        for (int count = 0; count < (int)nodeMap.size(); count++) {
            // Pick min key vertex not in MST (Greedy selection)
            string u = "";
            int minKey = INT_MAX;
            for (auto& p : nodeMap) {
                if (!inMST[p.first] && key[p.first] < minKey) {
                    minKey = key[p.first];
                    u = p.first;
                }
            }

            if (u.empty()) break;
            inMST[u] = true;

            if (parent.find(u) != parent.end()) {
                cout << "  " << setw(12) << left << parent[u]
                     << " <--> " << setw(12) << left << u
                     << "| " << key[u] << " km\n";
                totalCost += key[u];
                edgesAdded++;
            }

            Node* node = nodeMap[u];
            for (int i = 0; i < node->getNeighborCount(); i++) {
                string v      = node->getNeighbor(i)->getName();
                int    weight = node->getWeight(i);
                if (!inMST[v] && weight < key[v]) {
                    key[v]    = weight;
                    parent[v] = u;
                }
            }
        }

        cout << "  ------------------------|---------\n";
        cout << "  Total MST Cost: " << totalCost << " km\n";
        cout << "  Edges in MST: " << edgesAdded << "\n";

        auto end = chrono::high_resolution_clock::now();
        cout << "  Time: "
             << chrono::duration_cast<chrono::microseconds>(end - start).count()
             << " microseconds\n";
    }

    // ============================================================
    // ALGORITHM COMPARISON
    // ============================================================
    void compareAlgorithms(const string& src, const string& dest) {
        cout << "\n  [ALGORITHM PERFORMANCE COMPARISON]\n";
        cout << "  From: " << src << " --> To: " << dest << "\n";
        cout << "  ==========================================\n";

        // Time Dijkstra
        auto t1 = chrono::high_resolution_clock::now();
        try { dijkstra(src, dest); } catch (...) {}
        auto t2 = chrono::high_resolution_clock::now();

        // Time BFS
        auto t3 = chrono::high_resolution_clock::now();
        try { bfs(src); } catch (...) {}
        auto t4 = chrono::high_resolution_clock::now();

        cout << "\n  ==========================================\n";
        cout << "  SUMMARY:\n";
        cout << "  Dijkstra : "
             << chrono::duration_cast<chrono::microseconds>(t2 - t1).count()
             << " microseconds\n";
        cout << "  BFS      : "
             << chrono::duration_cast<chrono::microseconds>(t4 - t3).count()
             << " microseconds\n";
        cout << "  ==========================================\n";
    }
};

#endif
