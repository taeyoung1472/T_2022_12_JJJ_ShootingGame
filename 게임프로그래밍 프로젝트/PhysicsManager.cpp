#include "pch.h"
#include "PhysicsManager.h"
#include "Collider.h"
#include "GameObject.h"

void PhysicsManager::Update()
{
	CheckCollision();
}

void PhysicsManager::CheckCollision()
{
	vector<pair<int, int>> colledPair;

	for (int i = 0; i < m_controllingColliderList.size(); i++)
	{
		for (int j = 0; j < m_controllingColliderList.size(); j++)
		{
			if (i == j) continue;

			Vector2 posOne = m_controllingColliderList[i]->GetPos();
			Vector2 sizeOne = m_controllingColliderList[i]->GetSize();
			RECT rtOne;
			rtOne.left = posOne.x - sizeOne.x / 2; rtOne.top = posOne.y - sizeOne.y / 2; rtOne.right = posOne.x + sizeOne.x / 2;  rtOne.bottom = posOne.y + sizeOne.y / 2;

			Vector2 posTwo = m_controllingColliderList[j]->GetPos();
			Vector2 sizeTwo = m_controllingColliderList[j]->GetSize();
			RECT rtTwo;
			rtTwo.left = posTwo.x - sizeTwo.x / 2; rtTwo.top = posTwo.y - sizeTwo.y / 2; rtTwo.right = posTwo.x + sizeTwo.x / 2;  rtTwo.bottom = posTwo.y + sizeTwo.y / 2;

			RECT intersectRect;

			if (IntersectRect(&intersectRect, &rtOne, &rtTwo)) {
				if (find(colledPair.begin(), colledPair.end(), make_pair(i, j)) == colledPair.end())
				{
					m_controllingColliderList[i]->GetGameObject()->CollisionEnter(m_controllingColliderList[j]);
					m_controllingColliderList[j]->GetGameObject()->CollisionEnter(m_controllingColliderList[i]);
					colledPair.push_back(make_pair(i, j));
					colledPair.push_back(make_pair(j, i));
				}
			}
		}
	}
}