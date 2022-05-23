#include "AutomatDetermin.h"

void WriteThis() {
	std::cout << "This";
}

bool CheckUpRegister(char ch) {
	if (ch >= 'A' && ch <= 'Я') {
		return true;
	}
	else if (ch >= 'A' && ch <= 'Z') {
		return true;
	}
	return false;
}

std::vector<std::vector<std::string>> FirsElemInEnd(std::vector<std::vector<std::string>> matrica) {
	std::vector<std::vector<std::string>> matricaEnd;
	std::vector<std::vector<std::string>>::iterator elemFirst = matrica.begin();
	for (std::vector<std::vector<std::string>>::iterator elem = ++matrica.begin(); elem != matrica.end(); ++elem) {
		matricaEnd.push_back(elem[0]);
	}
	matricaEnd.push_back(elemFirst[0]);
	return matricaEnd;
}

std::vector<std::vector<std::string>> DeleteFirsElem(std::vector<std::vector<std::string>> matrica) {
	std::vector<std::vector<std::string>> matricaEnd;
	for (std::vector<std::vector<std::string>>::iterator elem = ++matrica.begin(); elem != matrica.end(); ++elem) {
		matricaEnd.push_back(elem[0]);
	}
	return matricaEnd;
}

void SwapString(std::string& string1, std::string& string2) {
	std::string nullString;
	nullString = string1;
	string1 = string2;
	string2 = nullString;
}

std::vector<std::vector<std::string>> AutomatDetermin::ReadTransitions(std::ifstream& inputF, std::string grammarType) {
	std::vector<std::vector<std::string>> matrica;
	int skipNum = 2;
	int pos = 0;
	std::string line;
	std::string elem;
	std::string stateEnd;
	std::string stateNow;
	std::string nullString;
	std::string terminalSumbol;
	std::istringstream input{};
	if (grammarType == "L" || grammarType == "R") {
		bool GrammarIsLeft = true;
		if (grammarType == "R") {
			GrammarIsLeft = false;
		}

		matrica.push_back({ "H" });
		getline(inputF, line);
		while (line != "") {
			input = std::istringstream{ line };
			input >> elem;
			stateEnd = elem;
			input >> elem;
			while (!input.eof()) {
				stateNow = "";
				terminalSumbol = "";
				input >> elem;
				for (int i = 0; i < elem.size(); i++) {
					if (CheckUpRegister(elem[i])) {
						stateNow.push_back(elem[i]);
					}
					else {
						terminalSumbol.push_back(elem[i]);
					}
				}

				if (stateNow == "") {
					stateNow = "H";
				}

				if (!GrammarIsLeft) {
					SwapString(stateNow, stateEnd);
				}

				pos = FindPosInMatrica(matrica, stateNow, 0);
				if (pos == -1) {
					matrica.push_back({ stateNow,  stateEnd, terminalSumbol });
				}
				else {
					matrica[pos].push_back({ stateEnd });
					matrica[pos].push_back({ terminalSumbol });
				}
				if (!GrammarIsLeft) {
					SwapString(stateNow, stateEnd);
				}
				input >> elem;
			}
			getline(inputF, line);
		}
	}
	if (matrica[0].size() == 1) {
		matrica = FirsElemInEnd(matrica);
	}
	return matrica;
}

bool  VectorComparison(std::vector<std::string> v1, std::vector<std::string>v2) {
	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());
	return v1 == v2;
}

std::vector<std::string> FindTerminalSumbolsInMatrica(std::vector<std::vector<std::string>> matrica) {
	std::vector<std::string> terminalSumbols;
	for (std::vector<std::vector<std::string>>::iterator it1 = matrica.begin(); it1 != matrica.end(); ++it1) {
		for (int i = 2; i < it1[0].size(); i = i + 2) {
			if (find(terminalSumbols.begin(), terminalSumbols.end(), it1[0][i]) == terminalSumbols.end()) {
				terminalSumbols.push_back(it1[0][i]);
			}
		}
	}
	return terminalSumbols;
}

std::string FindNewTerminalSymbol(std::vector<std::vector<std::string>> matrica, int strNum, std::vector<std::string>& terminalSumbols) {
	std::string terminalSymbol = "";
	int index = 2;
	while (index < matrica[strNum].size()) {
		if (find(terminalSumbols.begin(), terminalSumbols.end(), matrica[strNum][index]) == terminalSumbols.end()) {
			terminalSumbols.push_back(matrica[strNum][index]);
			terminalSymbol = matrica[strNum][index];
		}
		index += 2;
	}
	return terminalSymbol;
}

std::vector<std::string> GetTerminalSymbols(std::vector<std::vector<std::string>> matrica, std::vector<std::vector<std::string>>::iterator elemMatr) {
	std::vector<std::string> terminalSymbols;
	std::vector<std::string> elem = elemMatr[0];
	std::vector<std::string>::iterator it = elem.begin();
	for (int i = 0; i < 4; i++) {
		it++;
	}
	for (it; it != elem.end(); ++it) {
		terminalSymbols.push_back(it[0]);
	}
	return terminalSymbols;
}

std::string VecStrToStr(std::vector<std::string> stateVec) {
	std::string stateStr = "(";
	stateStr += stateVec[0];
	for (std::vector<std::string>::iterator it2 = ++stateVec.begin(); it2 != stateVec.end(); ++it2) {
		stateStr += "," + it2[0];
	}
	stateStr += ")";
	return stateStr;
}

