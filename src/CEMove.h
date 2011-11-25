#ifndef CHESS_ENGINE_MOVE
#define CHESS_ENGINE_MOVE

namespace pgn
{
	class Ply;
};

namespace ChEngn
{
	class Table;

	class Move
	{
	public:
		Move() {};
		virtual ~Move() {};
		virtual bool make(const Table* table) const = 0;
	};
}

#endif // CHESS_ENGINE_MOVE 
