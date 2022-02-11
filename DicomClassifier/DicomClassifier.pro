QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -pthread

LIBS += -lpthread



SOURCES += \
    benchmark/memcount.cpp \
    benchmark/system_metrics.cpp \
    dicom/DicomReader.cpp \
    dicom/dicomutils.cpp \
    knn/Preprocessing.cpp \
    knn/ReadDataset.cpp \
    knn/dataset.cpp \
    knn/knn.cpp \
    knn/knnresults.cpp \
    knn/matrix.cpp \
    metrics/performance.cpp \
    random_forest/ArgumentHandler.cpp \
    random_forest/Data.cpp \
    random_forest/Forest.cpp \
    random_forest/ForestClassification.cpp \
    random_forest/ForestProbability.cpp \
    random_forest/ForestRegression.cpp \
    random_forest/ForestSurvival.cpp \
    random_forest/Tree.cpp \
    random_forest/TreeClassification.cpp \
    random_forest/TreeProbability.cpp \
    random_forest/TreeRegression.cpp \
    random_forest/TreeSurvival.cpp \
    random_forest/rf.cpp \
    random_forest/utility.cpp \
    svm/svm.cpp \
    fcm/fcm.cpp \
    svm/svm_util.cpp \
    tiny_dnn/third_party/gemmlowp/eight_bit_int_gemm/eight_bit_int_gemm.cc


