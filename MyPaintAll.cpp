#include "MyPaintAll.h"

MyPaintAll::MyPaintAll() {
}

MyPaintAll::~MyPaintAll() {
}
//MyPaintAll::MyPaint(){
//	int w, h;
//
//	//先在mdc中贴上背景图
//	SelectObject(bufdc, bg);
//	BitBlt(mdc, 0, 0, 640, 480, bufdc, 0, 0, SRCCOPY);
//
//	//按照目前的移动方向取出对应人物的连续走动图，并确定截取人物图的宽度与高度
//	SelectObject(bufdc, girl[dir]);
//	switch (dir) {
//		case 0:
//			w = 55;
//			h = 74;
//			break;
//		case 1:
//			w = 53;
//			h = 77;
//			break;
//		case 2:
//			w = 60;
//			h = 74;
//			break;
//		case 3:
//			w = 60;
//			h = 74;
//			break;
//	}
//	//按照目前的X，Y的值在mdc上进行透明贴图，然后显示在窗口画面上
//	BitBlt(mdc, x, y, w, h, bufdc, num * w, h, SRCAND);
//	BitBlt(mdc, x, y, w, h, bufdc, num * w, 0, SRCPAINT);
//
//	BitBlt(hdc, 0, 0, 640, 480, mdc, 0, 0, SRCCOPY);
//
//	tPre = GetTickCount();         //记录此次绘图时间
//
//	num++;			//静止也在动
//	if (num == 8)
//		num = 0;
//
//}