#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Node {
private:
    int index; // ez a mostani csucs indexe
    double x; // a csucs terbeli x koordinataja
    double y; // a csucs terbeli y koordinataja
    std::vector<std::pair<int, int> > Connections; // tarolja a kapcsolt csucsok indexeit
    double dist_from_zero;
    bool visited;
    
    public:

    static int NumNodes; // hany csucs van osszesen
    static std::vector<int> AllNodes; //eltarolja a csucsok indexeit
    //ctor terbeli koordinatakkal
    Node(int i, double x_pos, double y_pos, double d, bool v) : index(i), x(x_pos), y(y_pos), dist_from_zero(d), visited(v) {
        NumNodes++;
        AllNodes.push_back(i);
    }

    //ctor random terbeli koordinatakkal
    Node(int i) : index(i), x( rand() % 700 ), y( rand() % 550 ), dist_from_zero( 10000 ), visited(false) {
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
    const std::vector<std::pair<int, int> >& GetConnectionsLoud(std::string node_name = "") const{
        if(Connections.size() == 0){
            std::cout <<"All connections of node " << node_name << ": No connections!"<< std::endl;
            return Connections;
        }
        std::cout << "All connections of node " << node_name << ": [";
        for(auto it = Connections.begin(); it < Connections.end() - 1; ++it){
            std::cout << "N: " << it->first << ", W: " << it->second << ", ";
        }
        std::cout << "N: " << (Connections.end() - 1)->first << ", W: " << (Connections.end() - 1)->second << ']' << std::endl;

        return Connections;
    }

    const std::vector<std::pair<int, int> >& GetConnections() const{
        return Connections;
    }

    //igy tudunk kapcsolatot adni egy kivalasztott csucshoz
    void Connect(Node& other, const int conn_w){
        Connections.push_back({other.index, conn_w});
        other.Connections.push_back({index, conn_w});
    }

    void Set_dist(double d){
        dist_from_zero = d;
    }

    double Get_dist(){
        return dist_from_zero;
    }

    void Set_visited(int v){
        visited = v;
    }

    void Add_visited(int a){
        visited += a;
    }

    bool Get_visited(){
        return visited;
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

            bool duplicate;
            int conn_ix_1, conn_ix_2, conn_w;
            do{
                duplicate = false;
                conn_ix_1 = rand() % len;
                conn_ix_2 = rand() % len;
                conn_w = rand() % 20;
                if (conn_ix_1 == conn_ix_2){
                    duplicate = true;
                }

                for(auto ix : graph[conn_ix_1].Connections){
                    if (ix.first == conn_ix_2){
                        duplicate = true;
                    }
                }
            }
            while(duplicate);

            graph[conn_ix_1].Connections.push_back({conn_ix_2, conn_w});
            graph[conn_ix_2].Connections.push_back({conn_ix_1, conn_w});
        }
}


// kiirja egymas ala minden csucs kapcsolatait
void PrintGraph( std::vector<Node>& graph ){
    for(std::vector<Node>::iterator it = graph.begin(); it < graph.end(); ++it){
        (*it).GetConnectionsLoud(std::to_string(it->index));
    }
}
// maga az utkereso algo
void Dijkstra(std::vector<Node>& Graph, int allexplored=0){
    if(allexplored == Graph.size()){std::cout << "kaki" << std::endl; return;}
    int min_dist = 10000; std::vector<Node>::iterator it_v = Graph.end(); // megkeressuk azt a felfedezetlen pontot amiknek a tavolsaga a legkisebb
    
    for(std::vector<Node>::iterator it = Graph.begin(); it != Graph.end(); ++it){
        if(! it->Get_visited() && it->Get_dist() < min_dist){
            min_dist = it->Get_dist();
            it_v = it;
        }
    }
    if(it_v == Graph.end()){return;}
    for(auto ic = it_v->GetConnections().begin(); ic != it_v->GetConnections().end(); ++ic){
        if(!Graph[ic->first].Get_visited() && it_v->Get_dist() + ic->second < Graph[ic->first].Get_dist()){
            Graph[ic->first].Set_dist(it_v->Get_dist() + ic->second);
        }
    }
    it_v->Set_visited(true);
    allexplored++;
    Dijkstra(Graph, allexplored);
}




