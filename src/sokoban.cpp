#include "sokoban.hpp"

Sokoban::Sokoban(std::vector<std::vector<std::string>> levels) 
{
    this->levels = levels;
    current_level = 0;
    _board = levels.at(current_level);
}

unsigned int Sokoban::level() 
{
    return current_level;
}

bool Sokoban::solved() 
{
    for (std::string row : board()) {
        for (char cell : row) {
            if (cell == '.' || cell == '+') {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::string> Sokoban::board() 
{
    return _board;
}


void Sokobann::locate_player()
{
	for (int y = 0; y < _board.size(); y++)
	{
		for (int x = 0; x < _board[y].size(); x++)
		{
			if (_board[y][x] == '@' || _board[y][x] == '+')
			{
				px = x; py = y;
				return;
			}
		}
	}
	
	throw std::invalid_argument("Player not found...");
	
}