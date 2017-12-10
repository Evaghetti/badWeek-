#include "Widget.h"

Widget::Widget(const sf::Vector2f & position) : position(position) {
	usado = false;
}

void Widget::update() {
	if (usado)
		usado = false;
}