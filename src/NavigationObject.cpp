#include "NavigationObject.h"

NavigationObject::NavigationObject()
= default;

NavigationObject::~NavigationObject()
= default;

b2Vec2 NavigationObject::GetGridPosition() const
{
	return m_gridPosition;
}

void NavigationObject::SetGridPosition(const float col, const float row)
{
	m_gridPosition = b2Vec2(col, row);
}
