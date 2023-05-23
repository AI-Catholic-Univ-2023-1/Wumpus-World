
#include "Game.h"


/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;
//Uint32 bossTimer;
//SDL_Texture* bossTimerTexture;
TTF_Font* font;
PhaseInterface* game_phases[4];
Agent* agent;
//

//Mix_Chunk* hitSFX;


// Game Phases
int g_current_game_phase;

int main(int argc, char* argv[])
{
	srand((unsigned int)time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}
	font = TTF_OpenFont("Resources/DungGeunMo.ttf", 48);

	g_window = SDL_CreateWindow("Dogfight", 300, 50, 1000, 750, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	{
		{
			/*SDL_Surface* surface = IMG_Load("resources/panel/attackPanel.png");
			panelTexture[0] = SDL_CreateTextureFromSurface(g_renderer, surface);
			SDL_FreeSurface(surface);*/
		}
	}

	{
		//hitSFX = Mix_LoadWAV("Resources/sounds/hit.wav");
		//Mix_VolumeChunk(hitSFX, 10);
	}
	agent = new Agent();
	InitGame();
	g_last_time_ms = SDL_GetTicks();

	g_current_game_phase = PHASE_INTRO;
	//Mix_PlayMusic(game_phases[0]->bgm, -1);
	//Mix_VolumeMusic(50);

	while ( g_flag_running )
	{
		Uint32 cur_time_ms = SDL_GetTicks();

		if ( cur_time_ms-g_last_time_ms < 33 )
			continue;
		game_phases[g_current_game_phase]->HandleEvents();
		game_phases[g_current_game_phase]->Update();
		game_phases[g_current_game_phase]->Render();
		/*if (g_current_game_phase < 4) {
		}
		else {
			stage_phases[g_current_game_phase - 4]->HandleEvents();
			stage_phases[g_current_game_phase - 4]->Update();
			stage_phases[g_current_game_phase - 4]->Render();
		}*/
		g_last_time_ms = cur_time_ms;
	}

	//delete[] game_phases;
	//delete fade;
	//delete player;

	ClearGame();

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}
