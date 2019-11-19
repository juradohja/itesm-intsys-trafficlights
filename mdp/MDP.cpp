#include "MDP.h";
MDP::MDP(float rewards[][BOARD_SIZE], float gammaValue){
	for(int i = 0; i<BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			optimalRules[i][j] = 0;
		}
	}

	for(int i = 1; i<REAL_BOARD_SIZE; i++) {
		for (int j = 1; j < REAL_BOARD_SIZE; j++) {
			nextRules[i][j] = -1;
		}
	}

	for(int i = 0; i<BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			originalvalueGrid[i][j] = rewards[i][j];
			valueGrid[i][j] = rewards[i][j];
			nextValueGrid[i][j] = 0.0f;
		}
	}

	gamma = gammaValue;
}

MDP::~MDP(){}

bool MDP::didConverge(){
	for(int i = 0; i<BOARD_SIZE; i++) {
		for (int j = 0; j <BOARD_SIZE; j++) {
			if(nextRules[i][j] != optimalRules[i][j]){
				return false;
			}
		}
	}
	return true;
}

void MDP::doMDP(){
	std::cout << "DO MDP!"<<endl;
	int move;
	int l;
	int n = 0;
	float probability = 0.0f;
	float calculateValue = 0.0f;
	float currentMax = std::numeric_limits<float>::min();
	do {
		std::cout << "ENTERED DO: "<< n <<endl;
		for(int i = 1; i<REAL_BOARD_SIZE; i++) {
			for (int j = 1; j <REAL_BOARD_SIZE; j++) {
				l = 0; //just a counter to change the probabilities
				move = 0; //move that has to be updated to new grid
				for(int k = 1; k<9; k++) {
					// change probability value
					if(l == k) {
						probability = 0.9f;
					} else {
						probability = 0.014f;
					}

					//check right
					calculateValue += probability * valueGrid[i+1][j];
					//check down right
					calculateValue += probability * valueGrid[i+1][j-1];
					//check down
					calculateValue += probability * valueGrid[i][j-1];
					//check left down
					calculateValue += probability * valueGrid[i-1][j-1];
					//check left
					calculateValue += probability * valueGrid[i-1][j];
					//check up left
					calculateValue += probability * valueGrid[i-1][j+1];
					//check up
					calculateValue += probability * valueGrid[i][j+1];
					//check up right
					calculateValue += probability * valueGrid[i+1][j+1];

					if(calculateValue > currentMax) {
						currentMax = calculateValue;
						move = l;
					}
					l++;
				}
				nextValueGrid[i][j] = originalvalueGrid[i][j]+currentMax*gamma;
				nextRules[i][j] = move;

				calculateValue = 0.0f;
				currentMax = std::numeric_limits<float>::min();
			}
		}

		//update values of grid
		for(int i = 1; i< BOARD_SIZE; i++) {
			for (int j = 1; j < BOARD_SIZE; j++) {
				valueGrid[i][j] = nextValueGrid[i][j];
				optimalRules[i][j] = nextRules[i][j];
			}
		}

		//n++;
		//for (int i = 1; i < BOARD_SIZE-1; i++) { 
		//   for (int j = 1; j < BOARD_SIZE-1; j++) { 
		//      std::cout << optimalRules[i][j] << " "; 
		//   } 
		//     
		//   std::cout << endl; 
		//}
		//std::cout << endl;
		//std::cout << endl; 
		//std::cout << endl;
		//for (int i = 1; i < BOARD_SIZE-1; i++) { 
		//   for (int j = 1; j < BOARD_SIZE-1; j++) { 
		//      std::cout << valueGrid[i][j] << " "; 
		//   } 
		//     
		//   std::cout << endl; 
		//}


	} //while(n < 5);
	while(!didConverge());
}

// just for code test
int main() {
	float rewardGrid[BOARD_SIZE][BOARD_SIZE];
	int equilibrium = 80;
	for(int i = 1; i< REAL_BOARD_SIZE; i++) {
		for(int j = 1; j<REAL_BOARD_SIZE; j++) {
			if(i = j) {
				rewardGrid[i][j] = -0.2f;
			} else if(j > equilibrium && i > equilibrium) {
				rewardGrid[i][j] = -0.1f;
			} else if (j > i) {
				rewardGrid[i][j] = -0.4f;
			} else if (i > j) {
				rewardGrid[i][j] = -0.3f;
			}
		}
	}
	rewardGrid[equilibrium][equilibrium] = 10;
	rewardGrid[1][1] = -20;
	rewardGrid[100][1] = -5;
	rewardGrid[1][100] = -8;
	rewardGrid[100][100] = -10;

	MDP * mdp = new MDP(rewardGrid,0.8);
	std::cout << "HW!"<<endl;
	mdp->doMDP();
	std::cout << "HW 2 !!"<<endl;
	//std::cout << "Hello World!"<<endl;

	for (int i = 1; i < BOARD_SIZE-1; i++) { 
	   for (int j = 1; j < BOARD_SIZE-1; j++) { 
	      std::cout << mdp->nextRules[i][j] << " "; 
	   } 
	     
	   std::cout << endl; 
	}
}



















