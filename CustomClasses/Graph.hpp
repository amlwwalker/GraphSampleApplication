#ifndef __GRAPH__HPP__
#define __GRAPH__HPP__

#include "../../graphLibrary/src/GraphObjects/BaseGraph.hpp"
class Graph : public graphDB::BaseGraph {

public:
	void printHello() { std::cout << "hello world" << std::endl; }
private:
	int i;
};
#endif