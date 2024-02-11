#include <iostream>

#include "Logger.hpp"
#include "FilePathManager.hpp"

#include "Vec3.hpp"
#include "Color.hpp"       
#include "Ray.hpp"
#include "Hittable.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Utility.hpp"
#include "Camera.hpp"

int main()
{
    const auto logger = Logger{FilePathManager::getPath("configuration.conf")};

    HittableList world{};
    world.add(std::make_shared<Sphere>(Point3{0, 0 , -1}, 0.5));
    world.add(std::make_shared<Sphere>(Point3{0, -100.5, -1}, 100));

    Camera cam;
    cam.m_AspectRatio = 16.0 / 9.0;
    cam.m_ImageWidth = 400;
    cam.samplesPerPixel = 100;
    cam.maxDepth = 50;

    cam.Render(world);
}