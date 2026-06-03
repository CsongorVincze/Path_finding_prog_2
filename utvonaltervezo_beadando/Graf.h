// Vincze Csongor BG8SFC
#ifndef GRAF_H
#define GRAF_H

#include <vector>

// ez csak arra kell, hogy legyen egy gráf osztály
// igazából majd csak vesszük a Node osztályt és abból csinálunk egy vektort
template <typename CsucsT>
using Graf = std::vector<CsucsT>;

#endif
