#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

class AutomatMinimization
{
public:
	const std::string MILI = "Ml";
	const std::string MURA = "Mr";

	void ShowTransposition(std::vector<std::vector<std::string>> matrica);

	std::vector<std::vector<std::string>> ReadAutomatInFile(std::ifstream& inputF, int terminalStatesNumber, std::string automatType);

	std::vector<std::vector<std::string>> MuraInMili(std::vector<std::vector<std::string>> matrica, int terminalStatesNumber);

	void ReadAutomatOptionsInFile(std::ifstream& inputF);

	std::string EquivalenceClass(std::string key, std::vector<std::vector<std::string>>& classes, std::string earlyClass, int& classNumber);

	std::vector<std::vector<std::string>> FinalClasses(std::vector<std::vector<std::string>> matrica, int nowClassN, int terminalStatesNumber);

	std::vector<std::vector<std::string>> Minimization(std::vector<std::vector<std::string>> matrica, int terminalStatesNumber);

	std::vector<std::vector<std::string>> EditingForOutput(std::vector<std::vector<std::string>> initialMatrica, std::vector<std::vector<std::string>> matrica, int terminalStatesNumber);

	std::vector<std::vector<std::string>> AddClassesInMatrica(std::vector<std::vector<std::string>> matrica);

	int GetTerminalStatesNumber();

private:
	int FindPosInMatrica(std::vector<std::vector<std::string>> matrica, std::string className, int posInMatricaString);

	std::vector<std::vector<std::string>> SortMatrica(int indexElemForSort, int maxClassN, std::vector<std::vector<std::string>> matrica);

	int statesNumber = 0;
	int terminalStatesNumber = 0;
	int outSymbol = 0;
};

