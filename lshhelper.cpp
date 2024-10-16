#include <vector>
#include <cstdlib>
#include <fstream>
#include <list>
#include <chrono>
#include "lshhelper.h"
#include "frechetfunctions.h"

using namespace std;
using namespace std::chrono;

void nearestneighbours(vector<hashclass*> datasethashtable,long int ID, int bucket ,vector<float> query,int length,double* dist,int z,int N,string* neighbourname){
	int maxj,j;
	bool flag;
	double disttemp;
	for (auto temp:datasethashtable[z]->gethashlist(bucket)){        //check the bucket
		
		if (ID==temp.IDp){                      //check if they are close 
			disttemp = calcEuclideanDist(query, temp.dataset->getcoordinates(), length);   //distance
			flag=true;
			maxj = -1;
			for(j = 0; j < N * z; j++) {                                             //here check if the item is already in the list from other hashtable
				if(temp.dataset->getname()==neighbourname[N*z+j]){
					flag=false;
					break;
				}
			}
			if(flag){
				flag=false;
				for(j=0;j<N;j++){                                   //this for is for checking the N closest neighbours
					if(dist[N*z+j]==-1){                                     //now compare and save the closest neighbour so i can print them on the output file later
						dist[N*z+j]=disttemp;                             //if we haven't found N closest neighbours then count this one and stop the loop
						neighbourname[N*z+j]=temp.dataset->getname();
						flag=false;
						break;
					}
					else if(disttemp<dist[N*z+j]){                              //if there is a closest neighbour that is further than the one we have
						flag=true;
						if(maxj==-1){                                            //save him
							maxj=j;
						}
						else if(dist[N*z+j]>dist[N*z+maxj]){                     //and see if one of the closest neighbours we have has longer distance than the one we saved
							maxj=j;													//so if it does save him instead so we only save the closest of the closest neighbours
						}
					}
				}
				if(flag){															//in the end if all the N closest neighbours positions are filled and we found an even closer neighbour
					dist[N*z+maxj]=disttemp;                                             //change the position
					neighbourname[N*z+maxj]=temp.dataset->getname();
				}
			}
		}
	}
}

void nearestneighbours(vector<hashclass*> datasethashtable,long int ID, int bucket ,datasetarray* query,int length,double* dist,int z,int N,string* neighbourname,vector<float> gridaddingvalue,double M,double delta){    ///for ferchet
	int maxj,j;
	bool flag;
	double disttemp;
	vector<float> gridhashvalue;
	for (auto temp:datasethashtable[z]->gethashlist(bucket)){        //check the bucket		
		gridhashvalue=makegrid(*temp.dataset,delta,datasethashtable[z]->getRandomShiftT(),M);
		j=aresame(gridhashvalue,gridaddingvalue);
		if (ID==temp.IDp || j){                      //check if they are close 
			disttemp=ferchetdistance(temp.dataset, query);
			flag=true;
			maxj = -1;
			for(j = 0; j < N * z; j++) {                                             //here check if the item is already in the list from other hashtable
				if(temp.dataset->getname()==neighbourname[N*z+j]){
					flag=false;
					break;
				}
			}
			if(flag){
				flag=false;
				for(j=0;j<N;j++){                                   //this for is for checking the N closest neighbours
					if(dist[N*z+j]==-1){                                     //now compare and save the closest neighbour so i can print them on the output file later
						dist[N*z+j]=disttemp;                             //if we haven't found N closest neighbours then count this one and stop the loop
						neighbourname[N*z+j]=temp.dataset->getname();
						flag=false;
						break;
					}
					else if(disttemp<dist[N*z+j]){                              //if there is a closest neighbour that is further than the one we have
						flag=true;
						if(maxj==-1){                                            //save him
							maxj=j;
						}
						else if(dist[N*z+j]>dist[N*z+maxj]){                     //and see if one of the closest neighbours we have has longer distance than the one we saved
							maxj=j;													//so if it does save him instead so we only save the closest of the closest neighbours
						}
					}
				}
				if(flag){															//in the end if all the N closest neighbours positions are filled and we found an even closer neighbour
					dist[N*z+maxj]=disttemp;                                             //change the position
					neighbourname[N*z+maxj]=temp.dataset->getname();
				}
			}
		}
	}
}

