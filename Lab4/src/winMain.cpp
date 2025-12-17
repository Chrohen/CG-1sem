#include <iostream>
#include <thread>
#include "Window.hpp"

int main() {
	Window window(800, 600, L"CG Window");

	while (window.ProcessMessages()) {

	}

	return 0;
}