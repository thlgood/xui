#include "main_view.h"

#include "xui/background.h"
#include "xui/border.h"
#include "xui/widget.h"
#include "xui/controls/label.h"

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
  label_view_ = static_cast<xui::Label*>(AddChildView(new xui::Label(L"你好，世界")));
  label_view_->SetFont({L"Microsoft YaHei", 20});
  label_view_->SetPreferredSize(xui::Size(140, 40));
  label_view_->SetBackground(
      std::make_unique<xui::SolidBackground>(0x33F83425));

  xui::Widget* widget = new xui::Widget;
  xui::Widget::InitParams init_param;
  init_param.root_view_ = this;
  init_param.widget_delegate_ = this;

  xui::Rect rect(100, 100, 600, 400);
  widget->Init(init_param);
  widget->Create(rect);
  widget->Show();
}

void MainView::Layout() { 
  sub_view_->SetBounds(xui::Rect(10, 5, 80, 80)); 
  xui::Size size = label_view_->GetPreferredSize();
  label_view_->SetBounds(xui::Rect(100, 10, size.width, size.height));
}

void MainView::OnPaint(xui::Canvas* canvas) {
  //canvas->FillRect(LocalBounds(), is_hovered_ ? 0xFFFFFFFF : 0xFFFF0000);
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