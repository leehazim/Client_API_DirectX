#include "CAPIEngine.h"

HINSTANCE CAPIEngine::hInst = nullptr;

CAPIEngine::CAPIEngine() {
    memset(szWindowClass, 0, MAX_LOADSTRING * sizeof(WCHAR));
    memset(szTitle, 0, MAX_LOADSTRING * sizeof(WCHAR));
}

CAPIEngine::~CAPIEngine() {}

BOOL CAPIEngine::Create(HINSTANCE hInstance, int nCmdShow) {
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENTVIEWCODEINIT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }
    return TRUE;
}

MSG CAPIEngine::Run() {
    HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_CLIENTVIEWCODEINIT));
    MSG msg = { 0 };

    m_hDC = GetDC(m_hWnd);
    OnCreate();

    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            OnUpdate();
        }
    }

    OnDestroy();
    ReleaseDC(m_hWnd, m_hDC);

    return msg;
}

void CAPIEngine::OnCreate() {
    WCHAR szTemp[256] = L"";
    wsprintf(szTemp, L"CAPIEngine::OnCreate\n");
    OutputDebugString(szTemp);
}

void CAPIEngine::OnDestroy() {
    WCHAR szTemp[256] = L"";
    wsprintf(szTemp, L"CAPIEngine::OnDestroy\n");
    OutputDebugString(szTemp);
}

void CAPIEngine::OnUpdate() {
   /* TextOut(m_hDC, 0, 0, L"Test Text", lstrlen(L"Test Text"));
    TextOut(m_hDC, 0, 25, L"Hi Window", lstrlen(L"Hi Window"));
    TextOut(m_hDC, 0, 50, L"안녕하세요", lstrlen(L"안녕하세요"));

    LPCWSTR tString = L"WCHAR string";
    TextOut(m_hDC, 0, 75, tString, lstrlen(tString));

    Rectangle(m_hDC, 100, 100, 200, 200);

    MoveToEx(m_hDC, 100, 100, NULL);
    LineTo(m_hDC, 200, 200);

    Ellipse(m_hDC, 210, 100, 310, 200);*/
}

ATOM CAPIEngine::MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENTVIEWCODEINIT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CLIENTVIEWCODEINIT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL CAPIEngine::InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;

    m_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!m_hWnd) {
        return FALSE;
    }

    RECT rt = { 0,0, 800, 600 };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, TRUE);
    SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rt.right - rt.left, rt.bottom - rt.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);

    return TRUE;
}

LRESULT CAPIEngine::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
    switch (iMessage)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
        {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, DlgProc);
            break;
        }
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, iMessage, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, iMessage, wParam, lParam);
    }
    return 0;
}

INT_PTR CAPIEngine::DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (iMessage)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


void CAPIEngine::DrawCircle(float tX, float tY, float tRadius) {
    Ellipse(m_hDC, tX - tRadius, tY - tRadius,
            tX + tRadius, tY + tRadius);
}