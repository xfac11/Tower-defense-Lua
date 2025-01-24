#include"MyEventReceiver.h"

// This is the one method that we have to implement
bool MyEventReceiver::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch (event.MouseInput.Event)
		{
		case irr::EMIE_LMOUSE_PRESSED_DOWN:
			mouseState.leftButtonDown = true;
			break;

		case irr::EMIE_LMOUSE_LEFT_UP:
			mouseState.leftButtonDown = false;
			break;

		case irr::EMIE_RMOUSE_PRESSED_DOWN:
			mouseState.rightButtonDown = true;
			break;

		case irr::EMIE_RMOUSE_LEFT_UP:
			mouseState.rightButtonDown = false;
			break;

		case irr::EMIE_MOUSE_MOVED:
			mouseState.position.X = event.MouseInput.X;
			mouseState.position.Y = event.MouseInput.Y;
			break;

		default:
			break;
		}
	}
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

const SMouseState& MyEventReceiver::getMouseState() const
{
	return mouseState;
}

// This is used to check whether a key is being held down

bool MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

MyEventReceiver::MyEventReceiver()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
	
	memset(&mouseState, 0, sizeof(SMouseState));
}