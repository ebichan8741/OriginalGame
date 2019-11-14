#pragma once

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#define DIRECTINPUT_VERSION (0x0800)
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include "resource.h"

#pragma comment(lib,"winmm.lib")        //システム時刻取得に必要
#pragma comment(lib,"d3d9.lib")			//ライブラリのリンク
#pragma comment(lib,"d3dx9.lib")		//ライブラリのリンク
#pragma comment(lib,"dxguid.lib")		//ライブラリのリンク
#pragma comment(lib,"dinput8.lib")

#define SCREEN_WIDTH	(1280)			//ウィンドウの幅
#define SCREEN_HEIGHT	(960)			//ウィンドウの高さ
#define CLASS_NAME		"サンプル"		//ウィンドウクラスの名前
#define WINDOW_NAME		"ウィンドウ"	//ウィンドウの名前