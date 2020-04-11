#include <iostream>
#include <cmath>

using namespace std;

#define LINE 2
#define POINT 1
#define NONE 0

constexpr double eps = std::numeric_limits<double>::epsilon() * 100;
inline bool eq(double a, double b) { return abs(a - b) < eps; }

struct vec2
{
    double x, y;
    vec2() {}
    vec2(double x, double y) :x(x), y(y) {}
    vec2 operator+(const vec2& v) const { return vec2(x + v.x, y + v.y); }
    vec2 operator-(const vec2& v) const { return vec2(x - v.x, y - v.y); }
    double operator*(const vec2& v) const { return x * v.y - v.x * y; }
    vec2 operator*(double v) const { return vec2(x * v, y * v); }
};

double ccw(const vec2& a, const vec2& b, const vec2& c)
{
    return (c - b) * (a - b);
}

#define PVV pair<vec2, vec2>

int find_intersect(const PVV& a, const PVV& b, vec2& out)
{
    out.x = 0.; out.y = 0.;
    auto L1_s = a.first, L1_e = a.second, L2_s = b.first, L2_e = b.second;
    auto L1_dir = L1_e - L1_s, L2_dir = L2_e - L2_s;

    if(eq(L1_dir * L2_dir, 0.))  // parallel
        return eq(ccw(L1_s, L1_e, L2_s), 0.) ? LINE : NONE;
    
    double p = ((L2_s - L1_s) * L2_dir) / (L1_dir * L2_dir);
    out = L1_s + (L1_dir * p);
    return POINT;
}

int main(void)
{
    int T;
    cin >> T;
    PVV l1, l2;
    vec2 intersect;
    int kind;

    cout.setf(ios::fixed);
    cout.precision(2);

    while(T--)
    {
        cin >> l1.first.x >> l1.first.y >> l1.second.x >> l1.second.y >> l2.first.x >> l2.first.y >> l2.second.x >> l2.second.y;
        kind = find_intersect(l1, l2, intersect);
        if(kind == POINT)
            cout <<  "POINT " << intersect.x << " " << intersect.y << "\n";
        else 
            cout << (kind == LINE ? "LINE\n" : "NONE\n");
    }
}

