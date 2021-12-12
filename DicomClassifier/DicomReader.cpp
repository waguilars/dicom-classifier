#include "DicomReader.h"
#include <iostream>
#include <fstream>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h" /* for DicomImage */
#include "dcmtk/dcmjpeg/djdecode.h"

using namespace std;

void Test::run() {
    cout << "Hello" << endl;
}

DicomReader::DicomReader(const char *path)
{
    DJDecoderRegistration::registerCodecs();

    DicomImage *image = new DicomImage(path);
    this->image = image;
    this->width = this->image->getWidth();
    this->height = this->image->getHeight();
}

void DicomReader::saveCSV(const char *filename, int **data) {
    std::ofstream myfile;
    myfile.open (filename);
    for (int i = 0; i < this->getHeight(); ++i) {
        for (int j = 0; j < this->getWidth(); ++j) {
            myfile << data[i][j] << ";";
        }
        myfile << endl;
    }

    myfile.close();
    cout << filename << " has been created!" <<endl;
}

int DicomReader::getWidth() { return this->width; }

void DicomReader::setWidth(int width) { this->width = width; }

int DicomReader::getHeight() { return this->height; }

void DicomReader::setHeight(int height) { this->height = height;}

int **DicomReader::getImageArray(int depth = 16) {
    int width = image->getWidth();
    int height = image->getHeight();

    int **imageArray;
    imageArray = new int*[height];

    for (int i = 0; i < height; ++i) {
        imageArray[i] = new int[width];
    }

    if(this->image == NULL) {
        cerr << "Error: no image has been provided" << endl;
        return NULL;
    }

    if (this->image->getStatus() == EIS_Normal) {
        if (image->isMonochrome())
        {

            image->setMinMaxWindow();
            // int depth = image->getDepth(); // Profundidad
            Uint16 *pixelData = (Uint16 *)(image->getOutputData(depth));
            int max = pixelData[0];
            if (pixelData != NULL) {
                for (int i = 0; i < height; ++i) {
                    for (int j = 0; j < width; ++j) {
                        int value = pixelData[i*j];
                        if (value > max) {
                            max = value;
                        }
                        imageArray[i][j] = value;
                    }
                }
            }
        }
    } else {
        cerr << "Error: cannot load DICOM image (" << DicomImage::getString(image->getStatus()) << ")" << endl;
    }

    return imageArray;
}
