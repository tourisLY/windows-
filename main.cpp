#include <windows.h>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "Player.h"
#include "Enemy_one.h"
#include "Bullet.h"
#include "Shop.h"
//ȫ�ֱ�������
HBITMAP girl[4], bg,role;
HDC		hdc, mdc, bufdc, mdcStart, mdcShop;
HWND	hWnd;
DWORD	tPre, tNow,moveNow,movePre;
HBITMAP fullmap, shopMap;//��Ϸ�ĳ���

int sceneNum = 0;//��ǰ�������
//���廭��
HBRUSH redBrush, whiteBrush, greenBrush, yellowBrush, moneyBrush;

const int cols = 40, rows = 24; //������ÿ���ͼ�ĳ��Ϳ�
//��Ҷ���
Player player(100, 10, 10, 5);
int xMoveInput = 0, yMoveInput = 0;//�ƶ�����
int xBulletInput = 0, yBulletInput = 0; //�ӵ�����
const int bulletMax = 10;//�ӵ��������
int bulletHit = 0;//��¼�ӵ����й���ı��
char healthPoints[32];//��ʾѪ����ֵ��
char moneyNum[32];//��ʾ��Ǯ����
int killNum = 0;//��ɱ����
int sceneStart = 0;//������Ϸ��ʼ����

//�ӵ���ʼ��
Bullet bullet[bulletMax];
//�̵��ʼ��
Shop shop;

int testtt = 0;
//���˳�ʼ��
Enemy_one enemy_one[100];
int enemyNum = 0;
int bossLevel = 1;

//�洢���λ��
POINT mousePosition{0, 0};
bool wFlag,aFlag,sFlag,dFlag,upFlag,rightFlag,downFlag,leftFlag;


//���庯��
void EnemyMovePosition();
void BulletShoot();
void EnemyCreate();
void BulletMovePosition();
void PlayerMovePosition();
void BossOnePaint();
void BossOneTimer(WPARAM wParam);
void BossStartScene();
void MoneyNumPaint(int moneyNumber, int xPos, int yPos);
void ShopScenePaint();
int GetRandNum(int modNum, int randNum);
void MouseClick(LPARAM lParam);
void BossLevelFinish();
void ShopRefresh();
void ShopGoodPurchase(int goodNum);
void ShopEnd();
void SceneChangePaint();
void ScenePlayerSet();
void MapChange(int _xPos, int _yPos, int num);


//��ɫ��ͼ���������ټ�����ɫ�͵���λ��
int popMap[rows * cols] = {0};//��ұ��99
int bulletMap[rows * cols] = {0} ;//�ӵ����99
//��ͼ
int mapIndex[rows * cols] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //��1��
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //2
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //4
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //5
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //6
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //7
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //8
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //9
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //10/
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //11
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //12
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //13
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //14
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //15
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //16
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //17
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //18
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //19
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //20
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //21
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //22
                              1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //23
                              1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 //��25��
                            };//��8��

//������buffer
char buffer[32];

//Enemy_one enemy[10] = new Enemy_one[10] {}
//end
//ȫ�ֺ�������
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				MyPaint(HDC hdc);

HBITMAP map[3];
char filename[20] = "";
int rowNum, colNum;

//****WinMain������������ڵ㺯��***********************
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {
	MSG msg;

	MyRegisterClass(hInstance);

	//��ʼ��
	if (!InitInstance (hInstance, nCmdShow)) {
		return FALSE;
	}


	//��ʼ����ˢ
	redBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	whiteBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	greenBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
	yellowBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
	moneyBrush = (HBRUSH)CreateSolidBrush(RGB(198, 145, 69));

	//��ʼ�����
	if (mapIndex[player.yPos * 40 + player.xPos] != 0)
		mapIndex[player.yPos * 40 + player.xPos] = 0;
	if (player.Alive(mapIndex)) {
	} else {
		MessageBox(0, "player cant create!", "UNKNOWN ERROR", MB_OK);
	}
	popMap[player.yPos * 40 + player.xPos] = 99;
//	MessageBox(0, buffer, "hpnow", MB_OK);
//	sprintf(buffer, "%d", player.hpNow);

//	sprintf(buffer, "%d", player.hpMax);
//	MessageBox(0, buffer, "homax", MB_OK);


	GetMessage(&msg, NULL, NULL, NULL); //��ʼ��msg
	//��Ϸѭ��
	while ( msg.message != WM_QUIT ) {
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE) ) {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		} else {
			tNow = GetTickCount();
			if (tNow - tPre >= 40) {
				if (player.hpNow <= 0) {
					MessageBox(0, "YOU ARE DEAD!", "FAIL", MB_OK);
					PostQuitMessage(0);
				}
				BossLevelFinish();
				MyPaint(hdc);
			}
//				sprintf(buffer, "%lu", number);
//				MessageBox(0, "in the refresh", "My Message", MB_OK);
		}
	}
	return msg.wParam;
}

