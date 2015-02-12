add_library(OpticalFlow private/CLKTracker.cpp
                        private/COpticalFlowFeatureExtractor.cpp
                        private/COpticalFlowFeatureExtractor.hpp
                        private/IOpticalFlowFeatureExtractor.hpp
                        ITracker.hpp CLKTracker.hpp)
