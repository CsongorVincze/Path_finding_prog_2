Csongor BG8SFC

# Útvonaltervező - fejlesztői dokumentáció

## 1. A program célja

A program egy súlyozott, irányítatlan gráfot hoz létre és jelenít meg. A gráf csúcsai véletlenszerű képernyőpozíciót kapnak, majd a program véletlenszerű súlyozott élekkel köti össze őket. A 0. indexű csúcsból Dijkstra algoritmussal kiszámítja a többi csúcs elérési távolságát, és meghatározza a felhasználó által kiválasztott célcsúcshoz vezető legkisebb távolságú útvonalat.

Az eredmény egy SFML ablakban jelenik meg:

- a csúcsok zöld körök;
- az élek szürke vonalak;
- az élsúlyok rózsaszín számok;
- a csúcs indexe sötétkék szám;
- a 0. csúcstól számított Dijkstra-távolság rózsaszín szám;
- a kiválasztott célhoz vezető útvonal piros vastag vonal.

## 2. Fejlesztési és futtatási környezet

A grafikus megjelenítéshez a program az SFML 3.0.2 könyvtárat használja. Az SFML 3 eseménykezelése és a `std::optional` használata miatt a program C++17 módban fordítandó.

*(A laborvezető a program bemutatásakor nem kifogásolta az SFML használatát, így megtartottam a programban.)*

Szükséges összetevők:

- C++17-et támogató GCC/MinGW fordító;
- SFML 3.0.2 fejlécek és könyvtárak;
- `sfml-graphics-3.dll`;
- `sfml-window-3.dll`;
- `sfml-system-3.dll`;
- `Retro Floral.otf`.

A főprogram fordítása:

```bash
C:\msys64\mingw64\bin\g++.exe -std=c++17 -Wall -Wextra -pedantic main.cpp Node.cpp Ut.cpp GrafMuveletek.cpp -o utvonaltervezo.exe -IC:\msys64\SFML-3.0.2\include -LC:\msys64\SFML-3.0.2\lib -lsfml-graphics -lsfml-window -lsfml-system
```

A tesztprogram fordítása:

```bash
C:\msys64\mingw64\bin\g++.exe -std=c++17 -Wall -Wextra -pedantic teszt.cpp Node.cpp Ut.cpp GrafMuveletek.cpp -o teszt.exe
```

## 3. A projekt fájljai

### Forrásfájlok

`main.cpp`: a felhasználói program és az SFML megjelenítés. Létrehozza a gráfot, elindítja az útkeresést, bekéri a célcsúcsot és kirajzolja az eredményt.

`Node.h`, `Node.cpp`: a gráf csúcsát reprezentáló `Node` osztály deklarációja és implementációja.

`Ut.h`, `Ut.cpp`: a két csúcs közötti kapcsolatot reprezentáló `Ut` osztály deklarációja és implementációja.

`Graf.h`: a sablonos gráftípus deklarációja.

`GrafMuveletek.h`, `GrafMuveletek.cpp`: gráflétrehozó, útkereső, kiíró, mentő és betöltő függvények.

`teszt.cpp`: grafikus felület nélküli tesztprogram.

### Adat- és dokumentációs fájlok

`graf_mentes.txt`: a főprogram által mentett gráf.

`teszt_graf_mentes.txt`: a tesztprogram által mentett gráf.

`tesztelesi_eredmenyek.txt`: a tesztelés eredményei.

`README.md`: rövid fordítási és futtatási útmutató.

`felhasznaloi_segedlet.md`: a program használatának leírása.

## 4. Objektumorientált felépítés

### 4.1. Node osztály

A `Node` osztály egy gráfcsúcs teljes állapotát tárolja.

Privát adattagok:

- `int index`: a csúcs egyedi sorszáma;
- `double x`, `double y`: a csúcs koordinátái a grafikus ablakban;
- `std::vector<Ut> Connections`: a csúcsból induló utak;
- `double dist_from_zero`: a 0. csúcstól számított aktuális legkisebb költség;
- `bool visited`: jelzi, hogy a Dijkstra algoritmus feldolgozta-e a csúcsot;
- `int from`: az optimális útvonalon szereplő előző csúcs indexe.

Statikus adattagok:

- `int NumNodes`: a létrehozott csúcsok száma;
- `std::vector<int> AllNodes`: a létrehozott csúcsok indexei.

Konstruktorok:

- `Node()`: üres csúcsot hoz létre, elsősorban fájlból történő betöltéshez;
- `Node(int i)`: adott indexű csúcsot hoz létre véletlenszerű koordinátákkal;
- `Node(int i, double x_pos, double y_pos, double d, bool v)`: minden fontos kezdeti adat megadásával hoz létre csúcsot.

