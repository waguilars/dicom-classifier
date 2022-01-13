#include "dicomutils.h"
#include "DicomReader.h"
#include <dirent.h>
#include <fstream>

#include "kmeans/kmeans.h"

using namespace std;

// Return list with path of dicom files
vector<string> DicomUtils::getDicomFilesPath(const char *path) {
    vector<string> files;
    struct dirent *d;
    DIR *dr;
    dr = opendir(path);
    if(dr!=NULL)
    {

        for(d=readdir(dr); d!=NULL; d=readdir(dr))
        {
            string filename = d->d_name;
            if(filename.substr(filename.find_last_of(".") + 1) == "dcm") {
                string fullpath = path;
                fullpath += "/" + filename;
                files.push_back(fullpath);
            }
        }
        closedir(dr);
    }
    else {
        cout<<"\nError Occurred when reading dir!" << endl;
        return files;
    }
    return files;
}

// return width for the data set
int DicomUtils::getDataWidth(vector<string> dicomFiles)
{
    int maxW = 0;
    for (size_t i = 0; i < dicomFiles.size(); ++i) {
        DicomReader dcm(dicomFiles[i].c_str());

        if (dcm.getWidth() > maxW) {
            maxW = dcm.getWidth();
        }
    }

    return maxW;
}

// return height for the data set
int DicomUtils::getDataHeight(vector<string> dicomFiles)
{
    int maxH = 0;
    for (size_t i = 0; i < dicomFiles.size(); ++i) {
        DicomReader dcm(dicomFiles[i].c_str());


        if (dcm.getHeight() > maxH){
            maxH = dcm.getHeight();
        }
    }

    return maxH;

}

// Return basename from path file
string DicomUtils::base_name(const string &path, const string &delims)
{      return path.substr(path.find_last_of(delims) + 1);
}

// return dcm data as array pointer (for FCM)
double **DicomUtils::asFCMPointsData(int **arr, int numPoints, int numDims)
{
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


// Write metrics to file instance
// i, nombre, CPU, memoria, tiempo, alg_param
// alg_param: media del parametro a evaluar
void DicomUtils::writeMetrics(ofstream &file, int i, string filename, double cpu, int mem, double time, double param)
{
    file << i << "," << filename << "," << cpu << "," << mem << "," << time << "," << param << endl;
}

vector<Point> DicomUtils::getKMeansPoints(vector<vector<double> > data)
{
    vector<Point> all_points;
    for (int i = 0; i < data.size(); ++i) {
        Point point(i+1, data[i]);
        all_points.push_back(point);
    }
    return all_points;
}

vector<int> DicomUtils::readLabels(string filename, string delimiter)
{
    ifstream file(filename);
    string line = "";
    vector<int> labels;

    // Read label values and push to vector
    while (getline(file, line))
    {
        size_t pos = 0;
        string token;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            labels.push_back(stoi(token) );
        }
        labels.push_back(stoi(line));
    }
    // Close the File
    file.close();

    return labels;
}

vector<int> DicomUtils::genTargetValues(vector<vector<double> > data, int numClass)
{
    vector<int> values;
    for (size_t i = 0; i < data.size(); ++i) {
        double n = 0;
        for (size_t j = 0; j < data[0].size(); ++j) {
            n += data[i][j];
        }

        int m =(int)(n/data.size());
        values.push_back(m%numClass);
    }

    return values;
}

vector<Point> DicomUtils::getKMeansFilePoints(string filename)
{
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
    cout << "\nData fetched successfully!" << endl;

    return all_points;
}
