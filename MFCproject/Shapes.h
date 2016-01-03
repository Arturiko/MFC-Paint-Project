#pragma once
#include "afx.h"

class Shapes :public CObject
{
	DECLARE_SERIAL (Shapes)
public:
	void Serialize (CArchive& ar)
	{
		CObject::Serialize (ar);
		if (ar.IsStoring ())
		{
			ar << x1;
			ar << x2;
			ar << y1;
			ar << y2;
			ar << Pen_Thin;
			ar << curColor;
		}
		else
		{
			ar >> x1;
			ar >> x2;
			ar >> y1;
			ar >> y2;
			ar >> Pen_Thin;
			ar >> curColor;
		}
	}
public:
	Shapes(void);

	Shapes(int xx1,int yy1, int xx2, int yy2,int Pen_Thin, COLORREF curColor)
	{
		x1=xx1;
		x2=xx2;
		y1=yy1;
		y2=yy2;
		this->Pen_Thin=Pen_Thin;
		this->curColor=curColor;
	}
	virtual void Draw(CDC *dc){};
	virtual int getx1() {return x1;}
	virtual int gety1() {return y1;}
	virtual int getx2() {return x2;}
	virtual int gety2() {return y2;}
	virtual void setx1(int xx1){this->x1=xx1;	}
	virtual void sety1(int yy1){this->y1=yy1;	}
	virtual void setx2(int xx2){this->x2=xx2;}
	virtual void sety2(int yy2){this->y2=yy2;}

	virtual ~Shapes(void);

protected:
COLORREF curColor;
int Pen_Thin;
int x1,y1,x2,y2;
};

class draw_rect:public Shapes
{
	DECLARE_SERIAL (draw_rect)
public:
	draw_rect();
	draw_rect(int xx1,int yy1, int xx2, int yy2,int Pen_Thin, COLORREF curColor)
		:Shapes(xx1,yy1,xx2,yy2,Pen_Thin,curColor){}
	void Draw(CDC *dc)
	{
		CPen myPen1(PS_SOLID,Pen_Thin,curColor);
		CPen *old_pen;
		old_pen = dc->SelectObject(&myPen1);
		dc->Rectangle(x1, y1,x2, y2);
		dc->SelectObject(old_pen);
	}
};
class draw_ellipse:public draw_rect
{
		DECLARE_SERIAL (draw_ellipse)
public:
	draw_ellipse();
	draw_ellipse(int xx1,int yy1, int xx2, int yy2,int Pen_Thin, COLORREF curColor)
		:draw_rect(xx1,yy1,xx2,yy2,Pen_Thin,curColor){}
	void Draw(CDC *dc)
	{
		CPen myPen1(PS_SOLID,Pen_Thin,curColor);
		CPen *old_pen;
		old_pen = dc->SelectObject(&myPen1);
		dc->Ellipse(x1, y1,x2, y2);
		dc->SelectObject(old_pen);
	}
};