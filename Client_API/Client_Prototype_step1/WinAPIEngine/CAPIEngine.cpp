#include "resource.h"
#include "CAPIEngine.h"
#include "CTexture.h"
#include "CInputMgr.h"

HINSTANCE CAPIEngine::hInst = nullptr;

CAPIEngine::CAPIEngine() :m_ClientWidth(800.0f), m_ClientHeight(600.0f) {
    memset(szWindowClass, 0, MAX_LOADSTRING * sizeof(WCHAR));
    memset(szTitle, 0, MAX_LOADSTRING * sizeof(WCHAR));
}

CAPIEngine::~CAPIEngine() {}

BOOL CAPIEngine::Create(HINSTANCE hInstance, int nCmdShow) {
    /*LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENTVIEWCODEINIT, szWindowClass, MAX_LOADSTRING);*/
    wsprintf(szTitle, L"WinAPIEngine");
    wsprintf(szWindowClass, L"WinAPIEngine");
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }
    return TRUE;
}

MSG CAPIEngine::Run() {
    HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_CLIENTVIEWCODEINIT));
    MSG msg = { 0 };
    RECT crt = { 0, 0, m_ClientWidth, m_ClientHeight };

    m_hDC = GetDC(m_hWnd);
    m_pBackBuffer = new  CTexture();
    m_pBackBuffer->CreateBackBuffer(crt, hInst, m_hDC);

    CInputMgr::GetInstance();

    OnCreate();
    QueryPerformanceFrequency(&m_Second);
    QueryPerformanceCounter(&m_Time);

    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            LARGE_INTEGER tTime;
            QueryPerformanceCounter(&tTime);
            m_DeltaTime = static_cast<float>(tTime.QuadPart - m_Time.QuadPart) /
                          static_cast<float>(m_Second.QuadPart);
            m_Time = tTime;
            OnUpdate(m_DeltaTime);
        }
    }
    OnDestroy();

    CInputMgr::GetInstance()->ReleaseInstance();

    if (m_pBackBuffer != nullptr) {
        delete m_pBackBuffer;
        m_pBackBuffer = nullptr;
    }
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

void CAPIEngine::OnUpdate(float deltaTime) {
   
}

float CAPIEngine::GetClientWidth() const {
    return m_ClientWidth;
}

float CAPIEngine::GetClientHeight() const {
    return m_ClientHeight;
}

ATOM CAPIEngine::MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, nullptr);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = nullptr;

    return RegisterClassExW(&wcex);
}

BOOL CAPIEngine::InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;

    m_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!m_hWnd) {
        return FALSE;
    }

    RECT rt = { 0,0, m_ClientWidth, m_ClientHeight};
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rt.right - rt.left, rt.bottom - rt.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);

    return TRUE;
}

LRESULT CAPIEngine::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
    switch (iMessage)
    {
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

void CAPIEngine::DrawCircle(float X, float Y, float Radius) {
    Ellipse(m_pBackBuffer->m_hMemDC, X - Radius, Y - Radius,
            X + Radius, Y + Radius);
}

void CAPIEngine::DrawTexture(float X, float Y, CTexture* Texture) {
    // 백버퍼에 비트맵을 그리기
    BitBlt(m_pBackBuffer->m_hMemDC,
           X, Y,
           Texture->m_Info.bmWidth, Texture->m_Info.bmHeight,
           Texture->m_hMemDC, 0, 0, SRCCOPY);
}

void CAPIEngine::Clear(float R, float G, float B) {
    
    HPEN hPen, OldPen;
    HBRUSH hBrush, OldBrush;

    HDC tmpDC = this->m_pBackBuffer->m_hMemDC;

    hBrush = CreateSolidBrush(RGB(R * 255, G * 255, B * 255));
    hPen = CreatePen(PS_SOLID, 2, RGB(R * 255, G * 255, B * 255));

    OldPen = (HPEN)SelectObject(tmpDC, hPen);
    OldBrush = (HBRUSH)SelectObject(tmpDC, hBrush);
    Rectangle(m_pBackBuffer->m_hMemDC, 0, 0, m_ClientWidth, m_ClientHeight);

    DeleteObject(SelectObject(tmpDC, OldBrush));
    DeleteObject(SelectObject(tmpDC, OldPen));
}

void CAPIEngine::Present() {
    // 버퍼 갱신
    BitBlt(this->m_hDC,
           0, 0,
           m_ClientWidth, m_ClientHeight,
           m_pBackBuffer->m_hMemDC,
           0, 0, SRCCOPY);
}

void CAPIEngine::DeletePrefab(CUnit*& prefab) {
    if (prefab != nullptr) {
        prefab->Destroy();

        delete prefab;
        prefab = nullptr;
    }
}