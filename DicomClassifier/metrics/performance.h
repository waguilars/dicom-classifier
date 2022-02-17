#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <vector>
#include <string>

//enum TECHNIQUES { KMEANS, FCM, RANDOM_FOREST };

using namespace std;

class performance
{
public:
    performance();
    /**
     * @brief evaluar el algoritmo de fcm
     * 
     * @param dicomDir directior con el vector de la imagen
     * @param append añadir a las metricas
     */

    // vector with list of images directory
    // mode true if needs to append data
    // Create a csv with performance metrics (cpu, memory, time) in format [technique].metrics.csv
    static void eval_fcm(vector<string> dicomDir, bool append);

/**
 * @brief evaluar las metricas de kmeans 
 * 
 * @param dicomDir directorio con el vector de la imagen 
 * @param append añadir a las metricas
 */
    static void eval_kmeans(vector<string> dicomDir, bool append);
/**
 * @brief evaluar tecnica random forest 
 * 
 * @param dcmFiles dirtectorio con el vector de la imagen
 * @param targetValuesDir etiqueta de datos de la tecnica
 * @param append añadir a las metricas
 */

    static void eval_random_forest(vector<string> dcmFiles, const char* targetValuesDir, bool append);

private:
    static void writePerfMetrics(ofstream &file, int i, string filename, double cpu, int mem, double time);
};

#endif // PERFORMANCE_H
