#ifndef DICOMREADER_H
#define DICOMREADER_H

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
    static void sayHello();
};



class Test
{
public:
    void run();
};

#endif // DICOMREADER_H
