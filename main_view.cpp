#include "main_view.h"

#include "xui/background.h"
#include "xui/border.h"
#include "xui/widget.h"

class SubSubView : public xui::View {
 public:
  SubSubView() {}

  void OnPaint(xui::Canvas* canvas) override {
    canvas->FillRect(LocalBounds(), is_hovered_ ? 0xFFFFFFFF : 0xFF0000FF);
  }

  void OnMouseEnter() {
    is_hovered_ = true;
    InvalidateAll();
  }

  void OnMouseLeave() {
    is_hovered_ = false;
    InvalidateAll();
  }

 private:
  bool is_hovered_ = false;
};

class SubView : public xui::View {
 public:
  SubView() {
    sub_view_ = AddChildView(new SubSubView);
    SetBorder(std::make_unique<xui::SolidBorder>(0xFF9E9E9E, 2));
    SetBackground(std::make_unique<xui::SolidBackground>(0xFF00FF00));
  }

  void Layout() override { sub_view_->SetBounds(xui::Rect(10, 5, 40, 40)); }

  //   void OnPaint(xui::Canvas* canvas) override {
  //     canvas->FillRect(LocalBounds(),
  //                      is_hovered_ ? 0xFFFFFFFF : 0xFF00FF00);  // todo
  //   }

  void OnMouseEnter() {
    is_hovered_ = true;
    InvalidateAll();
  }

  void OnMouseLeave() {
    is_hovered_ = false;
    InvalidateAll();
  }

 private:
  View* sub_view_ = nullptr;
  bool is_hovered_ = false;
};

MainView::MainView() {}

void MainView::Init() {
  sub_view_ = AddChildView(new SubView);

  xui::Widget* widget = new xui::Widget;
  xui::Widget::InitParams init_param;
  init_param.root_view_ = this;
  init_param.widget_delegate_ = this;

  xui::Rect rect(100, 100, 600, 400);
  widget->Init(init_param);
  widget->Create(rect);
  widget->Show();
}

void MainView::Layout() { sub_view_->SetBounds(xui::Rect(10, 5, 80, 80)); }

void MainView::OnPaint(xui::Canvas* canvas) {
  canvas->FillRect(LocalBounds(), is_hovered_ ? 0xFFFFFFFF : 0xFFFF0000);
}

void MainView::OnMouseEnter() {
  is_hovered_ = true;
  InvalidateAll();
}

void MainView::OnMouseLeave() {
  is_hovered_ = false;
  InvalidateAll();
}

void MainView::OnWidgetDestroy() { PostQuitMessage(0); }