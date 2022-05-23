#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h> 
#include <time.h>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <limits.h>
using namespace std;

double leaveOneOutCrossValidation(vector<vector<double>> data, vector<int>current_set_of_features, int feature_to_add); //k-fold cross validation
void feature_search_demo(string data); //data is the input file 
void printCurrSet(vector<int> current_set_of_features);
void printRow(vector<double> row);
vector<vector<double>> convertFiletoData(string data); // input file and turns file into vector<vector<double>>