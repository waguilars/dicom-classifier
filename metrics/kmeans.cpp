#include <iostream>
#include "kmeans/kmeans.h"
#include "dicom/DicomReader.h"
#include "dicom/dicomutils.h"

#include "benchmark/system_metrics.hpp"
#include "benchmark/memcount.hpp"

using namespace std;

int main() {

    systemMetrics performance("perf");

    ofstream metrics;
    metrics.open("kmeans.metrics.csv");
    metrics << "i,nombre,CPU(%),memoria(kB),tiempo(s),err_c\n";

    const char* dir = "/home/will/Downloads/dicom-tesis/dicom-metrics";

    vector<string> dcmFiles= DicomUtils::getDicomFilesPath(dir);

    for (int i = 0; i < 2; ++i) {
        performance.resetCounters();

        // add image to dataset
        string filename = DicomUtils::base_name(dcmFiles[i], "/");
        int id = i+1;
        cout << "processing: " << id << ". "<< filename << "........." << endl;

        DicomReader img(dcmFiles[i].c_str());

        vector<vector<double>> data = img.getDoubleImageMatrix(12);
        vector<Point> all_points = DicomUtils::getKMeansPoints(data);

        int k = 2;
        // Return if number of clusters > number of points
        if ((int)all_points.size() < k)
        {
            cout << "Error: Number of clusters greater than number of points." << endl;
            return 1;
        }

        // Running K-Means Clustering
        int iters = 5;
        KMeans kmeans(k, iters, ".");
        kmeans.run(all_points); // last

        double avg = kmeans.getAvgClusters();
        performance.calculate();
        double cpu = performance.getCpuPercent();
        int mem = getRamUsage();
        double totalSeconds = performance.getDurationInSeconds();

        DicomUtils::writeMetrics(metrics, id, filename, cpu, mem, totalSeconds, avg);
        img.clear();
    }

    metrics.close();

    return 0;
}

