// AutomatonMinimization.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include "AutomatMinimization.h"

using namespace std;

void ShowVector(std::vector<std::vector<std::string>> vector)
{
	for (std::vector<std::vector<std::string>>::iterator it = vector.begin(); it != vector.end(); ++it) {
		std::vector<std::string>& elem = *it;
		for (std::vector<std::string>::iterator it1 = elem.begin(); it1 != elem.end(); ++it1) {
			cout << *it1 << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

int main()
{
	setlocale(LC_ALL, "Russian");
	const std::string FILE_PATH = "../Input/input.txt";

	std::vector<std::vector<std::string>> matrica;
	std::string automatType;

	AutomatMinimization AutomatMinim;

	std::ifstream inputF;
	inputF.open(FILE_PATH);

	while (!inputF.eof()) {
		getline(inputF, automatType);
		if (automatType == AutomatMinim.MILI || automatType == AutomatMinim.MURA) {
			matrica.clear();
			AutomatMinim.ReadAutomatOptionsInFile(inputF);
			matrica = AutomatMinim.ReadAutomatInFile(inputF, AutomatMinim.GetTerminalStatesNumber(), automatType);
			//ShowVector(matrica);
			//AutomatMinim.ShowTransposition(AutomatMinim.Minimization(matrica, AutomatMinim.GetTerminalStatesNumber()));
			AutomatMinim.ShowTransposition(AutomatMinim.EditingForOutput(matrica, AutomatMinim.Minimization(matrica, AutomatMinim.GetTerminalStatesNumber()), AutomatMinim.GetTerminalStatesNumber()));
		}
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
