#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <tuple>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Node {
private:
    int index; // ez a mostani csucs indexe
    double x; // a csucs terbeli x koordinataja
    double y; // a csucs terbeli y koordinataja
    std::vector<std::pair<int, int> > Connections; // tarolja a kapcsolt csucsok indexeit
    
    public:

    static int NumNodes; // hany csucs van osszesen
    static std::vector<int> AllNodes; //eltarolja a csucsok indexeit
    //ctor terbeli koordinatakkal
    Node(int i, double x_pos, double y_pos) : index(i), x(x_pos), y(y_pos) {
        NumNodes++;
        AllNodes.push_back(i);
    }

    //ctor random terbeli koordinatakkal
    Node(int i) : index(i), x( rand() % 800 ), y( rand() % 600 ) {
        NumNodes++;
        AllNodes.push_back(i);
    }


    //visszaadja egy csucs indexet (foleg teszteleshez)
    int GetIndex(){
        std::cout << index << std::endl;
        return index;
    }

    int GetIndexScilent(){
        return index;
    }

    double GetX() const{
        return x;
    }

    double GetY() const{
        return y;
    }

    // ez a fuggveny visszaadja es kiirja a kivant csucs kapcsolatait
    std::vector<std::pair<int, int> > GetConnections(std::string node_name = ""){
        if(Connections.size() == 0){
            std::cout <<"All connections of node " << node_name << ": No connections!"<< std::endl;
            return Connections;
        }
        std::cout << "All connections of node " << node_name << ": [";
        for(std::vector<std::pair<int, int> >::iterator it = Connections.begin(); it < Connections.end() - 1; ++it){
            std::cout << "N: " << it->first << ", W: " << it->second << ", ";
        }
        std::cout << "N: " << (Connections.end() - 1)->first << ", W: " << (Connections.end() - 1)->second << ']' << std::endl;

        return Connections;
    }

    std::vector<std::pair<int, int> > GetConnectionsSilent() const{
        return Connections;
    }

    //igy tudunk kapcsolatot adni egy kivalasztott csucshoz
    void Connect(Node& other, const int conn_w){
        Connections.push_back({other.index, conn_w});
        other.Connections.push_back({index, conn_w});
    }

    // visszaadja es kiirja h hany csucs van osszesen
    int GetNumNodes(){
        std::cout << NumNodes << std::endl;
        return NumNodes;
    }


    // kiirjuk es visszaadjuk az osszes csucs indexet
    std::vector<int> GetAllNodes(){
        std::cout << "All node indexes: [";
        for(std::vector<int>::iterator it = AllNodes.begin(); it < AllNodes.end() - 1; ++it){
            std::cout << *it << ", ";
        }
        std::cout << *(AllNodes.end() - 1) << ']' << std::endl;
        return AllNodes;
    }

    //random kapcsolatokat kreal egy meglevo grafban
    friend void RndConnect( std::vector<Node>& graph, const int max_connections );

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

            int conn_w = rand() % 20;
            
            while(conn_ix_1 == conn_ix_2){
                conn_ix_1 = rand() % len;
                conn_ix_2 = rand() % len;
            }
            graph[conn_ix_1].Connections.push_back({conn_ix_2, conn_w});
            graph[conn_ix_2].Connections.push_back({conn_ix_1, conn_w});
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


    












    sf::Font font;
    font.openFromFile("Retro Floral.otf");

    // ezt a reszt meg ird ujra
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Graf Vizualizacio (SFML)");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color(35, 35, 45)); // Sötét háttér


        std::vector<std::tuple<int, int, int> > edges;
        for(int i = 0; i < Node::NumNodes; ++i){
            std::vector<std::pair<int, int> > connections = Graph_1[i].GetConnectionsSilent();
            for(std::pair<int, int> conn : connections){
                if( i < conn.first ){
                    edges.push_back(std::make_tuple(i, conn.first, conn.second));
                }
            }
        }

        for(const auto edge : edges){
            sf::VertexArray line(sf::PrimitiveType::Lines, 2);
            line[0].position = sf::Vector2f( Graph_1[std::get<0>(edge)].GetX(), Graph_1[std::get<0>(edge)].GetY() );
            line[0].color = sf::Color(180, 180, 180, 150);

            line[1].position = sf::Vector2f( Graph_1[std::get<1>(edge)].GetX(), Graph_1[std::get<1>(edge)].GetY() );
            line[1].color = sf::Color(180, 180, 180, 150);

            sf::Text text(font);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::Green);
            text.setString(std::to_string(std::get<2>(edge)));

            float midX = (float)(Graph_1[std::get<1>(edge)].GetX() + Graph_1[std::get<0>(edge)].GetX())/2;
            float midY = (float)(Graph_1[std::get<1>(edge)].GetY() + Graph_1[std::get<0>(edge)].GetY())/2;
            text.setPosition({midX + 1, midY + 1});

            window.draw(text);

            window.draw(line);
        }

        double node_radius = 18.0;
        for(int i = 0; i < Node::NumNodes; ++i){
            sf::CircleShape circle(node_radius);
            circle.setFillColor(sf::Color(70, 200, 120));
            circle.setOutlineThickness(3.0);
            circle.setOutlineColor(sf::Color(255, 255, 255));

            circle.setPosition({
                // sf::Vector2f( Graph_1[i].GetX(), Graph_1[i].GetY() );
                Graph_1[i].GetX() - node_radius,
                Graph_1[i].GetY() - node_radius
            });
            window.draw(circle);
        }

        
        


        window.display();
    }







    return 0;
}


    // Node alma(4);
    // alma.GetConnections("alma");
    // Node korte(3);
    // korte.GetConnections("korte");
    // alma.Connect(korte);

    // alma.GetConnections("alma");
    // korte.GetConnections("korte");


