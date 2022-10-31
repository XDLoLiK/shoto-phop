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

void Window::setName(const std::string& name)
{
	m_name = name;
}

void Window::setGeometry(int w, int h)
{
	m_width  = w;
	m_height = h;
}

void Window::open()
{
	if (m_isOpened)
		return;

	Uint32 flags = (m_width && m_height) ? 0 : SDL_WINDOW_MAXIMIZED;

	m_realWindow = SDL_CreateWindow(m_name.c_str(), SDL_WINDOWPOS_CENTERED,
		                      SDL_WINDOWPOS_CENTERED, m_width, m_height, flags);
	if (!m_realWindow)
		std::cout << SDL_GetError() << std::endl;

	m_isOpened = true;
}

void Window::close()
{
	if (!m_isOpened)
		return;

	SDL_DestroyWindow(m_realWindow);

	m_realWindow = nullptr;
	m_isOpened   = false;
}

SDL_Window* Window::getRealWindow() const
{
	return m_realWindow;
}
