#include "RegularExpressionC.h"

std::string RegularExpressionC::ReturnParenthesizedStringFromPosition(std::string& str, int pos) {
	std::string retStr = "";
	std::string thisStr = "";
	bool flag = false;
	int countScob = 0;
	while (pos != 0) {
		pos--;
		if (flag) {
			thisStr = str[pos] + thisStr;
		}
		else {
			if (str[pos] == '(') {
				if (countScob == 0) {
					flag = !flag;
				}
				else {
					countScob--;
					retStr = str[pos] + retStr;
				}
			}
			else if (str[pos] == ')') {
				countScob++;
				retStr = str[pos] + retStr;
			}
			else {
				retStr = str[pos] + retStr;
			}
		}
	}
	str = thisStr;
	return retStr;
}

std::string RegularExpressionC::NewStatesSeparatedByOr(std::vector<std::vector<std::string>>& regularExpression, int pos, std::vector<std::string>& newStates) {
	std::string newState;
	std::string symbol;
	const std::string nullString = "";
	bool f = true;
	if (regularExpression[pos][2][regularExpression[pos][2].size() - 1] == '|') {
		for (int i = regularExpression[pos][2].size() - 2; i != -1; i--) {
			if (regularExpression[pos][2][i] == '|') {
				newStates.push_back(newState);
				newState.clear();
			}
			else {
				newState += nullString + regularExpression[pos][2][i];
			}
		}
	}
	GetNewState(regularExpression, pos, symbol, f);
	return newState;
}

std::string RegularExpressionC::GetNewState(std::vector<std::vector<std::string>>& regularExpression, int pos, std::string& sumbol, bool& thereAreTransformations) {
	std::string newState;
	std::string endString = "";
	const std::string nullString = "";
	sumbol = "";
	thereAreTransformations = false;
	if (find(TERMINAL_SUMBOLS.begin(), TERMINAL_SUMBOLS.end(), regularExpression[pos][2][regularExpression[pos][2].size() - 1]) == TERMINAL_SUMBOLS.end()) {  //нет терминального символа
		if (regularExpression[pos][2][regularExpression[pos][2].size() - 1] == ')') {  //если строка в скобках
			newState = ReturnParenthesizedStringFromPosition(regularExpression[pos][2], regularExpression[pos][2].size() - 1);
			thereAreTransformations = true;
			if (regularExpression[pos][2].size() == 0) {
				regularExpression[pos][2] = newState;
				newState = "";
			}
			else {
				if (find(TERMINAL_SUMBOLS.begin(), TERMINAL_SUMBOLS.end(), regularExpression[pos][2][regularExpression[pos][2].size() - 1]) != TERMINAL_SUMBOLS.end()) { //если есть символ после скобок
					if (regularExpression[pos][2][regularExpression[pos][2].size() - 1] == '+') {
						sumbol = regularExpression[pos][2][regularExpression[pos][2].size() - 1];
						regularExpression[pos][2].erase(regularExpression[pos][2].size() - 1, 1);
						if (regularExpression[pos][2].size() > 1 && regularExpression[pos][2][regularExpression[pos][2].size() - 1] == '|') {
							sumbol = regularExpression[pos][2][regularExpression[pos][2].size() - 1];
							regularExpression[pos][2].erase(regularExpression[pos][2].size() - 1, 1);
							newState = "+(" + newState + ")";
						}
					}
					else if (regularExpression[pos][2][regularExpression[pos][2].size() - 1] == '|') {
						newState = newState;
						sumbol = regularExpression[pos][2][regularExpression[pos][2].size() - 1];
						regularExpression[pos][2].erase(regularExpression[pos][2].size() - 1, 1);
					}
				}
			}
		}
		else {
			if (regularExpression[pos][2].size() > 1) {
				thereAreTransformations = true;
				newState = nullString + regularExpression[pos][2][regularExpression[pos][2].size() - 1];
				regularExpression[pos][2].erase(regularExpression[pos][2].size() - 1, 1);
				if (find(TERMINAL_SUMBOLS.begin(), TERMINAL_SUMBOLS.end(), regularExpression[pos][2][regularExpression[pos][2].size() - 1]) != TERMINAL_SUMBOLS.end()) {
					if (regularExpression[pos][2][regularExpression[pos][2].size() - 1] == '+') {
						sumbol = regularExpression[pos][2][regularExpression[pos][2].size() - 1];
						regularExpression[pos][2].erase(regularExpression[pos][2].size() - 1, 1);
						if (regularExpression[pos][2].size() > 1 && regularExpression[pos][2][regularExpression[pos][2].size() - 1] == '|') {
							sumbol = regularExpression[pos][2][regularExpression[pos][2].size() - 1];
							newState = "+(" + newState + ")";
						}
					}
					else if (regularExpression[pos][2][regularExpression[pos][2].size() - 1] == '|') {
						sumbol = regularExpression[pos][2][regularExpression[pos][2].size() - 1];
						regularExpression[pos][2].erase(regularExpression[pos][2].size() - 1, 1);
					}
				}
			}
		}
	}
	else {  //найден терминальный символ
		thereAreTransformations = true;
		sumbol = regularExpression[pos][2][regularExpression[pos][2].size() - 1];
		regularExpression[pos][2].erase(regularExpression[pos][2].size() - 1, 1);
		if (regularExpression[pos][2][regularExpression[pos][2].size() - 1] == ')') {
			newState = ReturnParenthesizedStringFromPosition(regularExpression[pos][2], regularExpression[pos][2].size() - 1);
			if (regularExpression[pos][2].size() > 1 && regularExpression[pos][2][regularExpression[pos][2].size() - 1] == '|') {
				sumbol = regularExpression[pos][2][regularExpression[pos][2].size() - 1];
				regularExpression[pos][2].erase(regularExpression[pos][2].size() - 1, 1);
				newState = newState + "*";
			}
		}
		else {
			if (regularExpression[pos][2].size() > 1) {
				newState = nullString + regularExpression[pos][2][regularExpression[pos][2].size() - 1];
				regularExpression[pos][2].erase(regularExpression[pos][2].size() - 1, 1);
				if (regularExpression[pos][2].size() > 1 && regularExpression[pos][2][regularExpression[pos][2].size() - 1] == '|') {
					sumbol = regularExpression[pos][2][regularExpression[pos][2].size() - 1];
					regularExpression[pos][2].erase(regularExpression[pos][2].size() - 1, 1);
					newState = newState + "*";
				}
			}
		}
	}
	return newState;
}

