#pragma once
#include<stack>
#include<utility>
#include "Grid.h"

using namespace std;

class Agent {
public:
	bool bump = false;
	int posRow = 1;
	int posCol = 1;
	int frontPosRow;
	int frontPosCol;
	int leftPosRow;
	int leftPosCol;
	int rightPosRow;
	int rightPosCol;
	int backPosRow;
	int backPosCol;
	int direction;
	int grid[6][6][7]; //x,y,state 
	int visited[6][6] = {0,};
	int arrows = 2;
	bool havingGold = false;
	bool dead = false;
	stack<pair<int, int>> stk; //way so far
	bool end;
	bool shot = false;

	Agent();
	void setGrid(int x, int y, int state, bool t);
	bool isGrid(int x, int y, int state);
	void goForward();
	void goForwardWithoutStacking();
	void turnLeft();
	void turnRight();
	void shoot();
	void climb();
	void grab();
	void die();
	void goBackward();
	int reasoning(bool stench, bool breeze, bool glitter, bool bump);
};