//****���һ��������****
ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "202205010409";
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

//****��ʼ������****
// ����λͼ���趨���ֳ�ʼֵ
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	hWnd = CreateWindow("202205010409", "202205010409", WS_OVERLAPPEDWINDOW,
	                    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd) {
		return FALSE;
	}

	MoveWindow(hWnd, 10, 10, cols * 32 + 16, rows * 32 + 36, true); //1280�ǿ�һ������ʮ�� 800�Ǹߣ�һ��25��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	////////////////////////////////////////


	sceneNum = sceneStart;
	shop.goodsAlive();

	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);//СDC��for���ͼ
	bufdc = CreateCompatibleDC(hdc);//СDC��forС��ͼ
	fullmap = CreateCompatibleBitmap(hdc, cols * 32,
	                                 rows * 32); //�Ƚ���fullmapΪ�հ׵�λͼ���������߷ֱ�Ϊ������*ͼ����롰����*ͼ��ߡ���
	//���ͼ��˫����
	mdcStart = CreateCompatibleDC(hdc);
	SelectObject(mdc, fullmap);   //��fullmap����mdc��


	mdcShop = CreateCompatibleDC(hdc);
	shopMap = CreateCompatibleBitmap(hdc, cols * 32, rows * 32); //�洢�̵�λͼ



	int i, x, y;

	//���ظ���λͼ
	for (i = 0; i < 2;
	        i++) { //����ѭ��ת��ͼ���ļ�����ȡ������ͼ����롰map[i]���С�ͼ���ļ���Ϊ��map0.bmp���͡�map1.bmp���ȡ�
		sprintf(filename, "scene/map%d.bmp", i);
		map[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	}
	role = (HBITMAP)LoadImage(NULL, "scene/role.bmp",IMAGE_BITMAP, 62, 32, LR_LOADFROMFILE);

	//����mapIndex�����еĶ���ȡ����Ӧͼ�飬���е�ͼƴ��
	//˫����1���Ȱ�С��ͼ�������ͼ��
	for (i = 0; i < rows * cols; i++) {
		SelectObject(bufdc,
		             map[mapIndex[i]]); //����mapIndex[i]�еĴ���ѡȡ��Ӧ��ͼ�鵽bufdc�С�����Ϊ��0����ȡ��map[0]�����Դ�����

		rowNum = i / cols;   //���б��
		colNum = i % cols;   //���б��
		x = colNum * 32;     //����ͼX����
		y = rowNum * 32;     //����ͼY����

		BitBlt(mdc, x, y, 32, 32, bufdc, 0, 0, SRCCOPY); //��mdc�Ͻ�����ͼ
	}
//	MessageBox(0, "first", "My Message", MB_OK);//

//�����̵�λͼ
// TODO ������Ҫ���룡
//	sprintf(filename, "scene/%s.bmp", "ShopScene");
	shopMap = (HBITMAP)LoadImage(NULL, "scene/ShopScene.bmp", IMAGE_BITMAP, 1280, 768, LR_LOADFROMFILE );
	SelectObject(mdcShop, shopMap);
	// BitBlt(mdcShop, 0, 0, 1280, 768
	// , bufdc, 0, 0, SRCCOPY);

	MyPaint(hdc);   //����������ѭ�������mdc�ϵ�ͼ����ͼ֮��fullmap����ƴ�ӳ����ĵ�ͼ����ʱ�ٵ���MyPaint�����������д�����ͼ��



	return TRUE;
}

//****�Զ����ͼ����****
// ������ͼ����������������ͼ
void MyPaint(HDC hdc) {
	switch (sceneNum) {
		case 0: {
			BossStartScene();
			break;
		}
		case 1: {
			BossOnePaint();
			break;
		}
		case 2: {
			SceneChangePaint();
			break;
		}
		case 3: {
			ScenePlayerSet();
			break;
		}
		case 99: {
			ShopScenePaint();
			break;
		}
		default: {
			break;
		}
	}

	tPre = GetTickCount();         //��¼�˴λ�ͼʱ��

}

//****��Ϣ������***********************************
// 1.���¡�Esc������������

