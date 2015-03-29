#include <iostream>
#include "matrices.h"


using namespace std;





cv::Mat getWikiRotationMatrix(float a, float b, float g)
{
    cv::Mat mat(4,4,CV_32FC1);
    mat.at<float>(0,0) = cos(a) * cos(g) - sin(a) * cos(b) * sin(g);
    mat.at<float>(0,1) = -cos(a) * sin(g) - sin(a) * cos(b) * cos(g);
    mat.at<float>(0,2) = sin(a) * sin(b);

    mat.at<float>(1,0) = sin(a) * cos(g) + cos(a) * cos(b) * sin(g);
    mat.at<float>(1,1) = -sin(a) * sin(g) + cos(a) * cos(b) * cos(g);
    mat.at<float>(1,2) = -cos(a) * sin(b);

    mat.at<float>(2,0) = sin(b) * sin(g);
    mat.at<float>(2,1) = sin(b) * cos(g);
    mat.at<float>(2,2) = cos(b);

    mat.at<float>(0,3) = 0;
    mat.at<float>(1,3) = 0;
    mat.at<float>(2,3) = 0;
    mat.at<float>(3,0) = 0;
    mat.at<float>(3,1) = 0;
    mat.at<float>(3,2) = 0;
    mat.at<float>(3,3) = 1;

    return mat;
}



//cv::Mat getQuaternion(float angleX, float angleY, float angleZ)
//{
//    cv::Mat mat(4,4,CV_32FC1);
//    float k = sqrt(1-angleX*angleX-angleY*angleY-angleZ*angleZ);
//    for (int i=0; i<4; i++)
//        mat.at<float>(i,i) = k;
//    mat.at<float>(0,1) = -angleX; mat.at<float>(0,2) = -angleY; mat.at<float>(0,3) = -angleZ;
//    mat.at<float>(1,0) = angleX; mat.at<float>(1,2) = -angleZ; mat.at<float>(1,3) = angleY;
//    mat.at<float>(2,0) = angleY; mat.at<float>(2,1) = angleZ; mat.at<float>(2,3) = -angleX;
//    mat.at<float>(3,0) = angleZ; mat.at<float>(3,1) = -angleY; mat.at<float>(3,2) = -angleX;
//    return mat;
//}


template<typename T>
matrix<T> rotateMatrixInOneAxis(T angle, int axis)
{
    matrix<T> mat(4,4);
    switch (axis) {
    case 1:
        mat(0,0) = 1;
        mat(1,0) = 0;
        mat(2,0) = 0;
        mat(0,1) = 0;
        mat(1,1) = cos(angle);
        mat(2,1) = sin(angle);
        mat(0,2) = 0;
        mat(1,2) = -sin(angle);
        mat(2,2) = cos(angle);
        break;
    case 2:
        mat(0,0) = cos(angle);
        mat(1,0) = 0;
        mat(2,0) = -sin(angle);
        mat(0,1) = 0;
        mat(1,1) = 1;
        mat(2,1) = 0;
        mat(0,2) = sin(angle);
        mat(1,2) = 0;
        mat(2,2) = cos(angle);
        break;
    default:
        mat(0,0) = cos(angle);
        mat(1,0) = sin(angle);
        mat(2,0) = 0;
        mat(0,1) = -sin(angle);
        mat(1,1) = cos(angle);
        mat(2,1) = 0;
        mat(0,2) = 0;
        mat(1,2) = 0;
        mat(2,2) = 1;
        break;
    }

    mat(0,3) = 0;
    mat(1,3) = 0;
    mat(2,3) = 0;
    mat(3,0) = 0;
    mat(3,1) = 0;
    mat(3,2) = 0;
    mat(3,3) = 1;
    return mat;
}





cv::Mat get2DPointMatrix(float imageX, float imageY)
{
    cv::Mat mat(3, 1, CV_32FC1);
    mat.at<float>(0,0) = imageX;
    mat.at<float>(1,0) = imageY;
    mat.at<float>(2,0) = 1;
    return mat;
}



void get2DPoints(vector <cv::Mat>& rotations, vector <cv::Mat>& translations,
                 vector<cv::Mat>& points3D, vector< vector <cv::Mat> >& points2D,
                 int pointNum, int frameNum)
{
//    for (int i=0; i<pointNum; i++)
//    {
//        vector<cv::Mat> temp;

//        for (int j=0; j<frameNum; j++)
//        {
//            temp.push_back( get2DPointMatrix(rotations.at(j),
//                                             translations.at(j),
//                                             points3D.at(i)) );

//        }

//        points2D.push_back(temp);
//    }
}

void initCameraParameters(double* params, int framesNum, vector <cv::Mat>& rotations, vector <cv::Mat>& translations)
{
//    double anX, anY, anZ, x, y, z;
////    qDebug()<<"===========INIT CAMERA PARAMETERS========";
//    for (int i=0; i<framesNum; i++)
//    {
//        anX = params[i*6 + 0]; anY = params[i*6 + 1]; anZ = params[i*6 + 2];
//        x   = params[i*6 + 3]; y   = params[i*6 + 4]; z   = params[i*6 + 5];
////        qDebug()<<anX<<" "<<anY<<" "<<anZ<<" "<<x<<" "<<y<<" "<<z<<"\n";
//        rotations.push_back( getRotationMatrix(anX, anY, anZ) );
//        translations.push_back( getTranslationMatrix(x, y, z) );
//    }
}

void getCameraParameters(const char* filePath, double* buf)
{
    FILE* f = fopen(filePath, "rt");
    assert(f!= NULL);

    for(int i=0; ; i++)
    {
        fscanf(f, "%lf", &buf[i]);
        if( feof(f) )
        {
            break;
        }
    }
    fclose(f);
}

void getCameraParameters(const char* fileName, vector <cv::Mat>& rotations, vector <cv::Mat>& translations)
{
//    float angleX, angleY, angleZ, x, y, z;
//    int scanRes;
//    int i=0;
//    FILE* fParams = fopen(fileName,"rt");
//    assert(fParams != NULL);

//    while ( !feof(fParams) )
//    {
//        scanRes = fscanf(fParams,"%f %f %f %f %f %f\n",
//                         &angleX, &angleY, &angleZ, &x, &y, &z);
//        if (scanRes == 0)
//            continue;
//        if (scanRes == EOF)
//            break;
////        qDebug()<<angleX<<" "<<angleY<<" "<<angleZ<<" "<<x<<" "<<y<<" "<<z<<"\n";
//        rotations.push_back( getRotationMatrix(angleX, angleY, angleZ) );
//        translations.push_back( getTranslationMatrix(x, y, z) );

//        i++;
//    }
//    fclose (fParams);
}

void printMatrix (cv::Mat& mat)
{
    for (int i=0; i<mat.rows; i++)
    {
        for(int j=0; j<mat.cols; j++)
        {
            //qDebug("%f ",mat.at<float>(i,j));
        }
    }
    //qDebug("==============================================\n");
}
