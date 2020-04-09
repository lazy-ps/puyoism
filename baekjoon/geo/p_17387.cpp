#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct vec2
{
    long long x, y;
    vec2(long long x, long long y) :x(x), y(y) {}
    vec2 operator-(const vec2& v) const { return vec2(x - v.x, y - v.y); }
    bool operator==(const vec2& v) const { return this->x == v.x && this->y == v.y; }
    bool operator<(const vec2& v) const { return this->y < v.y || (this->y == v.y && this->x < v.x); }
    long long operator*(const vec2& v) const { return x * v.y - v.x * y; }
};

long long ccw(const vec2& a, const vec2& b, const vec2& c)
{
    long long ret = (c - b) * (a - b);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}

#define PVV pair<vec2, vec2>

bool is_intersect(const PVV& a, const PVV& b)
{
    vec2 u = a.second - a.first;
    vec2 v = b.second - b.first;
    if(u * v == 0LL) // parallel
    {
        if((a.first - b.second) * u != 0LL) return false; // parallel but not in line

        vector<pair<vec2, int>> points({make_pair(a.first, 0), make_pair(a.second, 0), make_pair(b.first, 1), make_pair(b.second, 1)});
        sort(points.begin(), points.end());

        if(points[1].first == points[2].first)
            return true;
        else if(points[0].second == points[1].second)
            return false;
        else
            return true;
    }

    return ccw(a.first, a.second, b.first) * ccw(a.first, a.second, b.second) <= 0LL &&
        ccw(b.first, b.second, a.first) * ccw(b.first, b.second, a.second) <= 0LL;
}

int main(void)
{
    int x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    cout << is_intersect(make_pair(vec2(x1, y1), vec2(x2, y2)), make_pair(vec2(x3, y3), vec2(x4, y4)));
    return 0;
}
