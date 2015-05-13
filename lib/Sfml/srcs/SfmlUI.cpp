/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SfmlUI.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 17:49:28 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/13 13:46:36 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SfmlUI.hpp"
#include "IGame.hpp"
#include "ISnake.hpp"

SfmlUI::SfmlUI(std::pair<int, int> gameSize)
	: sf::RenderWindow(_getWindowSize(gameSize, _chunkSize), WINDOW_TITLE, sf::Style::Close),
	_gameSize(gameSize),
	_line(sf::LinesStrip, 2)
{
	_events[sf::Keyboard::Up] = EVENT_UP;
	_events[sf::Keyboard::Right] = EVENT_RIGHT;
	_events[sf::Keyboard::Down] = EVENT_DOWN;
	_events[sf::Keyboard::Left] = EVENT_LEFT;
	_events[sf::Keyboard::Space] = EVENT_SPACE;
	_events[sf::Keyboard::R] = EVENT_R;
	_events[sf::Keyboard::Num1] = EVENT_1;
	_events[sf::Keyboard::Num2] = EVENT_2;
	_events[sf::Keyboard::Num3] = EVENT_3;
	_events[sf::Keyboard::Num4] = EVENT_4;
	_events[sf::Keyboard::Num5] = EVENT_5;
	_events[sf::Keyboard::Num6] = EVENT_6;
	_events[sf::Keyboard::Num7] = EVENT_7;
	_line[0].color = sf::Color(GRID_COLOR);
	_line[1].color = sf::Color(GRID_COLOR);
}

SfmlUI::~SfmlUI(void)
{
}

EventType			SfmlUI::getEvent(void)
{
	sf::Event		event;

	pollEvent(event);
	if (event.type == sf::Event::Closed)
		close();
	else if (event.type == sf::Event::KeyPressed)
	{
		if (_events.find(event.key.code) != _events.end())
			return (_events[event.key.code]);
		if (event.key.code == sf::Keyboard::Q || sf::Keyboard::Escape)
			close();
	}
	return (EVENT_NOPE);
}

void				SfmlUI::draw(IGame const &game)
{
	clear();
	_drawGrid();
	// Draw blocks
	for (auto *b : game.getBlocks())
	{
		if (b->getType() == IBlock::GROW)
			_drawGrowBlock(b->getX(), b->getY());
		else
			_drawWallBlock(b->getX(), b->getY());
	}
	// Draw snake
	for (auto &c : game.getSnake().getChunks())
		_drawSnakeChunk(c.first, c.second);
	if (game.getSnake().isDie())
	{
		auto &head = *(game.getSnake().getChunks().begin());
		_drawWallBlock(head.first, head.second);
		_drawGrowBlock(head.first, head.second);
	}
	display();
}

bool				SfmlUI::windowShouldClose(void) const
{
	return (!isOpen());
}

void				SfmlUI::_drawGrid(void)
{
	static sf::RectangleShape	rect = sf::RectangleShape(sf::Vector2f(
		_gameSize.first * _chunkSize, _gameSize.second * _chunkSize));

	rect.setPosition(_chunkSize, _chunkSize);
	rect.setFillColor(sf::Color(GRID_COLOR, 30));
	sf::RenderWindow::draw(rect);
	for (int y = 0; y <= _gameSize.second; ++y)
		_drawLine(0, y * _chunkSize, _gameSize.first * _chunkSize, 0);
	for (int x = 0; x <= _gameSize.first; ++x)
		_drawLine(x * _chunkSize, 0, 0, _gameSize.second * _chunkSize);
}

void				SfmlUI::_drawWallBlock(int x, int y)
{
	x *= _chunkSize;
	y *= _chunkSize;
	_drawLine(x, y, _chunkSize, _chunkSize);
	_drawLine(x + _chunkSize, y, -_chunkSize, _chunkSize);
}

void				SfmlUI::_drawGrowBlock(int x, int y)
{
	static int			d = _chunkSize / 4;

	x *= _chunkSize;
	y *= _chunkSize;
	for (int w = 0; w < _chunkSize - 1; w += d)
		_drawLine(x + w, y, 0, _chunkSize);
}

void				SfmlUI::_drawSnakeChunk(int x, int y)
{
	static int			d = _chunkSize / 4;

	x *= _chunkSize;
	y *= _chunkSize;
	for (int h = 0; h < _chunkSize - 1; h += d)
		_drawLine(x, y + h, _chunkSize, 0);
}

void				SfmlUI::_drawLine(int x, int y, int w, int h)
{
	x += _chunkSize;
	y += _chunkSize;
	_line[0].position = sf::Vector2f(x, y);
	_line[1].position = sf::Vector2f(x + w, y + h);
	sf::RenderWindow::draw(_line);
}

sf::VideoMode		SfmlUI::_getWindowSize(std::pair<int, int> gameSize, int &chunkSize)
{
	sf::VideoMode		mode = sf::VideoMode::getDesktopMode();

	gameSize.first += 2;
	gameSize.second += 2;
	mode.width -= 100;
	mode.height -= 100;
	chunkSize = std::min(mode.width / gameSize.first, mode.height / gameSize.second);
	chunkSize = std::min(chunkSize - (chunkSize % 2), MAX_CHUNK_SIZE);
	mode.width = chunkSize * gameSize.first;
	mode.height = chunkSize * gameSize.second;
	return (mode);
}
