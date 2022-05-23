#include "AutomatDetermin.h"

void WriteThis() {
	std::cout << "This";
}

bool  VectorComparison(std::vector<std::string> v1, std::vector<std::string>v2) {
	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());
	return v1 == v2;
}

std::vector<std::string> AutomatDetermin::FindTerminalSumbolsInMatrica(std::vector<std::vector<std::string>> matrica) {
	std::vector<std::string> terminalSumbols;
	for (std::vector<std::vector<std::string>>::iterator it1 = matrica.begin(); it1 != matrica.end(); ++it1) {
		for (int i = TERMINAL_SYMBOL_FIRT_POS; i < it1[0].size(); i = i + 2) {
			if (find(terminalSumbols.begin(), terminalSumbols.end(), it1[0][i]) == terminalSumbols.end()) {
				terminalSumbols.push_back(it1[0][i]);
			}
		}
	}
	return terminalSumbols;
}

std::string AutomatDetermin::FindNewTerminalSymbol(std::vector<std::vector<std::string>> matrica, int strNum, std::vector<std::string>& terminalSumbols) {
	std::string terminalSymbol = "";
	int index = TERMINAL_SYMBOL_FIRT_POS;
	while (index < matrica[strNum].size()) {
		if (find(terminalSumbols.begin(), terminalSumbols.end(), matrica[strNum][index]) == terminalSumbols.end()) {
			terminalSumbols.push_back(matrica[strNum][index]);
			terminalSymbol = matrica[strNum][index];
		}
		index += 2;
	}
	return terminalSymbol;
}

std::vector<std::string> AutomatDetermin::GetTerminalSymbols(std::vector<std::vector<std::string>> matrica, std::vector<std::vector<std::string>>::iterator elemMatr) {
	std::vector<std::string> terminalSymbols;
	std::vector<std::string> elem = elemMatr[0];
	std::vector<std::string>::iterator it = elem.begin();
	for (int i = 0; i < FIRST_POSITION_OF_OLD_STATES; i++) {
		it++;
	}
	for (it; it != elem.end(); ++it) {
		terminalSymbols.push_back(it[0]);
	}
	return terminalSymbols;
}

std::vector<std::vector<std::string>> AutomatDetermin::JumpTableToMili(std::vector<std::vector<std::string>> matrica) {
	std::vector<std::vector<std::string>> endMatrica;
	int posNow = 0;
	int findPosNum = 0;
	for (std::vector<std::vector<std::string>>::iterator it = ++matrica.begin(); it != matrica.end(); ++it) {
		if (FindPosInMatrica(endMatrica, it[0][1], 0) == -1) {
			endMatrica.push_back({ it[0][1] });
			endMatrica[posNow].push_back(it[0][0]);
			endMatrica[posNow].push_back(it[0][TERMINAL_SYMBOL_FIRT_POS]);
			posNow++;
		}
		else {
			findPosNum = FindPosInMatrica(endMatrica, it[0][1], 0);
			endMatrica[findPosNum].push_back(it[0][0]);
			endMatrica[findPosNum].push_back(it[0][TERMINAL_SYMBOL_FIRT_POS]);
		}
	}
	return endMatrica;
}

std::vector<std::string> AutomatDetermin::SearchingForStatesOnNullSumbols(std::vector<std::vector<std::string>> matrica, int strNumInMatrica, int index, std::string terminalSymbol, std::vector<std::string>& states) {
	int pos = 0;
	if (matrica[strNumInMatrica][index] == "e") {
		int terminalSumbolPos = TERMINAL_SYMBOL_FIRT_POS;
		states.push_back(matrica[strNumInMatrica][index - 1]);
		pos = FindPosInMatrica(matrica, matrica[strNumInMatrica][index - 1], 0);
		//std::vector<std::string>::iterator it = matrica[pos].begin(); it != matrica[pos].end(); ++it
		if (pos != -1) {
			while (terminalSumbolPos < matrica[pos].size()) {
				if (matrica[pos][terminalSumbolPos] == "e" && find(states.begin(), states.end(), matrica[pos][terminalSumbolPos - 1]) == states.end()) {
					states.push_back(matrica[pos][terminalSumbolPos - 1]);
					SearchingForStatesOnNullSumbols(matrica, pos, terminalSumbolPos, terminalSymbol, states);
				}
				else if (matrica[pos][terminalSumbolPos] == terminalSymbol && find(states.begin(), states.end(), matrica[pos][terminalSumbolPos - 1]) == states.end()) {
					states.push_back(matrica[pos][terminalSumbolPos - 1]);
				}
				terminalSumbolPos += 2;
			}
		}
	}
	return states;
}

