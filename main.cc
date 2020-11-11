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


int board[9] = {0,0,0,0,0,0,0,0,0};
//int board[9] = {1,0,2,2,0,2,0,1,1};
int human = 1; // user
int ai = 2; // computer
int runs =0;

// Returns an array corresponding to the array, 0 for available move, -1 for taken.
int* getAvailableMoves(int board[9]){
    static int possibleMoves[9] = {0,0,0,0,0,0,0,0,0};
    for (int i = 0; i < 9; i++){
        if (board[i] != 0) {
            possibleMoves[i] = -1;
        }
    }

    return possibleMoves;
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

// Checks game returning 1 if human wins, 2 if ai wins, 0 if tie and -1 if no result.
int checkGame(int board[9]){
    if (winning(board, human)){
        return human;
    } else if (winning(board, ai)){
        return ai;
    } else {
        bool notFull = false;
        int possibleMoves[9] = {0,0,0,0,0,0,0,0,0};
        for (int i = 0; i < 9; i++){
            if (board[i] != 0) {
                possibleMoves[i] = -1;
            }
        }
        for (int i = 0; i < 9; i++){
            if (possibleMoves[i] == 0){
                notFull = true;
            }
        }
        if (!notFull){
            return 0;
        } else {
            return -1;
        }
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

int minimax(int board[9], int depth, bool isMax){
    runs++;
    int result = checkGame(board);
    if (result != -1){
        if (result == 1){
            return -10;
        } else if (result == 2){
            return 10;
        } else if (result == 0){
            return 0;
        }
    }
    int move = -1;
    if (isMax){
        int bestScore = -100000000;
        for (int i = 0; i < 9; i ++){
            if (board[i] == 0){
                board[i] = ai;
                int score = minimax(board, depth+1, false);
                board[i] = 0;
                if (score > bestScore){
                    bestScore = score;
                    move = i;
                }
            }
        }
        if (depth == 0){
            return move;
        }
        return bestScore;
    } else {
        int bestScore = 100000000;
        for (int i = 0; i < 9; i ++){
            if (board[i] == 0){
                board[i] = human;
                int score = minimax(board, depth+1, true);
                board[i] = 0;
                if (score < bestScore){
                    bestScore = score;
                    move = i;
                }
            }
        }
        return bestScore;
    }
}

int main(){
    display(board);
    while (checkGame(board) == -1){
        cout << "Your move: ";
        int move = 0;
        cin >> move;
        if (move == 0){
            break
        }
        move--;
        int possibleMoves[9] = {0,0,0,0,0,0,0,0,0};
        for (int i = 0; i < 9; i++){
            if (board[i] != 0) {
                possibleMoves[i] = -1;
            }
        }
        if (possibleMoves[move] != 0){
            cout << "Not possible... retry" << endl;
            continue;
        }
        board[move] = human;
        int aiMove = minimax(board, 0, true);
        board[aiMove] = ai;
        display(board);
    }
    int result = checkGame(board);
    if (result == 0){
        cout << "Tie!" << endl;
    } else if (result == human){
        cout << "You won!" << endl;
    } else if (result == ai){
        cout << "You lost! AI won" << endl;
    }
    return 0;
}