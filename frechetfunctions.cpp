#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <list>
#include <random>
#include "frechetfunctions.h"

using namespace std;

double ferchetdistance(datasetarray* a, datasetarray* b){   
	double ddarray[a->getdimension()/2][b->getdimension()/2];
	double dist,maxdist;
	int i,j;
	if(b->getdimension()>a->getdimension()){                     //to fit in the array
		for (i=1;i<a->getdimension();i=i+2){
			for(j=i;j<b->getdimension();j=j+2){                 //go horizontally
				if(i==1 && j==1){
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j);
				}
				else if(i==1 && j>1){
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j,ddarray[i/2][j/2-1]); 
				}
				else{
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j,ddarray[i/2][j/2-1],ddarray[i/2-1][j/2],ddarray[i/2-1][j/2-1]);    
				}
			}
			for(j=i+1;j<a->getdimension();j=j+2){                //go vertically
				if(i==1 && j>1){
					ddarray[j/2][i/2]=ferchethelper(a,b,j,i,ddarray[j/2-1][i/2]);  
				}
				else{
					ddarray[j/2][i/2]=ferchethelper(a,b,j,i,ddarray[j/2-1][i/2],ddarray[j/2][i/2-1],ddarray[j/2-1][i/2-1]);
				}
			}
		}
	}
	else{
		for (j=1;j<b->getdimension();j=j+2){
			for(i=j;i<a->getdimension();i=i+2){                 //go horizontally
				if(i==1 && j==1){
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j);
				}
				else if(j==1 && i>1){
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j,ddarray[i/2][j/2-1]);
				}
				else{
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j,ddarray[i/2][j/2-1],ddarray[i/2-1][j/2],ddarray[i/2-1][j/2-1]);
				}
			}
			for(i=j+1;i<b->getdimension();i=i+2){                //go vertically
				if(j==1 && i>1){
					ddarray[j/2][i/2]=ferchethelper(a,b,j,i,ddarray[j/2][i/2-1]); 
				}
				else{
					ddarray[j/2][i/2]=ferchethelper(a,b,j,i,ddarray[j/2-1][i/2],ddarray[j/2][i/2-1],ddarray[j/2-1][i/2-1]);
				}
			}
		}
	}
	i=a->getdimension()/2-1;
	j=b->getdimension()/2-1;
	maxdist=ddarray[i][j];
	while(i!=0 || j!=0){                           ///finds the smallest value path and the max distance
		if(i!=0 && j!=0){
			dist=findmin(ddarray[i][j-1],ddarray[i-1][j],ddarray[i-1][j-1]);
			if(dist==ddarray[i][j-1]){
				j--;
			}
			else if(dist==ddarray[i-1][j]){
				i--;
			}
			else{
				i--;
				j--;
			}
			if(dist>maxdist){
				maxdist=dist;
			}
		}
		else if(i!=0){
			if(ddarray[i-1][j]>maxdist){
				maxdist=ddarray[i-1][j];
			}
			i--;
		}
		else{
			if(ddarray[i][j-1]>maxdist){
				maxdist=ddarray[i][j-1];
			}
			j--;
		}
	}
	return maxdist;
}

