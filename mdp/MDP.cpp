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
	int n = 0;
	int l;
	float probability = 0.0f;
	float calculateValue = 0.0f;
	float currentMax = -std::numeric_limits<float>::max();
	int inX[9] = {0,1,1,0,-1,-1,-1,0,1};
	int inY[9] = {0,0,-1,-1,-1,0,1,1,1};
	do {
		std::cout << "ENTERED DO: "<< n <<endl;
		for(int i = 1; i<REAL_BOARD_SIZE; i++) {
			for (int j = 1; j <REAL_BOARD_SIZE; j++) {
				move = 0; //move that has to be updated to new grid
				for(int k = 1; k<9; k++) {

					for(l = 1; l<9; l++) {
						// change probability value
						if(l == k) {
							probability = 0.9f;
						} else {
							probability = 0.014f;
						}
						calculateValue += probability * valueGrid[i+inX[l]][j+inY[l]];
					}

					if(calculateValue > currentMax) {
						//std::cout << "change value ENTERED" << endl;
						currentMax = calculateValue;
						move = k;
					}
					calculateValue = 0.0f;
					
				}
				nextValueGrid[i][j] = originalvalueGrid[i][j]+currentMax*gamma;
				nextRules[i][j] = move;
				//std::cout << "for i: "<< i <<" j: "<< j<< " new value: "<<nextValueGrid[i][j] << " new move: "<< nextRules[i][j] << endl; 
				calculateValue = 0.0f;
				currentMax = -std::numeric_limits<float>::max();
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

	//for (int i = 1; i < BOARD_SIZE-1; i++) { 
	//   for (int j = 1; j < BOARD_SIZE-1; j++) { 
	//      std::cout << rewardGrid[i][j] << " "; 
	//   } 
	//     
	//   std::cout << endl; 
	//}
	//std::cout << endl;
	//std::cout << endl;
	//std::cout << endl;
	//std::cout << endl;
	//std::cout << endl;

	MDP * mdp = new MDP(rewardGrid,0.8);
	mdp->doMDP();

	for (int i = 1; i < BOARD_SIZE-1; i++) { 
	   for (int j = 1; j < BOARD_SIZE-1; j++) { 
	      std::cout << mdp->nextRules[i][j] << " "; 
	   } 
	   std::cout << endl; 
	}
}



















