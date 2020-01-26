#include<math.h>
#include"../inc/cell_type12.h"
struct Vect {
	double x, y, z;
};
size_t operations_order[8][4] = { {0,1,3,4},{1,2,0,5},{2,3,1,6},{3,0,2,7},{4,7,5,0},{5,4,6,1},{6,5,7,2},{7,6,4,3} };

double Compute(const Vect vect[3])
{
	Vect temp;
	temp.x = vect[0].y*vect[1].z - vect[0].z*vect[1].y;
	temp.y = vect[0].z*vect[1].x - vect[0].x*vect[1].z;
	temp.z = vect[0].x*vect[1].y - vect[0].y*vect[1].x;

	return (temp.x*vect[2].x + temp.y*vect[2].y + temp.z*vect[2].z);
}

void Cell::ComputeQuality(const std::vector<Point> & point)
{
	Vect vect[3];
	Vect temp_vect;
	double temp_length;
	double single_quality,sum=0;

	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 1; j < 4; j++) {
			temp_vect.x = point[point_index[operations_order[i][j]]].x - point[point_index[operations_order[i][0]]].x;
			temp_vect.y = point[point_index[operations_order[i][j]]].y - point[point_index[operations_order[i][0]]].y;
			temp_vect.z = point[point_index[operations_order[i][j]]].z - point[point_index[operations_order[i][0]]].z;
			temp_length = pow(temp_vect.x*temp_vect.x + temp_vect.y*temp_vect.y + temp_vect.z*temp_vect.z, 0.5);
			vect[j - 1].x = temp_vect.x / temp_length;
			vect[j - 1].y = temp_vect.y / temp_length;
			vect[j - 1].z = temp_vect.z / temp_length;			
		}
		single_quality = Compute(vect);
		sum = sum + single_quality;
	}
	quality = sum/8;
}