std::vector<std::vector<std::string>> AutomatDetermin::Determine(std::vector<std::vector<std::string>> matrica) {
	int index = 1;
	int strNumInMatrica = 0;
	int iteration = 1;
	int classNum = 1;
	int iterationNow = 1;
	const int STATES_START_POS = 4;
	std::vector<std::vector<std::string>> determineMatrica;
	std::vector<std::string> terminalSumbols;
	std::vector<std::string> allTerminalSumbols;
	std::vector<std::string> terminalSumbolsOnNullSumbol;
	std::string classForSearch = matrica[0][0]; //
	std::string terminalSymbolsStr = "";
	std::string terminalSymbol = "";


	determineMatrica.push_back({ matrica[0][0], "s0", "e ", "f", matrica[0][0] });

	allTerminalSumbols = FindTerminalSumbolsInMatrica(matrica);

	for (iteration; iteration <= determineMatrica.size(); iteration++) {

		if (determineMatrica[iteration - 1][POSITION_OF_DESIGNATION_OF_REPEATS] == "r") {
			continue;
		}
		//iteration++;
		//iterationNow = iteration;
		std::vector<std::vector<std::string>>::iterator itI = determineMatrica.begin();
		for (int i = 1; i < iteration; i++) {
			itI++;
		}
		std::vector<std::string> elem = *itI;
		std::vector<std::string>::iterator it = elem.begin();
		for (int i = 0; i < FIRST_POSITION_OF_OLD_STATES; i++) {
			it++;
		}

		terminalSumbols.clear();
		for (it; it != elem.end(); ++it) { //поиск всех состояний
			strNumInMatrica = FindPosInMatrica(matrica, it[0], 0);
			if (strNumInMatrica != -1) {
				FindNewTerminalSymbol(matrica, strNumInMatrica, terminalSumbols);
			}
		}

		if (find(terminalSumbols.begin(), terminalSumbols.end(), "e") != terminalSumbols.end()) {
			terminalSumbols = allTerminalSumbols;
		}

		for (std::vector<std::string>::iterator terminalSIter = terminalSumbols.begin(); terminalSIter != terminalSumbols.end(); ++terminalSIter) {
			terminalSymbol = terminalSIter[0];
			if (terminalSymbol == "e") {
				continue;
			}
			it = elem.begin();
			for (int i = 0; i < FIRST_POSITION_OF_OLD_STATES; i++) {
				it++;
			}
			//std::cout << ":" << classNum << ": ";
			
			bool flag = true;

			for (it; it != elem.end(); ++it) {
				bool flag = true;
				index = 2;
				strNumInMatrica = FindPosInMatrica(matrica, it[0], 0);
				if (strNumInMatrica != -1) {
					if (flag) {
						determineMatrica.push_back({ "s" + std::to_string(classNum + 1) });
						determineMatrica[iterationNow].push_back({ elem[0] });
						determineMatrica[iterationNow].push_back({ terminalSymbol });
						determineMatrica[iterationNow].push_back({ "f" });
						flag = false;
					}
					while (index < matrica[strNumInMatrica].size()) {
						std::vector<std::string>::iterator it1 = determineMatrica[iterationNow].begin();
						for (int i = 0; i < FIRST_POSITION_OF_OLD_STATES; i++) {
							it1++;
						}
						if (matrica[strNumInMatrica][index] == "e") {
							terminalSumbolsOnNullSumbol.clear();
							terminalSumbolsOnNullSumbol = SearchingForStatesOnNullSumbols(matrica, strNumInMatrica, index, terminalSymbol, terminalSumbolsOnNullSumbol);
							for (std::vector<std::string>::iterator th = terminalSumbolsOnNullSumbol.begin(); th != terminalSumbolsOnNullSumbol.end(); ++th) {
								std::vector<std::string>::iterator it2 = determineMatrica[iterationNow].begin();
								for (int i = 0; i < FIRST_POSITION_OF_OLD_STATES; i++) {
									it2++;
								}
								if (find(it2, determineMatrica[iterationNow].end(), th[0]) == determineMatrica[iterationNow].end()) {
									determineMatrica[iterationNow].push_back(th[0]);
									//ShowTransposition(determineMatrica);
								}
							}
						}
						else if (matrica[strNumInMatrica][index] == terminalSymbol && find(it1, determineMatrica[iterationNow].end(), matrica[strNumInMatrica][index - 1]) == determineMatrica[iterationNow].end()) {
							determineMatrica[iterationNow].push_back(matrica[strNumInMatrica][index - 1]);
						}
						index += 2;
					}
				}
			}

			std::vector<std::vector<std::string>>::iterator itF = determineMatrica.begin(); //проверяем повторы
			for (int i = 0; i < iterationNow; i++) {
				itF++;
			}
			std::vector<std::string> terminalSymbolsVec = GetTerminalSymbols(determineMatrica, itF); //проверяем повторы
			//WriteThis();
			int terminalSymbolsNumber = 0;
			for (std::vector<std::vector<std::string>>::iterator it1 = determineMatrica.begin(); it1 != determineMatrica.end(); ++it1) {
				if (it1[0][POSITION_OF_DESIGNATION_OF_REPEATS] != "r" && VectorComparison(terminalSymbolsVec, GetTerminalSymbols(determineMatrica, it1))) {
					itF[0][0] = it1[0][0];
					terminalSymbolsNumber++;
					if (terminalSymbolsNumber > 1) {
						classNum--;
						it1[0][POSITION_OF_DESIGNATION_OF_REPEATS] = "r";
					}
				}
			}
			iterationNow++;
			classNum++;
		}

		/*for (it; it != elem.end(); ++it) {
			strNumInMatrica = FindPosInMatrica(matrica, it[0], 0);
			terminalSymbol = FindNewTerminalSymbol(matrica, strNumInMatrica, terminalSumbols);
			std::cout << "\n" << terminalSymbol << "\n";
			if (terminalSymbol != "") {
				index = 2;
				determineMatrica.push_back({ "s" + std::to_string(iterationNow + 1) });
				determineMatrica[iterationNow].push_back({ terminalSymbol });
				determineMatrica[iterationNow].push_back({"f"});
				while (index < matrica[strNumInMatrica].size()) {
					if (matrica[strNumInMatrica][index] == terminalSymbol) {
						determineMatrica[iterationNow].push_back(matrica[strNumInMatrica][index - 1]);
					}
					index += 2;
				}

				std::vector<std::vector<std::string>>::iterator itF = determineMatrica.begin(); //проверяем повторы
				for (int i = 1; i < iterationNow; i++) {
					itF++;
				}
				terminalSymbolsStr = GetTerminalSymbols(determineMatrica, itF); //проверяем повторы
				//WriteThis();
				int terminalSymbolsNumber = 0;
				for (std::vector<std::vector<std::string>>::iterator it1 = determineMatrica.begin(); it1 != determineMatrica.end(); ++it1) {
					if (terminalSymbolsStr == GetTerminalSymbols(determineMatrica, it1)) {
						terminalSymbolsNumber++;
					}
					if (terminalSymbolsNumber > 1) {
						determineMatrica[iterationNow][2] =  "r";
					}
				}
				it--;
			}
			else {
				terminalSumbols.clear();
				iterationNow++;
			}

		}*/
		//ShowTransposition(determineMatrica);
	}
	//ShowTransposition(determineMatrica);
	return JumpTableToMili(determineMatrica);
	//return determineMatrica;
}