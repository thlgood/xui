#pragma once

#include <windows.h>
#include <gdiplus.h>

class GdiplusWrap
{
public:
  GdiplusWrap();

  ~GdiplusWrap();

private:
  ULONG_PTR token_;
};

