#pragma once
#include <stdint.h>

namespace xui {

using Color = uint32_t;

struct Point {
  Point() = default;
  Point(int ix, int iy) : x(ix), y(iy) {}

  Point operator-(const Point& pt) const { return Point(x - pt.x, y - pt.y); }
  Point operator+(const Point& pt) const { return Point(x + pt.x, y + pt.y); }

  int x = 0;
  int y = 0;
};

using Offset = Point;

struct Size {
  Size() = default;
  Size(int w, int h) : width(w), height(h) {}

  int width = 0;
  int height = 0;
};

struct Rect {
  Rect() = default;
  Rect(int ix, int iy, int w, int h) : x(ix), y(iy), width(w), height(h) {}

  Rect(const Size& s) : x(0), y(0), width(s.width), height(s.height) {}

  Size size() { return Size(width, height); }

  Point point() { return Point(x, y); }

  bool operator==(const Rect& rect) const {
    return x == rect.x && y == rect.y && width == rect.width &&
           height == rect.height;
  }
  bool operator!=(const Rect& rect) const { return !operator==(rect); }

  bool Contains(const Point& pt) const {
    return pt.x >= x && pt.x <= (x + width) && pt.y >= y &&
           pt.y <= (y + height);
  }

  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;
};

}  // namespace xui