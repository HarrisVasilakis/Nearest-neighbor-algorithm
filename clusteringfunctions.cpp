#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <list>
#include <random>
#include <time.h>
#include "clusteringfunctions.h"
#include "clusteringfrechetfunctions.h"
// #include "datasetarray.h"
// #include "class.h"
// #include "ghashfunction.h"

using namespace std;

int* readconfig(string path){
	int* arg = new int[6];
	int i,j;
	string text;
	char str[3];
	fstream MyReadFile(path);
	j=0;
	while (getline (MyReadFile, text)) { 
		memset (str,0,3);
		for (i=0 ; i<(int)text.length(); i++){ 
			if (isspace(text[i])!=0){
				str[0]=text[i+1];
				if(isspace(text[i+2])==0){
					str[1]=text[i+2];
				}
				else if(isspace(text[i+3])==0){
					str[1]=text[i+2];
					str[2]=text[i+3];
				}
				arg[j]=atoi(str);
				j++;
				break;
			}
		}
	}
	return arg;
}

void kmeansplusplus(vector<float*> &centroids,vector<datasetarray*> datasetarraytest,int K,int dim,int maxlength ){
	int i,j,z;
	double temp;
	double P[dim]={-1};
	float* tempcentroid=new float[maxlength];
	srand(time(NULL)); 
	int r=rand()%dim;                                        ///choose on random first centroid
	if(r<0){r=-r;}
	for(j=0;j<maxlength;j++){
		tempcentroid[j]=datasetarraytest[r]->getcoordinates()[j];
	}
	centroids.push_back(tempcentroid);
	for(z=0;z<K;z++){
		for(i=0;i<dim;i++){
			for(j=0;j<z;j++){
				temp =calcEuclideanDist(centroids,j,datasetarraytest[i]->getcoordinates(),maxlength);               ///make the distances
				if(P[i]==-1){
					P[i]=temp;
				}
				else if(P[i]>temp){
					P[i]=temp;
				}
			}
			P[i]=sqrt(P[i]);
			if(i>0){
				P[i]=P[i]+P[i-1];
			}

		}
		r=remainder((double)rand(),P[dim-1]);               ///pick a random number
		if(r<0){r=-r;}
		for(i=0;i<dim;i++){
			if(P[i]>=r){
				float* tempcentroid=new float[maxlength];             //initialize every time or it gets overwritten
				for(j=0;j<maxlength;j++){                             ///get next random centroid
					tempcentroid[j]=datasetarraytest[i]->getcoordinates()[j];
				}
				centroids.push_back(tempcentroid);
				break;
			}
		}
		for(j=0;j<dim;j++){
			P[j]=-1;
		}
	}
}

void kmeansplusplus(vector<float*> &centroids,vector<datasetarray*> datasetarraytest,int K,int dim,int maxlength ,int M){
	int i,j,z;
	double temp;
	double P[dim]={-1};
	float* tempcentroid=new float[2*maxlength];
	srand(time(NULL)); 
	int r=rand()%dim;                                        ///choose on random first centroid
	if(r<0){r=-r;}
	for(j=0;j<maxlength;j++){
		tempcentroid[j]=datasetarraytest[r]->getcoordinates()[j];
	}
	tempcentroid=padding(tempcentroid,M,maxlength,2*maxlength);
	centroids.push_back(tempcentroid);
	for(z=0;z<K;z++){
		for(i=0;i<dim;i++){
			for(j=0;j<z;j++){
				temp =calcEuclideanDist(centroids,j,datasetarraytest[i]->getcoordinates(),maxlength);               ///make the distances
				if(P[i]==-1){
					P[i]=temp;
				}
				else if(P[i]>temp){
					P[i]=temp;
				}
			}
			P[i]=sqrt(P[i]);
			if(i>0){
				P[i]=P[i]+P[i-1];
			}

		}
		r=remainder((double)rand(),P[dim-1]);               ///pick a random number
		if(r<0){r=-r;}
		for(i=0;i<dim;i++){
			if(P[i]>=r){
				float* tempcentroid=new float[2*maxlength];             //initialize every time or it gets overwritten
				for(j=0;j<maxlength;j++){                             ///get next random centroid
					tempcentroid[j]=datasetarraytest[i]->getcoordinates()[j];
				}
				tempcentroid=padding(tempcentroid,M,maxlength,2*maxlength);
				centroids.push_back(tempcentroid);
				break;
			}
		}
		for(j=0;j<dim;j++){
			P[j]=-1;
		}
	}
}

