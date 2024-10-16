#ifndef _CLASS_H_
#define _CLASS_H_

#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include "datasetarray.h" 

using namespace std;

class datasetarray;

struct hashlist {                     //this struct will be on buckets so I can store IDp also with the dataset
	long int IDp;
	datasetarray* dataset;
	hashlist(datasetarray& addingvalue);
	~hashlist();
	void addIDp(long int IDp);         //This is to evaluate if datasetarray is close to querryarray before calculating l2
};

class hashclass {
		float* v; 	// v random generated vector of dimension 128
		int* r; 	// k-d array of ints, one for each h
		int t; 		// random generated shift
		float ferchetT;
		int buckets;
		list<hashlist> *hashtable;
	public:
		hashclass(int buckets, int k, int d);
		hashclass(int buckets, int k, int d,double delta);
		~hashclass();
		void addtohashtable(datasetarray& addingvalue , int TableSize, int k, int d, hashclass hash);
		void addtohashtable(datasetarray& addingvalue , int TableSize, int k, int d, hashclass hash,double delta,float M);
		void printhashtable();
		void printhashtablebucket(int position);
		float* getRandomV();
		int* getRandomR();
		int getRandomShiftT();
		float getferchetT();
		list<hashlist> gethashlist(int position);
		bool ishashlistempty(int position);
};

float* nordist(int); // (dimension of the random vector)

#endif