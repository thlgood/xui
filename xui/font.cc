#include "font.h"

namespace xui {

Font::Font(const wchar_t* font_name, int font_size):
  font_name_(font_name), 
  font_size_(font_size)
{
}

 Font::Font(const Font& f): font_name_(f.font_name_), font_size_(f.font_size_) {}

bool Font::IsNull() const {
  return !font_impl_ptr_;
}

bool Font::TryCreate() {
  if(font_impl_ptr_) {
    return true;
  }

  font_impl_ptr_ = std::make_unique<Gdiplus::Font>(font_name_.c_str(), 
    (Gdiplus::REAL)font_size_,
    Gdiplus::FontStyle::FontStyleRegular, 
    Gdiplus::Unit::UnitPixel);
  if (font_impl_ptr_->IsAvailable()) {
    return true;
  } else {
    font_impl_ptr_.reset(nullptr);
    return false;
  }
}

xui::Font& Font::operator=(const Font& font) { 
  font_name_ = font.font_name_;
  font_size_ = font.font_size_;
  return *this;
}


}  // namespace xui
