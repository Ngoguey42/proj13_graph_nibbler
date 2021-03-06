/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesUI.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 20:58:30 by juloo             #+#    #+#             */
/*   Updated: 2015/06/04 16:45:24 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "NcursesUI.hpp"
#include "IGame.hpp"
#include "ISnake.hpp"
#include "IBlock.hpp"

NcursesUI::NcursesUI(std::pair<int, int> gameSize)
	: _gameSize(gameSize), _shouldClose(false)
{
	initscr();
}

NcursesUI::~NcursesUI(void)
{
	erase();
	refresh();
	endwin();
}

void				NcursesUI::init(void)
{
	cbreak();
	timeout(0);
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	start_color();
	init_color(17, 125, 125, 125);
	init_color(18, 110, 110, 110);
	init_color(19, 95, 95, 95);
	init_color(20, 500, 30, 30);
	init_color(30, 140, 140, 140);
	init_pair(1, COLOR_WHITE, 30);
	init_pair(2, COLOR_RED, COLOR_RED);
	init_pair(3, 20, 20);
	init_pair(20, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(21, COLOR_BLUE, COLOR_BLUE);
	init_pair(22, COLOR_BLACK, COLOR_BLACK);
	init_pair(23, COLOR_CYAN, COLOR_CYAN);
	init_pair(13, 17, 17);
	init_pair(14, 18, 18);
	init_pair(15, 19, 19);
	_events['1'] = EVENT_1;
	_events['2'] = EVENT_2;
	_events['3'] = EVENT_3;
	_events['4'] = EVENT_4;
	_events['5'] = EVENT_5;
	_events['6'] = EVENT_6;
	_events['7'] = EVENT_7;
	_events[265] = EVENT_1;
	_events[266] = EVENT_2;
	_events[267] = EVENT_3;
	_events[268] = EVENT_4;
	_events[269] = EVENT_5;
	_events[270] = EVENT_6;
	_events[271] = EVENT_7;
	_events['r'] = EVENT_R;
	_events[' '] = EVENT_SPACE;
	_events[KEY_UP] = EVENT_UP;
	_events[KEY_RIGHT] = EVENT_RIGHT;
	_events[KEY_DOWN] = EVENT_DOWN;
	_events[KEY_LEFT] = EVENT_LEFT;
	_updateSize();
}

#include <iostream>

EventType		NcursesUI::getEvent(void)
{
	int				c;

	c = getch();
	if (c == 'q')
		_shouldClose = true;
	else if (c != ERR && _events.find(c) != _events.end())
		return (_events[c]);
	if (c != -1)
		std::cerr << "LOL: " << (int)c << std::endl;
	_updateSize();
	return (EVENT_NOPE);
}

void			NcursesUI::draw(IGame const &game)
{
	int				color = 0;

	erase();
	// Draw background
	for (int x = _gameSize.first - 1; x >= 0; --x)
		for (int y = _gameSize.second - 1; y >= 0; --y)
			_drawChunk(x, y, (color = (x + y) % 3) + 13, '.');
	// Draw blocks
	for (auto *b : game.getBlocks())
		_drawChunk(b->getX(), b->getY(), 20 + b->getType(), '+' + b->getType());
	// Draw snake
	for (auto &c : game.getSnake().getChunks())
		_drawChunk(c.first, c.second, 2, 'X');
	if (game.getSnake().isDie())
	{
		auto &head = *(game.getSnake().getChunks().begin());
		_drawChunk(head.first, head.second, 3, 'x');
	}
	attron(COLOR_PAIR(1));
	move(0, 0);
	printw("Score: %-3d Time: %-3d Length: %-3d FPS: %d",
		game.getScore(), game.getPlayTime(),
		game.getSnake().getChunks().size(), game.getFPS());
	if (game.getSnake().isDie())
		printw("  [[ DIE ]]");
	else if (game.isPaused())
		printw("  [[ PAUSE ]]");
	refresh();
}

void			NcursesUI::_drawChunk(int x, int y, int color, char c)
{
	x = x * _chunkWidth + _offset.first;
	y = y * _chunkHeight + _offset.second;
	attron(COLOR_PAIR(color));
	for (int w = _chunkWidth + x - 1; w >= x; --w)
		for (int h = _chunkHeight + y - 1; h >= y; --h)
			mvaddch(h, w, c);
}

void			NcursesUI::_updateSize(void)
{
	int				width;
	int				height;

	getmaxyx(stdscr, height, width);
	_winSize.first = width;
	_winSize.second = height;
	_chunkWidth = std::max(2, std::min(width / _gameSize.first,
		height / (_gameSize.second) * 2));
	_chunkHeight = _chunkWidth / 2;
	_offset = std::make_pair((width - (_chunkWidth * _gameSize.first)) / 2,
		(height - (_chunkHeight * _gameSize.second)) / 2);
}

bool			NcursesUI::windowShouldClose(void) const
{
	return (_shouldClose);
}
