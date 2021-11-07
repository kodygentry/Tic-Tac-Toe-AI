#include <iostream>
#include <string>


const int PLAYER1 = 1, PLAYER2 = 2;
const char PLAYER1MOVE = 'O', PLAYER2MOVE = 'X';
const int GRID = 3; // value of size of board (ex. GRID 3 = 3x3. GRID 4 = 4x4)


// initialize
void header();
void displayBoardLayout();
void displayBoard(char board[][GRID]);
void initializeBoard(char board[][GRID]);

// game logic
void startGame(int);
bool winDetection(char board[][GRID]);

// AI implementation
int ABMinMax(char board[][GRID], int, bool);
int optimalMove(char board[][GRID], int);


int main(){
    header();
    char cont = 'n'; // used for continuing game or not
    do {
        char choice; // used for deciding who goes first
        std::cout << "Do you want to start first?(y/n) : ";
	 	std::cin >> choice;
        if(choice == 'n' || choice == 'N')
            startGame(PLAYER2);
        else if(choice == 'y' || choice == 'Y')
            startGame(PLAYER1);
        else
            std::cout << "Invalid input..." << std::endl;

        std::cout << "Keep playing?(y/n) : ";
        std::cin >> cont;
    } while(cont == 'y');
} 

// initialize
void header(){
        std::cout << "\n---------------------------------------------------------------\n"
              << "\n\t\t\tTic-Tac-Toe\n"
              << "\n---------------------------------------------------------------\n";
}

void displayBoardLayout(){
    std::cout << "\t\t\t 1 | 2 | 3 " << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t 4 | 5 | 6 " << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t 7 | 8 | 9 \n" << std::endl;
}

void displayBoard(char board[][GRID]){
    std::cout << "\t\t\t " << (board[0][0]) << " | " << (board[0][1]) << " | " << (board[0][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[1][0]) << " | " << (board[1][1]) << " | " << (board[1][2]) << std::endl
              << "\t\t\t-----------" << std::endl
              << "\t\t\t " << (board[2][0]) << " | " << (board[2][1]) << " | " << (board[2][2]) << std::endl;
}   

void initializeBoard(char board[][GRID]){
    for (int i = 0; i < GRID; i++){
		for (int j = 0; j < GRID; j++) 
			board[i][j] = ' '; 
    }
}

// game logic
void startGame(int turn){
    char board[GRID][GRID];
    int index = 0, row = 0, col = 0; // for depth index

    initializeBoard(board);
    displayBoardLayout();

    while (winDetection(board) == false && index != GRID * GRID){ 
		int n;

		if (turn == PLAYER1){
			std::cout<<"\n\nEnter move = ";
			std::cin >> n;
			n--;
			row = n / GRID;
			col = n % GRID; 
			if(board[row][col] == ' ' && n<9 && n>=0){
				board[row][col] = PLAYER1MOVE; 
				std::cout<<"\nPLAYER1 has put an " << PLAYER1MOVE << " in cell " << n+1 << "\n\n";
				displayBoard(board); 
				index ++; 
				turn = PLAYER2;
			}
			else if(board[row][col] != ' ' && n<9 && n>=0){
				std::cout<<"\nPosition is occupied\n\n";
			}
			else if(n<0 || n>8){
				std::cout<<"Invalid position\n";
			}
		} 

        else if (turn == PLAYER2){
			n = optimalMove(board, index);
			row = n / GRID;
			col = n % GRID;
			board[row][col] = PLAYER2MOVE; 
			std::cout << "PLAYER2 has put a " << PLAYER2MOVE << " in cell " << n+1 << "\n\n";
			displayBoard(board);
			index++; 
			turn = PLAYER1;
		}  
	} 

	// draw
	if (winDetection(board) == false && index == GRID * GRID) 
		std::cout << "Draw\n"; 
	else{ 
		if (turn == PLAYER1) 
			turn = PLAYER2; 
		else if (turn == PLAYER2) 
			turn = PLAYER1; 
		
		if (turn == PLAYER2) 
		    std::cout<<"PLAYER2 has won\n"; 
	    else
		    std::cout<<"PLAYER1 has won\n";  
	} 
} 

bool winDetection(char board[][GRID]){
	for (int i = 0; i < GRID; i++){ 
		if (board[i][0] == board[i][1] && 
			board[i][1] == board[i][2] && 
			board[i][0] != ' ') 
			return (true); 
        else if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] != ' ') 
			return (true); 
        else if (board[0][0] == board[1][1] && 
            board[1][1] == board[2][2] && 
            board[0][0] != ' ') 
            return(true); 
        else if (board[0][2] == board[1][1] && 
            board[1][1] == board[2][0] && 
            board[0][2] != ' ') 
            return(true); 
	} 
	return(false);
}

// AI implementation

int ABMinMax(char board[][GRID], int depth, bool isAI){
	int score = 0, bestScore = 0;
	if (winDetection(board) == true)
		return isAI;

	else{
		if(depth < 9){
			if(isAI == true){ // if AI move
				bestScore = -999; // negative infinity in our case
				for(int i=0; i<GRID; i++){
					for(int j=0; j<GRID; j++){
						if (board[i][j] == ' '){
							board[i][j] = PLAYER1;
							score = ABMinMax(board, depth + 1, false);
							board[i][j] = ' ';
							if(score > bestScore)
								bestScore = score;
						}
					}
				}
				return bestScore;
			}
			else{ // if not AI move
				bestScore = 999; // infinity in our case
				for (int i = 0; i < GRID; i++){
					for (int j = 0; j < GRID; j++){
						if (board[i][j] == ' '){
							board[i][j] = PLAYER2;
							score = ABMinMax(board, depth + 1, true);
							board[i][j] = ' ';
							if (score < bestScore)
								bestScore = score;
						}
					}
				}
				return bestScore;
			}
		}
		else return 0;
	}
}

int optimalMove(char board[][GRID], int moveIndex){
	int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < GRID; i++){
		for (int j = 0; j < GRID; j++){
			if (board[i][j] == ' '){
				board[i][j] = PLAYER2;
				score = ABMinMax(board, moveIndex+1, false);
				board[i][j] = ' ';
				if(score > bestScore){
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}
