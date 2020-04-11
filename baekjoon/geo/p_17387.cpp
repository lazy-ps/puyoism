#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct vec2
{
    long long x, y;
    vec2(long long x, long long y) :x(x), y(y) {}
    vec2 operator-(const vec2& v) const { return vec2(x - v.x, y - v.y); }
    bool operator<(const vec2& v) const { return this->y < v.y || (this->y == v.y && this->x < v.x); }
    long long operator*(const vec2& v) const { return x * v.y - v.x * y; }
};

int ccw(const vec2& a, const vec2& b, const vec2& c)
{
    long long ret = (c - b) * (a - b);
    return ret ? (ret > 0LL ? 1 : -1) : 0;
}

#define PVV pair<vec2, vec2>

bool is_intersect(const PVV& a, const PVV& b)
{
    auto L1_s = a.first, L1_e = a.second, L2_s = b.first, L2_e = b.second;
    int L1_ccw = ccw(L1_s, L1_e, L2_s) * ccw(L1_s, L1_e, L2_e);
    int L2_ccw = ccw(L2_s, L2_e, L1_s) * ccw(L2_s, L2_e, L1_e);
    if(L1_ccw == 0 && L2_ccw == 0) // parallel
    {
        if(L1_e < L1_s) swap(L1_s, L1_e);
        if(L2_e < L2_s) swap(L2_s, L2_e);

        return !(L1_e < L2_s || L2_e < L1_s);
    }
    
    return L1_ccw <= 0 && L2_ccw <= 0;
}

int main(void)
{
    int x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    cout << is_intersect(make_pair(vec2(x1, y1), vec2(x2, y2)), make_pair(vec2(x3, y3), vec2(x4, y4)));
    return 0;
}