// 2.���·����������ͼ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CREATE:
			SetTimer(hWnd, 1, 2000, NULL);//���ﴴ��
			SetTimer(hWnd, 2, 1100, NULL);//�����ƶ�
			SetTimer(hWnd, 3, 200, NULL); //����ƶ�
			SetTimer(hWnd, 4, 210, NULL);//�ж��ӵ�����
			SetTimer(hWnd, 5, 500, NULL);//�ӵ��ƶ�
			break;
		case WM_TIMER:
			if (sceneNum == 1) {
				BossOneTimer(wParam);
			}
			break;
		case WM_KEYDOWN:	     //���¼�����Ϣ
			//�жϰ������������
			switch (wParam) {
				case VK_UP:				  //���¡�������
					yBulletInput = -1;
					if(upFlag == false){
						upFlag = true;
						BulletShoot();
					}
					break;
				case VK_DOWN:			  //���¡�������
					yBulletInput = 1;
					if(downFlag == false){
						downFlag = true;
						BulletShoot();
					}
					break;
				case VK_LEFT:			  //���¡�������
					xBulletInput = -1;
					if(leftFlag == false){
						leftFlag = true;
						BulletShoot();
					}
					break;
				case VK_RIGHT:			   //���¡�������
					xBulletInput = 1;
					if(rightFlag == false){
						rightFlag = true;
						BulletShoot();
					}
					break;
				default:
					break;
			}
			break;
		case WM_KEYUP: {
			if (wParam == 119 || wParam == 87 || wParam == 97 || wParam == 65 || wParam == 115 || wParam == 83 || wParam == 100
			        || wParam == 68) {
				xMoveInput = yMoveInput = 0;
				wFlag = aFlag = sFlag = dFlag = false;
			} else {
				switch (wParam) {
					case VK_UP: {
						
						yBulletInput = 0;
						if(upFlag == true)upFlag =false;
						break;
					}
					case VK_DOWN: {
						yBulletInput = 0;
						if(downFlag == true)downFlag = false;
						break;
					}
					case VK_LEFT: {
						xBulletInput = 0;
						if(leftFlag == true)leftFlag = false;
						break;
					}
					case VK_RIGHT: {
						xBulletInput = 0;
						if(rightFlag == true)rightFlag = false;
						break;
					}
					default: {
						break;
					}
				}
			}
			break;
		}
		case WM_CHAR: { //���¼�����ĸ����Ϣ����

			if (wParam == 119 || wParam == 87) { //������w����W
				xMoveInput = 0;
				yMoveInput = -1;
				if(wFlag == false){
					wFlag = true;
					PlayerMovePosition();
					movePre = GetTickCount();
				}
			}
			if (wParam == 97 || wParam == 65) { //������a����A
				xMoveInput = -1;
				yMoveInput = 0;
				if(aFlag == false){
					aFlag = true;
					PlayerMovePosition();
					movePre = GetTickCount();
				}
			}
			if (wParam == 115 || wParam == 83) { //������s����S
				xMoveInput = 0;
				yMoveInput = 1;
				if(sFlag == false){
					sFlag = true;
					PlayerMovePosition();
					movePre = GetTickCount();
				}
			}
			if (wParam == 100 || wParam == 68) { //������d����D
				xMoveInput = 1;
				yMoveInput = 0;
				if(dFlag == false){
					dFlag = true;
					PlayerMovePosition();
					movePre = GetTickCount();
				}
			}


			break;
		}
		case WM_LBUTTONDOWN: {
			MouseClick(lParam);
			break;
		}
		case WM_DESTROY:			    	//���ڽ�����Ϣ
			int i;

			DeleteDC(mdc);
			DeleteDC(bufdc);
			for (i = 0; i < 4; i++)
				DeleteObject(girl[i]);
			DeleteObject(bg);
			ReleaseDC(hWnd, hdc);
			//���ٶ�ʱ��
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);
			KillTimer(hWnd, 4);
			KillTimer(hWnd, 5);
			PostQuitMessage(0);
			break;
		default:							//������Ϣ
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
void EnemyMovePosition() {
	bool flag = false;
	for (int i = 0; i < bossLevel * 6; i++) {
		flag = false;
		if (enemy_one[i].alive) {
			mapIndex[enemy_one[i].yPos * cols + enemy_one[i].xPos] = 0;
			popMap[enemy_one[i].yPos * cols + enemy_one[i].xPos] = 0;
			flag = enemy_one[i].EnemyMove(player.xPos, player.yPos, mapIndex, GetRandNum(2, 0));
			mapIndex[enemy_one[i].yPos * cols + enemy_one[i].xPos] = 3;
			popMap[enemy_one[i].yPos * cols + enemy_one[i].xPos] = i + 1;
			if (bulletMap[enemy_one[i].yPos * 40 + enemy_one[i].xPos] != 0) {
				if (enemy_one[i].Damage(player.attackPower)) {
					killNum++;
					mapIndex[enemy_one[i].yPos * cols + enemy_one[i].xPos] = 0;
					popMap[enemy_one[i].yPos * cols + enemy_one[i].xPos] = 0;
					// sprintf(buffer, "%d", killNum);
					// MessageBox(0, buffer, "UNKNOWN ERROR", MB_OK);
					player.GetMoney(enemy_one[i].value);
				}

				bullet[bulletMap[enemy_one[i].yPos * 40 + enemy_one[i].xPos]].Dead();
				bulletMap[enemy_one[i].yPos * 40 + enemy_one[i].xPos] = 0;
			}
		}
		if (enemy_one[i].alive && flag == true) {
			player.Damage(enemy_one[i].attackPower);
		}
	}
}

