#include<Tower-defense-Lua/Game.h>
irr::IrrlichtDevice* Game::device = nullptr;
irr::video::IVideoDriver* Game::driver = nullptr;
irr::scene::ISceneManager* Game::smgr = nullptr;
irr::gui::IGUIEnvironment* Game::guienv = nullptr;
irr::scene::ICameraSceneNode* Game::camera = nullptr;
const irr::scene::IGeometryCreator* Game::geomentryCreator = nullptr;

MyEventReceiver Game::eventRec = MyEventReceiver();
float Game::deltaTime = 0;
irr::gui::IGUIFont* Game::font = nullptr;


Game::Game()
{
	HRESULT hresult = CoInitialize(nullptr);
	if(hresult != S_OK)
	{
		throw std::logic_error("Could not CoInititialzie"); 
	}
	L = luaL_newstate();
	if(L == nullptr)
	{
		throw std::logic_error("Could not create a new lua state");
	}
	luaL_openlibs(L);
	this->eventRec = MyEventReceiver();
	int result = initIrrlicht();
	if (result != 0)
	{
		throw std::logic_error("Could not create and init irrlicht");
	}
	initLua();
	device->getCursorControl()->setVisible(true);
}

Game::~Game()
{
	CoUninitialize();
	if(device != nullptr)
	{
		device->drop();
	}
	lua_close(L);
}

int Game::initIrrlicht()
{
	SIrrlichtCreationParameters params = SIrrlichtCreationParameters();
	params.AntiAlias = ANTIALIAS;
	params.DriverType = DRIVERTYPE;
	params.WindowSize = WINDOWSIZE;
	params.EventReceiver = &eventRec;

	this->device = irr::createDeviceEx(params);
	if(this->device == NULL)
	{
		return -1;
	}
	this->driver = device->getVideoDriver();
	this->smgr = device->getSceneManager();
	this->guienv = device->getGUIEnvironment();
	this->geomentryCreator = smgr->getGeometryCreator();


	//Set default settings and a camera for irrlicht
	/*if (device->getFileSystem()->changeWorkingDirectoryTo(CWD))
	{
		std::cout << "Successfully changed the working directory to:" << device->getFileSystem()->getWorkingDirectory().c_str() << "\n";
	}*/
	
	font = device->getGUIEnvironment()->getFont(DEFAULTFONT);

	this->camera = smgr->addCameraSceneNode((irr::scene::ISceneNode*)0, DEFAULTCAMERAPOSITION, DEFAULTCAMERALOOKAT);
	return 0;
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
	lua_pushcfunction(L, this->C_isButtonPressed);
	lua_setglobal(L, "C_isButtonPressed");
	lua_pushcfunction(L, this->C_getDeltaTime);
	lua_setglobal(L, "C_getDeltaTime");
	lua_pushcfunction(L, this->C_removeFromDraw);
	lua_setglobal(L, "C_removeFromDraw");
	lua_pushcfunction(L, this->C_setRotation);
	lua_setglobal(L, "C_setRotation");
	lua_pushcfunction(L, this->C_setText);
	lua_setglobal(L, "C_setText");
	lua_pushcfunction(L, this->C_setCamTarget);
	lua_setglobal(L, "C_setCamTarget");
	lua_pushcfunction(L, this->C_setUIPos);
	lua_setglobal(L, "C_setUIPos");
	lua_pushcfunction(L, this->C_setTexture);
	lua_setglobal(L, "C_setTexture");
	lua_pushcfunction(L, this->C_getText);
	lua_setglobal(L, "C_getText");
	lua_pushcfunction(L, this->C_setFont);
	lua_setglobal(L, "C_setFont");
	lua_pushcfunction(L, this->C_print);
	lua_setglobal(L, "C_print");

	lua_getglobal(L, "package");
	lua_getfield(L, -1, "path"); // get field "path" from table at top of stack (-1)
	std::string cur_path = lua_tostring(L, -1); // grab path string from top of stack
	cur_path.append(";" RESOURCES_PATH "LuaScripts/?.lua"); // do your path magic here
	lua_pop(L, 1); // get rid of the string on the stack we just pushed on line 5
	lua_pushstring(L, cur_path.c_str()); // push the new one
	lua_setfield(L, -2, "path"); // set the field "path" in table at -2 with value at top of stack
	lua_pop(L, 1); // get rid of package table from top of stack
	

	int result = luaL_dofile(L, RESOURCES_PATH "LuaScripts/Init.lua");
	if (result != LUA_OK)
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << "\n";
	}
	//Load and call update.lua script to push the global Update function in the lua script.
	//This Lua global Update function is then called in Game::update()
	result = luaL_dofile(L, RESOURCES_PATH "LuaScripts/update.lua");
	if (result != LUA_OK)
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << "\n";
	}
}

