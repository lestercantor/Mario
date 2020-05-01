#pragma once

struct Vector2D {
	float x;
	float y;

	Vector2D() {
		x = 0.0f;
		y = 0.0f;
	}
	Vector2D(float initialX, float initailY)
	{
		x = initialX;
		y = initailY;
	}
};

struct Rect2D {
	float x;
	float y;
	float width;
	float height;

	Rect2D() {
		x = 0.0f;
		y = 0.0f;
		height = 0.0f;
		width = 0.0f;
	}
	Rect2D(float iX, float iY, float iWidth, float iHeight) {
		x = iX;
		y = iY;
		width = iWidth;
		height = iHeight;
	}
};

struct Circle2D {
	float x;
	float y;
	float radius1;
	float radius2;

	Circle2D() {
		x = 0.0f;
		y = 0.0f;
		radius1 = 0.0f;
		radius2 = 0.0f;
	}

	Circle2D(float iX, float iY, float iRadius1, float iRadius2) {
		x = iX;
		y = iY;
		radius1 = iRadius1;
		radius2 = iRadius2;
	}
};

enum SCREENS {
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING {
	FACING_LEFT = 0,
	FACING_RIGHT
};