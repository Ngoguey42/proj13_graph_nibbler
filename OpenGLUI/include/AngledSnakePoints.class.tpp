// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AngledSnakePoints.class.tpp                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/15 08:02:43 by ngoguey           #+#    #+#             //
//   Updated: 2015/06/01 16:05:43 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

constexpr ftce::Array<size_t, 6>    AngledSnakePoints::calcPointsArraySize(
	bool sinistro)
{
	ftce::Array<size_t, 6>  ret;
	ARRAY_DEFAULT_SIZE      points{};
	float                   phase(0.f);

	for (size_t i = 0; i < points.size(); i++, phase += 1.f / NUM_PRECALC_POINTSF)
	{
		points[i].init(phase, sinistro);
		ret[0] = ftce::max(points[i].leftStrip1.getLastIndex() + 1, ret[0]);
		ret[1] = ftce::max(points[i].leftFan.getLastIndex() + 1, ret[1]);
		ret[2] = ftce::max(points[i].leftStrip2.getLastIndex() + 1, ret[2]);
		ret[3] = ftce::max(points[i].rightStrip1.getLastIndex() + 1, ret[3]);
		ret[4] = ftce::max(points[i].rightFan.getLastIndex() + 1, ret[4]);
		ret[5] = ftce::max(points[i].rightStrip2.getLastIndex() + 1, ret[5]);
	}
	return (ret);
}

template <size_t S1, size_t S2, size_t S3, size_t S4, size_t S5, size_t S6>
constexpr ARRAY_CUSTOM_SIZE         AngledSnakePoints::buildPointsArray(bool sinistro)
{
	ARRAY_CUSTOM_SIZE       points{};
	float                   phase(0.f);

	for (size_t i = 0; i < points.size(); i++, phase += 1.f / NUM_PRECALC_POINTSF)
	{
		points[i].init(phase, sinistro);
	}
	return points;
}


// * CONSTRUCTORS *********************************************************** //
constexpr AngledSnakePoints::AngledSnakePoints() :
	leftBranchIntersection(),
	leftBranchInPoints(),
	leftBranchInLastIndex(0),
	leftBranchOutPoints(),
	leftBranchOutLastIndex(0),

	middleBranchIntersection(),
	middleBranchInPoints(),
	middleBranchInLastIndex(0),
	middleBranchOutPoints(),
	middleBranchOutLastIndex(0),

	rightBranchIntersection(),
	rightBranchInPoints(),
	rightBranchInLastIndex(0),
	rightBranchOutPoints(),
	rightBranchOutLastIndex(0)
{
	return ;
}
constexpr AngledSnakePoints::AngledSnakePoints(AngledSnakePoints const &src) :
	leftBranchIntersection(src.leftBranchIntersection),
	leftBranchInPoints(src.leftBranchInPoints),
	leftBranchInLastIndex(src.leftBranchInLastIndex),
	leftBranchOutPoints(src.leftBranchOutPoints),
	leftBranchOutLastIndex(src.leftBranchOutLastIndex),

	middleBranchIntersection(src.middleBranchIntersection),
	middleBranchInPoints(src.middleBranchInPoints),
	middleBranchInLastIndex(src.middleBranchInLastIndex),
	middleBranchOutPoints(src.middleBranchOutPoints),
	middleBranchOutLastIndex(src.middleBranchOutLastIndex),

	rightBranchIntersection(src.rightBranchIntersection),
	rightBranchInPoints(src.rightBranchInPoints),
	rightBranchInLastIndex(src.rightBranchInLastIndex),
	rightBranchOutPoints(src.rightBranchOutPoints),
	rightBranchOutLastIndex(src.rightBranchOutLastIndex)
{
	return ;
}

