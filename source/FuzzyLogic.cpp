#include "FuzzyLogic.h"
array<float, 5> fuzzyfyData(float td) {
	array<float, 5> TDMembershipArr;
	for (int i = 0; i < 5; ++i) {
		TDMembershipArr[i] = 0.0f;
	}

	//L
	if(td <= 0.0f) {
		TDMembershipArr[0] = 0.0f;
	} else if(0.0f <= td && td < 1.0f) {
		TDMembershipArr[0] = 1.0f-td;
	} else {
		TDMembershipArr[0] = 0.0f;

	}

	//LM
	if(td < 0.0f) {
		TDMembershipArr[1] = 0.0f;
	} else if(0.0f <= td &&  td < 1.0) {
		TDMembershipArr[1] = td;
	} else if(1.0f <= td &&  td < 2.0) {
		TDMembershipArr[1] = 2.0 - td;
	} else {
		TDMembershipArr[1] = 0.0f;
	}

	//M
	if(td < 1.0f) {
		TDMembershipArr[2] = 0.0f;
	} else if(1.0f <= td &&  td < 2.0) {
		TDMembershipArr[2] = td - 1.0f;
	}else if(2.0f <= td &&  td < 3.0) {
		TDMembershipArr[2] = 3.0 - td;
	} else {
		TDMembershipArr[2] = 0.0f;
	}

	//MH
	if(td < 2.0f) {
		TDMembershipArr[3] = 0.0f;
	} else if(2.0f <= td &&  td < 3.0) {
		TDMembershipArr[3] = td - 2.0f;
	}else if(3.0f <= td && td < 4.0) {
		TDMembershipArr[3] = 3.0 - td;
	} else {
		TDMembershipArr[3] = 0.0f;
	}

	//H
	if(td < 3.0f) {
		TDMembershipArr[4] = 0.0f;
	} else if(3.0f <= td && td <= 4.0f) {
		TDMembershipArr[4] = td - 3.0f;
	} else {
		TDMembershipArr[4] = 0.0f;
	}


	return TDMembershipArr;
}

array<float, 5> fuzzyfyRules(array<float, 5> tda, array<float, 5> tdna) {
	array<float, 5> EXTMembershipArr;
	for (int i = 0; i < 5; ++i) {
		EXTMembershipArr[i] = 0.0f;
	}

	//RM
	EXTMembershipArr[0] += tda[0] * tdna[4];
	EXTMembershipArr[0] += tda[0] * (tdna[2]+tdna[3]);
	EXTMembershipArr[0] += tda[1] * (tdna[4]);

	//RL
	EXTMembershipArr[1] += tda[0] * (tdna[0]+tdna[1]);
	EXTMembershipArr[1] += tda[1] * (tdna[2]+tdna[3]);
	EXTMembershipArr[1] += tda[2] * (tdna[3]+tdna[4]);

	//Z
	EXTMembershipArr[2] += tda[1] * (tdna[0]+tdna[1]);
	EXTMembershipArr[2] += tda[2] * (tdna[2]);
	EXTMembershipArr[2] += tda[3] * (tdna[4]);

	//L
	EXTMembershipArr[3] += tda[2] * (tdna[0]+tdna[1]);
	EXTMembershipArr[3] += tda[3] * (tdna[2]+tdna[3]);
	EXTMembershipArr[3] += tda[4] * (tdna[4]);
	EXTMembershipArr[3] += tda[4] * (tdna[2]+tdna[3]);

	//M
	EXTMembershipArr[4] += tda[3] * (tdna[0]+tdna[1]);
	EXTMembershipArr[4] += tda[4] * (tdna[0]+tdna[1]);

	return EXTMembershipArr;
}

float defuzzyfy(array<float, 5> ext) {
	float res = 0.0f;
	res += ext[0] * EXT_RM;
	res += ext[1] * EXT_RL;
	res += ext[2] * EXT_Z;
	res += ext[3] * EXT_L;
	res += ext[4] * EXT_M;
	return res;
}

float fuzzyfy(float tda, float tdna) {
	array<float, 5> TDAMembershipArr = fuzzyfyData(tda);
	array<float, 5> TDNAMembershipArr = fuzzyfyData(tdna);
	array<float, 5> EXTMembershipArr = fuzzyfyRules(TDAMembershipArr,TDNAMembershipArr);
	float result = defuzzyfy(EXTMembershipArr);
    printf("FUZZY SYS ARRS: \n TDA[LA: %g, LMA: %g, MA: %g, MHA: %g, HA:%g] \n",TDAMembershipArr[0],TDAMembershipArr[1],TDAMembershipArr[2],TDAMembershipArr[3],TDAMembershipArr[4]);
    printf("TDNA[LN: %g, LMN: %g, MN: %g, MHN: %g, HN:%g] \n",TDNAMembershipArr[0],TDNAMembershipArr[1],TDNAMembershipArr[2],TDNAMembershipArr[3],TDNAMembershipArr[4]);
    printf("EXT[RM: %g, RL: %g, Z: %g, L: %g, M:%g] \n", EXTMembershipArr[0],EXTMembershipArr[1],EXTMembershipArr[2],EXTMembershipArr[3],EXTMembershipArr[4]);
    printf("Extension of: %g \n", result);
    return result;
}

