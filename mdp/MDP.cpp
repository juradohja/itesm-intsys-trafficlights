#include "MDP.h";
MDP::MDP(float rewards[][BOARD_SIZE_Y], float gammaValue){

	for(int x = 1; x<BOARD_SIZE_X-1; x++) {
		for (int y = 1; y < BOARD_SIZE_Y-1; y++) {
			optimalRules[x][y] = -1;
		}
	}

	for(int x = 1; x<BOARD_SIZE_X-1; x++) {
		for (int y = 1; y < BOARD_SIZE_Y-1; y++) {
			nextRules[x][y] = -2;
		}
	}

	for(int x = 1; x<BOARD_SIZE_X-1; x++) {
		for (int y = 1; y < BOARD_SIZE_Y-1; y++) {
			originalvalueGrid[x][y] = rewards[x][y];
			valueGrid[x][y] = rewards[x][y];
			nextValueGrid[x][y] = 0.0f;
		}
	}

	gamma = gammaValue;
}

MDP::~MDP(){}

bool MDP::didConverge(){
	for(int x = 1; x<BOARD_SIZE_X-1; x++) {
		for (int y = 1; y <BOARD_SIZE_Y-1; y++) {
			if(nextRules[x][y] != optimalRules[x][y]){
				return false;
			}
		}
	}
	return true;
}

void MDP::doMDP(){
	std::cout << "DO MDP!"<<endl;
	int move = 0;
	int n = 0;
	int l;
	float probability = 0.0f;
	float calculateValue = 0.0f;
	float currentMax = -std::numeric_limits<float>::max();
	bool flag;
	// 0 -> Stay
	// 1 -> Right
	// 2 -> UpRight
	// 3 -> up
	// 4 -> UpLeft
	// 5 -> Left
	// 6 -> DownLeft
	// 7 -> Down
	// 8 -> DownRight
	int inX[9] = {0,1,1,0,-1,-1,-1,0,1};
	int inY[9] = {0,0,1,1,1,0,-1,-1,-1};
	int countConv = 0;
	do {
		//std::cout << "ENTERED DO: "<< n <<endl;
		flag = false;
		for(int x = 1; x<BOARD_SIZE_X-1; x++) {
			for (int y = 1; y <BOARD_SIZE_Y-1; y++) {
				for(int k = 1; k<9; k++) {

					for(l = 1; l<9; l++) {
						// change probability value
						if(l == k) {
							probability = 0.9f;
						} else {
							probability = 0.014f;
						}
						calculateValue += (probability * valueGrid[x+inX[l]][y+inY[l]]);
					}

					if(calculateValue > currentMax) {
						//std::cout << "change value ENTERED" << endl;
						currentMax = calculateValue;
						move = k;
					}
					calculateValue = 0.0f;

				}
				nextValueGrid[x][y] = originalvalueGrid[x][y]+currentMax*gamma;
				nextRules[x][y] = move;
				//std::cout << "for i: "<< i <<" j: "<< j<< " new value: "<<nextValueGrid[i][j] << " new move: "<< nextRules[i][j] << endl; 
				calculateValue = 0.0f;
				move = 0; //move that has to be updated to new grid
				currentMax = -std::numeric_limits<float>::max();
			}
		}

		//update values of grid
		for(int x = 1; x< BOARD_SIZE_X-1; x++) {
			for (int y = 1; y < BOARD_SIZE_Y-1; y++) {
				valueGrid[x][y] = nextValueGrid[x][y];
				if (optimalRules[x][y] != nextRules[x][y]) {
					flag = true;
					countConv = 0;
				}
				optimalRules[x][y] = nextRules[x][y];
			}
		}
		if (flag == false) {
			countConv++;
		}
		n++;
		if (n%15 == 0) {
			std::cout << "ITERATION N:     " << n << "<---------------Internal print value---------------->" << endl;
			for (int y = BOARD_SIZE_Y-2; y > 0; y--) {
				for (int x = 1; x < BOARD_SIZE_X-1; x++) {
					//std::cout.precision(2);
					std::cout << optimalRules[x][y] << " ";
					if(x == 40 || x== 60) {
						std::cout << "   ";
					}
				}
				std::cout << endl;
				if(y == 41 || y== 61) {
					std::cout << endl;
					std::cout << endl;
				}
			}
		}
		
	} //while(n < 5);
	while(flag  && countConv < 10);
}



