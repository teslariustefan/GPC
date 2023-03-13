#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "glut.h"

#define dim 300

unsigned char prevKey;

void Display1() {
	double xmax, ymax, xmin, ymin;
	double a = 1, b = 2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;

	xmax = a - b - 1;
	xmin = a + b + 1;
	ymax = ymin = 0;
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = a + b * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		x2 = a - b * cos(t);
		xmax = (xmax < x2) ? x2 : xmax;
		xmin = (xmin > x2) ? x2 : xmin;

		y1 = a * tan(t) + b * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;

		y2 = a * tan(t) - b * sin(t);
		ymax = (ymax < y2) ? y2 : ymax;
		ymin = (ymin > y2) ? y2 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x2, y2);
	}
	glEnd();
}

// The graph of the function 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display2() {
	double pi = 4 * atan(1.0);
	double xmax = 8 * pi;
	double ymax = exp(1.1);
	double ratia = 0.05;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x < xmax; x += ratia) {
		double x1, y1;
		x1 = x / xmax;
		y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();
}

void Display3() {
	// Set up initial values
	const double X_MAX = 27.0;
	const double STEP_SIZE = 0.05;
	double y_max = -INFINITY;
	double y_min = INFINITY;
	double y, x;
	// Calculate y_max and y_min
	for (x = 0; x < X_MAX; x += STEP_SIZE) {
		if (x == 0) {
			y = 1;
		}
		else {
			double dist = x - round(x);
			dist = (dist < 0) ? -dist : dist; // Use ternary operator to simplify code
			y = dist / x;
		}
		y_max = fmax(y, y_max);
		y_min = fmin(y, y_min);
	}

	// Set y_max to the larger of the absolute values of y_max and y_min
	y_max = fabs(y_max) > fabs(y_min) ? fabs(y_max) : fabs(y_min);

	// Set up drawing color
	glColor3f(1.0f, 0.1f, 0.1f);

	// Draw the function
	glBegin(GL_LINE_STRIP);
	for (x = 0; x < X_MAX; x += STEP_SIZE) {
		if (x == 0) {
			y = 1;
		}
		else {
			double dist = x - round(x);
			dist = (dist < 0) ? -dist : dist; // Use ternary operator to simplify code
			y = dist / x;
		}

		// Normalize x and y coordinates
		double x_norm = x / X_MAX;
		double y_norm = y / y_max - (STEP_SIZE / 2.0f);

		// Draw the vertex
		glVertex2f(x_norm, y_norm);
	}
	glEnd();
}

void Display4() {
	// Set up initial values
	const double A = 0.3;
	const double B = 0.2;
	const double PI = 3.14159;
	const double INCREMENT = 0.05;
	double t = -PI;
	// Set up drawing color
	glColor3f(1.0f, 0.1f, 0.1f);

	// Draw the Pascal's snail
	glBegin(GL_LINE_STRIP);
	while (t < PI) {
		double x = (A * cos(t) + B) * cos(t);
		double y = (A * cos(t) + B) * sin(t);
		glVertex2f(2.0f * x / 1.1f, 2.0f * y / 1.1f); // Normalize coordinates and divide by 1.1
		t += INCREMENT;
	}
	glEnd();
}

