#include "chess.h"
#include "chess_pieces.h"
#include <iostream>

using namespace std;

Space chessBoard[8][8] = {
  {Space(), Space(), Space(), Space(), Space(), Space(), Space(), Space()},
  {Space(), Space(), Space(), Space(), Space(), Space(), Space(), Space()},
  {Space(), Space(), Space(), Space(), Space(), Space(), Space(), Space()},
  {Space(), Space(), Space(), Space(), Space(), Space(), Space(), Space()},
  {Space(), Space(), Space(), Space(), Space(), Space(), Space(), Space()},
  {Space(), Space(), Space(), Space(), Space(), Space(), Space(), Space()},
  {Space(), Space(), Space(), Space(), Space(), Space(), Space(), Space()},
  {Space(), Space(), Space(), Space(), Space(), Space(), Space(), Space()},
};

// Coord members
Coord::Coord(){
  this->x = 9;
  this->y = 9;
}
Coord::Coord(int x, int y){
  this->x = x;
  this->y = y;
}

// Piece members
Piece::Piece(){}
Piece::Piece(int r, int c, int color){
  this->pos = Coord(r, c);
  this->color = color;
  this->opponent = (-1 * color);
  this->state = ALIVE;
}
Coord Piece::getPosition(){
  return this->pos;
}
int Piece::getX(){
  return this->pos.x;
}
int Piece::getY(){
  return this->pos.y;
}
int Piece::getIdentity(){
  return this->ident;
}
int Piece::getColor(){
  return this->color;
}
int Piece::isAlive(){
  return this->state;
}
int Piece::lookUpMoves(Space board[][8]){};// specific to each piece 
void Piece::addmove(int i, Coord mov){
  this->moves[i] = mov;
}
void Piece::move(Coord pos){
//    Controller.movePiece(this, pos); // need to 
  this->pos = pos;
}
void Piece::die(){
  this->state = DEAD;
}