int RegularExpressionC::NewStateInTable(std::vector<std::vector<std::string>>& regularExpression, int pos, int& nowStateNum, bool& thereAreTransformations) {
	std::vector<std::vector<std::string>> newMatrica;
	std::string newState;
	std::vector<std::string> newStates;
	std::string sumbol = "";
	std::string previousSumbol = "";
	int nowPos = pos;
	bool flag = true;
	for (int i = 0; i != pos + 1; i++) {
		newMatrica.push_back(regularExpression[i]);
	}
	newState = "";
	previousSumbol = sumbol;
	newState = GetNewState(newMatrica, pos, sumbol, thereAreTransformations);
	//std::cout << sumbol << ":" << newState;
	if (sumbol == "" && newState == "" && previousSumbol != "|") {
		flag = false;
	}

	if (sumbol == "" && newState != "" && previousSumbol != "|") {
		nowStateNum++;
		nowPos += 1;
		newMatrica.push_back({ std::to_string(nowStateNum), newMatrica[pos][1] , newState });
		newMatrica[pos][1] = std::to_string(nowStateNum);
	}
	else if (sumbol == "*" && newState != "" && previousSumbol != "|") {
		nowStateNum++;
		nowPos += 1;
		if (newMatrica[pos][2] == "") {
			newMatrica.push_back({ std::to_string(nowStateNum), std::to_string(nowStateNum) , newState });
			newMatrica.push_back({ std::to_string(nowStateNum), newMatrica[pos][1] , "e" });
			newMatrica[pos][2] = "e";
			newMatrica[pos][1] = std::to_string(nowStateNum);
		}
		else {
			newMatrica.push_back({ std::to_string(nowStateNum), std::to_string(++nowStateNum) , "e" });
			newMatrica.push_back({ std::to_string(nowStateNum), std::to_string(nowStateNum) , newState });
			newMatrica.push_back({ std::to_string(nowStateNum), newMatrica[pos][1] , "e" });
			newMatrica[pos][1] = std::to_string(nowStateNum - 1);
		}
	}
	else if (sumbol == "+" && newState != "" && previousSumbol != "|") {
		nowStateNum++;
		nowPos += 1;
		if (newMatrica[pos][2] == "") {
			newMatrica.push_back({ std::to_string(nowStateNum), std::to_string(nowStateNum) , newState });
			newMatrica.push_back({ std::to_string(nowStateNum), newMatrica[pos][1] , "e" });
			newMatrica[pos][1] = std::to_string(nowStateNum);
			newMatrica[pos][2] = newState;
		}
		else {
			newMatrica.push_back({ std::to_string(nowStateNum), std::to_string(++nowStateNum) , newState});
			newMatrica.push_back({ std::to_string(nowStateNum), std::to_string(nowStateNum) , newState });
			newMatrica.push_back({ std::to_string(nowStateNum), newMatrica[pos][1] , "e" });
			newMatrica[pos][1] = std::to_string(nowStateNum - 1);
		}
	}
	else if (sumbol == "|" && newState != "") {
		bool isLastState = false;
		++nowStateNum;
		while (!isLastState) {
			if (sumbol == "|" && newState != "") {
				newStates.push_back(newState);
			}
			else {
				isLastState = true;
				if (sumbol == "*") {
					newStates.push_back("(" + newState + ")*");
				}
				else if (sumbol == "+") {
					newStates.push_back("+(" + newState + ")");
				}
				else {
					newStates.push_back(newState);
				}
				for (std::vector<std::string>::iterator it = newStates.begin(); it != newStates.end(); ++it) {
					newMatrica.push_back({ std::to_string(nowStateNum), newMatrica[pos][1] , it[0] });
				}
				if (newMatrica[pos][2] == "") {
					newMatrica[pos][2] = "e";
				}
				newMatrica[pos][1] = std::to_string(nowStateNum);
			}
			newState = GetNewState(newMatrica, pos, sumbol, thereAreTransformations);
		}
	}
	for (int i = pos + 1; i < regularExpression.size(); i++) {
		newMatrica.push_back(regularExpression[i]);
	}
	regularExpression = newMatrica;
	return nowPos;
}