HEADERS += \
    benchmark/memcount.hpp \
    benchmark/system_metrics.hpp \
    dicom/DicomReader.h \
    dicom/dicomutils.h \
    knn/Preprocessing.h \
    knn/ReadDataset.h \
    knn/dataset.h \
    knn/debug.h \
    knn/knn.h \
    knn/knnUtils.h \
    knn/matrix.h \
    metrics/performance.h \
    random_forest/rf.h \
    svm/svm.h \
    fcm/fcm.h \
    kmeans/kmeans.h \
    svm/svm_util.h \
    tiny_dnn/activations/activation_layer.h \
    tiny_dnn/activations/asinh_layer.h \
    tiny_dnn/activations/elu_layer.h \
    tiny_dnn/activations/leaky_relu_layer.h \
    tiny_dnn/activations/relu_layer.h \
    tiny_dnn/activations/selu_layer.h \
    tiny_dnn/activations/sigmoid_layer.h \
    tiny_dnn/activations/softmax_layer.h \
    tiny_dnn/activations/softplus_layer.h \
    tiny_dnn/activations/softsign_layer.h \
    tiny_dnn/activations/tanh_layer.h \
    tiny_dnn/activations/tanh_p1m2_layer.h \
    tiny_dnn/config.h \
    tiny_dnn/core/backend.h \
    tiny_dnn/core/backend_avx.h \
    tiny_dnn/core/backend_tiny.h \
    tiny_dnn/core/framework/device.fwd.h \
    tiny_dnn/core/framework/device.h \
    tiny_dnn/core/framework/op_kernel.h \
    tiny_dnn/core/framework/program.h \
    tiny_dnn/core/framework/program_manager.h \
    tiny_dnn/core/framework/tensor.h \
    tiny_dnn/core/framework/tensor_utils.h \
    tiny_dnn/core/kernels/avx_deconv2d_back_kernel.h \
    tiny_dnn/core/kernels/avx_deconv2d_kernel.h \
    tiny_dnn/core/kernels/avx_kernel_common.h \
    tiny_dnn/core/kernels/conv2d_grad_op.h \
    tiny_dnn/core/kernels/conv2d_grad_op_avx.h \
    tiny_dnn/core/kernels/conv2d_op.h \
    tiny_dnn/core/kernels/conv2d_op_avx.h \
    tiny_dnn/core/kernels/conv2d_op_internal.h \
    tiny_dnn/core/kernels/conv2d_op_libdnn.h \
    tiny_dnn/core/kernels/conv2d_op_nnpack.h \
    tiny_dnn/core/kernels/conv2d_op_opencl.h \
    tiny_dnn/core/kernels/fully_connected_grad_op.h \
    tiny_dnn/core/kernels/fully_connected_op.h \
    tiny_dnn/core/kernels/fully_connected_op_avx.h \
    tiny_dnn/core/kernels/fully_connected_op_cblas.h \
    tiny_dnn/core/kernels/fully_connected_op_intel_mkl.h \
    tiny_dnn/core/kernels/fully_connected_op_internal.h \
    tiny_dnn/core/kernels/fully_connected_op_nnpack.h \
    tiny_dnn/core/kernels/global_avepool_grad_op.h \
    tiny_dnn/core/kernels/global_avepool_op.h \
    tiny_dnn/core/kernels/global_avepool_op_avx.h \
    tiny_dnn/core/kernels/global_avepool_op_internal.h \
    tiny_dnn/core/kernels/gru_cell_grad_op.h \
    tiny_dnn/core/kernels/gru_cell_op.h \
    tiny_dnn/core/kernels/gru_cell_op_internal.h \
    tiny_dnn/core/kernels/lstm_cell_grad_op.h \
    tiny_dnn/core/kernels/lstm_cell_op.h \
    tiny_dnn/core/kernels/lstm_cell_op_internal.h \
    tiny_dnn/core/kernels/maxpool_grad_op.h \
    tiny_dnn/core/kernels/maxpool_op.h \
    tiny_dnn/core/kernels/maxpool_op_avx.h \
    tiny_dnn/core/kernels/maxpool_op_internal.h \
    tiny_dnn/core/kernels/maxpool_op_nnpack.h \
    tiny_dnn/core/kernels/nnp_deconv2d_kernel.h \
    tiny_dnn/core/kernels/rnn_cell_grad_op.h \
    tiny_dnn/core/kernels/rnn_cell_op.h \
    tiny_dnn/core/kernels/rnn_cell_op_internal.h \
    tiny_dnn/core/kernels/tiny_deconv2d_back_kernel.h \
    tiny_dnn/core/kernels/tiny_deconv2d_kernel.h \
    tiny_dnn/core/kernels/tiny_quantization_kernel.h \
    tiny_dnn/core/kernels/tiny_quantized_conv2d_kernel.h \
    tiny_dnn/core/kernels/tiny_quantized_deconv2d_kernel.h \
    tiny_dnn/core/kernels/tiny_quantized_fully_connected_kernel.h \
    tiny_dnn/core/kernels/tiny_quantized_matmul_kernel.h \
    tiny_dnn/core/params/conv_params.h \
    tiny_dnn/core/params/deconv_params.h \
    tiny_dnn/core/params/fully_params.h \
    tiny_dnn/core/params/global_avepool_params.h \
    tiny_dnn/core/params/gru_cell_params.h \
    tiny_dnn/core/params/lstm_cell_params.h \
    tiny_dnn/core/params/maxpool_params.h \
    tiny_dnn/core/params/params.h \
    tiny_dnn/core/params/rnn_cell_params.h \
    tiny_dnn/core/session.h \
    tiny_dnn/io/caffe/layer_factory.h \
    tiny_dnn/io/caffe/layer_factory_impl.h \
    tiny_dnn/io/cifar10_parser.h \
    tiny_dnn/io/display.h \
    tiny_dnn/io/layer_factory.h \
    tiny_dnn/io/mnist_parser.h \
    tiny_dnn/layers/arithmetic_layer.h \
    tiny_dnn/layers/average_pooling_layer.h \
    tiny_dnn/layers/average_unpooling_layer.h \
    tiny_dnn/layers/batch_normalization_layer.h \
    tiny_dnn/layers/cell.h \
    tiny_dnn/layers/cells.h \
    tiny_dnn/layers/concat_layer.h \
    tiny_dnn/layers/convolutional_layer.h \
    tiny_dnn/layers/deconvolutional_layer.h \
    tiny_dnn/layers/dropout_layer.h \
    tiny_dnn/layers/fully_connected_layer.h \
    tiny_dnn/layers/global_average_pooling_layer.h \
    tiny_dnn/layers/gru_cell.h \
    tiny_dnn/layers/input_layer.h \
    tiny_dnn/layers/l2_normalization_layer.h \
    tiny_dnn/layers/layer.h \
    tiny_dnn/layers/layers.h \
    tiny_dnn/layers/linear_layer.h \
    tiny_dnn/layers/lrn_layer.h \
    tiny_dnn/layers/lstm_cell.h \
    tiny_dnn/layers/max_pooling_layer.h \
    tiny_dnn/layers/max_unpooling_layer.h \
    tiny_dnn/layers/partial_connected_layer.h \
    tiny_dnn/layers/power_layer.h \
    tiny_dnn/layers/quantized_convolutional_layer.h \
    tiny_dnn/layers/quantized_deconvolutional_layer.h \
    tiny_dnn/layers/quantized_fully_connected_layer.h \
    tiny_dnn/layers/recurrent_layer.h \
    tiny_dnn/layers/rnn_cell.h \
    tiny_dnn/layers/slice_layer.h \
    tiny_dnn/layers/zero_pad_layer.h \
    tiny_dnn/lossfunctions/loss_function.h \
    tiny_dnn/models/alexnet.h \
    tiny_dnn/network.h \
    tiny_dnn/node.h \
    tiny_dnn/nodes.h \
    tiny_dnn/optimizers/optimizer.h \
    tiny_dnn/third_party/CLCudaAPI/clpp11.h \
    tiny_dnn/third_party/CLCudaAPI/cupp11.h \
    tiny_dnn/third_party/catch2/catch.hpp \
    tiny_dnn/third_party/gemmlowp/eight_bit_int_gemm/eight_bit_int_gemm.h \
    tiny_dnn/third_party/gemmlowp/internal/allocator.h \
    tiny_dnn/third_party/gemmlowp/internal/block_params.h \
    tiny_dnn/third_party/gemmlowp/internal/common.h \
    tiny_dnn/third_party/gemmlowp/internal/compute.h \
    tiny_dnn/third_party/gemmlowp/internal/fixedpoint.h \
    tiny_dnn/third_party/gemmlowp/internal/fixedpoint_neon.h \
    tiny_dnn/third_party/gemmlowp/internal/iterator.h \
    tiny_dnn/third_party/gemmlowp/internal/kernel.h \
    tiny_dnn/third_party/gemmlowp/internal/kernel_SSE.h \
    tiny_dnn/third_party/gemmlowp/internal/kernel_default.h \
    tiny_dnn/third_party/gemmlowp/internal/kernel_neon.h \
    tiny_dnn/third_party/gemmlowp/internal/kernel_reference.h \
    tiny_dnn/third_party/gemmlowp/internal/multi_thread_gemm.h \
    tiny_dnn/third_party/gemmlowp/internal/output.h \
    tiny_dnn/third_party/gemmlowp/internal/output_neon.h \
    tiny_dnn/third_party/gemmlowp/internal/pack.h \
    tiny_dnn/third_party/gemmlowp/internal/pack_SSE.h \
    tiny_dnn/third_party/gemmlowp/internal/pack_neon.h \
    tiny_dnn/third_party/gemmlowp/internal/single_thread_gemm.h \
    tiny_dnn/third_party/gemmlowp/internal/unpack.h \
    tiny_dnn/third_party/gemmlowp/internal/unpack_neon.h \
    tiny_dnn/third_party/gemmlowp/meta/multi_thread_common.h \
    tiny_dnn/third_party/gemmlowp/meta/multi_thread_gemm.h \
    tiny_dnn/third_party/gemmlowp/meta/multi_thread_gemv.h \
    tiny_dnn/third_party/gemmlowp/meta/operations_common.h \
    tiny_dnn/third_party/gemmlowp/meta/single_thread_gemm.h \
    tiny_dnn/third_party/gemmlowp/meta/single_thread_gemm_arm32.h \
    tiny_dnn/third_party/gemmlowp/meta/single_thread_gemm_arm64.h \
    tiny_dnn/third_party/gemmlowp/profiling/instrumentation.h \
    tiny_dnn/third_party/gemmlowp/profiling/profiler.h \
    tiny_dnn/third_party/gemmlowp/public/bit_depth.h \
    tiny_dnn/third_party/gemmlowp/public/gemmlowp.h \
    tiny_dnn/third_party/gemmlowp/public/map.h \
    tiny_dnn/third_party/gemmlowp/public/output_stages.h \
    tiny_dnn/third_party/gemmlowp/public/reference_gemm.h \
    tiny_dnn/third_party/stb/stb_image.h \
    tiny_dnn/third_party/stb/stb_image_resize.h \
    tiny_dnn/third_party/stb/stb_image_write.h \
    tiny_dnn/tiny_dnn.h \
    tiny_dnn/util/aligned_allocator.h \
    tiny_dnn/util/colored_print.h \
    tiny_dnn/util/deform.h \
    tiny_dnn/util/deserialization_helper.h \
    tiny_dnn/util/gradient_check.h \
    tiny_dnn/util/graph_visualizer.h \
    tiny_dnn/util/image.h \
    tiny_dnn/util/macro.h \
    tiny_dnn/util/math_functions.h \
    tiny_dnn/util/nms.h \
    tiny_dnn/util/nn_error.h \
    tiny_dnn/util/parallel_for.h \
    tiny_dnn/util/product.h \
    tiny_dnn/util/random.h \
    tiny_dnn/util/serialization_functions.h \
    tiny_dnn/util/serialization_helper.h \
    tiny_dnn/util/serialization_layer_list.h \
    tiny_dnn/util/target_cost.h \
    tiny_dnn/util/util.h \
    tiny_dnn/util/weight_init.h \
    tiny_dnn/xtensor/xadapt.hpp \
    tiny_dnn/xtensor/xarray.hpp \
    tiny_dnn/xtensor/xassign.hpp \
    tiny_dnn/xtensor/xaxis_iterator.hpp \
    tiny_dnn/xtensor/xbroadcast.hpp \
    tiny_dnn/xtensor/xbuffer_adaptor.hpp \
    tiny_dnn/xtensor/xbuilder.hpp \
    tiny_dnn/xtensor/xcomplex.hpp \
    tiny_dnn/xtensor/xcontainer.hpp \
    tiny_dnn/xtensor/xcsv.hpp \
    tiny_dnn/xtensor/xeval.hpp \
    tiny_dnn/xtensor/xexception.hpp \
    tiny_dnn/xtensor/xexpression.hpp \
    tiny_dnn/xtensor/xfunction.hpp \
    tiny_dnn/xtensor/xfunctorview.hpp \
    tiny_dnn/xtensor/xgenerator.hpp \
    tiny_dnn/xtensor/xindexview.hpp \
    tiny_dnn/xtensor/xinfo.hpp \
    tiny_dnn/xtensor/xio.hpp \
    tiny_dnn/xtensor/xiterable.hpp \
    tiny_dnn/xtensor/xiterator.hpp \
    tiny_dnn/xtensor/xlayout.hpp \
    tiny_dnn/xtensor/xmath.hpp \
    tiny_dnn/xtensor/xmissing.hpp \
    tiny_dnn/xtensor/xnoalias.hpp \
    tiny_dnn/xtensor/xoffsetview.hpp \
    tiny_dnn/xtensor/xoperation.hpp \
    tiny_dnn/xtensor/xoptional.hpp \
    tiny_dnn/xtensor/xrandom.hpp \
    tiny_dnn/xtensor/xreducer.hpp \
    tiny_dnn/xtensor/xscalar.hpp \
    tiny_dnn/xtensor/xsemantic.hpp \
    tiny_dnn/xtensor/xslice.hpp \
    tiny_dnn/xtensor/xstorage.hpp \
    tiny_dnn/xtensor/xstridedview.hpp \
    tiny_dnn/xtensor/xstrides.hpp \
    tiny_dnn/xtensor/xtensor.hpp \
    tiny_dnn/xtensor/xtensor_config.hpp \
    tiny_dnn/xtensor/xtensor_forward.hpp \
    tiny_dnn/xtensor/xutils.hpp \
    tiny_dnn/xtensor/xvectorize.hpp \
    tiny_dnn/xtensor/xview.hpp \
    tiny_dnn/xtensor/xview_utils.hpp



