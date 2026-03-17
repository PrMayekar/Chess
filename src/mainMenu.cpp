#include <raylib.h>
#include <iostream>
#include "resource_dir.h"
#include "utils.h"
#include "mainMenu.h"
#include "game.h"

Menu::Menu()
{

}

void Menu::setGameStarted()
{
	gameStarted = true;
}

void Menu::clearGameStarted()
{
	gameStarted = false;
}

bool Menu::getGameStarted()
{
	return gameStarted;
}

void Menu::displayMenu()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 800, "Menu");

	while (!WindowShouldClose() && gameStarted ==false)
	{
		BeginDrawing();
		ClearBackground(WHITE);
		Texture2D backGround = LoadTexture("assets/background.png");
		
		DrawTexturePro(backGround,
			{ 0.0f,
			0.0f,
			(float)backGround.width,
			(float)backGround.height },
			{ 0.0f,
			0.0f,
			800.0f,
			800.0f },
			{ 0.0f,0.0f },
			0.0f,
			WHITE
		);
		
		DrawRectangle(120, 300, 560, 100, Color{ 255, 255, 255, 200 });
		DrawText("NEW GAME", 130, 300, 100, BLACK);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{	
			Vector2 mouse = GetMousePosition();
			if (CheckCollisionPointRec(mouse, { 120, 300, 560, 100 }))
			{
				Game game;
				setGameStarted();
				EndDrawing();
				CloseWindow();
				game.initialize();
				clearGameStarted();
				goto jp;
			}
		}
		EndDrawing();
	}
	CloseWindow();
	jp:
	return;
}