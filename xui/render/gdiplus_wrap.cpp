#include "gdiplus_wrap.h"

#pragma comment(lib, "gdiplus")

GdiplusWrap::GdiplusWrap()
{
  Gdiplus::GdiplusStartupInput StartupInput;
  Gdiplus::GdiplusStartup(&token_, &StartupInput, NULL);
}

GdiplusWrap::~GdiplusWrap()
{
  Gdiplus::GdiplusShutdown(token_);
}