double ferchetdistance(float* a,int length, datasetarray* b){
	double ddarray[length/2][b->getdimension()/2];
	double dist,maxdist;
	int i,j;
	if(b->getdimension()>length){                     //to fit in the array
		for (i=1;i<length;i=i+2){
			for(j=i;j<b->getdimension();j=j+2){                 //go horizontally
				if(i==1 && j==1){
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j);
				}
				else if(i==1 && j>1){
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j,ddarray[i/2][j/2-1]); 
				}
				else{
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j,ddarray[i/2][j/2-1],ddarray[i/2-1][j/2],ddarray[i/2-1][j/2-1]);    
				}
			}
			for(j=i+1;j<length;j=j+2){                //go vertically
				if(i==1 && j>1){
					ddarray[j/2][i/2]=ferchethelper(a,b,j,i,ddarray[j/2-1][i/2]);  
				}
				else{
					ddarray[j/2][i/2]=ferchethelper(a,b,j,i,ddarray[j/2-1][i/2],ddarray[j/2][i/2-1],ddarray[j/2-1][i/2-1]);
				}
			}
		}
	}
	else{
		for (j=1;j<b->getdimension();j=j+2){
			for(i=j;i<length;i=i+2){                 //go horizontally
				if(i==1 && j==1){
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j);
				}
				else if(j==1 && i>1){
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j,ddarray[i/2][j/2-1]);
				}
				else{
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j,ddarray[i/2][j/2-1],ddarray[i/2-1][j/2],ddarray[i/2-1][j/2-1]);
				}
			}
			for(i=j+1;i<b->getdimension();i=i+2){                //go vertically
				if(j==1 && i>1){
					ddarray[j/2][i/2]=ferchethelper(a,b,j,i,ddarray[j/2][i/2-1]); 
				}
				else{
					ddarray[j/2][i/2]=ferchethelper(a,b,j,i,ddarray[j/2-1][i/2],ddarray[j/2][i/2-1],ddarray[j/2-1][i/2-1]);
				}
			}
		}
	}
	i=length/2-1;
	j=b->getdimension()/2-1;
	maxdist=ddarray[i][j];
	while(i!=0 || j!=0){                           ///finds the smallest value path and the max distance
		if(i!=0 && j!=0){
			dist=findmin(ddarray[i][j-1],ddarray[i-1][j],ddarray[i-1][j-1]);
			if(dist==ddarray[i][j-1]){
				j--;
			}
			else if(dist==ddarray[i-1][j]){
				i--;
			}
			else{
				i--;
				j--;
			}
			if(dist>maxdist){
				maxdist=dist;
			}
		}
		else if(i!=0){
			if(ddarray[i-1][j]>maxdist){
				maxdist=ddarray[i-1][j];
			}
			i--;
		}
		else{
			if(ddarray[i][j-1]>maxdist){
				maxdist=ddarray[i][j-1];
			}
			j--;
		}
	}
	return maxdist;
}

vector<double*> ferchetdistancearray(datasetarray* a, datasetarray* b){
	vector<double*> ddarray;
	double* temp;
	int i,j;
	for(i=0;i<a->getdimension()/2;i++){
		temp=new double[b->getdimension()/2];
		ddarray.push_back(temp);
	}

	if(b->getdimension()>a->getdimension()){                     //to fit in the array
		for (i=1;i<a->getdimension();i=i+2){
			for(j=i;j<b->getdimension();j=j+2){                 //go horizontally
				if(i==1 && j==1){
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j);
				}
				else if(i==1 && j>1){
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j,ddarray[i/2][j/2-1]); 
				}
				else{
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j,ddarray[i/2][j/2-1],ddarray[i/2-1][j/2],ddarray[i/2-1][j/2-1]);    
				}
			}
			for(j=i+1;j<a->getdimension();j=j+2){                //go vertically
				if(i==1 && j>1){
					ddarray[j/2][i/2]=ferchethelper(a,b,j,i,ddarray[j/2-1][i/2]);  
				}
				else{
					ddarray[j/2][i/2]=ferchethelper(a,b,j,i,ddarray[j/2-1][i/2],ddarray[j/2][i/2-1],ddarray[j/2-1][i/2-1]);
				}
			}
		}
	}
	else{
		for (j=1;j<b->getdimension();j=j+2){
			for(i=j;i<a->getdimension();i=i+2){                 //go horizontally
				if(i==1 && j==1){
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j);
				}
				else if(j==1 && i>1){
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j,ddarray[i/2][j/2-1]);
				}
				else{
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j,ddarray[i/2][j/2-1],ddarray[i/2-1][j/2],ddarray[i/2-1][j/2-1]);
				}
			}
			for(i=j+1;i<b->getdimension();i=i+2){                //go vertically
				if(j==1 && i>1){
					ddarray[j/2][i/2]=ferchethelper(a,b,j,i,ddarray[j/2][i/2-1]); 
				}
				else{
					ddarray[j/2][i/2]=ferchethelper(a,b,j,i,ddarray[j/2-1][i/2],ddarray[j/2][i/2-1],ddarray[j/2-1][i/2-1]);
				}
			}
		}
	}
	return ddarray;
}

