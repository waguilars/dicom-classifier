#include "kmeans.h"

vector<Point> getPoints(string filename) {
    ifstream infile(filename.c_str());
    if (!infile.is_open())
    {
        cout << "Error: Failed to open file: " << filename << endl;
        return {};
    }
    int pointId = 1;
    vector<Point> all_points;
    string line;

    while (getline(infile, line))
    {
        Point point(pointId, line);
        all_points.push_back(point);
        pointId++;
    }

    infile.close();
    cout << "\nData fetched successfully!" << endl
         << endl;

    return all_points;
}

int main() {

    int k = 2;
    string filename = "/home/will/Downloads/data.csv";
    string testFile = "/home/will/Downloads/test.csv";

    vector<Point> all_points = getPoints(filename);
    vector<Point> test_points = getPoints(testFile);

    // Return if number of clusters > number of points
    if ((int)all_points.size() < k)
    {
        cout << "Error: Number of clusters greater than number of points." << endl;
        return 1;
    }

    // Running K-Means Clustering
    int iters = 5;

    KMeans kmeans(k, iters, ".");

    kmeans.run(all_points);
    return 0;
}

