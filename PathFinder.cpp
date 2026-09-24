#include "PathFinder.h"
#include "Map.h"
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <functional>
#include <queue>
#include <utility>

std::vector<GridPosition> PathFinder::findPathToExit(const Map& map, GridPosition from) const
{
    GridPosition exit{};
    if (!findExit(map, exit))
        return {};

    return findPath(map, from, exit);
}

std::vector<GridPosition> PathFinder::findPath(const Map& map, GridPosition start, GridPosition goal) const
{
    if (!isWalkable(map, start.x, start.y) || !isWalkable(map, goal.x, goal.y))
        return {};

    const int width = map.getWidth();
    const int tileCount = width * map.getHeight();

    auto toIndex = [width](int x, int y) { return y * width + x; };
    const int startIndex = toIndex(start.x, start.y);
    const int goalIndex = toIndex(goal.x, goal.y);

    std::vector<int> gCost(tileCount, INT_MAX);
    std::vector<int> cameFrom(tileCount, -1);
    std::vector<bool> closed(tileCount, false);

    using OpenEntry = std::pair<int, int>; // (Cost, Tile-Index)
    std::priority_queue<OpenEntry, std::vector<OpenEntry>, std::greater<OpenEntry>> openList;

    gCost[startIndex] = 0;
    openList.push({ heuristic(start, goal), startIndex });

    const int dirX[4] = { 0, 0, -1, 1 };
    const int dirY[4] = { -1, 1, 0, 0 };

    while (!openList.empty())
    {
        const int current = openList.top().second;
        openList.pop();

        if (closed[current])
            continue;
        closed[current] = true;

        if (current == goalIndex)
        {
            std::vector<GridPosition> path;
            for (int index = goalIndex; index != -1; index = cameFrom[index])
                path.push_back({ index % width, index / width });

            std::reverse(path.begin(), path.end());
            return path;
        }

        const int currentX = current % width;
        const int currentY = current / width;

        for (int dir = 0; dir < 4; ++dir)
        {
            const int nextX = currentX + dirX[dir];
            const int nextY = currentY + dirY[dir];

            if (!isWalkable(map, nextX, nextY))
                continue;

            const int next = toIndex(nextX, nextY);
            if (closed[next])
                continue;

            const int newCost = gCost[current] + 1;
            if (newCost < gCost[next])
            {
                gCost[next] = newCost;
                cameFrom[next] = current;
                openList.push({ newCost + heuristic({ nextX, nextY }, goal), next });
            }
        }
    }

    return {};
}

int PathFinder::heuristic(GridPosition a, GridPosition b)
{
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

bool PathFinder::isWalkable(const Map& map, int x, int y)
{
    auto tile = map.getTile(x, y);
    return tile != nullptr && tile->isTraversable();
}

bool PathFinder::findExit(const Map& map, GridPosition& exit)
{
    for (int y = 0; y < map.getHeight(); ++y)
    {
        for (int x = 0; x < map.getWidth(); ++x)
        {
            auto tile = map.getTile(x, y);
            if (tile != nullptr && tile->isEndTile())
            {
                exit = { x, y };
                return true;
            }
        }
    }
    return false;
}
