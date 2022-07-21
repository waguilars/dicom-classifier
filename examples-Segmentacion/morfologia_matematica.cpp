#include <iostream>
#include <vector>
#include <stdio.h>
#include <omp.h>
#include "performance/benchmark.h"
#include "morfologia_matematica/morfologia_matematica.h"
#include "dicom/DicomReader.h"

using namespace std;

int main()
{
    //DEFINIR NÚMERO DE HILOS A UTILIZAR, SI NO SE DEFINE OCUPA EL NÚMERO TOTAL DE PROCESADORES (6 POR DEFECTO)
    omp_set_num_threads(32);

    //DECLARAR E INICIALIZAR VARIABLE DE TIEMPO
    double tbegin = omp_get_wtime();

    //LECTURA DE IMAGEN DE TIPO DICOM
    DicomReader dicomObj("/home/debian11/Documentos/morfologia-matematica/build-test_morfologia_matematica-Desktop_Qt_6_2_4_GCC_64bit-Debug/dataset/MasaMicro1.dcm");
    vector<vector<int>> data = dicomObj.getIntImageMatrix(12);

    //CREAR UN ELEMENTO ESTRUCTURANTE CON UNA DIMENSIÓN IMPAR Y CUALQUIERA DE LOS SIGUIENTES TIPOS:
    //1 -> KERNEL CUADRADO
    //2 -> KERNEL HORIZONTAL
    //3 -> KERNEL VERTICAL
    //4 -> KERNEL CRUZADO
    int dimension = 3;
    int tipo = 4;
    vector<vector<element>> elementoEstructurante = determinarKernel(dimension,tipo);

    //CREACION DE VECTORES PARA CADA OPERACIÓN MORFOLÓGICA
    vector<vector<element>> vectDilatacion, vectErosion, vectApertura, vectCierre;

    //EJECUCIÓN DE OPERACIONES MORFOLÓGICAS
    //ENVÍA COMO PARÁMETROS LA IMAGEN DICOM Y EL ELEMENTO ESTRUCTURANTE PREVIAMENTE CREADO
    vectApertura = apertura(data, elementoEstructurante);
    vectCierre = cierre(data, elementoEstructurante);
    vectDilatacion = dilatacion(data, elementoEstructurante);
    vectErosion = erosion(data, elementoEstructurante);

    //GUARDAR RESULTADO EN UN ARCHIVO DE TEXTO
    DicomReader::saveData(vectApertura, "/home/debian11/Documentos/morfologia-matematica/build-test_morfologia_matematica-Desktop_Qt_6_2_4_GCC_64bit-Debug/Resultados/MM1_A.txt", ",", 0);
    DicomReader::saveData(vectCierre, "/home/debian11/Documentos/morfologia-matematica/build-test_morfologia_matematica-Desktop_Qt_6_2_4_GCC_64bit-Debug/Resultados/MM1_C.txt", ",", 0);
    DicomReader::saveData(vectDilatacion, "/home/debian11/Documentos/morfologia-matematica/build-test_morfologia_matematica-Desktop_Qt_6_2_4_GCC_64bit-Debug/Resultados/MM1_D.txt", ",", 0);
    DicomReader::saveData(vectErosion, "/home/debian11/Documentos/morfologia-matematica/build-test_morfologia_matematica-Desktop_Qt_6_2_4_GCC_64bit-Debug/Resultados/MM1_E.txt", ",", 0);

    //TOMAR TIEMPO FINAL Y CALCULARLO
    double time = omp_get_wtime() - tbegin;
    cout << "Execution Time De La Técnica: " << time <<"; Max Threads:" << omp_get_max_threads() <<endl;

    return 0;
}
