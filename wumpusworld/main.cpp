 
#include "Game.h"
#include "Stage.h"

/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;
//Uint32 bossTimer;
//SDL_Texture* bossTimerTexture;
TTF_Font* font;
PhaseInterface* stage;
Agent* agent;
//



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
	g_window = SDL_CreateWindow("WumpusWorld", 300, 50, 1000, 750, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	agent = new Agent();
	InitGame();
	g_last_time_ms = SDL_GetTicks();

	g_current_game_phase = PHASE_INTRO;
	//Mix_PlayMusic(game_phases[0]->bgm, -1);
	//Mix_VolumeMusic(50);
	stage = new Stage();
	while ( g_flag_running )
	{
		Uint32 cur_time_ms = SDL_GetTicks();
		if ( cur_time_ms-g_last_time_ms < 33 ) //33=>60fps
			continue;
		
		stage->HandleEvents(); 
		if (cur_time_ms - g_last_time_ms >= 200 && stage->end == false) {//reasoning and acting delay least 33
			stage->Update();
			g_last_time_ms = cur_time_ms;
		}
		stage->Render();
	}

	delete stage;
	delete agent;

	ClearGame();

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}
