#pragma once
using namespace SGE;

class Grid
{
public:
	Grid();
	~Grid();

	// Array Initializer
	void InitializeArray();
	void MakeWalls();

	// Picking Start/End Points
	void PickLocation();
	void PickStartPoint();
	void PickEndPoint();

	// Looking for adjacent squares.
	void LookAround(int positionX, int positionY);

	// Finding scores for each adjacent square.
	void FindGScore();
	void FindHScore();
	void FindFScore();

	// Checking for similarities/conflicts.
	void CheckFs();

	// Getting the available paths from the lists.
	void FindPath();

	// Other.
	void Update(float deltaTime);
	void Render();

private:

	// Grid
	SRect mRectArray[5][5]{};

	// Grid Locators
	int mX = 0;
	int mY = 0;

	// Walls
	SRect mWall;

	// Rect dimensions
	SVector2 mPos;
	SVector2 mDim;
	SVector2 mPosDim;

	// Pathfinder
	SRect mPathFinder;

	// Start/End Points
	bool mStartPoint = false;
	bool mEndPoint = false;
	bool mWalls = true;
	SRect mStartPointRect;
	SRect mEndPointRect;
	int mStartPointX = 0;
	int mStartPointY = 0;

	// Current Positions
	int mCurrentPositionX = 0;
	int mCurrentPositionY = 0;

	// Lists
	std::vector<SRect> openList = {};
	std::vector<SRect> closedList = {};
	std::vector<SRect> adjList = {};
	std::vector<SRect> wallList = {};

	// Index location
	int index = 0;
	int counter = 0;






};