// just for code test

int main() {

	/* //prity print
	float rewards[BOARD_SIZE_X][BOARD_SIZE_Y];

	for(int x = 1; x< BOARD_SIZE_X-1; x++) {
		for (int y = 1; y < BOARD_SIZE_Y-1; y++) {
			if((x < 41 && y < 41) ||
			(x >= 61 && y < 41) ||
			(x < 41 && y >= 61) ||
			(x >= 61 && y >= 61)) {
				rewards[x][y] = 0; //walls -20.0f
			} else if((x>= 47 && x <= 54) &&
				(y>= 47 && y <= 54)) {
				rewards[x][y] = 0; //wall glorieta -20.0f
			} else if (x == 100 || y == 1) {
				rewards[x][y] = 8; //goals 10.0f
			} else if((x < 43 && y < 43) ||
			(x >= 59 && y < 43) ||
			(x < 43 && y >= 59) ||
			(x >= 59 && y >= 59)) {
				rewards[x][y] = 1; //sidewalk -2.0f
			} else {
				rewards[x][y] = 2; //white space -0.4f
			}
		}
	}

	//reset
	rewards[47][47] = 2;
	rewards[48][47] = 2;
	rewards[47][48] = 2;
	rewards[48][48] = 2;

	rewards[53][47] = 2;
	rewards[54][47] = 2;
	rewards[53][48] = 2;
	rewards[54][48] = 2;

	rewards[53][53] = 2;
	rewards[54][53] = 2;
	rewards[53][54] = 2;
	rewards[54][54] = 2;

	rewards[47][53] = 2;
	rewards[48][53] = 2;
	rewards[47][54] = 2;
	rewards[48][54] = 2;

	//walls in goal west
	rewards[96][46] = 0;
	rewards[97][46] = 0;
	rewards[98][46] = 0;
	rewards[99][46] = 0;
	rewards[100][46] = 0;

	rewards[96][51] = 0;
	rewards[97][51] = 0;
	rewards[98][51] = 0;
	rewards[99][51] = 0;
	rewards[100][51] = 0;

	rewards[96][56] = 0;
	rewards[97][56] = 0;
	rewards[98][56] = 0;
	rewards[99][56] = 0;
	rewards[100][56] = 0;

	//walls in goal south
	rewards[45][1] = 0;
	rewards[45][2] = 0;
	rewards[45][3] = 0;
	rewards[45][4] = 0;
	rewards[45][5] = 0;

	rewards[50][1] = 0;
	rewards[50][2] = 0;
	rewards[50][3] = 0;
	rewards[50][4] = 0;
	rewards[50][5] = 0;

	rewards[55][1] = 0;
	rewards[55][2] = 0;
	rewards[55][3] = 0;
	rewards[55][4] = 0;
	rewards[55][5] = 0;


	std::cout << "<--------------------Initial REWARDS---------------->" << endl;
	for (int y = BOARD_SIZE_Y-2; y > 0; y--) {
		for (int x = 1; x < BOARD_SIZE_X-1; x++) {
			std::cout << std::setprecision(0);
			std::cout << rewards[x][y] << " ";
			if(x == 40 || x== 60) {
				std::cout << "   ";
			}
		}
		std::cout << endl;
		if(y == 41 || y== 61) {
			std::cout << endl;
			std::cout << endl;
		}
	}

	MDP * mdp = new MDP(rewards,0.8);
	mdp->doMDP();

	std::cout << "<--------------------FINAL OPTIMAL RULES---------------->" << endl;
	for (int y = BOARD_SIZE_Y-2; y > 0; y--) {
		for (int x = 1; x < BOARD_SIZE_X-1; x++) {
			std::cout << mdp->optimalRules[x][y] << " ";
			if(x == 40 || x== 60) {
				std::cout << "   ";
			}
		}
		std::cout << endl;
		if(y == 41 || y== 61) {
			std::cout << endl;
			std::cout << endl;
		}
	}*/

	float rewards[BOARD_SIZE_X][BOARD_SIZE_Y];

	for(int x = 1; x< BOARD_SIZE_X-1; x++) {
		for (int y = 1; y < BOARD_SIZE_Y-1; y++) {
			if((x < 41 && y < 41) ||
			(x >= 61 && y < 41) ||
			(x < 41 && y >= 61) ||
			(x >= 61 && y >= 61)) {
				rewards[x][y] = WALL_REWARD; //walls -20.0f
			} else if((x>= 47 && x <= 54) &&
				(y>= 47 && y <= 54)) {
				rewards[x][y] = WALL_REWARD; //wall glorieta -20.0f
			} else if (x == 100) {
				rewards[x][y] = GOAL_REWARD; //goals 10.0f
			} else if((x < 43 && y < 43) ||
			(x >= 59 && y < 43) ||
			(x < 43 && y >= 59) ||
			(x >= 59 && y >= 59)) {
				rewards[x][y] = SIDEWALK_REWARD; //sidewalk -2.0f
			} else {
				rewards[x][y] = WHITE_SPACE_REWARD; //white space -0.4f
			}
		}
	}

	//reset
	rewards[47][47] = WHITE_SPACE_REWARD;
	rewards[48][47] = WHITE_SPACE_REWARD;
	rewards[47][48] = WHITE_SPACE_REWARD;
	rewards[48][48] = WHITE_SPACE_REWARD;

	rewards[53][47] = WHITE_SPACE_REWARD;
	rewards[54][47] = WHITE_SPACE_REWARD;
	rewards[53][48] = WHITE_SPACE_REWARD;
	rewards[54][48] = WHITE_SPACE_REWARD;

	rewards[53][53] = WHITE_SPACE_REWARD;
	rewards[54][53] = WHITE_SPACE_REWARD;
	rewards[53][54] = WHITE_SPACE_REWARD;
	rewards[54][54] = WHITE_SPACE_REWARD;

	rewards[47][53] = WHITE_SPACE_REWARD;
	rewards[48][53] = WHITE_SPACE_REWARD;
	rewards[47][54] = WHITE_SPACE_REWARD;
	rewards[48][54] = WHITE_SPACE_REWARD;

	//walls in goal west
	rewards[96][46] = WALL_REWARD;
	rewards[97][46] = WALL_REWARD;
	rewards[98][46] = WALL_REWARD;
	rewards[99][46] = WALL_REWARD;
	rewards[100][46] = WALL_REWARD;

	rewards[96][51] = WALL_REWARD;
	rewards[97][51] = WALL_REWARD;
	rewards[98][51] = WALL_REWARD;
	rewards[99][51] = WALL_REWARD;
	rewards[100][51] = WALL_REWARD;

	rewards[96][56] = WALL_REWARD;
	rewards[97][56] = WALL_REWARD;
	rewards[98][56] = WALL_REWARD;
	rewards[99][56] = WALL_REWARD;
	rewards[100][56] = WALL_REWARD;

	//walls in goal south
	rewards[45][1] = WALL_REWARD;
	rewards[45][2] = WALL_REWARD;
	rewards[45][3] = WALL_REWARD;
	rewards[45][4] = WALL_REWARD;
	rewards[45][5] = WALL_REWARD;

	rewards[50][1] = WALL_REWARD;
	rewards[50][2] = WALL_REWARD;
	rewards[50][3] = WALL_REWARD;
	rewards[50][4] = WALL_REWARD;
	rewards[50][5] = WALL_REWARD;

	rewards[55][1] = WALL_REWARD;
	rewards[55][2] = WALL_REWARD;
	rewards[55][3] = WALL_REWARD;
	rewards[55][4] = WALL_REWARD;
	rewards[55][5] = WALL_REWARD;

	MDP * mdp = new MDP(rewards,0.8);
	mdp->doMDP();

	std::cout << "<--------------------FINAL OPTIMAL RULES---------------->" << endl;
	for (int y = BOARD_SIZE_Y-2; y > 0; y--) {
		for (int x = 1; x < BOARD_SIZE_X-1; x++) {
			std::cout << mdp->optimalRules[x][y] << " ";
			if(x == 40 || x== 60) {
				std::cout << "   ";
			}
		}
		std::cout << endl;
		if(y == 41 || y== 61) {
			std::cout << endl;
			std::cout << endl;
		}
	}

	/*
	float rewards2[BOARD_SIZE_X][BOARD_SIZE_Y];

	for(int x = 1; x< BOARD_SIZE_X-1; x++) {
		for (int y = 1; y < BOARD_SIZE_Y-1; y++) {
			if((x < 41 && y < 41) ||
			(x >= 61 && y < 41) ||
			(x < 41 && y >= 61) ||
			(x >= 61 && y >= 61)) {
				rewards2[x][y] = -50.0f; //walls -20.0f
			} else if((x>= 47 && x <= 54) &&
				(y>= 47 && y <= 54)) {
				rewards2[x][y] = -50.0f; //wall glorieta -20.0f
			} else if (y == 1) {
				rewards2[x][y] = 10.0f; //goals 10.0f
			} else if((x < 43 && y < 43) ||
			(x >= 59 && y < 43) ||
			(x < 43 && y >= 59) ||
			(x >= 59 && y >= 59)) {
				rewards2[x][y] = -5.0f; //sidewalk -2.0f
			} else {
				rewards2[x][y] = -0.4f; //white space -0.4f
			}
		}
	}

	//reset
	rewards2[47][47] = -0.4f;
	rewards2[48][47] = -0.4f;
	rewards2[47][48] = -0.4f;
	rewards2[48][48] = -0.4f;

	rewards2[53][47] = -0.4f;
	rewards2[54][47] = -0.4f;
	rewards2[53][48] = -0.4f;
	rewards2[54][48] = -0.4f;

	rewards2[53][53] = -0.4f;
	rewards2[54][53] = -0.4f;
	rewards2[53][54] = -0.4f;
	rewards2[54][54] = -0.4f;

	rewards2[47][53] = -0.4f;
	rewards2[48][53] = -0.4f;
	rewards2[47][54] = -0.4f;
	rewards2[48][54] = -0.4f;

	//walls in goal west
	rewards2[96][46] = -50.0f;
	rewards2[97][46] = -50.0f;
	rewards2[98][46] = -50.0f;
	rewards2[99][46] = -50.0f;
	rewards2[100][46] = -50.0f;

	rewards2[96][51] = -50.0f;
	rewards2[97][51] = -50.0f;
	rewards2[98][51] = -50.0f;
	rewards2[99][51] = -50.0f;
	rewards2[100][51] = -50.0f;

	rewards2[96][56] = -50.0f;
	rewards2[97][56] = -50.0f;
	rewards2[98][56] = -50.0f;
	rewards2[99][56] = -50.0f;
	rewards2[100][56] = -50.0f;

	//walls in goal south
	rewards2[45][1] = -50.0f;
	rewards2[45][2] = -50.0f;
	rewards2[45][3] = -50.0f;
	rewards2[45][4] = -50.0f;
	rewards2[45][5] = -50.0f;

	rewards2[50][1] = -50.0f;
	rewards2[50][2] = -50.0f;
	rewards2[50][3] = -50.0f;
	rewards2[50][4] = -50.0f;
	rewards2[50][5] = -50.0f;

	rewards2[55][1] = -50.0f;
	rewards2[55][2] = -50.0f;
	rewards2[55][3] = -50.0f;
	rewards2[55][4] = -50.0f;
	rewards2[55][5] = -50.0f;

	MDP * mdp2 = new MDP(rewards2,0.8);
	mdp2->doMDP();

	std::cout << "<--------------------FINAL OPTIMAL RULES---------------->" << endl;
	for (int y = BOARD_SIZE_Y-2; y > 0; y--) {
		for (int x = 1; x < BOARD_SIZE_X-1; x++) {
			std::cout << mdp2->optimalRules[x][y] << " ";
			if(x == 40 || x== 60) {
				std::cout << "   ";
			}
		}
		std::cout << endl;
		if(y == 41 || y== 61) {
			std::cout << endl;
			std::cout << endl;
		}
	} */

	/*
	//Para la tarea lo de poblaciones
	//Cambiar board size x y y a 17 en caso de uso
	float rewardGrid[BOARD_SIZE_X][BOARD_SIZE_Y];

	for(int x = 1; x< BOARD_SIZE_X-1; x++) {
		for (int y = 1; y < BOARD_SIZE_Y-1; y++) {
			if(x == y) {
				rewardGrid[x][y] = -0.2f; 
			} else if (x >= 10 && y >= 10) {
				rewardGrid[x][y] = -0.1f;
			} else if (x > y) {
				rewardGrid[x][y] = -0.4f; 
			} else if (y > x) {
				rewardGrid[x][y] = -0.3f;
			}
		}
	}

	rewardGrid[10][10] = 10.0f;

	rewardGrid[1][1] = -20.0f;
	rewardGrid[1][15] = -5.0f;
	rewardGrid[15][1] = -8.0f;
	rewardGrid[15][15] = -10.0f;

	std::cout << "<---------------INIT REWARD GRID---------------->" << endl;
	for (int y = BOARD_SIZE_Y -2; y > 0; y--) {
		for (int x = 1; x < BOARD_SIZE_X -1; x++) {
			std::cout << rewardGrid[x][y] << " ";
		}
		std::cout << endl; 
	}

	MDP * mdp = new MDP(rewardGrid,0.8);
	mdp->doMDP();

	std::cout << "<--------------------FINAL OPTIMAL RULES---------------->" << endl;
	for (int y = BOARD_SIZE_Y-2; y > 0; y--) {
		for (int x = 1; x < BOARD_SIZE_X-1; x++) {
			std::cout << mdp->optimalRules[x][y] << " ";
		}
		std::cout << endl; 
	}
	*/

	

	/*
	//EJEMPLO DE TAREA EN CLASE

	float rewardGrid[BOARD_SIZE_X][BOARD_SIZE_Y];

	for(int x = 1; x< BOARD_SIZE_X-1; x++) {
		for (int y = 1; y < BOARD_SIZE_Y-1; y++) {
			rewardGrid[x][y] = -0.04f;
		}
	}

	rewardGrid[3][1] = -10.0f;
	rewardGrid[3][3] = -10.0f;
	rewardGrid[3][5] = -10.0f;
	rewardGrid[3][7] = -10.0f;
	rewardGrid[3][9] = -10.0f;
	rewardGrid[6][2] = -10.0f;
	rewardGrid[6][4] = -10.0f;
	rewardGrid[6][6] = -10.0f;
	rewardGrid[6][8] = -10.0f;
	rewardGrid[6][10] = -10.0f;
	rewardGrid[6][6] = -10.0f;
	rewardGrid[10][1] = 10.0f;
	rewardGrid[10][5] = -10.0f;
	rewardGrid[10][7] = -10.0f;
	rewardGrid[10][9] = -10.0f;
	rewardGrid[15][10] = 20.0f;

	std::cout << "<---------------INIT REWARD GRID---------------->" << endl;
	for (int y = BOARD_SIZE_Y -2; y > 0; y--) {
		for (int x = 1; x < BOARD_SIZE_X -1; x++) {
			std::cout << rewardGrid[x][y] << " ";
		}
		std::cout << endl; 
	}

	MDP * mdp = new MDP(rewardGrid,0.8);
	mdp->doMDP();

	std::cout << "<--------------------FINAL OPTIMAL RULES---------------->" << endl;
	for (int y = BOARD_SIZE_Y-2; y > 0; y--) {
		for (int x = 1; x < BOARD_SIZE_X-1; x++) {
			std::cout << mdp->optimalRules[x][y] << " ";
		}
		std::cout << endl; 
	}*/
	

}
















