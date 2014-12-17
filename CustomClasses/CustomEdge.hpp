#ifndef __CUSTOMEDGE__
#define __CUSTOMEDGE__

#include "../../graphLibrary/src/GraphObjects/Edge.hpp"
class CustomEdge : public graphDB::Edge {

public:
	void printHello() { std::cout << "hello world" << std::endl; }
private:
	int i;
};
#endif