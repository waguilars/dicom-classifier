#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "dicom/DicomReader.h"
#include "dicom/dicomutils.h"
#include "fcm/fcm.h"
#include "benchmark/system_metrics.hpp"
#include "benchmark/memcount.hpp"


using namespace std;

int main()
{

    systemMetrics performance("perf");

    ofstream metrics;
    metrics.open("fuzzycmeans.metrics.csv");
    metrics << "i,nombre,CPU(%),memoria(kB),tiempo(s),err_c\n";

    const char* dir = "/home/will/Downloads/dicom-tesis/dicom-metrics";

    vector<string> dcmFiles= DicomUtils::getDicomFilesPath(dir);


//    cout << "Begin..." << endl;
    for (int i = 0; i < dcmFiles.size(); ++i) {
        performance.resetCounters();
        // add image to dataset
        string filename = DicomUtils::base_name(dcmFiles[i], "/");
        int id = i+1;
        cout << "processing: " << id << ". "<< filename << "........." << endl;

        DicomReader img(dcmFiles[i].c_str());
        int rows = img.getHeight();
        int cols = img.getWidth();

        int **arr = img.getImageArray(12);
        double **data = DicomUtils::asFCMPointsData(arr, rows, cols);
        FCM *fcm;
        fcm = new FCM(2.0, 0.00001); // Fuzzines and epsilon

        int clusters = 3;

        fcm->init(data, clusters, rows, cols);

        fcm->eval();

        double cavg = fcm->getCenterAVG();

        //        // Take performance metrics
        performance.calculate();
        double cpu = performance.getCpuPercent();
        int mem = getRamUsage();
        double totalSeconds = performance.getDurationInSeconds();

        DicomUtils::writeMetrics(metrics, id, filename, cpu, mem, totalSeconds, cavg);
        img.clear();
    }


    metrics.close();
//    fcm->saveClusters("test");
//    fcm->saveCenters("test.centers.csv");
//    fcm->saveMembershipMatrixU("test.memU.csv");

  return 0;
}

