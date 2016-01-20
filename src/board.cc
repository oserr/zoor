/**
 * @file board.cc
 * @author Omar A Serrano
 * @date 2015-12-26
 */

// STL headers
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>

// zoor headers
#include "piececode.hh"
#include "piececount.hh"
#include "square.hh"
#include "piecemoves.hh"
#include "board.hh"

namespace zoor {

/**
 * TODO: determine how to initialize default board.
 */
Board::Board() {}

/**
 * TODO: implement getMoves function
 */
vector<PieceMoves> Board::getMoves() const noexcept
{
  return vector<PieceMoves>();
}

/**
 * TODO: implement moveCopy
 */
Board Board::moveCopy(const Square &square1, const Square &square2) const noexcept
{
  return Board();
}

/**
 * TODO: implement moveRef
 */
Board& Board::moveRef(const Square &square1, const Square &square2) noexcept
{
  return *this;
}

/**
 * TODO: implement movePawn
 */
vector<PieceMoves> Board::movePawn(dim_type row, dim_type column) const noexcept
{
  return vector<PieceMoves>();
}

/**
 * TODO: implement moveKnight
 */
vector<PieceMoves> Board::moveKnight(dim_type row, dim_type column) const noexcept
{
  return vector<PieceMoves>();
}

/**
 * TODO: implement moveBishop
 */
vector<PieceMoves> Board::moveBishop(dim_type row, dim_type column) const noexcept
{
  return vector<PieceMoves>();
}

/**
 * TODO: implement moveRook
 */
vector<PieceMoves> Board::moveRook(dim_type row, dim_type column) const noexcept
{
  return vector<PieceMoves>();
}

/**
 * TODO: implement moveQueen
 */
vector<PieceMoves> Board::moveQueen(dim_type row, dim_type column) const noexcept
{
  return vector<PieceMoves>();
}

/**
 * TODO: implement moveKing
 */
vector<PieceMoves> Board::moveKing(dim_type row, dim_type column) const noexcept
{
  return vector<PieceMoves>();
}

/**
 * TODO: implement getBoardsFromMoves function
 */
vector<Board> Board::getBoardsFromMoves() const noexcept
{
  return vector<Board>();
}

/**
 * TODO: implement makeMoveCopy function
 */
Board
Board::makeMoveCopy(const Square &square1, const Square &square2) const noexcept
{
  return Board();
}

/**
 * TODO: implement makeMove function
 */
Board& Board::makeMove(const Square &square1, const Square &square2) noexcept
{
  return *this;
}

/**
 * TODO: implement undo function
 */
Board& Board::undo() noexcept
{
  return *this;
}

/**
 * TODO: implement whiteCount function
 */
PieceCount Board::whiteCount() const noexcept
{
  return PieceCount();
}

/**
 * TODO: implement blackCount function
 */
PieceCount Board::blackCount() const noexcept
{
  return PieceCount();
}

/**
 * TODO: implement lastMove function
 */
pair<Square, Square> Board::lastMove() const noexcept
{
  return std::make_pair(Squre(), Square());
}

/**
 * TODO: implement operator() function
 */
Square Board::operator()(dim_type row, dim_type column) const noexcept
{
  return Square();
}

iterator Board::begin() const noexcept
{
  return iterator(this);
}

iterator Board::end() const noexcept
{
  return iterator();
}

/**
 * TODO: implement output operator for Board
 */
std:ostream& operator<<(std:ostream &os, const Board &board)
{
  return os;
}

bool operator==(const Board &boar1, const Board &board2) noexcept
{
  return board1.mColorMove == board2.mColorMove
      && std::equal(board1.begin(), board1.end(), board2.begin());
}

bool operator!=(const Board &boar1, const Board &board2) noexcept
{
  return !(board1 == board2);
}

// BoardIterator

BoardIterator::BoardIterator(const Board *board)
  : mBoardPtr(board),
    mIndex(0)
{
  assert(mBoardPtr != nullptr);
}

BoardIterator::BoardIterator(const Board *board, int)
  : mBoardPtr(board),
    mIndex(LAST_INDEX)
{
  assert(mBoardPtr != nullptr);
}

BoardIterator& BoardIterator::operator++()
{
  if (mIndex >= LAST_INDEX)
    throw BoardIteratorError("Error: iterator cannot move beyond board");

  ++mIndex;
  return *this;
}

BoardIterator BoardIterator::operator++(int)
{
  if (mIndex >= LAST_INDEX)
    throw BoardIteratorError("Error: iterator cannot move beyond board");

  BoardIterator bi(*this);
  ++(*this);
  return bi;
}

BoardIterator& BoardIterator::operator+=(BaordIterator::difference_type value)
{
  mIndex += value;
  if (mIndex < static_cast<difference_type>(0)
      || mIndex > static_cast<difference_type>(LAST_INDEX))
    throw BoardIteratorError("Error: iterator cannot move beyond board");

  return *this;
}

BoardIterator& BoardIterator::operator-=(BaordIterator::difference_type value)
{
  mIndex -= value;
  if (mIndex < static_cast<difference_type>(0)
      || mIndex > static_cast<difference_type>(LAST_INDEX))
    throw BoardIteratorError("Error: iterator cannot move beyond board");

  return *this;
}

BoardIterator::value_type BoardIterator::operator*() const
{
  if (mIndex >= LAST_INDEX)
    throw BoardIteratorError("Error: cannot access square beyond board");

  auto row = static_cast<Board::dim_type>(mIndex) / Board::BOARD_DIM;
  auto col = static_cast<Board::dim_type>(mIndex) % Board::BOARD_DIM;
  auto code = mBoardPtr->get(row, col);
  return Square(row, col, getPieceCode(pcode), getPieceColor(pcode));
}

} // namespace zoor
