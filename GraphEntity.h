#ifndef GRAPHENTITY_H
#define GRAPHENTITY_H
#include "Node.h"
#include <iostream>
#include <string>
using namespace std;

// Abstract Base Class
class GraphEntity {
public:
    virtual void display() const = 0;
    virtual string getName() const = 0;
    virtual ~GraphEntity() {}
};

#endif
