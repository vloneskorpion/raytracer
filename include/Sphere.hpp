#pragma once

#include "Hittable.hpp"
#include "Vec3.hpp"

class Sphere : public Hittable
{
    public:

        Sphere(Point3 center, double radius) : m_Center{center}, m_Radius{radius} {};

        bool hit(const Ray& r, Interval interval, HitRecord& rec) const override
        {
            const auto oc = r.origin() - m_Center;
            const auto a = r.direction().lenghtSquared();
            const auto halfB = dot(oc, r.direction());
            const auto c = oc.lenghtSquared() - m_Radius * m_Radius;

            const auto discriminant = halfB*halfB -  a * c;
            const auto sqrtd = sqrt(discriminant);
            if(discriminant < 0.0)
            {
                return false;
            }

            auto root = (-halfB - sqrtd ) / a;
            if(not interval.surrounds(root))
            {
                root = (-halfB + sqrtd) / a;
                if(not interval.surrounds(root))
                {
                    return false;
                }
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            rec.normal =  rec.p - m_Center / m_Radius;
            Vec3 outwardNormal = (rec.p - m_Center) / m_Radius;
            rec.setFaceNormal(r, outwardNormal);

            return true;
        }

    private:
        Point3 m_Center;
        double m_Radius;
};