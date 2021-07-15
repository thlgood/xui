#pragma once

#include <windows.h>

#include <string>
#include <vector>

#include "types.h"

namespace Gdiplus {
class Graphics;
typedef UINT GraphicsState;
}  // namespace Gdiplus

namespace xui {
class Font;

class Canvas {
 public:
  Canvas(HDC hdc, int w, int h);
  ~Canvas();

  void Save();
  void Restore();

  void TransForm(const Offset& offset);
  void Clip(const Rect& rect);

  void DrawRect(const Rect& rect, int width, Color color);
  void FillRect(const Rect& rect, Color color);
  void DrawString(const Rect& rect, const std::wstring& str, Font& font,
                  Color color);

  void Commit();

 private:
  std::vector<Gdiplus::GraphicsState> graphics_state_;
  Gdiplus::Graphics* graphics_;
  int width_ = 0;
  int height_ = 0;
  HDC hdc_ = 0;
};
}  // namespace xui