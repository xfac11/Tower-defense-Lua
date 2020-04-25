#include"Game.h"
irr::IrrlichtDevice* Game::device = nullptr;
irr::video::IVideoDriver* Game::driver = nullptr;
irr::scene::ISceneManager* Game::smgr = nullptr;
irr::gui::IGUIEnvironment* Game::guienv = nullptr;
irr::scene::ICameraSceneNode* Game::camera = nullptr;
MyEventReceiver Game::eventRec = MyEventReceiver();

Game::Game()
{
	L = luaL_newstate();
	luaL_openlibs(L);
	this->eventRec = MyEventReceiver();
}

Game::~Game()
{
	lua_close(L);
}

void Game::run()
{
	initialize();
	initLua();
	device->getCursorControl()->setVisible(true);

	while (device->run())
	{

		this->update();
		this->render();
		
	}
	device->drop();

}

int Game::C_addToDraw(lua_State* L)
{

	int type = (int)lua_tonumber(L,-2);
	lua_remove(L, -2);
	switch (type)
	{
	case 0:
		//mesh
		
		const char* model = lua_tostring(L, -1);
		lua_pop(L, 1);
		irr::scene::IMesh* mesh = smgr->getMesh(model);//change to model
		
		scene::IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
		node->setMaterialTexture(0, driver->getTexture("3DObjects/cube2.tga"));
		//node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		//scene::IMeshSceneNode* pi = (scene::IMeshSceneNode*)lua_newuserdata(L, sizeof(scene::IMeshSceneNode));
		lua_pushlightuserdata(L, node);
		
		break;
	}
	////Create meshnode with string parameter
	////put in array of pointers
	////return index of the place in the array

	//std::string meshFile = lua_tostring(L, -1);
	//irr::scene::IMesh* planeMesh = smgr->getMesh("3DObjects/planeGrass.obj");
	//if (!planeMesh)
	//{
	//	device->drop();
	//	return 1;
	//}
	//irr::scene::IMeshSceneNode* planeGrassNode = smgr->addMeshSceneNode(planeMesh);
	//lua_pushnumber(L, index);
	return 1;
}

int Game::C_removeFromDraw(lua_State* L)
{
	//remove it from array and delete it
	return 0;
}

int Game::C_setVisible(lua_State* L)
{

	bool arg = lua_toboolean(L, -1);
	scene::IMeshSceneNode* node = (scene::IMeshSceneNode*)lua_touserdata(L, -2);
	if(node != nullptr)
		node->setVisible(arg);
	lua_pop(L, 2);
	//get the parameter, a bool
	//get the parameter, a int
	//lookup with the index parameter in the array of nodes and set visible
	return 0;
}

