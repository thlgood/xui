#include "controls/label.h"

namespace xui {
Label::Label() {}

Label::Label(const std::wstring& content, Font font /*= Font()*/,
             Color color /*= 0*/)
    : content_(content), font_(font), color_(color) {}

Label::~Label() {}

void Label::SetText(const std::wstring& text) {
  if (text != content_) {
    content_ = text;
    InvalidateRect(LocalBounds());  // todo need replaced by updatelayout();
  }
}

void Label::SetFont(const Font& font) {
  font_ = font;
  InvalidateRect(LocalBounds());
}

void Label::SetColor(Color color) {
  if (color_ != color) {
    color_ = color;
    InvalidateRect(LocalBounds());
  }
}

Size Label::CalculatePreferredSize() const {
  if (preferred_size_cache_) {
    return *preferred_size_cache_;
  } else {
    return Size();  // todo
  }
}

void Label::OnPaint(Canvas* canvas) {
  canvas->DrawString(LocalBounds(), content_, font_, color_);
}

}  // namespace xui