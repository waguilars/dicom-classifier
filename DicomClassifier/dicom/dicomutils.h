#ifndef DICOMUTILS_H
#define DICOMUTILS_H

#include <vector>
#include <string>
#include <iostream>

#include "kmeans/kmeans.h"

using namespace std;

class DicomUtils
{
public:
    DicomUtils();
    static vector<string> getDicomFilesPath(const char *path);
    static int getDataWidth(vector<string> dicomFiles);
    static int getDataHeight(vector<string> dicomFiles);
    static string base_name(string const & path, string const &delims);
    static double **asFCMPointsData(int **arr, int numPoints, int numDims);
    static void writeMetrics(ofstream &file, int i, string filename, double cpu, int mem, double time, double param);

    static vector<Point> getKMeansFilePoints(string filename);
    static vector<Point> getKMeansPoints(vector<vector<double>> data);

    static vector<int> readLabels(string filename, string delimiter);

};

#endif // DICOMUTILS_H
