#include "Stage.h"
#include<stdlib.h>
Stage::Stage() {
	// Agent 이미지 로드
	SDL_Surface* agent_surface = IMG_Load("Resources/agent.png");					// 이미지 로드
	agent_texture = SDL_CreateTextureFromSurface(g_renderer, agent_surface);		// 로드한 이미지를 텍스쳐로 만들기
	SDL_FreeSurface(agent_surface);													// 로드한 이미지는 이제 사용 안하므로 삭제
	agent_source_rect = { 0, 0 ,400 ,400 };											// 이미지에서 가져올 부분

	// Wumpus 이미지 로드
	SDL_Surface* wumpus_surface = IMG_Load("Resources/wumpus.png");
	wumpus_texture = SDL_CreateTextureFromSurface(g_renderer, wumpus_surface);
	SDL_FreeSurface(wumpus_surface);
	wumpus_source_rect = { 0, 0 ,512 ,512 };

	// Pit 이미지 로드
	SDL_Surface* pit_surface = IMG_Load("Resources/pit.png");
	pit_texture = SDL_CreateTextureFromSurface(g_renderer, pit_surface);
	SDL_FreeSurface(pit_surface);
	pit_source_rect = { 0, 0 ,400 ,400 };

	// Gold 이미지 로드
	SDL_Surface* gold_surface = IMG_Load("Resources/gold.png");
	gold_texture = SDL_CreateTextureFromSurface(g_renderer, gold_surface);
	SDL_FreeSurface(gold_surface);
	gold_source_rect = { 0, 0 ,500 ,500 };

	// Stench 이미지 로드
	SDL_Surface* stench_surface = IMG_Load("Resources/stench.png");
	stench_texture = SDL_CreateTextureFromSurface(g_renderer, stench_surface);
	SDL_FreeSurface(stench_surface);
	stench_source_rect = { 0, 0 ,612 ,612 };

	// Breeze 이미지 로드
	SDL_Surface* breeze_surface = IMG_Load("Resources/breeze.png");
	breeze_texture = SDL_CreateTextureFromSurface(g_renderer, breeze_surface);
	SDL_FreeSurface(breeze_surface);
	breeze_source_rect = { 0, 0 ,640 ,640 };

	// Wall 이미지 로드
	SDL_Surface* wall_surface = IMG_Load("Resources/wall.png");
	wall_texture = SDL_CreateTextureFromSurface(g_renderer, wall_surface);
	SDL_FreeSurface(wall_surface);
	wall_source_rect = { 0, 0 ,920 ,920 };

	// Arrow 이미지 로드
	SDL_Surface* arrow_surface = IMG_Load("Resources/arrow.png");
	arrow_texture = SDL_CreateTextureFromSurface(g_renderer, arrow_surface);
	SDL_FreeSurface(arrow_surface);
	arrow_source_rect = { 0, 0 ,800 ,800 };
	arrow_destination_rect = { 20, 435, 50, 50 };

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
	font = TTF_OpenFont("Resources/NanumSquareNeo-dEb.ttf", 40);				// 폰트 크기 설정 및 로드
	message = "Wumpus World";
	SDL_Surface* msg_surface = TTF_RenderText_Blended(font, message, black);	// 문구 삽입 (한글X)
	msg_texture = SDL_CreateTextureFromSurface(g_renderer, msg_surface);
	msg_source_rect = { 0, 0, msg_surface->w, msg_surface->h };
	msg_destination_rect = { 40, 670, msg_source_rect.w, msg_source_rect.h };
	SDL_FreeSurface(msg_surface);

	// Arrow Message
	arrow = "X 2";
	SDL_Surface* arrowMsg_surface = TTF_RenderText_Blended(font, arrow, black);
	arrowMsg_texture = SDL_CreateTextureFromSurface(g_renderer, arrowMsg_surface);
	arrowMsg_source_rect = { 0, 0, arrowMsg_surface->w, arrowMsg_surface->h };
	arrowMsg_destination_rect = { 80, 440, arrowMsg_source_rect.w, arrowMsg_source_rect.h };
	SDL_FreeSurface(arrowMsg_surface);
}

