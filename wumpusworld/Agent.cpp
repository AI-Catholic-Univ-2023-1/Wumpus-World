#include "Agent.h"

Agent::Agent() {
}
void Agent::printState() {
	cout << "direction = " << direction<<"\n";
	cout << "row = " << posRow << "\n";
	cout << "col = " << posCol << "\n";
	cout << "Lrow = " << leftPosRow << "\n";
	cout << "Lcol = " << leftPosCol << "\n";
	cout << "Rrow = " << rightPosRow << "\n";
	cout << "Rcol = " << rightPosCol << "\n";
	cout << "Brow = " << backPosRow << "\n";
	cout << "Bcol = " << backPosCol << "\n";

}
void Agent::goForward() {
	shot = false;
	if (visited[frontPosRow][frontPosCol] == false) {
		stk.push(pair<int, int>(posRow, posCol));
	}
	else {
		stk.pop();
	}
	if (direction == north) {
		posRow--;
		frontPosRow--;
		backPosRow--;
		leftPosRow--;
		rightPosRow--;
	}
	else if (direction == south) {
		posRow++;
		frontPosRow++;
		backPosRow++;
		leftPosRow++;
		rightPosRow++;
	}
	else if (direction == east) {
		posCol++;
		frontPosCol++;
		backPosCol++;
		leftPosCol++;
		rightPosCol++;
	}
	else if (direction == west) {
		posCol--;
		frontPosCol--;
		backPosCol--;
		leftPosCol--;
		rightPosCol--;
	}
}
	void Agent::goForwardWithoutStacking() {
		shot = false;
		stk.pop();
		if (direction == north) {
			posRow--;
			frontPosRow--;
			backPosRow--;
			leftPosRow--;
			rightPosRow--;
		}
		else if (direction == south) {
			posRow++;
			frontPosRow++;
			backPosRow++;
			leftPosRow++;
			rightPosRow++;
		}
		else if (direction == east) {
			posCol++;
			frontPosCol++;
			backPosCol++;
			leftPosCol++;
			rightPosCol++;
		}
		else if (direction == west) {
			posCol--;
			frontPosCol--;
			backPosCol--;
			leftPosCol--;
			rightPosCol--;
		}

	}
	void Agent::turnLeft() {
		shot = false;
		if (direction == east) {
			direction = north;
		}
		else {
			direction--;
		}
		int tempRow = frontPosRow;
		int tempCol = frontPosCol;
		frontPosRow = leftPosRow;
		frontPosCol = leftPosCol;
		leftPosRow = backPosRow;
		leftPosCol = backPosCol;
		backPosRow = rightPosRow;
		backPosCol = rightPosCol;
		rightPosRow = tempRow;
		rightPosCol = tempCol;
	}
	void Agent::turnRight() {
		shot = false;
		if (direction == north) {
			direction = east;
		}
		else {
			direction++;
		}
		int tempRow = frontPosRow;
		int tempCol = frontPosCol;
		frontPosRow = rightPosRow;
		frontPosCol = rightPosCol;
		rightPosRow = backPosRow;
		rightPosCol = backPosCol;
		backPosRow = leftPosRow;
		backPosCol = leftPosCol;
		leftPosRow = tempRow;
		leftPosCol = tempCol;
	}
	void Agent::shoot() {
		shot = true;
		arrows--;
	}
	void Agent::climb() {
	}
	void Agent::grab() {
		havingGold = true;
	}
	void Agent::die() {
		deathCount++;
		//위치 1,1로 옮기기
		posRow = 4;
		posCol = 1;
		direction = east;
		frontPosRow = posRow;
		frontPosCol = posCol + 1;
		leftPosRow = posRow - 1;
		leftPosCol = posCol;
		rightPosRow = posRow + 1;
		rightPosCol = posCol;
		backPosRow = posRow;
		backPosCol = posCol - 1;
		//화살개수 초기화
		arrows = 2;
		//스택초기화
		while (!stk.empty()) {
			stk.pop();
		}
		//visited 초기화
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				visited[i][j] = false;
			}
		}
	}
	void Agent::setGrid(int x, int y, int state, bool t) {
		grid[x][y][state] = t;
	}
	void Agent::goBackward() {
		stk.pop();
		if (direction == north) {
			posRow++;
			frontPosRow++;
			backPosRow++;
			leftPosRow++;
			rightPosRow++;
		}
		else if (direction == south) {
			posRow--;
			frontPosRow--;
			backPosRow--;
			leftPosRow--;
			rightPosRow--;
		}
		else if (direction == east) {
			posCol--;
			frontPosCol--;
			backPosCol--;
			leftPosCol--;
			rightPosCol--;
		}
		else if (direction == west) {
			posCol++;
			frontPosCol++;
			backPosCol++;
			leftPosCol++;
			rightPosCol++;
		}
	}
	bool Agent::isGrid(int x, int y, int state) {
		return grid[x][y][state];
	}
	void Agent::doAction() {
		if (action == go) {
			costFunc++;
			goForward();
		}
		else if (action == turnL) {
			costFunc++;
			turnLeft();
		}
		else if (action == turnR) {
			costFunc++;
			turnRight();
		}
		else if (action == grb) {
			costFunc++;
			grab();
		}
		else if (action == sht) {
			costFunc++;
			shoot();
		}
		else if (action == clmb) {
			costFunc++;
			climb();
		}
		else if (action == bmp) {
			goBackward();
		}
		else if (action == dead) {
			die();
		}
	}
	void Agent::checkSafe() {

	}
	void Agent::reasoning(bool stench, bool breeze, bool isGlitter, bool bump, bool death) {
		if (stk.empty() && havingGold) {
			//금이 있고 1,1에 도착
			action = clmb;
			return;
		}
		if (death == true) {
			action = dead;
			return;
		}
		visited[posRow][posCol] = true;
		setGrid(posRow, posCol, safe, true);
		if (bump == true) {
			//벽과 겹치면 튕겨져 나옴
			setGrid(posRow, posCol, wall, true);
			action = bmp;
			return;
		}
		if (!stench && !breeze) {
			//아무 일도 없으면 사방 안전
			setGrid(frontPosRow, frontPosCol, safe, true);
			setGrid(leftPosRow, leftPosCol, safe, true);
			setGrid(rightPosRow, rightPosCol, safe, true);
			setGrid(backPosRow, backPosCol, safe, true);
		}
		if (havingGold) {
			// 금이 있고 아직 1,1에 도착하지 못함
			if (frontPosRow != stk.top().first || frontPosCol != stk.top().second) {
				//왔던 타일을 바라보고 있지 않을 경우
				if (leftPosRow == stk.top().first && leftPosCol == stk.top().second) {
					action = turnL;
					return;
				}
				else if (rightPosRow == stk.top().first && rightPosCol == stk.top().second) {
					action = turnR;
					return;
				}
				action = turnL;
				return;
			}
			action = go;
			return;
		
		}
		if (isGlitter == true) {
			setGrid(posRow, posCol, glitter, true);
			action = grb;
			return;
		}


		// 방문하지 않고 벽이 아닌 안전한 타일로 이동
		if (visited[frontPosRow][frontPosCol] == false && isGrid(frontPosRow, frontPosCol, safe) == true && isGrid(frontPosRow, frontPosCol, wall) == false && isGrid(frontPosRow, frontPosCol, blocked) == false) {
			action = go;
			return;
		}
		else if (visited[leftPosRow][leftPosCol] == false && isGrid(leftPosRow, leftPosCol, safe) == true && isGrid(leftPosRow, leftPosCol, wall) == false && isGrid(leftPosRow, leftPosCol, blocked) == false) {
			action = turnL;
			return;
		}
		else if (visited[rightPosRow][rightPosCol] == false && isGrid(rightPosRow, rightPosCol, safe) == true && isGrid(rightPosRow, rightPosCol, wall) == false && isGrid(rightPosRow, rightPosCol, blocked) == false) {
			action = turnR;
			return;
		}
		else if (visited[backPosRow][backPosCol] == false && isGrid(backPosRow, backPosCol, safe) == true && isGrid(backPosRow, backPosCol, wall) == false && isGrid(backPosRow, backPosCol, blocked) == false) {
			action = turnR;
			return;
		}

		if (
			(isGrid(frontPosRow, frontPosCol, wall) == true || isGrid(frontPosRow, frontPosCol, pit) == true || isGrid(frontPosRow, frontPosCol, blocked) == true) &&
			(isGrid(backPosRow, backPosCol, wall) == true || isGrid(backPosRow, backPosCol, pit) == true || isGrid(backPosRow, backPosCol, blocked) == true) &&
			(isGrid(leftPosRow, leftPosCol, wall) == true || isGrid(leftPosRow, leftPosCol, pit) == true || isGrid(leftPosRow, leftPosCol, blocked) == true) &&
			(isGrid(rightPosRow, rightPosCol, wall) == true || isGrid(rightPosRow, rightPosCol, pit) == true || isGrid(rightPosRow, rightPosCol, blocked) == true)
			) {
			//사방이 갈 수 없는 경우
			action = clmb;
			return;
		}

		if (visited[frontPosRow][frontPosCol] == true) {
			//앞이 방문한 타일일 경우
			if (
				(isGrid(backPosRow, backPosCol, wall) == true || isGrid(backPosRow, backPosCol, pit) == true || visited[backPosRow][backPosCol] == true || isGrid(backPosRow, backPosCol, blocked) == true) &&
				(isGrid(leftPosRow, leftPosCol, wall) == true || isGrid(leftPosRow, leftPosCol, pit) == true || visited[leftPosRow][leftPosCol] == true || isGrid(leftPosRow, leftPosCol, blocked) == true) &&
				(isGrid(rightPosRow, rightPosCol, wall) == true || isGrid(rightPosRow, rightPosCol, pit) == true || visited[rightPosRow][rightPosCol] == true || isGrid(rightPosRow, rightPosCol, blocked) == true)
				) {
				//뒤, 좌, 우 방문불가(Pit 또는 벽 또는 방문함)
				if (frontPosRow != stk.top().first || frontPosCol != stk.top().second) {
					//왔던 타일을 바라보고 있지 않을 경우
					if (leftPosRow == stk.top().first && leftPosCol == stk.top().second) {
						action = turnL;
						return;
					}
					else if (rightPosRow == stk.top().first && rightPosCol == stk.top().second) {
						action = turnR;
						return;
					}
					action = turnL;
					return;
				}
				else {
					setGrid(posRow, posCol, blocked, true);
					setGrid(posRow, posCol, safe, false);
					action = go;
					return;
				}
			}
			else {
				action = turnL;
				return;
			}
		}
		if (stench == true) {//냄새가 나는데 3방향 타일의 정보가 있고,  남은 타일에 대한 정보가 없으면 그 타일은 괴물
			if (
				((visited[backPosRow][backPosCol] == true && isGrid(backPosRow, backPosCol, wumpus) == false)||isGrid(backPosRow,backPosCol,wall)==true || isGrid(backPosRow, backPosCol, blocked) == true) &&
				((visited[leftPosRow][leftPosCol] == true && isGrid(leftPosRow, leftPosCol, wumpus) == false) || isGrid(leftPosRow, leftPosCol, wall) == true || isGrid(leftPosRow, leftPosCol, blocked) == true) &&
				((visited[rightPosRow][rightPosCol] == true && isGrid(rightPosRow, rightPosCol, wumpus) == false) || isGrid(rightPosRow, rightPosCol, wall) == true || isGrid(rightPosRow, rightPosCol, blocked) == true) &&
				(visited[frontPosRow][frontPosCol] == false && isGrid(frontPosRow, frontPosCol, wumpus) == false)
				) {
				setGrid(frontPosRow, frontPosCol, wumpus, true);
				action = none;
				return;
			}
			else if (
				((visited[backPosRow][backPosCol] == true && isGrid(backPosRow, backPosCol, wumpus) == false) || isGrid(backPosRow, backPosCol, wall) == true || isGrid(backPosRow, backPosCol, blocked) == true) &&
				((visited[leftPosRow][leftPosCol] == true && isGrid(leftPosRow, leftPosCol, wumpus) == false) || isGrid(leftPosRow, leftPosCol, wall) == true || isGrid(leftPosRow, leftPosCol, blocked) == true) &&
				((visited[frontPosRow][frontPosCol] == true && isGrid(frontPosRow, frontPosCol, wumpus) == false) || isGrid(frontPosRow, frontPosCol, wall) == true || isGrid(frontPosRow, frontPosCol, blocked) == true) &&
				(visited[rightPosRow][rightPosCol] == false && isGrid(rightPosRow, rightPosCol, wumpus) == false)
				) {
				setGrid(rightPosRow, rightPosCol, wumpus, true);
				action = none;
				return;
			}
			else if (
				((visited[backPosRow][backPosCol] == true && isGrid(backPosRow, backPosCol, wumpus) == false) || isGrid(backPosRow, backPosCol, wall) == true || isGrid(backPosRow, backPosCol, blocked) == true) &&
				((visited[frontPosRow][frontPosCol] == true && isGrid(frontPosRow, frontPosCol, wumpus) == false) || isGrid(frontPosRow, frontPosCol, wall) == true || isGrid(frontPosRow, frontPosCol, blocked) == true) &&
				((visited[rightPosRow][rightPosCol] == true && isGrid(rightPosRow, rightPosCol, wumpus) == false) || isGrid(rightPosRow, rightPosCol, wall) == true || isGrid(rightPosRow, rightPosCol, blocked) == true) &&
				(visited[leftPosRow][leftPosCol] == false && isGrid(leftPosRow, leftPosCol, wumpus) == false)
				) {
				setGrid(leftPosRow, leftPosCol, wumpus, true);
				action = none;
				return;
			}
			else if (
				((visited[frontPosRow][frontPosCol] == true && isGrid(frontPosRow, frontPosCol, wumpus) == false) || isGrid(frontPosRow, frontPosCol, wall) == true || isGrid(frontPosRow, frontPosCol, blocked) == true) &&
				((visited[leftPosRow][leftPosCol] == true && isGrid(leftPosRow, leftPosCol, wumpus) == false) || isGrid(leftPosRow, leftPosCol, wall) == true || isGrid(leftPosRow, leftPosCol, blocked) == true) &&
				((visited[rightPosRow][rightPosCol] == true && isGrid(rightPosRow, rightPosCol, wumpus) == false) || isGrid(rightPosRow, rightPosCol, wall) == true || isGrid(rightPosRow, rightPosCol, blocked) == true) &&
				(visited[backPosRow][backPosCol] == false && isGrid(backPosRow, frontPosCol, backPosCol) == false)
				) {
				setGrid(backPosRow, backPosCol, wumpus, true);
				action = none;
				return;
			}
		}
		if (breeze == true) {//바람이 부는데 3방향 타일의 정보가 있고,  남은 타일에 대한 정보가 없으면 그 타일은 구덩이
			if (
				((visited[backPosRow][backPosCol] == true && isGrid(backPosRow, backPosCol, pit) == false) || isGrid(backPosRow, backPosCol, wall) == true || isGrid(backPosRow, backPosCol, blocked) == true) &&
				((visited[leftPosRow][leftPosCol] == true && isGrid(leftPosRow, leftPosCol, pit) == false) || isGrid(leftPosRow, leftPosCol, wall) == true || isGrid(leftPosRow, leftPosCol, blocked) == true) &&
				((visited[rightPosRow][rightPosCol] == true && isGrid(rightPosRow, rightPosCol, pit) == false) || isGrid(rightPosRow, rightPosCol, wall) == true || isGrid(rightPosRow, rightPosCol, blocked) == true) &&
				(visited[frontPosRow][frontPosCol] == false && isGrid(frontPosRow, frontPosCol, pit) == false)
				) {
				setGrid(frontPosRow, frontPosCol, pit, true);
				action = none;
				return;
			}
			else if (
				((visited[backPosRow][backPosCol] == true && isGrid(backPosRow, backPosCol, pit) == false) || isGrid(backPosRow, backPosCol, wall) == true || isGrid(backPosRow, backPosCol, blocked) == true) &&
				((visited[leftPosRow][leftPosCol] == true && isGrid(leftPosRow, leftPosCol, pit) == false) || isGrid(leftPosRow, leftPosCol, wall) == true || isGrid(leftPosRow, leftPosCol, blocked) == true) &&
				((visited[frontPosRow][frontPosCol] == true && isGrid(frontPosRow, frontPosCol, pit) == false) || isGrid(frontPosRow, frontPosCol, wall) == true || isGrid(frontPosRow, frontPosCol, blocked) == true) &&
				(visited[rightPosRow][rightPosCol] == false && isGrid(rightPosRow, rightPosCol, pit) == false)
				) {
				setGrid(rightPosRow, rightPosCol, pit, true);
				action = none;
				return;
			}
			else if (
				((visited[backPosRow][backPosCol] == true && isGrid(backPosRow, backPosCol, pit) == false) || isGrid(backPosRow, backPosCol, wall) == true || isGrid(backPosRow, backPosCol, blocked) == true) &&
				((visited[frontPosRow][frontPosCol] == true && isGrid(frontPosRow, frontPosCol, pit) == false) || isGrid(frontPosRow, frontPosCol, wall) == true || isGrid(frontPosRow, frontPosCol, blocked) == true) &&
				((visited[rightPosRow][rightPosCol] == true && isGrid(rightPosRow, rightPosCol, pit) == false) || isGrid(rightPosRow, rightPosCol, wall) == true || isGrid(rightPosRow, rightPosCol, blocked) == true) &&
				(visited[leftPosRow][leftPosCol] == false && isGrid(leftPosRow, leftPosCol, pit) == false)
				) {
				setGrid(leftPosRow, leftPosCol, pit, true);
				action = none;
				return;
			}
			else if (
				((visited[frontPosRow][frontPosCol] == true && isGrid(frontPosRow, frontPosCol, pit) == false) || isGrid(frontPosRow, frontPosCol, wall) == true || isGrid(frontPosRow, frontPosCol, blocked) == true) &&
				((visited[leftPosRow][leftPosCol] == true && isGrid(leftPosRow, leftPosCol, pit) == false) || isGrid(leftPosRow, leftPosCol, wall) == true || isGrid(leftPosRow, leftPosCol, blocked) == true) &&
				((visited[rightPosRow][rightPosCol] == true && isGrid(rightPosRow, rightPosCol, pit) == false) || isGrid(rightPosRow, rightPosCol, wall) == true || isGrid(rightPosRow, rightPosCol, blocked) == true) &&
				(visited[backPosRow][backPosCol] == false && isGrid(backPosRow, backPosCol, pit) == false)
				) {
				setGrid(backPosRow, backPosCol, pit, true);
				action = none;
				return;
			}
		}
		//괴물이 있는 쪽으로 돌리기
		if (isGrid(leftPosRow, leftPosCol, wumpus) == true && isGrid(frontPosRow,frontPosCol,wumpus)==false) {
			action = turnL;
			return;
		}
		if (isGrid(rightPosRow, rightPosCol, wumpus) == true && isGrid(frontPosRow, frontPosCol, wumpus) == false) {
			action = turnR;
			return; 
		}
		if (isGrid(backPosRow, backPosCol, wumpus) == true && isGrid(frontPosRow, frontPosCol, wumpus) == false) {
			action = turnR;
			return;
		}
		if (isGrid(frontPosRow, frontPosCol, wall) == true || isGrid(frontPosRow, frontPosCol, blocked) == true || isGrid(frontPosRow, frontPosCol, pit) == true) {
			//앞이 벽, x, 구덩이인 경우
			action = turnL;
			return;
		}
		if (stench == true || isGrid(frontPosRow, frontPosCol, wumpus) == true) {
			//7.냄새나거나 앞에 괴물
			if (arrows > 0 && shot==false) {
				action = sht;
				return;
			}
			else {
				action = go;
				return;
			}
		}
		if (isGrid(frontPosRow, frontPosCol, pit) == true) {
			//앞타일에 구덩이
			action = turnL;
			return;
		}
		if (breeze == true) {
			//바람이 느껴짐
			action = go;
			return;
		}
		action = go;
		return;
	}
	