#include "border.h"

#include "canvas.h"

namespace xui {

SolidBorder::SolidBorder(Color color, int width)
    : color_(color), width_(width) {}

void SolidBorder::PaintBorder(Canvas* canvas, const Rect& view_rect) {
  canvas->DrawRect(view_rect, width_, color_);
}

}  // namespace xui