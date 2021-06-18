#include <string>
#include <list>

#include "Order.hpp"
#include "Info.hpp"
#include "Machine.hpp"
#include "Track.hpp"

using std::string;
using std::list;

Order::Order() {
	cost = 0;
	volume = 0;
	startPoint = "";
	finishPoint = "";
	track = Track();
	type = Type::Economy;
}

Order::Order(Type deliv, string startP, string finishP, int vol) {
	startPoint = startP;
	finishPoint = finishP;
	type = deliv;
	track = best(startP, finishP, deliv, vol);
	cost = track.GetCost();
	volume = vol;
}

int Order::decr(string str)
{
	for (auto it = inf->GetTowns().begin(); it != inf->GetTowns().end(); it++)
	{
		if (str._Equal((*it).first))
			return (*it).second;
	}
	return -1;
}

int** Order::matrixUpd(Type type)
{
	int** matrix = new int* [16];
	for (int i = 0; i < 16; i++)
	{
		matrix[i] = new int[16];
		for (int j = 0; j < 16; j++)
		{
			matrix[i][j] = inf->GetMatrixDist(i, j);
		}
	}
	switch (type)
	{
	case Economy:
		for (int i = 0; i < 16; i++)
		{
			if (inf->GetPoints(i).find("TS"))
				for (int j = 0; j < 16; j++)
					matrix[i][j] = 99999;
		}
	case Standart:
		for (int i = 0; i < 16; i++)
		{
			if (inf->GetPoints(i).find("AP"))
				for (int j = 0; j < 16; j++)
					matrix[i][j] = 99999;
		}
	case Turbo:
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
				if (matrix[i][j] == 0)
					matrix[i][j] = 99999;
		}
	}
	return matrix;
}

int* Order::optim(int** arr, int beginPoint, int endPoint)
{
	int* d = new int[16];
	int* v = new int[16];
	int temp, minindex, min;
	int begin_index = beginPoint;

	for (int i = 0; i < 16; i++)
	{
		d[i] = 99999;
		v[i] = 1;
	}
	d[begin_index] = 0;

	do {
		minindex = 99999;
		min = 99999;
		for (int i = 0; i < 16; i++)
		{
			if ((v[i] == 1) && (d[i] < min))
			{
				min = d[i];
				minindex = i;
			}
		}

		if (minindex != 99999)
		{
			for (int i = 0; i < 16; i++)
			{
				if (arr[minindex][i] > 0)
				{
					temp = min + arr[minindex][i];
					if (temp < d[i])
					{
						d[i] = temp;
					}
				}
			}
			v[minindex] = 0;
		}
	} while (minindex < 99999);

	int* ver = new int[16];
	int end = endPoint;
	ver[0] = end;
	int k = 1;
	int weight = d[end];

	while (end != begin_index)
	{
		for (int i = 0; i < 16; i++)
			if (arr[end][i] != 0)
			{
				int temp = weight - arr[end][i];
				if (temp == d[i])
				{
					weight = temp;
					end = i;
					ver[k] = i + 1;
					k++;
				}
			}
	}
	for (int i = 0; i < k / 2; i++)
		std::swap(ver[i], ver[k - 1 - i]);
	delete[] d, v;
	return ver;
}

