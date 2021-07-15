#pragma once
#include <string>

#include "font.h"
#include "view.h"

namespace xui {

class Label : public View {
 public:
  Label();
  Label(const std::wstring& content, Font font = Font(),
        Color color = 0xFF000000);
  ~Label();

  void SetText(const std::wstring& text);
  void SetFont(const Font& font);
  void SetColor(Color color);

 protected:
  virtual Size CalculatePreferredSize() const override;
  virtual void OnPaint(Canvas* canvas) override;

 private:
  std::wstring content_;
  Font font_;
  Color color_;
  std::unique_ptr<Size> preferred_size_cache_;
};

}  // namespace xui