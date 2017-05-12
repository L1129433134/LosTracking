cmake_minimum_required(VERSION 2.8.4)

project(LosLabel)

# Build options
option(BUILD_EXAMPLES  "Set to ON to build examples"  ON)
option(USE_OPENMP      "Set to ON to build use openmp"  ON)
option(USE_SSE         "Set to ON to build use SSE"  ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Use C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
message(STATUS "C++11 support has been enabled by default.")

# Use SSE
if (USE_SSE)
    add_definitions(-DUSE_SSE)
    message(STATUS "Use SSE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1")
endif()

# Use OpenMP
if (USE_OPENMP)
    find_package(OpenMP QUIET)
    if (OPENMP_FOUND)
        message(STATUS "Use OpenMP")
        add_definitions(-DUSE_OPENMP)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    endif()
endif()

include_directories(include)

# Build Face Detection library
set(FaceDetectionSrc
        src/FaceDetectionSrc/util/nms.cpp
        src/FaceDetectionSrc/util/image_pyramid.cpp
        src/FaceDetectionSrc/io/lab_boost_model_reader.cpp
        src/FaceDetectionSrc/io/surf_mlp_model_reader.cpp
        src/FaceDetectionSrc/feat/lab_feature_map.cpp
        src/FaceDetectionSrc/feat/surf_feature_map.cpp
        src/FaceDetectionSrc/classifier/lab_boosted_classifier.cpp
        src/FaceDetectionSrc/classifier/mlp.cpp
        src/FaceDetectionSrc/classifier/surf_mlp.cpp
        src/FaceDetectionSrc/face_detection.cpp
        src/FaceDetectionSrc/fust.cpp
        )
add_library(seetaFaceDetectionLib SHARED ${FaceDetectionSrc})

# Build Face Alignment library
set(FaceAlignmentSrc
        src/FaceAlignmentSrc/cfan.cpp
        src/FaceAlignmentSrc/face_alignment.cpp
        src/FaceAlignmentSrc/sift.cpp)

add_library(seetaFaceAlignmentLib SHARED ${FaceAlignmentSrc})

set(required_libs
        seetaFaceDetectionLib
        seetaFaceAlignmentLib)

# Build examples
if (BUILD_EXAMPLES)
    find_package(OpenCV)
    if (NOT OpenCV_FOUND)
        message(WARNING "OpenCV not found. Test will not be built.")
    else()
        message(STATUS "OpenCV version: ${OpenCV_VERSION}")
        message(STATUS "Build with examples.")
        include_directories(${OpenCV_INCLUDE_DIRS})
        list(APPEND required_libs ${OpenCV_LIBS})

        add_executable(LosLabel
                src/demo/main.cpp
                src/demo/ImageReader.cpp
                src/demo/EyesDetector.cpp
                src/demo/LosLabel.cpp)
        target_link_libraries(LosLabel ${required_libs})
    endif()
endif()
