// Vincze Csongor BG8SFC
#ifndef NODE_H
#define NODE_H

#include "Ut.h"

#include <iostream>
#include <string>
#include <vector>

class Node {
private:
    int index; // Ez a mostani csúcs indexe.
    double x; // A csúcs térbeli x koordinátája.
    double y; // A csúcs térbeli y koordinátája.
    std::vector<Ut> Connections; // Kapcsolt csúcsok indexei és súlyai.
    double dist_from_zero;
    bool visited;
    int from; // Honnan jöttünk ide a Dijkstra algoritmusban.

public:
    static int NumNodes; // Hány csúcs van összesen.
    static std::vector<int> AllNodes; // Eltárolja az összes csúcs indexét.

    Node();
    // konstruktor megadott koordinátákkal.
    Node(int i, double x_pos, double y_pos, double d, bool v);
    // konstruktor véletlen koordinátákkal.
    explicit Node(int i);

    int GetIndex();
    int GetIndexScilent() const;
    double GetX() const;
    double GetY() const;

    // Kapcsolatok kiírása és lekérése teszteléshez és konzolos követéshez.
    const std::vector<Ut>& GetConnectionsLoud(std::string node_name = "") const;
    const std::vector<Ut>& GetConnections() const;

    // Kétirányú kapcsolat létrehozása
    void Connect(Node& other, int conn_w);

    // Dijkstra állapotmezők kezelése.
    void Set_dist(double d);
    double Get_dist() const;
    void Set_visited(bool v);
    bool Get_visited() const;
    int Get_from() const;
    void Set_from(int f);

    int GetNumNodes() const;
    std::vector<int> GetAllNodes() const;

    // Perzisztens tárolás
    friend std::ostream& operator<<(std::ostream& os, const Node& node);
    friend std::istream& operator>>(std::istream& is, Node& node);
};

#endif
