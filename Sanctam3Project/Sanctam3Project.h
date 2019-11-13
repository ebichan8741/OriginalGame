#pragma once

#include <mmsystem.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "resource.h"

#pragma comment(lib,"winmm.lib")        //システム時刻取得に必要

#define SCREEN_WIDTH	(1280)			//ウィンドウの幅
#define SCREEN_HEIGHT	(960)			//ウィンドウの高さ
#define CLASS_NAME		"サンプル"		//ウィンドウクラスの名前
#define WINDOW_NAME		"ウィンドウ"	//ウィンドウの名前