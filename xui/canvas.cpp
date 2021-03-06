#include "canvas.h"

#include <gdiplus.h>
#include <gdiplusbrush.h>
#include <windows.h>

#include "font.h"

namespace xui {
Canvas::Canvas(HDC hdc, int w, int h) : hdc_(hdc), width_(w), height_(h) {
  graphics_ = new Gdiplus::Graphics(hdc_);
}

Canvas::~Canvas() {
  if (graphics_) {
    delete graphics_;
  }
}

void Canvas::Save() { graphics_state_.push_back(graphics_->Save()); }

void Canvas::Restore() {
  graphics_->Restore(graphics_state_.back());
  graphics_state_.pop_back();
}

void Canvas::DrawRect(const Rect& rect, int width, Color color) {
  Gdiplus::Pen pen(color, (Gdiplus::REAL)width);

  float fwidth = (float)width;
  float offset = fwidth / 2.0f;

  graphics_->DrawRectangle(
      &pen, (Gdiplus::REAL)rect.x + offset, (Gdiplus::REAL)rect.y + offset,
      (Gdiplus::REAL)rect.width - fwidth, (Gdiplus::REAL)rect.height - fwidth);
}

void Canvas::FillRect(const Rect& rect, Color color) {
  Gdiplus::SolidBrush brush(color);
  // Gdiplus::Brush* b = &brush;
  graphics_->FillRectangle(&brush, rect.x, rect.y, rect.width, rect.height);
}

void Canvas::DrawString(const Rect& rect, const std::wstring& str, Font& font,
                        Color color) {
  if (str.empty() || rect.width <= 0 || rect.height <= 0) {
    return;
  }

  if (!font.IsNull() || font.TryCreate()) {
    Gdiplus::RectF rect_f((Gdiplus::REAL)rect.x, (Gdiplus::REAL)rect.x,
                          (Gdiplus::REAL)rect.width,
                          (Gdiplus::REAL)rect.height);
    Gdiplus::SolidBrush solid_brush(color);
    Gdiplus::StringFormat format(Gdiplus::StringAlignmentNear);

    graphics_->DrawString(str.c_str(), str.length(), font.font_impl_ptr_.get(),
                          rect_f, &format, &solid_brush);
  }
}

void Canvas::Commit() {
  // todo
}

void xui::Canvas::TransForm(const Offset& offset) {
  Gdiplus::Matrix matrix;
  matrix.Translate((Gdiplus::REAL)offset.x, (Gdiplus::REAL)offset.y);
  graphics_->MultiplyTransform(&matrix);
}

void xui::Canvas::Clip(const Rect& rect) {
  Gdiplus::Rect g_rect(rect.x, rect.y, rect.width, rect.height);
  graphics_->SetClip(g_rect);
}

}  // namespace xui