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
