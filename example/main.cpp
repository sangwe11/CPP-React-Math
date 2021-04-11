#include "vec3.h"

int main()
{
	react::vec3f a(1.0f, 1.0f, 1.0f);
	react::vec3f b(0.0f, 1.0f, 0.0f);

	react::vec3f c = react::vec3f::cross(a, b);
	react::vec3f::type d = a.dot(b);

	react::vec3f up = react::vec3f::UP;
	react::vec3f right = react::vec3f::RIGHT;

	react::vec3f::type f = react::vec3f::angle(up, right);

	std::cout << "A: (" << a << ")" << std::endl;
	std::cout << "B: (" << b << ")" << std::endl;
	std::cout << "cross(A, B) = (" << c << ")" << std::endl;
	std::cout << "dot(A, B) = " << d << std::endl;
	std::cout << "up: (" << up << ")" << std::endl;
	std::cout << "right: (" << right << ")" << std::endl;
	std::cout << "angle(up, right) = " << f << " radians" << std::endl;

	return 0;
}