Track Order::best(string startP, string finishP, Type deliv, int volume) {
	int start = decr(startP);
	int finish = decr(finishP);
	int** mat = new int* [16];
	for (int i = 0; i < 16; i++)
		mat[i] = new int[16];
	mat = matrixUpd(deliv);

	int* path = new int[16];
	for (int i = 0; i < 16; i++)
		path[i] = -1;
	path = optim(mat, start, finish);

	int count = 0;
	for (int i = 0; i < 16; i++) {
		if (path[i] != -1)
			count++;
		else
			break;
	}

	switch (count) {
	case 1: {
		Car car1 = Car();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++) {
			if ((*it).first.find(inf->GetPoints(path[0])))
				car1 = Car(inf->GetTableCost((*it).second * 3 + 2), inf->GetMatrixDist(path[0], path[1]));
		}

		list<Machine> c = { car1 };
		Track track = Track(c, volume);
		return track;
	}

	case 3: {
		Car car1 = Car();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++) {
			if ((*it).first.find(inf->GetPoints(path[0])))
				car1 = Car(inf->GetTableCost((*it).second * 3 + 2), inf->GetMatrixDist(path[0], path[1]));
		}

		Car car2 = Car();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++) {
			if ((*it).first.find(inf->GetPoints(path[2])))
				car2 = Car(inf->GetTableCost((*it).second * 3 + 2), inf->GetMatrixDist(path[2], path[3]));
		}

		Train train1 = Train();
		Plane plane1 = Plane();
		Track track = Track();

		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++) {
			if ((*it).first.find(inf->GetPoints(path[1])) && (inf->GetPoints(path[1])).find("TS")) {
				train1 = Train(inf->GetTableCost((*it).second * 3 + 1), inf->GetMatrixDist(path[1], path[2]));

				list<Machine> v = { car1, car2, train1 };
				track = Track(v, volume);
			}

			if ((*it).first.find(inf->GetPoints(path[1])) && (inf->GetPoints(path[1])).find("AP")) {
				plane1 = Plane(inf->GetTableCost((*it).second * 3), inf->GetMatrixDist(path[1], path[2]));

				list<Machine> v = { car1, car2, plane1 };
				track = Track(v, volume);
			}
		}
		return track;
	}

	case 5: {
		Car car1 = Car();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++) {
			if ((*it).first.find(inf->GetPoints(path[0])))
				car1 = Car(inf->GetTableCost((*it).second * 3 + 2), inf->GetMatrixDist(path[0], path[1]));
		}

		Train train1 = Train();
		Plane plane1 = Plane();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++) {
			if ((*it).first.find(inf->GetPoints(path[1])) && (inf->GetPoints(path[1])).find("TS")) {
				train1 = Train(inf->GetTableCost((*it).second * 3 + 1), inf->GetMatrixDist(path[1], path[2]));
			}
			if ((*it).first.find(inf->GetPoints(path[1])) && (inf->GetPoints(path[1])).find("AP")) {
				plane1 = Plane(inf->GetTableCost((*it).second * 3), inf->GetMatrixDist(path[1], path[2]));
			}
		}

		Car car2 = Car();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++) {
			if ((*it).first.find(inf->GetPoints(path[2]))) {
				car2 = Car(inf->GetTableCost((*it).second * 3 + 2), inf->GetMatrixDist(path[2], path[3]));
			}
		}

		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++)
		{
			if ((*it).first.find(inf->GetPoints(path[3])) && (inf->GetPoints(path[3])).find("AP"))
			{
				plane1 = Plane(inf->GetTableCost((*it).second * 3), inf->GetMatrixDist(path[3], path[4]));
			}
			if ((*it).first.find(inf->GetPoints(path[3])) && (inf->GetPoints(path[3])).find("TS"))
			{
				train1 = Train(inf->GetTableCost((*it).second * 3 + 1), inf->GetMatrixDist(path[3], path[4]));
			}
		}

		Car car3 = Car();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++)
		{
			if ((*it).first.find(inf->GetPoints(path[4])))
			{
				car3 = Car(inf->GetTableCost((*it).second * 3 + 2), inf->GetMatrixDist(path[4], path[5]));
			}
		}

		list<Machine> v = { car1, car2, car3, train1, plane1 };
		Track track = Track(v, volume);
		return track;
	}

	case 7:
	{
		Car car1 = Car();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++)
		{
			if ((*it).first.find(inf->GetPoints(path[0])))
			{
				car1 = Car(inf->GetTableCost((*it).second * 3 + 2), inf->GetMatrixDist(path[0], path[1]));
			}
		}

		Train train1 = Train();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++)
		{
			if ((*it).first.find(inf->GetPoints(path[1])))
			{
				train1 = Train(inf->GetTableCost((*it).second * 3 + 1), inf->GetMatrixDist(path[1], path[2]));
			}
		}

		Car car2 = Car();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++)
		{
			if ((*it).first.find(inf->GetPoints(path[2])))
			{
				car2 = Car(inf->GetTableCost((*it).second * 3 + 2), inf->GetMatrixDist(path[2], path[3]));
			}
		}

		Plane plane1 = Plane();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++)
		{
			if ((*it).first.find(inf->GetPoints(path[3])))
			{
				plane1 = Plane(inf->GetTableCost((*it).second * 3), inf->GetMatrixDist(path[3], path[4]));
			}
		}

		Car car3 = Car();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++)
		{
			if ((*it).first.find(inf->GetPoints(path[4])))
			{
				car3 = Car(inf->GetTableCost((*it).second * 3 + 2), inf->GetMatrixDist(path[4], path[5]));
			}
		}

		Train train2 = Train();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++)
		{
			if ((*it).first.find(inf->GetPoints(path[5])))
			{
				train2 = Train(inf->GetTableCost((*it).second * 3 + 1), inf->GetMatrixDist(path[5], path[6]));
			}
		}

		Car car4 = Car();
		for (auto it = inf->GetTable().begin(); it != inf->GetTable().end(); it++)
		{
			if ((*it).first.find(inf->GetPoints(path[6])))
			{
				car4 = Car(inf->GetTableCost((*it).second * 3 + 2), inf->GetMatrixDist(path[6], path[7]));
			}
		}

		list<Machine> v = { car1, car2, car3, car4, train1, train2, plane1 };
		Track track = Track(v, volume);
		return track;
	}
	}
}
