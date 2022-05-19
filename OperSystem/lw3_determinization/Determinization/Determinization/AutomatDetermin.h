#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include "AutomatMinimization.h"
#include <algorithm>

class AutomatDetermin: public AutomatMinimization
{
public:
	std::vector<std::vector<std::string>> Determine(std::vector<std::vector<std::string>> matrica);
	std::vector<std::vector<std::string>> ReadTransitions(std::ifstream& inputF, std::string grammarType);
	void ShowGrammar(std::vector<std::vector<std::string>> matrica);
protected:
	std::vector<std::string> SearchingForStatesOnNullSumbols(std::vector<std::vector<std::string>> matrica, int strNumInMatrica, int index, std::string terminalSymbol, std::vector<std::string>& states);
	std::vector<std::vector<std::string>> JumpTableToMili(std::vector<std::vector<std::string>> matrica);
	int statesNumber = 0;
	int terminalStatesNumber = 0;
	int outSymbol = 0;
	const int STATES_START_POS = 4;
};

