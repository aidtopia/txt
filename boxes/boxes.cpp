#define NOMINMAX
#include <atlbase.h>
#include <atlwin.h>
#include <Windows.h>

// Enable visual styles.
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

class DiagramWnd : public ATL::CWindowImpl<DiagramWnd> {
    public:
        DECLARE_WND_CLASS(L"Aidtopia Boxes Diagram Window");
    BEGIN_MSG_MAP(DiagramWnd)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

    private:
        LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL &) {
            NONCLIENTMETRICSW metrics = { sizeof(metrics) };
            ::SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, metrics.cbSize, &metrics, 0);
            LOGFONTW lf = metrics.lfMenuFont;
            lf.lfHeight *= 2;
            m_hfont = ::CreateFontIndirectW(&lf);
            return 0;
        }

        LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL &) {
            ::DeleteObject(m_hfont);
            m_hfont = static_cast<HFONT>(::GetStockObject(SYSTEM_FONT));
            return 0;
        }

        LRESULT OnPaint(UINT, WPARAM, LPARAM, BOOL &) {
            PAINTSTRUCT ps;
            BeginPaint(&ps);
            RECT rc;
            GetClientRect(&rc);
            const auto hfontOld = ::SelectObject(ps.hdc, m_hfont);
            ::DrawTextW(ps.hdc, L"Boxes Go Here", -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            ::SelectObject(ps.hdc, hfontOld);
            EndPaint(&ps);
            return 0;
        }

        HFONT m_hfont = NULL;
};

class BoxesWnd : public ATL::CWindowImpl<BoxesWnd, ATL::CWindow, ATL::CFrameWinTraits> {
    public:
        DECLARE_WND_CLASS(L"Aidtopia Boxes Window");
    BEGIN_MSG_MAP(BoxesWnd)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
    END_MSG_MAP()

    private:
        LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL &) {
            m_wndDiagram.Create(m_hWnd, 0, L"Diagram", WS_CHILD | WS_VISIBLE);
            return 0;
        }

        LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL &) {
            ::PostQuitMessage(0);
            return 0;
        }

        LRESULT OnEraseBkgnd(UINT, WPARAM, LPARAM, BOOL &) {
            // Since our children cover, we don't actually need to erase, so
            // we lie and say we have erased to avoid flicker.
            return TRUE;
        }

        LRESULT OnSize(UINT, WPARAM, LPARAM, BOOL &) {
            RECT rc;
            GetClientRect(&rc);
            m_wndDiagram.SetWindowPos(NULL, &rc, SWP_NOZORDER);
            return 0;
        }

        DiagramWnd m_wndDiagram;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int nCmdShow) {
    ::HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    BoxesWnd wnd;
    wnd.Create(NULL, 0, L"Boxes");
    wnd.ShowWindow(nCmdShow);
    wnd.UpdateWindow();
    MSG msg = {0};
    while (::GetMessage(&msg, NULL, 0, 0) > 0) {
        ::TranslateMessage(&msg);
        ::DispatchMessageW(&msg);
    }

    return (msg.message == WM_QUIT) ? static_cast<int>(msg.wParam) : EXIT_FAILURE;
}
