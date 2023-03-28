#pragma once
#ifndef __LEVEL_SELECTION_OBJECT_H__
#define __LEVEL_SELECTION_OBJECT_H__

#include "Obstacle.h"
#include <string>

const std::string startText = "../Assets/textures/SelectScreen/StartText.png";
const std::string startTextName = "startLabel";

class LevelSelectionObject : public Obstacle 
{
public:
	// Constructors
	LevelSelectionObject();
	LevelSelectionObject(const char* texture, const char* fileName);

	// Destructor
	~LevelSelectionObject();

	// Lifecycle functions
	void Draw() override;
	void Update() override;
	void Clean() override;

	void SetLabel(bool value);
	bool GetLabel();
private:
	bool m_isLabelEnabled;
};

#endif //!__LEVEL_SELECTION_OBJECT_H__