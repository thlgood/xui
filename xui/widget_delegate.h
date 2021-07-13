#pragma once

namespace xui {

class WidgetDelegate {
 public:
  virtual ~WidgetDelegate() {}

  virtual void OnWidgetClosing() {}
  virtual void OnWidgetDestroy() {}
};

}  // namespace xui