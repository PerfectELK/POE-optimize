#include "App/App.h"


HWND hwnd;

int CALLBACK wWinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE, PWSTR szCmdLine, int nCmdShow) {

	App app{};
	return app.Run();

}