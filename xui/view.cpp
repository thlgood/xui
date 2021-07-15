#include "view.h"

#include "border.h"
#include "widget.h"

namespace xui {

void View::OnPaint(Canvas* canvas) {}

Rect View::Bounds() { return bounds_; }

Rect View::LocalBounds() { return Rect(0, 0, bounds_.width, bounds_.height); }

void View::SetBounds(const Rect& rect) {
  if (rect != bounds_) {
    bounds_ = rect;
    Layout();
  }
}

void View::Layout() {}

View* View::AddChildView(View* view) {
  _ASSERT(view);
  _ASSERT(!view->parent_);
  _ASSERT(this != view);

  if (!view || this == view || view->parent_ == this) {
    return nullptr;
  }

  children_.push_back(view);
  view->parent_ = this;
  view->is_root_view_ = false;

  return view;
}

void View::RemoveChildView(View* view) {
  _ASSERT(view);
  _ASSERT(view->parent_ == this);
  auto iter = std::find(children_.begin(), children_.end(), view);
  _ASSERT(iter != children_.end());

  children_.erase(iter);
}

void View::InvalidateAll() {
  Widget* widget = GetWidget();
  if (!widget) {
    //_ASSERT(widget);
    return;
  }

  if (widget) {
    widget->InvalidateAll();
  }
}

void View::InvalidateRect(const Rect& rect) {}

xui::Widget* View::GetWidget() {
  if (is_root_view_) {
    return widget_;
  }

  View* parent_view = parent_;
  while (parent_view) {
    if (parent_view->is_root_view_) {
      return parent_view->GetWidget();
    } else {
      parent_view = parent_view->parent_;
    }
  }

  return nullptr;
}

void View::SetWidget(Widget* widget) {
  _ASSERT(is_root_view_);
  if (!is_root_view_) {
    return;
  }

  if (widget_ == widget) {
    return;
  }

  widget_->init_params_.root_view_ = nullptr;

  widget_ = widget;
  widget_->init_params_.root_view_ = this;

  // todo notify
}

bool View::IsRootView() { return is_root_view_; }

xui::View* View::GetParent() { return parent_; }

void View::SetBorder(std::unique_ptr<Border> border) {
  border_ = std::move(border);
  InvalidateRect(LocalBounds());
}

void View::SetBackground(std::unique_ptr<Background> background) {
  background_ = std::move(background);
  InvalidateRect(LocalBounds());
}

void View::OnMouseEnter() {}

void View::OnMouseMove(Point pt) {}

void View::OnMouseLeave() {}

Size View::GetPreferredSize() const {
  if (preferred_size_) {
    return *preferred_size_;
  } else {
    return CalculatePreferredSize();
  }
}

void View::SetPreferredSize(const Size& size) {
  preferred_size_.reset(new Size(size));
}

Size View::CalculatePreferredSize() const { return Size(); }


void View::Paint(Canvas* canvas) {
  PaintBackground(canvas);
  OnPaint(canvas);
  PaintBorder(canvas);

  for (View* v : children_) {
    canvas->Save();
    xui::Offset offset(v->Bounds().point());
    canvas->Clip(v->Bounds());
    canvas->TransForm(offset);
    v->Paint(canvas);
    canvas->Restore();
  }
}

void View::PaintBorder(Canvas* canvas) {
  if (border_) {
    border_->PaintBorder(canvas, LocalBounds());
  }
}

void View::PaintBackground(Canvas* canvas) {
  if (background_) {
    background_->PaintBackground(canvas, LocalBounds());
  }
}

View* View::FindViewByPoint(Point pt) {
  View* target_child_view = nullptr;
  bool handled = false;

  for (auto i = children_.rbegin(); i != children_.rend(); ++i) {
    View* v = *i;
    if (v->bounds_.Contains(pt)) {
      target_child_view = v;
      break;
    }
  }

  if (target_child_view) {
    Point pt_in_child = pt - target_child_view->bounds_.point();
    return target_child_view->FindViewByPoint(pt_in_child);
  } else if (bounds_.Contains(pt)) {
    return this;
  } else {
    return nullptr;
  }
}

Point View::GetPosInRootView() {
  View* v = this;
  Point pt;

  while (v) {
    if (v->IsRootView()) {
      break;
    }
    pt = pt + bounds_.point();
    v = v->GetParent();
  }

  return pt;
}

void View::MouseLeaveEvent() {}

}  // namespace xui