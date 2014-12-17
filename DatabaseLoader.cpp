// # 2014 Walking Software

#include "DatabaseLoader.hpp"
#include <iomanip>      // std::setprecision

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
		tempNode = (Node *) mGraph.addNode();
		//The group is its index based on its position in the list
		tempNode->setGroup(uniq);
		
		
		
		std::ostringstream timeStampString;
		timeStampString << std::setprecision(15) << data[i]["TimeStamp"].GetDouble();
		
		tempNode->setName(timeStampString.str());

		if (lastNode != NULL){
				Edge* majorEdge;
				majorEdge = (Edge *)mGraph.addEdge();

				majorEdge->setFrom(lastNode);
				majorEdge->setTo(tempNode);

				// lastNode->addEdge(majorEdge);
				// tempNode->addEdge(majorEdge);

				majorEdge->setWeight(3);

				majorEdge->setName(std::to_string(uniq));

				
		}

			for(rapidjson::Value::ConstMemberIterator it=data[i]["Odds"].MemberBegin(); it != data[i]["Odds"].MemberEnd(); it++) {
					uniq++;
					assert(it->value.IsObject());
					
					tempNode->addProperty("children", it->name.GetString());

					Node *tempBookieNode;
					tempBookieNode = (Node *) mGraph.addNode();

					tempBookieNode->setGroup(uniq);
					

					tempBookieNode->setName(it->name.GetString());

					tempBookieNode->addProperty("parent", timeStampString.str());
					Edge *tempBookieEdge;
					tempBookieEdge = (Edge *) mGraph.addEdge();

					tempBookieEdge->setTo(tempNode);
					tempBookieEdge->setFrom(tempBookieNode);

					// tempNode->addEdge(tempBookieEdge);
					// tempBookieNode->addEdge(tempBookieEdge);

					tempBookieEdge->setName(std::to_string(uniq));

					tempBookieEdge->setWeight(3);
					

					for(rapidjson::Value::ConstMemberIterator innerIt=it->value.MemberBegin(); innerIt != it->value.MemberEnd(); innerIt++) {
						
						std::string name = innerIt->name.GetString();
						double value = innerIt->value.GetDouble();

						uniq++;
						
						tempBookieNode->addProperty("children", name);

						Node *tempOddNode;
						tempOddNode = (Node *) mGraph.addNode();
						tempOddNode->setGroup(uniq);
						
						
						tempOddNode->setName(name);

						tempOddNode->addProperty("parent", tempBookieNode->getId());
						tempOddNode->addProperty("price", std::to_string(value));
						Edge *tempOddEdge;
						tempOddEdge = (Edge *) mGraph.addEdge();
						tempOddEdge->setTo(tempBookieNode);
						tempOddEdge->setFrom(tempOddNode);

						// tempBookieNode->addEdge(tempOddEdge);
						// tempOddNode->addEdge(tempOddEdge);

						tempOddEdge->setName(std::to_string(uniq)); //random name

						tempOddEdge->setWeight(3);
							
					}	
			}
			lastNode = tempNode;
			uniq++;
	}
}

