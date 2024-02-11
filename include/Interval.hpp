#pragma once

#include "Utility.hpp"

class Interval
{
    public:
        Interval() : m_Min{+infinity}, m_Max{-infinity} {}
        Interval(double min, double max) : m_Min{min}, m_Max{max} {}

        bool contains(double x) const
        {
            return m_Min <= x and x <= m_Max;
        }

        bool surrounds(double x) const
        {
            return m_Min < x and x < m_Max;
        }

        inline double getMax() const { return m_Max; }
        inline double getMin() const { return m_Min; }

        double clamp(double x) const
        {
            if (x < m_Min) return m_Min;
            if (x > m_Max) return m_Max;
            return x;
        }

        static const Interval empty, universe;
    private:
        double m_Min, m_Max;
};

const static Interval empty(+infinity, -infinity);
const static Interval universe(-infinity, +infinity);