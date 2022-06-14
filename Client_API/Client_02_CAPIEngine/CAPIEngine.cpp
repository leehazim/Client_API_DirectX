#include "CAPIEngine.h"

HINSTANCE CAPIEngine::hInst = nullptr;

CAPIEngine::CAPIEngine() {
    memset(szWindowClass, 0, MAX_LOADSTRING * sizeof(WCHAR));
    memset(szTitle, 0, MAX_LOADSTRING * sizeof(WCHAR));
}

CAPIEngine::~CAPIEngine() {

}

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

    OnCreate();
    /*while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/
    
    // 루프 수정
    while (msg.message != WM_QUIT) {
        // PeekMessage 메시지 있으면 true 없으면 false
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            OnUpdate();
        }
    }

    OnDestroy();

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
    /*WCHAR szTemp[256] = L"";
    wsprintf(szTemp, L"CAPIEngine::OnUpdate\n");
    OutputDebugString(szTemp);*/
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

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    
    if (!hWnd) {
        return FALSE;
    }
    // 화면 크기 재설정
    RECT rt= {0, 0, 800, 600};
    
    // 입력한 렉트 구조체에 있는 크기만큼의 클라이언트 렉트로 설정되도록 캡션과 메뉴의 크기를 추가한 렉트값으로 전달한 입출력(lpRect)에 저장
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, TRUE);
    SetWindowPos(hWnd, HWND_TOPMOST, 100, 100,
                 rt.right - rt.left, rt.bottom - rt.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

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
        //TODO : 
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
