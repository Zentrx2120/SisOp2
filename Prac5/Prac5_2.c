/*  Absalon Cortes Sebastian
    Izoteco Zacarias Pedro Uriel
    11 de junio 2024
    version 1.00
    Practica 5 Evaluacion: Compilador Grafico
*/
#include <windows.h>
#include <stdio.h>

#define LABEL "ABRIR"
#define FILENAME "C:\\Users\\Sebas\\OneDrive\\Desktop\\Escom\\CuartoSemestre\\SisOp2\\Prac5\\Lorem ipsum.txt"

// Prototipos de funciones
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OpenFileAndDisplay(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "Sample Window Class";
    WNDCLASS wc = {0};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Ventana de Saludo",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rect;
            GetClientRect(hwnd, &rect);
            DrawText(hdc, LABEL, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_LBUTTONDOWN: {
            RECT rect;
            GetClientRect(hwnd, &rect);
            POINT pt = { LOWORD(lParam), HIWORD(lParam) };
            if (PtInRect(&rect, pt)) {
                OpenFileAndDisplay(hwnd);
            }
            return 0;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void OpenFileAndDisplay(HWND hwnd) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        MessageBox(hwnd, "No se pudo abrir el archivo", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, file);
    fclose(file);

    string[fsize] = 0;

    MessageBox(hwnd, string, "Lorem ipsum", MB_OK | MB_ICONINFORMATION);
    free(string);
}