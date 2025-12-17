#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <Windows.h>

class Window {
public:
	Window(int width, int height, const wchar_t* title);
	~Window();

	bool ProcessMessages();

	HWND GetHWND() const;


private:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND m_hwnd = nullptr;
	bool m_running = true;
};


#endif WINDOW_HPP