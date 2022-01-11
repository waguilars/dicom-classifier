#include "dicomutils.h"
#include "DicomReader.h"
#include <dirent.h>
#include <fstream>

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
