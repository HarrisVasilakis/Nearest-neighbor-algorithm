#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <list>
#include "clusteringfrechetfunctions.h"

using namespace std;



vector<float> createbtree(vector<string>& names,int h,int n,vector<datasetarray*> datasetarraytest,int M,int maxlength){          //h=current height  ,  n=number of leaves  
	vector<float> curveright,curveleft;
	if(heightnum(h)>=2*n-1){             //2*n-1 is number of nodes of "tree"
		curveright=meancurve(names[0],datasetarraytest);  
		names.erase(names.begin()+0);
		return curveright;                                 ///meancurve actually
	}
	curveright=createbtree(names,h+1,n,datasetarraytest,M,maxlength);
	if((int)names.size()!=0){                                         ///check if the left branch exists cause its not necesarily a full btree
		curveleft=createbtree(names,h+1,n,datasetarraytest,M,maxlength);
		curveright=meancurve(curveright,curveleft,maxlength,M); 
	}
	if(h==0){
		// cout <<  " 1111111111111| " << (int)curveright.size() << "<" << maxlength << endl;
		// if((int)curveright.size()>maxlength){
		// 	curveright=filtering(curveright,M);
		// }
		if((int)curveright.size()>maxlength){
			for(int i=(int)curveright.size()-1;i>maxlength-1;i--){
				curveright.erase(curveright.begin()+i);
			}
		}
		if((int)curveright.size()<maxlength){                         ///or fill it if it is shorter
			curveright=padding(curveright,(float) M,maxlength);
		}
		// cout << "5655555555555555555555555555| " << (int)curveright.size() << "<" << maxlength << endl;
	}
	return curveright;
}

vector<float*> newmeancurve(vector<float*> centroids,vector<string>* namevalues,int maxlength,int K,vector<datasetarray*> datasetarraytest,int M ){
	int i,j;
	float* tempcentroid=new float[2*maxlength];
	vector<float*> newcentroids;
	vector<string> tempnames;
	vector<float> meancurve;
	for(i=0;i<K;i++){          ///calc new curves
		tempnames.clear();
		tempnames=namevalues[i];
		if((int)tempnames.size()!=0){       //maybe a cluster has no values
			meancurve.clear();
			meancurve=createbtree(tempnames,0,(int)tempnames.size(),datasetarraytest,M,maxlength);
			for(j=0;j<(int)meancurve.size();j++){
				tempcentroid[j]=meancurve[j];
			}
			newcentroids.push_back(tempcentroid);
		}
		else{
			newcentroids.push_back(centroids[i]);    //then get old centroid, it doesn't change
		}
	}
	return newcentroids;
}

vector<float> meancurve(string namevalues,vector<datasetarray*> datasetarraytest){         ///for leaf nodes get the curve
	int i;
	i=finddatapos(namevalues,datasetarraytest);
	return datasetarraytest[i]->getcoordinates();
}

vector<float> meancurve(vector<float> value1,vector<float> value2,int maxlength,int M){   //calc the mean curve 
	int i,j;
	double dist;
	vector<float> meancurve,tempmeancurve;
	vector<double*> ddarray=ferchetdistancearray(value1,value2);
	i=(int)value1.size()-1;
	j=(int)value2.size()-1;
	while(i>0 || j>0){                                          ///get the frechet array from dynamic programming and find the best pairs of the curves
		tempmeancurve.push_back((value1[i]+value2[j])/2);       //for each pair find the mean
		if(i-1>=0 && j-1>=0){
			tempmeancurve.push_back((value1[--i]+value2[--j])/2);
		}
		if(i!=0 && j!=0){
			dist=findmin(ddarray[i][j-1],ddarray[i-1][j],ddarray[i-1][j-1]);
			if(dist==ddarray[i][j-1]){                 //traverse the array until you find the first position
				j--;
			}
			else if(dist==ddarray[i-1][j]){
				i--;
			}
			else{
				i--;
				j--;
			}
		}
		else if(i!=0){
			i--;
		}
		else{
			j--;
		}
	}
	for(i=(int)tempmeancurve.size()-1;i>=0;i--){        ///do the filtering if the newcurve is longer than what we want
		meancurve.push_back(tempmeancurve[i]);
	}
	// cout <<  " 1111111111111| " << (int)meancurve.size() << "<" << maxlength << endl;
	// // if((int)meancurve.size()>maxlength){
	// // 	meancurve=filtering(meancurve,M);
	// // }
	// if((int)meancurve.size()>maxlength){
	// 	for(i=(int)meancurve.size()-1;i>maxlength-1;i--){
	// 		meancurve.erase(meancurve.begin()+i);
	// 	}
	// }
	// cout << (int)meancurve.size() << "<" << maxlength << endl;
	// if((int)meancurve.size()<maxlength){                         ///or fill it if it is shorter
	// 	meancurve=padding(meancurve,(float) M,maxlength);
	// }
	// cout << "5655555555555555555555555555| " << (int)meancurve.size() << "<" << maxlength << endl;
	return meancurve;
}

int heightnum(int a){      ///returns the number of nodes if the tree was full
	int i,h=0;
	for(i=0;i<=a;i++){
		h=h+pow(2,a);
	}
	return h;
}