#include <iostream>

#include "Logger.hpp"
#include "FilePathManager.hpp"

//#include "Vec3.hpp"
#include "Color.hpp"

int main()
{
    const auto logger = Logger{FilePathManager::getPath("configuration.conf")};

    auto imageWidth = 256;
    auto imageHeight = 256;

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for(int j = 0; j < imageHeight; j++)
    {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << " " << std::flush;
        for(int i = 0; i < imageWidth; i++)
        {
            auto pixelColor = Color{double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0.0};
            writeColor(std::cout, pixelColor);
        }
    }
}