//# 2014 Walking Software
 
#include "main.h"

Graph *graph;
DatabaseLoader *db;

//WEB SERVER STUFF: WARNING VULNERABLE TO POTENTIAL ATTACK
//currently this may crash the program if an invalid parameter 
//is parsed in.
static const char *s_no_cache_header =
  "Cache-Control: max-age=0, post-check=0, "
  "pre-check=0, no-store, no-cache, must-revalidate\r\n";

static void showAll(struct mg_connection *conn) {
	char length[100];
  std::cout << "show all" << std::endl;
	mg_get_var(conn, "length", length, sizeof(length));
  mg_printf_data(conn, graph->printEverything(*graph->getNodes(),*graph->getEdges(), strtod(length, NULL)).c_str());
}

static void showAllNodes(struct mg_connection *conn) {
	char length[100];
	mg_get_var(conn, "length", length, sizeof(length));
  mg_printf_data(conn, graph->printNodesToJson(*graph->getNodes(), strtod(length, NULL)).c_str());
}

static void showAllEdges(struct mg_connection *conn) {
	char length[100];
	mg_get_var(conn, "length", length, sizeof(length));
  mg_printf_data(conn, graph->printEdgesToJson(*graph->getEdges(), strtod(length, NULL)).c_str());
}

static void showNode(struct mg_connection *conn) {
	char nodeId[100];
	mg_get_var(conn, "id", nodeId, sizeof(nodeId));
	//crashes if the id doesnt exist (or isnt set)
	graphDB::BaseNode *n = graph->findNodeWithId(nodeId);
	if (n == NULL){
		mg_printf_data(conn, "Sorry no node found...");
		return;
	}

  mg_printf_data(conn, graph->printNodeToJson(n).c_str());
}
static void graphNeighbouringNodes(struct mg_connection *conn) {
  char nodeId[100];
  mg_get_var(conn, "id", nodeId, sizeof(nodeId));
  //crashes if the id doesnt exist (or isnt set)
  graphDB::BaseNode *n = graph->findNodeWithId(nodeId); //finds the first one?
  if (n == NULL){
    mg_printf_data(conn, "Sorry no node found...");
    return;
  }
  std::vector<graphDB::BaseNode*> *nodes;
  nodes = new (std::vector<graphDB::BaseNode*>);
  graph->getNeighbouringNodes(n, *nodes);
  mg_printf_data(conn, graph->printEverything(*nodes, graph->getEdgesOnNode(n)).c_str());
  delete(nodes);
}

static void showEdge(struct mg_connection *conn) {
	char edgeId[100];
	mg_get_var(conn, "id", edgeId, sizeof(edgeId));
	//crashes if the id doesnt exist (or isnt set)
	graphDB::BaseEdge *e = graph->findEdgeWithId(edgeId);
	if (e == NULL){
		mg_printf_data(conn, "Sorry no edge found...");
		return;
	}

  mg_printf_data(conn, graph->printEdgeToJson(e).c_str());
}

static void exampleCalc(struct mg_connection *conn) {
  char n1[100], n2[100]; //could be buffer overflowed???12345

  // Get form variables
  mg_get_var(conn, "n1", n1, sizeof(n1));
  mg_get_var(conn, "n2", n2, sizeof(n2));

  mg_printf_data(conn, "{ \"result\": %lf }", strtod(n1, NULL) + strtod(n2, NULL));

}

static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
  switch (ev) {
    case MG_AUTH: return MG_TRUE;
    case MG_REQUEST:
      if (!strcmp(conn->uri, "/example/calc")) {
        exampleCalc(conn);
        return MG_TRUE;
      }
      else if (!strcmp(conn->uri, "/showAll")) {
        showAll(conn);
        return MG_TRUE;
      }
      else if (!strcmp(conn->uri, "/showAllNodes")) {
        showAllNodes(conn);
        return MG_TRUE;
      }
      else if (!strcmp(conn->uri, "/showNode")) {
        showNode(conn);
        return MG_TRUE;
      }
      else if (!strcmp(conn->uri, "/displayNode")) {
        graphNeighbouringNodes(conn);
        return MG_TRUE;
      }
      else if (!strcmp(conn->uri, "/showAllEdges")) {
        showAllEdges(conn);
        return MG_TRUE;
      }
      else if (!strcmp(conn->uri, "/showEdge")) {
        showEdge(conn);
        return MG_TRUE;
      }
      else if (!strcmp(conn->uri, "/graph")) {
        mg_send_file(conn, "web/graph.html", s_no_cache_header);
        return MG_MORE;
      }
        mg_send_file(conn, "web/index.html", s_no_cache_header);
        return MG_MORE;
    default: return MG_FALSE;
  }
}

void startWebServer(){
	struct mg_server *server;	

	// // Create and configure the server
  server = mg_create_server(NULL, ev_handler);
  mg_set_option(server, "listening_port", "8000");

  // Serve request. Hit Ctrl-C to terminate the program
  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
  for (;;) {
  mg_poll_server(server, 1000);
}

  // Cleanup, and free server instance
  mg_destroy_server(&server);
}

int main ( int argc, char *argv[] )
{	
	if ( argc != 2 ) { // argc should be 2 for correct execution
    // We print argv[0] assuming it is the program name
    	std::cout <<"usage: "<< argv[0] <<" <file name>" << std::endl ;
		return 0;
	}
//The idea is to load all of the json in the mentioned file
//and create a graph of the data
//the output that to the browser
  Edge *e;
  e = new (Edge);
  e->setWeight(3);
	graph = new Graph();
	  	//creating nodes and edges from a JSON file
	db = new DatabaseLoader(argv[1], *graph);
  std::cout << "graph size: " << graph->getNodes()->size() << std::endl;

	db->loadDatabase();	
  delete(db); //could kill something we need

  std::cout << "graph size after load: " << graph->getNodes()->size() << std::endl;
	startWebServer();
  return 0;
}

