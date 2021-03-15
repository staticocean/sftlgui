
#ifndef __ISVG__
#define __ISVG__

//----------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <math.h>

#define NANOSVG_ALL_COLOR_KEYWORDS	// Include full list of color keywords.
#define NANOSVG_IMPLEMENTATION		// Expands implementation
#include "nanosvg.h"

//----------------------------------------------------------------\

NSVGimage* g_image = NULL;

static unsigned char bgColor[4] = {205,202,200,255};
static unsigned char lineColor[4] = {0,160,192,255};

static float distPtSeg(float x, float y, float px, float py, float qx, float qy)
{
	float pqx, pqy, dx, dy, d, t;
	pqx = qx-px;
	pqy = qy-py;
	dx = x-px;
	dy = y-py;
	d = pqx*pqx + pqy*pqy;
	t = pqx*dx + pqy*dy;
	if (d > 0) t /= d;
	if (t < 0) t = 0;
	else if (t > 1) t = 1;
	dx = px + t*pqx - x;
	dy = py + t*pqy - y;
	return dx*dx + dy*dy;
}

static void cubicBez(float x1, float y1, float x2, float y2,
					 float x3, float y3, float x4, float y4,
					 float tol, int level)
{
	float x12,y12,x23,y23,x34,y34,x123,y123,x234,y234,x1234,y1234;
	float d;
	
	if (level > 12) return;

	x12 = (x1+x2)*0.5f;
	y12 = (y1+y2)*0.5f;
	x23 = (x2+x3)*0.5f;
	y23 = (y2+y3)*0.5f;
	x34 = (x3+x4)*0.5f;
	y34 = (y3+y4)*0.5f;
	x123 = (x12+x23)*0.5f;
	y123 = (y12+y23)*0.5f;
	x234 = (x23+x34)*0.5f;
	y234 = (y23+y34)*0.5f;
	x1234 = (x123+x234)*0.5f;
	y1234 = (y123+y234)*0.5f;

	d = distPtSeg(x1234, y1234, x1,y1, x4,y4);
	if (d > tol*tol) {
		cubicBez(x1,y1, x12,y12, x123,y123, x1234,y1234, tol, level+1); 
		cubicBez(x1234,y1234, x234,y234, x34,y34, x4,y4, tol, level+1); 
	} else {
		glVertex2f(x4, y4);
	}
}

void drawPath(float* pts, int npts, char closed, float tol)
{
	int i;
	glBegin(GL_LINE_STRIP);
	glColor4ubv(lineColor);
	glVertex2f(pts[0], pts[1]);
	for (i = 0; i < npts-1; i += 3) {
		float* p = &pts[i*2];
		cubicBez(p[0],p[1], p[2],p[3], p[4],p[5], p[6],p[7], tol, 0);
	}
	if (closed) {
		glVertex2f(pts[0], pts[1]);
	}
	glEnd();
}

void drawframe(GLFWwindow* window)
{
	int width = 0, height = 0;
	float view[4], cx, cy, hw, hh, aspect, px;
	NSVGshape* shape;
	NSVGpath* path;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glClearColor(220.0f/255.0f, 220.0f/255.0f, 220.0f/255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Fit view to bounds
	cx = g_image->width*0.5f;
	cy = g_image->height*0.5f;
	hw = g_image->width*0.5f;
	hh = g_image->height*0.5f;

	if (width/hw < height/hh) {
		aspect = (float)height / (float)width;
		view[0] = cx - hw * 1.2f;
		view[2] = cx + hw * 1.2f;
		view[1] = cy - hw * 1.2f * aspect;
		view[3] = cy + hw * 1.2f * aspect;
	} else {
		aspect = (float)width / (float)height;
		view[0] = cx - hh * 1.2f * aspect;
		view[2] = cx + hh * 1.2f * aspect;
		view[1] = cy - hh * 1.2f;
		view[3] = cy + hh * 1.2f;
	}
	// Size of one pixel.
	px = (view[2] - view[1]) / (float)width;

	glOrtho(view[0], view[2], view[3], view[1], -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glColor4ub(255,255,255,255);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	// Draw bounds
	glColor4ub(0,0,0,64);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0, 0);
	glVertex2f(g_image->width, 0);
	glVertex2f(g_image->width, g_image->height);
	glVertex2f(0, g_image->height);
	glEnd();

	for (shape = g_image->shapes; shape != NULL; shape = shape->next) {
		for (path = shape->paths; path != NULL; path = path->next) {
			drawPath(path->pts, path->npts, path->closed, px * 1.5f);
			drawControlPts(path->pts, path->npts);
		}
	}

	glfwSwapBuffers(window);
}

//----------------------------------------------------------------

#endif /* __ISVG__ */