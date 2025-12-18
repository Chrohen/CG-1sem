#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

#include <memory>
#include <Windows.h>
#include <windowsx.h>
#include "Window.hpp"
#include "Timer.hpp"

class Framework : public IWindowMessageHandler {
public:
	Framework(int width, int height, const wchar_t* title);
	virtual ~Framework() = default;

	bool Init();
	int Run();

	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

protected:
	virtual void CreateRtvAndDsvDescriptorHeaps();
	virtual void OnResize();
	virtual void Update(const double& dt);
	virtual void Draw();

	virtual void OnMouseDown(WPARAM btnState, int x, int y);
	virtual void OnMouseUp(WPARAM btnState, int x, int y);
	virtual void OnMouseMove(WPARAM btnState, int x, int y);

	HWND MainWnd() const { return m_window ? m_window->GetHWND() : nullptr; }
	int ClientWidth() const { return m_clientWidth; }
	int ClientHeight() const { return m_clientHeight; }

	Timer m_timer;

private:
	int m_initWidth = 0;
	int m_initHeight = 0;
	const wchar_t* m_title = nullptr;

	std::unique_ptr<Window> m_window;

	int m_clientWidth = 0;
	int m_clientHeight = 0;

	bool m_appPaused = false;
	bool m_minimized = false;
	bool m_maximized = false;
	bool m_resizing = false;
	

	POINT m_lastMousePos = { 0,0 };
};

#endif // FRAMEWORK_HPP