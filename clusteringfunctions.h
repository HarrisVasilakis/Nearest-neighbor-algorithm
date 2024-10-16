#ifndef _CLUSTERINGFUNCTIONS_H_
#define _CLUSTERINGFUNCTIONS_H_

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <list>
#include <random>
#include <time.h>
#include "ghashfunction.h"


using namespace std;

int* readconfig(string path);
void kmeansplusplus(vector<float*> &centroids,vector<datasetarray*> datasetarraytest,int K,int dim,int maxlength );
void kmeansplusplus(vector<float*> &centroids,vector<datasetarray*> datasetarraytest,int K,int dim,int maxlength ,int M);
vector<string>* lsh(vector<datasetarray*> datasetarraytest,vector<float*>& centroids,int dimensions,int maxlength,int K,int L, int k);
vector<string>* loyd(vector<datasetarray*> datasetarraytest,vector<float*>& centroids,int dimensions,int maxlength,int K);
void Silhouette(int length,int K,ofstream& outfile,vector<datasetarray*> datasetarraytest,vector<float*> centroids,vector<string>* clusteredvaluesnames,int dimensions);
vector<string>* loydfrechet(vector<datasetarray*> datasetarraytest,vector<float*>& centroids,int dimensions,int maxlength,int K,int M);
vector<string>* lshfrechet(vector<datasetarray*> datasetarraytest,vector<float*>& centroids,int dimensions,int maxlength,int K,int L, int k,int M);


#endif