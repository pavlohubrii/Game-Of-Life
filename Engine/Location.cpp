#include "Location.h"

Location::Location(int xi, int yi)
	:
	x(xi),
	y(yi)
{}

Location &Location::operator=(Location src){
	x = src.x;
	y = src.y;
	return *this;
}
