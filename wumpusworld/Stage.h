#pragma once
#ifndef __STAGE_H
#define __STAGE_H
#include "Game.h"
#include <windows.h>


class Stage : public PhaseInterface
{
protected:
	Uint32 enemySpawnFormerTime = 0;

	SDL_Texture* enemyTexture; 
	SDL_Rect panelSrcPos = { 0,0,320,420 };

	SDL_Rect bossTimerSrcRect={0,0,1,1};
	SDL_Color white = { 255,255,255,0 };


public:
	int grid[6][6][7];//x,y,state
	int xarr[4] = { 1,-1,0,0 };
	int yarr[4] = { 0,0,1,-1 };
	int action = 0;

	Stage();
	~Stage();

	void HandleEvents();
	void Update();
	void Render();
	void reasoning();
	void setWumpus();
	void setPit();
	void setGold();
	void process();
};

#endif