// Sanctam3Project.cpp : アプリケーションのエントリ ポイントを定義します。
//
#include "stdafx.h"
#include "Sanctam3Project.h"
#include "Manager.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

static int g_FPSCount = 0;

// このコード モジュールに含まれる関数の宣言を転送します:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // ウィンドウクラスの登録
    WNDCLASSEX wcex;

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SANCTAM3PROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = CLASS_NAME;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassEx(&wcex);

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SANCTAM3PROJECT, szWindowClass, MAX_LOADSTRING);

    hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

    RECT cr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    RECT dr;

    GetWindowRect(GetDesktopWindow(), &dr);

    int dw = dr.right - dr.left;		//デスクトップの幅を求める
    int dh = dr.bottom - dr.top;		//デスクトップの高さを求める

    DWORD style = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);	//ウィンドウスタイル

    AdjustWindowRect(&cr, style, FALSE);	//スタイルや高さ幅を変更するもの

    int ww = cr.right - cr.left;		//ウィンドウの幅「フレームも合わせた」
    int wh = cr.bottom - cr.top;		//ウィンドウの高さ「フレームも合わせた」

    int wx = ww > dw ? 0 : (dw - ww) / 2;	//ウィンドウの左右の真ん中を求める
    int wy = wh > dh ? 0 : (dh - wh) / 2;	//ウィンドウの上下の真ん中を求める

    HWND hWnd = CreateWindowEx(0,		//拡張ウィンドウスタイル
        CLASS_NAME,                     //ウィンドウクラスの名前
        WINDOW_NAME,                    //ウィンドウの名前
        WS_OVERLAPPEDWINDOW,            //ウィンドウのスタイル
        CW_USEDEFAULT,                  //ウィンドウの座標(X座標単位ピクセル)
        0,                              //ウィンドウの座標(Y座標単位ピクセル)
        CW_USEDEFAULT,                  //ウィンドウの幅「フレームも合わせた」
        0,                              //ウィンドウの高さ「フレームも合わせた」
        nullptr,                        //親ウィンドウのハンドル
        nullptr,                        //メニューハンドルまたは子ウィンドウＩＤ
        hInstance,                      //インスタンスハンドル
        nullptr);                       //ウィンドウ作成データ

    // マネージャークラスインスタンスの生成
    CManager *pManager = NULL;
    pManager = new CManager;

    // マネージャークラスの初期化
    if (FAILED(pManager->Init(hInstance, hWnd, true)))
    {
        MessageBox(NULL, "初期化に失敗しました。", "", MB_OK);
        return E_FAIL;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SANCTAM3PROJECT));

    MSG msg;

    DWORD dwFrameCount = 0;
    DWORD dwCurrentTime = 0;
    DWORD dwExecLastTime = 0;
    DWORD dwFPSLastTime = 0;

    // 分解能を設定
    timeBeginPeriod(1);

    //各カウンターの初期化
    dwCurrentTime = 0;
    dwFrameCount = 0;
    dwExecLastTime = dwFPSLastTime = timeGetTime();	//システム時刻をミリ秒単位で取得

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // メイン メッセージ ループ:
    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
        {
            // アプリケーションの終了
            if (msg.message == WM_QUIT)
            {
                break;
            }
            else if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg); //仮想キーメッセージを文字メッセージへ変換
                DispatchMessage(&msg);  //ウィンドウプロシージャへメッセージを送出
            }
        }
        else
        {
            // FPSカウント
            dwCurrentTime = timeGetTime();

            // 0.5秒ごとにFPS表示用の変数（g_FPSCount）を更新している
            if ((dwCurrentTime - dwFPSLastTime) >= 500)
            {
                g_FPSCount = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
                dwFPSLastTime = dwCurrentTime;
                dwFrameCount = 0;
            }

            // 60FPSで計算、描画処理を回す
            if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
            {
                // 更新と描画
                pManager->Update();
                pManager->Draw();

                dwExecLastTime = dwCurrentTime;
                dwFrameCount++;
            }
        }
    }

    //ウィンドウの終了処理
    UnregisterClass(CLASS_NAME, wcex.hInstance);

    //終了処理
    if (pManager != NULL)
    {
        pManager->Uninit();
        pManager = NULL;
    }

    // 分解能を戻す
    timeEndPeriod(1);

    return (int) msg.wParam;
}


//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
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
