#ifndef __NODE__
#define __NODE__

#include "../../graphLibrary/src/GraphObjects/BaseNode.hpp"
class Node : public graphDB::BaseNode {

public:
	void printHello() { std::cout << "hello world" << std::endl; }
private:
	int i;
};
#endif