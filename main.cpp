#include "FileManager.h"
#include <iostream>
#include <limits>
using namespace std;

// ============================================================
// UTILITY FUNCTIONS
// ============================================================
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader() {
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════╗\n";
    cout << "  ║   SMART MEMORY-BASED GRAPH NAVIGATOR             ║\n";
    cout << "  ║   C++ + DAA Mini Project  | By Gurudutt Tiwari   ║\n";
    cout << "  ╚══════════════════════════════════════════════════╝\n";
}

void printMenu() {
    cout << "\n";
    cout << "  ┌─────────────────────────────────────────────────┐\n";
    cout << "  │                  MAIN MENU                      │\n";
    cout << "  ├─────────────────────────────────────────────────┤\n";
    cout << "  │  [GRAPH OPERATIONS]                             │\n";
    cout << "  │  1. Add Location (Node)                         │\n";
    cout << "  │  2. Add Road (Edge with Distance)               │\n";
    cout << "  │  3. Remove Location                             │\n";
    cout << "  │  4. Remove Road                                 │\n";
    cout << "  │  5. Display Full Graph                          │\n";
    cout << "  ├─────────────────────────────────────────────────┤\n";
    cout << "  │  [DAA ALGORITHMS]                               │\n";
    cout << "  │  6. Shortest Path - Dijkstra's Algorithm        │\n";
    cout << "  │  7. BFS Traversal                               │\n";
    cout << "  │  8. DFS Traversal                               │\n";
    cout << "  │  9. Find ALL Paths - Backtracking               │\n";
    cout << "  │  10. Minimum Spanning Tree - Prim's Algorithm   │\n";
    cout << "  │  11. Compare Algorithm Performance              │\n";
    cout << "  ├─────────────────────────────────────────────────┤\n";
    cout << "  │  [FILE HANDLING]                                │\n";
    cout << "  │  12. Save Graph to File                         │\n";
    cout << "  │  13. Load Graph from File                       │\n";
    cout << "  │  14. Load Sample City Data                      │\n";
    cout << "  ├─────────────────────────────────────────────────┤\n";
    cout << "  │  [SYSTEM]                                       │\n";
    cout << "  │  15. Memory Management Report                   │\n";
    cout << "  │  0.  Exit                                       │\n";
    cout << "  └─────────────────────────────────────────────────┘\n";
    cout << "  Enter your choice: ";
}

string getInput(const string& prompt) {
    string val;
    cout << "  " << prompt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, val);
    return val;
}

string getInputNoFlush(const string& prompt) {
    string val;
    cout << "  " << prompt;
    getline(cin, val);
    return val;
}

int getInt(const string& prompt) {
    int val;
    cout << "  " << prompt;
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid! Enter a number: ";
    }
    return val;
}

// ============================================================
// MAIN FUNCTION
// ============================================================
int main() {
    FileManager navigator;
    int choice;

    printHeader();
    cout << "\n  Welcome! Load sample data to get started quickly.\n";

    while (true) {
        printMenu();
        cin >> choice;

        try {
            switch (choice) {

                // ---- GRAPH OPERATIONS ----

                case 1: {
                    string name = getInput("Enter location name: ");
                    navigator.addNode(name);
                    break;
                }

                case 2: {
                    string src  = getInput("Enter source location: ");
                    string dest = getInputNoFlush("Enter destination location: ");
                    int dist    = getInt("Enter distance (km): ");
                    navigator.addEdge(src, dest, dist);
                    break;
                }

                case 3: {
                    string name = getInput("Enter location to remove: ");
                    navigator.removeNode(name);
                    break;
                }

                case 4: {
                    string src  = getInput("Enter source location: ");
                    string dest = getInputNoFlush("Enter destination location: ");
                    navigator.removeEdge(src, dest);
                    break;
                }

                case 5: {
                    navigator.display();
                    break;
                }

                // ---- DAA ALGORITHMS ----

                case 6: {
                    string src  = getInput("Enter source location: ");
                    string dest = getInputNoFlush("Enter destination location: ");
                    navigator.dijkstra(src, dest);
                    break;
                }

                case 7: {
                    string src = getInput("Enter starting location for BFS: ");
                    navigator.bfs(src);
                    break;
                }

                case 8: {
                    string src = getInput("Enter starting location for DFS: ");
                    navigator.dfs(src);
                    break;
                }

                case 9: {
                    string src  = getInput("Enter source location: ");
                    string dest = getInputNoFlush("Enter destination location: ");
                    navigator.findAllPaths(src, dest);
                    break;
                }

                case 10: {
                    navigator.primsMST();
                    break;
                }

                case 11: {
                    string src  = getInput("Enter source location: ");
                    string dest = getInputNoFlush("Enter destination location: ");
                    navigator.compareAlgorithms(src, dest);
                    break;
                }

                // ---- FILE HANDLING ----

                case 12: {
                    string filename = getInput("Enter filename to save (e.g. graph.txt): ");
                    navigator.saveGraph(filename);
                    break;
                }

                case 13: {
                    string filename = getInput("Enter filename to load: ");
                    navigator.loadGraph(filename);
                    break;
                }

                case 14: {
                    navigator.loadSampleData();
                    break;
                }

                // ---- SYSTEM ----

                case 15: {
                    navigator.memoryReport();
                    break;
                }

                case 0: {
                    cout << "\n  ╔══════════════════════════════════════╗\n";
                    cout << "  ║  Thank you! Graph memory freed.      ║\n";
                    cout << "  ║  All Node* pointers deleted safely.  ║\n";
                    cout << "  ╚══════════════════════════════════════╝\n\n";
                    return 0;
                }

                default:
                    cout << "  Invalid choice! Please enter 0-15.\n";
            }

        } catch (const runtime_error& e) {
            cout << "\n  [ERROR] " << e.what() << "\n";
        } catch (const invalid_argument& e) {
            cout << "\n  [INVALID INPUT] " << e.what() << "\n";
        } catch (...) {
            cout << "\n  [UNKNOWN ERROR] Something went wrong.\n";
        }

        cout << "\n  Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    return 0;
}
