/**
 * @file piececode.hh
 * @author Omar A Serrano
 * @date 2015-12-24
 */

#ifndef _PIECECODES_H
#define _PIECECODES_H

namespace zoor {

/**
 * Represents a piece on the board.
 *
 * Since each piece on a board is represented in a byte, the type for
 * each PieceCode is an unsigned char.
 */
enum class PieceCode: unsigned char
{
  NONE = 0,
  PAWN,
  KNIGHT,
  BISHOP,
  ROOK,
  QUEEN,
  KING
};

/**
 * Represents the color of a piece. 
 *
 * The PieceColor can be logically ORed with a PiceCode to
 * make a piece have color.
 */
enum class PieceColor: unsigned char
{
  NONE,
  WHITE = 1 << 4,
  BLACK = 1 << 5
};

/**
 * Represents the value of a piece.
 */
enum class PieceValue: unsigned short
{
  PAWN = 1,
  KNIGHT = 3,
  BISHOP = KNIGHT,
  ROOK = 5,
  QUEEN = 9,
  KING = ~0
};

/**
 * Gets the short name of a piece.
 *
 * The short piece names are N, P, KN, B, R, Q, and KI. The letters correspond to
 * @c PieceCode values for none, pawn, knight, bishop, rook, queen, and king.
 *
 * @param piece The @c PieceCode.
 * @return A string representing the one letter intial of the piece.
 */
string pieceToString(const PieceCode &piece) noexcept;

/**
 * Gets the long name of a given piece.
 *
 * The long piece names are NONE, PAWN, KNIGHT, BISHOT, ROOK, QUEEN, and KING. The
 * letters correspond to @c PieceCode values for none, pawn, knight, bishop, rook,
 * queen, and king.
 *
 * @param piece The @c PieceCode.
 * @return A string representing the long name of the piece.
 */
string pieceToStringLong(const PieceCode &piece) noexcept;

/**
 * Gets the one letter initial for the color of a piece.
 *
 * The one letter initials for colors are N, W, and B for none, white, and black.
 *
 * @param color The @c PieceColor.
 * @return A string representing the one letter intial of the color.
 */
string colorToString(const PieceColor &color) noexcept;
string colorToStringLong(const PieceColor &color) noexcept;

} // namespace zoor

#endif 
