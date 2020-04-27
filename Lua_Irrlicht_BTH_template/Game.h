#pragma once
#pragma comment(lib, "Irrlicht.lib")
#ifdef _DEBUG
#pragma comment(lib, "LuaLibd.lib")
#else
#pragma comment(lib, "Lualib.lib")
#endif
#include <fstream>
#include <lua.hpp>
#include <Windows.h>
#include <iostream>
#include <thread>
#include "lua.hpp"
#include <vector>
#include <string>
#include <irrlicht.h>
#include"Gameobject.h"
using namespace irr;
class MyEventReceiver : public irr::IEventReceiver
{
public:
	struct SMouseState
	{
		core::position2di position;
		bool leftButtonDown;
		bool rightButtonDown;
		SMouseState() : leftButtonDown(false), rightButtonDown(false)
		{

		}
	} MouseState;

	// This is the one method that we have to implement
	virtual bool OnEvent(const irr::SEvent& event)
	{
		if (event.EventType == EET_MOUSE_INPUT_EVENT)
		{
			switch (event.MouseInput.Event)
			{
			case EMIE_LMOUSE_PRESSED_DOWN:
				MouseState.leftButtonDown = true;
				break;

			case EMIE_LMOUSE_LEFT_UP:
				MouseState.leftButtonDown = false;
				break;
				
			case EMIE_RMOUSE_PRESSED_DOWN:
				MouseState.rightButtonDown = true;
				break;

			case EMIE_RMOUSE_LEFT_UP:
				MouseState.rightButtonDown = false;
				break;

			case EMIE_MOUSE_MOVED:
				MouseState.position.X = event.MouseInput.X;
				MouseState.position.Y = event.MouseInput.Y;
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

	const SMouseState& getMouseState() const
	{
		return MouseState;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}
	
	MyEventReceiver()
	{
		for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    
};
struct Stage
{
	Stage()
	{
		for (int i = 0; i < 1024; i++)
		{
			grid[i] = 0;
		}
	}
	int height;
	int width;
	int grid[1024]; // 32 x 32
};
struct LuaDraw
{
	std::vector<irr::scene::IMeshSceneNode*> sceneObjects;
	std::vector<irr::gui::IGUIButton*> sceneButtons;
	std::vector<irr::gui::IGUIStaticText*> sceneText;
};
class Game
{
public:
	Game();
	~Game();
	void run();
	static int C_addToDraw(lua_State* L);
	static int C_removeFromDraw(lua_State* L);
	static int C_setVisible(lua_State* L);
	static int C_loadStage(lua_State* L);
	static int C_saveStage(lua_State* L);
	static int C_setPosition(lua_State* L);
	static int C_setScale(lua_State* L);
	static int C_setRotation(lua_State* L);
	static int C_addCube(lua_State* L);
	static int C_isKeyPressed(lua_State* L);
	static int C_setColor(lua_State* L);
	static int C_getMousePos3D(lua_State* L);
	static int C_setCamPos(lua_State* L);
	static int C_setUIPos(lua_State* L);
	static int C_isButtonPressed(lua_State* L);
	static int C_getDeltaTime(lua_State* L);
	lua_State* L;
private:
	static MyEventReceiver eventRec;
	static irr::video::IVideoDriver* driver;
	static irr::scene::ISceneManager* smgr;
	static irr::gui::IGUIEnvironment* guienv;
	static irr::IrrlichtDevice* device;
	static irr::scene::ICameraSceneNode* camera;
	static float deltaTime;
	void render();//C++
	void initialize();
	void update();//LUA
	void initLua();
	
};
