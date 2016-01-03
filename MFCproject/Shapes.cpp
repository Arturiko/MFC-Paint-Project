#include "StdAfx.h"
#include "Shapes.h"

IMPLEMENT_SERIAL (Shapes, CObject, 1)
IMPLEMENT_SERIAL (draw_rect, CObject, 1)
IMPLEMENT_SERIAL (draw_ellipse, CObject, 1)

Shapes::Shapes(void){}
Shapes::~Shapes(void){}
draw_rect::draw_rect(){}
draw_ellipse::draw_ellipse(){}