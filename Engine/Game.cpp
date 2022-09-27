/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Location.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}
void Game::UpdateModel()
{
	auto now = std::chrono::steady_clock::now();
	if(1000/speed < std::chrono::duration_cast<std::chrono::milliseconds>(now - mark).count() && !paused){
		test.Update();
		mark = now;
	}

	if(wnd.kbd.KeyIsPressed(VK_SPACE) && !pauseIsPressed){
		paused = !paused;
		pauseIsPressed = true;
	}
	else if(!wnd.kbd.KeyIsPressed(VK_SPACE))
		pauseIsPressed = false;

	if(wnd.kbd.KeyIsPressed(VK_OEM_PLUS))
		speed += 0.05f;

	if(wnd.kbd.KeyIsPressed(VK_OEM_MINUS))
		speed -= 0.05f;

	if(wnd.kbd.KeyIsPressed('C'))
		test.ClearBoard();

	if(wnd.kbd.KeyIsPressed('R'))
		test.Reset();

	if(wnd.mouse.LeftIsPressed()){
		Location loc(wnd.mouse.GetPosX() / Board::cellSize, wnd.mouse.GetPosY() / Board::cellSize);
		test.SpawnCell(loc);
	}
	if(wnd.mouse.RightIsPressed()){
		Location loc(wnd.mouse.GetPosX() / Board::cellSize, wnd.mouse.GetPosY() / Board::cellSize);
		test.KillCell(loc);
	}
}

void Game::ComposeFrame()
{
	test.Draw(gfx);
}
