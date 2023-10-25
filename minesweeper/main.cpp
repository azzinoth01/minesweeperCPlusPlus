// sudoku.cpp : Defines the entry point for the application.
//

#include "Windows.h"
#include "D3D11Renderer.h"
#include "Minesweeper.h"


LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
D3D11Renderer* renderer;
Minesweeper minesweeper;
SpriteRenderer resetButton;

int windowWidth;
int windowHeight;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) {

    std::string currentDir = __argv[0];
    size_t lastBackSlash = currentDir.find_last_of('\\');
    currentDir.erase(lastBackSlash);
    SetCurrentDirectoryA(currentDir.c_str());

    WNDCLASSEXW wc = {};

    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = L"Minesweeper";

    RegisterClassExW(&wc);

    DWORD wndStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
    HWND hwnd = CreateWindowExW(0, wc.lpszClassName, L"Minesweeper", wndStyle, 0, 0, 800, 600, nullptr, nullptr, wc.hInstance, nullptr);

    DEVMODE devMode = {};
    EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &devMode);

    if (hwnd == nullptr) {
        return 0;
    }

    windowWidth = 700;
    windowHeight = 600;

    int left = (static_cast<int>(devMode.dmPelsWidth) - windowWidth) / 2;
    int top = (static_cast<int>(devMode.dmPelsHeight) - windowHeight) / 2;

    RECT rc = {};
    SetRect(&rc, left, top, left + windowWidth, top + windowHeight);
    AdjustWindowRectEx(&rc, wndStyle, false, 0);
    MoveWindow(hwnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);




    renderer = new D3D11Renderer();

    if (!renderer->Init(hwnd, windowWidth, windowHeight)) {
        return false;
    }


    minesweeper.GenerateField(Vector2Int(10, 10));

    resetButton.SetMaterial("VertexShader.cso", "PixelShader.cso");
    resetButton.SetTexture("Assets\\Reset.png");

    resetButton.SetPosition(Vector3(250, 550));
    resetButton.SetHeight(50);
    resetButton.SetWidth(200);
    resetButton.InitRender();

    bool open = true;
    MSG msg = {};

    int errcode = 0;

    while (open) {
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);

            if (msg.message == WM_QUIT) {
                open = false;
            }
            else if (msg.message == WM_LBUTTONDOWN) {
                int xPos = LOWORD(msg.lParam);
                int yPos = HIWORD(msg.lParam);

                Vector2Int position(xPos, windowHeight - yPos);
                minesweeper.LeftClickOnPosition(position);

                Vector3 botLeftPos = resetButton.GetPosition();
                Vector3 topRightPos = botLeftPos + Vector3::VectorRight * resetButton.GetWidth() + Vector3::VectorUp * resetButton.GetHeight();
                bool check = true;

                check = check && botLeftPos.X <= position.X && botLeftPos.Y <= position.Y;
                check = check && topRightPos.X >= position.X && topRightPos.Y >= position.Y;

                if (check == true) {
                    minesweeper.Reset();
                }


            }
            else if (msg.message == WM_RBUTTONDOWN) {
                int xPos = LOWORD(msg.lParam);
                int yPos = HIWORD(msg.lParam);

                Vector2Int position(xPos, windowHeight - yPos);
                minesweeper.RightClickOnPosition(position);
            }

        }

        if (!renderer->BeginRender()) {
            break;
        }

        minesweeper.BeginRender();
        resetButton.BeginRender();

        if (!renderer->Render()) {
            break;
        }

        minesweeper.Render();
        resetButton.Render();

        if (!renderer->EndRender()) {
            break;
        }

    }

    return errcode;
}

void ResizeWindow(HWND hwnd) {
    if (renderer != nullptr) {
        RECT rect = {};
        GetClientRect(hwnd, &rect);
        windowHeight = rect.bottom - rect.top;
        windowWidth = rect.right - rect.left;
        renderer->OnSizeChange(windowWidth, windowHeight);
    }

}

LRESULT WINAPI WndProc(HWND hwnd, UINT msgId, WPARAM wparam, LPARAM lparam) {
    switch (msgId) {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
        ResizeWindow(hwnd);
        return 0;
    default:
        break;
    }
    return DefWindowProcW(hwnd, msgId, wparam, lparam);
}

