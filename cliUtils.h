#ifndef _LSH_UTILS_H_
#define _LSH_UTILS_H_

#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

int getCliArgs(int, char**, string&, string&, string&, int&, int&, int&, float&, double&, string&, string&);
int getCliArgs(int argc, char *argv[], string &datapath, string &configpath, string &outputpath, string& method, string& update, bool& flag7,bool& flag8);

#endif