/*
 *  Copyright (C) 2020, Ryky Nelson
 */

#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <math.h>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace Eigen;


int main(int argc, char* argv[]){
    if (argc <= 1){
	cout << "ERROR: please provide Wavefunction file!" << '\n';
	return 0;
    }
    

    ifstream wffile( argv[1] );
    if(!wffile) {
	cerr << "Unable to open " << argv[1] << endl;
	return 0;
    }

    string line; Vector3i nGrids;
    getline(wffile,line);
    {
	string stmp;
	stringstream ss(line);
	ss >> stmp >> stmp >> stmp >> stmp >> stmp >> stmp >> stmp
	   >> nGrids(0) >> nGrids(1) >> nGrids(2);
    }

    int numOfLines = nGrids.prod();
    ArrayX3d grids(numOfLines,3);
    ArrayXd WFR(numOfLines), WFI(numOfLines);

    for (int il = 0; il < nGrids(0); ++il) {
	for (int jl = 0; jl < nGrids(1); ++jl) {
	    for (int kl = 0; kl < nGrids(2); ++kl) {

		double garbage;
		getline(wffile,line);
		stringstream ss(line);

		int idx = kl + ( jl*nGrids(2) ) + ( il*nGrids(2)*nGrids(1) );
		ss >> grids(idx,0) >> grids(idx,1) >> grids(idx,2) >> garbage
		   >> WFR(idx) >> WFI(idx);
		
	    }
	}
    }

    cout.precision(4);
    cout.setf(ios::fixed, ios::floatfield);
    cout << "BEGIN_BLOCK_DATAGRID_3D\n"
    	 << "  my_3D_datagrid\n"
    	//print the real components
    	 << "  BEGIN_DATAGRID_3D_this_is_3Dgrid#1\n"
    	 << "   " << nGrids.transpose() << endl
    	 << "   " << grids.row(0) << endl
    	 << "   " << grids(numOfLines-1,0)-grids(0,0) << ' ' << 0. << ' ' << 0. << endl
    	 << "   " << 0. << ' ' << grids(numOfLines-1,1)-grids(0,1) << ' ' << 0. << endl
    	 << "   " << 0. << ' ' << 0. << ' ' << grids(numOfLines-1,2)-grids(0,2) << endl;
    for (int iz = 0; iz < nGrids(2); ++iz) {
    	for (int iy = 0; iy < nGrids(1); ++iy) {
    	    for (int ix = 0; ix < nGrids(0); ++ix) {
		int idx = iz + ( iy*nGrids(2) ) + ( ix*nGrids(2)*nGrids(1) );
    		cout << "       " <<  WFR(idx) << ' ';
    	    }
    	    cout << endl;
    	}
    	if (iz == nGrids(2)-1) cout << "   END_DATAGRID_3D\n";
    	else cout << endl;
    }

    //print the imaginary components
    cout << "  BEGIN_DATAGRID_3D_this_is_3Dgrid#2\n"
    	 << "   " << nGrids.transpose() << endl
    	 << "   " << grids.row(0) << endl
    	 << "   " << grids(numOfLines-1,0)-grids(0,0) << ' ' << 0. << ' ' << 0. << endl
    	 << "   " << 0. << ' ' << grids(numOfLines-1,1)-grids(0,1) << ' ' << 0. << endl
    	 << "   " << 0. << ' ' << 0. << ' ' << grids(numOfLines-1,2)-grids(0,2) << endl;
    for (int iz = 0; iz < nGrids(2); ++iz) {
    	for (int iy = 0; iy < nGrids(1); ++iy) {
    	    for (int ix = 0; ix < nGrids(0); ++ix) {
		int idx = iz + ( iy*nGrids(2) ) + ( ix*nGrids(2)*nGrids(1) );
    		cout << "       " <<  WFI(idx) << ' ';
    	    }
    	    cout << endl;
    	}
    	if (iz == nGrids(2)-1) cout << "   END_DATAGRID_3D\n";
    	else cout << endl;
    }
    cout << "END_BLOCK_DATAGRID_3D\n";	    

    return 0;
}

