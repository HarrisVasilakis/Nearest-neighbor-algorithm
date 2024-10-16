#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <list>
#include <random>
#include <time.h>
#include <chrono>
#include "clusteringfunctions.h"
#include "cliUtils.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
	int i,j,c,K,L,k,maxlength,dimensions;
	int* arg=new int[6];                                    ///{K,L,k,M,k,probes}
	bool flag7=false,flag8=false;
	string datapath,configpath,outputpath,method,update,assignment;
	ofstream outfile;
	vector<datasetarray*> datasetarraytest;
	vector<hashclass*> datasethashtable;
	vector<float> tempcoordinates;
	if ( getCliArgs(argc, argv,datapath, configpath, outputpath, method, update, flag7,flag8) == -1 ) {
		return -1;
	}
	srand(time(NULL)); 
	int* dim=new int[4];

	outfile.open(outputpath);
	if(update=="Mean_Frechet"){
		dim=xreadfile(datapath,datasetarraytest);
	}
	else{
		dim=readfile(datapath,datasetarraytest);         ///makw dataset array
	}
	vector<float*> centroids;
	arg=readconfig(configpath);
	dimensions=dim[0];
	maxlength=dim[1];
	K=arg[0];
	L=arg[1];
	k=arg[2];
	auto start = high_resolution_clock::now();
	if(update=="Mean_Frechet"){
		kmeansplusplus(centroids,datasetarraytest,K,dim[0],dim[1] );
	}
	else{
		kmeansplusplus(centroids,datasetarraytest,K,dim[0],dim[1] );
	}
	vector<string>* clusteredvaluesnames = new vector<string>(K);
	// vector<string> clusteredvaluesnames[K];
	if(method=="lsh" || method=="LSH"){
		if(update=="Mean_Frechet"){
			cout << "wrong update\n";
			return -1;
		}
		clusteredvaluesnames=lsh(datasetarraytest,centroids,dimensions,maxlength,K,L,k);
	}
	else if(method=="loyd" || method=="Classic"){
		if(update=="Mean_Frechet"){
			clusteredvaluesnames=loydfrechet(datasetarraytest,centroids,dimensions,dim[3],K,dim[2]);
		}
		else{
			clusteredvaluesnames=loyd(datasetarraytest,centroids,dimensions,maxlength,K);
		}
	}
	else if(method=="LSH_Frechet" || method=="lsh_frechet"){
		clusteredvaluesnames=lshfrechet(datasetarraytest,centroids,dimensions,maxlength,K,L,k,dim[2]);
	}
	else{
		cout << "There is no such method \n";
		return 0;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);

	for(c=0;c<arg[0];c++){ 
		outfile << "CLUSTER-" << c << " {size:" << clusteredvaluesnames[c].size() << ", centroid: ";
		for(j=0;j<dim[1];j++){  
			outfile << centroids[c][j] << " ";
		}
		outfile << endl;
	}
	outfile << "clustering_time: " << duration.count() << endl;
	if(flag8){
		Silhouette(dim[1],arg[0],outfile,datasetarraytest,centroids,clusteredvaluesnames,dim[0]);
	}
	if(flag7){                ///-complete
		for(c=0;c<arg[0];c++){ 
			outfile << "CLUSTER-" << c << " {";
			for(i=0;i<(int)clusteredvaluesnames[c].size();i++){
				outfile << clusteredvaluesnames[c][i] << ", ";
			}
			outfile<< "} \n";
		}
	}
	outfile.close();
}