std::vector<std::vector<std::string>> RegularExpressionC::RegularExpressionInTransitionTable(std::vector<std::vector<std::string>> regularExpression) {
	const int expressionPos = 2;
	int nowStateNum = 2;
	int checkStateNum = nowStateNum;
	bool thereAreTransformations = true;
	bool flag = true;
	while (thereAreTransformations) {
		flag = true;
		for (int i = 0; i < regularExpression.size(); i++) {
			checkStateNum = nowStateNum;
			i = NewStateInTable(regularExpression, i, nowStateNum, thereAreTransformations);
			if (flag) {
				flag = !thereAreTransformations;
			}
		}
		if (!flag) {
			thereAreTransformations = true;
		}
	}
	return regularExpression;
}


std::vector<std::vector<std::string>> RemoveNullTransitions(std::vector<std::vector<std::string>> matrica) {
	std::vector<std::vector<std::string>> newMatrica;
	std::string stateLast = "";
	std::string stateNow = "";
	for (std::vector<std::vector<std::string>>::iterator it = matrica.begin(); it != matrica.end(); it++) {
		if (it[0][2] == "e") {
			stateLast = it[0][1];
			stateNow = it[0][0];
			for (std::vector<std::vector<std::string>>::iterator it1 = matrica.begin(); it1 != matrica.end(); it1++) {
				if (it1[0][0] == stateLast) {
					it1[0][0] = stateNow;
				}
				if (it1[0][1] == stateLast) {
					it1[0][1] = stateNow;
				}
			}
		}
	}
	for (std::vector<std::vector<std::string>>::iterator it = matrica.begin(); it != matrica.end(); it++) {
		if (it[0][2] != "e") {
			newMatrica.push_back(it[0]);
		}
	}
	return newMatrica;
}

std::vector<std::vector<std::string>> AddEndStates(std::vector<std::vector<std::string>> matrica) {
	std::vector<std::vector<std::string>> newMatrica;
	std::string state = "";
	bool isNullTransition = true;
	while (isNullTransition) {
		isNullTransition = false;
		for (int i = 0; i < matrica.size(); i++) {
			if (matrica[i][2] == "e") {
				isNullTransition = true;
				state = matrica[i][1];
				for (int j = 0; j < matrica.size(); j++) {
					if (state == matrica[j][0]) {
						newMatrica.push_back({ matrica[i][0], matrica[j][1],  matrica[j][2] });
					}
				}
			}
			else {
				newMatrica.push_back(matrica[i]);
			}
		}
		matrica = newMatrica;
		newMatrica.clear();
	}
	return matrica;
}

std::vector<std::vector<std::string>> RegularExpressionC::MergeTableFields(std::vector<std::vector<std::string>> matrica) { //nen jib,rf
	//matrica = RemoveNullTransitions(matrica);
	matrica = AddEndStates(matrica);
	//matrica.erase(--matrica.end());
	std::vector<std::vector<std::string>> newMatrica;
	std::vector<std::vector<std::string>> newMatricaCopy;
	bool flag = true;
	for (int i = 0; i < matrica.size(); i++) {
		newMatrica.push_back(matrica[i]);
		std::vector<std::vector<std::string>>::iterator it = matrica.begin();
		std::vector<std::vector<std::string>>::iterator it1 = matrica.begin();
		for (int j = 0; j != i + 1; j++) {
			it++;
		}
		for (it; it != matrica.end(); it++) {
			if (newMatrica[i][0] == it[0][0]) {
				newMatrica[i].push_back(it[0][1]);
				newMatrica[i].push_back(it[0][2]);
			}
		}
		flag = true;
		it = matrica.begin();
		for (it; it != matrica.end(); it++) {
			if (flag && newMatrica[i][0] == it[0][0]) {
				newMatricaCopy.push_back(it[0]);
				flag = false;
			}
			else if(newMatrica[i][0] != it[0][0]) {
				newMatricaCopy.push_back(it[0]);
			}
		}
		matrica = newMatricaCopy;
		newMatricaCopy.clear();
	}
	return newMatrica;
}