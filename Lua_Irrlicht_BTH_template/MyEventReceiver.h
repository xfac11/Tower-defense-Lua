#pragma once
#include<irrlicht.h>
struct SMouseState
{
	irr::core::position2di position;
	bool leftButtonDown;
	bool rightButtonDown;
	SMouseState()
	{
		leftButtonDown = false;
		rightButtonDown = false;
	};
};
class MyEventReceiver : public irr::IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const irr::SEvent& event);

	const SMouseState& getMouseState() const;

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

	MyEventReceiver();

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];

	SMouseState mouseState;
};