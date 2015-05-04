/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:54:45 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/04 14:55:31 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <deque>

class	Snake
{
public:
	Snake(int x, int y);
	virtual ~Snake(void);

	typedef std::pair<int, int>	Chunk;

	std::deque<Chunk> const		&getChunks(void) const;

	void						move(int x, int y);

protected:

	std::deque<Chunk>			_chunks;

private:
	Snake(void);
	Snake(Snake const &src);
	Snake						&operator=(Snake const &rhs);
};

#endif
