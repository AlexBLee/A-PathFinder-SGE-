#include "Precompiled.h"
#include "Grid.h"

Grid::Grid()
	: mPos(0, 0)
	, mDim(0, 0)
{
	mDim = SVector2(50, 50);
}

Grid::~Grid()
{

}

void Grid::InitializeArray()
{
	// Initializes the array of rectangles with given size.
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			mPos = SVector2(i*192,j*192);
			mPosDim = mPos + mDim;
			mRectArray[i][j] = SRect(mPos,mPosDim);
			
		}
	}

}

void Grid::PickLocation()
{
	// This is used to specify the location of the thing you are currently trying to place.

	if (Input_IsKeyPressed(Keys::RIGHT))
		mX++;

	if (Input_IsKeyPressed(Keys::LEFT))
		mX--;

	if (Input_IsKeyPressed(Keys::UP))
		mY--;

	if (Input_IsKeyPressed(Keys::DOWN))
		mY++;

	// If you attempt to go beyond the grid, it will make sure you stay at the maximum or minimum value.
	
	if (mX > 4)
		mX = 4;
	if (mX < 0)
		mX = 0;
	if (mY > 4)
		mY = 4;
	if (mY < 0)
		mY = 0;

}

void Grid::PickStartPoint()
{
	PickLocation();

	Graphics_DebugRect(mRectArray[mX][mY], 0xff);

	// Places the start point at the location that you specify and adds it to the closed list.
	if (Input_IsKeyPressed(Keys::ENTER))
	{
		int X = mX;
		int Y = mY;

		mStartPoint = false;
		mEndPoint = true;

		mStartPointRect = mRectArray[X][Y];

		closedList.push_back(mStartPointRect);
		mStartPointX = X;
		mStartPointY = Y;


	}


}

void Grid::PickEndPoint()
{
	PickLocation();

	Graphics_DebugRect(mRectArray[mX][mY], 0xFF0000);

	// Places the end point at the location that you specify.
	if (Input_IsKeyPressed(Keys::SPACE))
	{
		int X = mX;
		int Y = mY;

		mStartPoint = false;
		mEndPoint = false;

		mEndPointRect = mRectArray[X][Y];
	}
}

void Grid::MakeWalls()
{
	PickLocation();

	Graphics_DebugRect(mRectArray[mX][mY], 0xff00ff);

	// Places walls at the specified locations so the algorithm won't consider them when trying to find the path.
	if (Input_IsKeyPressed(Keys::NUMPAD5))
	{
		int X = mX;
		int Y = mY;

		mWall = mRectArray[mX][mY];
		wallList.push_back(mWall);

		++counter;

	}

	// The amount of walls you can put.
	if (counter == 3)
	{
		mWalls = false;
		mStartPoint = true;
	}

}

void Grid::LookAround(int positionX, int positionY)
{
	// A function which the purpose is to look at all the adjacent squares and add the correct 
	// ones to the open list.

	// Needs many edge cases due to risk of going out of bounds.

	if (mPathFinder.min != mEndPointRect.min)
	{
		int counter = 0;

		mCurrentPositionX = positionX;
		mCurrentPositionY = positionY;

		if ((mCurrentPositionX + 1 >= 0 && mCurrentPositionX + 1 < 5))
		{
			openList.push_back(mRectArray[mCurrentPositionX + 1][mCurrentPositionY]);
			++counter;
		}

		if ((mCurrentPositionX - 1 >= 0 && mCurrentPositionX - 1 < 5))
		{
			openList.push_back(mRectArray[mCurrentPositionX - 1][mCurrentPositionY]);
			++counter;
		}

		if ((mCurrentPositionY - 1 >= 0 && mCurrentPositionY - 1 < 5))
		{
			openList.push_back(mRectArray[mCurrentPositionX][mCurrentPositionY - 1]);
			++counter;
		}

		if ((mCurrentPositionY + 1 >= 0 && mCurrentPositionY + 1 < 5))
		{
			openList.push_back(mRectArray[mCurrentPositionX][mCurrentPositionY + 1]);
			++counter;
		}

		if ((mCurrentPositionX + 1 >= 0 && mCurrentPositionX + 1 < 5) && (mCurrentPositionY + 1 >= 0 && mCurrentPositionY + 1 < 5))
		{
			openList.push_back(mRectArray[mCurrentPositionX + 1][mCurrentPositionY + 1]);
			++counter;
		}

		if ((mCurrentPositionX + 1 >= 0 && mCurrentPositionX + 1 < 5) && (mCurrentPositionY - 1 >= 0 && mCurrentPositionY - 1 < 5))
		{
			openList.push_back(mRectArray[mCurrentPositionX + 1][mCurrentPositionY - 1]);
			++counter;
		}

		if ((mCurrentPositionX - 1 >= 0 && mCurrentPositionX - 1 < 5) && (mCurrentPositionY + 1 >= 0 && mCurrentPositionY + 1 < 5))
		{
			openList.push_back(mRectArray[mCurrentPositionX - 1][mCurrentPositionY + 1]);
			++counter;
		}

		if ((mCurrentPositionX - 1 >= 0 && mCurrentPositionX - 1 < 5) && (mCurrentPositionY - 1 >= 0 && mCurrentPositionY - 1 < 5))
		{
			openList.push_back(mRectArray[mCurrentPositionX - 1][mCurrentPositionY - 1]);
			++counter;
		}

		// If any of squares in the open list happen to be in the wall lists, delete them.
		for (int i = 0; i < wallList.size(); i++)
		{
			for (int j = 0; j < openList.size(); j++)
			{
				if (openList[j].min == wallList[i].min)
				{
					openList.erase(openList.begin() + j);
					--counter;
				}
			}
			
		}

		// Find all the scores for optimized path.
		FindGScore();
		FindHScore();
		FindFScore();


		// Add to adjacent list.
		for (int i = openList.size() - counter; i < openList.size(); i++)
		{
			adjList.push_back(openList[i]);
		}

		FindPath();


		
	}

	


}

