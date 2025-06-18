#include<Tower-defense-Lua/Gameobject.h>

Gameobject::Gameobject()
{
}

Gameobject::~Gameobject()
{
}

void Gameobject::setTexture(irr::video::ITexture* aTexture)
{
	this->texture = texture;
	if (this->object != nullptr)
		this->object->setMaterialTexture(0, this->texture);
}

void Gameobject::setMeshNode(irr::scene::IMesh* aMesh, irr::scene::ISceneManager* sceneMgr)
{
	this->mesh = aMesh;
	this->object = sceneMgr->addMeshSceneNode(this->mesh);
	if (this->texture != nullptr)
		this->object->setMaterialTexture(0, this->texture);

}

void Gameobject::setMeshNode(irr::scene::IMeshSceneNode* meshSceneNode)
{
	this->mesh = meshSceneNode->getMesh();
	this->object = meshSceneNode;
	if (this->texture != nullptr)
		this->object->setMaterialTexture(0, this->texture);
}

void Gameobject::setPosition(float x, float y, float z)
{
	if (!checkSceneNode())
		return;

	this->object->setPosition(irr::core::vector3df(x, y, z));
	
}

void Gameobject::setPosition(const irr::core::vector3df& vector)
{
	if (!checkSceneNode())
		return;

	this->object->setPosition(vector);
}

void Gameobject::move(float x, float y, float z)
{
	if (!checkSceneNode())
		return;

	this->object->setPosition(this->object->getPosition()+irr::core::vector3df(x, y, z));
}

void Gameobject::move(const irr::core::vector3df& vector)
{
	if(!checkSceneNode())
		return;

	this->object->setPosition(this->object->getPosition() + vector);
}

void Gameobject::setRotation(float yaw, float pitch, float roll)
{
	if (!checkSceneNode())
		return;

	this->object->setRotation(irr::core::vector3df(yaw, pitch, roll));
}

void Gameobject::setRotation(const irr::core::vector3df& yawPitchRoll)
{
	if (!checkSceneNode())
		return;

	this->object->setRotation(yawPitchRoll);
}

void Gameobject::rotate(float yaw, float pitch, float roll)
{
	if (!checkSceneNode())
		return;

	this->object->setRotation(this->object->getRotation() + irr::core::vector3df(yaw, pitch, roll));
}

void Gameobject::rotate(const irr::core::vector3df& yawPitchRoll)
{
	if (!checkSceneNode())
		return;

	this->object->setRotation(this->object->getRotation() + yawPitchRoll);
}

irr::core::vector3df Gameobject::getPosition() const
{
	if (!checkSceneNode())
		return irr::core::vector3df();

	return this->object->getPosition();
}

irr::core::vector3df Gameobject::getRotation() const
{
	if (!checkSceneNode())
		return irr::core::vector3df();

	return this->object->getRotation();
}

bool Gameobject::checkSceneNode()const
{
	return this->object != nullptr;
}
