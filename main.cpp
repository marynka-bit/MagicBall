#include <Windows.h>
#include <ctime>
#include <stdexcept>
#include "resource.h"
#include <Commctrl.h>
//включаем системные стили для элементов управления
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 
// инициализация переменных
HINSTANCE hInstance;
UINT uMsg;
HWND ball, field;
HBITMAP hbit;
// обработчик сообщений
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    srand(time(NULL));
    HFONT myFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    std::wstring result = L"";
    wchar_t value[256];
    bool qmarks = false;
    switch (message) {
    // создание элементов управления
    case WM_CREATE:
        ball = CreateWindow(L"BUTTON", NULL, WS_CHILD | WS_VISIBLE | BS_BITMAP,
            50, 30, 180, 180, hWnd, reinterpret_cast<HMENU>(1), hInstance, nullptr);
        field = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            50, 230, 180, 21, hWnd, nullptr, hInstance, nullptr);
        hbit = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));//L"Bit");
        SendMessage(ball, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hbit);
        SendMessage(field, WM_SETFONT, WPARAM(myFont), TRUE);
        SendMessage(field, EM_SETCUEBANNER, FALSE, (LPARAM)L"Задай вопрос");
        break;
    // обработка сообщения
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) { 
            GetWindowText(field, value, sizeof(value) / sizeof(value[0]));
            if (!wcscmp(value, L"")) {
                MessageBox(nullptr, L"Введите предсказание!", L"Ответ шара", MB_ICONERROR | MB_OK);
                    break;
            }
            for (int i = 0; i < sizeof(value) / sizeof(value[0]); i++) {
                if (value[i] == L'?') {
                    switch (rand() % (24 + 1)) {
                    case 0: MessageBox(nullptr, L"Думаю нет", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 1: MessageBox(nullptr, L"Духи говорят нет", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 2: MessageBox(nullptr, L"Спросите позже", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 3: MessageBox(nullptr, L"Очень вероятно", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 4: MessageBox(nullptr, L"Мало шансов", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 5: MessageBox(nullptr, L"Есть сомнения", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 6: MessageBox(nullptr, L"Точно да", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 7: MessageBox(nullptr, L"Духи говорят да", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 8: MessageBox(nullptr, L"Нет", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 9: MessageBox(nullptr, L"Без сомнений", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 10: MessageBox(nullptr, L"Точно нет", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 11: MessageBox(nullptr, L"Шансы хорошие", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 12: MessageBox(nullptr, L"Думаю да", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 13: MessageBox(nullptr, L"Да", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 14: MessageBox(nullptr, L"Непонятно", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 15: MessageBox(nullptr, L"Спросите снова", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 16: MessageBox(nullptr, L"Не могу показать", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 17: MessageBox(nullptr, L"Неясно", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 18: MessageBox(nullptr, L"Возможно", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    case 19: MessageBox(nullptr, L"Не сейчас", L"Ответ шара", MB_ICONINFORMATION | MB_OK); break;
                    }
                    qmarks = true;
                    break;
                }
            }
            if (qmarks == false) MessageBox(nullptr, L"Введите вопрос, а не предложение!", L"Ответ шара", MB_ICONERROR | MB_OK);
            else qmarks = false;
            if (wcscmp(value, L"")) SetWindowText(field, result.c_str());
        }
        break;
    // завершение приложения
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
// Главная функция графического приложения
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInst);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // Регистрация класса окна и задание его свойств
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
    // При ошибке регистрации окна
    if (!RegisterClassEx(&wcex)) {
        MessageBox(nullptr, L"Ошибка регистрации окна!", L"Ошибка!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    // Создание главного окна
    HWND hWnd = CreateWindowEx(0, L"MagicBallClass", L"Шар Судьбы", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, hInstance, nullptr);
    if (!hWnd) {
        MessageBox(nullptr, L"Не удалось создать окно!", L"Ошибка!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    RECT rc;
    GetWindowRect(hWnd, &rc);
    int xPos = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
    int yPos = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;
    SetWindowPos(hWnd, 0, xPos, yPos, 0, 0, SWP_NOSIZE);
    // Отображение окна
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    // Цикл обработки сообщений
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}