Stage::~Stage() {
	resetStage();
	SDL_DestroyTexture(enemyTexture);
	SDL_DestroyTexture(agent_texture);	// 텍스쳐 파괴
	SDL_DestroyTexture(wumpus_texture);
	SDL_DestroyTexture(pit_texture);
	SDL_DestroyTexture(gold_texture);
	SDL_DestroyTexture(stench_texture);
	SDL_DestroyTexture(breeze_texture);
	SDL_DestroyTexture(wall_texture);
	SDL_DestroyTexture(msg_texture);
	SDL_DestroyTexture(arrowMsg_texture);
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
}

void Stage::Update() {
	process();
}

void Stage::Render() {
	// 화면 초기화
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);


	// 6x6 Grid
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			// 사각형 위치 지정
			grid_rect[i][j] = { (j + 1) * 100 + 100, i * 100 + 30, 70, 70 };

			// 바깥 사각형
			SDL_SetRenderDrawColor(g_renderer, 200, 200, 200, 255);
			SDL_RenderFillRect(g_renderer, &grid_rect[i][j]);

			// 방문하지 않은 타일은 진한회색 타일
			if (agent->visited[i][j] == false && (i!=agent->posRow || j!=agent->posCol)) {
				SDL_SetRenderDrawColor(g_renderer, 80, 80, 80, 255);
				SDL_RenderFillRect(g_renderer, &grid_rect[i][j]);
			}
			 
			if (agent->grid[i][j][wumpus] == 1) {	// Wumpus
				SDL_RenderCopy(g_renderer, wumpus_texture, &wumpus_source_rect, &grid_rect[i][j]);
			}
			if (grid[i][j][stench] == 1 && agent->visited[i][j]) {	// Stench
				SDL_RenderCopy(g_renderer, stench_texture, &stench_source_rect, &grid_rect[i][j]);
			}
			if (grid[i][j][breeze] == 1 && agent->visited[i][j]) {	// Breeze
				SDL_RenderCopy(g_renderer, breeze_texture, &breeze_source_rect, &grid_rect[i][j]);
			}
			if (agent->grid[i][j][pit] == 1) {		// Pit
				SDL_RenderCopy(g_renderer, pit_texture, &pit_source_rect, &grid_rect[i][j]);
			}
			if (agent->grid[i][j][glitter] == 1) {	// Glitter
				SDL_RenderCopy(g_renderer, gold_texture, &gold_source_rect, &grid_rect[i][j]);
			}
			if (agent->grid[i][j][wall] == 1) {		// Wall
				SDL_RenderCopy(g_renderer, wall_texture, &wall_source_rect, &grid_rect[i][j]);
			}
			// Agent
			if (i == agent->posRow && j == agent->posCol) {
				SDL_RenderCopyEx(g_renderer, agent_texture, &agent_source_rect, &grid_rect[i][j], agent->direction * 90, NULL, SDL_FLIP_NONE);
			}
		}
	}


	// 메시지 출력
	SDL_SetRenderDrawColor(g_renderer, 200, 200, 200, 255);
	SDL_RenderFillRect(g_renderer, &msg_box_rect);
	{
		SDL_Surface* msg_surface = TTF_RenderText_Blended(font, message, black);	// 문구 삽입 (한글X)
		msg_texture = SDL_CreateTextureFromSurface(g_renderer, msg_surface);
		msg_source_rect = { 0, 0, msg_surface->w, msg_surface->h };
		msg_destination_rect = { 140, 670, msg_source_rect.w, msg_source_rect.h };
		SDL_FreeSurface(msg_surface);
	}

	SDL_RenderCopy(g_renderer, msg_texture, &msg_source_rect, &msg_destination_rect);

	SDL_RenderCopy(g_renderer, arrow_texture, &arrow_source_rect, &arrow_destination_rect);
	SDL_RenderCopy(g_renderer, arrowMsg_texture, &arrowMsg_source_rect, &arrowMsg_destination_rect);


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
				if (x > 0) {
					grid[x - 1][y][stench] = true;
				}
				if (y > 0) {
					grid[x][y - 1][stench] = true;
				}
				if (x < 5) {
					grid[x + 1][y][stench] = true;
				}
				if (y < 5) {
					grid[x][y + 1][stench] = true;
				}
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
				if (x > 0) {
					grid[x - 1][y][breeze] = true;
				}
				if (y > 0) {
					grid[x][y - 1][breeze] = true;
				}
				if (x < 5) {
					grid[x + 1][y][breeze] = true;
				}
				if (y < 5) {
					grid[x][y + 1][breeze] = true;
				}
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

	if (agent->percept == false) {
		agent->percept = true;
		if (grid[x][y][wumpus] == 1) {
			message = "Died";
			agent->setGrid(x, y, wumpus, true);
			agent->reasoning(false, false, false, false, true);
			return;
		}
		else if (grid[x][y][pit] == 1) {
			message = "Died";
			agent->setGrid(x, y, pit, true);
			agent->reasoning(false, false, false, false, true);
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
		agent->reasoning(isStench, isBreeze, isGlitter, bump, false);
		if (isStench&&isBreeze) {
			message = "Stench & Breeze";
		}
		else if (isStench) {
			message = "Stench";
		}
		else if (isBreeze) {
			message = "Breeze";
		}
	}
	else {
		agent->percept = false;
		agent->doAction();
		if (agent->action == go) {
			message = "Go Forward";
		}
		else if (agent->action == turnL) {
			message = "Turn Left";
		}
		else if (agent->action == turnR) {
			message = "Turn Right";
		}
		else if (agent->action == bmp) {
			message = "Bumped!";
		}
		else if (agent->action == sht) {
			message = "Shot but not Screamed";
			//화살이 날아가서 환경에 변화가 있는지
			int r, c;
			bool killed = false;
			if (agent->direction == north) {
				//agent->posRow++;
				for (int arrow = agent->posRow; arrow >= 1; arrow--) {
					if (grid[arrow][agent->posCol][wumpus] == true) {
						grid[arrow][agent->posCol][wumpus] = false;
						r = arrow;
						c = y;
						killed = true;
						message = "Shot and Wumpus Screamed";
						//스크림 울려퍼지게
						break;
					}
				}
			}
			else if (agent->direction == south) {
				//agent->posRow--;
				for (int arrow = agent->posRow; arrow <= 4; arrow++) {
					if (grid[arrow][agent->posCol][wumpus] == true) {
						grid[arrow][agent->posCol][wumpus] = false;
						r = arrow;
						c = y;
						killed = true;
						message = "Shot and Wumpus Screamed";
						//스크림 울려퍼지게
						break;
					}
				}
			}
			else if (agent->direction == east) {
				//agent->posCol++;
				for (int arrow = agent->posCol; arrow <= 4; arrow++) {
					if (grid[agent->posRow][arrow][wumpus] == true) {
						grid[agent->posRow][arrow][wumpus] = false;
						r = x;
						c = arrow;
						killed = true;
						message = "Shot and Wumpus Screamed";
						//스크림 울려퍼지게
						break;
					}
				}
			}
			else if (agent->direction == west) {
				//agent->posCol--;
				for (int arrow = agent->posCol; arrow >= 1; arrow--) {
					if (grid[agent->posRow][arrow][wumpus] == true) {
						grid[agent->posRow][arrow][wumpus] = false;
						r = x;
						c = arrow;
						killed = true;
						message = "Shot and Wumpus Screamed";
						//스크림 울려퍼지게
						break;
					}
				}
			}
			if (killed) {
				if (r > 0) {
					grid[r - 1][c][stench] = false;
				}
				if (c > 0) {
					grid[r][c - 1][stench] = false;
				}
				if (r < 5) {
					grid[r + 1][c][stench] = false;
				}
				if (c < 5) {
					grid[r][c + 1][stench] = false;
				}
			}
		}
		else if (agent->action == grb) {
			// 금을 주운 후
			message = "Grabbed Gold";
			grid[x][y][glitter] = false;
		}
	}
	return;
}