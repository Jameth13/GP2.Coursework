#include "GameObject.h"

class ReindeerGirl : public GameObject
{
public:
	ReindeerGirl();
	~ReindeerGirl();
	
	void Start();
	void Update();

private:
	float counter;
};

