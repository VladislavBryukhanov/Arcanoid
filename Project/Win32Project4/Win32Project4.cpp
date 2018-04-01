#include <stdio.h>
#include <conio.h>
#include"stdafx.h"
#include "resource.h"
#include<ctime>
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HWND hStatic1,hButton,hDialog,hAbout,hPicture;
int  dx, dy;
HINSTANCE hInst;
int ball_top,ball_right,board_right;
int switc,difficult,level,points,off=0;
TCHAR* str;
TCHAR* str2;
HMENU hMenu;
HBITMAP hBit[4];
HWND hImage;
RECT rect;
int record;
HANDLE hFile;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{

	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc); 
}


int ReadCounter() {
	DWORD  dwTemp;
	int dwCounter;
	HANDLE hFile = CreateFile(L"./rec.txt", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, &dwCounter, sizeof(dwCounter), &dwTemp, NULL);
	CloseHandle(hFile);
	return dwCounter;
}
VOID WriteCounter(int dwCounter) {
	DWORD dwTemp;
	HANDLE hFile = CreateFile(TEXT("./rec.txt"), GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, &dwCounter, sizeof(dwCounter), &dwTemp, NULL);
	CloseHandle(hFile);
}


void enable_menu(int record)
{
	if((record>=80)&&(off!=1))
	{	
		EnableMenuItem(hMenu, ID_lvl2, MF_BYCOMMAND | MF_ENABLED );
		EnableMenuItem(hMenu, ID_mid, MF_BYCOMMAND | MF_ENABLED );
		if(record>=220)
		{
			EnableMenuItem(hMenu, ID_lvl3, MF_BYCOMMAND | MF_ENABLED );
			EnableMenuItem(hMenu, ID_hard, MF_BYCOMMAND | MF_ENABLED );
			off=1;
		}
	}
}