vector<double*> ferchetdistancearray(vector<float> a, vector<float> b){
	vector<double*> ddarray;
	double* temp;
	int i,j;
	for(i=0;i<(int)a.size();i++){
		temp=new double[(int)b.size()];
		ddarray.push_back(temp);
	}

	if((int)b.size()>(int)a.size()){                     //to fit in the array
		for (i=0;i<(int)a.size();i++){
			for(j=i;j<(int)b.size();j++){                 //go horizontally
				if(i==0 && j==0){
					ddarray[i][j]=ferchethelper(a,b,i,j);
				}
				else if(i==0 && j>0){
					ddarray[i][j]=ferchethelper(a,b,i,j,ddarray[i][j-1]); 
				}
				else{
					ddarray[i][j]=ferchethelper(a,b,i,j,ddarray[i][j-1],ddarray[i-1][j],ddarray[i-1][j-1]);    
				}
			}
			for(j=i+1;j<(int)a.size();j++){                //go vertically
				if(i==0 && j>0){
					ddarray[j][i]=ferchethelper(a,b,j,i,ddarray[j-1][i]);  
				}
				else{
					ddarray[j][i]=ferchethelper(a,b,j,i,ddarray[j-1][i],ddarray[j][i-1],ddarray[j-1][i-1]);
				}
			}
		}
	}
	else{
		for (j=0;j<(int)b.size();j++){
			for(i=j;i<(int)a.size();i++){                 //go horizontally
				if(i==0 && j==0){
					ddarray[i/2][j/2]=ferchethelper(a,b,i,j);
				}
				else if(j==0 && i>0){
					ddarray[i][j]=ferchethelper(a,b,i,j,ddarray[i][j-1]);
				}
				else{
					ddarray[i][j]=ferchethelper(a,b,i,j,ddarray[i][j-1],ddarray[i-1][j],ddarray[i-1][j-1]);
				}
			}
			for(i=j+1;i<(int)b.size();i=i+2){                //go vertically
				if(j==0 && i>0){
					ddarray[j][i]=ferchethelper(a,b,j,i,ddarray[j][i-1]); 
				}
				else{
					ddarray[j][i]=ferchethelper(a,b,j,i,ddarray[j-1][i],ddarray[j][i-1],ddarray[j-1][i-1]);
				}
			}
		}
	}
	return ddarray;
}

double ferchetdistance(vector<double*> ddarray,int a , int b){
	double dist,maxdist;
	int i,j;
	i=a;
	j=b;
	maxdist=ddarray[i][j];
	while(i!=0 || j!=0){                           ///finds the smallest value path and the max distance
		if(i!=0 && j!=0){
			dist=findmin(ddarray[i][j-1],ddarray[i-1][j],ddarray[i-1][j-1]);
			if(dist==ddarray[i][j-1]){
				j--;
			}
			else if(dist==ddarray[i-1][j]){
				i--;
			}
			else{
				i--;
				j--;
			}
			if(dist>maxdist){
				maxdist=dist;
			}
		}
		else if(i!=0){
			if(ddarray[i-1][j]>maxdist){
				maxdist=ddarray[i-1][j];
			}
			i--;
		}
		else{
			if(ddarray[i][j-1]>maxdist){
				maxdist=ddarray[i][j-1];
			}
			j--;
		}
	}
	return maxdist;
}

double ferchethelper(datasetarray* a, datasetarray* b,int i,int j,double x,double y,double xy){
	vector<float> a2,b2;
	double dist,mindist,maxdist;
	a2.push_back(a->getcoordinates()[i]);            ///vector of only (x,y)
	a2.push_back(a->getcoordinates()[i+1]);
	b2.push_back(b->getcoordinates()[j]);
	b2.push_back(b->getcoordinates()[j+1]);
	dist=calcEuclideanDist(a2,b2, 2);         ///for (0,0) find only the euklidean distance sqrt((x1-x2)^2+(y1-y2)^2)
	mindist=findmin(x,y,xy);
	maxdist=findmax(mindist,dist);
	return maxdist;
}