void Game::run()
{
	irr::u32 then = device->getTimer()->getTime();
	while (device->run())
	{
		const irr::u32 now = device->getTimer()->getTime();
		deltaTime = (irr::f32)(now - then) / 1000.f; // Time in seconds
		then = now;
		this->update();
		this->render();
	}
}

int Game::C_addToDraw(lua_State* L)
{

	int type = (int)lua_tonumber(L, -2);
	lua_remove(L, -2);
	if (type == DrawType::MESH)
	{
		//mesh
		int top = lua_gettop(L);
		if (top != 1)
		{
			return luaL_error(L, "Error, not enought parameters were passed\n");
		}
		const char* model = lua_tostring(L, -1);
		std::string path = RESOURCES_PATH;
		path.append(model);
		lua_pop(L, 1);
		irr::scene::IMesh* mesh = smgr->getMesh(path.c_str());//change to model
		if (mesh == nullptr)
		{
			return luaL_error(L, "Could not load mesh with path: %s", path);
		}
		scene::IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
		irr::video::ITexture *texture = driver->getTexture(RESOURCES_PATH "Assets/3DObjects/cube2.tga");
		if(texture == nullptr)
		{
			return luaL_error(L, "Could not load texture %s", "Assets/3DObjects/cube2.tga");
		}
		else
		{
			std::cout << "Successfully loaded texture " << "Assets/3DObjects/cube2.tga\n";
		}
		node->setMaterialTexture(0, texture);
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		lua_pushlightuserdata(L, node);

	}
	else if (type == DrawType::BUTTON)
	{
		//button
		int top = lua_gettop(L);
		if (top != 1)
		{
			std::cerr << "Error, not enought parameters were passed\n";
		}

		std::string texture = RESOURCES_PATH;
		texture.append(lua_tostring(L, -1));


		gui::IGUIButton* button = guienv->addButton(core::recti(0, 0, 50, 50));
		button->setImage(driver->getTexture(texture.c_str()));
		//button->setScaleImage(true);
		button->setOverrideFont(font);
		
		lua_pop(L, 1);
		lua_pushlightuserdata(L, button);
	}
	else if (type == DrawType::TEXT)
	{
		//text

		int top = lua_gettop(L);
		if (top != 5)
		{
			std::cerr << "Error, not enought parameters were passed\n";
		}

		int x = (int)lua_tonumber(L, -5);
		int y = (int)lua_tonumber(L, -4);
		int x1 = (int)lua_tonumber(L, -3);
		int y1 = (int)lua_tonumber(L, -2);
		const char* text = lua_tostring(L, -1);

		WideText wText(text);

		core::recti rectangle(x, y, x1, y1);

		gui::IGUIStaticText* statText = guienv->addStaticText(wText.getWideChar(), rectangle);
		statText->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER);
		statText->setTextRestrainedInside(false);
		statText->setOverrideFont(font);
		lua_pop(L, 5);
		lua_pushlightuserdata(L, statText);
	}
	else if (type == DrawType::EDITBOX)
	{
		int top = lua_gettop(L);
		if (top != 5)
		{
			std::cerr << "Error, not enought parameters were passed\n";
		}
		int x = (int)lua_tonumber(L, -5);
		int y = (int)lua_tonumber(L, -4);
		int x1 = (int)lua_tonumber(L, -3);
		int y1 = (int)lua_tonumber(L, -2);
		const char* text = lua_tostring(L, -1);
		
		WideText wideText(text);

		core::recti rectangle(x, y, x1, y1);

		gui::IGUIEditBox* editBox = guienv->addEditBox(wideText.getWideChar(), rectangle);
		lua_pop(L, 5);
		lua_pushlightuserdata(L, editBox);
	}
	else if (type == DrawType::IMAGE)
	{
		int top = lua_gettop(L);
		if (top != 3)
		{
			std::cerr << "Error, not enought parameters were passed\n";
		}

		int x = (int)lua_tonumber(L, -3);
		int y = (int)lua_tonumber(L, -2);

		std::string texture = RESOURCES_PATH;
		texture.append(lua_tostring(L, -1));

		core::vector2di position(x, y);

		gui::IGUIImage* image = nullptr;
		irr::video::ITexture* irrTexture = nullptr;
		irrTexture = driver->getTexture(texture.c_str());
		if (irrTexture == nullptr)
		{
			std::cerr << " Error loading texture \n";
		}
		image = guienv->addImage(irrTexture, position);
		if (image == nullptr)
		{
			std::cerr << " Error adding image \n";
		}
		lua_pop(L, 3);
		lua_pushlightuserdata(L, image);
	}

	return 1;
}

