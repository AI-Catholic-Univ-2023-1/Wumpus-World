#pragma once
#include<stack>
#include<utility>
#include<iostream>
#include "Grid.h"

using namespace std;

class Agent {
public:
	bool bump = false;
	int posRow = 4;
	int posCol = 1;
	int frontPosRow = 4;
	int frontPosCol = 2;
	int leftPosRow = 3;
	int leftPosCol = 1;
	int rightPosRow = 5;
	int rightPosCol = 1;
	int backPosRow = 4;
	int backPosCol = 0;
	int direction = east;
	bool grid[6][6][9]; //x,y,state 
	bool visited[6][6];
	int arrows = 2;
	bool havingGold = false;
	stack<pair<int, int>> stk; //way so far
	bool end=false;
	bool shot = false;
	bool percept = false;
	int action = -1;

	Agent();
	void printState();
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
	void doAction();
	void reasoning(bool stench, bool breeze, bool glitter, bool bump, bool dead);
};