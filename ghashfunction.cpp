#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <cmath>
#include <stdlib.h>     
#include <time.h>
#include <fstream>
#include <functional>
#include "ghashfunction.h"

using namespace std;

long int* ghashfunction(datasetarray dataset, int TableSize, int k, int width, hashclass hash) { 
	float* v = hash.getRandomV();
	int* r = hash.getRandomR();
	int t = hash.getRandomShiftT();
	// srand (time(NULL));          //random root
	long int M = 2;                 //big numbers so I need a log int or else I cant store
	for (int i = 1; i < 32; i++) {      //Make M = pow(2,32)-5
		M = M * 2; 
	}
	M = M - 5;
	long int g = 0;                  //start making g(p)
	for (int i = 0; i < k; i++) {	       // k is number for how many h functions
		
		g = g + r[i] * hFunction(dataset.getcoordinates(), v, t, w, width);		//k1h(p)+k2h(p)+......+kkH(p)
	}
	g= modulo(g,M); 
	long int* ID = new long int[2];
	ID[0] = g;
	g= modulo(g,TableSize); 
	if (g < 0) {         //for negative g
		g = -g;
	}
	// v.clear();
	ID[1] = g;
	return ID;
}

long int* ghashfunction(float* dataset, int TableSize, int k, int width, hashclass hash) { 
	float* v = hash.getRandomV();
	int* r = hash.getRandomR();
	int t = hash.getRandomShiftT();
	// srand (time(NULL));          //random root
	long int M = 2;                 //big numbers so I need a log int or else I cant store
	for (int i = 1; i < 32; i++) {      //Make M = pow(2,32)-5
		M = M * 2; 
	}
	M = M - 5;
	long int g = 0;                  //start making g(p)
	for (int i = 0; i < k; i++) {	       // k is number for how many h functions
		
		g = g + r[i] * hFunction(dataset, v, t, w, width);		//k1h(p)+k2h(p)+......+kkH(p)
	}
	g= modulo(g,M); 
	long int* ID = new long int[2];
	ID[0] = g;
	g= modulo(g,TableSize); 
	if (g < 0) {         //for negative g
		g = -g;
	}
	// v.clear();
	ID[1] = g;
	//cout << g << endl;
	return ID;
}

long int* ghashfunction(vector<float> dataset, int TableSize, int k, int width, hashclass hash) { 
	float* v = hash.getRandomV();
	int* r = hash.getRandomR();
	int t = hash.getRandomShiftT();
	// srand (time(NULL));          //random root
	long int M = 2;                 //big numbers so I need a log int or else I cant store
	for (int i = 1; i < 32; i++) {      //Make M = pow(2,32)-5
		M = M * 2; 
	}
	M = M - 5;
	long int g = 0;                  //start making g(p)
	for (int i = 0; i < k; i++) {	       // k is number for how many h functions
		
		g = g + r[i] * hFunction(dataset, v, t, w, width);		//k1h(p)+k2h(p)+......+kkH(p)
	}
	g= modulo(g,M); 
	long int* ID = new long int[2];
	ID[0] = g;
	g= modulo(g,TableSize); 
	if (g < 0) {         //for negative g
		g = -g;
	}
	// v.clear();
	ID[1] = g;
	//cout << g << endl;
	return ID;
}

float innerproduct(vector<float> p, float* v, int d) { // p vector, v random gen vector, d dimension of both vectors
	float inpr = 0;
	for (int i = 0; i < d; i++) {
		inpr = inpr + v[i] * p[i];
	}
	return inpr;
}

float innerproduct(float* p, float* v, int d) { // p vector, v random gen vector, d dimension of both vectors
	float inpr = 0;
	for (int i = 0; i < d; i++) {
		inpr = inpr + v[i] * p[i];
	}
	return inpr;
}


long int hFunction(vector<float> p, float* v, int t,  int window, int d) {
  float inpr = innerproduct(p, v, d);
  long int h = floor( (inpr + t) / window );
  return h;
}

long int hFunction(float* p, float* v, int t,  int window, int d) {
  float inpr = innerproduct(p, v, d);
  long int h = floor( (inpr + t) / window );
  return h;
}

double calcEuclideanDist(vector<float> v1, vector<float> v2,int dimension) {
  double sumOfSquares = 0;
  for (int i = 0; i < dimension; i++) {
    double diff = v1[i] - v2[i];
	sumOfSquares += diff * diff;
  }
  double dist = sqrt(sumOfSquares);
  return dist;
}

double calcEuclideanDist(vector<float*> v1,int j, vector<float> v2,int dimension) {
  double sumOfSquares = 0;
  for (int i = 0; i < dimension; i++) {
    double diff = v1[j][i] - v2[i];
	sumOfSquares += diff * diff;
  }
  double dist = sqrt(sumOfSquares);
  return dist;
}

