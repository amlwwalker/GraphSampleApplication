#ifndef __CUSTOMNODE__
#define __CUSTOMNODE__

#include "../../graphLibrary/src/GraphObjects/Node.hpp"
class CustomNode : public graphDB::Node {

public:
	void printHello() { std::cout << "hello world" << std::endl; }
private:
	int i;
};
#endif