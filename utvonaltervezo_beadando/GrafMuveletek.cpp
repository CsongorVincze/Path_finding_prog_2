// Vincze Csongor BG8SFC
#include "GrafMuveletek.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <stdexcept>

Graf<Node> SweepNodes(int how_many_nodes) {
    // Az eredeti statikus számlálókat új gráf készítésekor nullázzuk.
    Node::NumNodes = 0;
    Node::AllNodes.clear();

    // gráf létrehozása
    Graf<Node> Graph;
    for (int i = 0; i < how_many_nodes; ++i) {
        // A Node(int) konstruktor véletlen koordinátákat ad a csúcsnak.
        Graph.push_back(Node(i));
    }
    return Graph;
}

void RndConnect(Graf<Node>& graph, int max_connections) {
    // random csúcspárokat választunk
    int len = static_cast<int>(graph.size());
    if (len < 2) {
        throw std::runtime_error("Legalább két csúcs kell a kapcsolatokhoz.");
    }

    for (int j = 0; j < max_connections; ++j) {
        bool duplicate;
        int conn_ix_1;
        int conn_ix_2;
        int conn_w;

        do {
            // Addig próbálkozunk, amíg elkeruljuk az önhurkot és a duplikalt elelet
            duplicate = false;
            conn_ix_1 = rand() % len;
            conn_ix_2 = rand() % len;
            conn_w = rand() % 20;
            
            if (conn_w == 0) {
                conn_w = 1;
            }

            if (conn_ix_1 == conn_ix_2) {
                duplicate = true;
            }

            // Megnézzük, hogy a kisorsolt él létezik-e már.
            for (std::vector<Ut>::const_iterator it = graph[conn_ix_1].GetConnections().begin();
                 it != graph[conn_ix_1].GetConnections().end(); ++it) {
                if (it->GetCel() == conn_ix_2) {
                    duplicate = true;
                }
            }
        } while (duplicate);

        // A Connect kétirányú kapcsolatot hoz létre.
        graph[conn_ix_1].Connect(graph[conn_ix_2], conn_w);
    }
}

void PrintGraph(Graf<Node>& graph) {
    // Konzolos ellenőrzéshez
    for (Graf<Node>::iterator it = graph.begin(); it < graph.end(); ++it) {
        (*it).GetConnectionsLoud(std::to_string(it->GetIndexScilent()));
    }
}

void Dijkstra(Graf<Node>& Graph, int allexplored) {
    // Rekurzív Dijkstra függvény
    if (allexplored == static_cast<int>(Graph.size())) {
        std::cout << "vége" << std::endl;
        // Nincs több elérhető, feldolgozatlan csúcs.
        return;
    }

    int min_dist = 10000;
    Graf<Node>::iterator it_v = Graph.end();

    // Megkeressük a még nem látogatott, legkisebb távolságú csúcsot.
    for (Graf<Node>::iterator it = Graph.begin(); it != Graph.end(); ++it) {
        if (!it->Get_visited() && it->Get_dist() < min_dist) {
            min_dist = static_cast<int>(it->Get_dist());
            it_v = it;
        }
    }

    if (it_v == Graph.end()) {
        return;
    }

    // A kiválasztott csúcsból induló élekkel frissítjük a szomszédokat.
    for (std::vector<Ut>::const_iterator ic = it_v->GetConnections().begin();
         ic != it_v->GetConnections().end(); ++ic) {
        if (!Graph[ic->GetCel()].Get_visited() &&
            it_v->Get_dist() + ic->GetSuly() < Graph[ic->GetCel()].Get_dist()) {
            Graph[ic->GetCel()].Set_dist(it_v->Get_dist() + ic->GetSuly());
            Graph[ic->GetCel()].Set_from(it_v->GetIndex());
        }
    }

    it_v->Set_visited(true);
    allexplored++;
    //rekurzívan hivunk
    Dijkstra(Graph, allexplored);
}

std::vector<int> Trace(Graf<Node>& Graph, int destination) {
    // A cél indexét ellenőrizzük, mert ezt a felhasználó írja be.
    if (destination < 0 || destination >= static_cast<int>(Graph.size())) {
        throw std::out_of_range("Érvénytelen célcsúcs.");
    }

    Graph[0].Set_from(-1);
    int i = destination;
    std::vector<int> tr;
    // A from mezőkön visszalépünk a kezdőcsúcsig.
    while (i >= 0) {
        tr.push_back(i);
        i = Graph[i].Get_from();
    }
    std::reverse(tr.begin(), tr.end());
    // A visszaadott útvonal már kezdőponttól célpontig halad.
    return tr;
}

void SaveGraph(const Graf<Node>& graph, const std::string& file_name) {
    // A teljes gráfot soros szövegfájlba mentjük.
    std::ofstream file(file_name.c_str());
    if (!file) {
        throw std::runtime_error("Nem sikerült megnyitni a mentési fájlt, bocsi.");
    }

    file << graph.size() << '\n';
    // Minden csúcs saját operator<< művelete írja a részletes adatokat.
    for (Graf<Node>::const_iterator it = graph.begin(); it != graph.end(); ++it) {
        file << *it << '\n';
    }
}

Graf<Node> LoadGraph(const std::string& file_name) {
    // A SaveGraph által írt formátumot olvassuk vissza.
    std::ifstream file(file_name.c_str());
    if (!file) {
        throw std::runtime_error("Nem sikerült megnyitni a betöltendő fájlt, bocsi.");
    }

    std::size_t size;
    file >> size;
    Graf<Node> graph(size);
    Node::NumNodes = static_cast<int>(size);
    Node::AllNodes.clear();

    for (std::size_t i = 0; i < size; ++i) {
        // A Node operator>> visszaállítja a csúcs kapcsolatait is.
        file >> graph[i];
        Node::AllNodes.push_back(static_cast<int>(i));
    }

    return graph;
}
