#include "Machine.hpp"

#include <tuple>

using std::tuple;
using std::unique_ptr;

Machine::Machine() {
	machineSpeed = 0;
	machineVol = 0;
	machinePrice = 0.0f;
	dist = 0;
}

Machine::Machine(std::tuple<int, int, double> vehicleParams, int distance) :
	machineSpeed(get<0>(vehicleParams)),
	machineVol(get<1>(vehicleParams)),
	machinePrice(get<2>(vehicleParams)),
	dist(distance) {}

double Machine::SumCost(int mass, int dist) {
	return (mass / machineVol) * SumTime(dist) * machinePrice;
}

double Machine::SumTime(int dist) const {
	return dist / machineSpeed;
}

int Machine::GetDistance() const { return dist; };
void Machine::SetSpeed(int speed) { machineSpeed = speed; }
void Machine::SetVolume(int volume) { machineVol = volume; }
void Machine::SetPrice(double price) { machinePrice = price; }
void Machine::SetDistance(int distance) { dist = distance; }

/** ------------------------------------------------------------ */

Train::Train() : Machine(make_tuple(100, 500, 200), 0) {}

Train::Train(std::tuple<int, int, double> trainParams, int distance) :
	Machine(trainParams, distance) {}

/** ------------------------------------------------------------ */

Car::Car() : Machine(make_tuple(60, 50, 100), 0) {}

Car::Car(std::tuple<int, int, double> trainParams, int distance) :
	Machine(trainParams, distance) {};

/** ------------------------------------------------------------ */

Plane::Plane() : Machine(make_tuple(300, 100, 500), 0) {}

Plane::Plane(std::tuple<int, int, double> trainParams, int distance) :
	Machine(trainParams, distance) {}


void CarBuilder::Reset() {
	car_ = std::unique_ptr<Machine>(new Car());
}
Machine* CarBuilder::GetCar() {
	return car_.get();
}

void CarBuilder::BuildSpeed(int speed) { car_->SetSpeed(speed); }
void CarBuilder::BuildVolume(int volume) { car_->SetVolume(volume); }
void CarBuilder::BuildPrice(double price) { car_->SetPrice(price); }
void CarBuilder::BuildDistance(int distance) { car_->SetDistance(distance); }

/* ---------------------------------- */

void TrainBuilder::Reset() {
	train_ = std::unique_ptr<Machine>(new Train());
}
Machine* TrainBuilder::GetTrain() {
	return train_.get();
}

void TrainBuilder::BuildSpeed(int speed) { train_->SetSpeed(speed); }
void TrainBuilder::BuildVolume(int volume) { train_->SetVolume(volume); }
void TrainBuilder::BuildPrice(double price) { train_->SetPrice(price); }
void TrainBuilder::BuildDistance(int distance) { train_->SetDistance(distance); }

/* ---------------------------------- */

void PlaneBuilder::Reset() {
	plane_ = std::unique_ptr<Machine>(new Plane());
}
Machine* PlaneBuilder::GetPlane() {
	return plane_.get();
}

void PlaneBuilder::BuildSpeed(int speed) { plane_->SetSpeed(speed); }
void PlaneBuilder::BuildVolume(int volume) { plane_->SetVolume(volume); }
void PlaneBuilder::BuildPrice(double price) { plane_->SetPrice(price); }
void PlaneBuilder::BuildDistance(int distance) { plane_->SetDistance(distance); }