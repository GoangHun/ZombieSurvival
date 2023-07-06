#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Utils.h"

class GameObject
{
protected:
	std::string name;
	sf::Vector2f position;

	bool isActive = true;

	Origins origin;

public:
	int sortLayer = 0;	//���� ���� ���� public���� ������� �������
	int sortOrder = 0;

	GameObject(const std::string n = "");
	virtual ~GameObject();

	bool GetActive() const;
	void SetActive(bool active);

	std::string GetName();
	virtual void SetName(const std::string& n);

	virtual const sf::Vector2f GetPosition() const;

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);


	virtual void Init() = 0;	//������ ����
	virtual void Release() {};	//�Ҹ��� ����
	virtual void Reset() {};	//�ʱ�ȭ ����

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
};