void BulletShoot() {
	if ((xBulletInput != 0 || yBulletInput != 0)
	        && bulletMap[(player.yPos + yBulletInput) * 40 + (player.xPos + xBulletInput)] == 0) {
		for (int i = 0; i < bulletMax; i++) {
			if (bullet[i].alive == false ) {
				bullet[i].Alive(player.xPos, player.yPos, xBulletInput, yBulletInput, player.attackPower);
				bulletMap[bullet[i].yPos * 40 + bullet[i].xPos] = i;
				// if (mapIndex[bullet[i].yPos * 40 + bullet[i].xPos] != 0) {
				// 	int shootHit = popMap[bullet[i].yPos * 40 + bullet[i].xPos];
				// 	bulletMap[bullet[i].yPos * 40 + bullet[i].xPos] = 0;
				// 	if (shootHit != 0 && shootHit != 99) {
				// 		if (enemy_one[shootHit].Damage(player.attackPower)) {
				// 			killNum++;
				// 			player.GetMoney(enemy_one[shootHit].value);
				// 		}
				// 	}
				// }
				break;
			}
		}
	}
}

void EnemyCreate() {
	int xxx, yyy;
	if (enemyNum < bossLevel * 6) {
		for (int i = 0; i <= 3; i++) {
			xxx = GetRandNum(40, 0);
			yyy = GetRandNum(24, 0);
			if (mapIndex[yyy * 40 + xxx] == 0 && enemy_one[i].mapNew[yyy * 40 + xxx] == 0) {
				enemy_one[enemyNum].Alive(xxx, yyy, mapIndex);
				mapIndex[yyy * 40 + xxx] = 3;
				popMap[yyy * 40 + xxx] = enemyNum + 1;
				enemyNum++;
				break;
			}
		}

	}
}

void BulletMovePosition() {
	for (int i = 0; i < bulletMax; i++) {
		if (bullet[i].alive == true ) {
			bulletMap[bullet[i].yPos * 40 + bullet[i].xPos] = 0;
			bulletHit = bullet[i].Move(mapIndex, popMap);
			bulletMap[bullet[i].yPos * 40 + bullet[i].xPos] = i;
			if (bulletHit != 0) {
				bulletHit--;
				bulletMap[bullet[i].yPos * 40 + bullet[i].xPos] = 0;
				if (enemy_one[bulletHit].Damage(player.attackPower)) {
					mapIndex[enemy_one[bulletHit].yPos * 40 + enemy_one[bulletHit].xPos] = 0;
					popMap[enemy_one[bulletHit].yPos * 40 + enemy_one[bulletHit].xPos] = 0;
//									enemy_one[bulletHit].alive = false;
					killNum ++;
					// sprintf(buffer, "%d, %s", killNum,"in the bullet");
					// MessageBox(0, buffer, "UNKNOWN ERROR", MB_OK);
					player.GetMoney(enemy_one[i].value);
				}
//								sprintf(buffer, "%d %d %d",bulletHit,player.attackPower,enemy_one[bulletHit].hpNow);
//								MessageBox(0, buffer, "My Message", MB_OK);
			}
		}
	}
}
void PlayerMovePosition() {
	mapIndex[player.yPos * 40 + player.xPos] = 0;
	popMap[player.yPos * 40 + player.xPos] = 0;
	player.PlayerMove(xMoveInput, yMoveInput, mapIndex);
	mapIndex[player.yPos * 40 + player.xPos] = 2;
	popMap[player.yPos * 40 + player.xPos] = 99;
}

