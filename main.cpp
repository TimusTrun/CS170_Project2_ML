#include "main.h"



void printRow(vector<double> row){
    for (int j = 0; j < row.size(); j++){
        cout << row.at(j) << " ";
    }
    cout << endl;
}

vector<vector<double>> convertFiletoData(string data){
    string fileName = data; //user picks either large dataset or small "small-test-dataset.txt"
    cout << fileName << endl;
    ifstream fin;  //initialize datastream
    string line;
    vector<string> temp = {}; //use to store the rows in (all numbers separated)
    int i = 0;
    vector<vector<string>> fileInput; //vector that holds each row and each number is an element of the row in string form
    vector<vector<double>> fileInputDoubles; //vector that holds each row in form of doubles

    fin.open(fileName); //opens file

    while (fin) { //loops until reaches end of file
        getline(fin, line); //reads file line by line "2.0000000e+000  5.0688373e+000  3.1403378e+000  1.2891084e+000  5.7634216e-001  2.7268616e+000  1.9103920e+000  4.6027145e+000  3.3621920e+000  4.0253170e+000  2.8503988e+000"
        string s(line);//converted char* to string
        istringstream iss(s);
        do { //taking row and breaking it up into individual elements
            string word;
            iss >> word;
            
            if (word == "\n"){
                //if newline detected, do nothing
            } else {
                // cout << word << endl; 
                temp.push_back(word);
            }
        } while(iss); 
        fileInput.push_back(temp); //push back the row
        // printRow(fileInput.at(i));
        i++;
        temp = {};
    }
    
    fin.close(); // now we have all rows into a 2d vector in fileInput as strings
    for (int i = 0; i < fileInput.size(); i++) { //resize each row to be 11
        fileInput.at(i).resize(11);
        // cout << "Size at row " << i << " is " << fileInput.at(i).size() << endl;
    } 

    vector<double> temp2 = {};
    for (int i = 0; i < fileInput.size()-1; i++){ //turn all strings into doubles and store into double array
        for (int j = 0; j < fileInput.at(0).size(); j++){
            string s = fileInput.at(i).at(j);
            istringstream os(s);
            double d;
            os >> d;
            temp2.push_back(d);
            // cout << d << endl;
        }
        fileInputDoubles.push_back(temp2); //pushing rows into vector
        temp2 = {};
    }
    return fileInputDoubles;
}

double leaveOneOutCrossValidation(vector<vector<double>> data, vector<int>current_set_of_features, int feature_to_add){
    //current set of features is the ones i want to isolate, feature to add is also isolated (every other column becomes 0)
    vector<vector<double>> dataset = data;
    // printRow(dataset.at(1));
    for (int i = 0; i < dataset.size(); i++){
        for (int j = 0; j < dataset.at(0).size(); j++){
            if (find(current_set_of_features.begin(), current_set_of_features.end(), j) != current_set_of_features.end()){
                //if j index is one of our curr features, do not turn that column to 0
            } else { //if j index is not one of our curr features, turn column to 0, if classifier column or feature_to_add, dont change it
                if (j != 0 && j != feature_to_add){ //if currCol not classifier index and not featureToAdd, change to 0
                    dataset.at(i).at(j) = 0;
                }
            }
        }
    }
    // printRow(dataset.at(1));
    
    vector<double> objectToClassify;
    double labelObjectToClassify;
    double nearestNeighborDistance = INT_MAX;
    double nearestNeighborLocation = INT_MAX;
    double nearestNeighborLabel; 
    vector<double> temp3;
    double sum;
    double distance;
    double numberCorrectlyClassified = 0;
    double accuracy;
    
    for (int i = 0; i < dataset.size(); i++){
        //cout << i << "BYE" << endl;
        objectToClassify = {};
        for (int x = 1; x < dataset.at(0).size(); x++){ //all features of the ith object
            objectToClassify.push_back(dataset.at(i).at(x));
            //cout << objectToClassify.size() << endl;
        } //Grabbed Object to classify
        labelObjectToClassify = dataset.at(i).at(0); //first index of each row, identifier
        
        nearestNeighborDistance = INT_MAX;
        nearestNeighborLocation = INT_MAX;
        
        for (int j = 0; j < dataset.size(); j++){
            temp3 = {};
            sum = 0;
            if (j != i){ 
                //cout << "Ask if " << i << " is nearest neighbor with " << j << endl;
                for (int y = 1; y < dataset.at(0).size(); y++){ //push features into temp1
                    temp3.push_back(dataset.at(j).at(y)); 
                }
                for (int x = 0; x < objectToClassify.size(); x++){ //calculating distance for NN
                    //TODO: FINISH EUCLIDEAN DISTANCES **************************************
                    sum += pow((objectToClassify.at(x) - temp3.at(x)), 2); //add up all differences squared
                }
                distance = sqrt(sum); //sqrt of the sums
                //cout << distance << endl;
                if (distance < nearestNeighborDistance){
                    nearestNeighborDistance = distance;
                    nearestNeighborLocation = j;
                    nearestNeighborLabel = dataset.at(j).at(0); //label of the closest neighbor
                }
            }
        }
        if (labelObjectToClassify == nearestNeighborLabel) {numberCorrectlyClassified++;}
    }
    accuracy = numberCorrectlyClassified / (double)dataset.size();
    //cout << accuracy << endl;
    return accuracy;
}

