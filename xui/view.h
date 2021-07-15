#pragma once

#include <list>
#include <memory>

#include "background.h"
#include "border.h"
#include "canvas.h"
#include "types.h"

namespace xui {
class Widget;
class Border;

class View {
 public:
  virtual void OnPaint(Canvas* canvas);

  Rect Bounds();
  Rect LocalBounds();
  void SetBounds(const Rect& rect);

  virtual void Layout();

  View* AddChildView(View* view);
  void RemoveChildView(View* view);

  void InvalidateAll();
  void InvalidateRect(const Rect& rect);

  virtual Widget* GetWidget();
  void SetWidget(Widget* widget);

  bool IsRootView();

  View* GetParent();

  void SetBorder(std::unique_ptr<Border> border);
  void SetBackground(std::unique_ptr<Background> background);

  virtual void OnMouseEnter();
  virtual void OnMouseMove(Point pt);
  virtual void OnMouseLeave();

  Size GetPreferredSize() const;
  void SetPreferredSize(const Size& size);

 protected:
  virtual Size CalculatePreferredSize() const;

 private:
  void Paint(Canvas* canvas);
  void PaintBorder(Canvas* canvas);
  void PaintBackground(Canvas* canvas);

  void MouseLeaveEvent();

  View* FindViewByPoint(Point pt);
  Point GetPosInRootView();

 private:
  friend class Widget;
  std::list<View*> children_;
  View* parent_ = nullptr;
  Widget* widget_;

  Rect bounds_;

  bool is_root_view_ = true;
  bool is_hover_ = false;

  std::unique_ptr<Border> border_;
  std::unique_ptr<Background> background_;

  std::unique_ptr<Size> preferred_size_;
};

}  // namespace xui