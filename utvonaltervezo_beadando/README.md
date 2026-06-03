Csongor BG8SFC

# Útvonaltervező

A program véletlenszerű súlyozott gráfot hoz létre, Dijkstra algoritmussal kiszámítja a 0. csúcsból induló legkisebb költségű útvonalakat, majd SFML ablakban megjeleníti a gráfot és a kiválasztott célcsúcshoz vezető útvonalat.

A program SFML 3.0.2-t és C++17 fordítási módot használ. Az SFML és a C++17 használatához a laborvezető jóváhagyása szükséges.

## Fordítás

Főprogram:

```bash
C:\msys64\mingw64\bin\g++.exe -std=c++17 -Wall -Wextra -pedantic main.cpp Node.cpp Ut.cpp GrafMuveletek.cpp -o utvonaltervezo.exe -IC:\msys64\SFML-3.0.2\include -LC:\msys64\SFML-3.0.2\lib -lsfml-graphics -lsfml-window -lsfml-system
```

Tesztprogram:

```bash
C:\msys64\mingw64\bin\g++.exe -std=c++17 -Wall -Wextra -pedantic teszt.cpp Node.cpp Ut.cpp GrafMuveletek.cpp -o teszt.exe
```

## Futtatás

```bash
.\utvonaltervezo.exe
```

A futtatáshoz az alábbi fájloknak az `utvonaltervezo.exe` mellett kell lenniük:

- `sfml-graphics-3.dll`;
- `sfml-window-3.dll`;
- `sfml-system-3.dll`;
- `Retro Floral.otf`.

Indítás után a program bekéri a célcsúcs indexét. A létrehozott gráf 10 csúcsot tartalmaz, ezért 0 és 9 közötti index adható meg.

## Megjelenítés

- zöld kör: csúcs;
- sötétkék szám: csúcsindex;
- rózsaszín szám a csúcs mellett: Dijkstra-távolság;
- szürke vonal: él;
- rózsaszín szám az élen: élsúly;
- piros vastag vonal: a kiválasztott célhoz vezető útvonal.

## Projektfájlok

- `Node.h`, `Node.cpp`: csúcsosztály;
- `Ut.h`, `Ut.cpp`: útosztály;
- `Graf.h`: gráfsablon;
- `GrafMuveletek.h`, `GrafMuveletek.cpp`: gráfkezelő és útkereső függvények;
- `main.cpp`: grafikus főprogram;
- `teszt.cpp`: tesztprogram;
- `fejlesztoi_dokumentacio.md`: részletes fejlesztői dokumentáció;
- `felhasznaloi_segedlet.md`: felhasználói útmutató;
- `tesztelesi_eredmenyek.txt`: teszteredmények.
