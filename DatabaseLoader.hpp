// # 2014 Walking Software

#include <string.h>
#include <iostream>
#include <vector>
#include "CustomClasses/Node.hpp"
#include "CustomClasses/Edge.hpp"
#include "CustomClasses/Graph.hpp"
#include "../rapidjson/document.h"		// rapidjson's DOM-style API
#include "../rapidjson/prettywriter.h"	// for stringify JSON
#include "../rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output

class DatabaseLoader {

	public:
		DatabaseLoader(std::string filename, Graph &graph);
		~DatabaseLoader();
		void loadDatabase();
	private:
		std::string mFileName;
		Graph &mGraph;
};