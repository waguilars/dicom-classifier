#ifndef DICOMREADER_H
#define DICOMREADER_H

#include<vector>

class DicomImage;

class DicomReader
{
private:
    DicomImage *image;
    int width;
    int height;

public:
    DicomReader(char const *path);
    int getWidth();
    void setWidth(int width);
    int getHeight();
    void setHeight(int height);
    int **getImageArray(int depth);
    void saveCSV(const char *filename, int **data);

    std::vector<std::vector<int>> getIntImageMatrix(int depth);

    std::vector<std::vector<float>> getFloatImageMatrix(int depth);

    std::vector<std::vector<double>> getDoubleImageMatrix(int depth);

};



class Test
{
public:
    void run();
};

#endif // DICOMREADER_H
