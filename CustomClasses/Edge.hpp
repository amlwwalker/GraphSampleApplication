#ifndef __EDGE__
#define __EDGE__

#include "../../graphLibrary/src/GraphObjects/BaseEdge.hpp"
class Edge : public graphDB::BaseEdge {

public:
	void printHello() { std::cout << "hello world" << std::endl; }
private:
	int i;
};
#endif