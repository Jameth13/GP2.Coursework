#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionManager.h"


Collider::Collider(float radius)
{
	colMan = CollisionManager::GetInstance();
	sphere->Update(radius);
	colMan->Add(this);
}

Collider::~Collider()
{
	colMan->Remove(this);
}

void Collider::Start() {}

void Collider::Update()
{
	Transform* trans = gameObject->GetComponent<Transform>();
	sphere->Update(trans->GetPos());
}
