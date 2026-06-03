// Csongor BG8SFC
#include "Ut.h"

#include <stdexcept>

Ut::Ut() : cel(-1), suly(0) {
}

Ut::Ut(int cel, int suly) : cel(cel), suly(suly) {
    // Nulla vagy negatív él nem lenne értelmes útvonaltervezési költség.
    if (suly <= 0) {
        throw std::invalid_argument("Az út súlya pozitív kell legyen.");
    }
}

int Ut::GetCel() const {
    return cel;
}

int Ut::GetSuly() const {
    return suly;
}

std::ostream& operator<<(std::ostream& os, const Ut& ut) {
    os << ut.cel << ' ' << ut.suly;
    return os;
}

std::istream& operator>>(std::istream& is, Ut& ut) {
    // Ideiglenes változókkal olvasunk, majd érvényes objektumot készítünk.
    int cel;
    int suly;
    is >> cel >> suly;
    if (is) {
        ut = Ut(cel, suly);
    }
    return is;
}
