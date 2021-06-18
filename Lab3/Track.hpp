#pragma once
#include <list>

class Machine;

class Track {
private:
	double cost;
	double time;
	int volume;	
public:
	Track();
	~Track() = default;
	Track(std::list<Machine> vehicles, int volume);

	double GetCost();
};