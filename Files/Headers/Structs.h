#pragma once

#include <vector>

//Hier sind zwei structs, die in dem Spiel oft vorkommen. Einmal vec2d, ein Vektor, der die Position und Geschwindigkeit speichrt.
//Rect beinhaltet die Dinge für ein Rechteck
struct vec2d {
	float x;
	float y;
};

struct rect {
	float x;
	float y;
	float w;
	float h;
	bool activated;
};