constexpr AngledSnakePoints		&AngledSnakePoints::operator=(AngledSnakePoints const &rhs)
{
	this->leftBranchIntersection = rhs.leftBranchIntersection;
	this->leftBranchInPoints = rhs.leftBranchInPoints;
	this->leftBranchInLastIndex = rhs.leftBranchInLastIndex;
	this->leftBranchOutPoints = rhs.leftBranchOutPoints;
	this->leftBranchOutLastIndex = rhs.leftBranchOutLastIndex;
	this->middleBranchIntersection = rhs.middleBranchIntersection;
	this->middleBranchInPoints = rhs.middleBranchInPoints;
	this->middleBranchInLastIndex = rhs.middleBranchInLastIndex;
	this->middleBranchOutPoints = rhs.middleBranchOutPoints;
	this->middleBranchOutLastIndex = rhs.middleBranchOutLastIndex;
	this->rightBranchIntersection = rhs.rightBranchIntersection;
	this->rightBranchInPoints = rhs.rightBranchInPoints;
	this->rightBranchInLastIndex = rhs.rightBranchInLastIndex;
	this->rightBranchOutPoints = rhs.rightBranchOutPoints;
	this->rightBranchOutLastIndex = rhs.rightBranchOutLastIndex;
	return (*this);
}

