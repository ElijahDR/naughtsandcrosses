#include <iostream>
#include <map>
#include <string>

using namespace std;

int board[9];
int player1 = 1; // user
int player2 = -1; // computer

class Move{
    public:
        int score;
        int index;
};

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

int minimax(int newBoard[9], int player){
    int availMoves[9] = {0,1,2,3,4,5,6,7,8};
    for (int i = 0; i < 9; i++){
        if (newBoard[i] != 0){ availMoves[i] = -1; }
    }

    if (winning(newBoard, 1)){
        return -10;
    } else if (winning(newBoard, -1)){
        return 10;
    } 
    bool moves;
    for (int i =0; i < 9; i++){
        if (newBoard[i] != -1) { moves = true;}
    }
    if (!moves){
        return 0;
    }

    moves = new Move[9];
    int movesI = 0;
    for (int i = 0; i < 9; i++){
        if (availMoves[i] == -1){
            continue;
        }
        map <string, int> move;
        move["index"] = availMoves[i];
        newBoard[availMoves[i]] = player;
        if (player == -1){
            int result = minimax(newBoard, 1);
            move["score"] = result;
        } else {
            int result = minimax(newBoard, -1);
            move["score"] = result;
        }

        newBoard[availMoves[i]] = 0;
        moves[movesI] = move;
        movesI++;
    }
}


int main(){
    display(board);
    return 0;
}