vector<string>* lsh(vector<datasetarray*> datasetarraytest,vector<float*>& centroids,int dimensions,int maxlength,int K,int L, int k){
	int i,z,j,TableSize,c,min,pos;
	vector<hashclass*> datasethashtable;
	vector<float> tempcoordinates;
	bool flag6=true,flag5=true;
	float R;
	double distance,mindistance;
	float* newcentroid = new float[maxlength];
	float* oldcentroid = new float[maxlength];
	vector<string> clusterednames[K],totalclusterednames;
	vector<string> clusteredvaluesnames[K];
	TableSize=dimensions/32;
	if(TableSize<=0){
		TableSize=1;
	}
	for (i=0; i<L; i++){
		hashclass* temphashclass=new hashclass(TableSize, k, maxlength);              ///make hashclass for lsh
		datasethashtable.push_back(temphashclass);
	} 
	for(z=0; z<L; z++){
		for (i=0; i<dimensions; i++){             
			datasethashtable[z]->addtohashtable(*datasetarraytest[i], TableSize, k, datasetarraytest[i]->getdimension(), *datasethashtable[z]);
		}
	}
	while(flag5){
		R=0;
		while(flag6){
			c=0;
			for(auto tempos:centroids){
				clusterednames[c].clear();
				clusterednames[c]=rangesearch(L,TableSize,maxlength,datasethashtable,tempos,R,R+10,k);       //search for range [i,i+x]
				for(auto name:clusterednames[c]){
					for(auto totalnames:totalclusterednames){
						if(totalnames==name){                                                                                    //if i find a name that has been counted before end lsh implementation
							flag6=false;
							break;                                                                                         
						}
					}
					totalclusterednames.push_back(name);
				}
				c++;

			}
			if(flag6){
				for(c=0;c<K;c++){
					for(auto name:clusterednames[c]){
						clusteredvaluesnames[c].push_back(name);                  //here i put the range names in the right name array of the right cluster
					}
				}
			}
			if(flag6){
				R=R+10;
				if(R>100000){
					cout << "infinite loop can't find neighbours\n";
					return 0;
				}
			}
		}
		flag6=true;
		do{
			totalclusterednames.clear();
			for(auto tempos2:centroids){
				clusterednames[0].clear();
				clusterednames[0]=rangesearch(L,TableSize,maxlength,datasethashtable,tempos2,R,R+100,k); //like lsh get the range 
				for(auto anothername:clusterednames[0]){                 
					totalclusterednames.push_back(anothername);
				}
			}
			for(auto name:totalclusterednames){                                                               //but for the names you get , do loyd
				pos=finddatapos(name,datasetarraytest,0,dimensions);
				tempcoordinates=datasetarraytest[pos]->getcoordinates();
				for(c=0;c<K;c++){                              //and for every centroid
					if(c==0){
						mindistance=calcEuclideanDist(centroids,c,tempcoordinates,maxlength);           //count distance and put it in the cluster that has the minimum distance from the centroid
						min=c;
					}
					else{
						distance=calcEuclideanDist(centroids,c,tempcoordinates,maxlength);
						if(mindistance>distance){
							mindistance=distance;
							min=c;
						}
					}
				}
				for(auto clusname:clusteredvaluesnames[min]){
					if(clusname==name){
						flag6=false;
					}
				}
				if(flag6){
					clusteredvaluesnames[min].push_back(name);
				}
				flag6=true;
			}
			R=R+100;
		}while(totalclusterednames.empty()==false);                ///do this until range returns nothing
		flag6=true;
		for(c=0;c<K;c++){                              //for every centroid                      
			for(i=0;i<maxlength;i++){                         ///make a new centroid
				newcentroid[i]=0;
				oldcentroid[i]=centroids[c][i];
			}
			if((int)clusteredvaluesnames[c].size()!=0){  
				for(auto datasetname:clusteredvaluesnames[c]){
					tempcoordinates.clear();
					pos=finddatapos(datasetname,datasetarraytest,0,dimensions);
					tempcoordinates=datasetarraytest[pos]->getcoordinates();
					for(j=0;j<maxlength;j++){
						newcentroid[j]=newcentroid[j]+tempcoordinates[j];                       //that is the mean of all the datasets in the cluster
						
					}
					
				}
				for(j=0;j<maxlength;j++){
					newcentroid[j]=newcentroid[j]/(float)clusteredvaluesnames[c].size();
				}
				for(j=0;j<maxlength;j++){  
					centroids[c][j]=newcentroid[j];
				}
			}
			if(flag6){
				for(j=0;j<maxlength;j++){                                //see if the new centroid changes or else end function
					if(centroids[c][j]==oldcentroid[j]){
						flag5=false;                  //it must find that everything has remained the same
					}
					else{
						flag5=true;                   //flag5 is to end the algorithm if the centroids don't change
						flag6=false;                  ///flag6 is if it finds one that has changed then ensure that the whole loop will continue
						break;
					}
				}
			}
		}
	}
	vector<string>* newclusteredvaluesnames = new vector<string>[K];
	for(i=0;i<K;i++){
		newclusteredvaluesnames[i]=clusteredvaluesnames[i];
	}
	return newclusteredvaluesnames;
}

