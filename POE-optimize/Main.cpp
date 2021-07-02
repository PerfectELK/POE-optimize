#include "App/App.h"

int CALLBACK wWinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE, PWSTR szCmdLine, int nCmdShow) {
	App app{};
	return app.Run();
}