#include "Framework.hpp"

int main() {
	Framework app(800, 600, L"CG Window");

	if (!app.Init())
		return 0;

	return app.Run();
}