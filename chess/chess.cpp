#include "chess_pieces.h"
#include "chess.h"
#include <iostream>

using namespace std;

// Space members
Space::Space(){
  this->state = EMPTY;
}
bool Space::occupied(){
  return this->state == OCCUPIED;
}
void Space::pieceOn(Piece *p){
  this->crnt_piece = p;
  this->state = OCCUPIED;
  /*
  cout << this->crnt_piece->getIdentity() << " has been placed on: "; 
  cout << "(" << this->crnt_piece->getX();
  cout << ", " << this->crnt_piece->getY() << ")\n";
  */
}
void Space::pieceOff(){
  this->state = EMPTY;
}

// Player members
Player::Player(int color, Space board[][8]){
  this->color = color;
  this->alive = 16; // number of pieces still alive
    
  if(color == WHITE){
    front_row = 1;
    back_row = 0;
  }else{
    front_row = 6;
    back_row = 7;
  }
  // <editor-fold defaultstate="collapsed" desc="Set-up Pieces">
  for(int c = 0; c < 8; c++){
    this->pieces[c] = new Pawn(front_row, c, this->color);
    board[front_row][c].pieceOn(this->pieces[c]);
  }

  this->pieces[8] = new Rook(back_row, 0, this->color);;
  board[back_row][0].pieceOn(this->pieces[8]);

  this->pieces[9] = new Knight(back_row, 1, this->color);
  board[back_row][1].pieceOn(this->pieces[9]);

  this->pieces[10] = new Bishop(back_row, 2, this->color);
  board[back_row][2].pieceOn(this->pieces[10]);

  this->pieces[11] = new Queen(back_row, 3, this->color);
  board[back_row][3].pieceOn(this->pieces[11]);

  this->pieces[12] = new King(back_row, 4, this->color);
  board[back_row][4].pieceOn(this->pieces[12]);

  this->pieces[13] = new Bishop(back_row, 5, this->color);
  board[back_row][5].pieceOn(this->pieces[13]);

  this->pieces[14] = new Knight(back_row, 6, this->color);
  board[back_row][6].pieceOn(this->pieces[14]);

  this->pieces[15] = new Rook(back_row, 7, this->color);
  board[back_row][7].pieceOn(this->pieces[15]); 

    // </editor-fold>
  
  /**
  for(int i = 0; i < 16; i++){
      cout << "identity: " << this->pieces[i]->getIdentity() << "\n";
      cout << "color: " << this->pieces[i]->getColor() << "\n";
      cout << "position: (" << this->pieces[i]->getX() << "," << this->pieces[i]->getY() << ")\n\n";
  }
  cout << "--------------------------------\n\n";*/
}
Piece* Player::getPiece(int index){
    return this->pieces[index];
}
void Player::movePiece(Space board[][8], Piece *p, Coord new_pos){
  if(board[new_pos.x][new_pos.y].occupied()){
    board[new_pos.x][new_pos.y].crnt_piece->die();
  }    
  board[p->getX()][p->getY()].pieceOff();
  p->move(new_pos);
  board[p->getX()][p->getY()].pieceOn(p);

}
int Player::takeTurn(Space board[][8]){
  turn++;
  player_state = LOST;
  if(pieces[12]->isAlive()){//is the king alive
    player_state = PLAYING;
  }
  if(player_state == LOST){
    return 0;
  }
  int piece;
  int num_of_moves = 0;
  int move;
  int choosing = 1;
  while(choosing){
      // 1) select piece to move
      for(int i = 0; i < 16; i++){
        if(this->getPiece(i)->isAlive()){
            //change to print on LCD somehow for arduino
            cout << i << ": ";
            cout << this->getPiece(i)->getIdentity() << " at ";
            cout << "(" << this->getPiece(i)->getX() << ", ";
            cout << this->getPiece(i)->getY() << ")\n";
        }  
      }
      while(1){
        cout << "Select an piece: ";
        cin >> piece;
        if((piece >= 0) & (piece < 16)){
          if(this->getPiece(piece)->isAlive())
            break;
        }
      }
      // 2) select space for that piece to move to
      this->getPiece(piece)->lookUpMoves(board);
      for(int i=0; i<27; i++){
        if(this->getPiece(piece)->moves[i].x == 9)
          break;
        num_of_moves++;
        cout << i << ": " << "(" << this->getPiece(piece)->moves[i].x << ", ";
        cout << this->getPiece(piece)->moves[i].y << ")\n";  
      }
      while(1){
        cout << "Select a move (20 to go back): ";
        cin >> move;
        if(move == 20)
          break;
        if((move >= 0) & (move < num_of_moves)){
          choosing = 0;
          break;
        }
      }
  }
  // MOVE PIECE
  this->movePiece(board, this->getPiece(piece), this->getPiece(piece)->moves[move]);
    //switch which player's turn it is
    //this probably will need changing...
  if(self == WHITE){
    self = BLACK;
    opponent = WHITE;
  }else{
    self = WHITE;
    opponent = BLACK;
  }
}

