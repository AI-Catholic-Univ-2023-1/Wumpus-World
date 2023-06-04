#pragma once
#ifndef __STAGE_H
#define __STAGE_H
#include <windows.h>
#include "Game.h"
#include "Grid.h"


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
	SDL_Rect grid_rect[6][6];

	// Texture
	SDL_Texture* agent_texture;
	SDL_Texture* wumpus_texture;
	SDL_Texture* pit_texture;
	SDL_Texture* gold_texture;
	SDL_Texture* stench_texture;
	SDL_Texture* breeze_texture;
	SDL_Texture* wall_texture;
	SDL_Texture* arrow_texture;
	SDL_Texture* x_texture;
	SDL_Texture* died_texture;
	SDL_Texture* action_texture;

	// Rect
	SDL_Rect agent_source_rect;
	SDL_Rect wumpus_source_rect;
	SDL_Rect pit_source_rect;
	SDL_Rect gold_source_rect;
	SDL_Rect stench_source_rect;
	SDL_Rect breeze_source_rect;
	SDL_Rect wall_source_rect;
	SDL_Rect arrow_source_rect;
	SDL_Rect arrow_destination_rect;
	SDL_Rect x_source_rect;
	SDL_Rect x_destination_rect;
	SDL_Rect died_source_rect;
	SDL_Rect died_destination_rect;
	SDL_Rect action_source_rect;
	SDL_Rect action_destination_rect;

	// Font
	SDL_Texture* msg_texture;
	SDL_Texture* arrowMsg_texture;
	SDL_Texture* diedMsg_texture;
	SDL_Texture* actionMsg_texture;
	SDL_Rect msg_box_rect = { 130, 650, 700, 80 };
	SDL_Rect right_box_rect = { 755, 30, 190, 270 };
	SDL_Rect msg_source_rect;
	SDL_Rect msg_destination_rect;
	SDL_Rect arrowMsg_source_rect;
	SDL_Rect arrowMsg_destination_rect;
	SDL_Rect diedMsg_source_rect;
	SDL_Rect diedMsg_destination_rect;
	SDL_Rect actionMsg_source_rect;
	SDL_Rect actionMsg_destination_rect;
	TTF_Font* font;
	SDL_Color black = { 0,0,0,0 };
	const char* message;
	const char* arrowMsg;
	const char* diedMsg;
	const char* actionMsg;

public:
	bool grid[6][6][8];//x,y,state
	int xarr[4] = { 1,-1,0,0 };
	int yarr[4] = { 0,0,1,-1 };
	int action = 0;

	Stage();
	~Stage();

	void reset();
	void stenchGridCheck();
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