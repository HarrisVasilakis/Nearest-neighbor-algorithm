#ifndef _FERCHETFUNCTIONS_H_
#define _FERCHETFUNCTIONS_H_

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <list>
#include "ghashfunction.h"

double ferchetdistance(datasetarray* a, datasetarray* b);
double findmax(double a,double b);
int findmax(int a,int b);
double findmin(double a, double b, double c);
vector<float> filtering(vector<float> a,int e);
double ferchethelper(datasetarray* a, datasetarray* b,int i,int j,double x,double y,double xy);
double ferchethelper(datasetarray* a, datasetarray* b,int i,int j,double x);
double ferchethelper(datasetarray* a, datasetarray* b,int i,int j);
double ferchethelper(float* a, datasetarray* b,int i,int j,double x,double y,double xy);
double ferchethelper(float* a, datasetarray* b,int i,int j,double x);
double ferchethelper(float* a, datasetarray* b,int i,int j);
double ferchethelper(vector<float> a, vector<float> b,int i,int j,double x,double y,double xy);
double ferchethelper(vector<float> a, vector<float> b,int i,int j,double x);
double ferchethelper(vector<float> a, vector<float> b,int i,int j);
float snapping(double delta,float x,float t);
float makerandomt(double delta);
vector<float> makegrid(datasetarray a, double delta, float t,float M);
vector<float> padding(vector<float> a,float M,int size);
float* padding(float* a,float M,int start,int size);
vector<double*> ferchetdistancearray(datasetarray* a, datasetarray* b);
vector<double*> ferchetdistancearray(vector<float> a, vector<float> b);
double ferchetdistance(vector<double*> ddarray,int a , int b);
double ferchetdistance(float* a,int length, datasetarray* b);
vector<float> makegrid(float* a,int dim, double delta, float t,float M);

#endif