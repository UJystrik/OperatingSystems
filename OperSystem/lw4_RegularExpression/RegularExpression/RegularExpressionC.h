#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "AutomatDetermin.h"

class RegularExpressionC : public AutomatDetermin
{
public:
	std::vector<std::vector<std::string>> RegularExpressionInTransitionTable(std::vector<std::vector<std::string>> regularExpression);

	std::vector<std::vector<std::string>> MergeTableFields(std::vector<std::vector<std::string>> matrica);

protected:
	std::vector<char> TERMINAL_SUMBOLS = { '*', '|', '+' };

	std::string GetNewState(std::vector<std::vector<std::string>>& regularExpression, int pos, std::string& sumbol, bool& thereAreTransformations);

	int NewStateInTable(std::vector<std::vector<std::string>>& regularExpression, int pos, int& nowStateNum, bool& thereAreTransformations);

	std::string ReturnParenthesizedStringFromPosition(std::string& str, int pos);

	std::string NewStatesSeparatedByOr(std::vector<std::vector<std::string>>& regularExpression, int pos, std::vector<std::string>& newStates);
};

