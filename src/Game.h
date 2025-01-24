#pragma once
#include <fstream>
#include <lua.hpp>
#include <Windows.h>
#include <iostream>
#include <thread>
#include "lua.hpp"
#include <vector>
#include <string>
#include <irrlicht.h>
#include <comdef.h>
#include"MyEventReceiver.h"
#include"WideText.h"
using namespace irr;
class Game
{
public:
	struct Stage
	{
		uint32_t height;
		uint32_t width;
		int grid[1024]; // 32 x 32
	};
	enum DrawType
	{
		MESH,
		BUTTON,
		TEXT,
		EDITBOX,
		IMAGE
	};
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
	static int C_setCamTarget(lua_State* L);
	static int C_setTexture(lua_State* L);
	static int C_setUIPos(lua_State* L);
	static int C_isButtonPressed(lua_State* L);
	static int C_getDeltaTime(lua_State* L);
	static int C_setText(lua_State* L);
	static int C_getText(lua_State* L);
	static int C_setFont(lua_State* L);
	lua_State* L;
private:
	static MyEventReceiver eventRec;
	static irr::video::IVideoDriver* driver;
	static irr::scene::ISceneManager* smgr;
	static irr::gui::IGUIEnvironment* guienv;
	static irr::IrrlichtDevice* device;
	static irr::scene::ICameraSceneNode* camera;
	const static irr::scene::IGeometryCreator* geomentryCreator;
	static float deltaTime;
	static gui::IGUIFont* font;

	const irr::video::SColor CLEARCOLOR = irr::video::SColor(255, 0, 0, 200);
	const irr::u8 ANTIALIAS = 4;
	const irr::video::E_DRIVER_TYPE DRIVERTYPE = irr::video::EDT_OPENGL;
	const core::dimension2d<u32> WINDOWSIZE = core::dimension2d<u32>(1280, 720);
	const irr::io::path CWD = irr::io::path("");
	const irr::io::path DEFAULTFONT = irr::io::path("Assets/Fonts/myfont.xml");
	const core::vector3df DEFAULTCAMERALOOKAT = core::vector3df(0, 0, 0);
	const core::vector3df DEFAULTCAMERAPOSITION = core::vector3df(0, 50, -1);

	void render();//C++
	void initIrrlicht();
	void update() const;//LUA
	void initLua();

};
