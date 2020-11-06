#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Move{
    public:
        int score;
        int index;
        int getScore();
        Move();
};

int Move::getScore(){
    return score;
}

Move::Move(void) {
    score = 0;
    index = 0;
}

bool winning(int board[9], int player){
    if (
        (board[0] == player && board[1] == player && board[2] == player) ||
        (board[3] == player && board[4] == player && board[5] == player) ||
        (board[6] == player && board[7] == player && board[8] == player) ||
        (board[0] == player && board[3] == player && board[6] == player) ||
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player) ||
        (board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player)
        ) {
            return true;
    } else {
        return false;
    }
}

void display(int board[9]){
    for (int i =0 ; i < 3; i++){
        for (int j = 0; j < 3; j++){
            int pos = board[(i*3) + j];
            if (pos == 0){
                cout << "   ";
            } else {
                cout << (pos == 1 ? " X " : " O ");
            }
            cout << ( j < 2 ? "|" : "");
        }
        cout << endl;
        cout << ( i < 2 ? "-----------" : "");
        cout << endl;
    }
    cout << endl;
}

int board[9] = {0,0,0,0,0,0,0,0,0};
int player1 = 1; // user
int player2 = -1; // computer
int runs =0;

int minimax(int newBoard[9], int player){
    cout << runs << endl;
    runs++;
    int availMoves[9] = {0,1,2,3,4,5,6,7,8};
    for (int i = 0; i < 9; i++){
        if (newBoard[i] != 0){ availMoves[i] = -1; }
    }
    if (winning(newBoard, 1)){
        return -10;
    } else if (winning(newBoard, -1)){
        return 10;
    } 
    bool movePoss;
    for (int i =0; i < 9; i++){
        if (newBoard[i] != -1) { movePoss = true;}
    }
    if (!movePoss){
        return 0;
    }

    // vector <Move> moves(9);
    Move moves[9];
    int mI = 0;
    for (int i = 0; i < 9; i++){
        if (availMoves[i] == -1){
            continue;
        }
        Move move;
        move.index = availMoves[i];
        newBoard[availMoves[i]] = player;
        if (player == -1){
            int result = minimax(newBoard, 1);
            move.score = result;
        } else {
            int result = minimax(newBoard, -1);
            move.score = result;
        }

        newBoard[availMoves[i]] = 0;
        moves[mI] = move;
        mI++;
    }

    int bestMove;
    // for (int i = 0; i < 9; i++){
    //     cout << moves[i].index << " " << moves[i].score;
    // }
    if (player == -1){
        int bestScore = -10000;
        for (int i = 0; i < 9; i++){
            if (availMoves[i] == -1){
                continue;
            }
            if (moves[i].score > bestScore){
                bestScore = moves[i].score;
                bestMove = i;
            }
        }
    } else {
        int bestScore = 10000;
        for (int i = 0; i < 9; i++){
            if (availMoves[i] == -1){
                continue;
            }
            if (moves[i].score < bestScore){
                bestScore = moves[i].score;
                bestMove = i;
            }
        }
    }

    return moves[bestMove].index;
}

int main(){
    display(board);
    cout << minimax(board, -1) << endl;
    cout << runs << endl;
    return 0;
}