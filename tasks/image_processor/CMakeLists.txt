cmake_minimum_required(VERSION 3.16)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image_processor.cpp
        image_processor.h parser.cpp reader.cpp writer.cpp GrayScale.cpp Negative.cpp Crop.cpp Sharpening.cpp EdgeDetection.cpp enquiry.cpp filters_factory.cpp Jitter.cpp Crop.h Jitter.h GrayScale.h EdgeDetection.h filters_factory.h Negative.h Sharpening.h reader.h writer.h parser.h test.cpp)