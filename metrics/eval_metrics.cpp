#include <iostream>
#include <vector>
#include <string>

#include "dicom/dicomutils.h"

#include "metrics/performance.h"

using namespace std;

int main()
{

    const char* dir = "/home/will/Downloads/dicom-tesis/dicom-metrics";

    vector<string> dcmFiles= DicomUtils::getDicomFilesPath(dir);


    performance::eval_fcm(dcmFiles, true);

    return 0;
}

