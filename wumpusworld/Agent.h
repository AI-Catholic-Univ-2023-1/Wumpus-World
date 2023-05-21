#pragma once
#include<stack>
#include<utility>

using namespace std;

class Agent {
public:
	bool bump = false;
	int posX = 1;
	int posY = 1;
	int frontPosX;
	int frontPosY;
	int worldDirection;
	int grid[6][6];
	int visited[6][6] = {0,};
	int arrows = 2;
	bool havingGold = false;
	bool dead = false;
	stack<pair<int, int>> stk; //way so far
	int frontState;
	int backState;
	int leftState;
	int rightState;

	Agent();
	void goForward();
	void turnLeft();
	void turnRight();
	void climb();
	void shoot();
	void grab();
	void percept();
	void die();
};