#pragma once

#include "Hittable.hpp"

#include <memory>
#include <vector>

class HittableList : public Hittable
{
    public:
        HittableList() {};
        HittableList(std::shared_ptr<Hittable> object) { add(object); }

        void clear() { m_Objects.clear(); }

        void add(std::shared_ptr<Hittable> object)
        {
            m_Objects.push_back(object);
        }

        bool hit(const Ray& r, Interval interval, HitRecord& rec) const override
        {
            HitRecord tempRec;
            bool hitAnything = false;
            auto closestSoFar = interval.getMax();

            for(const auto& object : m_Objects)
            {
                if(object->hit(r, Interval{interval.getMin(), closestSoFar}, tempRec))
                {
                    hitAnything = true;
                    closestSoFar = tempRec.t;
                    rec = tempRec;
                }
            }

            return hitAnything;
        }

    private:
        std::vector<std::shared_ptr<Hittable>> m_Objects;
};