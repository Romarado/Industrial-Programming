#include <list>

#include "Track.hpp"
#include "Machine.hpp"

using std::list;

Track::Track(list<Machine> vehicles, int volume) {
	for (auto it = vehicles.begin(); it != vehicles.end(); it++) {
		cost += (*it).SumCost(volume, (*it).GetDistance());
		time += (*it).SumTime((*it).GetDistance());
	}
}

Track::Track() { cost = time = volume = 0; }

double Track::GetCost() { return cost; }