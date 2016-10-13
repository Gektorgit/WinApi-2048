#include <Windows.h>
#include "H_2048.h"
#include "resource.h"
#include <vector>
#include <time.h>
using namespace std;
//========================================================================================================================================================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void Line (int  &temp1, int &temp2, int &temp3,int &temp4, bool &flag);

void Four_Line (int *arr, int flag, bool &flag2, int length);
void Image (HWND hWnd, int *arr);
void Random (HWND hWnd, int *arr, bool &flag);
void Destroi_Button (HWND hWnd, int *arr);
void Button (HWND hWnd, int length);
void Scores (HWND hWnd);

//========================================================================================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

#pragma region 1. WindowClass
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WndProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra  = 0;
	wcl.hInstance = hInstance;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	
	wcl.hbrBackground = (HBRUSH)(16);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = L"X and 0";
	wcl.hIconSm = NULL;
	if (!RegisterClassEx(&wcl))	return 0;
#pragma endregion
#pragma region 2. Window
	HWND hWnd = CreateWindowEx(0, wcl.lpszClassName, L"                  2048", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, 0, WIDTH * 5, HEIGHT * 6, NULL, NULL, hInstance, NULL);
#pragma endregion

#pragma region Menu
	HMENU hMenuMain = CreateMenu();
	HMENU hMenuCorrection = CreatePopupMenu();
	//-----------------------------------------------------------------------------
	AppendMenu(hMenuMain, MF_STRING|MF_POPUP, (UINT)hMenuCorrection, L"&Menu");
	//----------------------------------------------------------------------------
	AppendMenu(hMenuCorrection, MF_STRING, ID_NEW_4x4, L"New Game 4x4");
	AppendMenu(hMenuCorrection, MF_STRING, ID_EXIT, L"Exit");

	//----------------------------------------------------------------------------	
	SetMenu(hWnd, hMenuMain);
#pragma endregion

#pragma region 3. Other Operations
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while(GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
#pragma endregion
}
//========================================================================================================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInst = GetModuleHandle(0);

	static int arr [16] = {0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0,
						   0, 0, 0, 0};
	static bool flag;
	static int Length;
	
	switch(message)
	{
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case ID_NEW_4x4:
				{
					Length = 4;
					flag =1;
					Destroi_Button (hWnd, arr);
					Button (hWnd, Length);
					Image (hWnd,  arr);
					Random (hWnd, arr, flag);
					Button (hWnd, Length);
					Image (hWnd,  arr);
				}
				break;
				
			case ID_EXIT:
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
				}
				break;
			}
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
			case VK_LEFT:
				{
					Four_Line (arr, 1, flag, Length);
					Random (hWnd, arr, flag);
					Image (hWnd,  arr);
					Scores (hWnd);
				}

				break;
			case VK_RIGHT:
				{
					Four_Line (arr, 2, flag, Length);
					Random (hWnd, arr, flag);
					Image (hWnd,  arr);
					Scores (hWnd);
				}
				break;
			case VK_UP:
				{
					Four_Line (arr, 3, flag, Length);
					Random (hWnd, arr, flag);
					Image (hWnd,  arr);
					Scores (hWnd);
				}
				break;
			case VK_DOWN:
				{
					Four_Line (arr, 4, flag, Length);
					Random (hWnd, arr, flag);
					Image (hWnd,  arr);
					Scores (hWnd);
				}
				break;
		}
		break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}