int Game::C_removeFromDraw(lua_State* L)
{
	int type = (int)lua_tonumber(L, -2);
	lua_remove(L, -2);
	if (type == DrawType::MESH)
	{
		scene::IMeshSceneNode* node = (scene::IMeshSceneNode*)lua_touserdata(L, -1);
		lua_pop(L, 1);
		if (node != nullptr)
			node->remove();

	}
	else if (type == DrawType::BUTTON)
	{
		gui::IGUIButton * button = (gui::IGUIButton*)lua_touserdata(L, -1);
		lua_pop(L, 1);
		if (button != nullptr)
			button->remove();

	}
	else if (type == DrawType::TEXT)
	{
		gui::IGUIStaticText * text = (gui::IGUIStaticText*)lua_touserdata(L, -1);
		lua_pop(L, 1);
		if (text != nullptr)
			text->remove();
		
	}
	return 0;
}

int Game::C_setVisible(lua_State* L)
{

	bool arg = lua_toboolean(L, -1);
	scene::IMeshSceneNode* node = (scene::IMeshSceneNode*)lua_touserdata(L, -2);
	if (node != nullptr)
		node->setVisible(arg);
	lua_pop(L, 2);
	return 0;
}

int Game::C_loadStage(lua_State* L)
{
	std::string fileName = RESOURCES_PATH;
	fileName.append(lua_tostring(L, -1));
	lua_pop(L, 1);
	std::ifstream rf(fileName, std::ios::out | std::ios::binary);
	Stage stage;
	memset(&stage, 0, sizeof(Stage));
	if (!rf)
	{
		return 0;
	}

	rf.read((char*)&stage, sizeof(Stage));

	lua_createtable(L, 0, 1024);

	for (int i = 0; i < stage.height * stage.width; i++)
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
	std::string fileName = RESOURCES_PATH;
	fileName.append(lua_tostring(L, -1));
	lua_pop(L, 1);
	std::ofstream wf(fileName, std::ios::out | std::ios::binary);
	Stage stage{};
	memset(&stage, 0, sizeof(Stage));

	stage.width = (int)lua_tonumber(L, -1);
	stage.height = (int)lua_tonumber(L, -2);

	lua_remove(L, -1);
	lua_remove(L, -1);

	for (int i = 0; i < stage.width * stage.height; i++)
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
	if (node)
		node->setPosition(core::vector3df(x, y, z));
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

	lua_pushlightuserdata(L, node);



	return 1;
}
int Game::C_isKeyPressed(lua_State* L)
{
	int key = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);
	if (key == EKEY_CODE::KEY_LBUTTON)
	{
		lua_pushboolean(L, eventRec.getMouseState().leftButtonDown);
	}
	else if (key == EKEY_CODE::KEY_RBUTTON)
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

