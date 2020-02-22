#include<math.h>
#include"../inc/cxz.h"
using namespace std;

void cxz::io::read_vtk(
	std::vector<double>& points,
	std::vector<std::size_t>& cells,
	std::vector<std::size_t>& cell_types,
	const std::string& file_path
) {
	ifstream file(file_path);
	string line;
	std::size_t temp_number = 0;

	while (getline(file, line)) {
		string temp;
		istringstream in(line);
		in >> temp;

		if (temp == "POINTS") {
			double double_number;
			in >> temp_number;
			for (std::size_t i = 0; i < temp_number; i++) {
				getline(file, line);
				in.clear();
				in.str(line);
				for (auto j = 0; j < 3; j++) {
					in >> double_number;
					points.push_back(double_number);
				}
			}
		}
		if (temp == "CELLS") {
			std::size_t size_tt;
			in >> temp_number;
			for (std::size_t i = 0; i < temp_number; i++) {
				getline(file, line);
				in.clear();
				in.str(line);
				for (auto j = 0; j < 9; j++) {
					in >> size_tt;
					cells.push_back(size_tt);
				}
			}
		}
		if (temp == "CELL_TYPES") {
			std::size_t size_tt;
			in >> temp_number;
			for (std::size_t i = 0; i < temp_number; i++) {
					getline(file, line);
					in.clear();
					in.str(line);
					in >> size_tt;
					cell_types.push_back(size_tt);
			}
		}
	}
}

namespace cxz {
	namespace hex_scaled_jacobian_auxiliary {
		struct Vect { double x, y, z;};
		std::size_t operations_order[8][4] = { {0,1,3,4},{1,2,0,5},{2,3,1,6},{3,0,2,7},{4,7,5,0},{5,4,6,1},{6,5,7,2},{7,6,4,3} };
		double ComputeCrossProduct(const Vect vect[3]) {
			Vect temp;
			temp.x = vect[0].y*vect[1].z - vect[0].z*vect[1].y;
			temp.y = vect[0].z*vect[1].x - vect[0].x*vect[1].z;
			temp.z = vect[0].x*vect[1].y - vect[0].y*vect[1].x;

			return (temp.x*vect[2].x + temp.y*vect[2].y + temp.z*vect[2].z);
		};
	};
};

int cxz::hex_scaled_jacobian_hex(
	std::vector<double>& sj,
	const std::vector<double>& points,
	const std::vector<std::size_t>& cells,
	const std::vector<std::size_t>& cell_types
) {
	using namespace cxz::hex_scaled_jacobian_auxiliary;
	
	Vect vect[3];
	Vect temp_vect;
	std::size_t cell_numebr = cell_types.size();
	double temp_length;
	double temp_quality,smallest_quality;

	for (std::size_t k = 0; k < cell_numebr; k++) {
		if (cell_types[k] != 12) {
			return 1;
		}

		smallest_quality = 1;
		for (size_t i = 0; i < 8; i++) {
			for (size_t j = 1; j < 4; j++) {
				temp_vect.x = points[cells[(9 * k + 1 + operations_order[i][j])] * 3] - points[cells[(9 * k + 1 + operations_order[i][0])] * 3];
				temp_vect.y = points[cells[(9 * k + 1 + operations_order[i][j])] * 3 + 1] - points[cells[(9 * k + 1 + operations_order[i][0])] * 3 + 1];
				temp_vect.z = points[cells[(9 * k + 1 + operations_order[i][j])] * 3 + 2] - points[cells[(9 * k + 1 + operations_order[i][0])] * 3 + 2];
				temp_length = pow(temp_vect.x*temp_vect.x + temp_vect.y*temp_vect.y + temp_vect.z*temp_vect.z, 0.5);
				vect[j - 1].x = temp_vect.x / temp_length;
				vect[j - 1].y = temp_vect.y / temp_length;
				vect[j - 1].z = temp_vect.z / temp_length;
			}
			temp_quality = ComputeCrossProduct(vect);
			if (smallest_quality > temp_quality)
				smallest_quality = temp_quality;
		}
		sj.push_back(smallest_quality);
	}

	return 0;
}