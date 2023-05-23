#pragma once
#include<stack>
#include<utility>
#include "Grid.h"

using namespace std;

class Agent {
public:
	bool bump = false;
	int posX = 1;
	int posY = 1;
	int frontPosX;
	int frontPosY;
	int leftPosX;
	int leftPosY;
	int rightPosX;
	int rightPosY;
	int backPosX;
	int backPosY;
	int worldDirection;
	int grid[6][6][7]; //x,y,state 
	int visited[6][6] = {0,};
	int arrows = 2;
	bool havingGold = false;
	bool dead = false;
	stack<pair<int, int>> stk; //way so far
	int frontState;
	int backState;
	int leftState;
	int rightState;
	bool end;
	bool shot = false;

	Agent();
	void setGrid(int x, int y, int state, bool t);
	bool isGrid(int x, int y, int state);
	void goForward();
	void goForwardWithoutStacking();
	void turnLeft();
	void turnRight();
	void climb();
	void shoot();
	void grab();
	void die();
	void goBackward();
	int reasoning(bool stench, bool breeze, bool glitter, bool bump);
};