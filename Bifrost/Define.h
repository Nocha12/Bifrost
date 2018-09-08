#pragma once
#pragma warning (disable:4244 4800)
#include "DXUT.h"

#if defined(DEBUG) | defined(_DEBUG)
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#define for_iter(iter, col) for(auto iter = col.begin(); iter != col.end(); ++iter)


#define Vec2(x, y) D3DXVECTOR2((x),(y))
typedef D3DXVECTOR2 Vec2;

using namespace std;
using namespace std::tr2::sys;

class Rect : public RECT
{
public:
	Rect()
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}

	Rect(int l, int r, int t, int b)
	{
		left = l;
		right = r;
		top = t;
		bottom = b;
	}

	int width()
	{
		return right - left;
	}

	int height(){
		return bottom - top;
	}

	bool intersects(Rect t, Rect *inter)
	{
		return IntersectRect(inter, this, &t);
	}

	bool contain(Vec2 p)
	{
		return left < p.x && right > p.x && top < p.y && bottom > p.y;
	}

	Vec2 center()
	{
		return Vec2(width() / 2, height() / 2);
	}

	Rect offset(Vec2 p)
 	{
		Rect t = *this;
		t.left += p.x;
		t.right += p.x;
		t.top += p.y;
		t.bottom += p.y;
		return t;
	}
};

inline int random(int from, int to)
{
	static default_random_engine random(timeGetTime());
	uniform_int_distribution<int> d(from, to);
	return d(random);
}

inline float random(float from, float to)
{
	static default_random_engine random(timeGetTime());
	uniform_real_distribution<float> d(from, to);
	return d(random);
}

inline float angle(Vec2 p1, Vec2 p2)
{
	return atan2(p2.y - p1.y, p2.x - p1.x);
}

inline bool circleCol(Vec2 p1, Vec2 p2, float range)
{
	return pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) <= range * range;
}