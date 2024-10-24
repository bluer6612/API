#include "PreCompile.h"
#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>

//class AActor
//{
//    Player* NewPlayer; // <= ���ߴ�.
//};
//
//class Player : public AActor
//{
//
//};

// ������ ���� ����� ������ ���� 
// #include <EngineCore/EngineAPICore.h>

//#ifdef _WINDOWS
//#include <Windows.h>
//#elseif _������
//#include <Windows.h>
//#elseif �ȵ���̵�
//#endif 

HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasss;
int WindowCount = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        --WindowCount;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void UEngineWindow::EngineWindowInit(HINSTANCE _Instance, WNDCLASSEXA _wcex)
{
    hInstance = _Instance;

    // ������ ������ ����� �Ѵٸ� ���⼭ �Ϸ��� �Ѱ�.
    // ����Ʈ ������ Ŭ���� ���
    _wcex.cbSize = sizeof(WNDCLASSEX);
    _wcex.style = CS_HREDRAW | CS_VREDRAW;
    _wcex.lpfnWndProc = WndProc;
    _wcex.cbClsExtra = 0;
    _wcex.cbWndExtra = 0;
    _wcex.hInstance = hInstance;
    _wcex.hIcon = nullptr;
    _wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    _wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 9);
    _wcex.lpszMenuName = nullptr;
    _wcex.lpszClassName = "Default" + WindowCount;
    _wcex.hIconSm = nullptr;
    ++WindowCount;
    CreateWindowClass(_wcex);
}

int UEngineWindow::WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction)
{
    // ����Ű �ε� ����
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));
    MSG msg = MSG();

    // �⺻ �޽��� �����Դϴ�:
    // �޼��� ������ getMessage��� ������ ������ ������ ����.
    // ���� �Լ��̱� �����̴�.
    // ���� �ڽ��� ������ ���������� �����ϴ� �Լ�.

    // GetMessage
    // �޼����� ���� => ������ ��ٸ�
    // �޼����� �ִ� => ó���ϰ� ����

    // ó���ϰ� ����
    // �޼����� ���� => ����
    // �޼����� �ִ� => ó���ϰ� ����

    // WindowCount;

    // ���α׷� �����ϰ� �� 1�� �ؾ����� �ִٸ� ���⿡ �־��.
    // �ִ��� ����ó�� ���ִ°� ����.
    if (true == _StartFunction.IsBind())
    {
        _StartFunction();
    }

    while (0 != WindowCount)
    {
        // if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))  => ������ ����Ű ��ü�� �������
        // ���� ���̹Ƿ� �׳� ����
        
        // PM_REMOVE == ���� ó���Ҷ� ���ݱ��� ���� �޼��� ������.
        if(0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (true == _FrameFunction.IsBind())
        {
            _FrameFunction();
        }
        // �޼����� ���� �ð��� �� ������ �����°ž�.
        // �޼��� ó���ϰ� ���� �� ���ӿ����� ������.
    }

    return (int)msg.wParam;
}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{
    // �Ϲ����� ���� ����

    std::map<std::string, WNDCLASSEXA>::iterator EndIter = WindowClasss.end();
    std::map<std::string, WNDCLASSEXA>::iterator FindIter = WindowClasss.find(std::string(_Class.lpszClassName));

    // ckw
    if (EndIter != FindIter)
    {
        // std::string ErrorText = "���� �̸��� ������ Ŭ������ 2�� ����߽��ϴ�" + std::string(_Class.lpszClassName);

        // std::string ���ο� ��� �ִ� �ɹ����� => std::string => std::vector<char>
        // std::vector<char> char* = new char[100];
        // ErrorText const char* �������ִ� �Լ��� c_str()
        // const char* Text = ErrorText.c_str();
        MSGASSERT(std::string(_Class.lpszClassName) + " ���� �̸��� ������ Ŭ������ 2�� ����߽��ϴ�");
        return;
    }

    RegisterClassExA(&_Class);

    WindowClasss.insert(std::pair{ _Class.lpszClassName, _Class });
}

UEngineWindow::UEngineWindow() 
{

    
}

UEngineWindow::~UEngineWindow()
{
}

void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{

    if (false == WindowClasss.contains(_ClassName.data()))
    {
        MSGASSERT(std::string(_ClassName) + " ������� ���� Ŭ������ ������â�� ������� �߽��ϴ�");
        return;
    }

    //WS_OVERLAPPEDWINDOW
    WindowHandle = CreateWindowA(_ClassName.data(), 0, WS_OVERLAPPED,
        -10, (ScreenY - (ScreenY / 3)), WS_SYSMENU, ScreenY / 3, nullptr, nullptr, hInstance, nullptr);

    WindowHandleSub = CreateWindowA(_ClassName.data() + 'S', 0, WS_OVERLAPPED,
        -10, ScreenY / 3, WS_SYSMENU, (ScreenY - (ScreenY / 3)), WindowHandle, nullptr, hInstance + 'S', nullptr);

    if (nullptr == WindowHandle)
    {
        MSGASSERT(std::string(_TitleName) + " ������ ������ �����߽��ϴ�.");
        return;
    }

    // �����찡 ��������� hdc�� ���⼭ ���� �̴ϴ�.
    BackBuffer = GetDC(WindowHandle);
}

void UEngineWindow::Open(std::string_view _TitleName /*= "Window"*/)
{
    // �� window �ȸ���� ������ �ϳ�?
    if (0 == WindowHandle)
    {
        // �����
        Create("Window");
    }

    if (0 == WindowHandle)
    {
        return;
    }

	// �ܼ��� ����â�� �����ִ� �͸��� �ƴ϶�
	ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);
    SetWindowTopMost(WindowHandle);

    ShowWindow(WindowHandleSub, SW_SHOW);
    UpdateWindow(WindowHandleSub);
    SetWindowTopMost(WindowHandleSub);
    SetWindowOpacity(WindowHandleSub);

	// ShowWindow(WindowHandle, SW_HIDE);
}

void UEngineWindow::SetWindowTopMost(HWND _WindowHandle)
{
    RECT rc1;
    ::GetWindowRect(_WindowHandle, &rc1);
    SetForegroundWindow(_WindowHandle);
    SetWindowPos(_WindowHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

    long style = ::GetWindowLongA(_WindowHandle, GWL_STYLE);
    style &= ~WS_CAPTION;
    SetWindowLongA(_WindowHandle, GWL_STYLE, style);

    //SetWindowRgn(WindowHandle, hRgn, false);
}

void UEngineWindow::SetWindowOpacity(HWND _WindowHandle)
{
    SetWindowLong(_WindowHandle, GWL_EXSTYLE, GetWindowLong(_WindowHandle, GWL_EXSTYLE) | WS_EX_LAYERED); SetLayeredWindowAttributes(_WindowHandle, 0, 150, LWA_ALPHA);
}