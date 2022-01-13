#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <vector>
#include <string>

//enum TECHNIQUES { KMEANS, FCM, RANDOM_FOREST };

using namespace std;

class performance
{
public:
    performance();

    // vector with list of images directory
    // mode true if needs to append data
    // Create a csv with performance metrics (cpu, memory, time) in format [technique].metrics.csv
    static void eval_fcm(vector<string> dicomDir, bool append);

    static void eval_kmeans(vector<string> dicomDir, bool append);

private:
    static void writePerfMetrics(ofstream &file, int i, string filename, double cpu, int mem, double time);
};

#endif // PERFORMANCE_H