void nearestneighbours(vector<hashclass*> datasethashtable,long int ID, int bucket ,datasetarray* query,int length,double* dist,int z,int N,string* neighbourname,vector<float> gridaddingvalue,double M,double delta,vector<double*> frechetdistances,vector<datasetarray*> datasetarraytest,vector<datasetarray*> queryarray){    ///for ferchet
	int maxj,j,x,y;
	bool flag;
	double disttemp;
	vector<float> gridhashvalue;
	for (auto temp:datasethashtable[z]->gethashlist(bucket)){        //check the bucket		
		gridhashvalue=makegrid(*temp.dataset,delta,datasethashtable[z]->getRandomShiftT(),M);
		j=aresame(gridhashvalue,gridaddingvalue);
		if (ID==temp.IDp || j){                      //check if they are close 
			x=finddatapos(temp.dataset->getname(),datasetarraytest);
			y=finddatapos(query->getname(),queryarray);
			disttemp=frechetdistances[x][y];
			flag=true;
			maxj = -1;
			for(j = 0; j < N * z; j++) {                                             //here check if the item is already in the list from other hashtable
				if(temp.dataset->getname()==neighbourname[N*z+j]){
					flag=false;
					break;
				}
			}
			if(flag){
				flag=false;
				for(j=0;j<N;j++){                                   //this for is for checking the N closest neighbours
					if(dist[N*z+j]==-1){                                     //now compare and save the closest neighbour so i can print them on the output file later
						dist[N*z+j]=disttemp;                             //if we haven't found N closest neighbours then count this one and stop the loop
						neighbourname[N*z+j]=temp.dataset->getname();
						flag=false;
						break;
					}
					else if(disttemp<dist[N*z+j]){                              //if there is a closest neighbour that is further than the one we have
						flag=true;
						if(maxj==-1){                                            //save him
							maxj=j;
						}
						else if(dist[N*z+j]>dist[N*z+maxj]){                     //and see if one of the closest neighbours we have has longer distance than the one we saved
							maxj=j;													//so if it does save him instead so we only save the closest of the closest neighbours
						}
					}
				}
				if(flag){															//in the end if all the N closest neighbours positions are filled and we found an even closer neighbour
					dist[N*z+maxj]=disttemp;                                             //change the position
					neighbourname[N*z+maxj]=temp.dataset->getname();
				}
			}
		}
	}
}

void nearestneighbours(vector<hashclass*> datasethashtable, int bucket ,vector<float> query,int length,double* dist,int z,int N,string* neighbourname){
	int maxj,j;
	bool flag;
	double disttemp;
	for (auto temp:datasethashtable[z]->gethashlist(bucket)){        //if didn't find same IDp then do it again but check everything
		disttemp = calcEuclideanDist(query, temp.dataset->getcoordinates(), length);   //distance
			flag=true;
			maxj = -1;
			for(j = 0; j < N * z; j++) {                                             //here check if the item is already in the list from other hashtable
				if(temp.dataset->getname()==neighbourname[N*z+j]){
					flag=false;
					break;
				}
			}
			if(flag){
				flag=false;
				for(j=0;j<N;j++){                                   //this for is for checking the N closest neighbours
					if(dist[N*z+j]==-1){                                     //now compare and save the closest neighbour so i can print them on the output file later
						dist[N*z+j]=disttemp;                             //if we haven't found N closest neighbours then count this one and stop the loop
						neighbourname[N*z+j]=temp.dataset->getname();
						flag=false;
						break;
					}
					else if(disttemp<dist[N*z+j]){                              //if there is a closest neighbour that is further than the one we have
						flag=true;
						if(maxj==-1){                                            //save him
							maxj=j;
						}
						else if(dist[N*z+j]>dist[N*z+maxj]){                     //and see if one of the closest neighbours we have has longer distance than the one we saved
							maxj=j;													//so if it does save him instead so we only save the closest of the closest neighbours
						}
					}
				}
				if(flag){															//in the end if all the N closest neighbours positions are filled and we found an even closer neighbour
					dist[N*z+maxj]=disttemp;                                             //change the position
					neighbourname[N*z+maxj]=temp.dataset->getname();
			}
		}
	}
}

