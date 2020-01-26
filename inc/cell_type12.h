#ifndef _CELL_H_
#define _CELL_H_
#include<string>
#include<vector>

struct Point {
	double x, y, z;
};

class Cell {
public:
	std::string cell_type;
	size_t point_index[8];
	double quality;

	void ComputeQuality(const std::vector<Point> & point); 
};

#endif// _CELL_H_