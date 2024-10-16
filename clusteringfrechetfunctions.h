#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <list>
#include "ghashfunction.h"
#include "frechetfunctions.h"

using namespace std;

vector<float*> newmeancurve(vector<float*> centroids,vector<string>* namevalues,int maxlength,int K,vector<datasetarray*> datasetarraytest,int M );
vector<float> meancurve(string namevalues,vector<datasetarray*> datasetarraytest);
vector<float> meancurve(vector<float> value1,vector<float> value2,int maxlength,int M);
vector<float> createbtree(vector<string>& names,int h,int n,vector<datasetarray*> datasetarraytest,int M,int maxlength);
int heightnum(int a);