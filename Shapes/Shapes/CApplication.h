#pragma once

#include <SFML/Graphics.hpp>
#include "CCanvas.h"
#include "CToolbar.h"

class CApplication {
public:
	static CApplication* GetInstance(std::istream& input, std::ostream& output, sf::RenderWindow& window);

	void Start();

private:
	CApplication(istream& input, ostream& output, sf::RenderWindow& window);

	void Read();
	void Write();
	void HandleEvent(sf::Event event);

	static CApplication* m_instance;

	std::istream& m_in;
	std::ostream& m_out;

	sf::RenderWindow& m_window;

	CCanvas* m_canvas;
	CToolbar* m_toolbar;
};
