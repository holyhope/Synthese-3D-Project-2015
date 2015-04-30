#include <cstdlib>
#include <ctime>

void initTools() {
	srand(time(NULL));
}

float randomFloat(float a, float b) {
	float random = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

float randomColorCoeff(float coeff) {
	return randomFloat(0, 1) * coeff;
}

float randomColor() {
	return randomColorCoeff(1);
}
