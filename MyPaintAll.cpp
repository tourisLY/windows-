#include "MyPaintAll.h"

MyPaintAll::MyPaintAll() {
}

MyPaintAll::~MyPaintAll() {
}
//MyPaintAll::MyPaint(){
//	int w, h;
//
//	//����mdc�����ϱ���ͼ
//	SelectObject(bufdc, bg);
//	BitBlt(mdc, 0, 0, 640, 480, bufdc, 0, 0, SRCCOPY);
//
//	//����Ŀǰ���ƶ�����ȡ����Ӧ����������߶�ͼ����ȷ����ȡ����ͼ�Ŀ����߶�
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
//	//����Ŀǰ��X��Y��ֵ��mdc�Ͻ���͸����ͼ��Ȼ����ʾ�ڴ��ڻ�����
//	BitBlt(mdc, x, y, w, h, bufdc, num * w, h, SRCAND);
//	BitBlt(mdc, x, y, w, h, bufdc, num * w, 0, SRCPAINT);
//
//	BitBlt(hdc, 0, 0, 640, 480, mdc, 0, 0, SRCCOPY);
//
//	tPre = GetTickCount();         //��¼�˴λ�ͼʱ��
//
//	num++;			//��ֹҲ�ڶ�
//	if (num == 8)
//		num = 0;
//
//}