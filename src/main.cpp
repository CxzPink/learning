#include<iostream>
#include"../inc/sid.hpp"
#include"../inc/vtk.h"

int main(int argc, char* argv[])
{
	Vtk vtk;
	std::string s(argv[1]);

	if (vtk.ReadFile(s))
		std::cout << "false" << std::endl;
	else {
		vtk.ScaledJacobian();
	}
	test();
}