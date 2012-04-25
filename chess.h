/* 
 * File:   board.h
 * Author: alexfrost
 *
 * Created on April 5, 2012, 10:42 AM
 */
#ifndef BOARD_H
#define	BOARD_H
#include "chess_pieces.h"

const int OCCUPIED = 1;
const int EMPTY = 0;

class Space{// spaces on the chessboard
public:
  int state;
  Piece *crnt_piece;
  Space();
  bool occupied();
  void pieceOn(Piece *p);
  void pieceOff();
};

class Player{
private:
  Piece *pieces[16];
public:
  int color; // -1 or 1 denotes black or white respectively
  int front_row, back_row;
  int alive;
  int player_state;
  //see if can still just use an multi-array of Spaces instead of an entire class
  Player(int color, Space board[][8]);
  Piece* getPiece(int index);
  void movePiece(Space[][8], Piece *p, Coord new_pos);
  int takeTurn(Space board[][8]);
};
#endif	/* BOARD_H */
