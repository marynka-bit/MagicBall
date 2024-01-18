#include <Windows.h>
#include <ctime>
#include <stdexcept>
#include "resource.h"
#include <Commctrl.h>
//�������� ��������� ����� ��� ��������� ����������
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 
// ������������� ����������
HINSTANCE hInstance;
UINT uMsg;
HWND ball, field;
HBITMAP hbit;
// ���������� ���������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    srand(time(NULL));
    HFONT myFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    std::wstring result = L"";
    wchar_t value[256];
    bool qmarks = false;
    switch (message) {
    // �������� ��������� ����������
    case WM_CREATE:
        ball = CreateWindow(L"BUTTON", NULL, WS_CHILD | WS_VISIBLE | BS_BITMAP,
            50, 30, 180, 180, hWnd, reinterpret_cast<HMENU>(1), hInstance, nullptr);
        field = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            50, 230, 180, 21, hWnd, nullptr, hInstance, nullptr);
        hbit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));//L"Bit");
        SendMessage(ball, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbit);
        SendMessage(field, WM_SETFONT, WPARAM(myFont), TRUE);
        SendMessage(field, EM_SETCUEBANNER, FALSE, (LPARAM)L"����� ������");
        break;
    // ��������� ���������
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) { 
            GetWindowText(field, value, sizeof(value) / sizeof(value[0]));
            if (!wcscmp(value, L"")) {
                MessageBox(nullptr, L"������� ������������!", L"����� ����", MB_ICONERROR | MB_OK);
                    break;
            }
            for (int i = 0; i < sizeof(value) / sizeof(value[0]); i++) {
                if (value[i] == L'?') {
                    switch (rand() % (24 + 1)) {
                    case 0: MessageBox(nullptr, L"����� ���", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 1: MessageBox(nullptr, L"���� ������� ���", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 2: MessageBox(nullptr, L"�������� �����", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 3: MessageBox(nullptr, L"����� ��������", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 4: MessageBox(nullptr, L"���� ������", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 5: MessageBox(nullptr, L"���� ��������", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 6: MessageBox(nullptr, L"����� ��", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 7: MessageBox(nullptr, L"���� ������� ��", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 8: MessageBox(nullptr, L"���", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 9: MessageBox(nullptr, L"��� ��������", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 10: MessageBox(nullptr, L"����� ���", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 11: MessageBox(nullptr, L"����� �������", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 12: MessageBox(nullptr, L"����� ��", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 13: MessageBox(nullptr, L"��", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 14: MessageBox(nullptr, L"���������", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 15: MessageBox(nullptr, L"�������� �����", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 16: MessageBox(nullptr, L"�� ���� ��������", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 17: MessageBox(nullptr, L"������", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 18: MessageBox(nullptr, L"��������", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    case 19: MessageBox(nullptr, L"�� ������", L"����� ����", MB_ICONINFORMATION | MB_OK); break;
                    }
                    qmarks = true;
                    break;
                }
            }
            if (qmarks == false) MessageBox(nullptr, L"������� ������, � �� �����������!", L"����� ����", MB_ICONERROR | MB_OK);
            else qmarks = false;
            if (wcscmp(value, L"")) SetWindowText(field, result.c_str());
        }
        break;
    // ���������� ����������
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
// ������� ������� ������������ ����������
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInst);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // ����������� ������ ���� � ������� ��� �������
    hInstance = hInst;
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"MagicBallClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
    // ��� ������ ����������� ����
    if (!RegisterClassEx(&wcex)) {
        MessageBox(nullptr, L"������ ����������� ����!", L"������!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    // �������� �������� ����
    HWND hWnd = CreateWindowEx(0, L"MagicBallClass", L"��� ������", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, hInstance, nullptr);
    if (!hWnd) {
        MessageBox(nullptr, L"�� ������� ������� ����!", L"������!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    RECT rc;
    GetWindowRect(hWnd, &rc);
    int xPos = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
    int yPos = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;
    SetWindowPos(hWnd, 0, xPos, yPos, 0, 0, SWP_NOSIZE);
    // ����������� ����
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    // ���� ��������� ���������
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}



