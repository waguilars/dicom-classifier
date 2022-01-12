#ifndef RF_H
#define RF_H

#include <vector>
#include <string>

#include "random_forest/globals.h"
#include "random_forest/ForestClassification.h"
#include "random_forest/utility.h"
#include "random_forest/Data.h"

using namespace std;
using namespace ranger;

class RF
{
public:
    std::unique_ptr<Forest> forest;

    RF();
    ~RF();

    void setTrainData(vector<vector<double>> data, vector<int> target);
    void predict(vector<vector<double>> data, vector<int> target, bool showOutput);
    void init(bool showOutput);

private:
        // Config
        uint mtry;
        MemoryMode mode;
        string  filename;
        string outprefix;
//        std::ofstream logfile { arg_handler.outprefix + ".log" };
        uint default_seed;
        string predict_file;
        string split_weights_file;
        vector<std::string> split_vars;
        string status_var_name;
        bool replacement;
        vector<std::string> cat_vars;
        bool save_memory;
        string weights_file;
        bool predall;
        double samplefraction;
        bool holdout;
        vector<double> reg_factor;
        bool reg_usedepth;

    string generateDataFormat(vector<vector<double>> data, vector<int> target);
};

#endif // RF_H