double calcEuclideanDist(float* v1, vector<float> v2,int dimension) {
  double sumOfSquares = 0;
  for (int i = 0; i < dimension; i++) {
    double diff = v1[i] - v2[i];
	sumOfSquares += diff * diff;
  }
  double dist = sqrt(sumOfSquares);
  return dist;
}

int* readfile(string datapath,vector<datasetarray*>& datasetarraytest){       //function for reading files
	string text;											//I will use this for reading the lines of the file
	int i,j,length,s,width=0;
	char datasetstring[10];                                //I will use this for reading each word/number of the line
	fstream MyReadFile(datapath);                         //reads the file
	length=0;												  // k is size of lines in the file
	while (getline (MyReadFile, text)) {                  //one line at a time
  	  j=0;            
  	  s=0;   
  	  width=0;                    
  	  memset (datasetstring,0,10);
  	  for (i=0 ; i < (int)text.length(); i++){                   //then read the line by character to separate the tabs and get each set separate 
  	  	if (isspace(text[i])==0){
  	  		datasetstring[s]=text[i];               //then save it in an array , where the 0 position is the id name
  	  		s++;                                     //s counts the position of the char array for saving the words/numbers
  	  	}
  	  	else{
  	  		if(j==0){
  	  			datasetarray *d=new datasetarray(datasetstring);
  	  			datasetarraytest.push_back(d);
  	  		}
  	  		else{
  	  			datasetarraytest[length]->addcoordinate(atof(datasetstring));     //this is to turn a string into an int and add it to the allocated space of the class
  	  			width++;
  	  		}
  	  		s=0;
  	  		memset (datasetstring,0,10);                                            //delete space
  	  		j++;
  	  	}
  	  }
  	  datasetarraytest[length]->adddimension(width-1);
  	  length++;
	}
	datasetarraytest[length-1]->adddimension(width);  //it doesnt read the final \n so the last set comes off one value
	int* dim= new int[2];
	dim[0]=length;
	dim[1]=width;
	MyReadFile.close();
	return dim;
}

vector<string> rangesearch(int L, int TableSize, int* dim,vector<hashclass*> datasethashtable,datasetarray queryarray,float R,int k){
	int z;
	double disttemp;
	bool flag4;
	long int* gtest=new long int[2]; 
	vector<string> namebank,namelist;
	for(z=0;z<L;z++){       ///every hash table

		gtest = ghashfunction(queryarray,TableSize,k,dim[1],*datasethashtable[z]);
		
		for (auto temp:datasethashtable[z]->gethashlist(gtest[1])){        //check the bucket
			disttemp = calcEuclideanDist(queryarray.getcoordinates(), temp.dataset->getcoordinates(),dim[1]);   //distance
			flag4=true;
			for(auto tempnamebank: namebank){                                             //here check if the item is already in the list of already checked names
				if(temp.dataset->getname()==tempnamebank){
					flag4=false;
					break;
				}
			}
			if(flag4){
				namebank.push_back(temp.dataset->getname());                                 //save name for future
				if(disttemp<=R){															//if inside range print
					namelist.push_back(temp.dataset->getname()); 
				}
			}
		}   
			
	}
	return namelist;
}

vector<string> rangesearch(int L, int TableSize, int* dim,vector<hashclass*> datasethashtable,datasetarray* queryarray,float R,int k,float M,double delta){  //for frechet
	int z;
	double disttemp;
	bool flag4;
	long int* gtest=new long int[2];
	vector<float> gridaddingvalue;
	vector<string> namebank,namelist;
	for(z=0;z<L;z++){       ///every hash table
		gridaddingvalue = makegrid(*queryarray,delta,datasethashtable[z]->getferchetT(),M);
		gtest = ghashfunction(gridaddingvalue,TableSize,k,dim[1],*datasethashtable[z]);
		
		for (auto temp:datasethashtable[z]->gethashlist(gtest[1])){        //check the bucket
			disttemp = ferchetdistance(temp.dataset, queryarray);   //distance
			flag4=true;
			for(auto tempnamebank: namebank){                                             //here check if the item is already in the list of already checked names
				if(temp.dataset->getname()==tempnamebank){
					flag4=false;
					break;
				}
			}
			if(flag4){
				namebank.push_back(temp.dataset->getname());                                 //save name for future
				if(disttemp<=R){															//if inside range print
					namelist.push_back(temp.dataset->getname()); 
				}
			}
		}   
			
	}
	return namelist;
}