std::vector<std::string> TrimVectorFromThePosition(std::vector<std::string> vec, int STATES_START_POS) {
	std::vector<std::string> endVec;
	std::vector<std::string>::iterator it1 = vec.begin();
	for (int i = 0; i < STATES_START_POS; i++) {
		it1++;
	}
	for (it1; it1 != vec.end(); ++it1) {
		endVec.push_back(it1[0]);
	}
	return endVec;
}

std::vector<std::vector<std::string>> AutomatDetermin::JumpTableToMili(std::vector<std::vector<std::string>> matrica) {
	std::vector<std::vector<std::string>> endMatrica;
	std::vector<std::string> stateVec;
	std::string stateStrThis;
	std::string stateStrNext;
	std::string nullStr;
	int posNow = 0;
	int findPosNum = 0;
	for(std::vector<std::vector<std::string>>::iterator it = ++matrica.begin(); it != matrica.end(); ++it){
		stateVec.clear();
		stateStrThis = "";
		stateStrNext = "";
		std::vector<std::string> elem = *it;
		stateVec = TrimVectorFromThePosition(elem, STATES_START_POS);
		std::sort(stateVec.begin(), stateVec.end());
		stateStrNext = VecStrToStr(stateVec);

		stateVec = TrimVectorFromThePosition(matrica[FindPosInMatrica(matrica, it[0][1], 0)], STATES_START_POS);
		std::sort(stateVec.begin(), stateVec.end());
		stateStrThis = VecStrToStr(stateVec);

		if (FindPosInMatrica(endMatrica, stateStrThis, 0) == -1) {
			endMatrica.push_back({ stateStrThis });
			endMatrica[posNow].push_back(it[0][2] + stateStrNext);
			posNow++;
		}
		else {
			findPosNum = FindPosInMatrica(endMatrica, stateStrThis, 0);
			endMatrica[findPosNum].push_back( it[0][2] + stateStrNext);
		}
	}
	return endMatrica;
}

void AutomatDetermin::ShowGrammar(std::vector<std::vector<std::string>> matrica) {
	for (std::vector<std::vector<std::string>>::iterator it = matrica.begin(); it != matrica.end(); ++it) {
		std::vector<std::string> elem = *it;
		std::cout << elem[0] << " -> " << elem[1];
		for (std::vector<std::string>::iterator it1 = ++(++elem.begin()); it1 != elem.end(); ++it1) {
			std::cout << " | " << it1[0];
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

std::vector<std::string> AutomatDetermin::SearchingForStatesOnNullSumbols(std::vector<std::vector<std::string>> matrica,int strNumInMatrica, int index,std::string terminalSymbol, std::vector<std::string>& states) {
	int pos = 0;
	if (matrica[strNumInMatrica][index] == "e") {
		int terminalSumbolPos = 2;
		states.push_back(matrica[strNumInMatrica][index - 1]);
		pos = FindPosInMatrica(matrica, matrica[strNumInMatrica][index - 1], 0);
		//std::vector<std::string>::iterator it = matrica[pos].begin(); it != matrica[pos].end(); ++it
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
	return states;
}

std::vector<std::vector<std::string>> AutomatDetermin::Determine(std::vector<std::vector<std::string>> matrica) {
	int index = 1;
	int strNumInMatrica = 0;
	int iteration = 1;
	int classNum = 1;
	int iterationNow = 1;
	std::vector<std::vector<std::string>> determineMatrica;
	std::vector<std::string> terminalSumbols;
	std::vector<std::string> allTerminalSumbols;
	std::vector<std::string> terminalSumbolsOnNullSumbol;
	std::string classForSearch = matrica[0][0]; //
	std::string terminalSymbolsStr = "";
	std::string terminalSymbol = "";


	determineMatrica.push_back({ matrica[0][0], "s0", "e ", "f", matrica[0][0]});

	allTerminalSumbols = FindTerminalSumbolsInMatrica(matrica);

	for (iteration; iteration <= determineMatrica.size(); iteration++) {

		if (determineMatrica[iteration - 1][3] == "r") {
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
		for (int i = 0; i < STATES_START_POS; i++) {
			it++;
		}

		terminalSumbols.clear();
		for (it; it != elem.end(); ++it) { //поиск всех состояний
			strNumInMatrica = FindPosInMatrica(matrica, it[0], 0);
			FindNewTerminalSymbol(matrica, strNumInMatrica, terminalSumbols);
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
			for (int i = 0; i < STATES_START_POS; i++) {
				it++;
			}
			determineMatrica.push_back({ "s" + std::to_string(classNum + 1) });
			determineMatrica[iterationNow].push_back({ elem[0] });
			determineMatrica[iterationNow].push_back({ terminalSymbol });
			determineMatrica[iterationNow].push_back({ "f" });
			for (it; it != elem.end(); ++it) {
				index = 2;
				strNumInMatrica = FindPosInMatrica(matrica, it[0], 0);
				while (index < matrica[strNumInMatrica].size()) {
					std::vector<std::string>::iterator it1 = determineMatrica[iterationNow].begin();
					for (int i = 0; i < STATES_START_POS; i++) {
						it1++;
					}
					if (matrica[strNumInMatrica][index] == "e") {
						terminalSumbolsOnNullSumbol.clear();
						terminalSumbolsOnNullSumbol = SearchingForStatesOnNullSumbols(matrica, strNumInMatrica, index, terminalSymbol, terminalSumbolsOnNullSumbol);
						for (std::vector<std::string>::iterator th = terminalSumbolsOnNullSumbol.begin(); th != terminalSumbolsOnNullSumbol.end(); ++th) {
							std::vector<std::string>::iterator it2 = determineMatrica[iterationNow].begin();
							for (int i = 0; i < STATES_START_POS; i++) {
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
	return  JumpTableToMili(determineMatrica);
	//return determineMatrica;
}