vector<string>* lshfrechet(vector<datasetarray*> datasetarraytest,vector<float*>& centroids,int dimensions,int maxlength,int K,int L, int k,int M){
	int i,z,j,TableSize,c,min,pos;
	vector<hashclass*> datasethashtable;
	vector<float> tempcoordinates;
	bool flag6=true,flag5=true;
	float R;
	double distance,mindistance;
	vector<float*> newcentroids;
	vector<string> clusterednames[K],totalclusterednames;
	double delta=4*2*dimensions/1000;
	vector<string> clusteredvaluesnames[K];
	TableSize=dimensions/32;
	if(TableSize<=0){
		TableSize=2;
	}
	for (i=0; i<L; i++){
		hashclass* temphashclass=new hashclass(TableSize, k, maxlength);              ///make hashclass for lsh
		datasethashtable.push_back(temphashclass);
	} 
	for(z=0; z<L; z++){
		for (i=0; i<dimensions; i++){                 
			datasethashtable[z]->addtohashtable(*datasetarraytest[i], TableSize, k, datasetarraytest[i]->getdimension(), *datasethashtable[z],delta,M);
		}
	}
	while(flag5){
		R=0;
		while(flag6){
			c=0;
			for(auto tempos:centroids){
				clusterednames[c].clear();
				clusterednames[c]=rangesearch(L,TableSize,maxlength,datasethashtable,tempos,R,R+10,k,delta,M);       //search for range [i,i+x]
				for(auto name:clusterednames[c]){
					for(auto totalnames:totalclusterednames){
						if(totalnames==name){                                                                                    //if i find a name that has been counted before end lsh implementation
							flag6=false;
							break;                                                                                         
						}
					}
					totalclusterednames.push_back(name);
				}
				c++;

			}
			if(flag6){
				for(c=0;c<K;c++){
					for(auto name:clusterednames[c]){
						clusteredvaluesnames[c].push_back(name);                  //here i put the range names in the right name array of the right cluster
					}
				}
			}
			if(flag6){
				R=R+10;
				if(R>300000){
					cout << "nothing found in range\n";
					flag6=false;
					break;
				}
			}
		}
		flag6=true;
		do{
			totalclusterednames.clear();
			for(auto tempos2:centroids){
				clusterednames[0].clear();
				clusterednames[0]=rangesearch(L,TableSize,maxlength,datasethashtable,tempos2,R,R+100,k,delta,M); //like lsh get the range 
				for(auto anothername:clusterednames[0]){                 
					totalclusterednames.push_back(anothername);
				}
			}
			for(auto name:totalclusterednames){                                                               //but for the names you get , do loyd
				pos=finddatapos(name,datasetarraytest,0,dimensions);
				for(c=0;c<K;c++){                              //and for every centroid
					if(c==0){
						mindistance=ferchetdistance(centroids[c],maxlength,datasetarraytest[pos]);           //count distance and put it in the cluster that has the minimum distance from the centroid
						min=c;
					}
					else{
						distance=ferchetdistance(centroids[c],maxlength,datasetarraytest[pos]);
						if(mindistance>distance){
							mindistance=distance;
							min=c;
						}
					}
				}
				for(auto clusname:clusteredvaluesnames[min]){
					if(clusname==name){
						flag6=false;
					}
				}
				if(flag6){
					clusteredvaluesnames[min].push_back(name);
				}
				flag6=true;
			}
			R=R+100;
			if(R>500000){
				cout << "nothing found in range again\n";
				break;
			}
		}while(totalclusterednames.empty()==false);                ///do this until range returns nothing
		newcentroids.clear();
		newcentroids=newmeancurve(centroids,clusteredvaluesnames,maxlength,K,datasetarraytest,M);
		flag6=false;
		flag5=false;
		for(i=0;i<K;i++){
			for(j=0;j<maxlength;j++){
				if(centroids[i][j]!=newcentroids[i][j]){
					flag5=true;
					flag6=true;
					break;
				}
			}
			if(flag6){
				break;
			}
		}
		centroids.clear();
		centroids=newcentroids;
	}
	vector<string>* newclusteredvaluesnames = new vector<string>[K];
	for(i=0;i<K;i++){
		newclusteredvaluesnames[i]=clusteredvaluesnames[i];
	}
	return newclusteredvaluesnames;
}

