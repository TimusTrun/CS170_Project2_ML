#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h> 
#include <time.h>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// double leaveOneOutCrossValidation(int feature_to_add);
double leaveOneOutCrossValidation(int data, vector<int>current_set_of_features, vector<int>feature_to_add);
void feature_search_demo(int data); //for now data represents number of rows