void ShopScenePaint() {
	//  SelectObject(mdcShop, shopMap);
	//  BitBlt(mdcShop, 0, 0, cols * 32, rows * 32, bufdc, 0, 0, SRCCOPY);
	if (shop.shopFlag == false) {
		ShopRefresh();
		shop.shopFlag = true;
	}



	BitBlt(hdc, 0, 0, cols * 32, rows * 32, mdcShop, 0, 0, SRCCOPY);
	MoneyNumPaint(player.money, 1000, 10);

	//��Ʒһ
	if (shop.goodExit[0] == true) {
		const char *tempChar1 = shop.goods[shop.shopNo[0]].name.data();
		sprintf(buffer, "%s", tempChar1 );
		TextOut(hdc, 410, 175, buffer, shop.goods[shop.shopNo[0]].nameLen);
		const char *tempChar2 = shop.goods[shop.shopNo[0]].describe.data();
		sprintf(buffer, "%s", tempChar2 );
		TextOut(hdc, 410, 225, buffer, shop.goods[shop.shopNo[0]].describeLen);
		MoneyNumPaint(shop.goods[shop.shopNo[0]].value, 410, 275);
	}
	if (shop.goodExit[1] == true) {
		//��Ʒ��
		const char *tempChar3 = shop.goods[shop.shopNo[1]].name.data() ;
		sprintf(buffer, "%s", tempChar3);
		TextOut(hdc, 410, 345, buffer, shop.goods[shop.shopNo[1]].nameLen);
		const char *tempChar4 = shop.goods[shop.shopNo[1]].describe.data();
		sprintf(buffer, "%s", tempChar4);
		TextOut(hdc, 410, 395, buffer, shop.goods[shop.shopNo[1]].describeLen);
		MoneyNumPaint(shop.goods[shop.shopNo[1]].value, 410, 445);
	}
	if (shop.goodExit[2] == true) { //��Ʒ��
		const char *tempChar5 = shop.goods[shop.shopNo[2]].name.data();
		sprintf(buffer, "%s", tempChar5);
		TextOut(hdc, 410, 515, buffer, shop.goods[shop.shopNo[2]].nameLen);
		const char *tempChar6 = shop.goods[shop.shopNo[2]].describe.data();
		sprintf(buffer, "%s", tempChar6 );
		TextOut(hdc, 410, 565, buffer, shop.goods[shop.shopNo[2]].describeLen);
		MoneyNumPaint(shop.goods[shop.shopNo[2]].value, 410, 615);
	}

	MoneyNumPaint(shop.shopRefreshSpend, 1030, 370);

	// sprintf(buffer, "%d", shop.goods[shop.shopNo[0]].value);
	// TextOut(hdc, 410, 275,buffer, strlen(buffer));



//	TextOut(hdc, 500,500,"����",2);
}

