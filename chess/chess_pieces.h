/* 
 * File:   chess_pieces.h
 * Author: alexfrost
 *
 * Created on April 5, 2012, 9:30 AM
 */
#ifndef CHESS_PIECES_H
#define	CHESS_PIECES_H

class Space;// so chess pieces know what Space board[][] is

const int BLACK = -1;
const int WHITE = 1;

const int PLAYING = 1;
const int LOST = 0;

const int ALIVE = 1;
const int DEAD = 0;

const int PAWN = 0;
const int ROOK = 1;
const int KNIGHT = 2;
const int BISHOP = 3;
const int KING = 4;
const int QUEEN = 5;

static int self = WHITE;
static int opponent = BLACK;
static int turn;

class Coord{
public:
  int x;
  int y;
  Coord();
  Coord(int x, int y);
};
class Piece{
private:
  int color;
  int state;
public:
  int opponent;
  int ident;
  Coord pos;
  Coord moves[27];
  Piece();
  Piece(int r, int c, int color);
  Coord getPosition();
  int getX();
  int getY();
  int getIdentity();
  int getColor();
  int isAlive();
  virtual int lookUpMoves(Space board[][8]) = 0;// specific to each piece 
  void addmove(int i, Coord mov);
  void move(Coord pos);
  void die();
};
class Pawn : public Piece{
public:
  int moved;
  // black(-1) can move up and white(1) can move down
  Pawn(int r, int c, int color);
  int lookUpMoves(Space board[][8]);
};
class Rook : public Piece{
public:
  Rook(int r, int c, int color);
  int lookUpMoves(Space board[][8]);
};
class Knight : public Piece{
public:
  Knight(int r, int c, int color);
  int lookUpMoves(Space board[][8]);
};
class Bishop : public Piece{
public:
  Bishop(int r, int c, int color);
  int lookUpMoves(Space board[][8]);
};
class King : public Piece{
public:
  King(int r, int c, int color);
  int lookUpMoves(Space board[][8]);
};
class Queen : public Piece{
public:
  Queen(int r, int c, int color);
  int lookUpMoves(Space board[][8]);
};
#endif	/* CHESS_PIECES_H */