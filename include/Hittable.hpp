#pragma once

#include "Ray.hpp"
#include "Interval.hpp"

struct HitRecord
{
    Point3 p;
    Vec3 normal;
    double t;
    bool frontFace;

    void setFaceNormal(const Ray& r, const Vec3& outwardNormal)
    {
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
    public:
        virtual ~Hittable() = default;
        virtual bool hit(const Ray& r, Interval interval, HitRecord& rec) const = 0;
};