
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <memory>

#include "random_forest/globals.h"
#include "random_forest/ArgumentHandler.h"
#include "random_forest/ForestClassification.h"
#include "random_forest/ForestRegression.h"
#include "random_forest/ForestSurvival.h"
#include "random_forest/ForestProbability.h"
#include "random_forest/utility.h"
#include "random_forest/Data.h"

using namespace ranger;

int main () {
    std::unique_ptr<Forest> forest {};

    forest = make_unique<ForestClassification>();

    // Config
    uint mtry = 0;
    MemoryMode mode = MEM_DOUBLE;
    std::string  filename = "/home/will/Downloads/iris.txt";
    std::string outprefix = "out_file";
    // std::ofstream logfile { arg_handler.outprefix + ".log" };
    uint default_seed = 0;
    std::string predict_file = ""; // Use to load predict file
    std::string split_weights_file = "";
    std::vector<std::string> split_vars;
    std::string status_var_name = "";
    bool replacement = false;
    std::vector<std::string> cat_vars;
    bool save_memory = false;
    std::string weights_file;
    bool predall = false;
    double samplefraction = 0;
    bool holdout = false;
    std::vector<double> reg_factor;
    bool reg_usedepth = false;

    forest->initCpp("Species", mode, filename, mtry, outprefix, DEFAULT_NUM_TREE, &std::cout,
                    default_seed, DEFAULT_NUM_THREADS,predict_file, DEFAULT_IMPORTANCE_MODE, DEFAULT_MIN_NODE_SIZE_CLASSIFICATION,
                    split_weights_file, split_vars, status_var_name, replacement, cat_vars, save_memory,
                    DEFAULT_SPLITRULE, weights_file, predall, samplefraction, DEFAULT_ALPHA,
                    DEFAULT_MINPROP, holdout, DEFAULT_PREDICTIONTYPE, DEFAULT_NUM_RANDOM_SPLITS,
                    DEFAULT_MAXDEPTH, reg_factor, reg_usedepth);

    forest->run(true, true);


    forest->writeOutput();
    forest->saveToFile();

    return 0;
}

