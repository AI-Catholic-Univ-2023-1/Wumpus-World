#pragma once

class Environment {
	int grid[6][6];

	void setWumpus();
	void setPit();
	void setGold();
	int whatIsHere(int x, int y);
};