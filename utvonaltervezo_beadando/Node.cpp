// Vincze Csongor BG8SFC
#include "Node.h"

#include <cstdlib>

int Node::NumNodes = 0;
std::vector<int> Node::AllNodes;

Node::Node() : index(-1), x(0), y(0), dist_from_zero(10000), visited(false), from(-1) {
}

// konkrét koordinátás konstruktor
Node::Node(int i, double x_pos, double y_pos, double d, bool v)
    : index(i), x(x_pos), y(y_pos), dist_from_zero(d), visited(v), from(-1) {
    NumNodes++;
    AllNodes.push_back(i);
}

// minden csúcs véletlen képernyőpozíciót kap
Node::Node(int i)
    : index(i), x(rand() % 700), y(rand() % 550), dist_from_zero(10000), visited(false), from(-1) {
    NumNodes++;
    AllNodes.push_back(i);
}

int Node::GetIndex() {
    std::cout << index << std::endl;
    return index;
}

int Node::GetIndexScilent() const {
    return index;
}

double Node::GetX() const {
    return x;
}

double Node::GetY() const {
    return y;
}

const std::vector<Ut>& Node::GetConnectionsLoud(std::string node_name) const {
    // kiírjuk a kapcsolatokat
    if (Connections.size() == 0) {
        std::cout << "All connections of node " << node_name << ": No connections!" << std::endl;
        return Connections;
    }

    std::cout << "All connections of node " << node_name << ": [";
    for (std::vector<Ut>::const_iterator it = Connections.begin();
         it < Connections.end() - 1; ++it) {
        std::cout << "N: " << it->GetCel() << ", W: " << it->GetSuly() << ", ";
    }
    std::cout << "N: " << (Connections.end() - 1)->GetCel()
              << ", W: " << (Connections.end() - 1)->GetSuly() << ']' << std::endl;

    return Connections;
}

const std::vector<Ut>& Node::GetConnections() const {
    return Connections;
}

void Node::Connect(Node& other, int conn_w) {
    // Irányítatlan gráfot rajzolunk, ezért mindkét csúcshoz bekerül az él.
    Connections.push_back(Ut(other.index, conn_w));
    other.Connections.push_back(Ut(index, conn_w));
}

void Node::AddConnection(int other_index, int conn_w) {
    Connections.push_back(Ut(other_index, conn_w));
}

void Node::Set_dist(double d) {
    dist_from_zero = d;
}

double Node::Get_dist() const {
    return dist_from_zero;
}

void Node::Set_visited(bool v) {
    visited = v;
}

bool Node::Get_visited() const {
    return visited;
}

int Node::Get_from() const {
    return from;
}

void Node::Set_from(int f) {
    from = f;
}

int Node::GetNumNodes() const {
    std::cout << NumNodes << std::endl;
    return NumNodes;
}

std::vector<int> Node::GetAllNodes() const {
    std::cout << "All node indexes: [";
    for (std::vector<int>::iterator it = AllNodes.begin(); it < AllNodes.end() - 1; ++it) {
        std::cout << *it << ", ";
    }
    std::cout << *(AllNodes.end() - 1) << ']' << std::endl;
    return AllNodes;
}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    // Egy sor egy teljes csúcsot ír le, a kapcsolatokkal együtt.
    os << node.index << ' ' << node.x << ' ' << node.y << ' '
       << node.dist_from_zero << ' ' << node.visited << ' ' << node.from << ' '
       << node.Connections.size();
    for (std::vector<Ut>::const_iterator it = node.Connections.begin();
         it != node.Connections.end(); ++it) {
        os << ' ' << *it;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Node& node) {
    // az operator<< kimenetét olvassa vissza.
    std::size_t connection_count;
    is >> node.index >> node.x >> node.y >> node.dist_from_zero
       >> node.visited >> node.from >> connection_count;

    if (!is) {
        return is;
    }

    node.Connections.clear();
    for (std::size_t i = 0; i < connection_count; ++i) {
        Ut ut;
        is >> ut;
        node.Connections.push_back(ut);
    }
    return is;
}
