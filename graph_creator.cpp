#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Node {
private:
    int index; // ez a mostani csucs indexe
    std::vector<int> Connections; // tarolja a kapcsolt csucsok indexeit
    static int NumNodes; // hany csucs van osszesen
    static std::vector<int> AllNodes; //eltarolja a csucsok indexeit

public:
    //ctor
    Node(int i) : index(i) {
        NumNodes++;
        AllNodes.push_back(i);
    }

    //visszaadja egy csucs indexet (foleg teszteleshez)
    int GetIndex(){
        std::cout << index << std::endl;
        return index;
    }

    // ez e fuggveny visszaadja es kiirja a kivant csucs kapcsolatait
    std::vector<int> GetConnections(std::string node_name = ""){
        if(Connections.size() == 0){
            std::cout <<"All connections of node " << node_name << ": No connections!"<< std::endl;
            return Connections;
        }
        std::cout << "All connections of node " << node_name << ": [";
        for(std::vector<int>::iterator it = Connections.begin(); it < Connections.end() - 1; ++it){
            std::cout << *it << ", ";
        }
        std::cout << *(Connections.end() - 1) << ']' << std::endl;

        return Connections;
    }

    //igy tudunk kapcsolatot adni egy kivalasztott csucshoz
    void Connect(Node& other){
        Connections.push_back(other.index);
        other.Connections.push_back(index);
    }

    // visszaadja es kiirja h hany csucs van osszesen
    int GetNumNodes(){
        std::cout << NumNodes << std::endl;
        return NumNodes;
    }

    // kiirjuk es visszaadjuk az osszes csucs indexet
    std::vector<int> GetAllNodes(){
        std::cout << "All node indexes: [";
        for(std::vector<int>::iterator it = AllNodes.begin(); it <AllNodes.end() - 1; ++it){
            std::cout << *it << ", ";
        }
        std::cout << *(AllNodes.end() - 1) << ']' << std::endl;
        return AllNodes;
    }

    //random kapcsolatokat kreal egy meglevo grafban
    friend void RndConnect( std::vector<Node>& graph, int max_connections );

    friend void PrintGraph( std::vector<Node>& graph );
};





//inicializaljuk a statikus valtozoinkat
int Node::NumNodes = 0;
std::vector<int> Node::AllNodes;

// elkesziti a graf csucsait. 0-tol a kivant szamig elindexeli a csucsokat
std::vector<Node> SweepNodes(const int& how_many_nodes){
    std::vector<Node> Graph;
    for(int i = 0; i < how_many_nodes; ++i){
        Graph.push_back(Node(i));
    }
    return Graph;
}

//random kapcsolatokat kreal egy meglevo grafban
void RndConnect( std::vector<Node>& graph, int max_connections ){
    int len = graph.size();
        // it->Connections.clear();
        for(int j = 0; j < max_connections; ++j){
            int conn_ix_1 = rand() % len;
            int conn_ix_2 = rand() % len;
            
            while(conn_ix_1 == conn_ix_2){
                conn_ix_1 = rand() % len;
                conn_ix_2 = rand() % len;
            }
            graph[conn_ix_1].Connections.push_back(conn_ix_2);
            graph[conn_ix_2].Connections.push_back(conn_ix_1);
        }
}


// kiirja egymas ala minden csucs kapcsolatait
void PrintGraph( std::vector<Node>& graph ){
    for(std::vector<Node>::iterator it = graph.begin(); it < graph.end(); ++it){
        (*it).GetConnections(std::to_string(it->index));
    }
}


int main(){

    srand(time(0));

    std::vector<Node> Graph_1 = SweepNodes(10);
    Graph_1[0].GetNumNodes();
    Graph_1[0].GetAllNodes();
    Graph_1[0].GetConnections("Graph_1[0]");
    RndConnect(Graph_1, 10);
    Graph_1[0].GetConnections("Graph_1[0]");
    
    std::cout << std::endl << std::endl;
    PrintGraph(Graph_1);








    return 0;
}


    // Node alma(4);
    // alma.GetConnections("alma");
    // Node korte(3);
    // korte.GetConnections("korte");
    // alma.Connect(korte);

    // alma.GetConnections("alma");
    // korte.GetConnections("korte");


