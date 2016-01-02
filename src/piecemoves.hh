/**
 * @file piecemoves.hh
 * @author Omar A Serrano
 * @date 2015-12-29
 */
#ifndef _PIECEMOVES_H
#define _PIECEMOVES_H

#include <vector>
#include <iostream>
#include <memory>

#include "square.hh"

namespace zoor {

/**
 * @brief Represents the list of legal moves that are possible for a given piece from
 * a given square on a board.
 *
 * @c PieceMoves is aware of the piece type, the location in the board, and whether
 * a given move is legal.
 */
class PieceMoves
{
  friend std::ostream& operator<<(std::ostream&, const PieceMoves&) noexcept;
  friend bool operator==(const PieceMoves&, const PieceMoves&) noexcept;

public:
  // typedefs
  using iterator = std::vector<Square>::iterator;
  using const_iterator = std::vector<Square>::const_iterator;
  using size_type = std::vector<Square>::size_type;

  // custom constructors
  PieceMoves(PieceColor, PieceCode, Square);
  PieceMoves(PieceColor, PieceCode, Square, std::vector<Square>);
  
  // standard copy control
  PieceMoves();
  PieceMoves(const PieceMoves&);
  PieceMoves(PieceMoves&&) = default;
  PieceMoves& operator=(const PieceMoves&) = default;
  PieceMoves& operator=(PieceMoves &&) = default;
  ~PieceMoves() noexcept = default;

  // interface
  PieceMoves& setColor(PieceColor) noexcept;
  PieceMoves& setPiece(PieceCode) noexcept;
  PieceMoves& setSquare(Square) noexcept;

  PieceColor color() const noexcept;
  PieceCode piece() const noexcept;
  Square square(Square) const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;

  // iterator access
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() noexcept;
  const_iterator cend() noexcept;

  // adding and removing Square elements
  PieceMoves& push_back(const Square&);
  PieceMoves& pop_back();
  PieceMoves& clear();

  // TODO: add emplace_back

private:
  Square mSquare;
  std::vector<Square> mMoves;
};

} // namespace zoor

#endif // _PIECEMOVES_H
