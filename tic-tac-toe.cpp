#include <bits/stdc++.h>
using namespace std;

int checkWinner(vector< vector<char> >&board);
bool isValidCell(int x,int y);
void printBoard(vector< vector<char> >&board);
int main()
{
    int n = 3;
    int m = 3;
    vector< vector<char> >board(n,vector<char>(m, ' '));
    cout << "Initial state of the board is:\n";
    printBoard(board);
    cout << endl;
    // cout << "To play, input the row and the column number(both 0 indexed) of the cell where you want to mark\n";
    vector<char>mp = {'X', '0'};
    int symbol = 0;//symbol = 0 means it's turn of 'X' player else it's turn of '0' player
    int x = 0,y = 0;// to store player's cell 
    bool gameOn = true;
    int move = 1;
    int winner = -1;//to store winner of the game
    while(gameOn && move <= 9){
        cout << "Player " <<  symbol+1 <<"'s Turn, enter your move:";
        cin >> x >> y;
        if(isValidCell(x,y) && board[x][y] == ' '){
            board[x][y] = mp[symbol];
            printBoard(board);
            winner = checkWinner(board);
            if(winner != -1){
                if(winner)
                    cout << "Player 1 wins!\n";
                else
                    cout << "Player 2 wins!\n";
                gameOn = false;
                
            }
            symbol = 1 - symbol;
            move += 1;
        }
        else{
            cout << "Input valid cell value\n";
        }
    }
    if(winner == -1)
        cout << "Game is drawn!\n";
    return 0;
}
bool isValidCell(int x,int y){
    return (x>=0 && x < 3 && y >= 0 && y < 3); 
}
void printBoard(vector< vector<char> >&board){
    for(int i=0;i<board.size();i++){    
        cout << board[i][0] << "|" << board[i][1] << "|" << board[i][2] << endl;
        if(i < board.size() - 1)
            cout << "-+-+-\n";
    }
}
int checkWinner(vector< vector<char> >&board){
    int winner = -1;//-1 means no winner, 0 mein '0' won and 1 means 'X' won
    //horizontal condition
    if(board[0][0] == board[0][1] && board[0][0] == board[0][2])
        if(board[0][0] == '0')
            winner = 0;
        else if(board[0][0] == 'X')
            winner = 1;
    if(winner == -1 && board[1][0] == board[1][1] && board[1][0] == board[1][2])
        if(board[1][0] == '0')
            winner = 0;
        else if(board[1][0] == 'X')
            winner = 1;
    if(winner == -1 && board[2][0] == board[2][1] && board[2][0] == board[2][2])
        if(board[2][0] == '0')
            winner = 0;
        else if(board[2][0] == 'X')
            winner = 1;
    //vertical condition
    if(winner == -1 && board[0][0] == board[1][0] && board[0][0] == board[2][0])
        if(board[0][0] == '0')
            winner = 0;
        else if(board[0][0] == 'X')
            winner = 1;
    if(winner == -1 && board[0][1] == board[1][1] && board[0][1] == board[2][1])
        if(board[0][1] == '0')
            winner = 0;
        else if(board[0][1] == 'X')
            winner = 1;
    if(winner == -1 && board[0][2] == board[1][2] && board[0][2] == board[2][2])
        if(board[0][2] == '0')
            winner = 0;
        else if(board[0][2] == 'X')
            winner = 1;
    //diagonal condition
    if(winner == -1 && board[0][0] == board[1][1] && board[0][0] == board[2][2])
        if(board[0][0] == '0')
            winner = 0;
        else if(board[0][0] == 'X')
            winner = 1;
    if(winner == -1 && board[0][2] == board[1][1] && board[0][2] == board[2][0])
        if(board[0][2] == '0')
            winner = 0;
        else if(board[0][2] == 'X')
            winner = 1;
    return winner;
}