double ferchethelper(datasetarray* a, datasetarray* b,int i,int j,double x){
	vector<float> a2,b2;
	double dist,maxdist;
	a2.push_back(a->getcoordinates()[i]);            ///vector of only (x,y)
	a2.push_back(a->getcoordinates()[i+1]);
	b2.push_back(b->getcoordinates()[j]);
	b2.push_back(b->getcoordinates()[j+1]);
	dist=calcEuclideanDist(a2,b2, 2);         ///for (0,0) find only the euklidean distance sqrt((x1-x2)^2+(y1-y2)^2)
	maxdist=findmax(x,dist);
	return maxdist;
}

double ferchethelper(datasetarray* a, datasetarray* b,int i,int j){
	vector<float> a2,b2;
	double dist;
	a2.push_back(a->getcoordinates()[i]);            ///vector of only (x,y)
	a2.push_back(a->getcoordinates()[i+1]);
	b2.push_back(b->getcoordinates()[j]);
	b2.push_back(b->getcoordinates()[j+1]);
	dist=calcEuclideanDist(a2,b2, 2);         ///for (0,0) find only the euklidean distance sqrt((x1-x2)^2+(y1-y2)^2)
	return dist;
}

double ferchethelper(float* a, datasetarray* b,int i,int j,double x,double y,double xy){
	vector<float> a2,b2;
	double dist,mindist,maxdist;
	a2.push_back(a[i]);            ///vector of only (x,y)
	a2.push_back(a[i+1]);
	b2.push_back(b->getcoordinates()[j]);
	b2.push_back(b->getcoordinates()[j+1]);
	dist=calcEuclideanDist(a2,b2, 2);         ///for (0,0) find only the euklidean distance sqrt((x1-x2)^2+(y1-y2)^2)
	mindist=findmin(x,y,xy);
	maxdist=findmax(mindist,dist);
	return maxdist;
}

double ferchethelper(float* a, datasetarray* b,int i,int j,double x){
	vector<float> a2,b2;
	double dist,maxdist;
	a2.push_back(a[i]);            ///vector of only (x,y)
	a2.push_back(a[i+1]);
	b2.push_back(b->getcoordinates()[j]);
	b2.push_back(b->getcoordinates()[j+1]);
	dist=calcEuclideanDist(a2,b2, 2);         ///for (0,0) find only the euklidean distance sqrt((x1-x2)^2+(y1-y2)^2)
	maxdist=findmax(x,dist);
	return maxdist;
}

double ferchethelper(float* a, datasetarray* b,int i,int j){
	vector<float> a2,b2;
	double dist;
	a2.push_back(a[i]);            ///vector of only (x,y)
	a2.push_back(a[i+1]);
	b2.push_back(b->getcoordinates()[j]);
	b2.push_back(b->getcoordinates()[j+1]);
	dist=calcEuclideanDist(a2,b2, 2);         ///for (0,0) find only the euklidean distance sqrt((x1-x2)^2+(y1-y2)^2)
	return dist;
}

double ferchethelper(vector<float> a, vector<float> b,int i,int j,double x,double y,double xy){
	vector<float> a2,b2;
	double dist,mindist,maxdist;
	a2.push_back(a[i]);            ///vector of only (x,y)
	a2.push_back(a[i+1]);
	b2.push_back(b[j]);
	b2.push_back(b[j+1]);
	dist=calcEuclideanDist(a2,b2, 2);         ///for (0,0) find only the euklidean distance sqrt((x1-x2)^2+(y1-y2)^2)
	mindist=findmin(x,y,xy);
	maxdist=findmax(mindist,dist);
	return maxdist;
}

