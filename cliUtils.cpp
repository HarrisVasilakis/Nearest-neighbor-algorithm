#include <iostream>
#include <cstring>
#include <stdio.h>
#include "cliUtils.h"

using namespace std;

int getCliArgs(int argc, char *argv[], string &datapath, string &querypath, string &outputpath, int &k, int &L, int &N, float &R, double& delta , string& algorithm, string& metric) {
	bool datasetNotProvided=true, queryNotProvided=true, outputNotProvided=true, algorithmprovided =true, metricprovided=true;
    if ( argc > 1 ) {
		for ( int i = 1; i < argc; i += 2 ) {

			if ( strcmp( argv[i], "-i" ) == 0 ) {       //-i for path of dataset
				datapath = argv[i+1];
				datasetNotProvided = false;
			}
			else if ( strcmp( argv[i], "-q" ) == 0 ) {    //-q for path to query file
				querypath = argv[i+1];
				queryNotProvided = false;
			}
			else if( strcmp( argv[i], "-o" ) == 0 ) {    //-o for path to output file
				outputpath = argv[i+1];
				outputNotProvided = false;
			}
			else if( strcmp( argv[i], "-k" ) == 0 ) {   //-k for number of LSH functions
 				k = atoi(argv[i+1]);
			}
			else if( strcmp( argv[i], "-L" ) == 0 ) {    //-L for number of hash tables
				L = atoi(argv[i+1]);
			}
			else if( strcmp( argv[i], "-N" ) == 0 ) {    //-N for number of nearest neighbours
				N = atoi(argv[i+1]);
			}
			else if( strcmp( argv[i], "-R" ) == 0 ) {    //-R for number of search radius 
				R = atof(argv[i+1]);
			}
			else if (strcmp(argv[i],"-delta") == 0) {
				delta = atof(argv[i+1]);
			} 
			else if (strcmp(argv[i],"-algorithm") == 0) {
				algorithm = argv[i+1];
				algorithmprovided = false;
			} 
			else if (strcmp(argv[i],"-metric") == 0) {
				metric = argv[i+1];
				metricprovided = false;
			}
			else {
				cout << "Wrong input\n";
				return -1;
			}
		}
	}
    if(datasetNotProvided) {
		cout << "Give dataset file path\n";   //give path of the dataset file 
		cin >> datapath;                  // e.g. :   dataset.txt
	}
	if(queryNotProvided) {
		cout << "Give query file path\n";   
		cin >> querypath;                  
	}
	if(outputNotProvided) {
		cout << "Give output file path\n";   
		cin >> outputpath;                  
	}
	if(algorithmprovided) {
		cout << "Give algorithm method\n";  
		cin >> algorithm;                 
	}
	if(metricprovided && (algorithm=="Frechet" || algorithm=="frechet")) {
		cout << "Give metric\n";  
		cin >> metric;                  
	}
    return 0;
}


int getCliArgs(int argc, char *argv[], string &datapath, string &configpath, string &outputpath, string& method, string& update, bool& flag7,bool& flag8){        ///clustering
	bool flag1=true,flag2=true,flag3=true,flag9=true,flag10=true;
	if(argc>1){
		for(int i=1; i<argc; i++){
			if(strcmp(argv[i],"-i")==0){       //-i for path of dataset
				datapath=argv[i+1];
				flag1=false;
			}
			else if(strcmp(argv[i],"-c")==0){    //-c for path to configuration file
				configpath=argv[i+1];
				flag2=false;
			}
			else if(strcmp(argv[i],"-o")==0){    //-o for path to output file
				outputpath=argv[i+1];
				flag3=false;
			}
			else if(strcmp(argv[i],"-complete")==0){    //-complete for printing
				flag7=true;
			}
			else if(strcmp(argv[i],"-silhouette")==0){
				flag8=true;
			}
			else if(strcmp(argv[i],"-update")==0){
				flag9=false;
				update=argv[i+1];
			}
			else if(strcmp(argv[i],"-assignment")==0){
				flag10=false;
				method=argv[i+1];
			}
		}
	}
	if(flag1){
		cout << "Give dataset file path\n";   //give path of the dataset file 
		cin >> datapath;                  // e.g. :   dataset.txt
	}
	if(flag2){
		cout << "Give configuration file path\n";   
		cin >> configpath;                  
	}
	if(flag3){
		cout << "Give output file path\n";   
		cin >> outputpath;                  
	}
	if(flag9){
		cout << "Give Mean_Vector or Mean_Frechet\n";
		cin >> update; 
	}
	if(flag10){
		cout << "Give method of assignment\n";
	    cin >> method;
	}
	if(method=="LSH_Frechet" && update=="Mean_Vector"){
		cout << "wrong input\n";
		return -1;
	}
	if(method=="LSH_Vector" && update=="Mean_Frechet"){
		cout << "wrong input\n";
		return -1;
	}
	return 0;
}
