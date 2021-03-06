/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nibbler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 19:08:22 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/22 17:44:47 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_H
# define NIBBLER_H

/*
** ========================================================================== **
** Prototypes
*/

// Shared
class	IGame;
class	ISnake;
class	IBlock;
class	IUI;
class	IAudio;
// -

class	Game;
class	Snake;
class	Event;
class	ABlock;
class	GrowBlock;
class	WallBlock;
class	WallSpawnBlock;

/*
** ========================================================================== **
** Types
*/

enum	EventType
{
	EVENT_UP,
	EVENT_RIGHT,
	EVENT_DOWN,
	EVENT_LEFT,
	EVENT_SPACE,
	EVENT_R,
	EVENT_1,
	EVENT_2,
	EVENT_3,
	EVENT_4,
	EVENT_5,
	EVENT_6,
	EVENT_7,
	EVENT_NOPE
};

/*
** ========================================================================== **
** Libs
*/

# define WINDOW_TITLE		":: Nibbler ::"

# define INIT_FUNCTION		init

# define UI_1				"OpenGLUI/OpenGLUI.so"
# define UI_2				"NcursesUI/NcursesUI.so"
# define UI_3				"SfmlUI/SfmlUI.so"
# define UI_4				"SDLUI/SDLUI.so"

# define INITIAL_UI			UI_2

# define AUDIO_1			"SfmlAudio/SfmlAudio.so"

/*
** ========================================================================== **
** Utils
*/

// # define EACH(it,c)			auto it = (c).begin(); it != (c).end(); ++it

# define CAT(a, b)			a##b

# define STR_VALUE(s)		#s
# define STR(s)				STR_VALUE(s)

# define PRINT(msg)			std::cout << msg << std::endl;

# define DEBUG(msg)
// # define DEBUG(msg)			PRINT("Debug: " << msg)

#endif
