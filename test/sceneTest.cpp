
#include "Scene3D/CScene3D.hpp"

int main() {
    CScene3D scene;
    CScene3D::tPointPtr p = scene.getPoint(0);
    (*p).position[0] = 1;
    CScene3D::tCameraPtr c = scene.createCamera();
    (*c).rotation[0] = 1;
    scene.saveToObj("/mnt/test.obj");
    return 0;
}
