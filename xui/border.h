#pragma once

#include "types.h"

namespace xui {
class View;
class Canvas;

class Border {
 public:
  virtual ~Border() {}
  virtual void PaintBorder(Canvas* canvas, const Rect& view_rect) = 0;
};

class SolidBorder : public Border {
 public:
  SolidBorder(Color color, int width);
  virtual void PaintBorder(Canvas* canvas, const Rect& view_rect) override;

 private:
  Color color_;
  int width_;
};

}  // namespace xui