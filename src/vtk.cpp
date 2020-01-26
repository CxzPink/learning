#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include"../inc/vtk.h"
using namespace std;

int Vtk::ReadFile(std::string& address)
{
	ifstream file(address);
	string line;
	Point *p = nullptr;
	Cell *c = nullptr;
	size_t temp_number = 0;
	file_address = address;

	getline(file, line);
	if (line[0] == '#') {
		string s0, s1, s2, s3, s4;
		istringstream in(line);
		in >> s0 >> s1 >> s2 >> s3 >> s4;
		if (s1 == "vtk" && s2 == "DataFile" && s3 == "Version")
			version = s4;
		else
			return 1;
	}
	else
		return 1;

	while (getline(file, line)) {
		string temp;
		istringstream in(line);
		in >> temp;
		if (temp == "DATASET") {
			in >> DATASET;
		}
		if (temp == "POINTS") {
			in >> size_point;
			for (size_t i = 0; i < size_point; i++) {
				getline(file, line);
				in.clear();
				in.str(line);
				p = new Point();
				in >> p->x >> p->y >> p->z;
				point.push_back(*p);
				delete p;

			}
		}
		if (temp == "CELLS") {
			in >> size_cell;
			for (size_t i = 0; i < size_cell; i++) {
				c = new Cell();
				getline(file, line);
				in.clear();
				in.str(line);
				in >> temp_number;
				for (size_t i = 0; i < temp_number; i++)
					in >> c->point_index[i];
				cell.push_back(*c);
				delete c;
			}
		}
		if (temp == "CELL_TYPES") {
			in >> temp_number;
			if (temp_number == size_cell) {
				for (size_t i = 0; i < size_cell; i++) {
					getline(file, line);
					in.clear();
					in.str(line);
					in >> cell[i].cell_type;
				}
				return 0;
			}
			else
				return 1;
		}
	}
	return 1;
}

void Vtk::ScaledJacobian(void)
{
	double smallest_quality = 1;
	double sum=0;
	for (auto i : cell) {
		i.ComputeQuality(point);
		if (smallest_quality > i.quality)
			smallest_quality = i.quality;
		sum = sum + i.quality;
	}
	std::cout << "smallest "<<smallest_quality << " | " << "average "<<sum / size_cell << std::endl;
}