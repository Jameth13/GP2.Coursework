#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class CameraComponent : public Component
{
public:
	CameraComponent();
	~CameraComponent();

	void Start();
	void Update();

	void Init(float fov, float aspect, float nearClip, float farClip);
	glm::mat4 GetViewProjection();


private:
	glm::mat4 projection;
};
