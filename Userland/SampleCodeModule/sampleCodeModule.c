
#include <bizcocho.h>

int main() {
	point_t topLeft = {0,0};
	point_t bottomRight = {24,79};
	sys_add_task(bizcocho, &topLeft, &bottomRight, 1, 0, NULL);
	return 0;
}
