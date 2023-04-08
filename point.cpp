#include <algorithm>
#include "point.h"
#include "utils.h"

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(int priority) {
	int rev = reverseSummation(priority);
	int sum = summation(rev);
	y = priority - sum;
	x = rev - y;
}

Point::Point(int x, int y) {
	x = x;
	y = y;
}

Point::Point(const Point& rhs) {
	x = rhs.x;
	y = rhs.y;
}

Point::~Point() {
}

Point& Point::set(int x, int y) {
	x = x;
	y = y;
	return *this;
}

Point& Point::modAdd(int x, int y) {
	x += x;
	y += y;
	return *this;
}

Point& Point::modSub(int x, int y) {
	x -= x;
	y -= y;
	return *this;
}

Point& Point::modMul(int mod) {
	x *= mod;
	y *= mod;
	return *this;
}

Point& Point::modDiv(int mod) {
	x /= mod;
	y /= mod;
	return *this;
}

Point& Point::modInv() {
	x = -x;
	y = -y;
	return *this;
}

Point Point::add(int x, int y) const {
	return Point(x + x, y + y);
}

Point Point::sub(int x, int y) const {
	return Point(x - x, y - y);
}

Point Point::mul(int mod) const {
	return Point(x * mod, y * mod);
}

Point Point::div(int mod) const {
	return Point(x / mod, y / mod);
}

Point Point::inv() const {
	return Point(-x, -y);
}

Point Point::absDiff(const Point& pos) const {
	return Point(abs(x-pos.x), abs(y-pos.y));
}

Point& Point::operator= (const Point& rhs) {
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Point& Point::operator+= (const Point& rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Point& Point::operator-= (const Point& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Point Point::operator+ (const Point& rhs) const {
	return Point(x + rhs.x, y + rhs.y);
}

Point Point::operator- (const Point& rhs) const {
	return Point(x - rhs.x, y - rhs.y);
}

Point Point::operator* (const Point& rhs) const {
	return Point(x * rhs.x, y * rhs.y);
}

Point Point::operator* (int mod) const {
	return Point(x * mod, y * mod);
}

Point Point::operator* (double mod) const {
	return Point(x * mod, y * mod);
}

Point Point::operator/ (const Point& rhs) const {
	return Point(x / rhs.x, y / rhs.y);
}

Point Point::operator/ (int mod) const {
	return Point(x / mod, y / mod);
}

Point Point::operator/ (double mod) const {
	return Point(x / mod, y / mod);
}

Point Point::operator% (int limit) const {
	return Point(x % limit, y % limit);
}

bool Point::operator== (const Point& rhs) const {
	return x == rhs.x && y == rhs.y;
}

bool Point::operator!= (const Point& rhs) const {
	return x != rhs.x || y != rhs.y;
}

bool Point::rectLessThan (const Point& rhs) const {
	if (x <= rhs.x && y < rhs.y) {
		return true;
	} else if (x < rhs.x && y <= rhs.y) {
		return true;
	}
	return false;
}

bool Point::rectMoreThan (const Point& rhs) const {
	if (x >= rhs.x && y > rhs.y) {
		return true;
	} else if (x > rhs.x && y >= rhs.y) {
		return true;
	}
	return false;
}

bool Point::operator< (const Point& rhs) const {
	if (x != rhs.x) return x < rhs.x;
	return y < rhs.y;
}

bool Point::operator>(const Point& rhs) const {
	if (x != rhs.x) return x > rhs.x;
	return y > rhs.y;
}

bool Point::operator< (int val) const {
	return x < val && y < val;
}

bool Point::operator>(int val) const {
	return x > val && y > val;
}

size_t Point::operator() (const Point& k) const {
	return summation(x + y) + y;
}

int Point::toRenderPriority() const {
	return summation(x + y) + y;
}

int Point::toRenderPriority(const Point& size) const {
	double dx = x + (size.x - 1) / 2.0;
	double dy = y + (size.y - 1) / 2.0;
	return summation(dx + dy) + dy;
}

int Point::toID(int xMax) const {
	return y * xMax + x;
}

Point Point::toIso() const {
	return Point(x - y, (x + y) / 2);
}

Point Point::toMap() const {
	return Point((2 * y + x) / 2, (2 * y - x) / 2);
}

Point Point::limit(int limit) const {
	int newX, newY;

	if (x < 0) {
        newX = std::max( x, -limit );
	} else {
        newX = std::min( x, limit );
	}

	if (y < 0) {
        newY = std::max( y, -limit );
	} else {
        newY = std::min( y, limit );
	}

	return Point(x, y);
}

void Point::iterate(int max, int min, int step) {
	x += step;
	if (x >= max) {
		y += step;
		x = min;
	}
}

void Point::convertToIso() {
	x -= y;
	y = (x + y) / 2;
}

void Point::convertToMap() {
	x = (2 * y + x) / 2;
	y = (2 * y - x) / 2;
}

bool Point::in(const Point& pos, const Point& size) const {
	Point max = pos + size;

	if (x < pos.x || y < pos.y ||
		x > max.x || y > max.y) {
		return false;
	}
	return true;
}

bool Point::in(const Rect& area) const {
	return in(area.pos, area.size);
}

bool Point::in(const Point& center, double radius) const {
	Point diff = absDiff(center);
	diff = diff*diff;
	return sqrt(diff.x + diff.y) <= radius;
}


Rect::Rect(const Point& newPos, const Point& newSize) {
    pos = newPos;
    size = newSize;
}

Rect::Rect( int x, int y, int w, int h ) {
    pos.x = x;
    pos.y = y;
    size.x = w;
    size.y = h;
}

Rect::Rect(const Rect& rhs) {
	pos = rhs.pos;
	size = rhs.size;
}

Rect& Rect::operator=(const Rect& rhs) {
	pos = rhs.pos;
	size = rhs.size;
	return *this;
}

bool Rect::contains(const Point& pos) const {
	return pos.in(pos, size);
}

void Rect::iterate(std::function<void(const Point&)>& action, int step) {
	Point last = pos + size, current;

	for (current = pos; current.x < last.x && current.y < last.y; current.iterate(last.x, pos.x, step)) {
		action(current);
	}
}

bool Rect::iterate(std::function<bool(const Point&)>& action, bool defaultVal, int step) {
	bool retval = defaultVal;
	Point last = pos + size, current;

	for (current = pos; current.x < last.x && current.y < last.y; current.iterate(last.x, pos.x, step)) {
		if (action(current) != defaultVal) {
			retval = !retval;
			break;
		}
	}
	return retval;
}
