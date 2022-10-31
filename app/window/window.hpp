#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

class Window
{
public:
	Window(const std::string& name = "", int width = 0, int height = 0);
	~Window();

	Window& operator=(const Window& other) = delete;
	Window(const Window& other)            = delete;

	Window& operator=(Window&& other);
	Window(Window&& other);

	void setName(const std::string& name);
	void setGeometry(int w, int h);

	void open();
	void close();

	SDL_Window* getRealWindow() const;

private:
	std::string m_name = "";

	int m_width  = 0;
	int m_height = 0;

	bool m_isOpened = false;
	
	SDL_Window* m_realWindow = nullptr;
};

#endif // WINDOW_HPP
