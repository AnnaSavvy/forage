#pragma once
#include <functional>

struct Rect;

struct Point {
	int _x = 0;
	int _y = 0;

	Point();
	Point(int);
	Point(int, int);
	Point(const Point&);
	~Point();

	Point& set(int, int);
	Point& modAdd(int, int);
	Point& modSub(int, int);
	Point& modMul(int);
	Point& modDiv(int);
	Point& modInv();
	Point add(int, int) const;
	Point sub(int, int) const;
	Point mul(int) const;
	Point div(int) const;
	Point inv() const;
	Point absDiff(const Point&) const;

	Point& operator= (const Point&);
	Point& operator+= (const Point&);
	Point& operator-= (const Point&);
	Point operator+ (const Point&) const;
	Point operator- (const Point&) const;
	Point operator* (const Point&) const;
	Point operator* (int mod) const;
	Point operator* (double mod) const;
	Point operator/ (const Point&) const;
	Point operator/ (int mod) const;
	Point operator/ (double mod) const;
	Point operator% (int limit) const;
	bool operator== (const Point&) const;
	bool operator!= (const Point&) const;
	bool rectLessThan(const Point&) const; // it's not a strict weak ordering; handle with care
	bool rectMoreThan(const Point&) const;
	bool operator> (const Point&) const; // default lexicographical ordering; suitable for std containers
	bool operator< (const Point&) const;
	bool operator> (int) const;
	bool operator< (int) const;
	size_t operator() (const Point& k) const;

	int toRenderPriority() const;
	int toRenderPriority(const Point&) const;
	int toID(int) const;
	Point toIso() const;
	Point toMap() const;
	Point limit(int) const;
	void iterate(int max, int min = 0, int step = 1);
	void convertToIso();
	void convertToMap();
	bool in(const Point& pos, const Point& size) const; // rectangle
	bool in(const Rect& area) const; // rectangle
	bool in(const Point& center, double radius) const; // circle
};

struct Rect {
    Point _pos;
    Point _size;

	Rect() = default;
    Rect( const Point &, const Point & );
    Rect( int, int, int, int );
    Rect( const Rect & );
	~Rect() = default;
	Rect& operator= (const Rect&);
    Rect & modAdd( int x, int y );
	bool contains(const Point& pos) const;
	void iterate(std::function<void(const Point&)>& action, int step = 1);
	bool iterate(std::function<bool(const Point&)>& action, bool defaultVal, int step = 1);
};

struct cmpPointsStrict {
	bool operator()(const Point& a, const Point& b) const {
		if (a._x != b._x) return a._x < b._x;
		return a._y < b._y;
	}
};