int main(){

    srand(time(0));

    std::vector<Node> Graph_1 = SweepNodes(10);
    Graph_1[0].GetNumNodes();
    Graph_1[0].GetAllNodes();
    Graph_1[0].GetConnectionsLoud("Graph_1[0]");
    RndConnect(Graph_1, 10);
    Graph_1[0].GetConnectionsLoud("Graph_1[0]");
    
    std::cout << std::endl << std::endl;
    PrintGraph(Graph_1);
    Graph_1[0].Set_dist(0);
    Dijkstra(Graph_1, 0);


    // Graph_1[0].Set_dist(0); // a kiindulo csucs tavoldaga 0
    // Graph_1[0].Set_visited(true);
    // int all_visited = 0; // megnoveljuk egyel ha egy csucsot teljesen megvizsgaltunk
    // Node* current = &Graph_1[0];

    // while(all_visited < Graph_1.size()){ //addig megy ameddig minden csucsot vegigneztunk
    //     for(auto ix:current->GetConnectionsSilent()){ // az adott csucsnak megnezzuk a kapcsolatait
    //         int viz_now = Graph_1[ix.first].Get_visited();
    //         int viz_max = Graph_1[ix.first].GetConnections().size();
    //         if(viz_now != viz_max){ // ha meg nincs teljesen bejarva akkor odamegyunk
    //             if(Graph_1[ix.first].Get_dist() > current->Get_dist() + ix.second){ // ha az igy kapott tavolsag kisebb 
    //                 Graph_1[ix.first].Set_dist(current->Get_dist() + ix.second); // -> arra allitjuk a tavolsagat
    //             }
    //             Graph_1[ix.first].Add_visited(1); // megnoveljuk h hanyszor latogattuk a csucsot
    //             if(viz_now == viz_max){ // ha eppen most lett meg az utolso
    //                 all_visited++; // az osszes latogatasi szamot megemeljuk
    //             }
    //             current->Add_visited(1); // az aktualis kiindulo csucs latogatasi szamat is noveljuk
    //         }
    //     }
    //     all_visited++;
        
    //     for(auto ix : current->GetConnections()){ //most uj csucsot valasztunk
    //         if(Graph_1[ix.first].Get_visited() != Graph_1[ix.first].GetConnections().size()){ // ha van meg nem teljesen bejart csucs
    //             current = &Graph_1[ix.first]; // akkor az lesz az uj csucs
    //             break;
    //         }//! mit csinalunk a legvegen?


    //     }
    // }

    













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

        window.clear(sf::Color(35, 35, 45)); // sotet hatter


        std::vector<std::tuple<int, int, int> > edges;
        for(int i = 0; i < Node::NumNodes; ++i){
            std::vector<std::pair<int, int> > connections = Graph_1[i].GetConnections();
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
            text.setCharacterSize(12);
            text.setFillColor(sf::Color::Green);
            text.setString(std::to_string(std::get<2>(edge)));

            float midX = (float)(Graph_1[std::get<1>(edge)].GetX() + Graph_1[std::get<0>(edge)].GetX())/2;
            float midY = (float)(Graph_1[std::get<1>(edge)].GetY() + Graph_1[std::get<0>(edge)].GetY())/2;
            text.setPosition({midX, midY});

            window.draw(text);

            window.draw(line);
        }

        double node_radius = 5.0;
        for(int i = 0; i < Node::NumNodes; ++i){
            sf::CircleShape circle(node_radius);
            circle.setFillColor(sf::Color(70, 200, 120));
            circle.setOutlineThickness(3.0);
            circle.setOutlineColor(sf::Color(255, 255, 255));

            circle.setPosition({
                // sf::Vector2f( Graph_1[i].GetX(), Graph_1[i].GetY() );
                (float)Graph_1[i].GetX() - node_radius,
                (float)Graph_1[i].GetY() - node_radius
            });
            window.draw(circle);

            sf::Text dist_text(font);
            dist_text.setCharacterSize(18);
            dist_text.setFillColor(sf::Color::White);
            int dist_val = (int)Graph_1[i].Get_dist();
            dist_text.setString(std::to_string(dist_val));
            dist_text.setPosition({
                (float)(Graph_1[i].GetX()),
                (float)(Graph_1[i].GetY())
            });

            window.draw(dist_text);
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