void nearestneighbours(vector<hashclass*> datasethashtable, int bucket ,datasetarray* query,int length,double* dist,int z,int N,string* neighbourname){ //for frechet
	int maxj,j;
	bool flag;
	double disttemp;
	for (auto temp:datasethashtable[z]->gethashlist(bucket)){        //if didn't find same IDp then do it again but check everything
		disttemp =ferchetdistance(temp.dataset,query);  //distance
			flag=true;
			maxj = -1;
			for(j = 0; j < N * z; j++) {                                             //here check if the item is already in the list from other hashtable
				if(temp.dataset->getname()==neighbourname[N*z+j]){
					flag=false;
					break;
				}
			}
			if(flag){
				flag=false;
				for(j=0;j<N;j++){                                   //this for is for checking the N closest neighbours
					if(dist[N*z+j]==-1){                                     //now compare and save the closest neighbour so i can print them on the output file later
						dist[N*z+j]=disttemp;                             //if we haven't found N closest neighbours then count this one and stop the loop
						neighbourname[N*z+j]=temp.dataset->getname();
						flag=false;
						break;
					}
					else if(disttemp<dist[N*z+j]){                              //if there is a closest neighbour that is further than the one we have
						flag=true;
						if(maxj==-1){                                            //save him
							maxj=j;
						}
						else if(dist[N*z+j]>dist[N*z+maxj]){                     //and see if one of the closest neighbours we have has longer distance than the one we saved
							maxj=j;													//so if it does save him instead so we only save the closest of the closest neighbours
						}
					}
				}
				if(flag){															//in the end if all the N closest neighbours positions are filled and we found an even closer neighbour
					dist[N*z+maxj]=disttemp;                                             //change the position
					neighbourname[N*z+maxj]=temp.dataset->getname();
			}
		}
	}
}

void nearestneighbours(vector<hashclass*> datasethashtable, int bucket ,datasetarray* query,int length,double* dist,int z,int N,string* neighbourname,vector<double*> frechetdistances,vector<datasetarray*> datasetarraytest,vector<datasetarray*> queryarray){
	int maxj,j,x,y;
	bool flag;
	double disttemp;
	for (auto temp:datasethashtable[z]->gethashlist(bucket)){        //if didn't find same IDp then do it again but check everything
		x=finddatapos(temp.dataset->getname(),datasetarraytest);
		y=finddatapos(query->getname(),queryarray);
		disttemp=frechetdistances[x][y];
		flag=true;
		maxj = -1;
		for(j = 0; j < N * z; j++) {                                             //here check if the item is already in the list from other hashtable
			if(temp.dataset->getname()==neighbourname[N*z+j]){
				flag=false;
				break;
			}
		}
		if(flag){
			flag=false;
			for(j=0;j<N;j++){                                   //this for is for checking the N closest neighbours
				if(dist[N*z+j]==-1){                                     //now compare and save the closest neighbour so i can print them on the output file later
					dist[N*z+j]=disttemp;                             //if we haven't found N closest neighbours then count this one and stop the loop
					neighbourname[N*z+j]=temp.dataset->getname();
					flag=false;
					break;
				}
				else if(disttemp<dist[N*z+j]){                              //if there is a closest neighbour that is further than the one we have
					flag=true;
					if(maxj==-1){                                            //save him
						maxj=j;
					}
					else if(dist[N*z+j]>dist[N*z+maxj]){                     //and see if one of the closest neighbours we have has longer distance than the one we saved
						maxj=j;													//so if it does save him instead so we only save the closest of the closest neighbours
					}
				}
			}
			if(flag){															//in the end if all the N closest neighbours positions are filled and we found an even closer neighbour
				dist[N*z+maxj]=disttemp;                                             //change the position
				neighbourname[N*z+maxj]=temp.dataset->getname();
			}
		}
	}
}


double exhaustivesearch(vector<double> truedist,int a,datasetarray* query,vector<datasetarray*> datasetarraytest,int lines){
	bool flag;
	int j,b;
	double disttemp,newdist=-1;
	for(j=0;j<lines;j++){                    ///exhaustive search
		flag=false;
		disttemp=ferchetdistance(datasetarraytest[j], query);  
		for(b=0;b<a;b++){
			if(truedist[b]==disttemp){        //this is for N nearest neighbours
				flag=true;
				break;
			}
		}
		if(flag){
			continue;
		}
		if(newdist==-1){
			newdist=disttemp;
		}
		else if(newdist>disttemp ){
			newdist=disttemp;
		}
	}
	return newdist;
}

