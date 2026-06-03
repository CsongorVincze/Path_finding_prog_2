Csongor BG8SFC

# Útvonaltervező - felhasználói segédlet

## A program feladata

A program véletlenszerű gráfot készít, majd megkeresi és megjeleníti a 0. csúcsból a felhasználó által választott célcsúcsba vezető legkisebb költségű útvonalat.

## Indítás

Indítsd el az `utvonaltervezo.exe` fájlt. A program először a konzolban kiírja a létrehozott gráf kapcsolatait, majd bekéri a célcsúcs indexét:

```text
What's your destination?
```

A gráf 10 csúcsot tartalmaz, ezért 0 és 9 közötti egész számot adj meg.

Példa:

```text
5
```

Érvénytelen index esetén a program hibaüzenetet ír ki.

## A grafikus ablak jelölései

- **Zöld kör:** egy gráfcsúcs.
- **Sötétkék szám a csúcs mellett, felső sor:** a csúcs indexe.
- **Rózsaszín szám a csúcs mellett, alsó sor:** a 0. csúcstól számított Dijkstra-távolság.
- **Szürke vonal:** két csúcs közötti él.
- **Rózsaszín szám az él közelében:** az él súlya.
- **Piros vastag vonal:** a 0. csúcsból a kiválasztott célcsúcsba vezető útvonal.

## Kilépés

A program az SFML ablak bezárásakor fejeződik be.

## Szükséges fájlok

Az `utvonaltervezo.exe` mellett legyenek jelen:

- `sfml-graphics-3.dll`;
- `sfml-window-3.dll`;
- `sfml-system-3.dll`;
- `Retro Floral.otf`.
