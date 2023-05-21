#pragma once
#ifndef __STAGE_H
#define __STAGE_H
#include "Game.h"
#include <windows.h>
#include "Agent.h"
#include "Environment.h"


class Stage : public PhaseInterface
{
protected:
	Uint32 enemySpawnFormerTime = 0;

	SDL_Texture* enemyTexture;
	SDL_Rect panelSrcPos = { 0,0,320,420 };

	SDL_Rect bossTimerSrcRect={0,0,1,1};
	SDL_Color white = { 255,255,255,0 };


public:
	Environment env;
	Agent agnt;

	Stage();
	~Stage();

	void HandleEvents();
	void Update();
	void Render();
	void reasoning();
};

#endif