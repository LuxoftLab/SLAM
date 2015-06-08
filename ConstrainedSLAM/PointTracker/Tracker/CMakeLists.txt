add_library(OpticalFlow private/CLKTracker.cpp
                        private/COpticalFlowFeatureExtractor.cpp
                        private/COpticalFlowFeatureExtractor.hpp
                        private/IOpticalFlowFeatureExtractor.hpp
                        ITracker.hpp CLKTracker.hpp)

add_library(SteinTracker private/CSteinTracker.cpp
                         private/CTritset.cpp
                         private/CTritset.hpp
                         ITracker.hpp 
                         CSteinTracker.hpp)