double ferchethelper(vector<float> a, vector<float> b,int i,int j,double x){
	vector<float> a2,b2;
	double dist,maxdist;
	a2.push_back(a[i]);            ///vector of only (x,y)
	a2.push_back(a[i+1]);
	b2.push_back(b[j]);
	b2.push_back(b[j+1]);
	dist=calcEuclideanDist(a2,b2, 2);         ///for (0,0) find only the euklidean distance sqrt((x1-x2)^2+(y1-y2)^2)
	maxdist=findmax(x,dist);
	return maxdist;
}

double ferchethelper(vector<float> a, vector<float> b,int i,int j){
	vector<float> a2,b2;
	double dist;
	a2.push_back(a[i]);            ///vector of only (x,y)
	a2.push_back(a[i+1]);
	b2.push_back(b[j]);
	b2.push_back(b[j+1]);
	dist=calcEuclideanDist(a2,b2, 2);         ///for (0,0) find only the euklidean distance sqrt((x1-x2)^2+(y1-y2)^2)
	return dist;
}

double findmax(double a,double b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}

int findmax(int a,int b){
	if(a>b){
		return a;
	}
	else{
		return b;
	}
}

double findmin(double a, double b, double c){
	double min;
	min =a;
	if(min>b){
		min=b;
	}
	if(min>c){
		min =c;
	}
	return min;
}


vector<float> filtering(vector<float> a ,int e){
	int j;
	for(j=1;j<(int)a.size()-4;j++){
		if(a[j]>a[j+2] && a[j+2]>a[j+4]){
			a.erase(a.begin()+(j+1));
			a.erase(a.begin()+(j+1));
		}
		else if(a[j]<a[j+2] && a[j+2]<a[j+4]){
			a.erase(a.begin()+(j+1));
			a.erase(a.begin()+(j+1));
		}
		if(a[j]>a[j+2]){
			if(a[j]-a[j+2]<e && a[j+2]-a[j+4]<e){
				a.erase(a.begin()+(j+1));
				a.erase(a.begin()+(j+1));
			}
		}
		else if(a[j]<a[j+2]){
			if(a[j+2]-a[j]<e && a[j+4]-a[j+2]<e){
				a.erase(a.begin()+(j+1));
				a.erase(a.begin()+(j+1));
			}
		}
	}
	return a;
}

float snapping(double delta,float x,float t){         ///returns position to grid that x snaps to
	float snap;	
	snap=floor((x-t)/delta + 1/2)*delta + t;
	return snap;
}



float makerandomt(double delta){
	random_device device_random_;
	default_random_engine generator(device_random_()); 	//random root
  	normal_distribution<float> distribution(0, delta);
  	float t=distribution(generator);
  	while(t>=delta){
  		t=distribution(generator);
  	}
  	if(t<0){
		t=-t;
	}
  	return t;
}

vector<float> makegrid(datasetarray a, double delta, float t,float M){
	int i;
	float gridnum1,gridnum2;
	vector<float> gridvector;
	for(i=0;i<a.getdimension();i=i+2){
		gridnum1=snapping(delta,a.getcoordinates()[i],t);
		gridnum2=snapping(delta,a.getcoordinates()[i+1],t);
		if(i==0 || gridvector[i-1]!=gridnum2){
			gridvector.push_back(gridnum1);
			gridvector.push_back(gridnum2);
		}		
	}
	gridvector=padding(gridvector,M,a.getdimension());
	return gridvector;
}

vector<float> padding(vector<float> a,float M,int size){

	for(int i=(int)a.size();i<size;i++){
		a.push_back(M);
	}
	return a;
}

float* padding(float* a,float M,int start,int size){
	for(int i=start;i<size;i++){
		a[i]=M;
	}
	return a;
}

vector<float> makegrid(float* a,int dim, double delta, float t,float M){
	int i;
	float gridnum1,gridnum2;
	vector<float> gridvector;
	for(i=0;i<dim;i=i+2){
		gridnum1=snapping(delta,a[i],t);
		gridnum2=snapping(delta,a[i+1],t);
		if(i==0 || gridvector[i-1]!=gridnum2){
			gridvector.push_back(gridnum1);
			gridvector.push_back(gridnum2);
		}		
	}
	gridvector=padding(gridvector,M,dim);
	return gridvector;
}

