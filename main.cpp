#include "window.h"

#include <iostream>

int main(int argc, char** argv)
{
	try {
		Window::Init();
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		Window::Quit();
	}

	Window::Quit();

	return 0;
}