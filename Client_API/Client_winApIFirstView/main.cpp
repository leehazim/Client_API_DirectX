#include <windows.h>

struct tag_Finish {
	HWND hWnd;
	bool isClear;
};

HINSTANCE g_hInst;
ATOM RegiClass(HINSTANCE);
tag_Finish InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// APIENTRY가 2개 정의 되어있는거 같다.
// wWinMain이 있고 WinMain이 있다.
// 3번째 매개변수가 LPWSTR이냐  LPSTR이냐가 다르다.
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdParam, int nCmdShow) {
   
    RegiClass(hInstance);
    g_hInst = hInstance;
    tag_Finish tmp = InitInstance(hInstance, nCmdShow);

    if (!tmp.isClear)
    {
        return FALSE;
    }

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

ATOM RegiClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"First Window";
    wcex.hIconSm = nullptr;

    return RegisterClassExW(&wcex);
}

tag_Finish InitInstance(HINSTANCE hInstance, int nCmdShow) {
    HWND hWnd;
    hWnd = CreateWindowW(L"First Window", L"First Window", WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    
    tag_Finish tmp;
    if (hWnd == nullptr) {
        tmp.hWnd = hWnd;
        tmp.isClear = false;
        return tmp;
    }
    tmp.hWnd = hWnd;
    tmp.isClear = true;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return tmp;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
    switch (iMessage) {

    case WM_PAINT:
    {
        HDC hdc; PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, iMessage, wParam, lParam);
}