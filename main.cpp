#include "main.h"

double leaveOneOutCrossValidation(int data, vector<int>current_set_of_features, int feature_to_add){
    int accuracy = rand() % 101; //range of 0 - 100 (whole number)
    int dec = rand() % 9; //0 - 9 (decimal part)
    string whole = to_string(accuracy);
    string decimal = to_string(dec);
    string num = whole + "." + decimal;
    double val = stod(num);
    return val; 
}

void printCurrSet(vector<int> current_set_of_features){
    for (int i = 0; i < current_set_of_features.size(); i++){
        cout << current_set_of_features.at(i) << ",";
    }
}

void feature_search_demo(int data){ //for NOW will pass in the number of rows
    int num = data; //data is the number of features for NOW
    vector<int> current_set_of_features; //initialize empty set
    int feature_to_add_at_this_level;
    double best_so_far_accuracy = 0;
    double accuracy = 0;
    bool featureNotInSet = true;

    for (int i = 1; i <= num; i++ ){
        // cout << "On the " << i << "th level of the search tree" << endl;
        feature_to_add_at_this_level = 0;//empty vector
        best_so_far_accuracy = 0;
        for (int j = 1; j <= num; j++ ){
                featureNotInSet = true;
                for (int feature : current_set_of_features){ //loop through current_set_of_features and see if the current feature(j) is already in it, if not  bool = true
                    if (j == feature){ //means that curr feature j already in
                        featureNotInSet = false;
                        break;
                    } 
                } 
                if (featureNotInSet){
                    // cout << "--Considering adding the " << j << " feature" << endl;
                    //"Using feature(s) {1} accuracy is 35.4%"
                    accuracy = leaveOneOutCrossValidation(data, current_set_of_features, j);
                    cout << "Using feature(s) {";
                    printCurrSet(current_set_of_features);
                    cout << j << "} accuracy is " << accuracy << "%" << endl;
                    

                    if (accuracy > best_so_far_accuracy){
                        best_so_far_accuracy = accuracy;
                        feature_to_add_at_this_level = j;
                    }
                }
        }
        
        cout << "\nFeature set {";
        printCurrSet(current_set_of_features);
        cout << feature_to_add_at_this_level << "} was best, accuracy was " << best_so_far_accuracy << "%\n" <<endl; 
        current_set_of_features.push_back(feature_to_add_at_this_level);
        // cout <<"On level " << i << " I added feature " << feature_to_add_at_this_level << " to current set\n" << endl;
        //Feature set {1,2} was best, accuracy was 58.9%
    }
}

int main(){
    vector<int> placeholder;

    cout << "Welcome to Thomas Tran' Feature Selection Algorithm\n" << endl;
    cout << "Please enter the total number of features" << endl;
    int numOfFeatures;
    cin >> numOfFeatures;

    cout << "Type the number of the algorithm you want to run.\n\n - Forward Selection(1) \n - Backward Selection(2) \n - Thomas' Special Algorithm(3)\n" << endl;
    int algo;
    cin >> algo;

    cout << "Using no features and \"random\" evaluation, I get an accuracy of " << leaveOneOutCrossValidation(numOfFeatures, placeholder, 0) << "%\n" << endl;
    cout << "Beginning search.\n" << endl;

    feature_search_demo(numOfFeatures);

    return 0;
}