void BossOnePaint() {
	//����mdc�����ϱ���ͼ
	SelectObject(bufdc, bg);
	// BitBlt(mdc, 0, 0, cols * 32, rows * 32, bufdc, 0, 0, SRCCOPY);

	//����Ŀǰ���ƶ�����ȡ����Ӧ����������߶�ͼ����ȷ����ȡ����ͼ�Ŀ����߶�
	//���ƹ���

	BitBlt(hdc, 0, 0, cols * 32, rows * 32, mdc, 0, 0, SRCCOPY);

	//�����ǳ���
	//Ѫ��
	SelectObject(hdc, whiteBrush);
	Rectangle(hdc, 10, 10, player.hpMax, 30);
	SelectObject(hdc, redBrush);
	Rectangle(hdc, 10, 10, player.hpNow, 30);
	//�滭Ѫ��ui
	sprintf(healthPoints, "%s%d%s%d", "hp:", player.hpNow, "/", player.hpMax);

	//�滭����

	for (int i = 0; i < 20; i++) {
		if (enemy_one[i].alive) {
			if (enemy_one[i].isHurt == true) {
				SelectObject(hdc, redBrush);
				enemy_one[i].RedCancle();
			} else {
				SelectObject(hdc, whiteBrush);
			}
			Rectangle(hdc, enemy_one[i].xPos * 32 + 6, enemy_one[i].yPos * 32 + 6, enemy_one[i].xPos * 32 + 26,
			          enemy_one[i].yPos * 32 + 26);
			SelectObject(hdc, redBrush);
			Rectangle(hdc, enemy_one[i].xPos * 32 + 6, enemy_one[i].yPos * 32 + 2,
			          enemy_one[i].xPos * 32 + 26 * enemy_one[i].hpNow / enemy_one[i].hpMax, enemy_one[i].yPos * 32 + 6 );

		}
	}

	SelectObject(bufdc, role);
	BitBlt(hdc, player.xPos * 32, player.yPos * 32,  31,  32, bufdc, 32, 0, SRCAND);
	BitBlt(hdc, player.xPos * 32, player.yPos * 32,  31,  32, bufdc, 0, 0, SRCPAINT);
	//�滭���
	if (player.alive) {
		SelectObject(hdc, greenBrush);
		// Ellipse(hdc, player.xPos * 32 + 6, player.yPos * 32 + 6, player.xPos * 32 + 26, player.yPos * 32 + 26 );
	}



	//�滭�ӵ�
	SelectObject(hdc, yellowBrush);
	for (int i = 0; i < bulletMax; i++) {
		if (bullet[i].alive) {

			Ellipse(hdc, bullet[i].xPos * 32 + 10, bullet[i].yPos * 32 + 10, bullet[i].xPos * 32 + 22, bullet[i].yPos * 32 + 22);
			// MessageBox(0, "i in paintING!!", "BULLET", MB_OK);
			// if (i == 0) {
			// 	sprintf(buffer, "%d ", killNum);
			// 	TextOut(hdc, 120 + player.hpMax, 10, buffer, 1);
			// }
		}
	}


	TextOut(hdc, 20 + player.hpMax, 10, healthPoints, 10);

	//�滭���
	MoneyNumPaint(player.money, 1000, 10);
}

void BossStartScene() {
	RECT rect;
	HPEN hp, hpOld;
	GetClientRect(hWnd, &rect);
	hp = (HPEN)CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
	hpOld = (HPEN)SelectObject(hdc, hp);
	POINT l[3] = {{rect.left, rect.top}, {rect.left, rect.bottom}, {(rect.left * 24 + rect.right * 5) / 29, rect.bottom}};
	POINT I[2] = {{(rect.left * 21 + rect.right * 8) / 29, rect.top}, {(rect.left * 21 + rect.right * 8) / 29, rect.bottom}};
	POINT y[4] = {{(rect.left * 17 + rect.right * 41) / 58, rect.bottom}, {(rect.left * 17 + rect.right * 41) / 58, (rect.top * 5 + rect.bottom * 4) / 9},
		{(rect.left * 11 + rect.right * 18) / 29, (rect.top)}, (rect.left * 6 + rect.right * 23) / 29, rect.top
	};
	POINT E[4] = {{(rect.right), rect.top},
		{(rect.left * 5 + rect.right * 24) / 29, rect.top},
		{(rect.left * 5 + rect.right * 24) / 29, rect.bottom},
		{(rect.right), rect.bottom}
	};
	for (int i = 0; i < 2; i++) {
		MoveToEx(hdc, l[i].x, l[i].y, NULL);
		LineTo(hdc, l[i + 1].x, l[i + 1].y);
	}
//y//I
	for (int i = 0; i < 1; i++) {
		MoveToEx(hdc, I[i].x, I[i].y, NULL);
		LineTo(hdc, I[i + 1].x, I[i + 1].y);
	}
	//U
	MoveToEx(hdc, (rect.left * 18 + rect.right * 11) / 29, (rect.top + rect.bottom * 3) / 4, NULL);
	LineTo(hdc, (rect.left * 18 + rect.right * 11) / 29, rect.top);
	MoveToEx(hdc, (rect.left * 13 + rect.right * 16) / 29, (rect.top + rect.bottom * 3) / 4, NULL);
	LineTo(hdc, (rect.left * 13 + rect.right * 16) / 29, rect.top);
	Arc(hdc, (rect.left * 18 + rect.right * 11) / 29, (rect.top + rect.bottom ) / 2,
	    (rect.left * 13 + rect.right * 16) / 29, (rect.bottom),
	    (rect.left * 18 + rect.right * 11) / 29, (rect.top + rect.bottom * 3) / 4, (rect.left * 13 + rect.right * 16) / 29,
	    (rect.top + rect.bottom * 3) / 4
	   );
	//E
	for (int i = 0; i < 3; i++) {
		MoveToEx(hdc, E[i].x, E[i].y, NULL);
		LineTo(hdc, E[i + 1].x, E[i + 1].y);
	}
	MoveToEx(hdc, (rect.left * 5 + rect.right * 24) / 29, (rect.top + rect.bottom) / 2, NULL);
	LineTo(hdc, rect.right, (rect.top + rect.bottom) / 2);
	for (int i = 0; i < 2; i++) {
		MoveToEx(hdc, y[i].x, y[i].y, NULL);
		LineTo(hdc, y[i + 1].x, y[i + 1].y);
	}
//			j

	MoveToEx(hdc, y[1].x, y[1].y, NULL);
	LineTo(hdc, y[3].x, y[3].y);
	char bufferStart[32];
	sprintf(bufferStart, "%s", "202205010409");
	TextOut(hdc, 400, 200, bufferStart, 12);
	sprintf(bufferStart, "%s", "MOVE:WASD");
	TextOut(hdc, 400, 300, bufferStart, 9);
	sprintf(bufferStart, "%s", "ATTACK: ��������");
	TextOut(hdc, 400, 400, bufferStart, 16);
	sprintf(bufferStart, "%s", "START GAME");
	TextOut(hdc, 400, 500, bufferStart, 10);
	BitBlt(hdc, 0, 0, cols * 32, rows * 32, mdcStart, 0, 0, SRCCOPY);
	hp = (HPEN)SelectObject(hdc, hpOld);
	DeleteObject(hp);
}

