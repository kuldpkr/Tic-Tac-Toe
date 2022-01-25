#include <bits/stdc++.h>
using namespace std;

vector<char>mp = {'X', '0'};
const int inf = 1e9;
int checkWinner(vector< vector<char> >&board);
bool isValidCell(int x,int y);
void printBoard(vector< vector<char> >&board);

//Step 1: given any board position find the best move for the current player
//Step 2: if I know the opponent's best move and utility after my every available move, I can choose the best move among those availbale moves
//Step 3: recursion does the trick here
pair< pair<int,int>, int> findBestMove(vector< vector<char> >&board, int player,int move){
    pair< pair<int,int>, int>bestMove = {{-1,-1}, -inf};
    pair< pair<int,int>, int>curMove = {{-1,-1}, -inf};
    int winner = -1;
    if(move >= 9){
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[0].size();j++){
                if(board[i][j] == ' '){
                    board[i][j] = mp[player];
                    winner = checkWinner(board);
                    bestMove.first = {i,j};
                    if(winner == player)
                        bestMove.second = 1;//winning position utility for player
                    else if(winner == -1)
                        bestMove.second = 0;//drawn position utility for player
                    else
                        bestMove.second = -1;//losing position utility for player
                    board[i][j] = ' ';
                }
            }
        }
    }
    else{  
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[0].size();j++){
                if(board[i][j] == ' '){
                    // cout << i << " " << j << "cell no\n";
                    board[i][j] = mp[player];
                    curMove.first = {i,j};
                    winner = checkWinner(board);
                    if(winner != -1){
                        if(winner == player)
                            curMove.second = 1;
                        else
                            curMove.second = -1;
                    }
                    else{
                        //getting my payoff from opponent's payoff(zero-sum-game) 
                        curMove.second = -(findBestMove(board, 1-player, move + 1).second);
                    }
                    if(curMove.second > bestMove.second)
                        bestMove = curMove;
                    board[i][j] = ' ';//backtracking
                }
            }
        }
    }
    // cout << mp[player] << " " << move << endl;
    // cout << bestMove.first.first << " " << bestMove.first.second << " " << bestMove.second << endl;
    return bestMove;
}

int main()
{
    int n = 3;
    int m = 3;
    vector< vector<char> >board(n,vector<char>(m, ' '));
    cout << "Initial state of the board is:\n";
    printBoard(board);
    cout << endl;
    // cout << "To play, input the row and the column number(both 0 indexed) of the cell where you want to mark\n";
    int player = 0;//player = 0 means it's turn of 'X' player else it's turn of '0' player
    int algoPlayer = 0;//to store whether algorithm plays as 'X' or '0' player
    int x = 0,y = 0;// to store player's cell 
    bool gameOn = true;
    int move = 1;
    int winner = -1;//to store winner of the game
    char response;
	bool responseFlag = true;
	while(responseFlag){
		cout << "Do you want to make the first move [Y/n]?";
		cin >> response;
		if(response == 'Y' || response == 'y'){
		    algoPlayer = 1;
			responseFlag = false; 
		}
		else if(response == 'N' || response == 'n'){
		    algoPlayer = 0;
			responseFlag = false;
		}
		else{
		    cout << "Enter valid response!\n";
		}
	}
    while(gameOn && move <= 9){
        if(player == algoPlayer){
            cout << "It's algorithm's turn.\n";
            pair<pair<int,int>,int>ans = findBestMove(board,player,move);
            cout << "Algorithm's move is " << ans.first.first << " " << ans.first.second << endl;
            board[ans.first.first][ans.first.second] = mp[algoPlayer];
            printBoard(board);
            winner = checkWinner(board);
            if(winner != -1){
                if(winner == algoPlayer)
                    cout << "Algorithm wins!\n";
                else
                    cout << "Congratulations! You have defeated the algorithm!\n";
                gameOn = false;
            }
        }
        else{
            cout << "It's your turn, Enter your move in form of x y:";
            cin >> x >> y;
            if(isValidCell(x,y) && board[x][y] == ' '){
                board[x][y] = mp[player];
                printBoard(board);
                winner = checkWinner(board);
                if(winner != -1){
                    if(winner == algoPlayer)
                        cout << "Algorithm wins!\n";
                    else
                        cout << "Congratulations! You have defeated the algorithm!\n";
                    gameOn = false;
                }
            }
            else{
                cout << "Enter valid cell value\n";
                continue;
            }
        }
        player = 1 - player;
        move += 1;
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
    int winner = -1;//-1 means no winner, 0 mein 'X' won and 1 means '0' won
    //horizontal condition
    if(board[0][0] == board[0][1] && board[0][0] == board[0][2])
        if(board[0][0] == '0')
            winner = 1;
        else if(board[0][0] == 'X')
            winner = 0;
    if(winner == -1 && board[1][0] == board[1][1] && board[1][0] == board[1][2])
        if(board[1][0] == '0')
            winner = 1;
        else if(board[1][0] == 'X')
            winner = 0;
    if(winner == -1 && board[2][0] == board[2][1] && board[2][0] == board[2][2])
        if(board[2][0] == '0')
            winner = 1;
        else if(board[2][0] == 'X')
            winner = 0;
    //vertical condition
    if(winner == -1 && board[0][0] == board[1][0] && board[0][0] == board[2][0])
        if(board[0][0] == '0')
            winner = 1;
        else if(board[0][0] == 'X')
            winner = 0;
    if(winner == -1 && board[0][1] == board[1][1] && board[0][1] == board[2][1])
        if(board[0][1] == '0')
            winner = 1;
        else if(board[0][1] == 'X')
            winner = 0;
    if(winner == -1 && board[0][2] == board[1][2] && board[0][2] == board[2][2])
        if(board[0][2] == '0')
            winner = 1;
        else if(board[0][2] == 'X')
            winner = 0;
    //diagonal condition
    if(winner == -1 && board[0][0] == board[1][1] && board[0][0] == board[2][2])
        if(board[0][0] == '0')
            winner = 1;
        else if(board[0][0] == 'X')
            winner = 0;
    if(winner == -1 && board[0][2] == board[1][1] && board[0][2] == board[2][0])
        if(board[0][2] == '0')
            winner = 1;
        else if(board[0][2] == 'X')
            winner = 0;
    return winner;
}
