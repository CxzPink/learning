#ifndef CXZ_H
#define CXZ_H

#include <vector>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

namespace cxz {
	namespace io {
		void read_vtk(
			std::vector<double>& points,
			std::vector<std::size_t>& cells,
			std::vector<std::size_t>& cell_types,
			const std::string& file_path
		);
		//points: 0.0 0.0 0.0  1.0 1.0 1.0  ...
		//cells: 4 0 1 2 3  4 4 5 6 7  ...
		//cell_types: 12 12  ...
	};
	int hex_scaled_jacobian_hex(
		std::vector<double>& sj,
		const std::vector<double>& points,
		const std::vector<std::size_t>& cells,
		const std::vector<std::size_t>& cell_types
	);
};

#endif