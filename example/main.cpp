#include "React-Math.h"

class Transform
{
public:
	Transform() {}
	Transform(const react::vec3f& position) : m_position(position) {}
	Transform(const react::vec3f& position, const react::vec3f& eulers) : m_position(position), m_orientation(eulers) {}
	Transform(const react::vec3f& position, const react::quatf& orientation) : m_position(position), m_orientation(orientation) {}

	const react::vec3f& getPosition() const { return m_position; }
	const react::quatf& getOrientation() const { return m_orientation; }
	const react::mat3f getBasis() const { return m_orientation.toMat3(); }

	void setPosition(const react::vec3f& position) { m_position = position; }	
	void setOrientation(const react::quatf& orientation) { m_orientation = orientation; }

	void rotateLocal(const react::vec3f& axis, const float& angle) { m_orientation = m_orientation * react::quatf::fromAxisAngle(axis, angle); }
	void rotateGlobal(const react::vec3f& axis, const float& angle) { m_orientation = react::quatf::fromAxisAngle(axis, angle) * m_orientation; }

	const react::mat4f modelMatrix() const
	{
		react::mat4f translation = react::mat4f::IDENTITY;
		translation.at(0, 3) = m_position.x();
		translation.at(1, 3) = m_position.y();
		translation.at(2, 3) = m_position.z();

		react::mat4f rotation = react::mat4f(m_orientation.toMat3());

		return translation * rotation;
	}

	inline const react::mat4f inverseModelMatrix() const
	{
		return modelMatrix().inverse();
	}
	

private:
	react::vec3f m_position = react::vec3f::ZERO;
	react::quatf m_orientation = react::quatf::IDENTITY;
};

int main()
{
	Transform t(react::vec3f::ZERO, react::vec3f::ZERO);

	t.setPosition(react::vec3f(-10.0f, 5.0f, 0.0f));
	t.rotateLocal(react::vec3f::UP, react::math::radians(90.0f));	
	t.rotateGlobal(react::vec3f::RIGHT, react::math::radians(-45.0f));

	react::vec3f pos = t.getPosition();
	react::vec3f eulers = t.getOrientation().toEulers();
	react::mat4f model = t.modelMatrix();
	react::mat4f inv_model = t.inverseModelMatrix();

	std::cout << "Position: " << pos << std::endl;
	std::cout << "Eulers: " << react::math::degrees(eulers) << std::endl;
	std::cout << "Model: " << std::endl << model << std::endl;
	std::cout << "Inverse Model: " << std::endl << inv_model << std::endl;


	return 0;
}