//========================================================================================================================================================================
void Line (int &temp1, int &temp2, int &temp3,int &temp4, bool &flag)
{
#pragma region O
	if (temp1 == 0)
	{
		if (temp2 != 0)
		{
			temp1 = temp2;
			temp2 = 0;
			flag = 1;
		}
		else if (temp3 != 0)
		{
			temp1 = temp3;
			temp3 = 0;
			flag = 1;
		}
		else if (temp4 != 0)
		{
			temp1 = temp4;
			temp4 = 0;
			flag = 1;
		}
	}
	if (temp2 == 0)
	{
		if (temp3 != 0)
		{
			temp2 = temp3;
			temp3 = 0;
			flag = 1;
		}
		else if (temp4 != 0)
		{
			temp2 = temp4;
			temp4 = 0;
			flag = 1;
		}
	}
	if (temp3 == 0)
	{
		if (temp4 != 0)
		{
			temp3 = temp4;
			temp4 = 0;
			flag = 1;
		}
	}
#pragma endregion
	if (temp1 > 0)
	{
		if (temp1 == temp2)
		{
			temp1 = temp1 + temp2;
			Score += temp1;
			temp2 = temp3;
			temp3 = temp4;
			temp4 = 0;
			flag = 1;
			if (temp2 == temp3 && temp2 >0)
			{
				temp2 = temp2 + temp3;
				Score += temp2;
				temp3 = 0;
				flag = 1;
			}
		}
		else if (temp2 == temp3 && temp2 >0)
		{
			temp2 = temp2 + temp3;
			Score += temp2;
			temp3 = temp4;
			temp4 = 0;
			flag = 1;
		}
		else if (temp3 == temp4 && temp3 >0)
		{
			temp3 = temp3 + temp4;
			Score += temp3;
			temp4 = 0;
			flag = 1;
		}
	}
}
//========================================================================================================================================================================
void Four_Line (int *arr, int flag, bool &flag2, int length)
{
	if (flag == 1)
	{
		Line (arr[0],  arr[1],  arr[2],  arr[3],  flag2);
		Line (arr[4],  arr[5],  arr[6],  arr[7],  flag2);
		Line (arr[8],  arr[9],  arr[10], arr[11], flag2);
		Line (arr[12], arr[13], arr[14], arr[15], flag2);
	}
	else if (flag == 2)
	{
		Line (arr[3],  arr[2],  arr[1],  arr[0],  flag2);
		Line (arr[7],  arr[6],  arr[5],  arr[4],  flag2);
	    Line (arr[11], arr[10], arr[9],  arr[8],  flag2);
		Line (arr[15], arr[14], arr[13], arr[12], flag2);
	}
	else if (flag == 3)
	{
		Line (arr[0],  arr[4],  arr[8],  arr[12], flag2);
		Line (arr[1],  arr[5],  arr[9],  arr[13], flag2);
		Line (arr[2],  arr[6],  arr[10], arr[14], flag2);
	    Line (arr[3],  arr[7],  arr[11], arr[15], flag2);
	}
	else if (flag == 4)
	{
		Line (arr[12], arr[8],  arr[4], arr[0], flag2);
	    Line (arr[13], arr[9],  arr[5], arr[1], flag2);
	    Line (arr[14], arr[10], arr[6], arr[2], flag2);
		Line (arr[15], arr[11], arr[7], arr[3], flag2);
	}
}
//========================================================================================================================================================================
void Image (HWND hWnd, int *arr)
{
	HINSTANCE hInst = GetModuleHandle(0);
	HBITMAP hB;

	int ID = ID_B1;
	for (int i = 0; i < 16; i++)
	{
		switch(arr[i])
		{
			default:
				 hB =    LoadBitmap (hInst, MAKEINTRESOURCE (arr[i]));
				SendMessage (GetDlgItem (hWnd, ID + i), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hB);
				break;
		}
	}
}
//========================================================================================================================================================================
void Random (HWND hWnd, int *arr, bool &flag)
{
	HINSTANCE hInst = GetModuleHandle(0);
	if (flag)
	{
		vector <int> vect;
		int temp = ID_B1;
		for (int i = 0; i < 16; i++)
		{
			if (arr[i] == 0)
				vect.push_back(temp + i);
		}
	
		temp = ID_B1;
		int random = rand()%vect.size();
		int count = vect[random];

		for (int i = 0; i < 16; i++)
		{
			if (count == temp + i)
				arr[i] = 2;
		}
	}
	else
	{
		if (arr[0] != 0 && arr[1] != 0 && arr[2] != 0 && arr[3] != 0 &&
			arr[4] != 0 && arr[5] != 0 && arr[6] != 0 && arr[7] != 0 &&
			arr[8] != 0 && arr[9] != 0 && arr[10] != 0 && arr[11] != 0 &&
			arr[12] != 0 && arr[13] != 0 && arr[14] != 0 && arr[15] != 0)
		{
			SetDlgItemText(hWnd, ID_GAME_OVER, L"GAME OVER");
		}
	}
	flag = 0;
}
//========================================================================================================================================================================
void Button (HWND hWnd, int length)
{
	HINSTANCE hInst = GetModuleHandle(0);
	int ID = ID_B1;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{

			CreateWindowEx(WS_EX_CLIENTEDGE, L"Static", L"", WS_CHILD|WS_VISIBLE|SS_BITMAP, 15 +(j*WIDTH),  100 + (i*HEIGHT),  WIDTH, HEIGHT, hWnd, (HMENU)ID++,	hInst, NULL);
			
		}
	}
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Static", L"Score = 0", WS_CHILD|WS_VISIBLE|SS_CENTER|WS_EX_CLIENTEDGE, 15,  15,  WIDTH * 2, HEIGHT - 20, hWnd, (HMENU)ID_SCORE,	hInst, NULL);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Static", L"", WS_CHILD|WS_VISIBLE|SS_CENTER|WS_EX_CLIENTEDGE,  215,  15,  WIDTH * 2, HEIGHT - 20, hWnd, (HMENU)ID_GAME_OVER,	hInst, NULL);
	
}
//========================================================================================================================================================================
void Destroi_Button (HWND hWnd, int *arr)
{
	DestroyWindow (GetDlgItem (hWnd, ID_B1));
	DestroyWindow (GetDlgItem (hWnd, ID_B2));
	DestroyWindow (GetDlgItem (hWnd, ID_B3));
	DestroyWindow (GetDlgItem (hWnd, ID_B4));
	DestroyWindow (GetDlgItem (hWnd, ID_B5));
	DestroyWindow (GetDlgItem (hWnd, ID_B6));
	DestroyWindow (GetDlgItem (hWnd, ID_B7));
	DestroyWindow (GetDlgItem (hWnd, ID_B8));
	DestroyWindow (GetDlgItem (hWnd, ID_B10));
	DestroyWindow (GetDlgItem (hWnd, ID_B11));
	DestroyWindow (GetDlgItem (hWnd, ID_B12));
	DestroyWindow (GetDlgItem (hWnd, ID_B13));
	DestroyWindow (GetDlgItem (hWnd, ID_B14));
	DestroyWindow (GetDlgItem (hWnd, ID_B15));
	DestroyWindow (GetDlgItem (hWnd, ID_B16));
	SetDlgItemText(hWnd, ID_GAME_OVER, L"");
	for (int i = 0; i < 16; i++)
	{
		arr[i] = 0;
	}
	Score = 0;
}
void Scores (HWND hWnd)
{
	WCHAR * buff = new WCHAR [2];
	WCHAR buff2 [10];
	wsprintf (buff2, L"%i", Score);
	wcscpy (buff, L"Score = ");
	wcscat (buff, buff2);
	SetDlgItemText(hWnd, ID_SCORE, buff);
	
}