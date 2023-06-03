#include "Stage.h"
#include<stdlib.h>
Stage::Stage() {
	// Agent �̹��� �ε�
	SDL_Surface* agent_surface = IMG_Load("Resources/agent.png");				// �̹��� �ε�
	agent_texture = SDL_CreateTextureFromSurface(g_renderer, agent_surface);		// �ε��� �̹����� �ؽ��ķ� �����
	SDL_FreeSurface(agent_surface);													// �ε��� �̹����� ���� ��� ���ϹǷ� ����
	agent_source_rect = { 0, 0 ,400 ,400 };											// �̹������� ������ �κ�

	// Wumpus �̹��� �ε�
	SDL_Surface* wumpus_surface = IMG_Load("Resources/wumpus.png");
	wumpus_texture = SDL_CreateTextureFromSurface(g_renderer, wumpus_surface);
	SDL_FreeSurface(wumpus_surface);
	wumpus_source_rect = { 0, 0 ,512 ,512 };

	// Pit �̹��� �ε�
	SDL_Surface* pit_surface = IMG_Load("Resources/pit.png");
	pit_texture = SDL_CreateTextureFromSurface(g_renderer, pit_surface);
	SDL_FreeSurface(pit_surface);
	pit_source_rect = { 0, 0 ,400 ,400 };

	// Gold �̹��� �ε�
	SDL_Surface* gold_surface = IMG_Load("Resources/gold.png");
	gold_texture = SDL_CreateTextureFromSurface(g_renderer, gold_surface);
	SDL_FreeSurface(gold_surface);
	gold_source_rect = { 0, 0 ,500 ,500 };

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			fill_n(grid[i][j], 8, 0);
		}
	}

	setWall();
	setWumpus();
	setPit();
	setGold();

	// Font
	font = TTF_OpenFont("Resources/NanumSquareNeo-dEb.ttf", 60);				// ��Ʈ ũ�� ���� �� �ε�
	message = "Any Message";
	SDL_Surface* msg_surface = TTF_RenderText_Blended(font, message, black);	// ���� ���� (�ѱ�X)
	msg_texture = SDL_CreateTextureFromSurface(g_renderer, msg_surface);
	msg_source_rect = { 0, 0, msg_surface->w, msg_surface->h };
	msg_destination_rect = { 280, 605, msg_source_rect.w, msg_source_rect.h };
	SDL_FreeSurface(msg_surface);
}

Stage::~Stage() {
	resetStage();
	SDL_DestroyTexture(enemyTexture);
	SDL_DestroyTexture(agent_texture);	// �ؽ��� �ı�
	SDL_DestroyTexture(wumpus_texture);
	SDL_DestroyTexture(pit_texture);
	SDL_DestroyTexture(gold_texture);
	SDL_DestroyTexture(msg_texture);
	TTF_CloseFont(font);
}

void Stage::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
			break;
		default:
			break;
		}
	}

	//	case SDL_KEYDOWN:
	//		// Agent Roatation
	//		if (event.key.keysym.sym == SDLK_SPACE) {
	//			agent_rotation++;
	//		}
	//		// Agent Key Move
	//		else if (event.key.keysym.sym == SDLK_UP) {
	//			if (agent_location[VERTICAL] > 0 && agent_location[VERTICAL] <= 3)
	//				agent_location[VERTICAL]--;
	//		}
	//		else if (event.key.keysym.sym == SDLK_DOWN) {
	//			if (agent_location[VERTICAL] >= 0 && agent_location[VERTICAL] < 3)
	//				agent_location[VERTICAL]++;
	//		}
	//		else if (event.key.keysym.sym == SDLK_RIGHT) {
	//			if (agent_location[HORIZONTAL] >= 0 && agent_location[HORIZONTAL] < 3)
	//				agent_location[HORIZONTAL]++;
	//		}
	//		else if (event.key.keysym.sym == SDLK_LEFT) {
	//			if (agent_location[HORIZONTAL] > 0 && agent_location[HORIZONTAL] <= 3)
	//				agent_location[HORIZONTAL]--;
	//		}

	//		break;
	//	case SDL_KEYUP:
	//		if (event.key.keysym.sym == SDLK_SPACE) {
	//		}
	//		break;
		//case SDL_MOUSEBUTTONDOWN:
		//	if (event.button.button == SDL_BUTTON_LEFT)
		//	{
		//	}
		//	break;

}

void Stage::Update() {
	process();
}

void Stage::Render() {
	// ȭ�� �ʱ�ȭ
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);


	// 4x4 Grid
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// �簢�� ��ġ ����
			grid_rect[i][j] = { (j + 1) * 125 + 130, i * 125 + 50, 100, 100 };

			// �ٱ� �簢��
			SDL_SetRenderDrawColor(g_renderer, 200, 200, 200, 255);
			SDL_RenderFillRect(g_renderer, &grid_rect[i][j]);
			 
			if (grid[i + 1][j + 1][wumpus]==1) {
				SDL_RenderCopy(g_renderer, wumpus_texture, &wumpus_source_rect, &grid_rect[i][j]);
			}
			if (grid[i + 1][j + 1][pit] == 1) {
				SDL_RenderCopy(g_renderer, pit_texture, &pit_source_rect, &grid_rect[i][j]);
			}
			if (grid[i + 1][j + 1][glitter] == 1) {
				SDL_RenderCopy(g_renderer, gold_texture, &gold_source_rect, &grid_rect[i][j]);
			}

			if (i+1 == agent->posRow && j+1 == agent->posCol) {
				SDL_RenderCopyEx(g_renderer, agent_texture, &agent_source_rect, &grid_rect[i][j], agent->direction * 90, NULL, SDL_FLIP_NONE);
			}

			// �湮���� ���� Ÿ���� �ٸ� �簢������ ����
			// �湮�߰ų� ������Ʈ�� �ִ� Ÿ���� �簢������ ���� ����
			if (agent->visited[i + 1][j + 1] == false && !(i + 1 == agent->posRow && j + 1 == agent->posCol)) {
				SDL_SetRenderDrawColor(g_renderer, 80, 80, 80, 255);
				SDL_RenderFillRect(g_renderer, &grid_rect[i][j]);
			}
		}
	}

	// �޽��� ���
	SDL_SetRenderDrawColor(g_renderer, 200, 200, 200, 255);
	SDL_RenderFillRect(g_renderer, &msg_box_rect);

	SDL_RenderCopy(g_renderer, msg_texture, &msg_source_rect, &msg_destination_rect);

	SDL_RenderPresent(g_renderer);
}

