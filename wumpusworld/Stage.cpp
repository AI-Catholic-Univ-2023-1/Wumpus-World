#include "Stage.h"
Stage::Stage() {
	// Wumpus 이미지 로드
	SDL_Surface* wumpus_surface = IMG_Load("Resources/wumpus.png");					// 이미지 로드
	cout << wumpus_surface;
	wumpus_texture = SDL_CreateTextureFromSurface(g_renderer, wumpus_surface);		// 로드한 이미지를 텍스쳐로 만들기
	SDL_FreeSurface(wumpus_surface);												// 로드한 이미지는 이제 사용 안하므로 삭제
	wumpus_source_rect = { 0, 0 ,512 ,512 };										// 이미지에서 가져올 부분
	wumpus_destination_rect = { 200, 200, 100, 100 };								// 게임 내에서 크기 설정
}
Stage::~Stage() {
	resetStage();
	SDL_DestroyTexture(enemyTexture);
	SDL_DestroyTexture(wumpus_texture);	// 텍스쳐 파괴
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
			if (event.key.keysym.sym == SDLK_SPACE) {
				//player->setEvasion();
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
	// 화면 초기화
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);


	// 4x4 Grid 출력
	/*
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 사각형 위치 지정
			grid_rect[i][j] = { (j + 1) * 125 + 50, i * 125 + 50, 100, 100 };

			// 사각형 랜더
			SDL_SetRenderDrawColor(g_renderer, 100, 100, 100, 255);
			SDL_RenderFillRect(g_renderer, &grid_rect[i][j]);
		}
	}
	*/

	// Wumpus 이미지 출력
	SDL_RenderCopy(g_renderer, wumpus_texture, &wumpus_source_rect, &wumpus_destination_rect);

	SDL_RenderPresent(g_renderer);
	



	//SDL_RenderCopy(g_renderer, bgTexture, &bgSrcRect, &bgRect);
	//back_cloudlist->render(); //back cloiud
	/*if (boss != NULL) {
		boss->renderBoss(bossTexture);
	}
	renderEnemies(EListHead, enemyTexture, enemyHitTexture);
	fuellist->render();		// Fuel Render
	missilelist->render();	// missile Render
	renderDead(DListHead, deadTexture,bossKilledTexture, player->killedTexture);
	player->RenderCopy();
	renderBullets(BListHead, bulletTexture);
	renderPBullets(PBListHead, pBulletTexture);
	front_cloudlist->render();	// back - player - front
	renderUI();
	renderLevelUpUI();
	SDL_RenderPresent(g_renderer);*/
}
//void Stage::statUpClickCheck(SDL_Event event) {
//	if (isLevelUp == true) {
//		if (event.button.y >= 275 && event.button.y <= 425) {
//			if (event.button.x >= 200 && event.button.x <= 350) {
//				statUp(statSelction[0]);
//			}
//			}
//		}
//	}
//}
//void Stage::renderUI() {
//	if (bossTimer < 90000) {
//		SDL_RenderCopy(g_renderer, bossTimerTexture, &bossTimerSrcRect, &bossTimerBarRect);
//		SDL_RenderCopy(g_renderer, player->dogTexture, &bossTimerSqrSrcRect, &bossTimerSqrRect);
//		SDL_RenderCopy(g_renderer, bossTagTexture, &bossTagSrcRect, &bossTimerBossRect);
//	}
//	else {
//		if (boss != NULL) {
//			bossHPRect.w = boss->hp * (hpBarRect.w-8) / boss->maxHP;
//			SDL_RenderCopy(g_renderer, barTexture, &barSrcRect, &bossHPBarRect);
//			SDL_RenderCopy(g_renderer, bossHPTexture, &gageSrcRect, &bossHPRect);
//			SDL_RenderCopy(g_renderer, barGlazeTexture, &barSrcRect, &bossHPBarRect);
//			SDL_RenderCopy(g_renderer, bossTagTexture, &bossTagSrcRect, &bossTagRect);
//		}
//	}
//	hpRect.w = player->getHP() * (hpBarRect.w - 8) / player->getMaxHP();
//	SDL_RenderCopy(g_renderer, barTexture, &barSrcRect, &hpBarRect);
//	SDL_RenderCopy(g_renderer, hpTexture, &gageSrcRect, &hpRect);
//	SDL_RenderCopy(g_renderer, barGlazeTexture, &barSrcRect, &hpBarRect);
//	if (player->P_GetEXP() <= player->P_GetNeedEXP())expRect.w = player->P_GetEXP() * (hpBarRect.w - 8) / player->P_GetNeedEXP();
//	else expRect.w = (hpBarRect.w - 8);
//	SDL_RenderCopy(g_renderer, barTexture, &barSrcRect, &expBarRect);
//	SDL_RenderCopy(g_renderer, expTexture, &gageSrcRect, &expRect);
//	SDL_RenderCopy(g_renderer, barGlazeTexture, &barSrcRect, &expBarRect);
//
//	{
//		char temp[10];
//		sprintf_s(temp, sizeof(temp), "LV.%02d", player->P_GetLevel());
//		SDL_Surface* surface = TTF_RenderText_Blended(font, temp, black);
//		SDL_Texture* levelUITexture = SDL_CreateTextureFromSurface(g_renderer, surface);
//
//		SDL_Rect levelSrcRect = { 0,0,surface->w,surface->h };
//		SDL_Rect levelRect = { 100, 600, surface->w, surface->h };
//
//		SDL_RenderCopy(g_renderer, levelUITexture, &levelSrcRect, &levelRect);
//		SDL_FreeSurface(surface);
//		SDL_DestroyTexture(levelUITexture);
//	}
//	{
//		SDL_Surface* surface = TTF_RenderUTF8_Blended(font, CW2A(L"부활", CP_UTF8), black);
//		SDL_Texture* levelUITexture = SDL_CreateTextureFromSurface(g_renderer, surface);
//
//		SDL_Rect levelSrcRect = { 0,0,surface->w,surface->h };
//		SDL_Rect levelRect = { 700, 600, surface->w, surface->h };
//
//		SDL_RenderCopy(g_renderer, levelUITexture, &levelSrcRect, &levelRect);
//		SDL_FreeSurface(surface);
//		SDL_DestroyTexture(levelUITexture);
//	}
//	{
//		char temp[10];
//		sprintf_s(temp, sizeof(temp), "%02d", player->getRebirthNum()); 
//		SDL_Surface* surface = TTF_RenderText_Blended(font, temp, black);
//		SDL_Texture* levelUITexture = SDL_CreateTextureFromSurface(g_renderer, surface);
//
//		SDL_Rect levelSrcRect = { 0,0,surface->w,surface->h };
//		SDL_Rect levelRect = { 800, 600, surface->w, surface->h };
//
//		SDL_RenderCopy(g_renderer, levelUITexture, &levelSrcRect, &levelRect);
//		SDL_FreeSurface(surface);
//		SDL_DestroyTexture(levelUITexture);
//	}
//	if(player->dead==false)
//	{
//		char temp[10];
//		sprintf_s(temp, sizeof(temp), "%d", player->getEvasionNum());
//		SDL_Surface* surface = TTF_RenderText_Blended(font, temp, black);
//		SDL_Texture* levelUITexture = SDL_CreateTextureFromSurface(g_renderer, surface);
//
//		SDL_Rect levelSrcRect = { 0,0,surface->w,surface->h };
//		SDL_Rect levelRect = { player->getPosW()/2+player->getPosX()-5
//			, player->getPosY() -30, surface->w/2, surface->h/2};
//
//		SDL_RenderCopy(g_renderer, levelUITexture, &levelSrcRect, &levelRect);
//		SDL_FreeSurface(surface);
//		SDL_DestroyTexture(levelUITexture);
//	}
//	if (bossTimer <2000) {
//		char temp[10];
//		sprintf_s(temp, sizeof(temp), "STAGE %d", enemyClass);
//		SDL_Surface* surface = TTF_RenderText_Blended(font, temp, black);
//		SDL_Texture* levelUITexture = SDL_CreateTextureFromSurface(g_renderer, surface);
//
//		SDL_Rect levelSrcRect = { 0,0,surface->w,surface->h };
//		SDL_Rect levelRect = { 350, 300, surface->w * 2, surface->h * 2 };
//
//		SDL_RenderCopy(g_renderer, levelUITexture, &levelSrcRect, &levelRect);
//		SDL_FreeSurface(surface);
//		SDL_DestroyTexture(levelUITexture);
//	}
//	if (boss!=NULL) {
//		if (boss->pos.x > 850) {
//			SDL_RenderCopy(g_renderer, halfTransparentBlackTexture, &bossTimerSrcRect, &bgRect);
//			SDL_Surface* surface = TTF_RenderUTF8_Blended(font, CW2A(L"BOSS ALERT", CP_UTF8), white);
//			SDL_Texture* levelUITexture = SDL_CreateTextureFromSurface(g_renderer, surface);
//
//			SDL_Rect levelSrcRect = { 0,0,surface->w,surface->h };
//			SDL_Rect levelRect = { 300, 300, surface->w * 2, surface->h * 2 };
//
//			SDL_RenderCopy(g_renderer, levelUITexture, &levelSrcRect, &levelRect);
//			SDL_FreeSurface(surface);
//			SDL_DestroyTexture(levelUITexture);
//		}
//	}
//	if (isPaused == true) {
//		SDL_RenderCopy(g_renderer, halfTransparentBlackTexture, &bossTimerSrcRect, &bgRect);
//		SDL_Surface* surface = TTF_RenderUTF8_Blended(font, CW2A(L"PAUSED", CP_UTF8), white);
//		SDL_Texture* levelUITexture = SDL_CreateTextureFromSurface(g_renderer, surface);
//
//		SDL_Rect levelSrcRect = { 0,0,surface->w,surface->h };
//		SDL_Rect levelRect = { 350, 300, surface->w*2, surface->h*2 };
//
//		SDL_RenderCopy(g_renderer, levelUITexture, &levelSrcRect, &levelRect);
//		SDL_FreeSurface(surface);
//		SDL_DestroyTexture(levelUITexture);
//	}
//}

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
		//화살이 날아가서 환경에 변화가 있는지
	}
	if (action == 2) {
		// 금을 주운 후
	}
	if (action == 3) {
		//금이 있으면 성공 없으면 실패
		//종료
	}
	return;
}