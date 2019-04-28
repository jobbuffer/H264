// SimpleH264Analyzer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Stream.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	CStreamFile h264stream(argv[1]);

	h264stream.Parse_h264_bitstream();

	system("pause");
	return 0;
}