void Display5() {
	// Set up initial values
	const double PI = 3.14159265358979323846;
	const double A = 0.2;
	const double STEP_SIZE = 0.005;
	// Draw the main curve
	double right_x = 0, right_y = 0, left_x = 0, left_y = 0;
	bool first = true;
	glColor3f(1.0f, 1.0f, 1.0f); // Set drawing color to white
	glBegin(GL_POINTS);
	for (double t = -PI / 2.0f + STEP_SIZE; t < -PI / 6.0f; t += STEP_SIZE) {
		if (t == -PI / 6.0f || t == PI / 6.0f) {
			continue;
		}
		double x = A / (4.0f * pow(cos(t), 2.0f) - 3.0f);
		double y = A * tan(t) / (4.0f * pow(cos(t), 2.0f) - 3.0f);
		if (x <= 0.0f && x >= -1.0f && y <= 1.0f && y >= 0.0f) {
			if (first) {
				right_x = x;
				right_y = y;
				first = false;
			}
			left_x = x;
			left_y = y;
			glVertex2f(x, y);
		}
	}

	// Draw the horizontal line and fill the shape
	glColor3f(0.0f, 0.0f, 1.0f); // Set drawing color to blue
	glBegin(GL_LINE_STRIP);
	glVertex2f(left_x, 0.9999f);
	glVertex2f(right_x, 1.0f);
	for (double t = -PI / 2.0f + STEP_SIZE; t < -PI / 6.0f; t += STEP_SIZE) {
		if (t == -PI / 6.0f || t == PI / 6.0f) {
			continue;
		}
		double x = A / (4.0f * pow(cos(t), 2.0f) - 3.0f);
		double y = A * tan(t) / (4.0f * pow(cos(t), 2.0f) - 3.0f);
		if (x <= 0.0f && x >= -1.0f && y <= 1.0f && y >= 0.0f) {
			glVertex2f(x, y);
		}
	}
	glVertex2f(left_x, left_y);
	glVertex2f(left_x, 0.9999f);
	glEnd();

	// Draw the triangles
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.1f, 0.1f); // Set drawing color to red
	int counter = 0;
	double last_x, last_y;
	for (double t = -PI / 2.0f + STEP_SIZE; t < -PI / 6.0f; t += STEP_SIZE) {
		if (t == -PI / 6.0f || t == PI / 6.0f) {
			continue;
		}
		double x = A / (4.0f * pow(cos(t), 2.0f) - 3.0f);
		double y = A * tan(t) / (4.0f * pow(cos(t), 2.0f) - 3.0f);
		if (x <= 0.0f && x >= -1.0f && y <= 1.0f && y >= 0.0f) {
			counter++;
			if (counter % 4 == 2) {
				if (y < 0.25f) {
					last_x = x;
					last_y = y;
					continue;
				}
				glVertex2f(last_x, last_y);
				glVertex2f(x, y);
				glVertex2f(left_x, 0.9999f);
			}
			else {
				last_x = x;
				last_y = y;
			}
		}
	}
	glEnd();
}

void Display6() {
	// Set up initial values
	const double A = 0.1;
	const double B = 0.2;
	const double PI = 3.14159265358979323846;
	const double STEP_SIZE = 0.05;
	double x_max = A * PI + 1.0f;
	double y_max = 0.0f;
	double x_min = 0.0f;
	double y_min = 0.0f;
	// Draw the main curve and update max/min values
	glColor3f(1.0f, 0.1f, 0.1f); // Set drawing color to red
	glBegin(GL_LINE_STRIP);
	for (double t = -4.0f * PI; t < 4.0f * PI; t += STEP_SIZE) {
		double x = A * t - B * sin(t);
		double y = A - B * cos(t);
		glVertex2f(x, y);

		// Update max/min values
		x_max = fmax(x_max, x);
		x_min = fmin(x_min, x);
		y_max = fmax(y_max, y);
		y_min = fmin(y_min, y);
	}
	glEnd();

	// Calculate absolute max/min values
	double abs_x_max = fmax(fabs(x_max), fabs(x_min));
	double abs_y_max = fmax(fabs(y_max), fabs(y_min));

	// Draw the secondary curve
	glBegin(GL_LINE_STRIP);
	for (double t = -3.0f * PI; t < 3.0f * PI; t += STEP_SIZE) {
		double x = A * t - B * sin(t);
		double y = A - B * cos(t);
		glVertex2f(x, y);
	}
	glEnd();
}


void Display7() {
	// Set up initial values
	const double RADIUS_BIG = 0.1;
	const double RADIUS_SMALL = 0.3;
	const double PI = 3.14159265358979323846;
	const double STEP_SIZE = 0.05;
	// Draw the curve
	glColor3f(1.0f, 0.1f, 0.1f); // Set drawing color to red
	glBegin(GL_LINE_STRIP);
	for (double t = -STEP_SIZE; t < 2.0f * PI + STEP_SIZE; t += STEP_SIZE) {
		double x = (RADIUS_BIG + RADIUS_SMALL) * cos(RADIUS_SMALL / RADIUS_BIG * t) - RADIUS_SMALL * cos(t + RADIUS_SMALL / RADIUS_BIG * t);
		double y = (RADIUS_BIG + RADIUS_SMALL) * sin(RADIUS_SMALL / RADIUS_BIG * t) - RADIUS_SMALL * sin(t + RADIUS_SMALL / RADIUS_BIG * t);
		glVertex2f(x, y);
	}
	glEnd();
}


