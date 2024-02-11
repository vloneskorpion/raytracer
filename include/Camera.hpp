#pragma once

#include "Color.hpp"
#include "Hittable.hpp"

class Camera
{
    public:
        double m_AspectRatio = 1.0;
        int m_ImageWidth = 100;
        int samplesPerPixel = 10;
        int maxDepth = 10;

        void Render(const Hittable& world)
        {
            initialize();

            std::cout << "P3\n" << m_ImageWidth << " " << m_ImageHeight << "\n255\n";

            for(int j = 0; j < m_ImageHeight; j++)
            {
                std::clog << "\rScanlines remaining: " << (m_ImageHeight - j) << " " << std::flush;
                for(int i = 0; i < m_ImageWidth; i++)
                {
                    Color pixelColor{0, 0, 0};
                    for(int sample = 0; sample < samplesPerPixel; sample++)
                    {
                        Ray r = getRay(i, j);
                        pixelColor += rayColor(r, maxDepth, world);
                    }

                    writeColor(std::cout, pixelColor, samplesPerPixel);
                }
            }
            
            std::clog << "\r Done.              \n";
        }

    private:

        int m_ImageHeight;
        Point3 m_Center;
        Point3 m_Pixel00Loc;
        Vec3 m_pixelDetlaU;
        Vec3 m_pixelDeltaV;


        void initialize()
        {
            m_ImageHeight = static_cast<int>(m_ImageWidth / m_AspectRatio);
            m_ImageHeight = (m_ImageHeight < 1) ? 1 : m_ImageHeight;

            m_Center = {0, 0, 0};

            // Camera
            auto focalLenght = 1.0;
            auto viewportHeight = 2.0;
            auto viewportWidth = viewportHeight * (static_cast<double>(m_ImageWidth) / m_ImageHeight);

            auto viewportU = Vec3(viewportWidth, 0 , 0);
            auto viewportV = Vec3(0, -viewportHeight, 0);

            m_pixelDetlaU = viewportU / m_ImageWidth;
            m_pixelDeltaV = viewportV / m_ImageHeight;

            auto viewportUpperLeft = m_Center - Vec3(0, 0, focalLenght) - (viewportU / 2) - (viewportV / 2);
            m_Pixel00Loc = viewportUpperLeft + 0.5 * (m_pixelDetlaU + m_pixelDeltaV);
        }

        Color rayColor(const Ray& r, int depth, const Hittable& world)
        {
            HitRecord rec;

            if(depth < 0)
            {
                return Color{0, 0, 0};
            }

            if(world.hit(r, Interval{0.001, infinity}, rec))
            {
                const auto direction = randomOnHemisphere(rec.normal);
                return 0.5 * rayColor(Ray(rec.p, direction), depth-1, world);
            }

            Vec3 unitDirection = unitVector(r.direction());
            auto a = 0.5 * (unitDirection.y() + 1.0);
            return (1.0 - a) * Color{1, 1 ,1} + a * Color{0.5, 0.7, 1.0};
        }

        Ray getRay(int i, int j) const
        {
            auto pixelCenter = m_Pixel00Loc + (i * m_pixelDetlaU) + (j * m_pixelDeltaV);
            auto pixelSample = pixelCenter + pixelSampleSquare();

            auto rayOrigin = m_Center;
            auto rayDirection = pixelSample - rayOrigin;

            return Ray(rayOrigin, rayDirection);
        }

        Vec3 pixelSampleSquare() const
        {
            auto px = -0.5 + random_double();
            auto py = -0.5 + random_double();

            return (px * m_pixelDetlaU) + (py * m_pixelDeltaV);
        }
};