// * MEMBER FUNCTIONS / METHODS ********************************************* //
constexpr int				AngledSnakePoints::init(float const initRatio,
													bool sinistro)
{
	float	curphase(initRatio);

	(void)sinistro;
	// Setting this->leftBranchInPoints		//
	if (sinistro)
	{
		for (int j = 0; j < MAX_POINTS_BEFORE_ANGLE; j++)
		{
			t_vertexf	&ref(this->leftBranchInPoints[j]);

			ref = t_vertexf(
				((ftce::cos((0.5f + curphase) * M_PI * 2.f) + 1.f) /
				 2.f * SNAKE_WIDTH_INV + SNAKE_WIDTH),
				j * (TRIANGLES_DISTANCE / CHUNK_SIZEF));
			this->rightBranchInPoints[j] = t_vertexf(
				ref.x - SNAKE_WIDTH,
				ref.y);
			this->middleBranchInPoints[j] = t_vertexf(
				ref.x - SNAKE_WIDTH_HALF,
				ref.y);
			curphase = ftce::fmod(curphase + PHASE_PER_TRIANGLE, 1.f);
		}
		// Setting this->leftBranchOutPoints		//
		curphase = ftce::fmod(initRatio + PHASE_PER_CHUNK, 1.f);
		for (int j = 0; j < MAX_POINTS_BEFORE_ANGLE; j++)
		{
			t_vertexf   &ref(this->leftBranchOutPoints[j]);

			ref = t_vertexf(
				1.f - j * (TRIANGLES_DISTANCE / CHUNK_SIZEF),
				SNAKE_WIDTH_INV - (ftce::cos((0.5f + curphase) * M_PI * 2.f)
								   + 1.f) / 2.f * SNAKE_WIDTH_INV);
			this->rightBranchOutPoints[j] = t_vertexf(
				ref.x,
				ref.y + SNAKE_WIDTH);
			this->middleBranchOutPoints[j] = t_vertexf(
				ref.x,
				ref.y + SNAKE_WIDTH_HALF);
			curphase = ftce::fmod(curphase - PHASE_PER_TRIANGLE, 1.f);
		}
	}
	else
	{
		for (int j = 0; j < MAX_POINTS_BEFORE_ANGLE; j++)
		{
			t_vertexf	&ref(this->leftBranchInPoints[j]);

			ref = t_vertexf(
				((ftce::cos((0.5f + curphase) * M_PI * 2.f) + 1.f) /
				 2.f * SNAKE_WIDTH_INV + SNAKE_WIDTH),
				j * (TRIANGLES_DISTANCE / CHUNK_SIZEF));
			this->rightBranchInPoints[j] = t_vertexf(
				ref.x - SNAKE_WIDTH,
				ref.y);
			this->middleBranchInPoints[j] = t_vertexf(
				ref.x - SNAKE_WIDTH_HALF,
				ref.y);
			curphase = ftce::fmod(curphase + PHASE_PER_TRIANGLE, 1.f);
		}
		// Setting this->leftBranchOutPoints		//
		curphase = ftce::fmod(initRatio + PHASE_PER_CHUNK, 1.f);
		for (int j = 0; j < MAX_POINTS_BEFORE_ANGLE; j++)
		{
			this->leftBranchOutPoints[j] = t_vertexf(
				j * (TRIANGLES_DISTANCE / CHUNK_SIZEF),
				SNAKE_WIDTH + (ftce::cos((0.5f + curphase) * M_PI * 2.f)
							   + 1.f) / 2.f * SNAKE_WIDTH_INV);
			this->rightBranchOutPoints[j] = t_vertexf(
				this->leftBranchOutPoints[j].x,
				this->leftBranchOutPoints[j].y - SNAKE_WIDTH);
			this->middleBranchOutPoints[j] = t_vertexf(
				this->leftBranchOutPoints[j].x,
				this->leftBranchOutPoints[j].y - SNAKE_WIDTH_HALF);
			curphase = ftce::fmod(curphase - PHASE_PER_TRIANGLE, 1.f);
		}
	}

	for (size_t i = 0; i <= this->leftBranchInPoints.getLastIndex(); i++)
		this->leftBranchInPoints[i] *= CHUNK_SIZEF;
	for (size_t i = 0; i <= this->leftBranchOutPoints.getLastIndex(); i++)
		this->leftBranchOutPoints[i] *= CHUNK_SIZEF;
	for (size_t i = 0; i <= this->middleBranchInPoints.getLastIndex(); i++)
		this->middleBranchInPoints[i] *= CHUNK_SIZEF;
	for (size_t i = 0; i <= this->middleBranchOutPoints.getLastIndex(); i++)
		this->middleBranchOutPoints[i] *= CHUNK_SIZEF;
	for (size_t i = 0; i <= this->rightBranchInPoints.getLastIndex(); i++)
		this->rightBranchInPoints[i] *= CHUNK_SIZEF;
	for (size_t i = 0; i <= this->rightBranchOutPoints.getLastIndex(); i++)
		this->rightBranchOutPoints[i] *= CHUNK_SIZEF;
	this->leftBranchIntersection = this->calcIntersection(
		this->leftBranchInPoints, this->leftBranchOutPoints,
		this->leftBranchInLastIndex, this->leftBranchOutLastIndex);
	this->rightBranchIntersection = this->calcIntersection(
		this->rightBranchInPoints, this->rightBranchOutPoints,
		this->rightBranchInLastIndex, this->rightBranchOutLastIndex);
	this->middleBranchIntersection = this->calcIntersection(
		this->middleBranchInPoints, this->middleBranchOutPoints,
		this->middleBranchInLastIndex, this->middleBranchOutLastIndex);
	return (0);
}

constexpr AngledSnakePoints::t_vertexf				AngledSnakePoints::calcIntersection(
	t_snakepoints const &inPoints, t_snakepoints const &outPoints,
	size_t &inLastIndex, size_t &outLastIndex)
{
	float	bestDistance = CHUNK_SIZEF;

	for (size_t i = 0; i <= inPoints.getLastIndex(); i++)
	{
		auto const &w = inPoints[i];
		for (size_t j = 0; j <= outPoints.getLastIndex(); j++)
		{
			auto const &x = outPoints[j];
			float const	dx = w.x - x.x;
			float const	dy = w.y - x.y;
			float const	distance = dx * dx + dy * dy;
			
			if (bestDistance > distance)
			{
				bestDistance = distance;
				inLastIndex = i;
				outLastIndex = j;
			}
		}
	}
	return (setBranchIntersection(inPoints[inLastIndex],
								  outPoints[outLastIndex]));
}

constexpr AngledSnakePoints::t_vertexf				AngledSnakePoints::setBranchIntersection(
	t_vertexf const &a, t_vertexf const &b)
{
	return (t_vertexf(
				b.x + (a.x - b.x) / 2,
				b.y + (a.y - b.y) / 2));
}
