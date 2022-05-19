#include "AutomatMinimization.h"

void AutomatMinimization::ShowTransposition(std::vector<std::vector<std::string>> matrica) {
	int matricaSize = matrica.size();
	if (matricaSize == 0) { return; }
	int elemSize = matrica[0].size();
	for (int i = 0; i < elemSize; i++) {
		for (int j = 0; j < matricaSize; j++) {
			std::cout << matrica[j][i] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

std::vector<std::vector<std::string>> AutomatMinimization::ReadAutomatInFile(std::ifstream& inputF, int terminalStatesNumber, std::string automatType) {
	std::vector<std::vector<std::string>> matrica;
	std::string line1;
	std::string line2;
	std::string elem1;
	std::string elem2;
	std::istringstream input1{};
	std::istringstream input2{};

	if (automatType == MILI)
	{
		getline(inputF, line1);
		input1 = std::istringstream{ line1 };
		for (int j = 0; !input1.eof(); j++) {
			input1 >> elem1;
			matrica.push_back({ elem1 });
		}
		for (int k = 0; k < terminalStatesNumber; k++) {
			getline(inputF, line1);
			getline(inputF, line2);
			input1 = std::istringstream{ line1 };
			input2 = std::istringstream{ line2 };
			input1 >> elem1;
			for (int j = 0; !input1.eof() && !input2.eof(); j++) {
				input1 >> elem1;
				matrica[j].push_back(elem1);
				input2 >> elem1;
				matrica[j].push_back(elem1);
			}
		}
	}
	else if (automatType == MURA)
	{
		getline(inputF, line1);
		input1 = std::istringstream{ line1 };
		getline(inputF, line1);
		input2 = std::istringstream{ line1 };
		for (int j = 0; !input1.eof() && !input2.eof(); j++) {
			input1 >> elem1;
			matrica.push_back({ elem1 });
			input2 >> elem1;
			matrica[j].push_back(elem1);
		}
		for (int k = 0; k < terminalStatesNumber; k++) {
			getline(inputF, line1);
			input1 = std::istringstream{ line1 };
			input1 >> elem1;
			for (int j = 0; !input1.eof(); j++) {
				input1 >> elem1;
				matrica[j].push_back(elem1);
			}
		}
		matrica = MuraInMili(matrica, terminalStatesNumber);
	}
	return matrica;
}

int AutomatMinimization::FindPosInMatrica(std::vector<std::vector<std::string>> matrica, std::string name, int posInMatricaString) {
	int num = 0;
	for (std::vector<std::vector<std::string>>::iterator it = matrica.begin(); it != matrica.end(); ++it) {
		std::vector<std::string> elem = *it;
		if (elem[posInMatricaString] == name) {
			return num;
		}
		num++;
	}
	return -1;
}

std::vector<std::vector<std::string>> AutomatMinimization::MuraInMili(std::vector<std::vector<std::string>> matrica, int terminalStatesNumber) {
	std::vector<std::vector<std::string>> matricaMili;
	int num = 0;
	int classPosition = 2;
	int positionY = 1;
	for (std::vector<std::vector<std::string>>::iterator it = matrica.begin(); it != matrica.end(); ++it) {
		matricaMili.push_back({ matrica[num][0] });
		std::vector<std::string> elem = *it;
		for (int i = 0; i < terminalStatesNumber; i++) {
			matricaMili[num].push_back(matrica[num][classPosition]);
			matricaMili[num].push_back(matrica[FindPosInMatrica(matrica, matrica[num][classPosition], 0)][positionY]);
			classPosition++;
		}
		num++;
		classPosition = 2;
	}
	return matricaMili;
}

void AutomatMinimization::ReadAutomatOptionsInFile(std::ifstream& inputF) {
	std::string elem1;
	getline(inputF, elem1);
	statesNumber = stoi(elem1);
	getline(inputF, elem1);
	terminalStatesNumber = stoi(elem1);
	getline(inputF, elem1);
	outSymbol = stoi(elem1);
}

std::string AutomatMinimization::EquivalenceClass(std::string key, std::vector<std::vector<std::string>>& classes, std::string earlyClass, int& classNumber) { //
	int vectorSize = classes.size();
	int i = 0;
	for (i; i < vectorSize; ++i) {
		if (classes[i][1] == key && earlyClass == classes[i][2]) {
			return classes[i][0];
		}
		if (classNumber < stoi(classes[i][0])) {
			classNumber = stoi(classes[i][0]);
		}
	}

	if (i == vectorSize) {
		classes.push_back({ std::to_string(++classNumber), key, earlyClass });
	}
	return std::to_string(classNumber);
}

std::vector<std::vector<std::string>> AutomatMinimization::FinalClasses(std::vector<std::vector<std::string>> matrica, int nowClassN, int terminalStatesNumber) {
	int earlyClassN = 0;
	std::string nowClass = "";
	int index = 2;
	while (earlyClassN < nowClassN) {
		earlyClassN = nowClassN;
		nowClassN = 0;

		std::vector<std::vector<std::string>> classes;
		for (std::vector<std::vector<std::string>>::iterator it = matrica.begin(); it != matrica.end(); ++it) {
			index = 4;
			it[0][0] = it[0][2 + terminalStatesNumber * 2];
			std::vector<std::string>& elem = *it;
			for (int i = 0; i < terminalStatesNumber; i++) {
				nowClass += elem[index];
				index += 2;
			}
			
			it[0][2 + terminalStatesNumber * 2] = EquivalenceClass(nowClass, classes, elem[0], nowClassN);
			nowClass = "";
		}
		classes.clear();
		//cout << "f\n";
	}
	return matrica;
}

std::vector<std::vector<std::string>> AutomatMinimization::SortMatrica(int indexElemForSort, int maxClassN, std::vector<std::vector<std::string>> matrica) {
	maxClassN++;
	std::vector<std::vector<std::string>> endMatrica;
	for (int i = 1; i != maxClassN; i++) {
		for (std::vector<std::vector<std::string>>::iterator it = matrica.begin(); it != matrica.end(); ++it) {
			if (stoi(it[0][indexElemForSort]) == i) {
				endMatrica.push_back(it[0]);
			}
		}
	}
	return endMatrica;
}

std::vector<std::vector<std::string>> AutomatMinimization::Minimization(std::vector<std::vector<std::string>> matrica, int terminalStatesNumber)
{
	matrica = AddClassesInMatrica(matrica);
	//1 изначальные классы эквивалентности
	std::vector<std::vector<std::string>> classes;
	int nowClassN = 0;
	int index = 0;
	std::string nowClassStr = "";
	int earlyClassN = -1;

	for (std::vector<std::vector<std::string>>::iterator it = matrica.begin(); it != matrica.end(); ++it) {
		index = 4; //номер Y в каждом элементе матрицы
		std::vector<std::string>& elem = *it;
		for (int i = 0; i < terminalStatesNumber; i++) {
			nowClassStr += elem[index];
			it[0][index] = it[0][index - 1];
			index += 2;
		}
		it[0][3 + terminalStatesNumber * 2] = EquivalenceClass(nowClassStr, classes, elem[0], nowClassN);
		nowClassStr = "";
	}
	classes.clear();

	for (std::vector<std::vector<std::string>>::iterator it = matrica.begin(); it != matrica.end(); ++it) {
		std::vector<std::string> elem = *it;
		it[0][0] = elem[3 + terminalStatesNumber * 2];
		index = 3;
		for (int i = 0; i < terminalStatesNumber; i++) {
			it[0][index] = matrica[FindPosInMatrica(matrica, it[0][index], 2)][3 + terminalStatesNumber * 2];
			index += 2;
		}
	}

	matrica = SortMatrica(0, nowClassN, matrica);

	while (earlyClassN < nowClassN) {
		earlyClassN = nowClassN;
		nowClassN = 0;
		for (std::vector<std::vector<std::string>>::iterator it = matrica.begin(); it != matrica.end(); ++it) {
			index = 3; //номер класса в каждом элементе матрицы
			std::vector<std::string>& elem = *it;
			for (int i = 0; i < terminalStatesNumber; i++) {
				nowClassStr += elem[index];
				index += 2;
			}
			it[0][3 + terminalStatesNumber * 2] = EquivalenceClass(nowClassStr, classes, elem[0], nowClassN);
			nowClassStr = "";
		}
		classes.clear();

		for (std::vector<std::vector<std::string>>::iterator it = matrica.begin(); it != matrica.end(); ++it) {
			it[0][0] = it[0][3 + terminalStatesNumber * 2];
			index = 3;
			for (int i = 0; i < terminalStatesNumber; i++) {
				it[0][index] = matrica[FindPosInMatrica(matrica, it[0][index + 1], 2)][3 + terminalStatesNumber * 2];
				index += 2;
			}
		}

		matrica = SortMatrica(0, nowClassN, matrica);
	}

	//2  изменение таблицы с использованием новых классов
	//cout << nowClassN << '\n';
	//matrica = FinalClasses(matrica, nowClassN, terminalStatesNumber);

	return matrica;
}

std::vector<std::vector<std::string>> AutomatMinimization::EditingForOutput(std::vector<std::vector<std::string>> initialMatrica, std::vector<std::vector<std::string>> matrica, int terminalStatesNumber) {
	initialMatrica = AddClassesInMatrica(initialMatrica);
	std::vector<std::vector<std::string>> finalMatrica;
	std::vector<std::string> elementMatrci;
	std::vector<std::string> classes;
	int nowClass = 0;
	int iterathion = 0;
	int index = 0;
	std::string stateName = "s";
	std::string forPush = "";
	int firstClass = 1;
	const int ELEMENT_SIZE = 2;

	for (std::vector<std::vector<std::string>>::iterator it = matrica.begin(); it != matrica.end(); ++it) {
		if (find(classes.begin(), classes.end(), it[0][0]) == classes.end()) {
			std::vector<std::string>& elem = *it;
			forPush = stateName + std::to_string(nowClass + firstClass);
			for (int i = forPush.size(); i != ELEMENT_SIZE; i++) {
				forPush += " ";
			}
			elementMatrci.push_back(forPush);
			index = 3;
			for (int i = 0; i < terminalStatesNumber; i++) {
				forPush = stateName + std::to_string(stoi(it[0][index]));
				for (int i = forPush.size(); i != ELEMENT_SIZE; i++) {
					forPush += " ";
				}
				elementMatrci.push_back(forPush);
				forPush = initialMatrica[FindPosInMatrica(initialMatrica, it[0][2], 2)][index + 1];
				for (int i = forPush.size(); i != ELEMENT_SIZE; i++) {
					forPush += " ";
				}
				elementMatrci.push_back(forPush);
				index += 2;
			}

			finalMatrica.push_back(elementMatrci);
			elementMatrci.clear();
			nowClass++;
			classes.push_back(it[0][0]);
		}
		iterathion++;
	}
	return finalMatrica;
}

std::vector<std::vector<std::string>> AutomatMinimization::AddClassesInMatrica(std::vector<std::vector<std::string>> matrica) {
	int i = 1;
	for (std::vector<std::vector<std::string>>::iterator it = matrica.begin(); it != matrica.end(); ++it) {
		it[0].insert(it[0].begin(), std::to_string(i));
		it[0].insert(it[0].begin(), std::to_string(1));
		it[0].push_back("0");
		i++;
	}
	return matrica;
};

int AutomatMinimization::GetTerminalStatesNumber() {
	return terminalStatesNumber;
}
