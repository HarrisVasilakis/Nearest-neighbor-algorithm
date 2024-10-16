#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <list>
#include <chrono>
#include "class.h"
#include "ghashfunction.h"
#include "cliUtils.h"
#include "lshhelper.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
	int k = 4, L = 5, N = 1;        //default values so you dont have to put everything in the command line
	double delta=0;
	float R = 800.0;
	string datapath, querypath, outputpath,algorithm, metric;
	

	if ( getCliArgs(argc, argv,datapath, querypath, outputpath, k, L, N, R, delta, algorithm, metric) == -1 ) {
		return -1;
	}
	if(algorithm=="LSH" || algorithm=="lsh"){
		lsh(k,L, N,R,datapath,querypath,outputpath);
	}
	else if(algorithm=="Frechet" || algorithm=="frechet"){
		if(metric=="continuous"){

		}
		else{
			frechet(k,L,N,R,datapath,querypath,outputpath,delta);
		}
	}
	else{
		cout << "wrong input\n";
		return -1;
	}
	return 0;
}