void printCurrSet(vector<int> current_set_of_features){
    for (int i = 0; i < current_set_of_features.size(); i++){
        cout << current_set_of_features.at(i) << ",";
    }
}

// void feature_search_demo(string data){ //string for file name
//     // int num = data; //data is the number of features for NOW
//     vector<int> current_set_of_features; //initialize empty set
//     int feature_to_add_at_this_level;
//     double best_so_far_accuracy = 0;
//     double accuracy = 0;
//     bool featureNotInSet = true;

//     for (int i = 1; i <= num; i++ ){
//         // cout << "On the " << i << "th level of the search tree" << endl;
//         feature_to_add_at_this_level = 0;//empty vector
//         best_so_far_accuracy = 0;
//         for (int j = 1; j <= num; j++ ){
//                 featureNotInSet = true;
//                 for (int feature : current_set_of_features){ //loop through current_set_of_features and see if the current feature(j) is already in it, if not  bool = true
//                     if (j == feature){ //means that curr feature j already in
//                         featureNotInSet = false;
//                         break;
//                     } 
//                 } 
//                 if (featureNotInSet){
//                     // cout << "--Considering adding the " << j << " feature" << endl;
//                     //"Using feature(s) {1} accuracy is 35.4%"
//                     accuracy = leaveOneOutCrossValidation(data, current_set_of_features, j);
//                     cout << "Using feature(s) {";
//                     printCurrSet(current_set_of_features);
//                     cout << j << "} accuracy is " << accuracy << "%" << endl;
                    

//                     if (accuracy > best_so_far_accuracy){
//                         best_so_far_accuracy = accuracy;
//                         feature_to_add_at_this_level = j;
//                     }
//                 }
//         }
        
//         cout << "\nFeature set {";
//         printCurrSet(current_set_of_features);
//         cout << feature_to_add_at_this_level << "} was best, accuracy was " << best_so_far_accuracy << "%\n" <<endl; 
//         current_set_of_features.push_back(feature_to_add_at_this_level);
//         // cout <<"On level " << i << " I added feature " << feature_to_add_at_this_level << " to current set\n" << endl;
//         //Feature set {1,2} was best, accuracy was 58.9%
//     }
// }

// int main(){ //part 1
//     vector<int> placeholder;

//     cout << "Welcome to Thomas Tran' Feature Selection Algorithm\n" << endl;
//     cout << "Please enter the total number of features" << endl;
//     int numOfFeatures;
//     cin >> numOfFeatures;

//     cout << "Type the number of the algorithm you want to run.\n\n - Forward Selection(1) \n - Backward Selection(2) \n - Thomas' Special Algorithm(3)\n" << endl;
//     int algo;
//     cin >> algo;

//     cout << "Using no features and \"random\" evaluation, I get an accuracy of " << leaveOneOutCrossValidation(numOfFeatures, placeholder, 0) << "%\n" << endl;
//     cout << "Beginning search.\n" << endl;

//     feature_search_demo(numOfFeatures);

//     return 0;
// }

int main(){ //part 2
    string fileName;
    cout << "Which dataset would you like to use? 1) small dataset or 2) large dataset" << endl;
    int set;
    cin >> set; //1 = small, 2 = large
    if (set == 1){fileName = "small-test-dataset.txt";}
    else if (set == 2){fileName = "Large-test-dataset.txt";}
    vector<int> placeholder = {3,4,5};
    vector<vector<double>> data;
    data = convertFiletoData(fileName);
    leaveOneOutCrossValidation(data, placeholder, 9);
    
    return 0;
}