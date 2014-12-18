// # 2014 Walking Software
#ifndef __DATABASELOADER_HPP_
#define __DATABASELOADER_HPP_

#include "../graphLibrary/src/BaseDatabaseLoader.hpp"
#include "CustomClasses/Graph.hpp"
#include "CustomClasses/Node.hpp"
#include "CustomClasses/Edge.hpp"

class DatabaseLoader : public graphDB::BaseDatabaseLoader{

	public:
		DatabaseLoader(std::string filename, Graph &graph) : BaseDatabaseLoader(filename, graph){} 
		~DatabaseLoader(){}
		void loadDatabase();
	// private:
	// 	std::string mFileName;
	// 	Graph &mGraph;
};
#endif