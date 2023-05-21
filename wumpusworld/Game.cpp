#include "Game.h"

void InitGame() {
	g_flag_running = true;
}

void ClearGame() {
	//delete[] game_phases;
	//delete[] stage_phases;
	
	//Mix_FreeChunk(hitSFX);
	/*for (int i = 0; i < 7; i++) {
		SDL_DestroyTexture(panelTexture[i]);
	}
	SDL_DestroyTexture(bossTimerTexture);
	SDL_DestroyTexture(barTexture);
	SDL_DestroyTexture(barGlazeTexture);
	SDL_DestroyTexture(expTexture);
	SDL_DestroyTexture(hpTexture);
	SDL_DestroyTexture(bossHPTexture);
	SDL_DestroyTexture(bossTagTexture);
	SDL_DestroyTexture(halfTransparentBlackTexture);
	delete[] stage_phases;*/
}

void PhaseInterface::resetStage(){};