vector<string>* loyd(vector<datasetarray*> datasetarraytest,vector<float*>& centroids,int dimensions,int maxlength,int K){
	int i,j,c,min,pos;
	vector<float> tempcoordinates;
	bool flag6=true,flag5=true;
	string dataname;
	double distance,mindistance;
	float* newcentroid = new float[maxlength];
	float* oldcentroid = new float[maxlength];
	vector<string> clusteredvaluesnames[K];
	while(flag5){                //flag5
		for(i=0;i<K;i++){
			clusteredvaluesnames[i].clear();               ///clear the list so I can put new names in the cluster as the centroids change
		}
		for(auto data:datasetarraytest){                      //for every dataset
			for(i=0;i<K;i++){                              //and for every centroid
				if(i==0){
					mindistance=calcEuclideanDist(centroids,i,data->getcoordinates(),maxlength);           //count distance and put it in the cluster that has the minimum distance from the centroid
					min=i;
					dataname=data->getname();
				}
				else{
					distance=calcEuclideanDist(centroids,i,data->getcoordinates(),maxlength);
					if(mindistance>distance){
						mindistance=distance;
						min=i;
						dataname=data->getname();
					}
				}
			}
			clusteredvaluesnames[min].push_back(dataname);
		}
		flag6=true;
		for(c=0;c<K;c++){                              //for every centroid                    
			for(i=0;i<maxlength;i++){                         ///make a new centroid
				newcentroid[i]=0;
				oldcentroid[i]=centroids[c][i];
			}
			if((int)clusteredvaluesnames[c].size()!=0){  
				for(auto datasetname:clusteredvaluesnames[c]){
					tempcoordinates.clear();
					pos=finddatapos(datasetname,datasetarraytest,0,dimensions);
					tempcoordinates=datasetarraytest[pos]->getcoordinates();
					for(j=0;j<maxlength;j++){
						newcentroid[j]=newcentroid[j]+tempcoordinates[j];                       //that is the mean of all the datasets in the cluster
						
					}
					
				}
				for(j=0;j<maxlength;j++){
					newcentroid[j]=newcentroid[j]/(float)clusteredvaluesnames[c].size();
				}
				for(j=0;j<maxlength;j++){  
					centroids[c][j]=newcentroid[j];
				}
			}
			if(flag6){
				for(j=0;j<maxlength;j++){                                //see if the new centroid changes or else end function
					if(centroids[c][j]==oldcentroid[j]){
						flag5=false;                  //it must find that everything has remained the same
					}
					else{
						flag5=true;                   //flag5 is to end the algorithm if the centroids don't change
						flag6=false;                  ///flag6 is if it finds one that has changed then ensure that the whole loop will continue
						break;
					}
				}
			}
		}
	}
	vector<string>* newclusteredvaluesnames = new vector<string>[K];
	for(i=0;i<K;i++){
		newclusteredvaluesnames[i]=clusteredvaluesnames[i];
	}
	return newclusteredvaluesnames;
}

