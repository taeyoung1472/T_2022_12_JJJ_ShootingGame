#pragma once
#include <algorithm>

class Collider;

class PhysicsManager
{
public:
	void Update();
	SINGLE(PhysicsManager);

public:
	void RegistCollision(shared_ptr<Collider> col) 
	{
		if (find(m_controllingColliderList.begin(), m_controllingColliderList.end(), col) == m_controllingColliderList.end())
		{
			m_controllingColliderList.push_back(col);
		}
	}
	void RemoveCollision(shared_ptr<Collider> col)
	{
		auto findIt = find(m_controllingColliderList.begin(), m_controllingColliderList.end(), col);
		if (findIt != m_controllingColliderList.end()) {
			m_controllingColliderList.erase(findIt);
		}
	}

private:
	void CheckCollision();

private:
	vector<shared_ptr<Collider>> m_controllingColliderList;
};

