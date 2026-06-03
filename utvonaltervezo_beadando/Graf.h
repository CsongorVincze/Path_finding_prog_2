// Csongor BG8SFC
#ifndef GRAF_H
#define GRAF_H

#include <vector>

// A gráf sablon szándékosan vékony réteg az eredeti std::vector<Node> fölött.
// Így teljesül a feladat sablonos gráf elvárása, de a saját kód szerkezete
// nem távolodik el feleslegesen az eredeti graph_creator.cpp megoldástól.
template <typename CsucsT>
using Graf = std::vector<CsucsT>;

#endif
