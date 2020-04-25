#pragma once
#include <irrlicht.h>
#include<cassert>
class Gameobject
{
public:
	Gameobject();
	~Gameobject();
	void setTexture(irr::video::ITexture* aTexture);//loads the texture and sets it to the meshSceneNode
	void setMeshNode(irr::scene::IMesh* aMesh, irr::scene::ISceneManager* sceneMgr);//loads the mesh and creates the meshSceneNode. This has to be called first 
	void setMeshNode(irr::scene::IMeshSceneNode* meshSceneNode);//Needs to be called first. Calling any position etc will not do anything
	void setPosition(float x, float y, float z);
	void setPosition(const irr::core::vector3df& vector);

	void move(float x, float y, float z);
	void move(const irr::core::vector3df& vector);

	void setRotation(float yaw, float pitch, float roll);
	void setRotation(const irr::core::vector3df& yawPitchRoll);

	void rotate(float yaw, float pitch, float roll);
	void rotate(const irr::core::vector3df& yawPitchRoll);

	irr::core::vector3df getPosition()const;
	irr::core::vector3df getRotation()const;
	
private:
	irr::scene::IMeshSceneNode* object;
	irr::video::ITexture* texture;//diffuseTexture
	irr::scene::IMesh* mesh;//mesh for the object

	irr::core::vector3df position;
	irr::core::vector3df rotation;

	bool checkSceneNode()const;
};