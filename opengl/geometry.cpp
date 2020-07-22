#include "geometry.h"
#include <cmath>
#define PI 3.1415926f
void drawCircle(int radius, int slices)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < slices; i++)
	{
		glVertex2f(radius * cos(2 * PI * i / slices), radius * sin(2 * PI * i / slices));   //¶¨Òå¶¥µã
	}
	glEnd();
}
