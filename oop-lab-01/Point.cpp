#include <windows.h>
#include <cmath>
#include "Point.h"
#include "Image.h"
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

extern HDC hdc;

Location::Location(int x, int y) : x(x), y(y) { };

Location::~Location(void) { };

int Location::getX(void) { return x; };	

int Location::getY(void) { return y; };

Point::Point(int initX, int initY) : Location(initX, initY) { visible = false; }

Point::~Point(void) { }

void Point::show(void) {
	visible = true;
	SetPixel(hdc, x, y, RGB(255, 0, 0));
	SetPixel(hdc, x + 1, y, RGB(255, 0, 0));
	SetPixel(hdc, x, y + 1, RGB(255, 0, 0));
	SetPixel(hdc, x + 1, y + 1, RGB(255, 0, 0));
}

void Point::hide(void) {
	visible = false;
	SetPixel(hdc, x, y, RGB(0, 0, 255));
	SetPixel(hdc, x + 1, y, RGB(0, 0, 255));
	SetPixel(hdc, x, y + 1, RGB(0, 0, 255));
	SetPixel(hdc, x + 1, y + 1, RGB(0, 0, 255));
}

bool Point::isVisible(void) { return visible; };

void Point::moveTo(int newX, int newY) {
	hide();
	x = newX;
	y = newY;
	show();
};

void Point::drug(int shift) {
	if (KEY_DOWN(VK_DOWN))
		moveTo(x, y + shift);
	if (KEY_DOWN(VK_UP))
		moveTo(x, y - shift);
	if (KEY_DOWN(VK_RIGHT))
		moveTo(x + shift, y);
	if (KEY_DOWN(VK_LEFT))
		moveTo(x - shift, y);
}

Glass::Glass(int initX, int initY, int initHeight, int initWidth): Point(initX, initY) {
	height = initHeight;
	width = initWidth;
}

Glass::~Glass(void) { };

void Glass::show(void) {
	visible = true;
	Image::glassShow(hdc, x, y);
}

void Glass::hide(void) {
	visible = false;
	Image::glassHide(hdc, x, y);
}

void Glass::moveTo(int newX, int newY) {
	hide();
	x = newX;
	y = newY;
	show();
}

void Glass::drug(int shift) {
	if (KEY_DOWN(VK_DOWN))
		moveTo(x, y + shift);
	if (KEY_DOWN(VK_UP))
		moveTo(x, y - shift);
	if (KEY_DOWN(VK_RIGHT))
		moveTo(x + shift, y);
	if (KEY_DOWN(VK_LEFT))
		moveTo(x - shift, y);
}