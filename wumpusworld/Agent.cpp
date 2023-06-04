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
		//��ġ 1,1�� �ű��
		posRow = 4;
		posCol = 1;
		direction = east;
		frontPosRow = posRow;
		frontPosCol = posCol + 1;
		leftPosRow = posRow + 1;
		leftPosCol = posCol;
		rightPosRow = posRow - 1;
		rightPosCol = posCol;
		backPosRow = posRow;
		backPosCol = posCol - 1;
		//ȭ�찳�� �ʱ�ȭ
		arrows = 2;
		//�����ʱ�ȭ
		while (!stk.empty()) {
			stk.pop();
		}
		//visited �ʱ�ȭ
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
			goForward();
		}
		else if (action == turnL) {
			turnLeft();
		}
		else if (action == turnR) {
			turnRight();
		}
		else if (action == grb) {
			grab();
		}
		else if (action == sht) {
			shoot();
		}
		else if (action == clmb) {
			climb();
		}
		else if (action == bmp) {
			goBackward();
		}
		else if (action == dead) {
			die();
		}
	}
	void Agent::reasoning(bool stench, bool breeze, bool glitter, bool bump, bool death) {
		if (death == true) {
			action = dead;
			return;
		}
		visited[posRow][posCol] = true;
		setGrid(posRow, posCol, safe, true);
		if (bump == true) {
			//���� ��ġ�� ƨ���� ����
			setGrid(posRow, posCol, wall, true);
			action = bmp;
			return;
		}
		if (!stench && !breeze) {
			//�ƹ� �ϵ� ������ ��� ����
			setGrid(frontPosRow, frontPosCol, safe, true);
			setGrid(leftPosRow, leftPosCol, safe, true);
			setGrid(rightPosRow, rightPosCol, safe, true);
			setGrid(backPosRow, backPosCol, safe, true);
		}
		if (stk.empty() && havingGold) {
			//���� �ְ� 1,1�� ����
			action = clmb;
			return;
		}
		if (havingGold) {
			// ���� �ְ� ���� 1,1�� �������� ����
			if (frontPosRow != stk.top().first || frontPosCol != stk.top().second) {
				//�Դ� Ÿ���� �ٶ󺸰� ���� ���� ���
				action = turnR;
				return;
			}
			action = go;
			return;
		
		}
		if (glitter == true) {
			action = grb;
			return;
		}


		// �湮���� �ʰ� ���� �ƴ� ������ Ÿ�Ϸ� �̵�
		if (visited[frontPosRow][frontPosCol] == false && isGrid(frontPosRow, frontPosCol, safe) == true && isGrid(frontPosRow, frontPosCol, wall) == false) {
			action = go;
			return;
		}
		else if (visited[rightPosRow][rightPosCol] == false && isGrid(rightPosRow, rightPosCol, safe) == true && isGrid(rightPosRow, rightPosCol, wall) == false) {
			action = turnR;
			return;
		}
		else if (visited[leftPosRow][leftPosCol] == false && isGrid(leftPosRow, leftPosCol, safe) == true && isGrid(leftPosRow, leftPosCol, wall) == false) {
			action = turnL;
			return;
		}
		else if (visited[backPosRow][backPosCol] == false && isGrid(backPosRow, backPosCol, safe) == true && isGrid(backPosRow, backPosCol, wall) == false) {
			action = turnR;
			return;
		}

		if (
			(isGrid(frontPosRow, frontPosCol, wall) == true || isGrid(frontPosRow, frontPosCol, pit) == true) &&
			(isGrid(backPosRow, backPosCol, wall) == true || isGrid(backPosRow, backPosCol, pit) == true) &&
			(isGrid(leftPosRow, leftPosCol, wall) == true || isGrid(leftPosRow, leftPosCol, pit) == true) &&
			(isGrid(rightPosRow, rightPosCol, wall) == true || isGrid(rightPosRow, rightPosCol, pit) == true)
			) {
			//����� �� �� ���� ���
			cout << "����";
			return;
		}

		if (visited[frontPosRow][frontPosCol] == true) {
			//���� �湮�� Ÿ���� ���
			if (
				(isGrid(backPosRow, backPosCol, wall) == true || isGrid(backPosRow, backPosCol, pit) == true || visited[backPosRow][backPosCol] == true) &&
				(isGrid(leftPosRow, leftPosCol, wall) == true || isGrid(leftPosRow, leftPosCol, pit) == true || visited[leftPosRow][leftPosCol] == true) &&
				(isGrid(rightPosRow, rightPosCol, wall) == true || isGrid(rightPosRow, rightPosCol, pit) == true || visited[rightPosRow][rightPosCol] == true)
				) {
				//��, ��, �� �湮�Ұ�(Pit �Ǵ� �� �Ǵ� �湮��)
				if (frontPosRow != stk.top().first || frontPosCol != stk.top().second) {
					//�Դ� Ÿ���� �ٶ󺸰� ���� ���� ���
					action = turnR;
					return;
				}
				else {
					setGrid(posRow, posRow, wall, true);
					action = go;
					return;
				}
			}
			else {
				action = turnR;
				return;
			}
		}
		if (isGrid(frontPosRow, frontPosCol, wall) == true) {
			//���� ���� ���
			action = turnR;
			return;
		}
		if (stench == true || isGrid(frontPosRow, frontPosCol, wumpus) == true) {
			//7.�������ų� �տ� ������ �ִ� ���
			if (shot == true) {
				//�̹� ������
				action = go;
				return;
			}
			else {
				if (arrows > 0) {
					action = sht;
					return;
				}
				else {
					action = go;
					return;
				}
			}
		}
		if (isGrid(frontPosRow, frontPosCol, pit) == true) {
			//��Ÿ�Ͽ� ������
			action = turnR;
			return;
		}
		if (breeze == true) {
			//�ٶ��� ������
			action = go;
			return;
		}
		action = go;
		return;
	}
	