Fontosabb tagfüggvények:

- `GetIndex()`: kiírja és visszaadja a csúcs indexét;
- `GetIndexScilent() const`: kiírás nélkül visszaadja a csúcs indexét;
- `GetX() const`, `GetY() const`: visszaadja a képernyőkoordinátákat;
- `GetConnectionsLoud() const`: kiírja és visszaadja a csúcs kapcsolatait;
- `GetConnections() const`: visszaadja a kapcsolatok konstans referenciáját;
- `Connect(Node&, int)`: kétirányú utat hoz létre két csúcs között;
- `AddConnection(int, int)`: egy kapcsolatot ad a csúcshoz;
- `Set_dist()`, `Get_dist() const`: a Dijkstra-távolság kezelése;
- `Set_visited()`, `Get_visited() const`: a feldolgozottsági állapot kezelése;
- `Set_from()`, `Get_from() const`: az előző csúcs kezelése;
- `GetNumNodes() const`: kiírja és visszaadja a csúcsok számát;
- `GetAllNodes() const`: kiírja és visszaadja a csúcsindexeket.

Perzisztencia:

- `operator<<`: szöveges formában kiírja a csúcs teljes állapotát;
- `operator>>`: visszaolvassa a csúcs teljes állapotát.

### 4.2. Ut osztály

Az `Ut` osztály egy súlyozott kapcsolatot reprezentál.

Privát adattagok:

- `int cel`: annak a csúcsnak az indexe, ahová az út vezet;
- `int suly`: az út költsége.

Konstruktorok:

- `Ut()`: üres objektumot hoz létre beolvasáshoz;
- `Ut(int cel, int suly)`: adott célcsúccsal és súllyal hoz létre utat.

Tagfüggvények:

- `GetCel() const`: visszaadja a célcsúcs indexét;
- `GetSuly() const`: visszaadja az út súlyát.

A paraméteres konstruktor `std::invalid_argument` kivételt dob, ha a súly nem pozitív.

Perzisztencia:

- `operator<<`: kiírja a célcsúcs indexét és az út súlyát;
- `operator>>`: visszaolvassa az út adatait.

### 4.3. Graf sablon

A gráf csúcsainak tárolására a program sablonos típust használ:

```cpp
template <typename CsucsT>
using Graf = std::vector<CsucsT>;
```

A sablon lehetővé teszi, hogy a gráf csúcstípusa paraméterezhető legyen. A programban használt konkrét típus:

```cpp
Graf<Node>
```

Az élek az egyes `Node` objektumok `Connections` tárolójában találhatók, ezért a gráf szomszédsági listás reprezentációt használ.

## 5. Gráfműveletek

### SweepNodes

```cpp
Graf<Node> SweepNodes(int how_many_nodes);
```

Nullázza a statikus csúcsnyilvántartást, majd létrehozza a megadott számú, 0-tól indexelt csúcsot. A csúcsok koordinátái véletlenszerűek.

### RndConnect

```cpp
void RndConnect(Graf<Node>& graph, int max_connections);
```

Véletlenszerű, kétirányú utakat hoz létre. A függvény nem enged önhurkot vagy duplikált kapcsolatot. Az útsúlyok pozitív egész számok.

### PrintGraph

```cpp
void PrintGraph(Graf<Node>& graph);
```

Konzolra írja minden csúcs kapcsolatait és a kapcsolatok súlyait.

### Dijkstra

```cpp
void Dijkstra(Graf<Node>& Graph, int allexplored = 0);
```

Rekurzív Dijkstra algoritmust valósít meg. A kiinduló csúcs távolságát a hívás előtt nullára kell állítani. A függvény minden lépésben kiválasztja a még nem feldolgozott, legkisebb távolságú csúcsot, majd frissíti annak szomszédait.

A feldolgozás során frissül:

- a csúcs `dist_from_zero` értéke;
- a csúcs `from` értéke;
- a csúcs `visited` állapota.

### Trace

```cpp
std::vector<int> Trace(Graf<Node>& Graph, int destination);
```

A célcsúcstól indulva a `from` mezőket követi vissza a 0. csúcsig. Az összegyűjtött indexeket megfordítja, ezért a visszaadott útvonal kezdőponttól célpontig halad.

Érvénytelen célindex esetén `std::out_of_range` kivételt dob.

### SaveGraph és LoadGraph

```cpp
void SaveGraph(const Graf<Node>& graph, const std::string& file_name);
Graf<Node> LoadGraph(const std::string& file_name);
```

A `SaveGraph` szövegfájlba menti a teljes gráfot. A `LoadGraph` ugyanebből a formátumból visszaállítja a csúcsokat, a kapcsolatokat és az algoritmus állapotadatait.

