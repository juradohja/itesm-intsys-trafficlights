#include "MDP.h";
MDP::MDP(double rewards[][BOARD_SIZE_Y], double gammaValue){

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
	double probability = 0.0f;
	double calculateValue = 0.0f;
	double currentMax = -std::numeric_limits<double>::max();
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

					if(calculateValue >= currentMax) {
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
				currentMax = -std::numeric_limits<double>::max();
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

		//if (n%15 == 0) {
		//	std::cout << "ITERATION N:     " << n << "<---------------Internal print value---------------->" << endl;
		//	for (int y = BOARD_SIZE_Y-2; y > 0; y--) {
		//		for (int x = 1; x < BOARD_SIZE_X-1; x++) {
		//			//std::cout.precision(2);
		//			std::cout << optimalRules[x][y] << " ";
		//			if(x == 40 || x== 60) {
		//				std::cout << "   ";
		//			}
		//		}
		//		std::cout << endl;
		//		if(y == 41 || y== 61) {
		//			std::cout << endl;
		//			std::cout << endl;
		//		}
		//	}
		//}

		n++;
		
	} //while(n < 5);
	while(flag  && countConv < 5);
}


/*
// just for code test

int main() {

	/*	
	//OFITIAL FOR PROYECT
	double rewards[BOARD_SIZE_X][BOARD_SIZE_Y];

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
			} else if (x == 100) { //x == 100 for east and y == 1 for south
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

	MDP * mdp = new MDP(rewards,0.9f);
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
	 
	

}

*/