int Game::C_setCamTarget(lua_State* L)
{
	float x = (float)lua_tonumber(L, -3);
	float y = (float)lua_tonumber(L, -2);
	float z = (float)lua_tonumber(L, -1);

	lua_pop(L, 3);
	core::vector3df pos(x, y, z);
	camera->setTarget(pos);
	return 0;
}
int Game::C_setTexture(lua_State* L)
{
	std::string texture = RESOURCES_PATH;
	texture.append(lua_tostring(L, -1));
	int type = (int)lua_tonumber(L, -2);
	scene::IMeshSceneNode* node = (scene::IMeshSceneNode*)lua_touserdata(L, -3);

	if (type == DrawType::MESH)
	{
		node->setMaterialTexture(0, driver->getTexture(texture.c_str()));
	}
	else if (type == DrawType::BUTTON)
	{
		gui::IGUIButton* button = (gui::IGUIButton*)lua_touserdata(L, -3);
		if (button != nullptr)
			button->setImage(driver->getTexture(texture.c_str()));
	}
	else if(type == 3)
	lua_pop(L, 3);
	return 0;
}
int Game::C_setUIPos(lua_State* L)
{
	int x = (int)lua_tonumber(L, -2);
	int y = (int)lua_tonumber(L, -1);

	gui::IGUIElement* uiElement = (gui::IGUIElement*)lua_touserdata(L, -3);
	if (uiElement)
		uiElement->setRelativePosition(core::vector2di(x, y));
	lua_pop(L, 3);
	return 0;
}
int Game::C_isButtonPressed(lua_State* L)
{
	gui::IGUIButton* button = (gui::IGUIButton*)lua_touserdata(L, -1);
	lua_pop(L, 1);
	if (button)
		lua_pushboolean(L, button->isPressed());
	return 1;
}
int Game::C_getDeltaTime(lua_State* L)
{
	lua_pushnumber(L, deltaTime);
	return 1;
}
int Game::C_setText(lua_State* L)
{
	const char* text = lua_tostring(L, -1);
	WideText wideText(text);

	gui::IGUIElement* node = (gui::IGUIElement*)lua_touserdata(L, -2);
	if (node != nullptr)
		node->setText(wideText.getWideChar());
	lua_pop(L, 2);

	return 0;
}
int Game::C_getText(lua_State* L)
{
	gui::IGUIEditBox* editBox = (gui::IGUIEditBox*)lua_touserdata(L, -1);
	lua_pop(L, 1);
	if (editBox)
	{
		const WCHAR* wc = editBox->getText();
		_bstr_t convert(wc);
		const char* text = convert;
		lua_pushstring(L, text);
	}
	return 1;
}
int Game::C_setFont(lua_State* L)
{
	if (lua_gettop(L) != 3)
	{
		std::cerr << "Not enought parameters for C_setFont\n" << lua_gettop(L) << " passed\n";
		return -1;
	}
	int type = (int)lua_tonumber(L, -2);
	lua_remove(L, -2);
	if (type == DrawType::BUTTON)
	{
		gui::IGUIButton* button = (gui::IGUIButton*)lua_touserdata(L, -2);
		std::string fontPath = RESOURCES_PATH;
		fontPath.append(lua_tostring(L, -1));
		if (button != nullptr)
		{
			const irr::io::path irrPath(fontPath.c_str());
			irr::gui::IGUIFont* irrFont = guienv->getFont(irrPath);
			if (irrFont == nullptr)
			{
				std::cerr << "Couldn't load the font: " << irrPath.c_str() << "\n";
			}
			button->setOverrideFont(irrFont);
		}
		lua_pop(L, 2);
	}
	else if (type == DrawType::TEXT)
	{
		gui::IGUIStaticText* text = (gui::IGUIStaticText*)lua_touserdata(L, -2);
		std::string fontPath = RESOURCES_PATH;
		fontPath.append(lua_tostring(L, -1));
		if (text != nullptr)
		{
			const irr::io::path irrPath(fontPath.c_str());
			irr::gui::IGUIFont* irrFont = guienv->getFont(irrPath);
			if (irrFont == nullptr)
			{
				std::cerr << "Couldn't load the font: " << irrPath.c_str() << "\n";
			}
			text->setOverrideFont(irrFont);
		}
		lua_pop(L, 2);
	}

	return 0;
}
int Game::C_print(lua_State* L)
{
	const char* text = lua_tostring(L, -1);
	std::cout << text << "\n";
	lua_pop(L, 1);
	return 0;
}
void Game::render()
{
	if (device->isWindowActive())
	{
		driver->beginScene(true, true, CLEARCOLOR);
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}
	else
	{
		device->yield();
	}
}



void Game::update() const
{
	//Update
	//call update script
	lua_getglobal(L, "Update");
	if (lua_type(L, -1) == LUA_TFUNCTION)
	{
		int numArgs = 0;
		lua_pcall(L, numArgs, 0, 0);//removes function from stack
	}
	else
	{
		luaL_error(L, "unknown script function %s", "Update");
	}
}


