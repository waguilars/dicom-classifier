#include "performance.h"

#include "dicom/DicomReader.h"
#include "dicom/dicomutils.h"
#include "fcm/fcm.h"
#include "benchmark/system_metrics.hpp"
#include "benchmark/memcount.hpp"

performance::performance()
{

}

void performance::eval_fcm(vector<string> dicomDir, bool append)
{
    systemMetrics performance("perf");
    ofstream metrics;

    if (append) {
        metrics.open("fcm.metrics.csv", ios_base::app); // Append
    } else {
        metrics.open("fcm.metrics.csv"); // Append
    }

    metrics << "i,nombre,CPU(%),memoria(kB),tiempo(ms)\n";

    for (size_t i = 0; i < dicomDir.size(); ++i) {
        performance.resetCounters();
        // add image to dataset
        string filename = DicomUtils::base_name(dicomDir[i], "/");
        int id = i+1;
        cout << "processing: " << id << ". "<< filename << "........." << endl;

        DicomReader img(dicomDir[i].c_str());
        int rows = img.getHeight();
        int cols = img.getWidth();

        int **arr = img.getImageArray(12);
        double **data = DicomUtils::asFCMPointsData(arr, rows, cols);
        FCM *fcm;
        fcm = new FCM(2.0, 0.00001); // Fuzzines and epsilon

        int clusters = 3;

        fcm->init(data, clusters, rows, cols);

        fcm->eval();

//        double cavg = fcm->getCenterAVG();

        // Take performance metrics
        performance.calculate();
        double cpu = performance.getCpuPercent();
        int mem = getRamUsage();
        double totalSeconds = performance.getDurationInMiliseconds();

        writePerfMetrics(metrics, id, filename, cpu, mem, totalSeconds);

        // Clear memory
        img.clear();
        delete fcm;
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
            delete[] arr[i];
        }
        delete[] data;
        delete[] arr;
    }


    metrics.close();

}

void performance::eval_kmeans(vector<string> dicomDir, bool append)
{

}

void performance::writePerfMetrics(ofstream &file, int i, string filename, double cpu, int mem, double time)
{
    file << i << "," << filename << "," << cpu << "," << mem << "," << time << endl;
}



