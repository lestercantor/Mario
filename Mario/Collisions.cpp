#include "Collisions.h"
#include "Character.h"

// Initialise the instance to null
Collisions* Collisions::mInstance = NULL;

Collisions::Collisions() {

}

Collisions::~Collisions() {
	mInstance = NULL;
}

Collisions* Collisions::Instance() {
	if (!mInstance) {
		mInstance = new Collisions;
	}
	return mInstance;
}

bool Collisions::Circle(Circle2D circle1, Circle2D circle2) {
	Vector2D vec = Vector2D((circle1.x - circle2.x),
		(circle1.y - circle2.y));

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	double combinedDistance = (circle1.radius1 + circle2.radius2);

	return distance < combinedDistance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2) {
	if (rect1.x + (rect1.width / 2) > rect2.x &&
		rect1.x + (rect1.width / 2) < rect2.x + rect2.width &&
		rect1.y + (rect1.height / 2) > rect2.y &&
		rect1.y + (rect1.height / 2) < rect2.y + rect2.height) {
		return true;
	}
	return false;
}
