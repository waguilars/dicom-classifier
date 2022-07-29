#include <iostream>
#include <segmentacion/regiongrowing.h>
#include <vector>
#include "regiongrowing.h"
#include <bits/stdc++.h>
#include <memory.h>
#include "dicom/DicomReader.h"
#include "performance/benchmark.h"
#include <omp.h>
using namespace std;

int main()
{
    //Leemos nuestra imagen dicom
    DicomReader dicomobj("C://Users//Jonathan//Desktop//imag.dcm");
    //Convertimos en vector de vectores
    vector<vector<element>> vect = dicomobj.getIntImageMatrix(12);
    systemMetrics systemMetrics("regiongrowing");
    systemMetrics.resetCounters();
    //Llamamos las funciones de la tecnica
    vect = regiongrowing(vect);
    systemMetrics.calculate();
    systemMetrics.printMetrics();
    //Imprimimos las metricas
        cout<<"RAM: " <<getRamUsage()<<"kb"<<endl;
    DicomReader::saveData(vect,"C://Users//Jonathan//Desktop//matrizresultante.txt",",",0);
    return 0;

}
