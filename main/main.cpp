#include <iostream>

#include "Logger.hpp"
#include "FilePathManager.hpp"

#include "Vec3.hpp"
#include "Color.hpp"       
#include "Ray.hpp"

bool hitSphere(const Point3& center, double radius, const Ray& r)
{
    const auto oc = r.origin() - center;
    const auto a = dot(r.direction(), r.direction());
    const auto b = 2.0 * dot(r.direction(), oc);
    const auto c = dot(oc, oc) - radius * radius;

    return b * b - 4 * a * c >= 0;
    // a, b, c
}

Color rayColor(const Ray& r)
{
    if(hitSphere(Point3(0, 0 , -1), 0.5, r))
    {
        return Color(0, 0 ,1);
    }

    Vec3 unitDirection = unitVector(r.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * Color{1, 1 ,1} + a * Color{0.5, 0.7, 1.0};
}



int main()
{
    const auto logger = Logger{FilePathManager::getPath("configuration.conf")};

    // Image
    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 4000;
    int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // Camera
    auto focalLenght = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);
    auto cameraCenter = Point3(0, 0, 0);

    auto viewportU = Vec3(viewportWidth, 0 , 0);
    auto viewportV = Vec3(0, -viewportHeight, 0);

    auto pixelDeltaU = viewportU / imageWidth;
    auto pixelDeltaV = viewportV / imageHeight;

    auto viewportUpperLeft = cameraCenter - Vec3(0, 0, focalLenght) - (viewportU / 2) - (viewportV / 2);
    auto pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    // Render
    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for(int j = 0; j < imageHeight; j++)
    {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << " " << std::flush;
        for(int i = 0; i < imageWidth; i++)
        {
            auto pixelCenter = pixel00Loc + ( i * pixelDeltaU) + ( j * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            Ray r{cameraCenter, rayDirection};

            Color pixelColor = rayColor(r);
            writeColor(std::cout, pixelColor);
        }
    }
}