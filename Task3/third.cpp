#include <bits/stdc++.h>
using namespace std;

const char PLAYER1 = 'X', PLAYER2 = 'O', EMPTY = '.';
char AI = 'O', HUMAN = 'X';

void printBoard(const vector<vector<char>>& board) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

bool movesLeft(const vector<vector<char>>& board) {
    for (const auto& row : board)
        for (char cell : row)
            if (cell == EMPTY) return true;
    return false;
}

bool isWin(const vector<vector<char>>& board, char player) {

    for (int i = 0; i < 3; i++)
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;

    for (int j = 0; j < 3; j++)
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return true;

    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;

    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

pair<int, int> findAnyMove(vector<vector<char>>& board) {
    if (board[1][1] == EMPTY) return {1, 1};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return {i, j};

    return {-1, -1};
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, EMPTY));
    int mode = 2;
    char sym = 'X';

    cout << "Tic-Tac-Toe\n";
    cout << "1. Play with Person\n";
    cout << "2. Play with Computer\n";
    cout << "Choose mode (default 2): ";

    if (!(cin >> mode)) {
        cin.clear();
        cin.ignore();
        mode = 2;
    }

    if (mode == 2) {
        cout << "Press X to start your turn: ";
        if (!(cin >> sym)) {
            cin.clear();
            cin.ignore();
            sym = 'X';
        }
        sym = toupper(sym);
        HUMAN = sym;
        AI = (sym == 'X') ? 'O' : 'X';
    }

    int turn = 0;
    while (true) {
        printBoard(board);

        if (mode == 1 || (turn == 0 && HUMAN == 'X') || (turn == 1 && HUMAN == 'O')) {
            int row, col;
            cout << (mode == 1 ?
                   "Player " + string(turn == 0 ? "1 (X)" : "2 (O)") + " enter (row col): " :
                   "Enter your move (row col): ");

            if (!(cin >> row >> col)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input. Try again.\n";
                continue;
            }
            row--; col--;

            if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != EMPTY) {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            board[row][col] = (mode == 1) ? (turn == 0 ? PLAYER1 : PLAYER2) : HUMAN;

            if (isWin(board, board[row][col])) {
                printBoard(board);
                cout << (mode == 1 ? "Player " + to_string(turn + 1) : "You") << " win!\n";
                break;
            }
        }
        else {
            cout << "Computer's move...\n";
            auto move = findAnyMove(board);
            board[move.first][move.second] = AI;

            if (isWin(board, AI)) {
                printBoard(board);
                cout << "Computer wins!\n";
                break;
            }
        }

        if (!movesLeft(board)) {
            printBoard(board);
            cout << "Draw!\n";
            break;
        }

        turn ^= 1;
    }
}
