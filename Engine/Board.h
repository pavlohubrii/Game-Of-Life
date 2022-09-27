#pragma once

#include "Location.h"
#include "Graphics.h"
#include <vector>

class Board{
private:
	class Cell{
	public:
		Cell() = default;
		Cell(Location loc);
		void Draw(Graphics &gfx);
		void SetLoc(Location &src);
		Cell &operator =(Cell &src);
		Location GetLoc();
		void Toggle();
		bool isAlive();
		void AddToToggle();
		void Tick();
	private:
		Location loc = {-2, -2};
		bool alive = false;
		bool toToggle = false;
	};
private:
	void InitSpawn();
public:
	Board();
	void Draw(Graphics &gfx);
	void KillCell(Cell &c);
	void KillCell(Location &loc);
	void SpawnCell(Cell &c);
	void SpawnCell(Location &loc);
	void ClearBoard();
	void Reset();
	void Update();
	static constexpr int cellSize = 2;
private:
//	Cell board[Graphics::ScreenHeight / cellSize][Graphics::ScreenWidth / cellSize];
	std::vector<std::vector<Cell>> board;
};

