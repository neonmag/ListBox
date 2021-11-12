#define _CRT_SECURE_NO_WARNINGS
#include "UsingListboxDlg.h"
#include <ctime>

TCHAR buf[20], result[20], multiplyS[20], average[20];

UsingListboxDlg* UsingListboxDlg::ptr = NULL;

bool pressed = false;

int prevCount;

UsingListboxDlg::UsingListboxDlg(void)
{
	ptr = this;
}

void UsingListboxDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL UsingListboxDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit = GetDlgItem(hwnd, IDC_EDIT1);
	hButton = GetDlgItem(hwnd, IDC_BUTTON1);
	hList = GetDlgItem(hwnd, IDC_LIST1);
	for (int i = 0; i < 3; i++)
	{
		hRadio[i] = GetDlgItem(hwnd, IDC_RADIO1 + i);
		EnableWindow(hRadio[i], SW_HIDE);
	}
	return TRUE;
}

void UsingListboxDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	srand(time(0));
	int countOfNums = rand() % 10 + 10;
	int* arr = new int[countOfNums];
	double sum = 0.;
	double multiply = 1;
	switch (id)
	{
	case IDC_RADIO1:
		SetWindowText(hEdit, result);
		break;
	case IDC_RADIO2:
		SetWindowText(hEdit, multiplyS);
		break;
	case IDC_RADIO3:
		SetWindowText(hEdit, average);
		break;
	case IDC_BUTTON1:
		if (pressed == true)
		{
			for (int i = 0; i < prevCount; i++)
			{
				SendMessage(hList, LB_DELETESTRING, 0, 0);
			}
		}
		pressed = true;
		for (int i = 0; i < 3; i++)
		{
			EnableWindow(hRadio[i], SW_SHOW);
		}
		for (int i = 0; i < countOfNums; i++)
		{
			arr[i] = rand() % 20 - 10;
			while (arr[i] == 0)
			{
				arr[i] = rand() % 20 - 10;
			}
			sum += arr[i];
			multiply *= arr[i];
			_itow(arr[i], buf, 10);
			SendMessage(hList, LB_ADDSTRING, 0, LPARAM(buf));
		}
		prevCount = countOfNums;
		_itow(sum, result, 10);
		_itow(multiply, multiplyS, 10);
		_itow(sum / countOfNums, average, 10);
		break;
	}
	delete[]arr;
	arr = nullptr;
}

BOOL CALLBACK UsingListboxDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}