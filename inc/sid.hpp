#ifndef SID_H
#define SID_H

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

void test();

namespace sid{
    namespace io{
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

/*
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

#include "sid.hpp"

int main(int argc, char* argv[]){
    //step 1
    test();

    //step 2
    if(argc == 0){
        std::cerr << "ERROR " << __LINE__ << " : " << "no input_file_path." << std::endl;
        exit(-1);
    }
    std::string file_path = argv[1];

    //step 3
    std::vector<double> points;
    std::vector<std::size_t> cells;
    std::vector<std::size_t> cell_types;

    sid::io::read_vtk(points, cells, cell_types, file_path);

    //step 4
    std::vector<double> sj;
    sid::hex_scaled_jacobian_hex(sj, points, cells, cell_types);

    double min_sj = *std::min_element(sj.begin(), sj.end());
    double sum_sj = std::accumulate(sj.begin(), sj.end(), 0.0);
    double ave_sj = -1.0;
    if(sj.size()) ave_sj = sum_sj / sj.size();

    std::cout << "INFO " << __LINE__ << " : ";
    std::cout << " n_hex: " << sj.size();
    std::cout << " min_sj: " << min_sj;
    std::cout << " ave_sj: " << ave_sj;
    std::cout << std::endl;

    return 0;
}
*/