#include "performance.h"

#include "dicom/DicomReader.h"
#include "dicom/dicomutils.h"

#include "fcm/fcm.h"
#include "random_forest/rf.h"

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

    systemMetrics performance("perf");

    ofstream metrics;
    if (append) {
            metrics.open("kmeans.metrics.csv", ios_base::app); // Append
        } else {
            metrics.open("kmeans.metrics.csv"); // Append
        }

    metrics << "i,nombre,CPU(%),memoria(kB),tiempo(ms)"<<endl;


    for (size_t i = 0; i < dicomDir.size(); ++i) {
        performance.resetCounters();

        // add image to dataset
        string filename = DicomUtils::base_name(dicomDir[i], "/");
        int id = i+1;
        cout << "processing: " << id << ". "<< filename << "........." << endl;

        DicomReader img(dicomDir[i].c_str());

        vector<vector<double>> data = img.getDoubleImageMatrix(12);
        vector<Point> all_points = DicomUtils::getKMeansPoints(data);

        int k = 2;

        // Running K-Means Clustering
        int iters = 5;
        KMeans kmeans(k, iters, ".");
        kmeans.run(all_points); // last

        double avg = kmeans.getAvgClusters();
        performance.calculate();
        double cpu = performance.getCpuPercent();
        int mem = getRamUsage();
        double totalSeconds = performance.getDurationInMiliseconds();

        writePerfMetrics(metrics, id, filename, cpu, mem, totalSeconds);
        img.clear();
    }

    metrics.close();

}

void performance::eval_random_forest(vector<string> dcmFiles, const char *targetValuesDir, bool append)
{
    systemMetrics performance("perf");

    ofstream metrics;
    if (append) {
        metrics.open("random_forest.metrics.csv", ios_base::app); // Append
    } else {
        metrics.open("random_forest.metrics.csv"); // Append
    }

    metrics << "i,nombre,CPU(%),memoria(kB),tiempo(ms)"<<endl;

    for (size_t i = 0; i < dcmFiles.size(); ++i) {
        performance.resetCounters();
        string basename = DicomUtils::base_name(dcmFiles[i], "/");
        vector<int> labels = DicomUtils::getDicomTargetRoi(targetValuesDir, basename);

//        // add image to dataset
        string filename = DicomUtils::base_name(dcmFiles[i], "/");
        int id = i+1;
        cout << "processing: " << id << ". "<< filename << "........." << endl;

        DicomReader img(dcmFiles[i].c_str());

        vector<vector<double>> data = img.getDoubleImageMatrix(12);

         // Load labels
        if (labels.size() != data.size()) {
            labels = DicomUtils::genTargetValues(data, 2);

        }

//        // use DEFAULT_NUM_TREE to set trees 500
        RF random_forest(250);
        random_forest.setTrainData(data, labels);


        random_forest.init(true);

//        // verbose mode and calculate oob error
        random_forest.forest->run(false, true);
         random_forest.forest->writeOutput();


//        double err = random_forest.forest->getOverallPredictionError();
        performance.calculate();
        double cpu = performance.getCpuPercent();
        int mem = getRamUsage();
        double totalSeconds = performance.getDurationInMiliseconds();

        writePerfMetrics(metrics, id, filename, cpu, mem, totalSeconds);
        img.clear();

    }

    metrics.close();

}

void performance::writePerfMetrics(ofstream &file, int i, string filename, double cpu, int mem, double time)
{
    file << i << "," << filename << "," << cpu << "," << mem << "," << time << endl;
}



