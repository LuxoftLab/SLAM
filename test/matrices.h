#ifndef MATRICES_H
#define MATRICES_H
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <ceres/ceres.h>
#include <boost/numeric/ublas/matrix.hpp>
using namespace std;

using boost::numeric::ublas::matrix;

template<typename T>
matrix<T> convert(cv::Mat mat);

void initCalibrationMatrix(const char * file);
void printMatrix (cv::Mat& mat);

template<typename T>
matrix<T> rotateMatrixInOneAxis(T angle, int axis);

template<typename T>
matrix<T> getRotationMatrix(const T angleX, const T angleY, const T angleZ);

cv::Mat rotateMatrixFull(float rx, float ry, float rz);

template<typename T>
matrix<T> getTranslationMatrix(const T x, const T y, const T z);

template<typename T>
matrix<T> get3DPointMatrix(const T x, const T y, const T z);

template<typename T>
matrix<T> get2DPointMatrix(matrix<T>  matRotation, matrix<T>  matTranslation, matrix<T>  mat3DPoint);
cv::Mat get2DPointMatrix(float imageX, float imageY);
void get2DPoints(vector <cv::Mat>& rotations, vector <cv::Mat>& translations,
                 vector<cv::Mat>& points3D, vector< vector <cv::Mat> >& points2D,
                 int pointNum, int frameNum);
void initCameraParameters(double* params, int framesNum, vector <cv::Mat>& rotations,
                          vector <cv::Mat>& translations);
void getCameraParameters(const char* fileName, vector <cv::Mat>& rotations, vector <cv::Mat>& translations);
void getCameraParameters(const char* filePath, double* buf);

template<typename T>
matrix<T> getRotationMatrix(const T angleX, const T angleY, const T angleZ)
{
   //matrix<T> matRotation(4, 4);
   //for(int i = 0; i < 4; i++)
      //matRotation(i, i) = T(1);
    matrix<T> matRotation = rotateMatrixInOneAxis<T>(angleX, 1);
    matRotation = boost::numeric::ublas::prod(matRotation, rotateMatrixInOneAxis<T>(angleY, 2));
    matRotation = boost::numeric::ublas::prod(matRotation, rotateMatrixInOneAxis<T>(angleZ, 3));

    return matRotation;
}

template<typename T>
matrix<T> getTranslationMatrix(const T x, const T y, const T z)
{
    matrix<T> matTranslation(4, 4);
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            if (i == j)
                matTranslation(i,j) = T(1);
            else
                matTranslation(i,j) = T(0);
        }
    }
    matTranslation(0,3) = x;
    matTranslation(1,3) = y;
    matTranslation(2,3) = z;
    return matTranslation;
}

cv::Mat matCalibration;
template<typename T>
matrix<T> get2DPointMatrix(matrix<T>  matRotation, matrix<T>  matTranslation, matrix<T>  mat3DPoint)
{
   matTranslation *= T(-1.0);
    matrix<T> matTransform = boost::numeric::ublas::prod(matRotation, matTranslation);

    matrix<T> mat1 = boost::numeric::ublas::prod(convert<T>(matCalibration), matTransform);

    matrix<T> mat2DPoint = boost::numeric::ublas::prod(mat1, mat3DPoint);

    T t = mat2DPoint(2,0);
    //if (t != 0)
    //{
        mat2DPoint(0,0) /= t;
        mat2DPoint(1,0) /= t;
        mat2DPoint(2,0) /= t;
    //}

    return mat2DPoint;
}

template<typename T>
matrix<T> convert(cv::Mat mat) {
   matrix<T> m(mat.rows, mat.cols);
   for(int y = 0; y < mat.rows; y++)
      for(int x = 0; x < mat.cols; x++)
         m(y, x) = T(mat.at<float>(y, x));
   return m;
}

void initCalibrationMatrix(const char * file)
{
    matCalibration.create(3,4,CV_32FC1);
    double calib[12];
    FILE* fCalib = fopen(file,"rt");
    assert(fCalib != NULL);

    //qDebug()<<"CALIBRATION MATRIX READ: \n";
    for (int i=0; i<12; i++)
    {
        fscanf(fCalib,"%lf ",&calib[i]);
        //qDebug()<<"х["<<i<<"]: "<<calib[i];
    }
    fclose(fCalib);
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<4; j++)
        {
            matCalibration.at<float>(i,j) = calib[i*4+j];
        }
    }
}

template<typename T>
matrix<T> get3DPointMatrix(const T x, const T y, const T z)
{
    matrix<T> mat(4, 1);
    mat(0,0) = x;
    mat(1,0) = y;
    mat(2,0) = z;
    mat(3,0) = T(1);
    return mat;
}

template<typename T>
matrix<T> rotateMatrixInOneAxis(T angle, int axis)
{
    matrix<T> mat(4,4);
    switch (axis) {
    case 1:
        mat(0,0) = T(1);
        mat(1,0) = T(0);
        mat(2,0) = T(0);
        mat(0,1) = T(0);
        mat(1,1) = ceres::cos(angle);
        mat(2,1) = ceres::sin(angle);
        mat(0,2) = T(0);
        mat(1,2) = -ceres::sin(angle);
        mat(2,2) = ceres::cos(angle);
        break;
    case 2:
        mat(0,0) = ceres::cos(angle);
        mat(1,0) = T(0);
        mat(2,0) = -ceres::sin(angle);
        mat(0,1) = T(0);
        mat(1,1) = T(1);
        mat(2,1) = T(0);
        mat(0,2) = ceres::sin(angle);
        mat(1,2) = T(0);
        mat(2,2) = ceres::cos(angle);
        break;
    default:
        mat(0,0) = ceres::cos(angle);
        mat(1,0) = ceres::sin(angle);
        mat(2,0) = T(0);
        mat(0,1) = -ceres::sin(angle);
        mat(1,1) = ceres::cos(angle);
        mat(2,1) = T(0);
        mat(0,2) = T(0);
        mat(1,2) = T(0);
        mat(2,2) = T(1);
        break;
    }

    mat(0,3) = T(0);
    mat(1,3) = T(0);
    mat(2,3) = T(0);
    mat(3,0) = T(0);
    mat(3,1) = T(0);
    mat(3,2) = T(0);
    mat(3,3) = T(1);
    return mat;
}
#endif // MATRICES_H
