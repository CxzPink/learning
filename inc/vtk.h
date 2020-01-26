#ifndef _VTK_H_
#define _VTK_H_
#include<string>
#include<vector>
#include"../inc/cell_type12.h"
class Vtk {
public:
	std::string version;// vtk version
	std::string file_address; // file address
	std::string DATASET;
	std::vector<Point> point;
	std::vector<Cell> cell;
	size_t size_point; //number of point
	size_t size_cell; //number of cell

	int ReadFile(std::string& address);// readfile
	void ScaledJacobian(void);// compute ScaledJacobian for every cell
};
#endif//_VTK_H_