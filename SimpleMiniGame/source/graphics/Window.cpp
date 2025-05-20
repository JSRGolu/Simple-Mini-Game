#include "../../include/graphics/Window.h"
#include "../../include/core/Game.h"
#include <iostream>

Window::Window() :
	windowTitle(""),
	windowSize({ 0,0 }),
	isFullscreen(false),
	isDone(false)
{ }

Window::~Window() { destroy(); }

void Window::loadFont(const std::string& fontFile)
{
	//Load the font for the GUI
	if (!guiFont.loadFromFile(fontFile))
	{
		throw std::runtime_error("Font file not found for Window: " + fontFile);
	}

	//Set up the text 
	fpsText.setCharacterSize(fontSize);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setFont(guiFont);

	pausedText.setCharacterSize(fontSize + 10);
	pausedText.setFillColor(sf::Color::Red);
	pausedText.setFont(guiFont);
	pausedText.setString("PAUSED!");

	commandText.setCharacterSize(fontSize + 10);
	commandText.setFillColor(sf::Color::White);
	commandText.setFont(guiFont);
	commandText.setString("Press 'F' to change movement command");
}

void Window::setup(const std::string& title, const sf::Vector2u& size)
{
	windowTitle = title;
	windowSize = size;
	create();
}


void Window::create()
{
	auto style = (isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	window.create({ windowSize.x, windowSize.y, 32 }, windowTitle, style);
	pausedText.setPosition(windowSize.x * 0.45f, 0.0f);
	commandText.setPosition(windowSize.x * 0.25f, windowSize.y * 0.95f);
}

void Window::destroy()
{
	window.close();
}

void Window::update()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			isDone = true;
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
			toggleFullscreen();
	}
}

void Window::toggleFullscreen()
{
	isFullscreen = !isFullscreen;
	redraw();
}

void Window::redraw()
{
	destroy();
	create();
}

void Window::beginDraw() { window.clear(sf::Color::Black); }
void Window::endDraw() { window.display(); }

bool Window::isWindowDone() const { return isDone; }
bool Window::isWindowFullscreen() const { return isFullscreen; }
const sf::Vector2u& Window::getWindowSize() const { return windowSize; }
const sf::Font& Window::getGUIFont() const { return guiFont; }
sf::Text& Window::getFPSText() { return fpsText; }

void Window::drawGUI(const Game& game)
{
	window.draw(fpsText);

	if (game.isPaused())
		window.draw(pausedText);

	window.draw(commandText);
}

void Window::draw(sf::Drawable& drawable) {
	window.draw(drawable);
}