vector<string> rangesearch(int L, int TableSize, int* dim,vector<hashclass*> datasethashtable,datasetarray* queryarray,float R,int k,float M,double delta,vector<double*> frechetdistances,vector<datasetarray*> datasetarraytest,vector<datasetarray*> queryarraytest){
	int z,x,y;
	double disttemp;
	bool flag4;
	long int* gtest=new long int[2];
	vector<float> gridaddingvalue;
	vector<string> namebank,namelist;
	for(z=0;z<L;z++){       ///every hash table
		gridaddingvalue = makegrid(*queryarray,delta,datasethashtable[z]->getferchetT(),M);
		gtest = ghashfunction(gridaddingvalue,TableSize,k,dim[1],*datasethashtable[z]);
		
		for (auto temp:datasethashtable[z]->gethashlist(gtest[1])){        //check the bucket
			x=finddatapos(temp.dataset->getname(),datasetarraytest);
			y=finddatapos(queryarray->getname(),queryarraytest);
			disttemp=frechetdistances[x][y];
			flag4=true;
			for(auto tempnamebank: namebank){                                             //here check if the item is already in the list of already checked names
				if(temp.dataset->getname()==tempnamebank){
					flag4=false;
					break;
				}
			}
			if(flag4){
				namebank.push_back(temp.dataset->getname());                                 //save name for future
				if(disttemp<=R){															//if inside range print
					namelist.push_back(temp.dataset->getname()); 
				}
			}
		}   
			
	}
	return namelist;
}

vector<string> rangesearch(int L, int TableSize, int* dim,vector<hashclass*> datasethashtable,float* queryarray,float R,int k){
	int z;
	double disttemp;
	bool flag4;
	long int* gtest=new long int[2]; 
	vector<string> namebank,namelist;
	for(z=0;z<L;z++){       ///every hash table
		gtest = ghashfunction(queryarray,TableSize,k,dim[1],*datasethashtable[z]);
		
		for (auto temp:datasethashtable[z]->gethashlist(gtest[1])){        //check the bucket
			disttemp = calcEuclideanDist(queryarray, temp.dataset->getcoordinates(),dim[1]);   //distance
			flag4=true;
			for(auto tempnamebank: namebank){                                             //here check if the item is already in the list of already checked names
				if(temp.dataset->getname()==tempnamebank){
					flag4=false;
					break;
				}
			}
			if(flag4){
				namebank.push_back(temp.dataset->getname());                                 //save name for future
				if(disttemp<=R){															//if inside range print
					namelist.push_back(temp.dataset->getname()); 
				}
			}
		}   
			
	}
	return namelist;
}

vector<string> rangesearch(int L, int TableSize, int* dim,vector<hashclass*> datasethashtable,float* queryarray,float Rmin, float Rmax,int k){
	int z;
	double disttemp;
	bool flag4;
	long int* gtest=new long int[2];
	vector<string> namebank,namelist;
	for(z=0;z<L;z++){       ///every hash table
		gtest = ghashfunction(queryarray,TableSize,k,dim[1],*datasethashtable[z]);
		
		for (auto temp:datasethashtable[z]->gethashlist(gtest[1])){        //check the bucket
			disttemp = calcEuclideanDist(queryarray, temp.dataset->getcoordinates(),dim[1]);   //distance
			flag4=true;
			for(auto tempnamebank: namebank){                                             //here check if the item is already in the list of already checked names
				if(temp.dataset->getname()==tempnamebank){
					flag4=false;
					break;
				}
			}
			if(flag4){
				namebank.push_back(temp.dataset->getname());                                 //save name for future
				if(disttemp<Rmax && disttemp>=Rmin){															//if inside range print
					namelist.push_back(temp.dataset->getname()); 
				}
			}
		}   
			
	}
	return namelist;
}

vector<string> rangesearch(int L, int TableSize, int dim,vector<hashclass*> datasethashtable,float* queryarray,float Rmin, float Rmax,int k,double delta,int M){
	int z;
	double disttemp;
	bool flag4;
	long int* gtest=new long int[2];
	vector<float> gridaddingvalue;
	vector<string> namebank,namelist;
	for(z=0;z<L;z++){       ///every hash table
		gridaddingvalue = makegrid(queryarray,dim,delta,datasethashtable[z]->getferchetT(),M);
		gtest = ghashfunction(gridaddingvalue,TableSize,k,dim,*datasethashtable[z]);		
		for (auto temp:datasethashtable[z]->gethashlist(gtest[1])){        //check the bucket
			disttemp = ferchetdistance(queryarray,dim, temp.dataset);   //distance
			flag4=true;
			for(auto tempnamebank: namebank){                                             //here check if the item is already in the list of already checked names
				if(temp.dataset->getname()==tempnamebank){
					flag4=false;
					break;
				}
			}
			if(flag4){
				namebank.push_back(temp.dataset->getname());                                 //save name for future
				if(disttemp<Rmax && disttemp>=Rmin){															//if inside range print
					namelist.push_back(temp.dataset->getname()); 
				}
			}
		}   
			
	}
	return namelist;
}

