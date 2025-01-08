#include <iostream>
#include <vector>
#include <unordered_map>

void display(std::vector<std::vector<int>> board, std::unordered_map<int, char> symbols){
	for (int i = 0; i < board.size(); i++){
		for (int j = 0; j < board[i].size(); j++){
			std::cout << symbols[board[i][j]];
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

std::vector<std::vector<int>> tick(std::vector<std::vector<int>> board){

	struct data_struct{ 
		int* pointer {NULL};
		int value {};
	};

	std::vector<data_struct> changes {};

	int neighbours {};
	data_struct data {};

	for (int i = 1; i < board.size()-1; i++){
		for (int j = 1; j < board[i].size()-1; j++){

			neighbours = 0;

			for (int k = -1; k < 2; k++){
				for (int l = -1; l < 2; l++){
					neighbours += board[i+k][j+l];
				}
			}

			neighbours -= board[i][j];
			if (neighbours != 2 && neighbours > 0){
				if (neighbours < 2 || neighbours > 3){
					data.value = 0;
				}
				else if (neighbours == 3){
					data.value = 1;
				}

				int *x = &board[i][j];
				data.pointer = x;

				changes.push_back(data);
			}

		}
	}

	for (int i = 0; i < changes.size(); i++){
		*changes[i].pointer = changes[i].value;
	}

	return board;

}

int main(){

	const std::unordered_map<int, char> symbols {{0, '.'}, {1, '#'}};

	std::vector<std::vector<int>> board (16, std::vector<int>(32, 0));

	int generations {};


	// Glider
	board[3][3] = 1;
    board[3][4] = 1;
    board[3][5] = 1;
    board[2][5] = 1;
    board[1][4] = 1;

    // todo add blinker

    std::cout << "Enter number of generations: ";
    std::cin >> generations;

	display(board, symbols);

    for (int i = 0; i < generations; i++){
    	std::cout << "\033[H\033[J";
    	board = tick(board);
    	display(board, symbols);
    }

}