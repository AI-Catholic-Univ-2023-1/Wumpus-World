#pragma once
#ifndef __STAGE_H
#define __STAGE_H
#include "Game.h"
#include "Grid.h"
#include <windows.h>


enum AgentLocation
{
	VERTICAL,
	HORIZONTAL,
};

class Stage : public PhaseInterface
{
protected:
	Uint32 enemySpawnFormerTime = 0;

	SDL_Texture* enemyTexture; 
	SDL_Rect panelSrcPos = { 0,0,320,420 };

	SDL_Rect bossTimerSrcRect={0,0,1,1};
	SDL_Color white = { 255,255,255,0 };

	// Grid
	SDL_Rect grid_rect[4][4];

	// Image
	SDL_Texture* agent_texture;
	SDL_Texture* wumpus_texture;
	SDL_Texture* pit_texture;
	SDL_Texture* gold_texture;
	SDL_Rect agent_source_rect;
	SDL_Rect wumpus_source_rect;
	SDL_Rect pit_source_rect;
	SDL_Rect gold_source_rect;

	// Agent image
	int agent_location[2] = { 3,0 };
	int agent_rotation = 0;

	// Wumpus, PIt, Gold Location
	int wumpus_location[2] = { 0,0 };
	int pit1_location[2] = { 0,0 };
	int pit2_location[2] = { 0,0 };
	int gold_location[2] = { 0,0 };

public:
	int grid[6][6][8];//x,y,state
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
	void setWall();
	void process();
};

#endif