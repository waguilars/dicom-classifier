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
    dicom/DicomReader.cpp \
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
    random_forest/utility.cpp \
    svm/svm.cpp \
    fcm/fcm.cpp \
    knn/knn.cpp \
    gbdt/Classifier.cxx \
    gbdt/FastBDT.cxx \
    gbdt/FastBDT_IO.cxx


HEADERS += \
    dicom/DicomReader.h \
    random_forest/ArgumentHandler.h \
    random_forest/Data.h \
    random_forest/DataChar.h \
    random_forest/DataDouble.h \
    random_forest/DataFloat.h \
    random_forest/DataRcpp.h \
    random_forest/Forest.h \
    random_forest/ForestClassification.h \
    random_forest/ForestProbability.h \
    random_forest/ForestRegression.h \
    random_forest/ForestSurvival.h \
    random_forest/Tree.h \
    random_forest/TreeClassification.h \
    random_forest/TreeProbability.h \
    random_forest/TreeRegression.h \
    random_forest/TreeSurvival.h \
    random_forest/globals.h \
    random_forest/utility.h \
    svm/svm.h \
    fcm/fcm.h \
    knn/knn.h \
    gbdt/Classifier.h



# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