double exhaustivesearch(vector<double> truedist,int a,datasetarray* query,vector<datasetarray*> datasetarraytest,int lines,vector<double*> frechetdistances,vector<datasetarray*> queryarray){
	bool flag;
	int j,b,x,y;
	double disttemp,newdist=-1;
	for(j=0;j<lines;j++){                    ///exhaustive search
		flag=false;
		x=finddatapos(datasetarraytest[j]->getname(),datasetarraytest);
		y=finddatapos(query->getname(),queryarray);
		disttemp=frechetdistances[x][y];  
		for(b=0;b<a;b++){
			if(truedist[b]==disttemp){        //this is for N nearest neighbours
				flag=true;
				break;
			}
		}
		if(flag){
			continue;
		}
		if(newdist==-1){
			newdist=disttemp;
		}
		else if(newdist>disttemp ){
			newdist=disttemp;
		}
	}
	return newdist;
}

double exhaustivesearch(vector<double> truedist,int a,vector<float> query,vector<datasetarray*> datasetarraytest,int length,int lines){
	bool flag;
	int j,b;
	double disttemp,newdist=-1;
	for(j=0;j<lines;j++){                    ///exhaustive search
		flag=false;
		disttemp=calcEuclideanDist(query, datasetarraytest[j]->getcoordinates(),length);
		for(b=0;b<a;b++){
			if(truedist[b]==disttemp){    //this is for N nearest neighbours
				flag=true;
				break;
			}
		}
		if(flag){
			continue;
		}
		if(newdist==-1){
			newdist=disttemp;
		}
		else if(newdist>disttemp ){
			newdist=disttemp;
		}
	}
	return newdist;
}

int minsearch(vector<int> min,int a,double* dist,int L){
	bool flag;
	int j;
	int newmin=-1;
	for(j=0;j<L;j++){         //find the minimum distance from all hashtables
		flag=false;
		for(int b=0;b<a;b++){                 //check if i have already included the distance
			if(dist[min[b]]==dist[j]){             ///what if some have the same distance???????????????
				flag=true;
				break;
			}
		}
		if(flag){
			continue;
		}
		if(dist[j]==-1){                     //fail proof
			continue;
		}
		if(newmin==-1){                       //initialize
			newmin=j;
		}
		else if(dist[newmin]>dist[j] ){   //if i find shorter distance 
			newmin=j;
		}
	}
	return newmin;
}

