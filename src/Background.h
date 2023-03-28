#pragma once
#ifndef __BACKGROUND__
#define __BACKGROUND__

#include "DisplayObject.h"
#include <string>

class Background final : public DisplayObject
{
public:
	Background();
	Background(std::string imgFile, std::string key);
	~Background() override;

	// Life Cycle Methods
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	// setters
	void SetScale(float scale);
	
private:
	std::string m_key;
	float m_scale;
	
};

#endif /* defined (__BACKGROUND__) */
