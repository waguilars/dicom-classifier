/*
    Copyright (c) 2013, Taiga Nomi and the respective contributors
    All rights reserved.

    Use of this source code is governed by a BSD-style license that can be found
    in the LICENSE file.
*/
#pragma once

#include "neural_net/config.h"
#include "neural_net/network.h"
#include "neural_net/nodes.h"

#include "neural_net/core/framework/tensor.h"

#include "neural_net/core/framework/device.h"
#include "neural_net/core/framework/program_manager.h"

#include "neural_net/activations/asinh_layer.h"
#include "neural_net/activations/elu_layer.h"
#include "neural_net/activations/leaky_relu_layer.h"
#include "neural_net/activations/relu_layer.h"
#include "neural_net/activations/selu_layer.h"
#include "neural_net/activations/sigmoid_layer.h"
#include "neural_net/activations/softmax_layer.h"
#include "neural_net/activations/softplus_layer.h"
#include "neural_net/activations/softsign_layer.h"
#include "neural_net/activations/tanh_layer.h"
#include "neural_net/activations/tanh_p1m2_layer.h"
#include "neural_net/layers/arithmetic_layer.h"
#include "neural_net/layers/average_pooling_layer.h"
#include "neural_net/layers/average_unpooling_layer.h"
#include "neural_net/layers/batch_normalization_layer.h"
#include "neural_net/layers/cell.h"
#include "neural_net/layers/cells.h"
#include "neural_net/layers/concat_layer.h"
#include "neural_net/layers/convolutional_layer.h"
#include "neural_net/layers/deconvolutional_layer.h"
#include "neural_net/layers/dropout_layer.h"
#include "neural_net/layers/fully_connected_layer.h"
#include "neural_net/layers/global_average_pooling_layer.h"
#include "neural_net/layers/input_layer.h"
#include "neural_net/layers/l2_normalization_layer.h"
#include "neural_net/layers/lrn_layer.h"
#include "neural_net/layers/lrn_layer.h"
#include "neural_net/layers/max_pooling_layer.h"
#include "neural_net/layers/max_unpooling_layer.h"
#include "neural_net/layers/power_layer.h"
#include "neural_net/layers/quantized_convolutional_layer.h"
#include "neural_net/layers/quantized_deconvolutional_layer.h"
#include "neural_net/layers/recurrent_layer.h"
#include "neural_net/layers/slice_layer.h"
#include "neural_net/layers/zero_pad_layer.h"

#ifdef CNN_USE_GEMMLOWP
#include "neural_net/layers/quantized_fully_connected_layer.h"
#endif  // CNN_USE_GEMMLOWP

#include "neural_net/lossfunctions/loss_function.h"
#include "neural_net/optimizers/optimizer.h"

#include "neural_net/util/deform.h"
#include "neural_net/util/graph_visualizer.h"
#include "neural_net/util/product.h"
#include "neural_net/util/weight_init.h"
#include "neural_net/util/nms.h"

#include "neural_net/io/cifar10_parser.h"
#include "neural_net/io/display.h"
#include "neural_net/io/layer_factory.h"
#include "neural_net/io/mnist_parser.h"

#ifdef DNN_USE_IMAGE_API
#include "neural_net/util/image.h"
#endif  // DNN_USE_IMAGE_API

#ifndef CNN_NO_SERIALIZATION
#include "neural_net/util/deserialization_helper.h"
#include "neural_net/util/serialization_helper.h"
// to allow upcasting
CEREAL_REGISTER_TYPE(tiny_dnn::elu_layer)
CEREAL_REGISTER_TYPE(tiny_dnn::leaky_relu_layer)
CEREAL_REGISTER_TYPE(tiny_dnn::relu_layer)
CEREAL_REGISTER_TYPE(tiny_dnn::sigmoid_layer)
CEREAL_REGISTER_TYPE(tiny_dnn::softmax_layer)
CEREAL_REGISTER_TYPE(tiny_dnn::softplus_layer)
CEREAL_REGISTER_TYPE(tiny_dnn::softsign_layer)
CEREAL_REGISTER_TYPE(tiny_dnn::tanh_layer)
CEREAL_REGISTER_TYPE(tiny_dnn::tanh_p1m2_layer)
#endif  // CNN_NO_SERIALIZATION

// shortcut version of layer names
namespace tiny_dnn {
namespace layers {

using conv = tiny_dnn::convolutional_layer;

using q_conv = tiny_dnn::quantized_convolutional_layer;

using max_pool = tiny_dnn::max_pooling_layer;

using ave_pool = tiny_dnn::average_pooling_layer;

using fc = tiny_dnn::fully_connected_layer;

using dense = tiny_dnn::fully_connected_layer;

using zero_pad = tiny_dnn::zero_pad_layer;

// using rnn_cell = tiny_dnn::rnn_cell_layer;

#ifdef CNN_USE_GEMMLOWP
using q_fc = tiny_dnn::quantized_fully_connected_layer;
#endif

using add = tiny_dnn::elementwise_add_layer;

using dropout = tiny_dnn::dropout_layer;

using input = tiny_dnn::input_layer;

using linear = linear_layer;

using lrn = tiny_dnn::lrn_layer;

using concat = tiny_dnn::concat_layer;

using deconv = tiny_dnn::deconvolutional_layer;

using max_unpool = tiny_dnn::max_unpooling_layer;

using ave_unpool = tiny_dnn::average_unpooling_layer;

}  // namespace layers

namespace activation {

using sigmoid = tiny_dnn::sigmoid_layer;

using asinh = tiny_dnn::asinh_layer;

using tanh = tiny_dnn::tanh_layer;

using relu = tiny_dnn::relu_layer;

using rectified_linear = tiny_dnn::relu_layer;

using softmax = tiny_dnn::softmax_layer;

using leaky_relu = tiny_dnn::leaky_relu_layer;

using elu = tiny_dnn::elu_layer;

using selu = tiny_dnn::selu_layer;

using tanh_p1m2 = tiny_dnn::tanh_p1m2_layer;

using softplus = tiny_dnn::softplus_layer;

using softsign = tiny_dnn::softsign_layer;

}  // namespace activation

#include "neural_net/models/alexnet.h"

using batch_norm = tiny_dnn::batch_normalization_layer;

using l2_norm = tiny_dnn::l2_normalization_layer;

using slice = tiny_dnn::slice_layer;

using power = tiny_dnn::power_layer;

}  // namespace tiny_dnn

#ifdef CNN_USE_CAFFE_CONVERTER
// experimental / require google protobuf
#include "neural_net/io/caffe/layer_factory.h"
#endif
