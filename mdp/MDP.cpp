#include "MDP.h";
MDP::MDP(float rewards[][BOARD_SIZE_Y], float gammaValue){
	for(int x = 0; x<BOARD_SIZE_X; x++) {
		for (int y = 0; y < BOARD_SIZE_Y; y++) {
			optimalRules[x][y] = -1;
		}
	}

	for(int x = 1; x<BOARD_SIZE_X-1; x++) {
		for (int y = 1; y < BOARD_SIZE_Y-1; y++) {
			nextRules[x][y] = -2;
		}
	}

	for(int x = 0; x<BOARD_SIZE_X; x++) {
		for (int y = 0; y < BOARD_SIZE_Y; y++) {
			originalvalueGrid[x][y] = rewards[x][y];
			valueGrid[x][y] = rewards[x][y];
			nextValueGrid[x][y] = 0.0f;
		}
	}

	gamma = gammaValue;
}

MDP::~MDP(){}

bool MDP::didConverge(){
	for(int x = 0; x<BOARD_SIZE_X; x++) {
		for (int y = 0; y <BOARD_SIZE_Y; y++) {
			if(nextRules[x][y] != optimalRules[x][y]){
				return false;
			}
		}
	}
	return true;
}

void MDP::doMDP(){
	std::cout << "DO MDP!"<<endl;
	int move;
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
	do {
		std::cout << "ENTERED DO: "<< n <<endl;
		flag = false;
		for(int x = 1; x<BOARD_SIZE_X-1; x++) {
			for (int y = 1; y <BOARD_SIZE_Y-1; y++) {
				move = 0; //move that has to be updated to new grid
				for(int k = 0; k<9; k++) {

					for(l = 0; l<9; l++) {
						// change probability value
						if(l == k) {
							probability = 0.9f;
						} else {
							probability = 0.014f;
						}
						calculateValue += probability * valueGrid[x+inX[l]][y+inY[l]];
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
				currentMax = -std::numeric_limits<float>::max();
			}
		}

		//update values of grid
		for(int x = 1; x< BOARD_SIZE_X-1; x++) {
			for (int y = 1; y < BOARD_SIZE_Y-1; y++) {
				valueGrid[x][y] = nextValueGrid[x][y];
				if (optimalRules[x][y] != nextRules[x][y]) {
					flag = true;
				}
				optimalRules[x][y] = nextRules[x][y];
			}
		}
		n++;

		std::cout << "<---------------Internal print value---------------->" << endl;
		for (int y = BOARD_SIZE_Y -1; y > 0; y--) {
			for (int x = 1; x < BOARD_SIZE_X -1; x++) {
				std::cout.precision(2);
				std::cout << valueGrid[x][y] << " ";
			}
			std::cout << endl; 
		}
	} //while(n < 5);
	while(flag);
}

// just for code test
int main() {
	/*float rewardGrid[BOARD_SIZE][BOARD_SIZE];
	int equilibrium = 80;
	for(int i = 1; i< REAL_BOARD_SIZE; i++) {
		for(int j = 1; j< REAL_BOARD_SIZE; j++) {
			if(i == j) {
				rewardGrid[i][j] = -2.0f;
			} else if(j >= equilibrium && i >= equilibrium) {
				rewardGrid[i][j] = -1.0f;
			} else if (j >= i) {
				rewardGrid[i][j] = -4.0f;
			} else if (i > j) {
				rewardGrid[i][j] = -3.0f;
			}
		}
	}
	rewardGrid[equilibrium][equilibrium] = 100;
	rewardGrid[equilibrium+1][equilibrium] = 100;
	rewardGrid[equilibrium][equilibrium+1] = 100;
	rewardGrid[equilibrium+1][equilibrium+1] = 100;
	rewardGrid[equilibrium-1][equilibrium] = 100;
	rewardGrid[equilibrium][equilibrium-1] = 100;
	rewardGrid[equilibrium-1][equilibrium-1] = 100;


	rewardGrid[1][1] = -200;
	rewardGrid[1][2] = -200;
	rewardGrid[2][1] = -200;
	rewardGrid[2][2] = -200;
	
	rewardGrid[100][1] = -50;
	rewardGrid[100][2] = -50;
	rewardGrid[99][2] = -50;
	rewardGrid[99][1] = -50;

	rewardGrid[1][100] = -80;
	rewardGrid[1][99] = -80;
	rewardGrid[2][100] = -80;
	rewardGrid[2][99] = -80;

	rewardGrid[100][100] = -100;
	rewardGrid[99][100] = -100;
	rewardGrid[100][99] = -100;
	rewardGrid[99][99] = -100;

	for (int y = BOARD_SIZE; y >= 0; y--) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			std::cout << rewardGrid[x][y] << " ";
		}
		std::cout << endl; 
	}*/

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
	for (int y = BOARD_SIZE_Y -1; y > 0; y--) {
		for (int x = 1; x < BOARD_SIZE_X -1; x++) {
			std::cout << rewardGrid[x][y] << " ";
		}
		std::cout << endl; 
	}

	MDP * mdp = new MDP(rewardGrid,0.8);
	mdp->doMDP();

	std::cout << "<--------------------FINAL OPTIMAL RULES---------------->" << endl;
	for (int y = BOARD_SIZE_Y-1; y > 0; y--) {
		for (int x = 1; x < BOARD_SIZE_X-1; x++) {
			std::cout << mdp->optimalRules[x][y] << " ";
		}
		std::cout << endl; 
	}

	//for (int y = BOARD_SIZE; y >= 0; y--) {
	//	for (int x = 0; x < BOARD_SIZE; x++) {
	//		std::cout << mdp->optimalRules[x][y] << " ";
	//	}
	//	std::cout << endl; 
	//}

}



















