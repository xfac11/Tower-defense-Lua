#include"Game.h"
void ConsoleThread(lua_State* L) 
{
	char command[1000];
	while(GetConsoleWindow()) {
		memset(command, 0, 1000);
		std::cin.getline(command, 1000);
		if( luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0) )
			std::cout << lua_tostring(L, -1) << '\n';
	}
}
void callScriptFunction(lua_State* L, const char* funcName, int x)
{
	lua_getglobal(L, funcName);
	if (lua_type(L, -1) == LUA_TFUNCTION)
	{
		int numArgs = 0;
		if (lua_pcall(L, numArgs, 0, 0) != 0)//removes function from stack
		{

		}
		else
		{

		}

	}
	else
	{
		luaL_error(L, "unknown script function %s", funcName);
	}
}
auto addToDraw = [](lua_State* L) -> int
{
	
};
auto removeFromDraw = [](lua_State* L) -> int
{
	//remove it from array and delete it
	return 0;
};
auto setVisible = [](lua_State* L) -> int
{
	//get the parameter, a bool
	//get the parameter, a int
	//lookup with the index parameter in the array of nodes and set visible
	return 0;
};

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	std::thread conThread(ConsoleThread, L);
	MyEventReceiver receiver;

	irr::IrrlichtDevice* device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280, 720), 16, false, false,false, &receiver);
	if(!device)
		return 1;
	
	luaL_dofile(L, "LuaScripts/updateScript.lua");
	callScriptFunction(L, "show", 0);
	Gameobject object;
	object.setPosition(1, 2, 3);
	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
	irr::video::IVideoDriver* driver	= device->getVideoDriver();
	irr::scene::ISceneManager* smgr		= device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv	= device->getGUIEnvironment();
	device->getFileSystem()->changeWorkingDirectoryTo("E:/Lua_Irrlicht_BTH_template");
	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!", irr::core::rect<irr::s32>(10, 10, 260, 42), true);
	guienv->addButton(irr::core::rect<irr::s32>(50, 50, 270, 72), nullptr, -1, L"BUTTON");
	irr::scene::IMesh* mesh = smgr->getMesh("3DObjects/cube2.obj");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	
	irr::scene::IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
	node->setPosition(irr::core::vector3df(10,10,10));
	//smgr->addArrowMesh();
	if (node)
	{
		//node->setMaterialFlag(EMF_LIGHTING, false);
		//node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		node->setMaterialTexture(0, driver->getTexture("3DObjects/cube2.mtl"));
		
	}
	irr::scene::IMesh* robotMesh = smgr->getMesh("3DObjects/robot.obj");
	if (!robotMesh)
	{
		device->drop();
		return 1;
	}
	irr::scene::IMeshSceneNode* robotNode = smgr->addMeshSceneNode(robotMesh);
	//robotMesh->setPosition(irr::core::vector3df(10, 10, 10));
	//smgr->addArrowMesh();
	if (robotNode)
	{
		//node->setMaterialFlag(EMF_LIGHTING, false);
		//node->setMD2Animation(scene::EMAT_STAND);
		robotNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		robotNode->setMaterialTexture(0, driver->getTexture("3DObjects/robot.mtl"));
	}

	irr::scene::IMesh* planeMesh = smgr->getMesh("3DObjects/planeGrass.obj");
	if (!planeMesh)
	{
		device->drop();
		return 1;
	}
	irr::scene::IMeshSceneNode* planeGrassNode = smgr->addMeshSceneNode(planeMesh);
	planeGrassNode->setVisible(false);
	//robotMesh->setPosition(irr::core::vector3df(10, 10, 10));
	//smgr->addArrowMesh();
	if (planeGrassNode)
	{
		//node->setMaterialFlag(EMF_LIGHTING, false);
		//node->setMD2Animation(scene::EMAT_STAND);
		planeGrassNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);

		planeGrassNode->setMaterialTexture(0, driver->getTexture("3DObjects/planeGrass.mtl"));
	}
	//smgr->addCameraSceneNode(0, irr::core::vector3df(0, 30, -40), irr::core::vector3df(5, 5, 5));
	irr::scene::ICameraSceneNode* cam = smgr->addCameraSceneNode((irr::scene::ISceneNode*)0,irr::core::vector3df(0,10,0),irr::core::vector3df(0,-100,0));
	
	device->getCursorControl()->setVisible(true);
	int lastFPS = -1;
	cam->setFOV(110.0f*(3.14/180));
	irr::u32 then = device->getTimer()->getTime();
	
	const irr::f32 MOVEMENT_SPEED = 20.f;

	while(device->run()) 
	{
		const irr::u32 now = device->getTimer()->getTime();
		const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f; // Time in seconds
		then = now;
		luaL_dofile(L, "LuaScripts/updateScript.lua");


		if (device->isWindowActive())
		{
			//Update
			irr::core::vector3df nodePosition;

			if (receiver.IsKeyDown(irr::KEY_KEY_W))
				nodePosition.Z = 1;
			else if (receiver.IsKeyDown(irr::KEY_KEY_S))
				nodePosition.Z = -1;

			if (receiver.IsKeyDown(irr::KEY_KEY_A))
				nodePosition.X = -1;
			else if (receiver.IsKeyDown(irr::KEY_KEY_D))
				nodePosition.X = 1;

			float x = 0;
			float z = 0;

			lua_getglobal(L, "update");
			if (lua_type(L, -1) == LUA_TFUNCTION)
			{
				int numArgs = 2;
				int numReturns = 2;
				lua_pushnumber(L, nodePosition.X);
				lua_pushnumber(L, nodePosition.Z);
				if (lua_pcall(L, numArgs, numReturns, 0) == 0)//removes function from stack
				{
					lua_Number newX = lua_tonumber(L, -2);
					lua_Number newZ = lua_tonumber(L, -1);
					x = (float)newX;
					z = (float)newZ;

					lua_pop(L, -1);
					lua_pop(L, -1);
				}
				else
				{

				}

			}
			else
			{
				luaL_error(L, "unknown script function %s", "update");
			}
			irr::core::vector3df newPos;
			newPos.X = x;
			newPos.Z = z;
	
			robotNode->setPosition(newPos);
			//Draw or Render
			driver->beginScene(true, true, irr::video::SColor(255, 200, 200, 200));
			

			smgr->drawAll();
			guienv->drawAll();

			
			driver->endScene();
			int fps = driver->getFPS();

			if (lastFPS != fps)
			{
				irr::core::stringw str= L"Irrlicht Engine - Quake 3 Map example [";
				str += driver->getName();
				str += "] FPS:";
				str += fps;

				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
			
		}
		else
		{
			device->yield();
		}
	}

	device->drop();

	conThread.join();
	return 0;
}