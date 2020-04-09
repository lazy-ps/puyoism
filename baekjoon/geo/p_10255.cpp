#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <tuple>

using namespace std;
#define NO 0
#define POINT 1
#define LINE 2

struct vec2
{
    long long x, y;
    vec2() :x(), y() {}
    vec2(long long x, long long y) :x(x), y(y) {}
    vec2 operator-(const vec2& v) const { return vec2(x - v.x, y - v.y); }
    bool operator==(const vec2& v) const { return this->x == v.x && this->y == v.y; }
    bool operator!=(const vec2& v) const { return !(*this==v); }
    bool operator<(const vec2& v) const { return this->y < v.y || (this->y == v.y && this->x < v.x); }
    long long operator*(const vec2& v) const { return x * v.y - v.x * y; }
};

long long ccw(const vec2& a, const vec2& b, const vec2& c)
{
    return (c - b) * (a - b);
}

#define PVV pair<vec2, vec2>

int is_intersect(const PVV& a, const PVV& b)
{
    vec2 u = a.second - a.first;
    vec2 v = b.second - b.first;
    long long c = u * v;
    if (c == 0LL) {
        if((a.first - b.second) * u != 0LL) return NO;
        vector<pair<vec2, int>> points({make_pair(a.first, 0), make_pair(a.second, 0), make_pair(b.first, 1), make_pair(b.second, 1)});
        sort(points.begin(), points.end());

        if(points[1].first == points[2].first)
            return points[1].first != b.first ? POINT : NO;  // trick for no count in start point of rectangle's side
        else if(points[0].second == points[1].second)
            return NO;
        else
            return LINE;
    }
    
    return ccw(a.first, a.second, b.first) * ccw(a.first, a.second, b.second) <= 0LL &&
        ccw(b.first, b.second, a.first) * ccw(b.first, b.second, a.second) <= 0LL &&
        ccw(a.first, a.second, b.first) != 0LL;  // trick for no count in start point of rectangle's side
}

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

int main(void)
{
    cin.tie(nullptr);
    int T, xmin, ymin, xmax, ymax, x1, y1, x2, y2;
    vector<int> intersects(4);
    cin >> T;
    while(T--)
    {
        cin >> xmin >> ymin >> xmax >> ymax;
        cin >> x1 >> y1 >> x2 >> y2;
        PVV line = make_pair(vec2(x1, y1), vec2(x2, y2));
        int intersect_num = 0;

        intersects[LEFT] = is_intersect(line, make_pair(vec2(xmin, ymin), vec2(xmin, ymax)));
        intersects[UP] = is_intersect(line, make_pair(vec2(xmin, ymax), vec2(xmax, ymax)));
        intersects[RIGHT] = is_intersect(line, make_pair(vec2(xmax, ymax), vec2(xmax, ymin)));
        intersects[DOWN] = is_intersect(line, make_pair(vec2(xmax, ymin), vec2(xmin, ymin)));
        
        for(auto &v : intersects)
        {
            if(v == LINE)
            {
                intersect_num = 4;
                break;
            }
            intersect_num += v;
        }
        cout << intersect_num << '\n';
    }
    return 0;
}