void Stage::reasoning() {
}
void Stage::setWumpus() {
	for (int x = 1; x <= 4; x++) {
		for (int y = 1; y <= 4; y++) {
			if (x == 4 && y == 1) continue;
			else if (x == 1 && y == 2) continue;
			else if (x == 2 && y == 1) continue;
			else if (x == 4 && y == 4) continue;
			else if (grid[x][y][glitter] == true) continue;
			int random = rand() % 10;
			if (random == 0) {
				grid[x][y][wumpus] = true;
			}
		}
	}
};
void Stage::setPit() {
	for (int x = 1; x <= 4; x++) {
		for (int y = 1; y <= 4; y++) {
			if (x == 4 && y == 1) continue;
			else if (x == 1 && y == 2) continue;
			else if (x == 2 && y == 1) continue;
			else if (x == 4 && y == 4) continue;
			else if (grid[x][y][wumpus] == true) continue;
			else if (grid[x][y][glitter] == true) continue;
			int random = rand() % 10;
			if (random == 0) {
				grid[x][y][pit] = true;
			}
		}
	}
}
void Stage::setGold() {
	while (true) {
		int x = (rand() % 4) + 1;
		int y = (rand() % 4) + 1;
		if (x == 4 && y == 1) continue;
		else if (grid[x][y][wumpus] == true) continue;
		else if (grid[x][y][pit] == true) continue;
		grid[x][y][glitter] = true;
		return;
	}
}
void Stage::setWall() {
	grid[0][0][wall] = true;
	grid[0][1][wall] = true;
	grid[0][2][wall] = true;
	grid[0][3][wall] = true;
	grid[0][4][wall] = true;
	grid[0][5][wall] = true;
	grid[1][0][wall] = true;
	grid[2][0][wall] = true;
	grid[3][0][wall] = true;
	grid[4][0][wall] = true;
	grid[5][0][wall] = true;
	grid[5][1][wall] = true;
	grid[5][2][wall] = true;
	grid[5][3][wall] = true;
	grid[5][4][wall] = true;
	grid[5][5][wall] = true;
	grid[4][5][wall] = true;
	grid[3][5][wall] = true;
	grid[2][5][wall] = true;
	grid[1][5][wall] = true;
}
void Stage::process() {

	int x = agent->posRow;
	int y = agent->posCol;
	if (grid[x][y][wumpus] == 1) {
		agent->die();
		agent->setGrid(x, y, wumpus, true);
		return;
	}
	else if (grid[x][y][pit] == 1) {
		agent->die();
		agent->setGrid(x, y, pit, true);
		return;
	}

	bool isStench;
	bool isBreeze;
	bool isGlitter;
	bool bump;
	isStench = grid[x][y][stench];
	isBreeze = grid[x][y][breeze];
	isGlitter = grid[x][y][glitter];
	bump = grid[x][y][wall];
	action = agent->reasoning(isStench, isBreeze, isGlitter, bump);
	agent->printState();

	if (action == 1) {
		//ȭ���� ���ư��� ȯ�濡 ��ȭ�� �ִ���
		if (agent->direction == north) {
			//agent->posRow++;
			for (int arrow = agent->posRow; arrow >= 1; arrow--) {
				if (grid[arrow][agent->posCol][wumpus] == true) {
					grid[arrow][agent->posCol][wumpus] = false;
					//��ũ�� ���������
					break;
				}
			}
		}
		else if (agent->direction == south) {
			//agent->posRow--;
			for (int arrow = agent->posRow; arrow <= 4; arrow++) {
				if (grid[arrow][agent->posCol][wumpus] == true) {
					grid[arrow][agent->posCol][wumpus] = false;
					//��ũ�� ���������
					break;
				}
			}
		}
		else if (agent->direction == east) {
			//agent->posCol++;
			for (int arrow = agent->posCol; arrow <= 4; arrow++) {
				if (grid[agent->posRow][arrow][wumpus] == true) {
					grid[agent->posRow][arrow][wumpus] = false;
					//��ũ�� ���������
					break;
				}
			}
		}
		else if (agent->direction == west) {
			//agent->posCol--;
			for (int arrow = agent->posCol; arrow >= 1; arrow--) {
				if (grid[agent->posRow][arrow][wumpus] == true) {
					grid[agent->posRow][arrow][wumpus] = false;
					//��ũ�� ���������
					break;
				}
			}
		}
	}
	if (action == 2) {
		// ���� �ֿ� ��
		grid[x][y][glitter] = false;
	}
	if (action == 3) {
		//���� ������ ���� ������ ����
		//����
	}
	return;
}