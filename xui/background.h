#pragma once

#include "types.h"

namespace xui {
struct Rect;
class Canvas;

class Background {
 public:
  ~Background() {}
  virtual void PaintBackground(Canvas* canvas, const Rect& view_rect) = 0;
};

class SolidBackground : public Background {
 public:
  SolidBackground(Color color);

  void PaintBackground(Canvas* canvas, const Rect& view_rect) override;

 private:
  Color color_;
};

}  // namespace xui