void Display8() {
	// Set up initial values
	const double RADIUS_BIG = 0.1;
	const double RADIUS_SMALL = 0.3;
	const double PI = 3.14159265358979323846;
	const double STEP_SIZE = 0.05;
	// Draw the first part of the curve
	glColor3f(1.0f, 0.1f, 0.1f); // Set drawing color to red
	glBegin(GL_LINE_STRIP);
	for (double t = -STEP_SIZE; t < 2.0f * PI + STEP_SIZE; t += STEP_SIZE) {
		double x = (RADIUS_BIG - RADIUS_SMALL) * cos(RADIUS_SMALL / RADIUS_BIG * t) - RADIUS_SMALL * cos(t - RADIUS_SMALL / RADIUS_BIG * t);
		double y = (RADIUS_BIG - RADIUS_SMALL) * sin(RADIUS_SMALL / RADIUS_BIG * t) - RADIUS_SMALL * sin(t - RADIUS_SMALL / RADIUS_BIG * t);
		glVertex2f(x, y);
	}
	glEnd();

	// Draw the second part of the curve
	glBegin(GL_LINE_STRIP);
	for (double t = 0.0f; t < 2.0f * PI; t += STEP_SIZE) {
		double x = (RADIUS_BIG - RADIUS_SMALL) * cos(RADIUS_SMALL / RADIUS_BIG * t) - RADIUS_SMALL * cos(t - RADIUS_SMALL / RADIUS_BIG * t);
		double y = (RADIUS_BIG - RADIUS_SMALL) * sin(RADIUS_SMALL / RADIUS_BIG * t) - RADIUS_SMALL * sin(t - RADIUS_SMALL / RADIUS_BIG * t);
		glVertex2f(x, y);
	}
	glEnd();

}

void Display9() {
	// Set up initial values
	const double A = 0.4;
	const double PI = 3.14159265358979323846;
	const double STEP_SIZE = 0.01;
	// Draw the upper part of the curve
	glColor3f(1.0f, 0.1f, 0.1f); // Set drawing color to red
	glBegin(GL_LINE_STRIP);
	for (double t = -PI / 4.0f; t < PI / 4.0f; t += STEP_SIZE) {
		double r = A * sqrt(2.0f * cos(2.0f * t));
		double x = r * cos(t);
		double y = r * sin(t);
		glVertex2f(x, y);
	}
	glEnd();

	// Draw the lower part of the curve
	glBegin(GL_LINE_STRIP);
	for (double t = -PI / 4.0f; t < PI / 4.0f; t += STEP_SIZE) {
		double r = -A * sqrt(2.0f * cos(2.0f * t));
		double x = r * cos(t);
		double y = r * sin(t);
		glVertex2f(x, y);
	}
	glEnd();

}

void Display0() {
	// Defineste si initializeaza constantele necesare
	const double a = 0.02;
	const double pi = 3.14159265358979323846;
	const double ratia = 0.01;
	// Seteaza culoarea curbei
	glColor3f(1, 0.1, 0.1);

	// Incepe desenarea curbei ca o linie continua
	glBegin(GL_LINE_STRIP);

	// Calculeaza si deseneaza punctele curbei
	for (double t = -ratia; t < 4 * pi; t += ratia) {
		// Calculeaza raza curbei si coordonatele punctului curent
		const double r = a * exp(1 + t);
		const double x = r * cos(t);
		const double y = r * sin(t);

		// Adauga punctul curent la curba
		glVertex2d(x, y);
	}

	// Inchide desenarea curbei
	glEnd();

}


void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	//   glPointSize(4);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		Display1();
		break;
	case '2':
		Display2();
		break;
	case '3':
		Display3();
		break;
	case '4':
		Display4();
		break;
	case '5':
		Display5();
		break;
	case '6':
		Display6();
		break;
	case '7':
		Display7();
		break;
	case '8':
		Display8();
		break;
	case '9':
		Display9();
		break;
	case '0':
		Display0();
		break;
	default:
		break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
