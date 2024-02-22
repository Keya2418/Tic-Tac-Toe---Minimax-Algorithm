#include<string>
#include<iostream>
#include <utility>

using namespace std;

const int Size = 3;
char board[Size][Size];


//1. initialize the board to ensure that player starts with a clean board without any moves
void initBoard(){
    for(int i=0; i<Size; i++){
        for(int j=0; j<Size; j++){
            board[i][j]=' ';
        }
    }
}

//2. display current state of the board by iterating through each cell of 2D array
void displayBoard(){
    for(int i=0; i<Size; i++){
        // Print horizontal line
        cout << "-------------" << endl;
        for(int j=0; j<Size; j++){
            //print row contents
             cout << "| " << board[i][j] << " ";
        }
        cout << "|" << endl;
    }
    // Print the bottom horizontal line
    cout << "-------------" << endl;
}


//3. check winner by checking vertical, horizontal, and diagonal pairs
bool checkWinner(char player){  //player is either 'X' or 'O'
    //a. check rows (horizontal pairs)           
    for(int i=0; i<Size; i++){
        if(board[i][0]==player && board[i][1]==player && board[i][2]==player){
            return true; //player has won in the current row
        }
    }
    
    //b. check columns (vertical pairs)
    for(int j=0; j<Size; j++){
        if(board[0][j]==player && board[1][j]==player && board[2][j]==player){
            return true; 
        }
    }
    //c. check diagonal pairs
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true; // Player has won in one of the diagonals
    }
    return false; // No winning combination found. it is a Tie
}

//4. check if the board is full that means if the game is over
bool isFull(){
    //iterate over each cell 
    for (int i=0; i<Size; i++) {
        for (int j=0; j<Size; j++) {
            // If any cell is empty, return false
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    // If all cells are occupied, return true
    return true;
}

//5. update the next move(whose turn it is?)
void makeMove(char player, int row, int col){
    board[row][col] = player;
}

//6. minimax function
//we want to maximize computer score fro AI to win
int minimax(char board[Size][Size], int depth, bool isMaximisingPlayer){
    //base case for recursion
    //if computer wins. return high score, if human wins, return low score
    if(checkWinner('X')){
        return 10-depth;
    }
    else if(checkWinner('O')){
        return depth-10;
    }
    else if(isFull()){
        return 0; //return 0 if it is a tie.
    }

    //if it is maximizing players turn (computer)
    if(isMaximisingPlayer){
        int bestScore = INT_MIN;
        //iterate through all empty cells and evalute each move
        for(int i=0; i<Size; i++){
            for(int j=0; j<Size; j++){
                //if there is empty space
                if(board[i][j]==' '){
                    //make a move
                    board[i][j]='X';
                    //recursively call minimax function on the opposite player
                    int score = minimax(board, depth+1, false);
                    //undo move
                    board[i][j]=' ';
                    //update best score
                    bestScore=max(bestScore,score);
                }
            }
        }
        return bestScore;
    }
    else{
        //if it is minimizing player's turn (human)
        int bestScore = INT_MAX;
        //iterate through all empty cells and evalute each move
        for(int i=0; i<Size; i++){
            for(int j=0; j<Size; j++){
                if(board[i][j]==' '){
                    //if board is empty, make the move
                    board[i][j] = 'O';
                    int score = minimax(board, depth+1, true);
                    //undo move
                    board[i][j]=' ';
                    //update best score
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

//7. function to implement computer move
void computerMove(){
    //a. Call the minimax function to determine the best move

    // - store highest score so far
    int bestScore = INT_MIN;
    // - using pair to store cordinates of the best move
    pair<int, int> bestMove;

    // - iterate over the board and check if there is empty cell available
    for(int i=0; i<Size; i++){
        for(int j=0; j<Size; j++){
            if(board[i][j]==' '){
                //temporarily make a computer move there to evaluate the score
                board[i][j]='X';

                //b. Update the board with the computer's move
                // - calls minimax function to find the score of current move
                // - passes 'false' to indicate it is not maximizing player's turn
                int score = minimax(board, 0, false);
                board[i][j]=' ';  //undo the move

                if(score>bestScore){
                    bestScore = score; //if score of current move is higher than previously found score then update score
                    bestMove = {i, j}; //stores cordinates of the best move
                }
            }
        }
    }
    //update the move with computer's move
    makeMove('X', bestMove.first, bestMove.second); 
}


//main
int main(){
    cout<<"\n Tic Tac Toe"<<endl<<endl;

    initBoard();
    displayBoard();

    char currentPlayer = 'O'; //human starts the game

    //game loop
    while(!checkWinner('X') && !checkWinner('O') && !isFull()){
        //if it is human's turn
        if(currentPlayer == 'O'){
            int row, col;
            cout<<"your turn. Please enter row and col (0-2). "<<endl;
            cin>>row>>col;
            //validate input
            if(row >=0 && row<Size && col>=0 && col<Size && board[row][col]==' '){
                makeMove(currentPlayer, row, col);
                currentPlayer = 'X';//switch to computer player
            }
            else{
                cout<<"Invalid move. Try again. ";
            }
        }
        else{
            //if it is computer turn
            computerMove();
            currentPlayer = 'O'; //switch to human player
        }
        displayBoard();
    }
    //check game result
    if (checkWinner('X')) {
        cout << "Computer wins! you cannot outsmart AI!" << endl;
    } else if (checkWinner('O')) {
        cout << "You Defeated AI, Congratulations!!" << endl;
    } else {
        cout << "It's a tie, better luck next time!" << endl;
    }
    return 0;
} 



