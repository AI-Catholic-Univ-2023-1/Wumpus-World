#include "Agent.h"

Agent::Agent() {

}
	void Agent::goForward() {
		shot = false;
		
	}
	void Agent::goForwardWithoutStacking() {
		shot = false;

	}
	void Agent::turnLeft() {
		shot = false;

	}
	void Agent::turnRight() {
		shot = false;

	}
	void Agent::climb() {

	}
	void Agent::grab() {
		havingGold = true;
	}
	void Agent::die() {

	}
	void Agent::setGrid(int x, int y, int state, bool t) {

	}
	void Agent::goBackward() {

	}
	bool Agent::isGrid(int x, int y, int state) {

	}
	int Agent::reasoning(bool stench, bool breeze, bool glitter, bool bump) {
		if (bump == true) {
			//벽과 겹치면 튕겨져 나옴
			setGrid(posX, posY, wall, true);
			goBackward();
			return 0;
		}
		visited[posX][posY] = true;
		setGrid(posX, posY, safe, true);
		if (!stench && !breeze) {
			//아무 일도 없으면 사방 안전
			setGrid(frontPosX, frontPosY, safe, true);
			setGrid(leftPosX, leftPosY, safe, true);
			setGrid(rightPosX, rightPosY, safe, true);
			setGrid(backPosX, backPosY, safe, true);
		}
		if (stk.empty() && havingGold) {
			//금이 있고 1,1에 도착
			climb();
			return 3;
		}
		if (havingGold) {
			// 금이 있고 아직 1,1에 도착하지 못함
			if (frontPosX != stk.top().first || frontPosY != stk.top().second) {
				//왔던 타일을 바라보고 있지 않을 경우
				turnRight();
				return 0;
			}
			else {
				goForwardWithoutStacking();
				return 0;
			}
		}
		if (glitter == true) {
			grab();
			return 2;
		}
		// 방문하지 않고 벽이 아닌 안전한 타일로 이동
		if (visited[frontPosX][frontPosY] == false && isGrid(frontPosX, frontPosY, safe) == true && isGrid(frontPosX, frontPosY, wall) == false) {
			goForward();
			return 0;
		}
		else if (visited[rightPosX][rightPosY] == false && isGrid(rightPosX, rightPosY, safe) == true && isGrid(rightPosX, rightPosY, wall) == false) {
			turnRight();
			return 0;
		}
		else if (visited[leftPosX][leftPosY] == false && isGrid(leftPosX, leftPosY, safe) == true && isGrid(leftPosX, leftPosY, wall) == false) {
			turnLeft();
			return 0;
		}
		else if (visited[backPosX][backPosY] == false && isGrid(backPosX, backPosY, safe) == true && isGrid(backPosX, backPosY, wall) == false) {
			turnRight();
			return 0;
		}

		if (
			(isGrid(frontPosX, frontPosY, wall) == true || isGrid(frontPosX, frontPosY, pit) == true) &&
			(isGrid(backPosX, backPosY, wall) == true || isGrid(backPosX, backPosY, pit) == true) &&
			(isGrid(leftPosX, leftPosY, wall) == true || isGrid(leftPosX, leftPosY, pit) == true) &&
			(isGrid(rightPosX, rightPosY, wall) == true || isGrid(rightPosX, rightPosY, pit) == true)
			) {
			//사방이 갈 수 없는 경우
			return 3;
		}

		if (visited[frontPosX][frontPosY] == true) {
			//앞이 방문한 타일일 경우
			if (
				(isGrid(backPosX, backPosY, wall) == true || isGrid(backPosX, backPosY, pit) == true || visited[backPosX][backPosY]==true) &&
				(isGrid(leftPosX, leftPosY, wall) == true || isGrid(leftPosX,leftPosY,pit) == true|| visited[leftPosX][leftPosY]==true) &&
				(isGrid(rightPosX, rightPosY, wall) == true || isGrid(rightPosX,rightPosY,pit)==true|| visited[rightPosX][rightPosY]==true)
				) {
				//뒤, 좌, 우 방문불가(Pit 또는 벽 또는 방문함)
				if (frontPosX != stk.top().first || frontPosY != stk.top().second) {
					//왔던 타일을 바라보고 있지 않을 경우
					turnRight();
					return 0;
				}
				else {
					setGrid(posX, posX, wall, true);
					goForwardWithoutStacking();
					stk.pop();
					return 0;
				}
			}
			else {
				turnRight();
				return 0;
			}
		}
		if (isGrid(frontPosX, frontPosY, wall) == true) {
			//앞이 벽일 경우
			turnRight();
			return 0;
		}
		if (stench == true || isGrid(frontPosX, frontPosY, wumpus) == true) {
			//7.냄새나거나 앞에 괴물이 있는 경우
			if (shot == true) {
				//이미 쐈으면
				goForward();
				return 0;
			}
			else {
				if (arrows > 0) {
					shot = true;
					return 1;
				}
				else {
					goForward();
					return 0;
				}
			}
		}
		if (isGrid(frontPosX, frontPosY, pit) == true) {
			//앞타일에 구덩이
			turnRight();
			return 0;
		}
		if (breeze == true) {
			//바람이 느껴짐
			goForward();
			return 0;
		}
		goForward();
		return 0;
	}
