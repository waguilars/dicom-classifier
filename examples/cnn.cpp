#include "tiny_dnn/tiny_dnn.h"
#include "dicom/DicomReader.h"

using namespace tiny_dnn;
using namespace tiny_dnn::activation;
using namespace tiny_dnn::layers;
using namespace std;

//    network<sequential> net;

    // first input dicom image size
    // final output 2 classes

    // add layers
    /* Conv_layer
    * @param in_width         [in] input image width
    * @param in_height        [in] input image height
    * @param window_size      [in] window(kernel) size of convolution
    * @param in_channels      [in] input image channels (grayscale=1, rgb=3)
    * @param out_channels     [in] output image channels
    *   output-size = (in-width - window_width + 1) *
    * (in-height - window_height + 1) * out_channels
    */

    /* Average_pool layer
     * @param in_width     [in] width of input image
     * @param in_height    [in] height of input image
     * @param in_channels  [in] the number of input image channels(depth)
     * @param pool_size    [in] factor by which to downscale
     */
//    net << conv(32, 32, 5, 1, 6) << activation::tanh()  // in:32x32x1, 5x5conv, 6fmaps
//        << ave_pool(28, 28, 6, 2) << activation::tanh() // in:28x28x6, 2x2pooling
//        << fc(14 * 14 * 6, 120) << activation::tanh()   // in:14x14x6, out:120
//        << fc(120, 10);                     // in:120,     out:10


vector<vec_t> parseVecT(vector<vector<double>> data) {
    vector<vec_t> result;

    for (auto row : data) {
        vec_t newRow;
        for (auto val : row) {
            newRow.push_back(val);
        }
        result.push_back(newRow);
    }

    return result;

}


vector<vector<double>> readCSV(string filename) {
    ifstream file(filename);
    string line = "";
    string delimiter = ",";

    vector<vector<double>> data;

    // Read label values and push to vector
    while (getline(file, line))
    {
        size_t pos = 0;
        string token;
        vector<double>  dataValues;
//        cout << line << endl;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            dataValues.push_back(stoi(token));
        }
        dataValues.push_back(stoi(line));
        data.push_back(dataValues);
    }
    // Close the File
    file.close();

    return data;
}

vector<label_t> parseLabelT(vector<double> data) {
    vector<label_t> labels;

    for (auto v : data) {
        labels.push_back(v);
    }

    return labels;
}

int main(int argc, char *argv[])
{
    DicomReader dicomObj("/home/will/Projects/dicom-classifier/data/20586908_6c613a14b80a8591_MG_R_CC_ANON.dcm");
    int rows = dicomObj.getHeight();
    int cols = dicomObj.getWidth();

    vector<vector<double>> imageData = dicomObj.getDoubleImageMatrix(12);
    vector<double> labelData = readCSV("/home/will/Downloads/labels.csv")[0];


    vector<vec_t> train_data = parseVecT(imageData); //4084 x 3328
    vector<label_t> train_label = parseLabelT(labelData);

    network<sequential> net;
    adam opt;

    // add layers
    int width = 52;
    int height = 64;

    net << conv(width, height, 5, 1, 1) << activation::tanh()  // in: 52x64x1, 5x5conv, 6fmaps
        << ave_pool(width-5+1, height-5+1, 1, 2) << activation::tanh() // in: 48x60x1, 2x2pooling
        << fc(24 * 30 * 1, 120) << activation::tanh()   // in: 24x30, out:120
        << fc(120, 3);; //in: 120 out: 3 classes

    size_t batch_size = 1;
    size_t epochs = 1 ;

    net.train<mse>(opt, train_data, train_label, batch_size, epochs);


    cout << "Loading training data..." <<endl;
    vector<vector<double>> testRawData = readCSV("/home/will/Downloads/test.csv");
    vector<vec_t> test_data = parseVecT(testRawData);

    for (auto row : test_data) {
        std::cout << "result: " << net.predict_label(row) << " | ";
        std::cout << "similarity: " << net.predict_max_value(row) << std::endl;
    }


    net.test(test_data, {1,1,1,1,2}).print_detail(cout);

//    network<sequential> net;
//    adagrad opt;
//    net << layers::fc(2, 3) << activation::tanh()
//        << layers::fc(3, 4) << activation::softmax();

//    // input_data[0] should be classified to id:3
//    // input_data[1] should be classified to id:1

//    size_t batch_size = 1;
//    size_t epochs = 1 ;

//    net.train<mse>(opt, input_data, desired_out, batch_size, epochs);

//    std::cout << "result: " << net.predict_label(input_data[0]) << std::endl;
//    std::cout << "similarity: " << net.predict_max_value(input_data[0]) << std::endl;





    // load MNIST dataset
//    std::vector<label_t> train_labels;
//    std::vector<vec_t> train_images;
//    parse_mnist_labels("../test_cnn/train-labels.idx1-ubyte", &train_labels);
//    parse_mnist_images("../test_cnn/train-images.idx3-ubyte", &train_images, -1.0, 1.0, 2, 2);




    // declare optimization algorithm
//    adagrad optimizer;

//    std::cout << "Before train" << std::endl;

    // train (50-epoch, 30-minibatch)
//    net.train<mse, adagrad>(optimizer, train_images, train_labels, 1, 1);

//    // save
//    net.save("net");

//    std::cout << "Training Finished" << std::endl;

    // load
    // network<sequential> net2;
    // net2.load("net");
    return 0;
}

