#pragma once
class WideText
{
public:
	WideText(const char* text);
	~WideText();
	wchar_t* getWideChar();
private:
	wchar_t* wchar;
};

