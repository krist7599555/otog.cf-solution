// 845 TUMSO19_maxtriarea
// https://api.otog.cf/problem/doc/845
// convex hull and find max triangle with
// https://stackoverflow.com/questions/1621364/how-to-find-largest-triangle-in-convex-hull-aside-from-brute-force-search/1621913#1621913
// https://arxiv.org/abs/1705.11035
// TODO: try devide and conquer algorithm from paper
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <istream>
#include <numeric>
#include <cassert>
#include <tuple>
#include <utility>
#include <cmath>
using namespace std;
#define rep(i,k,n) for(auto i = (k); i != (n); ++i)
#define all(x) (x).begin(), (x).end()
typedef long long lli;

enum ConvexHullCurve { ClockWise, CouterClockWise, Colinear };

template<typename T>
struct Point {
  T x, y;
  Point(T _x, T _y): x(_x), y(_y) {}
  friend inline bool operator==(const Point<T>& lhs, const Point<T>& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
  friend inline bool operator!=(const Point<T>& lhs, const Point<T>& rhs) { return !(lhs == rhs); }
  friend inline Point<T> operator+(const Point<T>& lhs, const Point<T>& rhs) { return Point(lhs.x + rhs.x, lhs.y + rhs.y); }
  friend inline Point<T> operator-(const Point<T>& lhs, const Point<T>& rhs) { return Point(lhs.x - rhs.x, lhs.y - rhs.y); }
  friend inline Point<T> operator*(const Point<T>& lhs, const Point<T>& rhs) { return Point(lhs.x * rhs.x, lhs.y * rhs.y); }
  friend inline Point<T> operator/(const Point<T>& lhs, const Point<T>& rhs) { return Point(lhs.x / rhs.x, lhs.y / rhs.y); }
  static ConvexHullCurve convex_angle(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    auto l2 = c - b;
    auto l1 = b - a;
    auto slope = l2.y * l1.x - l1.y * l2.x;
    if (slope < 0) return ConvexHullCurve::ClockWise;
    if (slope > 0) return ConvexHullCurve::CouterClockWise;
    return ConvexHullCurve::Colinear;
  }
  static double polar_angle(const Point<T>& a, const Point<T>& b) {
    auto diff = b - a;
    return atan2(diff.x, diff.y);
  }
  static T cross(const Point<T>& a, const Point<T>& b) {
    return a.x * b.y - a.y * b.x;
  }
  double polar_angle() const {
    return atan2(this->x, this->y);
  }
  double length() const {
    return std::hypot(this->x, this->y);
  }
  friend std::ostream& operator<<(std::ostream& o, const Point<T>& p) {
    return o << "Point(" << p.x << ',' << p.y << ")";
  }
};

template<typename T = int>
inline T input() {
  T inp; std::cin >> inp; return inp;
}

template<typename T = int>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& vec) {
  o << "std::vector { ";
  int sz = vec.size();
  for (auto& v : vec) {
    o << v << (--sz ? ", " : "");
  }
  return o << " }";
}

/**
 * Convex Hull using [Graham Scan](https://en.wikipedia.org/wiki/Graham_scan) algorithm
 * O(n log n)
*/
std::vector<Point<lli>> graham_scan_convexhull(const std::vector<Point<lli>>& _points) {
  std::vector<Point<lli>> points(_points);
  auto p0 = *std::min_element(all(points), [](auto& lhs, auto& rhs) {
    return std::tie(lhs.y, lhs.x) < std::tie(rhs.y, rhs.x);
    });
  std::sort(all(points), [=](auto& lhs, auto& rhs) {
    auto l = lhs - p0;
    auto r = rhs - p0;
    return std::make_tuple(l.polar_angle(), l.length()) > std::make_tuple(r.polar_angle(), r.length());
    });

  std::vector<Point<lli>> stack = { p0 };
  stack.reserve(_points.size());
  for (auto point : points) {
    if (point == p0) continue;
    while (stack.size() >= 2 && Point<lli>::convex_angle(stack[stack.size() - 2], stack[stack.size() - 1], point) == ConvexHullCurve::ClockWise) {
      stack.pop_back();
    }
    stack.push_back(point);
  }
  return stack;
}

double trangle_area(const Point<lli>& a, const Point<lli>& b, const Point<lli>& c) {
  return 0.5 * Point<lli>::cross(b - a, c - a);
}

int main() {
  {
    // TEST CONVEXHULL
    typedef std::vector<Point<lli>> Points;
    const Points out = graham_scan_convexhull(Points{ {1, 5}, {2, 3}, {2, 2}, {0, 1}, {2, -4}, {5, 1}, {6, 1} });
    const Points ans = Points{ {2, -4}, {6, 1},{1, 5},{0, 1} };
    assert(out == ans);
  }

  typedef std::vector<Point<lli>> Points;
  // const Points out = graham_scan_convexhull(Points{ {1, 5}, {2, 3}, {2, 2}, {0, 1}, {2, -4}, {5, 1}, {6, 1} });
  int n = input();
  std::vector<Point<lli>> out;
  rep(_, 0, n) {
    out.emplace_back(input(), input());
  }
  out = graham_scan_convexhull(out);
  n = out.size();

  int a = 0, b = 1, c = 2;
  std::tuple<int, int, int> ans = { a, b, c };
  auto area = [&out](int i, int j, int k) {
    return trangle_area(out[i], out[j], out[k]);
  };
  while (true) { // #loop A
    while (true) { //  #loop B
      while (area(a, b, c) <= area(a, b, (c + 1) % n)) {// #loop c
        c = (c + 1) % n;
      }
      if (area(a, b, c) <= area(a, (b + 1) % n, c)) {

        b = (b + 1) % n;
        continue;
      } else {

        break;
      }
    }

    if (area(a, b, c) > area(std::get<0>(ans), std::get<1>(ans), std::get<2>(ans))) {
      ans = std::make_tuple(a, b, c);
    }

    a = (a + 1) % n;
    b = (a + 1) % n;
    c = (a + 2) % n;
    if (a == 0) break;
  }

  const double ans_area = area(std::get<0>(ans), std::get<1>(ans), std::get<2>(ans));
  // assert(abs(20.500 - ans_area) < 1e-5);
  printf("%.3lf\n", ans_area);
}

/*
7
1 5
2 3
2 2
0 1
2 -4
5 1
6 1
---
20.500
*/
