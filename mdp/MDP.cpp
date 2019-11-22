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
	do {
		//std::cout << "ENTERED DO: "<< n <<endl;
		flag = false;
		for(int x = 1; x<BOARD_SIZE_X-1; x++) {
			for (int y = 1; y <BOARD_SIZE_Y-1; y++) {
				for(int k = 0; k<9; k++) {

					for(l = 0; l<9; l++) {
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
				}
				optimalRules[x][y] = nextRules[x][y];
			}
		}
		n++;

		//std::cout << "<---------------Internal print value---------------->" << endl;
		//for (int y = BOARD_SIZE_Y-2; y > 0; y--) {
		//	for (int x = 1; x < BOARD_SIZE_X-1; x++) {
		//		//std::cout.precision(2);
		//		std::cout << nextRules[x][y] << " ";
		//	}
		//	std::cout << endl; 
		//}
	} //while(n < 5);
	while(flag || !didConverge());
}

// just for code test
/*
int main() {

	//Para la tarea lo de poblaciones
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
	//rewardGrid[9][10] = 10.0f;
	//rewardGrid[10][9] = 10.0f;
	//rewardGrid[9][9] = 10.0f;
	//rewardGrid[11][11] = 10.0f;
	//rewardGrid[11][10] = 10.0f;
	//rewardGrid[10][11] = 10.0f;
	//rewardGrid[11][9] = 10.0f;
	//rewardGrid[9][11] = 10.0f;


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
	}

	//for (int y = BOARD_SIZE; y >= 0; y--) {
	//	for (int x = 0; x < BOARD_SIZE; x++) {
	//		std::cout << mdp->optimalRules[x][y] << " ";
	//	}
	//	std::cout << endl; 
	//}

	

}

*/

















