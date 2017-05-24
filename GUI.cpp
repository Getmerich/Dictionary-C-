

#include <windows.h>
#include "Diction.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK ListBoxExampleProc(HWND, UINT, WPARAM, LPARAM);
Dictionary list;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
LPSTR lpCmdLine, int nCmdShow)
{
	MSG  msg;
	WNDCLASS wc = { 0 };
	wc.lpszClassName = TEXT("Buttons");
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);


	RegisterClass(&wc);
	CreateWindow(wc.lpszClassName, TEXT("Dictionary"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		150, 150, 750, 400, 0, 0, hInstance, 0);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

//BUTTONS!
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	

	switch (msg)
	{
	case WM_CREATE:
	{
		CreateWindow(TEXT("edit"), TEXT("Type a word"),
			WS_VISIBLE | WS_CHILD,
			155, 302, 150, 20,
			hwnd, (HMENU)1, NULL, NULL);

		CreateWindow(TEXT("list box"), TEXT("Add New"),
			WS_VISIBLE | WS_CHILD,
			20, 50, 200, 30,
			hwnd, (HMENU)1, NULL, NULL);

		CreateWindow(TEXT("button"), TEXT("Add New"),
			WS_VISIBLE | WS_CHILD,
			50, 300, 80, 25,
			hwnd, (HMENU)1, NULL, NULL);

		CreateWindow(TEXT("button"), TEXT("Save"),
			WS_VISIBLE | WS_CHILD,
			250, 150, 80, 25,
			hwnd, (HMENU)2, NULL, NULL);

		CreateWindow(TEXT("button"), TEXT("Load"),
			WS_VISIBLE | WS_CHILD,
			250, 200, 80, 25,
			hwnd, (HMENU)3, NULL, NULL);

		CreateWindow(TEXT("button"), TEXT("Quit"),
			WS_VISIBLE | WS_CHILD,
			600, 300, 80, 25,
			hwnd, (HMENU)4, NULL, NULL);
		break;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == 1) {
			
			//bring up space to type/input words
		}

		if (LOWORD(wParam) == 2) {
			list.saveTxt("List.txt");
		}

		if (LOWORD(wParam) == 1) {
			list.loadTxt("List.txt");
		}

		if (LOWORD(wParam) == 4) {
			PostQuitMessage(0);
		}

		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//LIST???
INT_PTR CALLBACK ListBoxExampleProc(HWND hDlg, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		// Add items to list. 
		HWND hwndList = GetDlgItem(hDlg, IDC_LISTBOX_EXAMPLE);
		for (int i = 0; i < list.list.size(); i++)
		{
			int pos = (int)SendMessage(hwndList, LB_ADDSTRING, 0,
				(LPARAM) list.getWord(i));
			// Set the array index of the player as item data.
			// This enables us to retrieve the item from the array
			// even after the items are sorted by the list box.
			SendMessage(hwndList, LB_SETITEMDATA, pos, (LPARAM)i);
		}
		// Set input focus to the list box.
		SetFocus(hwndList);
		return TRUE;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;

		case IDC_LISTBOX_EXAMPLE:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
			{
				HWND hwndList = GetDlgItem(hDlg, IDC_LISTBOX_EXAMPLE);

				// Get selected index.
				int lbItem = (int)SendMessage(hwndList, LB_GETCURSEL, 0, 0);

				// Get item data.
				int i = (int)SendMessage(hwndList, LB_GETITEMDATA, lbItem, 0);

				// Do something with the data from Roster[i]
				TCHAR buff[MAX_PATH];
				StringCbPrintf(buff, ARRAYSIZE(buff),
					TEXT("Position: %s\nGames played: %d\nGoals: %d"),
					Roster[i].achPosition, Roster[i].nGamesPlayed,
					Roster[i].nGoalsScored);

				SetDlgItemText(hDlg, IDC_STATISTICS, buff);
				return TRUE;
			}
			}
		}
		return TRUE;
		}
	}
	return FALSE;
}


/*#include <windows.h>

// This is where all the input to the window goes to 
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {

		// trap the WM_CLOSE (clicking X) message, and actually tell the window to close 
	case WM_CLOSE: {
		DestroyWindow(hwnd);
		break;
	}

				   // Upon destruction, tell the main thread to stop 
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}

					 // All other messages (a lot of them) are processed using default procedures 
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

// The 'main' function of Win32 GUI programs: this is where execution starts 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; // A properties struct of our window 
	HWND hwnd; // A 'HANDLE', hence the H, or a pointer to our window 
	MSG Msg; // A temporary location for all messages 

			 // zero out the struct and set the stuff we want to modify 
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc; // This is where we will send messages to 
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	// White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Load a standard icon 
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "Taylor's Dictionary", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // x 
		CW_USEDEFAULT, // y 
		640, // width 
		480, // height 
		NULL, NULL, hInstance, NULL);


	HWND hwndButton = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"OK",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10,         // x position 
		10,         // y position 
		100,        // Button width
		100,        // Button height
		m_hwnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.


	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	
	//This is the heart of our program where all input is processed and
	//sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
	//this loop will not produre unreasonably CPU usage
	
	while (GetMessage(&Msg, NULL, 0, 0) > 0) { // If no error is received... 
		TranslateMessage(&Msg); // Translate keycodes to chars if present 
		DispatchMessage(&Msg); // Send it to WndProc 
	}
	return Msg.wParam;
}

*/
