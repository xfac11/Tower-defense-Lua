#include "WideText.h"
#include <stdlib.h>
#include <string.h>
WideText::WideText(const char* text)
{
	const size_t cSize = strlen(text) + 1;
	wchar = new wchar_t[cSize];
	size_t outSize;
	mbstowcs_s(&outSize, wchar, cSize, text, cSize - 1);
}

WideText::~WideText()
{
	delete[] wchar;
}

wchar_t* WideText::getWideChar()
{
	return wchar;
}
