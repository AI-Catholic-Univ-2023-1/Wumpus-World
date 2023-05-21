#pragma once

class Environment {
public:
	int grid[6][6];

	Environment();
	void setWumpus();
	void setPit();
	void setGold();
	int whatIsHere(int x, int y);
};