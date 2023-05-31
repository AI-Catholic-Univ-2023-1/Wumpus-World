#include "Agent.h"

Agent::Agent() {

}
	void Agent::goForward() {
		shot = false;
		stk.push(pair<int,int>(posRow, posCol));
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
		rightPosRow = tempCol;
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
		rightPosRow = backPosCol;
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

	}
	void Agent::setGrid(int x, int y, int state, bool t) {
		grid[x][y][state] = t;
	}
	void Agent::goBackward() {
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
	bool Agent::isGrid(int x, int y, int state)
		return [x][y][state];
	}
	int Agent::reasoning(bool stench, bool breeze, bool glitter, bool bump) {
		if (bump == true) {
			//���� ��ġ�� ƨ���� ����
			setGrid(posRow, posCol, wall, true);
			goBackward();
			return 0;
		}
		visited[posRow][posCol] = true;
		setGrid(posRow, posCol, safe, true);
		if (!stench && !breeze) {
			//�ƹ� �ϵ� ������ ��� ����
			setGrid(frontPosRow, frontPosCol, safe, true);
			setGrid(leftPosRow, leftPosCol, safe, true);
			setGrid(rightPosRow, rightPosCol, safe, true);
			setGrid(backPosRow, backPosCol, safe, true);
		}
		if (stk.empty() && havingGold) {
			//���� �ְ� 1,1�� ����
			climb();
			return 3;
		}
		if (havingGold) {
			// ���� �ְ� ���� 1,1�� �������� ����
			if (frontPosRow != stk.top().first || frontPosCol != stk.top().second) {
				//�Դ� Ÿ���� �ٶ󺸰� ���� ���� ���
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
		// �湮���� �ʰ� ���� �ƴ� ������ Ÿ�Ϸ� �̵�
		if (visited[frontPosRow][frontPosCol] == false && isGrid(frontPosRow, frontPosCol, safe) == true && isGrid(frontPosRow, frontPosCol, wall) == false) {
			goForward();
			return 0;
		}
		else if (visited[rightPosRow][rightPosCol] == false && isGrid(rightPosRow, rightPosCol, safe) == true && isGrid(rightPosRow, rightPosCol, wall) == false) {
			turnRight();
			return 0;
		}
		else if (visited[leftPosRow][leftPosCol] == false && isGrid(leftPosRow, leftPosCol, safe) == true && isGrid(leftPosRow, leftPosCol, wall) == false) {
			turnLeft();
			return 0;
		}
		else if (visited[backPosRow][backPosCol] == false && isGrid(backPosRow, backPosCol, safe) == true && isGrid(backPosRow, backPosCol, wall) == false) {
			turnRight();
			return 0;
		}

		if (
			(isGrid(frontPosRow, frontPosCol, wall) == true || isGrid(frontPosRow, frontPosCol, pit) == true) &&
			(isGrid(backPosRow, backPosCol, wall) == true || isGrid(backPosRow, backPosCol, pit) == true) &&
			(isGrid(leftPosRow, leftPosCol, wall) == true || isGrid(leftPosRow, leftPosCol, pit) == true) &&
			(isGrid(rightPosRow, rightPosCol, wall) == true || isGrid(rightPosRow, rightPosCol, pit) == true)
			) {
			//����� �� �� ���� ���
			return 3;
		}

		if (visited[frontPosRow][frontPosCol] == true) {
			//���� �湮�� Ÿ���� ���
			if (
				(isGrid(backPosRow, backPosCol, wall) == true || isGrid(backPosRow, backPosCol, pit) == true || visited[backPosRow][backPosCol]==true) &&
				(isGrid(leftPosRow, leftPosCol, wall) == true || isGrid(leftPosRow,leftPosCol,pit) == true|| visited[leftPosRow][leftPosCol]==true) &&
				(isGrid(rightPosRow, rightPosCol, wall) == true || isGrid(rightPosRow,rightPosCol,pit)==true|| visited[rightPosRow][rightPosCol]==true)
				) {
				//��, ��, �� �湮�Ұ�(Pit �Ǵ� �� �Ǵ� �湮��)
				if (frontPosRow != stk.top().first || frontPosCol != stk.top().second) {
					//�Դ� Ÿ���� �ٶ󺸰� ���� ���� ���
					turnRight();
					return 0;
				}
				else {
					setGrid(posRow, posRow, wall, true);
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
		if (isGrid(frontPosRow, frontPosCol, wall) == true) {
			//���� ���� ���
			turnRight();
			return 0;
		}
		if (stench == true || isGrid(frontPosRow, frontPosCol, wumpus) == true) {
			//7.�������ų� �տ� ������ �ִ� ���
			if (shot == true) {
				//�̹� ������
				goForward();
				return 0;
			}
			else {
				if (arrows > 0) {
					shoot();
					return 1;
				}
				else {
					goForward();
					return 0;
				}
			}
		}
		if (isGrid(frontPosRow, frontPosCol, pit) == true) {
			//��Ÿ�Ͽ� ������
			turnRight();
			return 0;
		}
		if (breeze == true) {
			//�ٶ��� ������
			goForward();
			return 0;
		}
		goForward();
		return 0;
	}
