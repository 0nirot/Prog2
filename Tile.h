#pragma once
#include <raylib.h>

class Tile
{
public:
	Tile();
	virtual ~Tile();

	virtual bool isTraversable() const;
	virtual bool isStartTile() const;
	virtual bool isEndTile() const;
	virtual bool isPlayerOnTile() const;
	virtual Color getTileVisualization() const;
	virtual void traverse();

	void setPlayerOnTile(bool player);
	bool isPathTile() const;
	void setPathTile(bool isPath);
	bool isWaypoint() const;
	void setWaypoint(bool waypoint);

protected:
	bool traversable;
	bool startTile;
	bool endTile;
	bool playerOnTile;
	bool isPath;
	bool waypoint;
	Color tileVisualization;
};
