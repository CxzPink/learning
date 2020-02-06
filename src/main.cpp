#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include"../inc/sid.hpp"
#include"../inc/cxz.h"

int main(int argc, char* argv[]) {
	//step 1
	test();

	//step 2
	if (argc != 2) {
		std::cerr << "ERROR " << __LINE__ << " : " << "no input_file_path." << std::endl;
		exit(-1);
	}
	std::string file_path = argv[1];

	//step 3
	std::vector<double> points;
	std::vector<std::size_t> cells;
	std::vector<std::size_t> cell_types;

	cxz::io::read_vtk(points, cells, cell_types, file_path);

	//step 4
	std::vector<double> sj;
	cxz::hex_scaled_jacobian_hex(sj, points, cells, cell_types);

	double min_sj = *std::min_element(sj.begin(), sj.end());
	double sum_sj = std::accumulate(sj.begin(), sj.end(), 0.0);
	double ave_sj = -1.0;
	if (sj.size()) ave_sj = sum_sj / sj.size();

	std::cout << "INFO " << __LINE__ << " : ";
	std::cout << " n_hex: " << sj.size();
	std::cout << " min_sj: " << min_sj;
	std::cout << " ave_sj: " << ave_sj;
	std::cout << std::endl;

	return 0;
}