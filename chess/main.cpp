/* 
 * File:   main.cpp
 * Author: alexfrost
 *
 * Created on April 5, 2012, 9:29 AM
 */

#include <cstdlib>
#include <iostream>
#include "chess.h"

using namespace std;

string identifyPiece(int ident){
    if(ident == 0){
        return "p";
    }else if(ident == 1){
        return "r";
    }else if(ident == 2){
        return "k";
    }else if(ident == 3){
        return "b";
    }else if(ident == 4){
        return "K";
    }else if(ident == 5){
        return "Q";
    }else
        return "#";
}

string identifyColor(int col){
    if(col == 1)
        return "W";
    else
        return "B";
}

void printBoard(Space board[][8]){
    for(int r = 0; r < 8; r++){
        cout << "===+---+---+---+---+---+---+---+---+\n";
        cout << " " << r << "|";
        for(int c = 0; c < 8; c++){
            if(board[c][r].occupied()){
                cout << "|" << identifyColor(board[c][r].crnt_piece->getColor()) << "_";
                cout << identifyPiece(board[c][r].crnt_piece->getIdentity());
                
                //POSITION
                //cout << "|" << board[c][r].crnt_piece->getX() << "," << board[c][r].crnt_piece->getY();
            }else{
                cout << "|   ";
            }
        }
        cout << "|\n";
    }
    cout << "===+---+---+---+---+---+---+---+---+\n";
    cout << "Y/X; 0 / 1 / 2 / 3 / 4 / 5 / 6 / 7 /\n\n";
}

void printPlayerPieces(Player player){
    for(int i = 0; i < 16; i++){
        if(player.getPiece(i)->isAlive()){
          cout << "identity: " << identifyPiece(player.getPiece(i)->getIdentity()) << "\n";
          cout << "color: " << identifyColor(player.getPiece(i)->getColor()) << "\n";
          cout << "position: (" << player.getPiece(i)->getX() << "," << player.getPiece(i)->getY() << ")\n\n";
        }
    }
}

void printPieceMoves(Piece *p){
    for(int i=0; i<27; i++){
        if(p->moves[i].x == 9)
            break;
        cout << "(" << p->moves[i].x << ", " << p->moves[i].y << ")\n";
    }
}

int main(int argc, char** argv) {
  Space board[8][8];
  for(int r = 0; r < 8; r++){
    for(int c = 0; c < 8; c++){
      board[r][c] = Space();
    }
  }
  /*
  int x = 0;
  int y = 6;
  Piece *k = new Knight(x, y, WHITE);
  board[x][y].pieceOn(k);
  printBoard(board);
  k->lookUpMoves(board);
  
  for(int i=0; i<27; i++){
    if(k->moves[i].x == 9)
      break;
    cout << i << ": " << "(" << k->moves[i].x << ", ";
    cout << k->moves[i].y << ")\n";  
  }**/
          
  //set up game
  Player white = Player(WHITE, board);
  Player black = Player(BLACK, board);
  int w_playing = 1;
  int b_playing = 1;
  
  while(w_playing & b_playing){
      printBoard(board);
      cout << "---WHITE PLAYER TURN---\n\n";
      w_playing = white.takeTurn(board);
      if(!(w_playing & b_playing))
        break;
      printBoard(board);
      cout << "---BLACK PLAYER TURN---\n\n";
      b_playing = black.takeTurn(board);
  }
  /*BUGS
   * 
   * 8)Game does not end when King is dead *kind of fixed*
   * 
   * 9)Knights aren't getting all available moves
   * 
   * 
   * 
   */
  cout << "GAME OVER!";
  return 0;
}