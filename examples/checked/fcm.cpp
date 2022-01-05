#include <iostream>
#include <vector>
#include <fstream>



#include "dicom/DicomReader.h"
#include "fcm/fcm.h"


using namespace std;

double **parseDouble(int **arr, int numPoints, int numDims) {
    double **data;
    data= new double*[numPoints];

    for (int i = 0; i < numPoints; ++i) {
        data[i] = new double[numDims];
        for (int j = 0; j < numDims; ++j) {
            data[i][j] = arr[i][j];
        }
    }

    return data;
}


int main()
{
    DicomReader dicomObj("/home/will/Projects/dicom-classifier/img/20586908_6c613a14b80a8591_MG_R_CC_ANON.dcm");
    int rows = dicomObj.getHeight();
    int cols = dicomObj.getWidth();

    int **arr = dicomObj.getImageArray(12);

    double **data = parseDouble(arr, rows, cols);
    FCM *fcm;
    fcm = new FCM(2.0, 0.00001); // Fuzzines and epsilon

    int clusters = 3;

    fcm->init(data, clusters, rows, cols);

    fcm->eval();
    double **centers;
    centers = fcm->getCenters();

    std::ofstream output_file("centers.csv");

    // Save results as csv
    for (int i = 0; i < clusters; ++i) {
        for (int j = 0; j < cols; ++j) {
            output_file << centers[i][j] << ",";
        }
        output_file << "\n";
    }
    output_file.close();

    double **U;
    U = fcm->getMembershipMatrix();
    std::ofstream output_file2("fuzzy_partitionMatrix(U).csv");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < clusters; ++j) {
            cout << U[i][j] << " " ;
            output_file2 << U[i][j] << "," ;
        }
        output_file2  << "\n";
        cout << endl;
    }


    return 0;
}