## 6. Dijkstra algoritmus

A Dijkstra algoritmus nemnegatív élköltségű gráfban határozza meg a kiinduló csúcsból a többi csúcsba vezető legkisebb költségű útvonalat.

A programban a kiinduló csúcs mindig a 0. indexű csúcs.

Az algoritmus lépései:

1. A 0. csúcs távolsága 0, a többi csúcs kezdeti távolsága 10000.
2. A program kiválasztja a még nem látogatott, legkisebb távolságú csúcsot.
3. Megvizsgálja a kiválasztott csúcsból induló utakat.
4. Ha egy szomszéd az aktuális csúcson keresztül kisebb költséggel érhető el, frissíti annak távolságát és előző csúcsát.
5. A kiválasztott csúcs látogatottá válik.
6. A feldolgozás rekurzívan folytatódik.

A megvalósítás időigénye prioritási sor nélkül közelítőleg `O(V^2 + E)`, ahol `V` a csúcsok, `E` az élek száma.

## 7. Perzisztens tárolás

A teljes gráf szöveges formában menthető. A fájl első sora a csúcsok számát tartalmazza. Ezután minden sor egy csúcs teljes állapotát írja le:

```text
index x y távolság látogatott előző kapcsolatok_száma cél súly cél súly ...
```

Példa:

```text
0 383 336 0 1 -1 2 1 2 3 8
```

A fenti sor jelentése:

- a csúcs indexe 0;
- koordinátái `(383, 336)`;
- Dijkstra-távolsága 0;
- már feldolgozott;
- nincs előző csúcsa;
- két kapcsolata van;
- az első kapcsolat az 1. csúcsba vezet 2-es súllyal;
- a második kapcsolat a 3. csúcsba vezet 8-as súllyal.

## 8. Kivételkezelés

A program az alábbi hibákat kezeli kivételekkel:

- két csúcsnál kisebb gráf véletlenszerű összekötése;
- nulla vagy negatív útsúly;
- érvénytelen célcsúcs;
- sikertelen fájlmegnyitás mentéskor;
- sikertelen fájlmegnyitás betöltéskor;
- sikertelen betűtípus-betöltés.

A főprogram és a tesztprogram `try-catch` blokkal kezeli a kivételeket, majd hibaüzenetet ír a konzolra.

## 9. Grafikus megjelenítés

A program 800 × 600 képpontos SFML ablakot használ.

Megjelenítési elemek:

- háttér: sötétszürke;
- csúcs: zöld kör fehér körvonallal;
- él: áttetsző szürke vonal;
- élsúly: rózsaszín felirat az él közepén;
- csúcsindex: sötétkék felirat a csúcs jobb oldalán, felső sorban;
- Dijkstra-távolság: rózsaszín felirat a csúcs jobb oldalán, alsó sorban;
- kiválasztott útvonal: piros vastag vonal.



## 10. A főprogram működése

1. Inicializálja a véletlenszám-generátort.
2. Létrehoz 10 véletlenszerű helyzetű csúcsot.
3. Létrehoz 10 véletlenszerű kapcsolatot.
4. Konzolra írja a gráf kapcsolatait.
5. Elmenti a gráfot `graf_mentes.txt` fájlba.
6. A 0. csúcs távolságát nullára állítja.
7. Lefuttatja a Dijkstra algoritmust.
8. Bekéri a célcsúcs indexét.
9. Meghatározza a célcsúcshoz vezető útvonalat.
10. Megnyitja az SFML ablakot és kirajzolja a gráfot.

## 11. Tesztelés

A `teszt.cpp` egy rögzített, 5 csúcsból álló gráfot hoz létre. A rögzített kapcsolatok miatt a várt eredmények minden futásnál azonosak.

A teszt ellenőrzi:

- a csúcsok létrehozását;
- a kétirányú kapcsolatok létrehozását;
- a kapcsolatok konzolos kiírását;
- a Dijkstra algoritmust;
- az útvonal visszafejtését;
- a gráf mentését;
- a gráf visszaolvasását;
- az érvénytelen célcsúcs kivételét.

A teszt részletes kimenete a `tesztelesi_eredmenyek.txt` fájlban található.

## 12. Korlátok

- A gráf minden főprogram-indításkor véletlenszerű.
- A célcsúcs indexszel adható meg.
- A Dijkstra algoritmus kiindulópontja mindig a 0. csúcs.
- A program csak pozitív egész élköltségeket kezel.
- Az SFML ablak futtatásához szükségesek a mellékelt DLL fájlok és a betűtípus.
- Nehézség még, hogy a véletlenül generált pozíció miatt néha egymásra kerülnek a csúcsok
