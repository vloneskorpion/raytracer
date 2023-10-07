#pragma once

#include "Vec3.hpp"

class Ray
{
    public:
        Ray();
        Ray(const Point3& origin, const Vec3& direction) : m_Origin{origin}, m_Direction{direction} {}

        inline Point3 origin() const { return m_Origin; }
        inline Vec3 direction() const { return m_Direction; }

        Point3 at(double t) const
        {
            return m_Origin + t * m_Direction;
        }

        private:
            Point3 m_Origin;
            Vec3 m_Direction;
};