int* xreadfile(string datapath,vector<datasetarray*>& datasetarraytest){       //this one puts the x time number before each value starting from 0 so [x1,y1,x2,y2....]
	string text;											//I will use this for reading the lines of the file
	int i,j,length,s,width=0,meanwidth=0,maxwidth=0;
	char datasetstring[10];                                //I will use this for reading each word/number of the line
	float M=0;                                               //for padding
	fstream MyReadFile(datapath);                         //reads the file
	length=0;												  // k is size of lines in the file
	while (getline (MyReadFile, text)) {                  //one line at a time
  	  j=0;            
  	  s=0;   
  	  width=0;                    
  	  memset (datasetstring,0,10);
  	  for (i=0 ; i < (int)text.length(); i++){                   //then read the line by character to separate the tabs and get each set separate 
  	  	if (isspace(text[i])==0){
  	  		datasetstring[s]=text[i];               //then save it in an array , where the 0 position is the id name
  	  		s++;                                     //s counts the position of the char array for saving the words/numbers
  	  	}
  	  	else{
  	  		if(j==0){
  	  			datasetarray *d=new datasetarray(datasetstring);
  	  			datasetarraytest.push_back(d);
  	  		}
  	  		else{
  	  			datasetarraytest[length]->addcoordinate(width+1);                    //x value starts from 1 not 0
  	  			datasetarraytest[length]->addcoordinate(atof(datasetstring));     //this is to turn a string into an int and add it to the allocated space of the class
  	  			if(M<atof(datasetstring)){
  	  				M=atof(datasetstring);
  	  			}
  	  			width++;
  	  		}
  	  		s=0;
  	  		memset (datasetstring,0,10);                                            //delete space
  	  		j++;
  	  	}
  	  }
  	  datasetarraytest[length]->adddimension(2*width);
  	  length++;
  	  if(2*width>maxwidth){
  	  	maxwidth=2*width;
  	  }
  	  meanwidth=meanwidth+2*width;
	}
	datasetarraytest[length-1]->adddimension(2*width);  
	int* dim= new int[4];
	dim[0]=length;
	if(length!=0){
		dim[1]=meanwidth/length;
	}
	else{
		dim[1]=0;
	}
	if(M>=dim[1]){            //biggest number in array might be a y or a x
		dim[2]=M;
	}
	else{
		dim[2]=dim[1];
	}
	dim[3]=maxwidth;             //longest curve
	MyReadFile.close();
	return dim;
}

vector<string> rangesearch(int L, int TableSize, int dim,vector<hashclass*> datasethashtable,float* queryarray,float Rmin, float Rmax,int k){
	int z;
	double disttemp;
	bool flag4;
	long int* gtest=new long int[2]; 
	vector<string> namebank,namelist;
	for(z=0;z<L;z++){       ///every hash table
		gtest = ghashfunction(queryarray,TableSize,k,dim,*datasethashtable[z]);
		
		for (auto temp:datasethashtable[z]->gethashlist(gtest[1])){        //check the bucket
			disttemp = calcEuclideanDist(queryarray, temp.dataset->getcoordinates(),dim);   //distance
			flag4=true;
			for(auto tempnamebank: namebank){                                             //here check if the item is already in the list of already checked names
				if(temp.dataset->getname()==tempnamebank){
					flag4=false;
					break;
				}
			}
			if(flag4){
				namebank.push_back(temp.dataset->getname());                                 //save name for future
				if(disttemp<Rmax && disttemp>=Rmin){															//if inside range print
					namelist.push_back(temp.dataset->getname()); 
				}
			}
		}   
			
	}
	// for(auto anme:namelist){
	// 	cout << anme << ", ";
	// }
	//cout << endl;
	return namelist;
}



// ====== MODULO ====== //

// calculates x mod y, where y is a power of 2
int modulo(int x, int y) {
	return x & (y - 1);
}

// calculates (x * y) mod M using (x mod M * y mod M) mod M
int multiModulo(int x, int y, int M) {
	int leftPart = modulo(x, M);
	int rightPart = modulo(y, M);
	return modulo(leftPart * rightPart, M);
}



int finddatapos(string name, vector<datasetarray*> datasetarraytest,int i,int size){
	// int mid;
	// while(size>=i){
	// 	mid = i + (size - i) / 2;
	// 	if (datasetarraytest[mid]->getname() == name){
	//         return mid;
	// 	}
	// 	if (datasetarraytest[mid]->getname() > name){
	//         size=mid-1;
	// 	}
	// 	else{
	// 		i=mid+1;
	// 	}
	// }
	for(i=0;i<size;i++){
		if(name==datasetarraytest[i]->getname()){
			return i;
		}
	}
	return -1;
}

int finddatapos(string name, vector<datasetarray*> datasetarraytest){
	int i;
	for(i=0;i<(int)datasetarraytest.size();i++){
		if(name==datasetarraytest[i]->getname()){
			return i;
		}
	}
	return -1;
}