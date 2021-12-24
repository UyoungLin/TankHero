#include "header.h"
#include "State.h"
#include "Scyyl7Engine.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

State::State() : m_engine(NULL)
{
}

State::State(Scyyl7Engine* engine)
	: m_engine(engine)
{
}

State::~State()
{
}

void State::loadMap(char* fileName)
{
	ifstream FILE;
	string tpLine;

	FILE.open(fileName, ios::in);
	if (FILE.is_open() == false)
	{
		cout << "Error with opening files." << endl;
		return;
	}

	while (getline(FILE, tpLine, ','))
	{
		if (tpLine.substr(0, 1) == "\n")
			tpLine.erase(0, 1);
		mapStr.push_back(tpLine);
	}

	FILE.close();
}

std::vector<std::string> State::getMapStr()
{
	return mapStr;
}

void State::clearMap()
{
	mapStr.clear();
}


