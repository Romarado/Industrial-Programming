#pragma once

#include <tuple>
#include <memory>

using std::unique_ptr;
using std::tuple;
using std::get;
using std::make_tuple;

class Machine {
private:
	int machineSpeed;
	int machineVol;
	double machinePrice;
	int dist;
public:
	Machine();
	Machine(std::tuple<int, int, double> vehicleParams, int distance);
	~Machine() = default;

	double SumCost(int mass, int dist);
	double SumTime(int dist) const;

	int GetDistance() const;
	void SetSpeed(int speed);
	void SetVolume(int volume);
	void SetPrice(double price);
	void SetDistance(int distance);
};

class Train : public Machine {
public:
	Train();
	Train(std::tuple<int, int, double> trainParams, int distance);
};

class Car : public Machine {
public:
	Car();
	Car(std::tuple<int, int, double> trainParams, int distance);
};

class Plane : public Machine {
public:
	Plane();
	Plane(std::tuple<int, int, double> trainParams, int distance);
};

/** ------------ BUILDERS ------------ */

/**
 * @brief Here we use Builder pattern.
 *			  It is an interface for builders.
 */
class MachineBuilder {
public:
	virtual ~MachineBuilder();
	virtual void BuildSpeed(int speed);
	virtual void BuildVolume(int volume);
	virtual void BuildPrice(double price);
	virtual void BuildDistance(int distance);
};

class CarBuilder : public MachineBuilder {
private:
	unique_ptr<Machine> car_;

public:
	void BuildSpeed(int speed) override;
	void BuildVolume(int volume) override;
	void BuildPrice(double price) override;
	void BuildDistance(int distance) override;
	void Reset();
	Machine* GetCar();
};

class TrainBuilder : public MachineBuilder {
private:
	unique_ptr<Machine> train_;

public:
	void BuildSpeed(int speed) override;
	void BuildVolume(int volume) override;
	void BuildPrice(double price) override;
	void BuildDistance(int distance) override;
	void Reset();
	Machine* GetTrain();
};

class PlaneBuilder : public MachineBuilder {
private:
	unique_ptr<Machine> plane_;

public:
	void BuildSpeed(int speed) override;
	void BuildVolume(int volume) override;
	void BuildPrice(double price) override;
	void BuildDistance(int distance) override;
	void Reset();
	Machine* GetPlane();
};
