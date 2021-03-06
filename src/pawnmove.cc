////////////////////////////////////////////////////////////////////////////////
//! @file pawnmove.cc
//! @author Omar A Serrano
//! @date 2016-09-09
////////////////////////////////////////////////////////////////////////////////

//
// STL
//
#include <array>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

//
// zoor
//
#include "basictypes.hh"
#include "board.hh"
#include "pawnmove.hh"
#include "piecemove.hh"

namespace zoor {

PawnMove::PawnMove(dim_t row, dim_t col, const Board &board) noexcept
  : IMove(row, col, board)
{
  assert(isPawn(mBoard(row, col).piece()));
  mDeltas = deltas();
}

Piece
PawnMove::piece() const noexcept
{
  return Piece::P;
}

bool
PawnMove::canMove(dim_t row, dim_t col) const noexcept
{
  return isLegal(row, col) ? _canMove(row, col) : false;
}

std::vector<PieceMove>
PawnMove::move(dim_t row, dim_t col) const
{
  using MoveList = std::vector<PieceMove>;

  if (isLegal(row, col)) {
    if (isForward(row, col))
      return MoveList{{_move(row, col)}};
    else if (isPromotion(row, col))
      return promote(row, col);
    else if (isAttack(row, col))
      return MoveList{{_move(row, col)}};
    else if (isEnPassant(row, col))
      return MoveList{{enPassant(row, col)}};
  }

  throw std::logic_error("Move is not legal");
}

std::vector<PieceMove>
PawnMove::moves() const
{
  std::vector<PieceMove> moveList;

  for (const auto delta : mDeltas) {
    dim_t row, col;
    std::tie(row, col) = delta;
    if (isForward(row, col))
      moveList.emplace_back(_move(row, col));
    else if (isPromotion(row, col)) {
      auto ml = promote(row, col);
      std::move(std::begin(ml), std::end(ml), std::back_inserter(moveList));
    }
    else if (isAttack(row, col))
      moveList.emplace_back(_move(row, col));
    else if (isEnPassant(row, col))
      moveList.emplace_back(enPassant(row, col));
  }

  return moveList;
}

PieceMove
PawnMove::_move(dim_t row, dim_t col) const
{
  PieceMove pm(mRow, mCol, Piece::P, mColor);
  pm.dPiece(row, col, mBoard(row, col).code());
  return pm;
}

bool
PawnMove::isPromotion(dim_t row, dim_t col) const noexcept
{
  if (col != mCol)
    return isWhite(mColor) ? row == 7 : row == 0;
  return false;
}

std::vector<PieceMove>
PawnMove::promote(dim_t row, dim_t col) const
{
  assert(mBoard(row, col).color() != mColor);
  const static std::array<Piece, 4> pieces = {
    Piece::N,
    Piece::B,
    Piece::R,
    Piece::Q
  };
  auto capture = mBoard(row, col).code();
  std::vector<PieceMove> moveList(4);
  for (auto p : pieces) {
    moveList.emplace_back(row, col, Piece::P, mColor);
    auto& pMove = moveList.back();
    pMove.dPiece(row, col, capture);
    pMove.xPiece(row, col, p, mColor);
  }

  return moveList;
}

bool
PawnMove::_canMove(dim_t row, dim_t col) const noexcept
{
  return isForward(row, col) or isAttack(row, col) or isEnPassant(row, col);
}

bool
PawnMove::isFirstMove() const noexcept
{
  return (isWhite(mColor) and mRow == 1)
      or (isBlack(mColor) and mRow == 6);
}

std::pair<dim_t, dim_t>
PawnMove::jumpTwo() const noexcept
{
  auto row = mRow + 2 * delta(mColor);
  return {row, mCol};
}

bool
PawnMove::isEnPassant(dim_t row, dim_t col) const noexcept
{
  assert(mBoard(row, col).color() != mColor);

  if (mCol == col)
    return false;

  const auto pc = mBoard(row, col).code();
  if (isPiece(pc))
    return false;

  dim_t enPassantRow;
  dim_t captureRow;
  dim_t pawnRow;

  if (isWhite(mColor)) {
    enPassantRow = 5;
    captureRow = 4;
    pawnRow = 1;
  } else {
    enPassantRow = 2;
    captureRow = 3;
    pawnRow = 6;
  }

  if (enPassantRow != row)
    return false;

  if (not isSame(pc, mColor) and isPawn(pc)) {
    auto pm = mBoard.lastMove();
    if (isPawn(pm.sPiece())
      and pm.sRow() == pawnRow
      and pm.sColumn() == col
      and pm.dColumn() == col
      and pm.dRow() == captureRow)
    return true;
  }

  return false;
}

PieceMove
PawnMove::enPassant(dim_t row, dim_t col) const noexcept
{
  const auto code = mColor | Piece::P;
  PieceMove pm(mRow, mCol, code, row, col);
  row += -1 * delta(mColor);
  pm.xPiece(row, col, mBoard(row, col).code());
  return pm;
}

std::vector<std::pair<dim_t, dim_t>>
PawnMove::deltas() const
{
  auto del = delta(mColor) + mRow;
  std::array<std::pair<dim_t, dim_t>, 3> arr = {{
    {del, mCol},
    {del, mCol+1},
    {del, mCol-1}
  }};
  std::vector<std::pair<dim_t, dim_t>> vec;
  for (auto d : arr) {
    if (inBound(d.first, d.second))
      vec.emplace_back(d.first, d.second);
  }
  if (isFirstMove())
    vec.emplace_back(jumpTwo());

  return vec;
}

bool
PawnMove::isAttack(dim_t row, dim_t col) const noexcept
{
  auto code = mBoard(row, col).code();
  return col != mCol and isPiece(code) and not isSame(code, mColor);
}

bool
PawnMove::isForward(dim_t row, dim_t col) const noexcept
{
  return col == mCol and notPiece(mBoard(row, col).piece());
}

bool
PawnMove::isLegal(dim_t row, dim_t col) const noexcept
{
  auto last = std::end(mDeltas);
  auto rowcol = std::make_pair(row, col);
  return last != find(std::begin(mDeltas), last, rowcol);
}

} // namespace zoor