BOOL CALLBACK PifProc(HWND hdlg, UINT messg, WPARAM wParam, LPARAM lParam)
{
	switch (messg)
	{
	case WM_INITDIALOG:
		
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
			{
			case IDC_BUTTON1:
				EndDialog(hdlg, 0); 
				break;
			}
		break;
	case WM_CLOSE:
		EndDialog(hdlg, 0); 
		break;
		
			
		default: return false;
		}
	} 


	BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch(message)
		{
		case WM_CLOSE:
			EndDialog(hWnd, 0); 
			return TRUE;
		case WM_INITDIALOG:
			for(int i = 0; i < 5; i++)
				hBit[i] = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1 + i));

			hPicture = GetDlgItem(hWnd, IDC_PICTURE);
			SendMessage(hPicture, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBit[1]));




			 CloseHandle(hFile);
			hDialog=hWnd;
			hStatic1 = GetDlgItem(hWnd, IDC_STATIC1);
			SendMessage(hStatic1, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBit[0]));

			hButton = GetDlgItem(hWnd, IDC_BUTTON1);
			srand(time(NULL));
			dx = 4;
			dy = 4;
			ball_top=40;
			ball_right=100;
			switc=1;
			GetWindowRect(hWnd, &rect);
			hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
			SetMenu(hDialog, hMenu);
			difficult=3;
			level=100;
			points=0;
			record=0;
			str=new TCHAR[100];
			str2=new TCHAR[100];
			points=0;
			CheckMenuItem(hMenu, ID_hard, MF_BYCOMMAND | MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_mid, MF_BYCOMMAND | MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_lvl3, MF_BYCOMMAND | MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_lvl2, MF_BYCOMMAND | MF_UNCHECKED);

			EnableMenuItem(hMenu, ID_hard, MF_BYCOMMAND | MF_GRAYED );
			EnableMenuItem(hMenu, ID_mid, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, ID_lvl3, MF_BYCOMMAND | MF_GRAYED );
			EnableMenuItem(hMenu, ID_lvl2, MF_BYCOMMAND | MF_GRAYED);

			if(ReadCounter()!=0)
			{
				record=ReadCounter();
				enable_menu(record);
			}
			
			return TRUE;
		

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case ID_es:
				difficult=3;
				CheckMenuItem(hMenu, ID_hard, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu, ID_mid, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu,ID_es, MF_BYCOMMAND | MF_CHECKED);
				return TRUE;
			case ID_mid:
				difficult=5;
				CheckMenuItem(hMenu, ID_hard, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu, ID_es, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu,ID_mid, MF_BYCOMMAND | MF_CHECKED);
				return TRUE;
			case ID_hard:
				difficult=7;
				CheckMenuItem(hMenu, ID_mid, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu, ID_es, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu,ID_hard, MF_BYCOMMAND | MF_CHECKED);
				return TRUE;
			case ID_lvl1:
				SendMessage(hStatic1, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBit[0]));
				SendMessage(hPicture, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBit[1]));
				level=100;
				CheckMenuItem(hMenu, ID_lvl3, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu, ID_lvl2, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu,ID_lvl1, MF_BYCOMMAND | MF_CHECKED);
				return TRUE;
			case ID_lvl2:
				SendMessage(hStatic1, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBit[4]));
				SendMessage(hPicture, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBit[2]));
				level=66;
				CheckMenuItem(hMenu, ID_lvl1, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu, ID_lvl3, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu,ID_lvl2, MF_BYCOMMAND | MF_CHECKED);
				return TRUE;
			case ID_lvl3:
				SendMessage(hStatic1, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBit[4]));
				SendMessage(hPicture, STM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBit[3]));
				level=33;
				CheckMenuItem(hMenu, ID_lvl1, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu, ID_lvl2, MF_BYCOMMAND | MF_UNCHECKED);
				CheckMenuItem(hMenu,ID_lvl3, MF_BYCOMMAND | MF_CHECKED);
				return TRUE;

			case ID_about:

				DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)PifProc);
				return TRUE;

			case ID_rec:
				wsprintf(str2, TEXT("Reocord: %d"),ReadCounter());
				MessageBox(hWnd,str2,L"Records",MB_OK | MB_ICONASTERISK);
				return TRUE;

			case ID_exit:
				EndDialog(hWnd, 0); 
				return TRUE;

			case ID_del:
				DeleteFile(L"./rec.txt");
				WriteCounter(0);	
				record=0;
				points=0;
				return TRUE;

			}

		case WM_RBUTTONDOWN:
			switc*=-1;
			KillTimer(hWnd,1);
			if(switc!=1)
				SetWindowText(hWnd, L"                                                         GAME PAUSED");
			return TRUE;



		case WM_TIMER:
			wsprintf(str, TEXT("                                                         Your Points:%d"),points);
			SetWindowText(hWnd, str);
			InvalidateRect(hStatic1, NULL, TRUE);
			UpdateWindow(hStatic1);
			InvalidateRect(hButton, NULL, TRUE);
			UpdateWindow(hButton);

			ball_right=ball_right + dx;
			ball_top = ball_top + dy;
			MoveWindow(hStatic1,	ball_right,ball_top,30,30,true);
			if (ball_top >= rect.bottom-60)
			{
				ball_top=30;
				switc*=-1;
				KillTimer(hWnd,1);
				if(switc!=1)
					SetWindowText(hWnd, L"                                                         GAME PAUSED");
				wsprintf(str, TEXT("You collected %d points"),points);
				MessageBox(hWnd,str, L"Game Over",MB_OK | MB_ICONASTERISK);
				if((record=ReadCounter())<points)
				{record=points;
				WriteCounter(record);	}
				enable_menu(record);
				points=0;
			}

			if (ball_top  <= 0 )

				dy *=-1;
			if (ball_right >= rect.right-30)
				dx *=-1;

			if (ball_right  <= 0)

				dx *=-1;
			if((ball_right  <=20)&&(ball_right>=board_right-20))
			{
				dx *=-1;
			}
			if ((ball_top >=rect.bottom-101)&&(ball_right>=board_right-20)&&(ball_right<=board_right+level/2))
			{
				dy = (rand()%difficult+difficult) * -1;
				dx = (rand()%difficult+difficult)*-1;
				points+=(((difficult-1)/2)*1000)/level;
			}
			if ((ball_top >=rect.bottom-101)&&(ball_right>=board_right+level/2)&&(ball_right<=board_right+level))
			{
				dy = (rand()%difficult+difficult) * -1;
				dx = (rand()%difficult+difficult)*+1;
				points+=(((difficult-1)/2)*1000)/level;
			}
			return TRUE;


		case WM_MOUSEMOVE:		
			if(switc==1)
			{
				SetTimer(hWnd, 1, 1, NULL);
				if(LOWORD(lParam)+level<=rect.right)
					board_right=LOWORD(lParam);
				MoveWindow(hButton,LOWORD(lParam),rect.bottom-70,level,10,true);
			}
			return TRUE;		
		}
		return FALSE;
	}
