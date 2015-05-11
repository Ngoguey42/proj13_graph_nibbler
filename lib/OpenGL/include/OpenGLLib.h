/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLLib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 08:52:25 by ngoguey           #+#    #+#             */
/*   Updated: 2015/05/11 12:12:55 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLLIB_H
# define OPENGLLIB_H

#include <cmath>

# ifndef DEG_TO_RAD
#  define DEG_TO_RAD(angleDegrees) (angleDegrees * M_PI / 180.0)
# endif

# ifndef M_PI
#  define M_PI 3.14159265358979323846f
# endif

# ifndef M_CEIL
#  define M_CEIL(x) ((int(x) == x) ? int(x) : (x >= 0.0) ? int(x) + 1 : int(x))
# endif

//  ==================================  //
#define CHUNK_SIZE 35                   // Pixels integer
#define SNAKE_WAVELENGTH 105.f          // Pixels float
#define SNAKE_WIDTH 0.66f               // Percent of CHUNK_SIZE
#define POINTS_PER_SIDE 9               //

/* #define SNAKE_WAVELENGTH 17.5f            // Pixels float */
/* #define SNAKE_WIDTH 0.8f             // Percent of CHUNK_SIZE */
/* #define POINTS_PER_SIDE 18               // */

#define PRECALC_POINTS_DELTA 0.25f        // Density of pre-calculated points
//  ==================================  //

//are all those macro evaluated preprocessor?
#define CHUNK_SIZEF static_cast<float>(CHUNK_SIZE)
#define POINTS_PER_SIDEF static_cast<float>(POINTS_PER_SIDE)

#define SNAKE_WIDTH_ABSOLUTE (SNAKE_WIDTH * CHUNK_SIZEF)
#define SNAKE_WIDTH_INV (1.f - SNAKE_WIDTH)
#define SNAKE_WIDTH_HALF (SNAKE_WIDTH / 2.f)
#define PHASE_PER_CHUNK (CHUNK_SIZEF / SNAKE_WAVELENGTH)
#define PHASE_PER_TRIANGLE (PHASE_PER_CHUNK / POINTS_PER_SIDEF)
#define TRIANGLES_DISTANCE (CHUNK_SIZEF / POINTS_PER_SIDEF)

//  Points pre-calculation macros ====  //
//      Number of pixels                //
#define PHASE_MAX_DELTA (CHUNK_SIZEF * (1 - SNAKE_WIDTH))
//      Number of points float          //
/* #define NUM_PRECALC_POINTSF ceilf(PHASE_MAX_DELTA / PRECALC_POINTS_DELTA) */
#define NUM_PRECALC_POINTSF M_CEIL(PHASE_MAX_DELTA / PRECALC_POINTS_DELTA)
//      Number of points integer        //
#define NUM_PRECALC_POINTS static_cast<int>(NUM_PRECALC_POINTSF)
//  ==================================  //

#define MAX_POINTS_BEFORE_ANGLEF floorf(POINTS_PER_SIDEF * SNAKE_WIDTH_INV + 1.f)
// #define MAX_POINTS_BEFORE_ANGLE static_cast<int>(MAX_POINTS_BEFORE_ANGLEF)
#define MAX_POINTS_BEFORE_ANGLE (POINTS_PER_SIDE + 1)

#endif