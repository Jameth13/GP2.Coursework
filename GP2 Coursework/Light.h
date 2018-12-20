#include "GameObject.h"

class Light : public GameObject
{
public:
	Light();
	~Light();

	void Awake();
	void Start();
	void Update();

private:
};
