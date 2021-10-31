#include <iostream>
#include <string>


const int PLAYER1 = 1, PLAYER2 = 2;
const char PLAYER1MOVE = 'O', PLAYER2MOVE = 'X';
const int GRID = 3; // value of size of board (ex. GRID 3 = 3x3. GRID 4 = 4x4)


// inititalize
void displayBoardLayout();
void displayBoard(char board[][GRID]);
void initializeBoard(char board[][GRID]);

// game logic
void startGame(int);
bool endGame(char board[][GRID]);
bool checkRow(char board[][GRID]);
bool checkCol(char board[][GRID]);
bool checkDiag(char board[][GRID]);
void declareWinner(int);

// AI implementation



int main(){
    std::cout << "\n---------------------------------------------------------------\n"
              << "\n\t\t\tTic-Tac-Toe\n"
              << "\n---------------------------------------------------------------\n";

    /* 
        temp input loop
        later implement AI vs AI
    */ 
    char cont = 'n'; // used for continuing game or not
    do {
        char choice; // used for deciding who goes first
        std::cout << "Do you want to start first?(y/n) : ";
	 	std::cin >> choice;
        if(choice == 'n' || choice == 'N')
            startGame(PLAYER1);
        else if(choice == 'y' || choice == 'Y')
            startGame(PLAYER2);
        else
            std::cout << "Invalid input..." << std::endl;

        std::cout << "Keep playing?(y/n) : ";
        std::cin >> cont;
    } while(cont == 'y');
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

void startGame(int turn){
    char board[GRID][GRID];
    int index = 0, row = 0, col = 0; // for depth index

    initializeBoard(board);
    displayBoardLayout();

    while (endGame(board) == false && index != GRID * GRID){ 
		int n;


		/*
        // AI player 1
		if (turn == PLAYER1){
			// insert min max here
			row = n / GRID;
			col = n % GRID;
			board[row][col] = PLAYER1MOVE; 
			std::cout << "PLAYER2 has put a " << PLAYER1MOVE << " in cell " << n+1 << "\n\n";
			displayBoard(board);
			index++; 
			turn = PLAYER2;
		} 
		

        // AI player two
        else if (turn == PLAYER2){
			// insert min max here
			row = n / GRID;
			col = n % GRID;
			board[row][col] = PLAYER1MOVE; 
			std::cout << "PLAYER2 has put a " << PLAYER2MOVE << " in cell " << n+1 << "\n\n";
			displayBoard(board);
			index++; 
			turn = PLAYER1;
		} 

		*/

		// HUMAN INPUT
		if (turn == PLAYER1){
			printf("You can insert in the following positions : ");
			for(int i=0; i < GRID; i++)
				for (int j = 0; j < GRID; j++)
					if (board[i][j] == ' ')
						printf("%d ", (i * 3 + j) + 1);
			printf("\n\nEnter the position = ");
			scanf("%d",&n);
			n--;
			row = n / GRID;
			col = n % GRID; 
			if(board[row][col] == ' ' && n<9 && n>=0){
				board[row][col] = PLAYER1MOVE; 
				printf ("\nPLAYER1 has put a %c in cell %d\n\n", PLAYER1MOVE, n+1); 
				displayBoard(board); 
				index ++; 
				turn = PLAYER2;
			}
			else if(board[row][col] != ' ' && n<9 && n>=0){
				printf("\nPosition is occupied, select any one place from the available places\n\n");
			}
			else if(n<0 || n>8){
				printf("Invalid position\n");
			}
		} 

		if (turn == PLAYER2){
			printf("You can insert in the following positions : ");
			for(int i=0; i < GRID; i++)
				for (int j = 0; j < GRID; j++)
					if (board[i][j] == ' ')
						printf("%d ", (i * 3 + j) + 1);
			printf("\n\nEnter the position = ");
			scanf("%d",&n);
			n--;
			row = n / GRID;
			col = n % GRID; 
			if(board[row][col] == ' ' && n<9 && n>=0){
				board[row][col] = PLAYER2MOVE; 
				printf ("\nPLAYER2 has put a %c in cell %d\n\n", PLAYER2MOVE, n+1); 
				displayBoard(board); 
				index ++; 
				turn = PLAYER1;
			}
			else if(board[row][col] != ' ' && n<9 && n>=0){
				printf("\nPosition is occupied, select any one place from the available places\n\n");
			}
			else if(n<0 || n>8){
				printf("Invalid position\n");
			}
		} 
		

 
	} 

	// If the game has drawn 
	if (endGame(board) == false && index == GRID * GRID) 
		std::cout << "Draw\n"; 
	else{ 
		// Toggling the user to declare the actual winner 
		if (turn == PLAYER1) 
			turn = PLAYER2; 
		else if (turn == PLAYER2) 
			turn = PLAYER1; 
		
		declareWinner(turn); 
	} 
} 

bool endGame(char board[][GRID]){
    return (checkDiag(board) || checkCol(board) || checkRow(board));
}

bool checkRow(char board[][GRID]) { 
	for (int i = 0; i < GRID; i++) { 
		if (board[i][0] == board[i][1] && 
			board[i][1] == board[i][2] && 
			board[i][0] != ' ') 
			return (true); 
	} 
	return(false); 
} 

bool checkCol(char board[][GRID]) { 
	for (int i = 0; i < GRID; i++) { 
		if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] != ' ') 
			return (true); 
	} 
	return(false); 
} 

bool checkDiag(char board[][GRID]) { 
	if (board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] && 
		board[0][0] != ' ') 
		return(true); 
		
	if (board[0][2] == board[1][1] && 
		board[1][1] == board[2][0] && 
		board[0][2] != ' ') 
		return(true); 

	return(false); 
}

void declareWinner(int turn){ 
	if (turn == PLAYER2) 
		printf("PLAYER2 has won\n"); 
	else
		printf("PLAYER1 has won\n"); 
} 