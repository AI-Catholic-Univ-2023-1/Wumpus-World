#include "Stage.h"
Stage::Stage() {
	// Agent �̹��� �ε�
	SDL_Surface* agent_surface = IMG_Load("../Resources/agent.png");				// �̹��� �ε�
	agent_texture = SDL_CreateTextureFromSurface(g_renderer, agent_surface);		// �ε��� �̹����� �ؽ��ķ� �����
	SDL_FreeSurface(agent_surface);													// �ε��� �̹����� ���� ��� ���ϹǷ� ����
	agent_source_rect = { 0, 0 ,400 ,400 };											// �̹������� ������ �κ�

	// Wumpus �̹��� �ε�
	SDL_Surface* wumpus_surface = IMG_Load("../Resources/wumpus.png");
	wumpus_texture = SDL_CreateTextureFromSurface(g_renderer, wumpus_surface);
	SDL_FreeSurface(wumpus_surface);
	wumpus_source_rect = { 0, 0 ,512 ,512 };

	// Pit �̹��� �ε�
	SDL_Surface* pit_surface = IMG_Load("../Resources/pit.png");
	pit_texture = SDL_CreateTextureFromSurface(g_renderer, pit_surface);
	SDL_FreeSurface(pit_surface);
	pit_source_rect = { 0, 0 ,400 ,400 };

	// Gold �̹��� �ε�
	SDL_Surface* gold_surface = IMG_Load("../Resources/gold.png");
	gold_texture = SDL_CreateTextureFromSurface(g_renderer, gold_surface);
	SDL_FreeSurface(gold_surface);
	gold_source_rect = { 0, 0 ,500 ,500 };



	// *****************Ȯ�ο�*************************
	// Wumpus, Pit, Gold ��ġ �Ȱ�ġ�� �������� ����
	srand((unsigned int)time(NULL));

	do {
		wumpus_location[0] = rand() % 4;
		wumpus_location[1] = rand() % 4;
	} while (wumpus_location[0] == agent_location[0] && wumpus_location[1] == agent_location[1]);

	do {
		pit1_location[0] = rand() % 4;
		pit1_location[1] = rand() % 4;
	} while ((pit1_location[0] == agent_location[0] && pit1_location[1] == agent_location[1]) ||
		(pit1_location[0] == wumpus_location[0] && pit1_location[1] == wumpus_location[1]));

	do {
		pit2_location[0] = rand() % 4;
		pit2_location[1] = rand() % 4;
	} while ((pit2_location[0] == agent_location[0] && pit2_location[1] == agent_location[1]) ||
		(pit2_location[0] == wumpus_location[0] && pit2_location[1] == wumpus_location[1]) ||
		(pit2_location[0] == pit1_location[0] && pit2_location[1] == pit1_location[1]));

	do {
		gold_location[0] = rand() % 4;
		gold_location[1] = rand() % 4;
	} while ((gold_location[0] == agent_location[0] && gold_location[1] == agent_location[1]) ||
		(gold_location[0] == wumpus_location[0] && gold_location[1] == wumpus_location[1]) ||
		(gold_location[0] == pit1_location[0] && gold_location[1] == pit1_location[1]) ||
		(gold_location[0] == pit2_location[0] && gold_location[1] == pit2_location[1]));

	// Debug
	cout << "wumpus : " << wumpus_location[1] + 1 << " " << 4 - wumpus_location[0] << endl;
	cout << "pit1 : " << pit1_location[1] + 1 << " " << 4 - pit1_location[0] << endl;
	cout << "pit2 : " << pit2_location[1] + 1 << " " << 4 - pit2_location[0] << endl;
	cout << "gold : " << gold_location[1] + 1 << " " << 4 - gold_location[0] << endl << endl;
}

