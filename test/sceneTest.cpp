
#include "Scene3D/CScene3D.hpp"

int main() {
    CScene3D scene;
    CScene3D::tPointPtr p = scene.getPoint(0);
    (*p).position[0] = 1;
    (*p).position[1] = 0;
    (*p).position[2] = 0;
    CScene3D::tCameraPtr c = scene.createCamera();
    (*c).rotation[0] = 1;
    (*c).rotation[1] = 0;
    (*c).rotation[2] = 0;
    scene.saveToObj("/mnt/test.obj");
    return 0;
}
