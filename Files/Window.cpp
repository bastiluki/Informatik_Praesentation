#include "Window.h"

//Initialisierungsfunktion der Window-Klasse
Window::Window(const char* title, int width, int height, Render* render) : window(NULL), renderer(NULL), constTitle(title), constRender(render) {

	//Hier wird die Variable displayMode deklariert, die Bildschirmeigenschaften speichert.
	SDL_DisplayMode displayMode;

	//Die Fenstereigenschaften werden in displayMode gespeichert.
	SDL_GetDesktopDisplayMode(0, &displayMode);

	//Die Eigentliche Größe des Bildschirms wird gespeichert.
	nativeWidth = displayMode.w;
	nativeHeight = displayMode.h;

	//Es wird ein Fenster erstellt.
	window = SDL_CreateWindow(constTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL)
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

	//Es wird ein Renderer erstellt.
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
		std::cout << "Renderer failed to init. Error: " << IMG_GetError() << std::endl;

	//Pixel werden können undurchsichtig dargestellt.
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	//Die neuen Werte werden der Render-Klasse übergeben.
	render->updateValues(window, renderer, width, height);
}

//In der Zerstörungsfunktion werden Renderer und Fenster aus dem Arbeitsspeicher geladen.
Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}


void Window::changeResolution(int width, int height) {

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);

	window = SDL_CreateWindow(constTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL)
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
		std::cout << "Renderer failed to init. Error: " << IMG_GetError() << std::endl;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	constRender->updateValues(window, renderer, width, height);
}

void Window::makeFullscreen() {
	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);

	window = SDL_CreateWindow(constTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, nativeWidth, nativeHeight, SDL_WINDOW_SHOWN || SDL_WINDOW_FULLSCREEN);

	if (window == NULL)
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
		std::cout << "Renderer failed to init. Error: " << IMG_GetError() << std::endl;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	constRender->updateValues(window, renderer, nativeWidth, nativeHeight);
}

SDL_Renderer* Window::returnRenderer() {
	return renderer;
}
