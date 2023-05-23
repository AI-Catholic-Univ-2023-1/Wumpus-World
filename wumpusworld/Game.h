#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include<cstdio>
#include <iostream>
#include <string>
#include <atlstr.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include"Agent.h"
#include"Grid.h"
//
//namespace DIRECTION {
//	enum {
//		RIGHT = 1,
//		LEFT = 2,
//		UP = 3,
//		DOWN = 4
//	};
//}

// Game Phases
const int PHASE_INTRO = 0;
const int PHASE_OPENING = 1;
const int PHASE_GAMEOVER = 2;
const int PHASE_ENDING = 3;
const int PHASE_STAGE1 = 4;
const int PHASE_STAGE2 = 5;
const int PHASE_STAGE3 = 6;

void InitGame();
void ClearGame();

class PhaseInterface;

extern Agent* agent;
extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern bool changingStage;
extern PhaseInterface* game_phases[4];
//extern SDL_Texture* bossTimerTexture;
//extern TTF_Font* font;

//extern Mix_Chunk* hitSFX;

class PhaseInterface
{
public:
	PhaseInterface() {};
	~PhaseInterface() {};

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	void resetStage();
	Mix_Music* bgm;
};

#endif