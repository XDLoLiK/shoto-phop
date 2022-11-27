#include "window.hpp"

Window::Window(const std::string& name, int width, int height):
	m_name(name),
	m_width(width),
	m_height(height)
{

}

Window::~Window()
{
	if (m_isOpened)
		this->close();

	m_name   = "";
	m_width  = 0;
	m_height = 0;
}

Window& Window::operator=(Window&& other)
{
	this->close();
	
	this->m_realWindow = other.m_realWindow;
	this->m_width      = other.m_width;
	this->m_height     = other.m_height;
	this->m_name       = other.m_name;
	this->m_isOpened   = other.m_isOpened;

	other.m_realWindow = nullptr;

	return *this;
}

Window::Window(Window&& other)
{
	this->m_realWindow = other.m_realWindow;
	this->m_width      = other.m_width;
	this->m_height     = other.m_height;
	this->m_name       = other.m_name;
	this->m_isOpened   = other.m_isOpened;

	other.m_realWindow = nullptr;
}

bool Window::setName(const std::string& name)
{
	if (m_isOpened) {
		std::cout << "Can't change the name of an opened window" << std::endl;
		return false;
	}

	m_name = name;

	return true;
}

bool Window::setGeometry(int w, int h)
{
	if (m_isOpened) {
		std::cout << "Can't change the size of an opened window" << std::endl;
		return false;
	}

	m_width  = w;
	m_height = h;

	return true;
}

bool Window::open()
{
	if (m_isOpened) {
		std::cout << "The window is already opened" << std::endl;
		return false;
	}

	Uint32 flags = (m_width && m_height) ? 0 : SDL_WINDOW_MAXIMIZED;
	flags |= SDL_WINDOW_BORDERLESS;
	m_realWindow = SDL_CreateWindow(m_name.c_str(), SDL_WINDOWPOS_CENTERED,
		                      SDL_WINDOWPOS_CENTERED, m_width, m_height, flags);
	if (!m_realWindow) {
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	m_isOpened = true;

	return true;
}

bool Window::close()
{
	if (!m_isOpened) {
		std::cout << "The window is already closed" << std::endl;
		return false;
	}

	SDL_DestroyWindow(m_realWindow);

	m_realWindow = nullptr;
	m_isOpened   = false;

	return true;
}

SDL_Window* Window::getRealWindow() const
{
	return m_realWindow;
}
