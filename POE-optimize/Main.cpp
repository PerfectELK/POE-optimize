#include "App/App.h"


HWND hwnd;

int CALLBACK wWinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE, PWSTR szCmdLine, int nCmdShow) {

	App app{};
	return app.Run();

}

// Это временный костыль для дебага в консоль, потом его уберу;
int main() {
	HINSTANCE hInstance{};
	HINSTANCE h{};
	PWSTR szCmdLine{};
	int nCmdShow = 1;

	wWinMain(hInstance,h, szCmdLine, nCmdShow);

	return 0;
}


