#pragma comment(lib, "Irrlicht.lib")
#ifdef _DEBUG
#pragma comment(lib, "LuaLibd.lib")
#else
#pragma comment(lib, "Lualib.lib")
#endif

#include <lua.hpp>
#include <Windows.h>
#include <iostream>
#include <thread>
#include "lua.hpp"
#include <irrlicht.h>
#include"Gameobject.h"
#include<cstdio>
int main()
{
	{
		/*lua_State* L = luaL_newstate();
		luaL_dostring(L, "x = 42");
		lua_getglobal(L, "x");
		lua_Number x = lua_tonumber(L, -1);
		std::cout << "Lua says x = " << x << std::endl;
		lua_close(L);*/
	}

	{
		//lua_State* L = luaL_newstate();
		//lua_pushnumber(L, 42);
		//lua_pushnumber(L, 52);
		//lua_pushnumber(L, 62);

		//lua_Number x = lua_tonumber(L, -2);
		//std::cout << "Lua says x = " << x << std::endl;

		//lua_remove(L, -1);//removes one at specific location, now -1, lua_pop will remove from top to down. pop(1) will remove top of stack and pop(2) will
		////remove top and top-1 [1,2,3,4,5]  pop(2) [1,2,3,x,x] 5 is top of stack
		//

		//lua_close(L);
	}

	{
		//lua_State* L = luaL_newstate();

		//constexpr const char* LUA_FILE = R"(
		//function Pythagoras( a, b )
		//	return (a * a) + (b * b), a, b
		//end
		//)";

		//luaL_dostring(L,LUA_FILE);
		//lua_getglobal(L, "Pythagoras");
		//if (lua_isfunction(L, -1))
		//{
		//	lua_pushnumber(L, 3); // a
		//	lua_pushnumber(L, 4); // b
		//	constexpr int NUM_ARGS = 2;
		//	constexpr int NUM_RETURNS = 3;
		//	lua_pcall(L, NUM_ARGS, NUM_RETURNS, 0);
		//	lua_Number c = lua_tonumber(L, -3); // -3 because the first to get push onto the stack is the left most return. So return c, a, b
		//	//[c, a, b] b top of stack. [c], [c, a], [c, a, b].
		//	printf("C = %d\n", (int)c);
		//}
		//lua_close(L);
	}

	{
		//auto  NativePythagoras = [](lua_State * L) -> int
		//{
		//	lua_Number a = lua_tonumber(L, -2);
		//	lua_Number b = lua_tonumber(L, -1);
		//	lua_Number csqr = (a * a) + (b * b);
		//	lua_pushnumber(L, csqr);
		//	return 1;//number of returns, number of pushed
		//};

		//lua_State* L = luaL_newstate();

		//lua_pushcfunction(L, NativePythagoras);
		//lua_setglobal(L, "NativePythagoras");

		//constexpr const char* LUA_FILE = R"(
		//function Pythagoras( a, b )
		//	csqr = NativePythagoras( a, b )
		//	return csqr, a, b
		//end
		//)";

		//luaL_dostring(L, LUA_FILE);
		//lua_getglobal(L, "Pythagoras");
		//if (lua_isfunction(L, -1))
		//{
		//	lua_pushnumber(L, 3); // a
		//	lua_pushnumber(L, 4); // b
		//	constexpr int NUM_ARGS = 2;
		//	constexpr int NUM_RETURNS = 3;
		//	lua_pcall(L, NUM_ARGS, NUM_RETURNS, 0);
		//	lua_Number c = lua_tonumber(L, -3); // -3 because the first to get push onto the stack is the left most return. So return c, a, b
		//	//[c, a, b] b top of stack. [c], [c, a], [c, a, b].
		//	printf("C = %d\n", (int)c);
		//}
		//lua_close(L);
	}

	{
		struct Sprite
		{
			int x; 
			int y;

			void Move(int velX, int velY)
			{
				x += velX;
				y += velY;
			}
		};
		auto addToDraw = [](lua_State* L) -> int
		{
			int index = 0;
			//Create meshnode with string parameter
			//put in array of pointers
			//return index of the place in the array
			std::string meshFile = lua_tostring(L, -1);
			lua_pushnumber(L, index);
			return 1;
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
		auto CreateSprite = [](lua_State* L) -> int
		{
			Sprite* sprite = (Sprite*)lua_newuserdata(L, sizeof(Sprite));
			sprite->x = 0;
			sprite->y = 0;
			return 1;
		};

		auto MoveSprite = [](lua_State* L) -> int
		{
			Sprite* sprite = (Sprite*)lua_touserdata(L, -3);
			lua_Number velX = lua_tonumber(L, -2);
			lua_Number velY = lua_tonumber(L, -1);
			sprite->Move((int)velX, (int)velY);
			return 0;
		};
		const constexpr char* FILE = R"(
		sprite = CreateSprite()
		MoveSprite( sprite, 5, 7 )
		)";

		lua_State* L = luaL_newstate();
		lua_pushcfunction(L, CreateSprite);
		lua_setglobal(L, "CreateSprite");
		lua_pushcfunction(L, MoveSprite);
		lua_setglobal(L, "MoveSprite");
		luaL_dostring(L, FILE);
		lua_getglobal(L, "sprite");
		if (lua_isuserdata(L, -1))
		{
			printf("We got a sprite from Lua\n");
			Sprite* sprite = (Sprite*)lua_touserdata(L, -1);
			printf("x = %d, y = %d\n", sprite->x, sprite->y);
		}
		else
		{
			printf("We didn't get a sprite from Lua");
		}

		lua_close(L);

	}

	{
		const constexpr char* FILE = R"(
		x = { dave = "busy", ian = "idle" }
		)";

		lua_State* L = luaL_newstate();
		luaL_dostring(L, FILE);

		lua_getglobal(L, "x");
		lua_pushstring(L, "dave");
		lua_gettable(L, -2); //index for the table on the stack not "dave"
		const char* daveIs = lua_tostring(L, -1);// can garbage collect. So if needed somewhere else copy it
		printf("daveIs = %s\n", daveIs);

		lua_getglobal(L, "x");
		lua_getfield(L, -1, "ian");// same as pushstring and gettable
		const char* ianIs = lua_tostring(L, -1);// can garbage collect. So if needed somewhere else copy it
		printf("ianIs = %s\n", ianIs);

		lua_getglobal(L, "x");
		lua_pushstring(L, "sleeping");
		lua_setfield(L, -2, "john");

		lua_getglobal(L, "x");
		lua_getfield(L, -1, "john");// same as pushstring and gettable
		const char* johnIs = lua_tostring(L, -1);// can garbage collect. So if needed somewhere else copy it
		printf("johnIs = %s\n", johnIs);

		lua_close(L);
	}
	system("pause");
	return 0;
}