void Grid::FindGScore()
{
	// Finds distance from start node
	for (int i = 0; i < openList.size(); i++)
	{
		int *pG = &openList[i].g;
		SVector2 otherMin = openList[i].min;
		SVector2 startPoint = mStartPointRect.min;

		if (startPoint != otherMin)
		{
			SVector2 resultOne = (otherMin - startPoint) / 192;

			*pG = abs(resultOne.x) + abs(resultOne.y);
		}
	}
	
}

void Grid::FindHScore()
{
	// Finds distance from end node.
	for (int i = 0; i < openList.size(); i++)
	{
		int *pH = &openList[i].h;

		SVector2 otherMin = openList[i].min;
		SVector2 endPoint = mEndPointRect.min;

		if (endPoint != otherMin)
		{
			SVector2 resultOne = (endPoint - otherMin) / 192;

			*pH = abs(resultOne.x) + abs(resultOne.y);
		}
	}


}

void Grid::FindFScore()
{
	// The sum of the G score and H score.
	for (int i = 0; i < openList.size(); i++)
	{
		int *pF = &openList[i].f;

		*pF = openList[i].g + openList[i].h;

	}

	
}

void Grid::CheckFs()
{
	int counter = 0;
	int fTest = adjList[0].f;
	SRect tempRect = SRect(0,0,0,0);
	std::vector<SRect> tempList = {};

	// Find lowest F score.
	for (int i = 0; i < adjList.size(); i++)
	{
		if (adjList[i].f < fTest)
		{
			fTest = adjList[i].f;
		}
	}

	// If there are any identical F scores, put them into a list.
	for (int i = 0; i < adjList.size(); i++)
	{
		if (fTest == adjList[i].f)
		{
			tempList.push_back(adjList[i]);
		}
	}

	int hTest = tempList[0].h;

	// Compare their H scores
	for (int i = 0; i < tempList.size(); i++)
	{
		if (tempList[i].h <= hTest)
		{
			hTest = tempList[i].h;
			tempRect = tempList[i];
		}

	}

	for (int i = 0; i < adjList.size(); i++)
	{
		if (adjList[i].min == tempRect.min)
		{
			index = i;
		}
	}
}

void Grid::FindPath()
{
	CheckFs();

	for (int i = 0; i < closedList.size(); i++)
	{
		if (adjList[index].min == closedList[i].min)
		{
			adjList.erase(adjList.begin() + index);
			CheckFs();
		}
	}


	closedList.push_back(adjList[index]);

	// Erase the squares that are being currently considered.
	openList.erase(openList.begin() + index);

	// Clear the adjacent list to prepare for new location.
	adjList.clear();

	// Give the pathfinder the latest location on the closed list.
	mPathFinder = closedList.back();

	int iIndex = 0;
	int jIndex = 0;

	// Find out where the pathfinder is on the grid.
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (mPathFinder.min == mRectArray[i][j].min)
			{
				iIndex = i;
				jIndex = j;
				break;
			}
		}
	}

	// Repeat until end.
	LookAround(iIndex, jIndex);

}

void Grid::Update(float deltaTime)
{
	Render();
}

void Grid::Render()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Graphics_DebugRect(mRectArray[i][j]);
		}
	}

	if (mWalls)
		MakeWalls();

	if(mStartPoint)
		PickStartPoint();

	Graphics_DebugRect(mStartPointRect, 0xff);

	if(mEndPoint)
		PickEndPoint();

	if (!mStartPoint && !mEndPoint && !mWalls)
		LookAround(mStartPointX, mStartPointY);

	if (mPathFinder.min == mEndPointRect.min)
		Graphics_DebugRect(mEndPointRect, 0xfff);


	for each(SRect rect in closedList)
	{
		Graphics_DebugRect(rect, 0x00ff00);
	}

	for each(SRect rect in wallList)
	{
		Graphics_DebugRect(rect, 0xff00ff);
	}

	



	//for each(SRect rect in openList)
	//{
	//	Graphics_DebugRect(rect, 0xff0000);
	//}

	/*Graphics_DebugRect(endPointRect, 0xFF0000);*/





	
}