void BossOneTimer(WPARAM wParam) {
	switch (wParam) {
		case 3: {
			moveNow = GetTickCount();
			if(moveNow - movePre >= 200)
			PlayerMovePosition();
			break;
		}
		case 5: {
			BulletMovePosition();

			break;
		}
		case 4: {
			BulletShoot();
			break;
		}
		case 1: {
			EnemyCreate();
//					TextOut(hdc, 100, 200, "11", 10);
			break;
		}
		case 2: {
			EnemyMovePosition();
//					TextOut(hdc, 100, 300, "22", 10);

			break;
		}
		default: {
			break;
		}
	}
}

void MoneyNumPaint(int moneyNumber, int xPos, int yPos) {
	SelectObject(hdc, moneyBrush);
	Ellipse(hdc, xPos, yPos, xPos + 20, yPos + 20);
	sprintf(moneyNum, "%d", moneyNumber);
	TextOut(hdc, xPos + 30, yPos, moneyNum, strlen(moneyNum));
}

int GetRandNum(int modNum, int randNum) {
	srand(tPre + randNum);
	return rand() % modNum;
}

void MouseClick(LPARAM lParam) {

	// sprintf(buffer, "%d", mapIndex[(mousePosition.y/32)*40 * (mousePosition.x/32)]);
	// MessageBox(hWnd, buffer, "1", MB_OK);
	mousePosition.y = HIWORD(lParam);
	mousePosition.x = LOWORD(lParam);
	// sprintf(buffer, "x:%d, y:%d", mousePosition.x, mousePosition.y);
	// MessageBox(hWnd, buffer, "1", MB_OK);
	switch (sceneNum) {
		case 0: {
			if (mousePosition.x > 400 && mousePosition.x < 500 && mousePosition.y > 500 && mousePosition.y < 530) {
				sceneNum = 1;
				break;
			}
			break;
		}
		case 2: {
			if (mousePosition.x > 0 && mousePosition.x < 50 && mousePosition.y > 0 && mousePosition.y < 30) {
				sceneNum = 3;
				MessageBox(hWnd, "��ѡ����ҵ�λ�ã�", "ѡ��λ��", MB_OK);
			} else {
				if (player.money > 0) {
					MapChange(mousePosition.x / 32, mousePosition.y / 32, 1);
					// mapIndex[(mousePosition.y/32)*40 * (mousePosition.x/32)] = 1;
					SelectObject(bufdc,
					             map[mapIndex[1]]);
					BitBlt(mdc, (mousePosition.x / 32) * 32, (mousePosition.y / 32) * 32, 32, 32, bufdc, 0, 0, SRCCOPY);
					player.GetShop(1);
				} else {
					MessageBox(hWnd, "����", "����ʧ��", MB_OK);
				}

			}


			break;
		}
		case 3: {

			if (mapIndex[(mousePosition.y / 32) * 40 + (mousePosition.x / 32)] == 0 && player.mapNew[(mousePosition.y / 32) * 40 + (mousePosition.x / 32)] == 0) {
				player.xPos = mousePosition.x / 32;
				player.yPos = mousePosition.y / 32;
				sceneNum = 1;
			} else {
				MessageBox(hWnd, "�����޷�����", "����ʧ��", MB_OK);
			}
			break;
		}
		case 99: {
			if (mousePosition.x >= 1027 && mousePosition.x <= 1176 && mousePosition.y >= 174 && mousePosition.y <= 369) {
				//TODO ˢ���̵깦��
				if (player.money >= shop.shopRefreshSpend) {
					ShopRefresh();
					shop.RefreshSpend(2);
					player.GetShop(shop.shopRefreshSpend-1);
					
				}

				break;
			}
			if (mousePosition.x >= 1027 && mousePosition.x <= 1176 && mousePosition.y >= 459 && mousePosition.y <= 657) {
				//TODO ��һ�ع���

				ShopEnd();
				break;
			}
			if (mousePosition.x >= 400 && mousePosition.x <= 900 && mousePosition.y >= 170 && mousePosition.y <= 320) {
				//TODO ������Ʒһ

				if (shop.goodExit[0] == true)
					ShopGoodPurchase(0);
				break;
			}
			if (mousePosition.x >= 400 && mousePosition.x <= 900 && mousePosition.y >= 340 && mousePosition.y <= 490) {
				//TODO ������Ʒ��
				if (shop.goodExit[1] == true)
					ShopGoodPurchase(1);
				break;
			}
			if (mousePosition.x >= 400 && mousePosition.x <= 900 && mousePosition.y >= 510 && mousePosition.y <= 660) {
				//TODO ������Ʒ��
				if (shop.goodExit[2] == true)
					ShopGoodPurchase(2);
				break;
			}
			break;
		}
		default: {
			break;
		}
	}
}