void lsh(int k,int L,int N,float R,string datapath,string querypath,string outputpath){
	int TableSize, perc = 0, tperc = 0,i,j,a,z,count; 
	int* dim = new int[2];
	int* dim2 = new int[2];
	long int* gtest = new long int[2];
	ofstream outfile;
	double* dist;
	string* neighbourname;
	vector<string> namebank;
	vector<datasetarray*> datasetarraytest;
	vector<datasetarray*> queryarray;
	vector<hashclass*> datasethashtable;
	vector<int> min(N,-1);
	vector<double> truedist(N,-1);
	outfile.open(outputpath);
	dim = readfile(datapath,datasetarraytest);  // here I read a file and save it in a vector of arrays of the class
	TableSize = dim[0]/32;                      // Initialize vector .. dim/4 is default
	if(TableSize==0){
		TableSize=2;
	}
	auto start = high_resolution_clock::now();
	for (i = 0; i < L; i++ ) {
		hashclass* temphashclass=new hashclass(TableSize, k, dim[1]);
		datasethashtable.push_back(temphashclass);
	} 
	for ( int z = 0; z  < L; z++ ) {
		for ( int i = 0; i < dim[0]; i++ ) {                 
			datasethashtable[z]->addtohashtable(*datasetarraytest[i], TableSize, k, dim[1], *datasethashtable[z]);
		}
	}
	dim2 = readfile(querypath,queryarray);
	dist = new double[N*L];
	neighbourname = new string[N*L];    // make L arrays of int and string
	for (i = 0; i < dim2[0]; i++ ) {          // take each querry array
		namebank.clear();
		for(z = 0; z < L; z++ ) {               // check all of hashtables to find the best results
			for(j = 0; j < N; j++ ) {
				dist[N*z + j] = -1;              
			}
			gtest = ghashfunction(*queryarray[i], TableSize, k, dim[1], *datasethashtable[z]);
			if ( datasethashtable[z]->ishashlistempty(gtest[1]) ) {              //this is to ensure it goes in a bucket
				count=0;
				do {
					gtest[1]++;
					if ( gtest[1] >= TableSize ) {
						gtest[1] = 0;
						count++;
					}
					if(count==2){
						cout << "error in hashing\n";
						return;
					}
				} while( datasethashtable[z]->ishashlistempty(gtest[1]) );
			}    
			nearestneighbours(datasethashtable,gtest[0],gtest[1] ,queryarray[i]->getcoordinates(),dim[1],dist,z,N,neighbourname);
			if(dist[N*z+N-1]==-1){
				nearestneighbours(datasethashtable,gtest[1] ,queryarray[i]->getcoordinates(),dim[1],dist,z,N,neighbourname);
			}
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		outfile << "Query: " << queryarray[i]->getname() << endl;
		auto truestart = high_resolution_clock::now();
		for(a=0;a<N;a++){
			min[a]=minsearch(min,a,dist,L);
			truedist[a]=exhaustivesearch(truedist,a,queryarray[i]->getcoordinates(),datasetarraytest,dim[1],dim[0]);
			if(dist[min[a]]==truedist[a]){
				perc++;
			}
			tperc++;
			outfile << "Nearest neighbor-" << a+1 << ": " << neighbourname[min[a]] << endl;
			outfile << "distanceLSH: " << dist[min[a]] << endl;
			outfile << "distanceTrue: " << truedist[a] << endl;      //write in output file
		}
		auto truestop = high_resolution_clock::now();
		auto trueduration = duration_cast<microseconds>(truestop - truestart);
		outfile << "tLSH: " << duration.count() << endl;
		outfile << "tTrue: " << trueduration.count() << endl;///the brute force approach seems faster but it is because I have already a lot of information from lsh and don't do a lot of computing
		outfile << R << "-near neighbors: " << endl;           ///R range search
		namebank=rangesearch(L,TableSize, dim,datasethashtable,*queryarray[i],R,k);
		for(auto tempnamebank:namebank){
			outfile << tempnamebank << endl;
		}
		outfile << endl;
	}
	cout << "Success rate: " << perc*100/tperc <<endl;
	outfile.close();
}

void frechet(int k,int L,int N,float R,string datapath,string querypath,string outputpath,double delta){
	int TableSize, perc = 0, tperc = 0,i,j,a,z,count; 
	int* dim = new int[4];
	int* dim2 = new int[4];
	long int* gtest = new long int[2];
	double M;
	ofstream outfile;
	double* dist;
	vector<double*> frechetdistances;
	string* neighbourname;
	vector<string> namebank;
	vector<datasetarray*> datasetarraytest;
	vector<datasetarray*> queryarray;
	vector<hashclass*> datasethashtable;
	vector<float> gridaddingvalue;
	vector<int> min(N,-1);
	vector<double> truedist(N,-1);
	outfile.open(outputpath);
	dim = xreadfile(datapath,datasetarraytest);  // here I read a file and save it in a vector of arrays of the class
	dim2 = xreadfile(querypath,queryarray);
	// maxlength=findmax(dim[3],dim2[3]);
	if(delta==0){
		delta=4*2*findmax(dim[1],dim2[1])/1000;
	}
	M = findmax(dim[2],dim2[2]);            ///for padding
	TableSize = dim[0]/32;                      // Initialize vector .. dim/4 is default
	auto start = high_resolution_clock::now();
	for (i = 0; i < L; i++ ) {
		hashclass* temphashclass=new hashclass(TableSize, k, dim[3],delta);
		datasethashtable.push_back(temphashclass);
	} 
	for ( int z = 0; z  < L; z++ ) {
		for ( int i = 0; i < dim[0]; i++ ) {                 
			datasethashtable[z]->addtohashtable(*datasetarraytest[i], TableSize, k, dim[1], *datasethashtable[z],delta,M);
		}
	}
	count=ishashtableempty(datasethashtable,L,TableSize);               ///only sometimes the hashtable isnt filled for some reason
	if(count){
		cout << "error in hashing\n";
		return;
	}
	dist = new double[dim2[0]];
	for(i=0;i<dim[0];i++){                     		
		for(z=0;z<dim2[0];z++){
			dist[z]=ferchetdistance(datasetarraytest[i],queryarray[z]);
			// cout << dist[z] << "   " << i <<  endl;     ///for testing delete later
		}
		frechetdistances.push_back(dist);
	}
	neighbourname = new string[N*L];    // make L arrays of int and string
	dist = new double[N*L];
	for (i = 0; i < dim2[0]; i++ ) {          // take each querry array
		namebank.clear();
		for(z = 0; z < L; z++ ) {               // check all of hashtables to find the best results
			for(j = 0; j < N; j++ ) {
				dist[N*z + j] = -1;              
			}
			gridaddingvalue = makegrid(*queryarray[i],delta,datasethashtable[z]->getferchetT(),M);
			gtest = ghashfunction(gridaddingvalue, TableSize, k, dim[1], *datasethashtable[z]);

			if ( datasethashtable[z]->ishashlistempty(gtest[1]) ) {              //this is to ensure it goes in a bucket
				count=0;
				do {
					gtest[1]++;
					if ( gtest[1] >= TableSize ) {
						gtest[1] = 0;
						count++;
					}
					if(count==2){                 ///why would the whole of the hashtable be empty
						cout << "Error in hashing\n";         ///I don't understand how this is happening
						return;
					}
				} while( datasethashtable[z]->ishashlistempty(gtest[1]) );
			}    
			nearestneighbours(datasethashtable,gtest[0],gtest[1] ,queryarray[i],dim[1],dist,z,N,neighbourname,gridaddingvalue,M,delta,frechetdistances,datasetarraytest,queryarray);
			// cout << dist[N*z+N-1] << " " << N*z+N-1<< endl;    ///for testing delete later
			if(dist[N*z+N-1]==-1){                                                                             //if id didn't help then search all of the bucket
				nearestneighbours(datasethashtable,gtest[1] ,queryarray[i],dim[1],dist,z,N,neighbourname,frechetdistances,datasetarraytest,queryarray);
			}		
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(stop - start);
		outfile << "Query: " << queryarray[i]->getname() << endl;
		auto truestart = high_resolution_clock::now();
		for(a=0;a<N;a++){
			min[a]=minsearch(min,a,dist,L);
			truedist[a]=exhaustivesearch(truedist,a,queryarray[i],datasetarraytest,dim[0],frechetdistances,queryarray);
			if(dist[min[a]]==truedist[a]){
				perc++;
			}
			tperc++;
			outfile << "Nearest neighbor-" << a+1 << ": " << neighbourname[min[a]] << endl;
			outfile << "distanceLSH: " << dist[min[a]] << endl;
			outfile << "distanceTrue: " << truedist[a] << endl;      //write in output file
		}
		auto truestop = high_resolution_clock::now();
		auto trueduration = duration_cast<seconds>(truestop - truestart);
		outfile << "tLSH: " << duration.count() << endl;
		outfile << "tTrue: " << trueduration.count() << endl;///the brute force approach seems faster but it is because I have already a lot of information from lsh and don't do a lot of computing
		outfile << R << "-near neighbors: " << endl;           ///R range search
		namebank=rangesearch(L,TableSize, dim,datasethashtable,queryarray[i],R,k,M,delta,frechetdistances,datasetarraytest,queryarray);
		for(auto tempnamebank:namebank){
			outfile << tempnamebank << endl;
		}
		outfile << endl;
	}
	cout << "Success rate: " << perc*100/tperc <<endl;
	outfile.close();
}



int aresame(vector<float> a , vector<float> b){
	int i;
	if(a.size()!=b.size()){
		return 0;
	}
	else{
		for(i=0;i<(int)a.size();i++){
			if(a[i]!=b[i]){
				return 0;
			}
		}
	}
	return 1;
}



int ishashtableempty(vector<hashclass*> datasethashtable,int L,int TableSize){
	int count,z,i;
	count=0;
	for (z = 0; z  < L; z++ ) {
		for (i = 0; i < TableSize; i++ ) {   
			if ( datasethashtable[z]->ishashlistempty(i) ){
				count++;
			}
		}
	}
	if(count==L*TableSize){
		return 1;
	}
	return 0;
}