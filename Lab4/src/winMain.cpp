#include <iostream>
#include <thread>
#include <Windows.h>

struct WindowStuff { //ugly struct
	bool running = true;
};

WindowStuff windowStuff;

//Обработчик сообщений
LRESULT windProc(HWND wind, UINT msg, WPARAM wp, LPARAM lp) {
	LRESULT rez = 0;

	switch (msg) {
	
		// Обработка события на закрытие окна
	case WM_CLOSE: 
		windowStuff.running = false;
		break;

		// Дефолтная обработка всего остального
	default:
		rez = DefWindowProc(wind, msg, wp, lp);
		break;
	}

	return rez;
}

int main() {

	//Создаем окно
	WNDCLASS window_class = { sizeof(WNDCLASS) }; // Я обязательно посмотрю первые видео по теме или нет

	window_class.hCursor = LoadCursor(0, IDC_ARROW); // Добавили курсор
	window_class.hInstance = GetModuleHandle(0); // экземпляр программы или как это называется
	window_class.lpszClassName = L"CGWindowClass"; // это имя класса? Вроде да
	window_class.style = CS_HREDRAW | CS_VREDRAW; // обновление окна при растяжении
	window_class.lpfnWndProc = windProc; // подвязываем обработчик событий
	window_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // черный фон

	if (!RegisterClass(&window_class)) { return 0; }; //регистрируем класс окна


	//Создаем окно
	HWND window = CreateWindowW(
		window_class.lpszClassName,
		L"CG window", // задаем название окна
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, // дефолтное окно,
		CW_USEDEFAULT, // позиция x 
		CW_USEDEFAULT, // позиция y
		CW_USEDEFAULT, // размер x
		CW_USEDEFAULT, // размер y
		0, 0, GetModuleHandle(0), 0 // я бы знал что это
	);

	while (windowStuff.running)
	{
		MSG msg = {}; // отправленные сообщения

		while (PeekMessage(&msg, window, 0, 0, PM_REMOVE) > 0) { // убираем сообщения из очереди
			TranslateMessage(&msg);
			DispatchMessageW(&msg); // вызываем сообщения через обработчик
		}
	}

	return 0;
}