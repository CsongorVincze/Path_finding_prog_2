// Csongor BG8SFC
#ifndef GRAF_MUVELETEK_H
#define GRAF_MUVELETEK_H

#include "Node.h"
#include "Graf.h"

#include <string>
#include <vector>

Graf<Node> SweepNodes(int how_many_nodes);
void RndConnect(Graf<Node>& graph, int max_connections);
void PrintGraph(Graf<Node>& graph);
void Dijkstra(Graf<Node>& Graph, int allexplored = 0);
// A következő függvények az eredeti szabad függvények modulba helyezett változatai.
std::vector<int> Trace(Graf<Node>& Graph, int destination);

// Perzisztencia: teljes gráf mentése és visszatöltése.
void SaveGraph(const Graf<Node>& graph, const std::string& file_name);
Graf<Node> LoadGraph(const std::string& file_name);

#endif
