#include <cmath>
#include <iostream>

using std::sqrt;

class Vec3;
using Point3 = Vec3;

class Vec3
{
    public:
        Vec3() : m_Elements{0.0, 0.0, 0.0} {}
        Vec3(double e0, double e1, double e2) : m_Elements{e0, e1, e2} {}

        inline double x() const { return m_Elements[0]; } 
        inline double y() const { return m_Elements[1]; } 
        inline double z() const { return m_Elements[2]; }

        Vec3 operator-() const { return Vec3{-m_Elements[0], -m_Elements[1], -m_Elements[2]}; }
        double operator[](int i) const { return m_Elements[i]; }
        double& operator[](int i) { return m_Elements[i]; }

        Vec3& operator+=(const Vec3& v)
        {
            m_Elements[0] += v.m_Elements[0];
            m_Elements[1] += v.m_Elements[1];
            m_Elements[2] += v.m_Elements[2];
            return *this;
        }

        Vec3& operator*=(double t)
        {
            m_Elements[0] *= t;
            m_Elements[1] *= t;
            m_Elements[2] *= t;
            return *this;
        }

        Vec3& operator/=(double t)
        {
            return *this *= 1/t;
        }

        double lenght() const
        {
            return sqrt(lenghtSquared());
        }

        double lenghtSquared() const
        {
            return  m_Elements[0] * m_Elements[0] +
                    m_Elements[1] * m_Elements[1] +
                    m_Elements[2] * m_Elements[2];
        }

        double m_Elements[3];
};

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.m_Elements[0] << " " << v.m_Elements[1] << " " << v.m_Elements[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3& v)
{
    return Vec3{u.m_Elements[0] + v.m_Elements[0], u.m_Elements[1] + v.m_Elements[1], u.m_Elements[2] + v.m_Elements[2]};
}

inline Vec3 operator-(const Vec3 &u, const Vec3& v)
{
    return Vec3{u.m_Elements[0] - v.m_Elements[0], u.m_Elements[1] - v.m_Elements[1], u.m_Elements[2] - v.m_Elements[2]};
}

inline Vec3 operator*(const Vec3 &u, const Vec3& v)
{
    return Vec3{u.m_Elements[0] * v.m_Elements[0], u.m_Elements[1] * v.m_Elements[1], u.m_Elements[2] * v.m_Elements[2]};
}

inline Vec3 operator*(double t, const Vec3& v)
{
    return Vec3{t * v.m_Elements[0], t * v.m_Elements[1], t * v.m_Elements[2]};
}

inline Vec3 operator*(const Vec3& v, double t)
{
    return t * v;
}

inline Vec3 operator/(const Vec3& v, double t)
{
    return (1/t) * v;
}

inline double dot(const Vec3& u, const Vec3& v)
{
    return  u.m_Elements[0] * v.m_Elements[0] +
            u.m_Elements[1] * v.m_Elements[1] +
            u.m_Elements[2] * v.m_Elements[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
    return Vec3(u.m_Elements[1] * v.m_Elements[2] - u.m_Elements[2] * v.m_Elements[1],
                u.m_Elements[2] * v.m_Elements[0] - u.m_Elements[0] * v.m_Elements[2],
                u.m_Elements[0] * v.m_Elements[1] - u.m_Elements[1] * v.m_Elements[0]);
}

inline Vec3 unitVector(const Vec3& v)
{
    return v / v.lenght();
}