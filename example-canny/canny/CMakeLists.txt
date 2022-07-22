cmake_minimum_required(VERSION 3.5)

project(ejemplolib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
find_package(OpenMP REQUIRED)

add_library(DicomClassifier STATIC IMPORTED)
set_target_properties(DicomClassifier PROPERTIES
IMPORTED_LOCATION "/home/usuario/Descargas/dicomlibreria/dicom-classifier-main/build2/libDicomClassifier.a"
INTERFACE_INCLUDE_DIRECTORIES "/home/usuario/Descargas/dicomlibreria/dicom-classifier-main/DicomClassifier"
)
add_library(DicomSegmentation STATIC IMPORTED)
set_target_properties(DicomSegmentation PROPERTIES
IMPORTED_LOCATION "/home/usuario/Descargas/dicomlibreria/dicom-classifier-main/build3/libDicomSegmentation.a"
INTERFACE_INCLUDE_DIRECTORIES "/home/usuario/Descargas/dicomlibreria/dicom-classifier-main/segmentation"
)

add_library(DicomMetrics STATIC IMPORTED)
set_target_properties(DicomMetrics PROPERTIES
    IMPORTED_LOCATION "/home/usuario/Descargas/dicomlibreria/dicom-classifier-main/build2/libDicomMetrics.a"
    INTERFACE_INCLUDE_DIRECTORIES "/home/usuario/Descargas/dicomlibreria/dicom-classifier-main/metrics"
)

add_executable(ejemplolib main.cpp)
target_link_libraries(ejemplolib DicomClassifier DicomSegmentation DicomMetrics -ldcmdata -ldcmimgle -ldcmimage -ldcmjpeg -lpthread ${OpenCV_LIBS} OpenMP::OpenMP_CXX)

