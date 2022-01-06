#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "dicom/DicomReader.h"
#include "knn/dataset.h"
#include "knn/knn.h"
#include "knn/knnUtils.h"

using namespace std;

vector<vector<double>> readCSV(string filename) {
    ifstream file(filename);
    string line = "";
    string delimiter = ",";

    vector<vector<double>> data;

    // Read label values and push to vector
    while (getline(file, line))
    {
        size_t pos = 0;
        string token;
        vector<double>  dataValues;
//        cout << line << endl;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            dataValues.push_back(stoi(token));
        }
        dataValues.push_back(stoi(line));
        data.push_back(dataValues);
    }
    // Close the File
    file.close();

    return data;
}


int main()
{
    DicomReader dicomObj("/home/will/Projects/dicom-classifier/img/20586908_6c613a14b80a8591_MG_R_CC_ANON.dcm");
    int rows = dicomObj.getHeight();
    int cols = dicomObj.getWidth();

    int **data = dicomObj.getImageArray(12);
//    vector<vector<double>> data = dicomObj.getDoubleImageMatrix(12);
//    vector<vector<double>> data= readCSV("/home/will/Downloads/dataset_withlabels.csv");
      vector<double> dataLabels = readCSV("/home/will/Downloads/labels.csv")[0];
    vector<vector<double>> testCSV = readCSV("/home/will/Downloads/test.csv");


    // Parse to array
    double *trainData = new double[rows*cols];

    int k = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            trainData[k] = data[i][j];
            k++;
        }
    }

    int *trainLabels = new int[rows];
    k = 0;
    for (auto label : dataLabels) {
        trainLabels[k] = label;
        k++;
    }



    double *testData= new double[5*cols];
    k=0;
    for (auto row : testCSV) {
        for (auto v : row) {
            testData[k] = v;
            k++;
        }
    }

    int testLabels[] = {1,1,1,1,2};


    int numLabels = 2;
    DatasetPointer dataset = makeDataset(rows, cols, numLabels, trainData, trainLabels);
    DatasetPointer test = makeDataset(testCSV.size(), cols, numLabels, testData, testLabels);

    KNN knn(dataset);


//    double bestSuccessRate = 0;
        int bestK = 0;
//    for(int k=1; k<=10; k++) {
//        printf("Trying K = %d ... ",k);
//        KNNResults res = knn.run(k, test);
//        double currentSuccess = res.top1Result().successRate();
//        if (currentSuccess > bestSuccessRate) {
//            bestSuccessRate = currentSuccess;
//            bestK = k;
//        }
//        printf("%lf\n", currentSuccess);
//    }
//    printf("Best K: %d. Success rate in validation set: %lf\n", bestK, bestSuccessRate);



       bestK = 1;
    KNNResults results = knn.run(bestK, test);
    cout << "Consolidating results" << endl;

    SingleExecutionResults top1 = results.top1Result();
    SingleExecutionResults top2 = results.topXResult(2);
    SingleExecutionResults top3 = results.topXResult(3);

    printf("Success Rate: %lf, Rejection Rate: %lf\n", top1.successRate(), top1.rejectionRate());
    printf("Top 2 Success Rate: %lf\n", top2.successRate());
    printf("Top 3 Success Rate: %lf\n", top3.successRate());
    printf("Confusion matrix:\n");




    MatrixPointer predictions = results.getPredictions();


    for (int i = 0; i < 5; ++i) {
        cout << "Point: " << i << endl;
        cout << "Original: " << testLabels[i]
                << " Predicted: " << predictions->pos(i,0) << endl;
    }




}