INCLUDEPATH += tiny_dnn random_forest

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    tiny_dnn/io/caffe/CPPLINT.cfg \
    tiny_dnn/io/caffe/caffe.proto \
    tiny_dnn/third_party/cl_kernels/activation.cl \
    tiny_dnn/third_party/cl_kernels/auxiliary.cl \
    tiny_dnn/third_party/cl_kernels/batch_reindex.cl \
    tiny_dnn/third_party/cl_kernels/benchmark.cl \
    tiny_dnn/third_party/cl_kernels/bias.cl \
    tiny_dnn/third_party/cl_kernels/bnll.cl \
    tiny_dnn/third_party/cl_kernels/channel.cl \
    tiny_dnn/third_party/cl_kernels/concat.cl \
    tiny_dnn/third_party/cl_kernels/contrastive_loss.cl \
    tiny_dnn/third_party/cl_kernels/conv_layer_spatial.cl \
    tiny_dnn/third_party/cl_kernels/conv_spatial_helper.cl \
    tiny_dnn/third_party/cl_kernels/crop.cl \
    tiny_dnn/third_party/cl_kernels/dropout.cl \
    tiny_dnn/third_party/cl_kernels/eltwise.cl \
    tiny_dnn/third_party/cl_kernels/elu.cl \
    tiny_dnn/third_party/cl_kernels/embed.cl \
    tiny_dnn/third_party/cl_kernels/fft.cl \
    tiny_dnn/third_party/cl_kernels/fillbuffer.cl \
    tiny_dnn/third_party/cl_kernels/im2col.cl \
    tiny_dnn/third_party/cl_kernels/im2col_nd.cl \
    tiny_dnn/third_party/cl_kernels/lrn.cl \
    tiny_dnn/third_party/cl_kernels/lstm_unit.cl \
    tiny_dnn/third_party/cl_kernels/math.cl \
    tiny_dnn/third_party/cl_kernels/mergecrop.cl \
    tiny_dnn/third_party/cl_kernels/pooling.cl \
    tiny_dnn/third_party/cl_kernels/pooling_nd.cl \
    tiny_dnn/third_party/cl_kernels/pooling_sk.cl \
    tiny_dnn/third_party/cl_kernels/slice.cl \
    tiny_dnn/third_party/cl_kernels/softmax_loss.cl \
    tiny_dnn/third_party/cl_kernels/solvers.cl \
    tiny_dnn/third_party/cl_kernels/tile.cl \
    tiny_dnn/third_party/cpplint.py \
    tiny_dnn/third_party/gemmlowp/meta/README \
    tiny_dnn/third_party/gemmlowp/meta/generators/cc_emitter.py \
    tiny_dnn/third_party/gemmlowp/meta/generators/gemm_MxNxK.py \
    tiny_dnn/third_party/gemmlowp/meta/generators/gemv_1xMxK.py \
    tiny_dnn/third_party/gemmlowp/meta/generators/meta.py \
    tiny_dnn/third_party/gemmlowp/meta/generators/meta_arm_32.py \
    tiny_dnn/third_party/gemmlowp/meta/generators/meta_arm_64.py \
    tiny_dnn/third_party/gemmlowp/meta/generators/meta_arm_common.py \
    tiny_dnn/third_party/gemmlowp/meta/generators/mul_1x8_Mx8_neon.py \
    tiny_dnn/third_party/gemmlowp/meta/generators/mul_Nx8_Mx8_neon.py \
    tiny_dnn/third_party/gemmlowp/meta/generators/neon_emitter.py \
    tiny_dnn/third_party/gemmlowp/meta/generators/neon_emitter_64.py \
    tiny_dnn/third_party/gemmlowp/meta/generators/qnt_Nx8_neon.py \
    tiny_dnn/third_party/gemmlowp/meta/generators/zip_Nx8_neon.py
