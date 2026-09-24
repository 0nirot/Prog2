#pragma once
#include <vector>

class Map;

// Eine Position auf der Map (Tile-Koordinaten)
struct GridPosition
{
    int x;
    int y;
};

// Findet mit dem A*-Algorithmus den kürzesten Weg auf der Map.
// Bewegt wird sich wie beim Spieler: nur hoch/runter/links/rechts,
// jeder Schritt kostet 1, nur begehbare Tiles (isTraversable) sind erlaubt.
class PathFinder
{
public:
    // Kürzester Weg von einer beliebigen Position (z.B. Spieler) zum Exit-Tile.
    // Enthält Start und Ziel. Leer, wenn es keinen Weg gibt.
    std::vector<GridPosition> findPathToExit(const Map& map, GridPosition from) const;

    // Kürzester Weg zwischen zwei beliebigen Positionen (A*).
    // Enthält Start und Ziel. Leer, wenn es keinen Weg gibt.
    std::vector<GridPosition> findPath(const Map& map, GridPosition start, GridPosition goal) const;

private:
    // Geschätzte Restkosten bis zum Ziel: Manhattan-Distanz.
    // Unterschätzt nie (man braucht mindestens so viele Schritte),
    // deshalb findet A* garantiert den kürzesten Weg.
    static int heuristic(GridPosition a, GridPosition b);

    static bool isWalkable(const Map& map, int x, int y);

    // Sucht das Exit-Tile auf der Map. false, wenn es keins gibt.
    static bool findExit(const Map& map, GridPosition& exit);
};
