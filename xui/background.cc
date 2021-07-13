#include "background.h"

#include "canvas.h"
#include "types.h"

namespace xui {

SolidBackground::SolidBackground(Color color) : color_(color) {}

void SolidBackground::PaintBackground(Canvas* canvas, const Rect& view_rect) {
  canvas->FillRect(view_rect, color_);
}

}  // namespace xui
