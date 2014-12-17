#ifndef __CUSTOMGRAPH__
#define __CUSTOMGRAPH__

#include "../../graphLibrary/src/GraphObjects/Graph.hpp"
class CustomGraph : public graphDB::Graph {

public:
	void printHello() { std::cout << "hello world" << std::endl; }
private:
	int i;
};
#endif