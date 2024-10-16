#ifndef _LSHHELPER_H_
#define _LSHHELPER_H_

#include <vector>
#include <cstdlib>
#include <fstream>
#include <list>
#include "class.h"
#include "ghashfunction.h"
#include "frechetfunctions.h"

using namespace std;

void nearestneighbours(vector<hashclass*> datasethashtable,long int ID, int bucket ,vector<float> query,int length,double* dist,int z,int N,string* neighbourname);
void nearestneighbours(vector<hashclass*> datasethashtable, int bucket ,vector<float> query,int length,double* dist,int z,int N,string* neighbourname);
void nearestneighbours(vector<hashclass*> datasethashtable,long int ID, int bucket ,datasetarray* query,int length,double* dist,int z,int N,string* neighbourname,vector<float> gridaddingvalue,double M,double delta);
void nearestneighbours(vector<hashclass*> datasethashtable, int bucket ,datasetarray* query,int length,double* dist,int z,int N,string* neighbourname);
void nearestneighbours(vector<hashclass*> datasethashtable,long int ID, int bucket ,datasetarray* query,int length,double* dist,int z,int N,string* neighbourname,vector<float> gridaddingvalue,double M,double delta,vector<double*> frechetdistances,vector<datasetarray*> datasetarraytest,vector<datasetarray*> queryarray);
void nearestneighbours(vector<hashclass*> datasethashtable, int bucket ,datasetarray* query,int length,double* dist,int z,int N,string* neighbourname,vector<double*> frechetdistances,vector<datasetarray*> datasetarraytest,vector<datasetarray*> queryarray);
double exhaustivesearch(vector<double> truedist,int a,vector<float> query,vector<datasetarray*> datasetarraytest,int length,int lines);
double exhaustivesearch(vector<double> truedist,int a,datasetarray* query,vector<datasetarray*> datasetarraytest,int lines,vector<double*> frechetdistances,vector<datasetarray*> queryarray);
int minsearch(vector<int> min,int a,double* dist,int L);
void lsh(int k,int L,int N,float R,string datapath,string querypath,string outputpath);
void frechet(int k,int L,int N,float R,string datapath,string querypath,string outputpath,double delta);
double exhaustivesearch(vector<double> truedist,int a,datasetarray* query,vector<datasetarray*> datasetarraytest,int lines);
int aresame(vector<float> a , vector<float> b);
int ishashtableempty(vector<hashclass*> datasethashtable,int L,int TableSize);




#endif