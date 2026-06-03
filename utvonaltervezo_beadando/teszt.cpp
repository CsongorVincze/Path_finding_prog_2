// Vincze Csongor BG8SFC
#include "GrafMuveletek.h"

#include <iostream>
#include <vector>

int main() {
    try {
        srand(1);

        // Fix gráfot használunk, hogy a teszt ne függjön a véletlentől.
        Graf<Node> graph = SweepNodes(5);
        graph[0].Connect(graph[1], 2);
        graph[1].Connect(graph[2], 3);
        graph[0].Connect(graph[3], 8);
        graph[3].Connect(graph[4], 1);
        graph[2].Connect(graph[4], 2);

        // A következő kiírások az eredeti konzolos ellenőrzésnek felelnek meg.
        std::cout << "Csúcsok száma: ";
        graph[0].GetNumNodes();
        graph[0].GetAllNodes();
        PrintGraph(graph);

        graph[0].Set_dist(0);
        Dijkstra(graph, 0);

        // A várt útvonal: 0 -> 1 -> 2 -> 4.
        std::vector<int> tr = Trace(graph, 4);
        std::cout << "Útvonal 0-ból 4-be: ";
        for (std::size_t i = 0; i < tr.size(); ++i) {
            if (i != 0) {
                std::cout << " -> ";
            }
            std::cout << tr[i];
        }
        std::cout << std::endl;

        SaveGraph(graph, "teszt_graf_mentes.txt");
        // A visszaolvasás azt ellenőrzi, hogy a perzisztencia működik.
        Graf<Node> loaded = LoadGraph("teszt_graf_mentes.txt");
        std::cout << "Visszaolvasott csúcsok száma: " << loaded.size() << std::endl;

        try {
            // Szándékosan hibás index, hogy a kivételkezelés is látszódjon.
            // Szándékosan hibás index, hogy a kivételkezelés is látszódjon.
            Trace(graph, 99);
            std::cout << "Hiba: az érvénytelen célcsúcs nem dobott kivételt." << std::endl;
            return 1;
        } catch (const std::exception& hiba) {
            std::cout << "Kivétel teszt rendben: " << hiba.what() << std::endl;
        }
    } catch (const std::exception& hiba) {
        std::cerr << "Teszt hiba: " << hiba.what() << std::endl;
        return 1;
    }

    return 0;
}
