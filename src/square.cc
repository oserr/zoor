/**
 * @file square.cc
 * @author Omar A Serrano
 * @data 2015-12-31
 */

#include <iostream>
#include <cassert>

#include "square.hh"
#include "piececode.hh"

namespace zoor {

using dim_type = Square::dim_type;

// default ctor
Square::Square() noexcept
  : mPiece(PieceCode::NONE),
    mColor(PieceColor::NONE),
    mRow(),
    mColumn() {}

// two param ctor
Square::Square(dim_type row, dim_type column) noexcept
  : mPiece(PieceCode::NONE),
    mColor(PieceColor::NONE),
    mRow(row),
    mColumn(column)
{
  assert(isInBound(row, column));
}

// three param ctor
Square::Square(dim_type row, dim_type column, piececode_t code) noexcept
  : mPiece(getPieceCode(code)),
    mColor(getPieceColor(code)),
    mRow(row),
    mColumn(column)
{
  assert(isInBound(row, column));
}

// 4 param ctor
Square::Square
  (dim_type row,
   dim_type column,
   PieceCode piece,
   PieceColor color) noexcept
  : mPiece(piece),
    mColor(color),
    mRow(row),
    mColumn(column)
{
  assert(isInBound(row, column));
}

// get the row
dim_type Square::row() const noexcept
{
  return mRow;
}

// get the column
dim_type Square::column() const noexcept
{
  return mColumn;
}

// get the piece type
PieceCode Square::piece() const noexcept
{
  return mPiece;
}

// get the piece color
PieceColor Square::color() const noexcept
{
  return mColor;
}

// get the bit code for the piece and color
piececode_t Square::code() const noexcept
{
  return mColor | mPiece;
}

// set the row
Square& Square::setRow(dim_type row) noexcept
{
  assert(isInBound(row));
  mRow = row;
  return *this;
}

// set the column
Square& Square::setColumn(dim_type column) noexcept
{
  assert(isInBound(column));
  mColumn = column;
  return *this;
}

// set the piece
Square& Square::setPiece(PieceCode piece) noexcept
{
  mPiece = piece;
  return *this;
}

// set the color
Square& Square::setColor(PieceColor color) noexcept
{
  mColor = color;
  return *this;
}

// set the piece and color
Square& Square::setPieceCode(piececode_t code) noexcept
{
  mPiece = getPieceCode(code);
  mColor = getPieceColor(code);
  return *this;
}

// set the row and column of the square
Square& Square::setLocation(dim_type row, dim_type column) noexcept
{
  assert(isInBound(row, column));
  mRow = row;
  mColumn = column;
  return *this;
}

// check if position is valid
bool Square::isInBound(dim_type position) noexcept
{
  return position >= 0 && position < BOARD_DIM;
}

// check if row and column are valid
bool Square::isInBound(dim_type row, dim_type column) noexcept
{
  return row >= 0 && row < BOARD_DIM
      && column >= 0 && column < BOARD_DIM;
}

bool operator==(const Square& square1, const Square& square2) noexcept
{
  return square1.mPiece == square2.mPiece
      && square1.mColor == square2.mColor
      && square1.mRow == square2.mRow
      && square1.mColumn == square2.mColumn;
}

bool operator!=(const Square& square1, const Square& square2) noexcept
{
  return !(square1 == square2);
}

std::ostream& operator<<(std::ostream& os, const Square& square)
{
  os << "("
     << square.mPiece << ", "
     << square.mColor << ", "
     << square.mRow << ", "
     << square.mColumn
     << ")";
  return os;
}

} // namespace zoor
