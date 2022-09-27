#include "Board.h"
#include <random>

Board::Cell::Cell(Location loc)
	:
	loc(loc){}

void Board::Cell::Draw(Graphics &gfx){
	gfx.DrawSquareWithPadding(loc.x*cellSize, loc.y*cellSize, cellSize, cellSize, Colors::Green);
}

void Board::Cell::SetLoc(Location &src){
	loc = src;
}

Board::Cell& Board::Cell::operator=(Cell &src){
	loc = src.GetLoc();
	alive = src.isAlive();
	return *this;
}

Location Board::Cell::GetLoc(){
	return loc;
}

void Board::Cell::Toggle(){
	alive = !alive;
}

bool Board::Cell::isAlive(){
	return alive;
}

void Board::Cell::AddToToggle(){
	toToggle = true;
}

void Board::Cell::Tick(){
	if(toToggle)
		Toggle();
	toToggle = false;
}

Board::Board()
{
	board.resize(Graphics::ScreenHeight / cellSize);
	for(auto &n : board)
		n.resize(Graphics::ScreenWidth / cellSize);
	InitSpawn();
	for(int y = 0; y < Graphics::ScreenHeight / cellSize; y++)
		for(int x = 0; x < Graphics::ScreenWidth / cellSize; x++){
			Location loc(x, y);
			board[y][x].SetLoc(loc);
		}
}

void Board::Draw(Graphics &gfx){
	for(int y = 0; y < Graphics::ScreenHeight / cellSize; y++)
		for(int x = 0; x < Graphics::ScreenWidth / cellSize; x++)
			if(board[y][x].isAlive())
				board[y][x].Draw(gfx);
}

void Board::InitSpawn(){
	std::mt19937 rng = std::mt19937(std::random_device()());
	std::uniform_int_distribution<int> xuid(0, Graphics::ScreenWidth / cellSize - 1);
	std::uniform_int_distribution<int> yuid(0, Graphics::ScreenHeight / cellSize - 1);
	for(int i = 0; i < 30000; i++){
		bool isOccupied = false;
		int x;
		int y;
		do{
			x = xuid(rng);
			y = yuid(rng);
		} while(board[y][x].isAlive());
		Location loc(x, y);
		board[y][x].SetLoc(loc);
		board[y][x].Toggle();
	}
}

void Board::KillCell(Cell &c){
	if(c.isAlive())
		c.Toggle();
}

void Board::KillCell(Location &loc){
	if(!((loc.x < 0) || (loc.y < 0) || (loc.x > Graphics::ScreenWidth / cellSize - 1) || (loc.y > Graphics::ScreenHeight / cellSize - 1)))
		KillCell(board[loc.y][loc.x]);
}

void Board::SpawnCell(Cell &c){
	if(!c.isAlive())
		c.Toggle();
}

void Board::SpawnCell(Location &loc){
	if(!((loc.x < 0) || (loc.y < 0) || (loc.x > Graphics::ScreenWidth / cellSize - 1) || (loc.y > Graphics::ScreenHeight / cellSize - 1)))
		SpawnCell(board[loc.y][loc.x]);
}

void Board::ClearBoard(){
	for(int y = 0; y < Graphics::ScreenHeight / cellSize; y++)
		for(int x = 0; x < Graphics::ScreenWidth / cellSize; x++)
			KillCell(board[y][x]);
}

void Board::Reset(){
	ClearBoard();
	InitSpawn();
}

void Board::Update(){
	for(int y = 0; y < Graphics::ScreenHeight / cellSize; y++)
		for(int x = 0; x < Graphics::ScreenWidth / cellSize; x++){
			int nNeighbours = 0;
			int xl = board[y][x].GetLoc().x;
			int yl = board[y][x].GetLoc().y;
			for(int xo = -1; xo <= 1; xo++)
				for(int yo = -1; yo <= 1; yo++){
					if(!((xl + xo < 0) || (yl + yo < 0) || (xl + xo > Graphics::ScreenWidth / cellSize - 1) || (yl + yo > Graphics::ScreenHeight / cellSize - 1)))
						if(!(xo == 0 && yo == 0))
							nNeighbours += board[(yl + yo)][(xl + xo)].isAlive();
				}

			if(board[y][x].isAlive() && (nNeighbours > 3 || nNeighbours < 2))
				board[y][x].AddToToggle();
			else if(!(board[y][x].isAlive()) && nNeighbours == 3)
				board[y][x].AddToToggle();
		}

	for(int y = 0; y < Graphics::ScreenHeight / cellSize; y++)
		for(int x = 0; x < Graphics::ScreenWidth / cellSize; x++)
			board[y][x].Tick();

}