int Game::C_loadStage(lua_State* L)
{
	std::string fileName = lua_tostring(L, -1);
	lua_pop(L, 1);
	std::ifstream rf(fileName, std::ios::out | std::ios::binary);
	Stage stage;
	if (!rf)
	{
		return 0;
	}
	
	rf.read((char*)&stage, sizeof(Stage));

	lua_createtable(L, 0, 1024);

	for (int i = 0; i < stage.height*stage.width; i++)
	{
		std::string str = std::to_string(i + 1);
		lua_pushnumber(L, stage.grid[i]);
		lua_setfield(L, -2, str.c_str());
	}
	lua_pushnumber(L, stage.width);
	lua_pushnumber(L, stage.height);

	rf.close();
	return 3;
}
int Game::C_saveStage(lua_State* L)
{
	std::string fileName = lua_tostring(L, -1);
	lua_pop(L, 1);
	std::ofstream wf(fileName, std::ios::out | std::ios::binary);
	Stage stage;
	
	stage.width = lua_tonumber(L, -1);
	stage.height = lua_tonumber(L, -2);

	lua_remove(L, -1);
	lua_remove(L, -1);

	for (int i = 0; i < stage.width*stage.height; i++)
	{
		std::string str = std::to_string(i + 1);
		lua_pushstring(L, str.c_str());
		lua_gettable(L, -2);

		int nr = (int)lua_tonumber(L, -1);
		stage.grid[i] = nr;
		lua_pop(L, 1);//pops the number gathered from the table
	}
	wf.write((char*)&stage, sizeof(Stage));
	wf.close();
	return 0;
}
int Game::C_setPosition(lua_State* L)
{
	float x = (float)lua_tonumber(L, -3);
	float y = (float)lua_tonumber(L, -2);
	float z = (float)lua_tonumber(L, -1);
	scene::IMeshSceneNode* node = (scene::IMeshSceneNode*)lua_touserdata(L, -4);
	if(node)
		node->setPosition(core::vector3df(x,y,z));
	lua_pop(L, 4);
	return 0;
}
int Game::C_setScale(lua_State* L)
{
	float x = (float)lua_tonumber(L, -3);
	float y = (float)lua_tonumber(L, -2);
	float z = (float)lua_tonumber(L, -1);
	scene::IMeshSceneNode* node = (scene::IMeshSceneNode*)lua_touserdata(L, -4);
	node->setScale(core::vector3df(x, y, z));
	lua_pop(L, 4);
	return 0;
}
int Game::C_setRotation(lua_State* L)
{
	float x = (float)lua_tonumber(L, -3);
	float y = (float)lua_tonumber(L, -2);
	float z = (float)lua_tonumber(L, -1);
	scene::IMeshSceneNode* node = (scene::IMeshSceneNode*)lua_touserdata(L, -4);
	node->setRotation(core::vector3df(x, y, z));
	lua_pop(L, 4);
	return 0;
}
int Game::C_addCube(lua_State* L)
{
	int type = (int)lua_tonumber(L, -2);
	

	scene::IMeshSceneNode* node = smgr->addCubeSceneNode();
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
	//scene::IMeshSceneNode* pi = (scene::IMeshSceneNode*)lua_newuserdata(L, sizeof(scene::IMeshSceneNode));
	lua_pushlightuserdata(L, node);

		
	
	return 1;
}
int Game::C_isKeyPressed(lua_State* L)
{
	int key = lua_tonumber(L,-1);
	lua_pop(L, 1);
	if (key == 1)
	{
		lua_pushboolean(L, eventRec.getMouseState().leftButtonDown);
	}
	else if (key == 2)
	{
		lua_pushboolean(L, eventRec.getMouseState().rightButtonDown);
	}
	else
	{
		lua_pushboolean(L, eventRec.IsKeyDown(irr::EKEY_CODE(key)));
	}
	return 1; 
}
int Game::C_setColor(lua_State* L)
{
	float r = (float)lua_tonumber(L, -3);
	float g = (float)lua_tonumber(L, -2);
	float b = (float)lua_tonumber(L, -1);
	scene::IMeshSceneNode* node = (scene::IMeshSceneNode*)lua_touserdata(L, -4);
	
	lua_pop(L, 4);
	return 0;
}
int Game::C_getMousePos3D(lua_State* L)
{
	// Create a ray through the mouse cursor.
	core::line3df ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
		eventRec.getMouseState().position, camera);
	float x = (float)lua_tonumber(L, -3);
	float y = (float)lua_tonumber(L, -2);
	float z = (float)lua_tonumber(L, -1);
	lua_pop(L, 3);
	core::vector3df objPos(x, y, z);
	// And intersect the ray with a plane on the grid
	core::plane3df plane(objPos, core::vector3df(0, 1, 0));
	core::vector3df mousePosition;
	if (plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
	{
		lua_pushnumber(L, mousePosition.X);
		lua_pushnumber(L, mousePosition.Y);
		lua_pushnumber(L, mousePosition.Z);
		return 3;
	}
	return 0;
}
int Game::C_setCamPos(lua_State* L)
{
	float x = (float)lua_tonumber(L, -3);
	float y = (float)lua_tonumber(L, -2);
	float z = (float)lua_tonumber(L, -1);

	lua_pop(L, 3);
	core::vector3df pos(x, y, z);
	camera->setPosition(pos);
	return 0;
}
void Game::render()
{
	if (device->isWindowActive())
	{
		

		//Draw or Render
		driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 200));


		smgr->drawAll();
		guienv->drawAll();


		driver->endScene();


	}
	else
	{
		device->yield();
	}
}

void Game::initialize()
{
	this->device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280, 720), 16, false, false, false, &eventRec);
	this->driver = device->getVideoDriver();
	this->smgr = device->getSceneManager();
	this->guienv = device->getGUIEnvironment();

	this->camera = smgr->addCameraSceneNode((irr::scene::ISceneNode*)0, core::vector3df(0, 50, -1), core::vector3df(0, 0, 0));
	device->getFileSystem()->changeWorkingDirectoryTo("E:/Lua_Irrlicht_BTH_template");
	smgr->addLightSceneNode((irr::scene::ISceneNode*)0, core::vector3df(0, 100, 0));
}

void Game::update()
{
	//Update
	//call update script
	if (this->eventRec.IsKeyDown(irr::KEY_KEY_V))
	{
		luaL_dofile(L, "Lua_Irrlicht_BTH_template/LuaScripts/test2.lua");
		int error = luaL_loadfile(L, "Lua_Irrlicht_BTH_template/LuaScripts/test2.lua");
		if (error)
		{
			std::cout << "error";
		}
	}
	luaL_dofile(L, "Lua_Irrlicht_BTH_template/LuaScripts/update.lua");
}

void Game::initLua()
{
	lua_pushcfunction(L, this->C_loadStage);
	lua_setglobal(L, "C_loadStage");
	lua_pushcfunction(L, this->C_saveStage);
	lua_setglobal(L, "C_saveStage");
	lua_pushcfunction(L, this->C_addToDraw);
	lua_setglobal(L, "C_addToDraw");
	lua_pushcfunction(L, this->C_setVisible);
	lua_setglobal(L, "C_setVisible");
	lua_pushcfunction(L, this->C_setPosition);
	lua_setglobal(L, "C_setPosition");
	lua_pushcfunction(L, this->C_setScale);
	lua_setglobal(L, "C_setScale");
	lua_pushcfunction(L, this->C_isKeyPressed);
	lua_setglobal(L, "C_isKeyPressed");
	lua_pushcfunction(L, this->C_getMousePos3D);
	lua_setglobal(L, "C_getMousePos3D");
	lua_pushcfunction(L, this->C_setCamPos);
	lua_setglobal(L, "C_setCamPos");
	int error = luaL_loadfile(L, "E:/Lua_Irrlicht_BTH_template/Lua_Irrlicht_BTH_template/LuaScripts/test2.lua"); 
	if (error)
	{
		std::cout << "error";
	}

	luaL_dofile(L, "Lua_Irrlicht_BTH_template/LuaScripts/Init.lua");


}
