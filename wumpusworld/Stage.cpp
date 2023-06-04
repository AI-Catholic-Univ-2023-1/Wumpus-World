#include "Stage.h"
#include<stdlib.h>
#include<string>

Stage::Stage() {
	agent = new Agent();
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
	arrow_destination_rect = { 775, 235, 50, 50 };

	// X 이미지 로드
	SDL_Surface* x_surface = IMG_Load("Resources/x.png");
	x_texture = SDL_CreateTextureFromSurface(g_renderer, x_surface);
	SDL_FreeSurface(x_surface);
	x_source_rect = { 0, 0 ,512 ,512 };

	// Died 이미지 로드
	SDL_Surface* died_surface = IMG_Load("Resources/died.png");
	died_texture = SDL_CreateTextureFromSurface(g_renderer, died_surface);
	SDL_FreeSurface(died_surface);
	died_source_rect = { 0, 0 ,726 ,726 };
	died_destination_rect = { 770, 40, 60, 60 };

	// Action 이미지 로드
	SDL_Surface* action_surface = IMG_Load("Resources/action.png");
	action_texture = SDL_CreateTextureFromSurface(g_renderer, action_surface);
	SDL_FreeSurface(action_surface);
	action_source_rect = { 0, 0 ,512 ,512 };
	action_destination_rect = { 770, 140, 60, 60 };

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			fill_n(grid[i][j], 8, 0);
		}
	}
	setWall();
	setGold();
	setWumpus();
	stenchGridCheck();
	setPit();

	// Font
	font = TTF_OpenFont("Resources/NanumSquareNeo-dEb.ttf", 40);				// 폰트 크기 설정 및 로드
	message = "Wumpus World";

	// Arrow Message
	arrowMsg = "X 2";

	// Died Message
	diedMsg = ": 99";

	// Action Message
	actionMsg = ": 99";
}

Stage::~Stage() {
	resetStage();
	SDL_DestroyTexture(enemyTexture);
	// 이미지 텍스쳐 파괴
	SDL_DestroyTexture(agent_texture);
	SDL_DestroyTexture(wumpus_texture);
	SDL_DestroyTexture(pit_texture);
	SDL_DestroyTexture(gold_texture);
	SDL_DestroyTexture(stench_texture);
	SDL_DestroyTexture(breeze_texture);
	SDL_DestroyTexture(wall_texture);
	SDL_DestroyTexture(x_texture);
	SDL_DestroyTexture(died_texture);
	SDL_DestroyTexture(action_texture);
	// 폰트 텍스쳐 파괴
	SDL_DestroyTexture(msg_texture);
	SDL_DestroyTexture(arrowMsg_texture);
	SDL_DestroyTexture(diedMsg_texture);
	SDL_DestroyTexture(actionMsg_texture);
	TTF_CloseFont(font);
}
void Stage::reset() {

	delete agent;
	agent = new Agent();
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			fill_n(grid[i][j], 8, 0);
		}
	}
	setWall();
	setGold();
	setWumpus();
	stenchGridCheck();
	setPit();
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
			if (event.key.keysym.sym == SDLK_SPACE && end == true) {
				end = false;
				reset();
			}
			else if (event.key.keysym.sym == SDLK_1) {
				speed = 1000;
			}
			else if (event.key.keysym.sym == SDLK_2) {
				speed = 500;
			}
			else if (event.key.keysym.sym == SDLK_3) {
				speed = 200;
			}
			else if (event.key.keysym.sym == SDLK_4) {
				speed = 50;
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE) {
				if (pause == false) {
					pause = true;
				}
				else {
					pause = false;
				}
			}
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
			grid_rect[i][j] = { (j + 1) * 100, i * 100 + 30, 70, 70 };

			// 바깥 사각형
			SDL_SetRenderDrawColor(g_renderer, 200, 200, 200, 255);
			SDL_RenderFillRect(g_renderer, &grid_rect[i][j]);

			// 방문하지 않은 타일은 진한회색 타일
			if (agent->visited[i][j] == false && (i!=agent->posRow || j!=agent->posCol)) {
				SDL_SetRenderDrawColor(g_renderer, 80, 80, 80, 255);
				SDL_RenderFillRect(g_renderer, &grid_rect[i][j]);
			}
			 
			if (agent->isGrid(i,j,wumpus) == true) {	// Wumpus
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
			if (agent->grid[i][j][blocked] == 1) {		// xblock
				SDL_RenderCopy(g_renderer, x_texture, &x_source_rect, &grid_rect[i][j]);
			}
			// Agent
			if (i == agent->posRow && j == agent->posCol) {
				SDL_RenderCopyEx(g_renderer, agent_texture, &agent_source_rect, &grid_rect[i][j], agent->direction * 90, NULL, SDL_FLIP_NONE);
			}
		}
	}

	// Action 메세지 출력
	SDL_SetRenderDrawColor(g_renderer, 200, 200, 200, 255);
	SDL_RenderFillRect(g_renderer, &msg_box_rect);
	{
		SDL_Surface* msg_surface = TTF_RenderText_Blended(font, message, black);	// 문구 삽입 (한글X)
		msg_texture = SDL_CreateTextureFromSurface(g_renderer, msg_surface);
		msg_source_rect = { 0, 0, msg_surface->w, msg_surface->h };
		msg_destination_rect = { 140, 670, msg_source_rect.w, msg_source_rect.h };
		SDL_FreeSurface(msg_surface);
		SDL_RenderCopy(g_renderer, msg_texture, &msg_source_rect, &msg_destination_rect);
		SDL_DestroyTexture(msg_texture);
	}


	// 우상단 박스
	SDL_SetRenderDrawColor(g_renderer, 200, 200, 200, 255);
	SDL_RenderFillRect(g_renderer, &right_box_rect);

	// Arrow 개수 출력
	SDL_RenderCopy(g_renderer, arrow_texture, &arrow_source_rect, &arrow_destination_rect);
	{
		string temp = std::to_string(agent->arrows);
		arrowMsg = temp.c_str();
		SDL_Surface* arrowMsg_surface = TTF_RenderText_Blended(font, arrowMsg, black);
		arrowMsg_texture = SDL_CreateTextureFromSurface(g_renderer, arrowMsg_surface);
		arrowMsg_source_rect = { 0, 0, arrowMsg_surface->w, arrowMsg_surface->h };
		arrowMsg_destination_rect = { 850, 240, arrowMsg_source_rect.w, arrowMsg_source_rect.h };
		SDL_FreeSurface(arrowMsg_surface);
		SDL_RenderCopy(g_renderer, arrowMsg_texture, &arrowMsg_source_rect, &arrowMsg_destination_rect);
		SDL_DestroyTexture(arrowMsg_texture);
	}

	// Death Count 출력
	{
		string temp = std::to_string(agent->deathCount);
		diedMsg = temp.c_str();
		SDL_Surface* diedMsg_surface = TTF_RenderText_Blended(font, diedMsg, black);
		diedMsg_texture = SDL_CreateTextureFromSurface(g_renderer, diedMsg_surface);
		diedMsg_source_rect = { 0, 0, diedMsg_surface->w, diedMsg_surface->h };
		diedMsg_destination_rect = { 850, 45, diedMsg_source_rect.w, diedMsg_source_rect.h };
		SDL_FreeSurface(diedMsg_surface);
		SDL_RenderCopy(g_renderer, died_texture, &died_source_rect, &died_destination_rect);
		SDL_RenderCopy(g_renderer, diedMsg_texture, &diedMsg_source_rect, &diedMsg_destination_rect);
		SDL_DestroyTexture(diedMsg_texture);
	}

	// Action 개수 출력
	{
		string temp = std::to_string(agent->costFunc);
		actionMsg = temp.c_str();
		SDL_Surface* actionMsg_surface = TTF_RenderText_Blended(font, actionMsg, black);
		actionMsg_texture = SDL_CreateTextureFromSurface(g_renderer, actionMsg_surface);
		actionMsg_source_rect = { 0, 0, actionMsg_surface->w, actionMsg_surface->h };
		actionMsg_destination_rect = { 850, 145, actionMsg_source_rect.w, actionMsg_source_rect.h };
		SDL_FreeSurface(actionMsg_surface);
		SDL_RenderCopy(g_renderer, action_texture, &action_source_rect, &action_destination_rect);
		SDL_RenderCopy(g_renderer, actionMsg_texture, &actionMsg_source_rect, &actionMsg_destination_rect);
		SDL_DestroyTexture(actionMsg_texture);
	}

	SDL_RenderPresent(g_renderer);
}