// Pawn members
Pawn::Pawn(int r, int c, int color) : Piece (r, c, color){  
  this->ident = PAWN;
  this->moved = 0;
}
int Pawn::lookUpMoves(Space board[][8]){
  int n = 0; // keep track of number of moves recorded
  int ahead = this->getX() + this->getColor();
  // <editor-fold defaultstate="collapsed" desc="First-turn move">
  if (moved == 0) {//first turn move can two spaces
    this->moves[n] = Coord(this->getX() + (2 * this->getColor()), this->getY());
    this->moved = 1;
    n++;
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Straight move">
  if (board[ahead][this->getY()].state == EMPTY) {
    this->moves[n] = Coord(ahead, this->getY()); //normal straight move
    this->moved = 1;
    n++;
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Diagonal Attack Left">
  if(this->getY() > 0) {
    //see if enemy piece is in that spot
    if(board[ahead][this->getY() - 1].occupied()){
      if(board[ahead][this->getY() - 1].crnt_piece->getColor() == this->opponent){
        this->moves[n] = Coord(ahead, this->getY() - 1);
        this->moved = 1;
        n++;
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Diagonal Attack Right">
  if (this->getY() < 7) {
    //see if enemy piece is in that spot
    if (board[ahead][this->getY() + 1].occupied()) {
      if (board[ahead][this->getY() + 1].crnt_piece->getColor() == this->opponent) {
        this->moves[n] = Coord(ahead, this->getY() + 1);
        this->moved = 1;
        n++;
      }
    }
  }// </editor-fold>
  for(n; n < 27; n++){
    moves[n] = Coord();
  }
  return 0;
}

// Rook members
Rook::Rook(int r, int c, int color) : Piece(r, c, color){
    this->ident = ROOK;
}
int Rook::lookUpMoves(Space board[][8]){
  int n = 0;
  // <editor-fold defaultstate="collapsed" desc="Up moves">
  for(int y = this->getY() + 1; y <= 7; y++) {
    if(!board[this->getX()][y].occupied()){
      moves[n] = Coord(this->getX(), y);
      n++;
    }else{
      if(board[this->getX()][y].crnt_piece->getColor() == this->opponent){
        moves[n] = Coord(this->getX(), y);
        n++;
        break;
      }else{
        break;
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Down moves">
  for(int y = this->getY() - 1; y >= 0; y--) {
    if(!board[this->getX()][y].occupied()){
      moves[n] = Coord(this->getX(), y);
      n++;
    }else{
      if(board[this->getX()][y].crnt_piece->getColor() == this->opponent){
        moves[n] = Coord(this->getX(), y);
        n++;
        break;
      }else{
        break;
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Right moves">
  for(int x = this->getX() + 1; x <= 7; x++) {
    if(!board[x][this->getY()].occupied()){
      moves[n] = Coord(x, this->getY());
      n++;
    }else{
      if(board[x][this->getY()].crnt_piece->getColor() == this->opponent){
        moves[n] = Coord(x, this->getY());
        n++;
        break;
      }else{
        break;
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Left moves">
  for(int x = this->getX() - 1; x >= 0; x--){
    if(!board[x][this->getY()].occupied()){
      moves[n] = Coord(x, this->getY());
      n++;
    }else{
      if(board[x][this->getY()].crnt_piece->getColor() == this->opponent){
        moves[n] = Coord(x, this->getY());
        n++;
        break;
      }else{
        break;
      }
    }
  }// </editor-fold>
  for(n; n < 27; n++){
    moves[n] = Coord();
  }
}

// Knight members
Knight::Knight(int r, int c, int color) : Piece(r, c, color){
  this->ident = KNIGHT;
}
int Knight::lookUpMoves(Space board[][8]){
  int n = 0;
  // <editor-fold defaultstate="collapsed" desc="Down">
  if (this->getY() < 6) {
    // <editor-fold defaultstate="collapsed" desc="Down-right">
    if (this->getX() < 7) {
      if (board[this->getX() + 1][this->getY() + 2].occupied()) {
        if (board[this->getX() + 1][this->getY() + 2].crnt_piece->getColor() == this->opponent) {
          moves[n] = Coord(this->getX() + 1, this->getY() + 2);
          n++;
        }
      }else{
        moves[n] = Coord(this->getX() + 1, this->getY() + 2);
        n++;
      }
    }// </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Down-left">
    if (this->getX() > 0) {
      if (board[this->getX() - 1][this->getY() + 2].occupied()) {
        if (board[this->getX() - 1][this->getY() + 2].crnt_piece->getColor() == this->opponent) {
          moves[n] = Coord(this->getX() - 1, this->getY() + 2);
          n++;
        }
      }else{
        moves[n] = Coord(this->getX() - 1, this->getY() + 2);
        n++;
      }
    }// </editor-fold>
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Up">
  if (this->getY() > 1) {
    // <editor-fold defaultstate="collapsed" desc="Up-left">
    if (this->getX() > 0) {
      if (board[this->getX() - 1][this->getY() - 2].occupied()) {
        if (board[this->getX() - 1][this->getY() - 2].crnt_piece->getColor() == this->opponent) {
          moves[n] = Coord(this->getX() - 1, this->getY() - 2);
          n++;
        }
      }else{
        moves[n] = Coord(this->getX() - 1, this->getY() - 2);
        n++;
      }
    }// </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Up-right">
    if (this->getX() < 7) {
      if (board[this->getX() + 1][this->getY() - 2].occupied()) {
        if (board[this->getX() + 1][this->getY() - 2].crnt_piece->getColor() == this->opponent) {
          moves[n] = Coord(this->getX() + 1, this->getY() - 2);
          n++;
        }
      }else{
        moves[n] = Coord(this->getX() + 1, this->getY() - 2);
        n++;
      }
    }// </editor-fold>
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Right">
  if (this->getX() < 6) {
    // <editor-fold defaultstate="collapsed" desc="Right-up">
    if (this->getY() > 0) {
      if (board[this->getX() + 2][this->getY() - 1].occupied()) {
        if (board[this->getX() + 2][this->getY() - 1].crnt_piece->getColor() == this->opponent) {
          moves[n] = Coord(this->getX() + 2, this->getY() - 1);
          n++;
        }
      }else{
        moves[n] = Coord(this->getX() + 2, this->getY() - 1);
        n++;
      }
    }// </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Right-down">
    if (this->getY() < 7) {
      if (board[this->getX() + 2][this->getY() + 1].occupied()) {
        if (board[this->getX() + 2][this->getY() + 1].crnt_piece->getColor() == this->opponent) {
          moves[n] = Coord(this->getX() + 2, this->getY() + 1);
          n++;
        }
      }else{
        moves[n] = Coord(this->getX() + 2, this->getY() + 1);
        n++;
      }
    }// </editor-fold>
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Left">
  if (this->getX() > 1) {
    // <editor-fold defaultstate="collapsed" desc="Left-up">
    if (this->getY() > 0) {
      if (board[this->getX() - 2][this->getY() - 1].occupied()) {
        if (board[this->getX() - 2][this->getY() - 1].crnt_piece->getColor() == this->opponent) {
          moves[n] = Coord(this->getX() - 2, this->getY() - 1);
          n++;
        }
      }else{
        moves[n] = Coord(this->getX() - 2, this->getY() - 1);
        n++;
      }
    }// </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Left-down">
    if (this->getY() < 7) {
      if (board[this->getX() - 2][this->getY() + 1].occupied()) {
        if (board[this->getX() - 2][this->getY() + 1].crnt_piece->getColor() == this->opponent) {
          moves[n] = Coord(this->getX() - 2, this->getY() + 1);
          n++;
        }
      }else{
        moves[n] = Coord(this->getX() - 2, this->getY() + 1);
        n++;
      }
    }// </editor-fold>
  }// </editor-fold>
  for(n; n < 27; n++){
    moves[n] = Coord();
  }
}

// Bishop members
Bishop::Bishop(int r, int c, int color) : Piece(r, c, color){
  this->ident = BISHOP;
}
int Bishop::lookUpMoves(Space board[][8]){
  int x, y;
  int n = 0;
  // <editor-fold defaultstate="collapsed" desc="Up-left">
  x = this->getX();
  for (y = this->getY() - 1; y >= 0; y--) {
    x--;
    if(x >= 0){
      if (!board[x][y].occupied()) {
        this->moves[n] = Coord(x, y);
        n++;
      }else{
        if (board[x][y].crnt_piece->getColor() == this->opponent) {
          this->moves[n] = Coord(x, y);
          n++;
          break;
        }else{
          break;
        }
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Up-right">
  x = this->getX();
  for (y = this->getY() - 1; y >= 0; y--) {
    x++;
    if(x <= 7){
      if (!board[x][y].occupied()) {
        this->moves[n] = Coord(x, y);
        n++;
      }else{
        if (board[x][y].crnt_piece->getColor() == this->opponent) {
          this->moves[n] = Coord(x, y);
          n++;
          break;
        }else{
          break;
        }
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Down-left">
  x = this->getX();
  for (y = this->getY() + 1; y <= 7; y++) {
    x--;
    if(x >= 0){
      if (!board[x][y].occupied()) {
        this->moves[n] = Coord(x, y);
        n++;
      }else{
        if (board[x][y].crnt_piece->getColor() == this->opponent) {
          this->moves[n] = Coord(x, y);
          n++;
          break;
        }else{
          break;
        }
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Down-right">
  x = this->getX();
  for (y = this->getY() + 1; y <= 7; y++) {
    x++;
    if(x <= 7){
      if (!board[x][y].occupied()) {
        this->moves[n] = Coord(x, y);
        n++;
      }else{
        if (board[x][y].crnt_piece->getColor() == this->opponent) {
          this->moves[n] = Coord(x, y);
          n++;
          break;
        }else{
          break;
        }
      }
    }
  }// </editor-fold>
  for(n; n < 27; n++){
    moves[n] = Coord();
  }
}

// King members
King::King(int r, int c, int color) : Piece(r, c, color){
  this->ident = KING;
}
int King::lookUpMoves(Space board[][8]){
  int n = 0;
  int x = this->getX();
  int y = this->getY();
  // <editor-fold defaultstate="collapsed" desc="Down">
  if (y < 7) {
    if (!board[x][y + 1].occupied()) {
      this->moves[n] = Coord(x, y + 1);
      n++;
    }else{   
      if(board[x][y + 1].crnt_piece->getColor() == this->opponent){
        this->moves[n] = Coord(x, y + 1);
        n++;
      }
    }
    // <editor-fold defaultstate="collapsed" desc="Down-Left">
    if (x > 0) {
      if (!board[x - 1][y + 1].occupied()) {
        this->moves[n] = Coord(x - 1, y + 1);
        n++;
      }else{   
        if(board[x - 1][y + 1].crnt_piece->getColor() == this->opponent){
          this->moves[n] = Coord(x - 1, y + 1);
          n++;
        }
      }
    }// </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Down-Right">
    if (x < 7) {
      if (!board[x + 1][y + 1].occupied()) {
        this->moves[n] = Coord(x + 1, y + 1);
        n++;
      }else{   
        if(board[x + 1][y + 1].crnt_piece->getColor() == this->opponent){
          this->moves[n] = Coord(x + 1, y + 1);
          n++;
        }
      }
    }// </editor-fold>
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Left">
  if (x > 0) {
    if (!board[x - 1][y].occupied()) {
      this->moves[n] = Coord(x - 1, y);
      n++;
    }else{   
      if(board[x - 1][y].crnt_piece->getColor() == this->opponent){
        this->moves[n] = Coord(x - 1, y);
        n++;
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Right">
  if (x < 7) {
    if (!board[x + 1][y].occupied()) {
      this->moves[n] = Coord(x + 1, y);
      n++;
    }else{   
      if(board[x + 1][y].crnt_piece->getColor() == this->opponent){
        this->moves[n] = Coord(x + 1, y);
        n++;
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Up">
  if (y > 0) {
    if (!board[x][y - 1].occupied()) {
      this->moves[n] = Coord(x, y - 1);
      n++;
    }else{   
      if(board[x][y - 1].crnt_piece->getColor() == this->opponent){
        this->moves[n] = Coord(x, y - 1);
        n++;
      }
    }
    // <editor-fold defaultstate="collapsed" desc="Up-Left">
    if (x > 0) {
      if (!board[x - 1][y - 1].occupied()) {
        this->moves[n] = Coord(x - 1, y - 1);
        n++;
      }else{   
        if(board[x - 1][y - 1].crnt_piece->getColor() == this->opponent){
          this->moves[n] = Coord(x - 1, y - 1);
          n++;
        }
      }
    }// </editor-fold>
    // <editor-fold defaultstate="collapsed" desc="Up-Right">
    if (x < 7) {
      if (!board[x + 1][y - 1].occupied()) {
        this->moves[n] = Coord(x + 1, y - 1);
        n++;
      }else{   
        if(board[x + 1][y - 1].crnt_piece->getColor() == this->opponent){
          this->moves[n] = Coord(x + 1, y - 1);
          n++;
        }
      }
    }// </editor-fold>
  }// </editor-fold>
  for(n; n < 27; n++){
    moves[n] = Coord();
  }
}

// Queen members
Queen::Queen(int r, int c, int color) : Piece(r, c, color){
  this->ident = QUEEN;
}
int Queen::lookUpMoves(Space board[][8]){
  int x, y;
  int n = 0;
  // <editor-fold defaultstate="collapsed" desc="Up moves">
  for(y = this->getY() + 1; y <= 7; y++) {
    if(!board[this->getX()][y].occupied()){
      moves[n] = Coord(this->getX(), y);
      n++;
    }else{
      if(board[this->getX()][y].crnt_piece->getColor() == this->opponent){
        moves[n] = Coord(this->getX(), y);
        n++;
        break;
      }else{
        break;
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Down moves">
  for(y = this->getY() - 1; y >= 0; y--) {
    if(!board[this->getX()][y].occupied()){
      moves[n] = Coord(this->getX(), y);
      n++;
    }else{
      if(board[this->getX()][y].crnt_piece->getColor() == this->opponent){
        moves[n] = Coord(this->getX(), y);
        n++;
        break;
      }else{
        break;
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Right moves">
  for(x = this->getX() + 1; x <= 7; x++) {
    if(!board[x][this->getY()].occupied()){
      moves[n] = Coord(x, this->getY());
      n++;
    }else{
      if(board[x][this->getY()].crnt_piece->getColor() == this->opponent){
        moves[n] = Coord(x, this->getY());
        n++;
        break;
      }else{
        break;
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Left moves">
  for(x = this->getX() - 1; x >= 0; x--){
    if(!board[x][this->getY()].occupied()){
      moves[n] = Coord(x, this->getY());
      n++;
    }else{
      if(board[x][this->getY()].crnt_piece->getColor() == this->opponent){
        moves[n] = Coord(x, this->getY());
        n++;
        break;
      }else{
        break;
      }
    }
  }// </editor-fold>
  
  // <editor-fold defaultstate="collapsed" desc="Up-left">
  x = this->getX();
  for (y = this->getY() - 1; y >= 0; y--) {
    x--;
    if(x >= 0){
      if (!board[x][y].occupied()) {
        this->moves[n] = Coord(x, y);
        n++;
      }else{
        if (board[x][y].crnt_piece->getColor() == this->opponent) {
          this->moves[n] = Coord(x, y);
          n++;
          break;
        }else{
          break;
        }
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Up-right">
  x = this->getX();
  for (y = this->getY() - 1; y >= 0; y--) {
    x++;
    if(x <= 7){
      if (!board[x][y].occupied()) {
        this->moves[n] = Coord(x, y);
        n++;
      }else{
        if (board[x][y].crnt_piece->getColor() == this->opponent) {
          this->moves[n] = Coord(x, y);
          n++;
          break;
        }else{
          break;
        }
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Down-left">
  x = this->getX();
  for (y = this->getY() + 1; y <= 7; y++) {
    x--;
    if(x >= 0){
      if (!board[x][y].occupied()) {
        this->moves[n] = Coord(x, y);
        n++;
      }else{
        if (board[x][y].crnt_piece->getColor() == this->opponent) {
          this->moves[n] = Coord(x, y);
          n++;
          break;
        }else{
          break;
        }
      }
    }
  }// </editor-fold>
  // <editor-fold defaultstate="collapsed" desc="Down-left">
  x = this->getX();
  for (y = this->getY() + 1; y <= 7; y++) {
    x++;
    if(x <= 7){
      if (!board[x][y].occupied()) {
        this->moves[n] = Coord(x, y);
        n++;
      }else{
        if (board[x][y].crnt_piece->getColor() == this->opponent) {
          this->moves[n] = Coord(x, y);
          n++;
          break;
        }else{
          break;
        }
      }
    }
  }// </editor-fold>
  for(n; n < 27; n++){
    moves[n] = Coord();
  }
}