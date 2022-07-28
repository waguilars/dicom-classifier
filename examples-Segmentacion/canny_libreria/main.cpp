#include <iostream>
#include <vector>
#include <math.h>
#include "dicom/DicomReader.h"
#include "Canny/canny.h"
#include "performance/benchmark.h"
#include "omp.h"

using namespace std;

int main()
{
         DicomReader dicomObj("/home/usuario/Descargas/imagendicom/dataset/MasaMicro2.dcm");
         vector<vector<int>> data = dicomObj.getIntImageMatrix(12);
         systemMetrics systemMetrics("canny");
         systemMetrics.resetCounters();
         data= canny(data,30,50);
         systemMetrics.calculate();
         systemMetrics.printMetrics();
         cout <<"RAM: " <<getRamUsage()<<" kb"<<endl;
         DicomReader::saveData(data,"/home/usuario/Documentos/metricas_resultados/matriz_resultanteejemplo.txt",",",0);
         return 0;

}