void BossLevelFinish() {
	if (killNum >= bossLevel * 6) {
		bossLevel++;
		killNum = 0;
		enemyNum = 0;
		sceneNum = 99;
		shop.shopFlag = false;
		popMap[player.yPos * 40 + player.xPos] = 0;
		mapIndex[player.yPos * 40 + player.xPos] = 0;
		for (int i = 0; i < bulletMax; i++) {
			bulletMap[bullet[i].yPos * 40 + bullet[i].xPos] = 0;
			bullet[i].Dead();
		}
		sprintf(buffer, "%s", "�ؿ������");
		MessageBox(hWnd, buffer, "111", MB_OK);
	}
}

void ShopRefresh() {

	int noNum = 0, tempNum;
	for (int i = 0; i < 3; i++)
		shop.goodExit[i] = true;
	while (noNum < 3) {
		tempNum = GetRandNum(shop.shopNum, noNum);
		shop.shopNo[noNum] = tempNum;
		noNum++;
//		sprintf(buffer, "%d", tempNum);
//		MessageBox(hWnd, buffer, "11", MB_OK);
		// for (int i = 0; i < noNum - 1; i++) {
		// 	if (shop.shopNo[i] == tempNum) {
		// 		noNum--;
		// 		break;
		// 	}
		// }
	}
}

void ShopGoodPurchase(int goodNum) {
	if (shop.goodExit[goodNum] == true) {
		if (player.money >= shop.goods[shop.shopNo[goodNum]].value) {
			shop.ShopSale(goodNum);
			player.GetShop(shop.goods[shop.shopNo[goodNum]].value);
			player.hpMax += shop.goods[shop.shopNo[goodNum]].hpMax;
			player.attackPower += shop.goods[shop.shopNo[goodNum]].attackPower;
		} else {
			sprintf(buffer, "%s", "������");
			MessageBox(hWnd, buffer, "����ʧ�ܣ�", MB_OK);
		}
	}
}
void ShopEnd() {
	player.hpNow = player.hpMax;
	bossLevel ++;
	sceneNum = 2;
	MessageBox(hWnd, "�����������Ի�һ��Ǯ���ı����", "��ʾ", MB_OK);
	shop.RefreshSpend(0);
}

void SceneChangePaint() {
	BitBlt(hdc, 0, 0, cols * 32, rows * 32, mdc, 0, 0, SRCCOPY);
	MoneyNumPaint(player.money, 1000, 10);
	sprintf(buffer, "%s", "��һ��");
	TextOut(hdc, 0, 0, buffer, 6);
}

void ScenePlayerSet() {

	BitBlt(hdc, 0, 0, cols * 32, rows * 32, mdc, 0, 0, SRCCOPY);
}

void MapChange(int _xPos, int _yPos, int num) {
	player.MapNewChange(_xPos, _yPos);
	for (int i = 0; i < 100; i++)
		enemy_one[i].MapNewChange(_xPos, _yPos);
	for(int i=0;i<10;i++)bullet[i].MapNewChange(_xPos, _yPos);
}