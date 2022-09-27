#pragma once

class Location{
public:
	Location(int xi, int yi);
	Location& operator =(Location src);
	int x, y;
};

