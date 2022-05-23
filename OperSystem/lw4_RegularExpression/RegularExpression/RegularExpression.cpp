// RegularExpression.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "RegularExpressionC.h"

void ShowVector(std::vector<std::vector<std::string>> vector)
{
	for (std::vector<std::vector<std::string>>::iterator it = vector.begin(); it != vector.end(); ++it) {
		std::vector<std::string>& elem = *it;
		for (std::vector<std::string>::iterator it1 = elem.begin(); it1 != elem.end(); ++it1) {
			std::cout << *it1 << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

int FindNumberElem(std::vector<std::string> vector, std::string str) {
	for (int i = 0; i < vector.size(); i++) {
		if (vector[i] == str) {
			return i;
		}
	}
	return -1;
}

int main()
{
	const std::string FILE_PATH = "../Input/input.txt";
	std::ifstream inputF;
	inputF.open(FILE_PATH);

	std::string regularExpression;
	std::vector<std::vector<std::string>> matrica;
	int stateNum = 0;
	RegularExpressionC regularEx;

	while (!inputF.eof()) {
		getline(inputF, regularExpression);
		matrica.push_back({ "1", "2", regularExpression });
		//matrica = regularEx.MergeTableFields(regularEx.RegularExpressionInTransitionTable(matrica));
		//matrica = regularEx.RegularExpressionInTransitionTable(matrica);
		matrica = regularEx.Determine(regularEx.MergeTableFields(regularEx.RegularExpressionInTransitionTable(matrica)));
		//ShowVector(matrica);
		//std::cout << regularExpression;
		regularEx.ShowTransposition(matrica);
		matrica.clear();
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
