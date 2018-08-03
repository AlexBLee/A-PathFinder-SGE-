#pragma once
#include <list>

using namespace SGE;

class Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();

	int gCost;
	int hCost;
	int fCost;

	void FindGScore();
	void FindHScore();
	void FindFScore() { fCost = gCost + hCost; }

	std::list<SRect> openList = {};
	std::list<SRect>::iterator it = openList.begin();

	std::list<SRect> closedList = {};
	std::list<SRect>::iterator it2 = closedList.begin();


private:
};

