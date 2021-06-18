#pragma once

#include "Info.hpp"
#include "Machine.hpp"
#include "Track.hpp"

using std::string;

enum Type {
	Turbo,
	Standart,
	Economy
};

class Order
{
	double cost;
	int volume;
	std::string startPoint;
	std::string finishPoint;
	enum::Type type;
	Track track;
	Info* inf = Info::GetInstance();

public:
	Order();
	Order(Type, std::string, std::string, int);
	~Order();
	int decr(std::string);
	int** matrixUpd(Type);
	int* optim(int**, int, int);
	Track best(std::string, std::string, Type, int);
};

