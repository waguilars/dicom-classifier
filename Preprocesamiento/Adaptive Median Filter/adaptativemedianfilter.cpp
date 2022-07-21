//ADAPTIVE MEDIAN FILTER
//AUTORES:Mariño Daniel, Sarmiento Steven, Raza Sebastian
//FECHA: Julio 2022

// El filtro adaptativo de la mediana está diseñado para eliminar ruido presente en imágenes. En especial, los inconvenientes que presenta el filtro estandar de la mediana. Su mayor ventaja es el tamaño variable del kernel que rodea a la imagen corrupta para obtener un mejor resultado.

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <memory.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core/hal/interface.h"

using namespace cv;
using namespace std;
typedef int element;

//Método de filtrado del pixel recibido del método Mat.
ushort adaptiveProcess(const Mat &im, int row, int col, int kernelSize, int maxSize)
{
    //Se determina los valores máximo, mínimo y mediana del kernel.
    vector <ushort> pixels;
    for(int a = -kernelSize / 2; a <= kernelSize / 2; a++){
        for(int b = -kernelSize / 2; b <= kernelSize / 2; b++){
            pixels.push_back(im.at<ushort>(row + a, col + b));
        }
    }
    sort(pixels.begin(), pixels.end());
    auto min = pixels[0];
    auto max = pixels[kernelSize * kernelSize - 1];
    ushort med = pixels[kernelSize * kernelSize / 2];
    ushort zxy = im.at<ushort>(row, col);
    //Se determina si el punto central del kernel es o no ruido. Si no es ruido se mantiene el punto, caso contrario toma el valor de la mediana.
    if(med > min && med < max){
        if(zxy > min && zxy < max){
            return zxy;
        }else{
            return med;
        }
    }
    else{
    //Si el valor de la mediana obtenido es un punto de ruido, se aumenta el tamaño del kernel hasta que deje de serlo o llegue a su valor máximo de tamaño.
        kernelSize += 2;
        if(kernelSize <= maxSize)
            return adaptiveProcess(im, row, col, kernelSize, maxSize);
        else
            return med;
    }
}


//Método para transformar de vector tipo Int a Mat 
Mat vectorInt_a_cvMat(vector<vector<element>> vect){
    element x = vect[0].size();
    element y = vect.size();
    Mat img = Mat::zeros(y,x,CV_16UC1);
        for (element i = 0; i < y; i++) {
            for (element j = 0; j < x; j++) {
                img.at<ushort>(Point(j,i))=vect[i][j];
            }
        }
     return img;
}
//Método para transformar de Mat a vector tipo Int
vector<vector<element>> cvMat_a_vectorInt(Mat img){
    vector<vector<element>> vec;
    element x = img.cols-1; 
    element y = img.rows-1; 
        for (element i = 0; i <= y; i++) {
            vector<element> v1;
            for (element j = 0; j<=x; j++) {
                element p = img.at<ushort>(Point(j,i)) ;
                v1.push_back(p);
            }
            vec.push_back(v1);
        }
    return vec;
}

//Método principal. Requiere tres argumentos: Vector de imagen, tamaño minimo inicial del kernel, tamaño máximo que tomará el kernel.
//Tanto el tamaño mínimo (minSize), como el tamaño máximo (maxSize) deben ser números impares.
//Se recomienda minSize=3, maxSize=7 o minSize=3, maxSize=5. Si hay abundante ruido se recomienda un kernel de mayor tamaño.
//Método que recorre el kernel a través de la imagen.

vector<vector<element>> adaptivemedianfilter(vector<vector<element>> data, int minSize, int maxSize){
    Mat src = vectorInt_a_cvMat(data);
    Mat dst;
    copyMakeBorder(src, dst, maxSize / 2, maxSize / 2, maxSize / 2, maxSize / 2, BORDER_REFLECT); //Extender los límites de la imagen
    int rows = dst.rows;
    int cols = dst.cols;
    //Bucle de análisis de la imagen
    for(int j = maxSize / 2; j < rows - maxSize / 2; j++){
        for(int i = maxSize / 2; i < cols * dst.channels() - maxSize / 2; i++){
            dst.at<ushort>(j, i) = adaptiveProcess(dst, j, i, minSize, maxSize);
        }
    }
    vector<vector<element>> dst2 = cvMat_a_vectorInt(dst);
    return dst2;
}
