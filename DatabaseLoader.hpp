// # 2014 Walking Software

#include <string.h>
#include <iostream>
#include <vector>
#include "CustomClasses/CustomNode.hpp"
#include "CustomClasses/CustomEdge.hpp"
#include "CustomClasses/CustomGraph.hpp"
#include "../rapidjson/document.h"		// rapidjson's DOM-style API
#include "../rapidjson/prettywriter.h"	// for stringify JSON
#include "../rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output

class DatabaseLoader {

	public:
		DatabaseLoader(std::string filename, CustomGraph &graph);
		~DatabaseLoader();
		void loadDatabase();
	private:
		std::string mFileName;
		CustomGraph &mGraph;
};