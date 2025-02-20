#include <windows.h>
#include <stdio.h>
HWND num1 ,num2;



/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	char t1[20], t2[20];
	HWND textfield, plusButton, minusB, mulB, divideB;
	switch(Message) {
		
		case WM_CREATE:
		textfield = CreateWindow("STATIC","Please input two numbers",WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 20 ,25 ,200,25, hwnd,NULL ,NULL ,NULL);
		plusButton = CreateWindow("BUTTON","+",WS_VISIBLE | WS_CHILD | WS_BORDER ,45,120,30,30,hwnd,(HMENU) 1,NULL,NULL);
		minusB = CreateWindow("BUTTON","-",WS_VISIBLE | WS_CHILD | WS_BORDER ,85,120,30,30,hwnd,(HMENU) 2,NULL,NULL);
		mulB = CreateWindow("BUTTON","*",WS_VISIBLE | WS_CHILD | WS_BORDER,125,120,30,30,hwnd,(HMENU) 3,NULL,NULL);
		divideB = CreateWindow("BUTTON","/",WS_VISIBLE | WS_CHILD | WS_BORDER ,165,120,30,30,hwnd,(HMENU) 4,NULL,NULL);

		num1 = CreateWindow("EDIT","",WS_BORDER | WS_CHILD | WS_VISIBLE,20 , 55, 200 ,25,hwnd,NULL,NULL,NULL);
		num2 = CreateWindow("EDIT","",WS_BORDER | WS_CHILD | WS_VISIBLE,20 , 85, 200 ,25,hwnd,NULL,NULL,NULL);

		
			break;
		/* Upon destruction, tell the main thread to stop */
		case WM_COMMAND:
		if (LOWORD(wParam) >= 1 && LOWORD(wParam) <= 4) {  
			GetWindowText(num1, t1, 20);
			GetWindowText(num2, t2, 20);

			double val1 = atof(t1);
			double val2 = atof(t2);
			double result = 0;
			char resultText[50];

			switch (LOWORD(wParam)) {
				case 1: result = val1 + val2; break;
				case 2: result = val1 - val2; break;
				case 3: result = val1 * val2; break;
				case 4: result = val1 / val2; break;
			}

			sprintf(resultText, "%f", result);
			MessageBox(hwnd, resultText, "Result", MB_OK);
		}
		break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(50, 102, 193));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
