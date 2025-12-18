#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN


#ifndef DX_12_COMMON_HPP
#define DX_12_COMMON_HPP

#include <Windows.h>

#include <wrl.h>
#include <dxgi1_6.h>
#include <d3d12.h>

using Microsoft::WRL::ComPtr;

#include <stdexcept>
#include <string>
#include <comdef.h>

inline void ThrowIfFailed(HRESULT hr) {
	if (FAILED(hr)) {
		_com_error err(hr);
		std::wstring msg = err.ErrorMessage();
		throw std::runtime_error(std::string(msg.begin(), msg.end()));
	}
}

static void DxTrace(const wchar_t* s)
{
#if defined(_DEBUG)
	OutputDebugStringW(s);
	OutputDebugStringW(L"\n");
#endif
}

#endif // !DX_12_COMMON_HPP