vector<string>* loydfrechet(vector<datasetarray*> datasetarraytest,vector<float*>& centroids,int dimensions,int maxlength,int K,int M){   ///for frechet
	int i,j,min,z;
	vector<float> tempcoordinates;
	bool flag5=true,flag6;
	string dataname;
	double distance,mindistance;
	vector<float*> newcentroids;
	vector<string> clusteredvaluesnames[K];
	while(flag5){                //flag5
		for(i=0;i<K;i++){
			clusteredvaluesnames[i].clear();               ///clear the list so I can put new names in the cluster as the centroids change
		}
		z=0;
		for(auto data:datasetarraytest){                      //for every dataset
			z++;
			for(i=0;i<K;i++){                              //and for every centroid
				if(i==0){
					mindistance=ferchetdistance(centroids[i],maxlength,data);  //count distance and put it in the cluster that has the minimum distance from the centroid
					min=i;
					dataname=data->getname();
				}
				else{
					distance=ferchetdistance(centroids[i],maxlength,data);
					// cout << distance << " " << i << " " << data->getcoordinates()[3] << centroids[i][1] << endl;
					if(mindistance>distance){
						mindistance=distance;
						min=i;
						dataname=data->getname();
					}
				}
			}
			clusteredvaluesnames[min].push_back(dataname);
		}
		newcentroids.clear();
		newcentroids=newmeancurve(centroids,clusteredvaluesnames,maxlength,K,datasetarraytest,M);
		// cout << clusteredvaluesnames[0].size() << " GAAAA " << clusteredvaluesnames[1].size() << " YAAA " << clusteredvaluesnames[2].size() << " SECRET "<<  clusteredvaluesnames[3].size()<<endl;
		flag6=false;
		flag5=false;
		for(i=0;i<K;i++){
			for(j=0;j<maxlength;j++){
				if(centroids[i][j]!=newcentroids[i][j]){    ///check if they are the same to end function
					flag5=true;
					flag6=true;
					break;
				}
			}
			if(flag6){
				break;
			}
		}
		centroids.clear();
		centroids=newcentroids;
	}
	vector<string>* newclusteredvaluesnames = new vector<string>[K];
	for(i=0;i<K;i++){
		newclusteredvaluesnames[i]=clusteredvaluesnames[i];
	}
	return newclusteredvaluesnames;

}

void Silhouette(int length,int K,ofstream& outfile,vector<datasetarray*> datasetarraytest,vector<float*> centroids,vector<string>* clusteredvaluesnames,int dimensions){
	double s,a,b,distance,mindistance,stotal=0,pos1,pos2,pos3;
	int c,min,i;
	outfile << "Silhouette: [";
	for(c=0;c<K;c++){ 
		s=0;
		if((int)clusteredvaluesnames[c].size()!=0){
			for(auto namecl:clusteredvaluesnames[c]){
				a=0;
				b=0;
				pos1=finddatapos(namecl,datasetarraytest,0,dimensions);
				for(auto namecl2:clusteredvaluesnames[c]){
					pos2=finddatapos(namecl2,datasetarraytest,0,dimensions);
					a=a+calcEuclideanDist(datasetarraytest[pos2]->getcoordinates(),datasetarraytest[pos1]->getcoordinates(),length);
				}
				for(i=0;i<K;i++){
					if(i!=c){
						if(i==0 || (c==0 && i==1)){
							mindistance=calcEuclideanDist(centroids,i,datasetarraytest[pos1]->getcoordinates(),length); //mindistance here is actually second minimum distance
							min=i;
						}
						else{
							distance=calcEuclideanDist(centroids,i,datasetarraytest[pos1]->getcoordinates(),length);
							if(mindistance>distance){
								mindistance=distance;
								min=i;
							}
						}
					}
				}
				for(auto namecl3:clusteredvaluesnames[min]){  
					pos3=finddatapos(namecl3,datasetarraytest,0,dimensions); 
					b=b+calcEuclideanDist(datasetarraytest[pos3]->getcoordinates(),datasetarraytest[pos1]->getcoordinates(),length);
				}  
				a=a/(clusteredvaluesnames[c].size()-1);
				if((int)clusteredvaluesnames[min].size()!=0){
					b=b/clusteredvaluesnames[min].size();
				}
				else{
					continue;
				}
				if(a>b && a!=0){
					s=s+((b-a)/a);
				}       
				else{
					s=s+((b-a)/b);
				}
			}
			s=s/clusteredvaluesnames[c].size();
		}
		outfile << s << ",";
		stotal=stotal+s;
	}
	stotal=stotal/K;
	outfile << stotal << "]\n";
}