void Stage::reasoning() {
}
void Stage::stenchGridCheck() {
	for (int x = 0; x < 6; x++) {
		for (int y = 0; y < 6; y++) {
			grid[x][y][stench] = false;
		}
	}
	for (int x = 1; x < 5; x++) {
		for (int y = 1; y < 5; y++) {
			if (grid[x][y][wumpus] == true) {
				grid[x - 1][y][stench] = true;
				grid[x][y - 1][stench] = true;
				grid[x + 1][y][stench] = true;
				grid[x][y + 1][stench] = true;
			}
		}
	}
}
void Stage::setWumpus() {
	for (int x = 1; x <= 4; x++) {
		for (int y = 1; y <= 4; y++) {
			if (x == 4 && y == 1) continue;
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
			else if (grid[x][y][wumpus] == true) continue;
			else if (grid[x][y][glitter] == true) continue;
			int random = rand() % 10;
			if (random == 0) {
				grid[x][y][pit] = true;
				grid[x - 1][y][breeze] = true;
				grid[x][y - 1][breeze] = true;
				grid[x + 1][y][breeze] = true;
				grid[x][y + 1][breeze] = true;
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
		if (isGlitter) {
			message = "Found Gold!!";
		}
		if (agent->action == none) {
			agent->percept = false;
		}
	}
	else {
		agent->percept = false;
		agent->doAction();
		cout << message << "\n";
		if (agent->action == clmb && agent->havingGold == true) {
			message = "Climb! Success!";
			end = true;
			return;
		}
		else if (agent->action == clmb && agent->havingGold == false) {
			message = "Not Reachable to Gold!";
			end = true;
			return;
		}
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
			bool killed = false;
			if (agent->direction == north) {
				//agent->posRow++;
				for (int arrow = agent->posRow; arrow >= 1; arrow--) {
					if (grid[arrow][agent->posCol][wumpus] == true) {
						grid[arrow][agent->posCol][wumpus] = false;
						agent->setGrid(arrow, agent->posCol, wumpus, false);
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
						agent->setGrid(arrow, agent->posCol, wumpus, false);
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
						agent->setGrid(agent->posRow, arrow, wumpus, false);
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
						agent->setGrid(agent->posRow, arrow, wumpus, false);
						killed = true;
						message = "Shot and Wumpus Screamed";
						//스크림 울려퍼지게
						break;
					}
				}
			}
			stenchGridCheck();
		}
		else if (agent->action == grb) {
			// 금을 주운 후
			message = "Grabbed Gold";
			grid[x][y][glitter] = false;
			agent->setGrid(x, y, glitter, false);
		}
	}
	return;
}