Stage::~Stage() {
	resetStage();
	SDL_DestroyTexture(enemyTexture);
	SDL_DestroyTexture(agent_texture);	// �ؽ��� �ı�
	SDL_DestroyTexture(wumpus_texture);
	SDL_DestroyTexture(pit_texture);
	SDL_DestroyTexture(gold_texture);
}

void Stage::HandleEvents()
{
	
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			// Agent Roatation
			if (event.key.keysym.sym == SDLK_SPACE) {
				agent_rotation++;
			}
			// Agent Key Move
			else if (event.key.keysym.sym == SDLK_UP) {
				if (agent_location[VERTICAL] > 0 && agent_location[VERTICAL] <= 3)
					agent_location[VERTICAL]--;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				if (agent_location[VERTICAL] >= 0 && agent_location[VERTICAL] < 3)
					agent_location[VERTICAL]++;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				if (agent_location[HORIZONTAL] >= 0 && agent_location[HORIZONTAL] < 3)
					agent_location[HORIZONTAL]++;
			}
			else if (event.key.keysym.sym == SDLK_LEFT) {
				if (agent_location[HORIZONTAL] > 0 && agent_location[HORIZONTAL] <= 3)
					agent_location[HORIZONTAL]--;
			}

			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_SPACE) {
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				//Mix_PlayChannel(2, clickSFX, 0);
				//statUpClickCheck(event);
			}
			break;

		default:
			break;
		}
	}
}

void Stage::Update() {
}

void Stage::Render() {
	// ȭ�� �ʱ�ȭ
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);


	// 4x4 Grid
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// �簢�� ��ġ ����
			grid_rect[i][j] = { (j + 1) * 125 + 50, i * 125 + 50, 100, 100 };

			// �ٱ� �簢��
			SDL_SetRenderDrawColor(g_renderer, 200, 200, 200, 255);
			SDL_RenderFillRect(g_renderer, &grid_rect[i][j]);


			// Agent, Wumpus, Pit, Gold ��ġ ����
			if (i == agent_location[VERTICAL] && j == agent_location[HORIZONTAL]) {
				SDL_RenderCopyEx(g_renderer, agent_texture, &agent_source_rect, &grid_rect[i][j], agent_rotation * 90, NULL, SDL_FLIP_NONE);
			}
			else if (i == gold_location[0] && j == gold_location[1])
				SDL_RenderCopy(g_renderer, gold_texture, &gold_source_rect, &grid_rect[i][j]);
			else if (i == wumpus_location[0] && j == wumpus_location[1])
				SDL_RenderCopy(g_renderer, wumpus_texture, &wumpus_source_rect, &grid_rect[i][j]);
			else if ((i == pit1_location[0] && j == pit1_location[1])||(i == pit2_location[0] && j == pit2_location[1]))
				SDL_RenderCopy(g_renderer, pit_texture, &pit_source_rect, &grid_rect[i][j]);
		}
	}


	SDL_RenderPresent(g_renderer);
}

void Stage::reasoning() {
}
void Stage::setWumpus() {

};
void Stage::setPit() {

}
void Stage::setGold() {

}
void Stage::process() {

	int x = agent->posRow;
	int y = agent->posCol;
	if (grid[x][y][wumpus] == 1) {
		agent->die();
		agent->setGrid(x, y, wumpus, true);
		return;
	}
	else if (grid[x][y][breeze] == 1) {
		agent->die();
		agent->setGrid(x, y, pit, true);
		return;
	}

	bool stench;
	bool breeze;
	bool glitter;
	bool bump;
	stench = grid[x][y][stench];
	breeze = grid[x][y][breeze];
	glitter = grid[x][y][glitter];
	bump = grid[x][y][bump];
	action = agent->reasoning(stench, breeze, glitter, bump);

	if (action == 1) {
		//ȭ���� ���ư��� ȯ�濡 ��ȭ�� �ִ���
	}
	if (action == 2) {
		// ���� �ֿ� ��
	}
	if (action == 3) {
		//���� ������ ���� ������ ����
		//����
	}
	return;
}