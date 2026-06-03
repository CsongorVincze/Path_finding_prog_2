// Csongor BG8SFC
#ifndef UT_H
#define UT_H

#include <iostream>

class Ut {
private:
    // Annak a csúcsnak az indexe, ahová az él vezet.
    int cel;
    // Az él súlya, ezt használja a Dijkstra algoritmus.
    int suly;

public:
    Ut();
    Ut(int cel, int suly);

    // Egyszerű lekérdezők, hogy a Node kapcsolatai kívülről ne módosuljanak.
    int GetCel() const;
    int GetSuly() const;

    // Az út objektum is menthető és visszaolvasható.
    friend std::ostream& operator<<(std::ostream& os, const Ut& ut);
    friend std::istream& operator>>(std::istream& is, Ut& ut);
};

#endif
