#include "Manifold.h"
#include <Novice.h>
void DrawManifold(const Manifold& manifold) {
	Novice::DrawEllipse(
		int(manifold.contactPoint.x), int(manifold.contactPoint.y),
		5,
		5,
		0.0f,
		0x0000FFFF,
		kFillModeSolid
	);

	Novice::DrawLine(
		int(manifold.contactPoint.x), int(manifold.contactPoint.y),
		int(manifold.contactPoint.x + manifold.normal.x * 50.0f), int(manifold.contactPoint.y + manifold.normal.y * 50.0f),
		0x0000FFFF
	);

	Novice::ScreenPrintf(0, 0, "manifold.contactPoint : %.2f,%.2f\n", manifold.contactPoint.x,manifold.contactPoint.y);
	Novice::ScreenPrintf(0, 20, "manifold.normal : %.2f,%.2f", manifold.normal.x,manifold.normal.y);
}