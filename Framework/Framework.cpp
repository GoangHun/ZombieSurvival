#include "stdafx.h"
#include "Framework.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "Scene.h" 

Framework::Framework(int w, int h, const std::string& title)
    : screenWidth(w), screenHeight(h), title(title)
{
}

void Framework::Init(int width, int height, const std::string title)
{
	window.create(sf::VideoMode(width, height), title);

    SCENE_MGR.Init();
}

void Framework::Release()
{
    SCENE_MGR.Release();
}

void Framework::Update(float dt)
{
    SCENE_MGR.Update(dt);}

void Framework::Draw(sf::RenderWindow& window)
{
    SCENE_MGR.Draw(window);
}

void Framework::Run()
{
    Init(screenWidth, screenHeight, title);

    clock.restart();

    //Ŀ�� �̹��� �����ϱ�
    sf::Image cusorImg;
    cusorImg.loadFromFile("graphics/crosshair.png");

    sf::Cursor cursor;
    if (cursor.loadFromPixels(cusorImg.getPixelsPtr(), cusorImg.getSize(),
        { cusorImg.getSize().x / 2, cusorImg.getSize().y / 2 }))
    {
        window.setMouseCursor(cursor);
    }

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        INPUT_MGR.Clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                SCENE_MGR.GetCurrScene()->Exit();
                window.close();
                break;
            case sf::Event::GainedFocus:
                window.setMouseCursor(cursor);
                break;
            }

            INPUT_MGR.Update(event);
        }

        if (window.isOpen())
        {
            Update(dt);

            window.clear();
            Draw(window);
            window.display();
        } 
    }

    Release();
}

sf::Vector2f Framework::GetWindowSize()
{
    return sf::Vector2f(screenWidth, screenHeight);
}

sf::RenderWindow& Framework::GetWindow()
{
    return window;
}
