#include <iostream>
#include <vector>

class Nodes {
private:
    int index; // ez a mostani csucs indexe
    std::vector<int> connections; // tarolja a kapcsolt csucsok indexeit
    static int NumNodes; // hany csucs van osszesen
    static std::vector<int> AllNodes; //eltarolja a csucsok indexeit

public:
    Nodes(int i) : index(i) {
        NumNodes++;
        AllNodes.push_back(i);
    }

    int GetIndex(){
        std::cout << index << std::endl;
        return index;
    }

    void AddConnection(const int& masik){
        connections.push_back(masik);
    }

    int GetNumNodes(){
        std::cout << NumNodes << std::endl;
        return NumNodes;
    }

    std::vector<int> GetAllNodes(){ // kiirjuk es visszaadjuk az osszes csucs indexet
        std::cout << "All node indexes: [";
        for(std::vector<int>::iterator it = AllNodes.begin(); it <AllNodes.end() - 1; ++it){
            std::cout << *it << ", ";
        }
        std::cout << *(AllNodes.end() - 1) << ']' << std::endl;
        return AllNodes;
    }

};

int Nodes::NumNodes = 0;
std::vector<int> Nodes::AllNodes;


int main(){


    Nodes alma(3);
    alma.GetIndex();

    Nodes korte(4);

    alma.GetNumNodes();
    alma.GetAllNodes();
    // std::cout << Nodes::NumNodes << std::endl;


    // std::vector<Nodes> graph(5);




    return 0;
}


