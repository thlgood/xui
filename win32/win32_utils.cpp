#include "win32_utils.h"

int xui::RcWidth(const RECT& rc) { return rc.right - rc.left; }

int xui::RcHeight(const RECT& rc) { return rc.bottom - rc.top; }
