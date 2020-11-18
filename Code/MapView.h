#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Simulator.h"
#include "Button.h"
#include "Definitions.h"

namespace ZPR {
	class MapView
	{
	public:
		MapView(SimulatorDataRef data, int gridSize);
		void Draw();

	private:
		sf::FloatRect CalculateViewPort();
		void DrawGrid();
		void GenerateGrid();
		SimulatorDataRef _data;
		int _gridSize;
		std::vector<sf::RectangleShape> _gridLines;
		sf::Sprite _backgroundTexture;
		sf::View _mapView;
	};
}

