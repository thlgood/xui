#pragma once

#include <gdiplus.h>
#include <windows.h>

#include <memory>
#include <string>

namespace xui {
class Canvas;
class Font {
 public:
  Font(const wchar_t* font_name = L"Microsoft YaHei", int font_size = 12);
  Font(const Font&);
  Font(Font&&) = default;

  bool IsNull() const;

  Font& operator=(const Font& font);

 private:
  bool TryCreate();

 private:
  friend class Canvas;
  std::wstring font_name_;
  int font_size_;
  std::unique_ptr<Gdiplus::Font> font_impl_ptr_;
};
}  // namespace xui