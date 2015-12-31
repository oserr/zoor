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

namespace zoor {

/**
 * Represents a position in the baord.
 */
class Square
{
  friend std::ostream& operator<<(std::ostream&, const Square&);
  friend bool operator==(const Square&, const Square&) noexcept;

public:
  using dim_type = unsigned short;
  static constexpr dim_type BOARD_DIM = 8;
  
  // standard copy control
  Square() noexcept = default
  Square(const Square&) noexcept = default
  Square(Square&&) noexcept = default
  Square& operator=(const Square&) noexcept = default
  Square& operator=(Square&&) noexcept = default
  ~Square() noexcept = default;
  // custom constructor
  Square(dim_type, dim_type);

  // getters
  dim_type row() const noexcept;
  dim_type col() const noexcept;

  // setters
  Square& setRow(dim_type) noexcept;
  Square& setCol(dim_type) noexcept;

private:
  dim_type mRow;
  dim_type mCol;
};

/**
 * @brief Represents a list of moves for a given piece from a particular position in
 * the board.
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
  using iterator = std::vector<MoveTo>::iterator;
  using const_iterator = std::vector<MoveTo>::const_iterator;
  using size_type = std::vector<MoveTo>::size_type;
  
  // copy control
  PieceMoves();
  PieceMoves(const PieceMoves&);
  PieceMoves(PieceColor, PieceCode, Square);
  PieceMoves(PieceColor, PieceCode, Square, std::vector<MoveTo>);
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
  
private:
  PieceColor mColor;
  PieceCode mPiece;
  Square mSquare;
  std::vector<MoveTo> mMoves;

public:
  /**
   * A move to a given position.
   */
  class MoveTo
  {
    friend std::ostream& operator<<(std::ostream&, const MoveTo&);
    friend bool operator==(const MoveTo&, const MoveTo&) noexcept;
    friend class PieceMoves;

  private:
    PieceColor mColor;
    PieceCode mPiece;
    Square mSquare;
    unique_ptr<PieceMoves> mParent;

  public:
    /* copy control */
    MoveTo() = default;
    MoveTo(PieceColor, PieceCode, const Square&) = default;
    MoveTo(PieceColor, PieceCode, Square&&) = default;
    MoveTo(const MoveTo&) = default;
    MoveTo(MoveTo&&) noexcept = default;
    MoveTo& operator=(const MoveTo&) = default;
    MoveTo& operator=(MoveTo&&) noexcept = default;
    ~MoveTo() noexcept = default;

    /* getters */
    PieceColor color() const noexcept;
    PieceCode piece() const noexcept;
    Square square() const noexcept;

    // TODO: implement as template with universal paramter T&&
    // setters with lvalue paramters
    MoveTo& setColor(const PieceColor&) noexcept;
    MoveTo& setPiece(const PieceCode&) noexcept;
    MoveTo& setSquare(const Square&) noexcept;

    // implement as template with universal paramter T&&
    // setters with rvalue paramters
    MoveTo& setColor(PieceColor&&) noexcept;
    MoveTo& setPiece(PieceCode&&) noexcept;
    MoveTo& setSquare(Square&&) noexcept;
  };
};

} // namespace zoor

#endif // _PIECEMOVES_H
