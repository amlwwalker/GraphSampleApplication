// # 2014 Walking Software

#include "DatabaseLoader.hpp"
#include <iomanip>      // std::setprecision

DatabaseLoader::DatabaseLoader(std::string aFileName, Graph &graph) 
										: mFileName(aFileName), mGraph(graph) {
	//constructor
}
DatabaseLoader::~DatabaseLoader(){
//destructor
}
void DatabaseLoader::loadDatabase(){
	FILE * pFile = std::fopen (mFileName.c_str() , "r");
	rapidjson::FileStream fs(pFile);
	rapidjson::Document document;
	document.ParseStream<0>(fs);

	printf("\nParsing document succeeded.\n");


//loading nodes:
	const rapidjson::Value& data = document["Data"];
	assert(data.IsArray());

//for each object in the data array
	int uniq = 0;
	Node *lastNode;
	for (rapidjson::SizeType i = 0; i < data.Size(); i++) {
		assert(data[i].IsObject());	
		
		Node *tempNode;
		tempNode = new(Node);
		//The group is its index based on its position in the list
		tempNode->setGroup(uniq);
		
		mGraph.addNode(tempNode);
		
		std::ostringstream timeStampString;
		timeStampString << std::setprecision(15) << data[i]["TimeStamp"].GetDouble();
		
		tempNode->setId(timeStampString.str());

		if (lastNode != NULL){
				Edge* majorEdge;
				majorEdge = new(Edge);

				majorEdge->setFrom(lastNode);
				majorEdge->setTo(tempNode);

				lastNode->addEdge(majorEdge);
				tempNode->addEdge(majorEdge);

				majorEdge->setWeight(3);

				majorEdge->setId(std::to_string(uniq));
				mGraph.addEdge(majorEdge);
		}

			for(rapidjson::Value::ConstMemberIterator it=data[i]["Odds"].MemberBegin(); it != data[i]["Odds"].MemberEnd(); it++) {
					uniq++;
					assert(it->value.IsObject());
					
					tempNode->addProperty("children", it->name.GetString());

					Node *tempBookieNode;
					tempBookieNode = new(Node);

					tempBookieNode->setGroup(uniq);
					mGraph.addNode(tempBookieNode);

					tempBookieNode->setId(it->name.GetString());
					tempBookieNode->addProperty("parent", timeStampString.str());
					Edge *tempBookieEdge;
					tempBookieEdge = new(Edge);

					tempBookieEdge->setTo(tempNode);
					tempBookieEdge->setFrom(tempBookieNode);

					tempNode->addEdge(tempBookieEdge);
					tempBookieNode->addEdge(tempBookieEdge);

					tempBookieEdge->setId(std::to_string(uniq));
					tempBookieEdge->setWeight(3);
					mGraph.addEdge(tempBookieEdge);

					for(rapidjson::Value::ConstMemberIterator innerIt=it->value.MemberBegin(); innerIt != it->value.MemberEnd(); innerIt++) {
						
						std::string name = innerIt->name.GetString();
						double value = innerIt->value.GetDouble();

						uniq++;
						
						tempBookieNode->addProperty("children", name);

						Node *tempOddNode;
						tempOddNode = new(Node);
						tempOddNode->setGroup(uniq);
						mGraph.addNode(tempOddNode);
						
						tempOddNode->setId(name);
						tempOddNode->addProperty("parent", tempBookieNode->getId());
						tempOddNode->addProperty("price", std::to_string(value));
						Edge *tempOddEdge;
						tempOddEdge = new(Edge);
						tempOddEdge->setTo(tempBookieNode);
						tempOddEdge->setFrom(tempOddNode);

						tempBookieNode->addEdge(tempOddEdge);
						tempOddNode->addEdge(tempOddEdge);

						tempOddEdge->setId(std::to_string(uniq)); //random name

						tempOddEdge->setWeight(3);
						mGraph.addEdge(tempOddEdge);	
					}	
			}
			lastNode = tempNode;
			uniq++;
	}
}

