#include <iostream>
using namespace std;

class board {
public:
    char boardcard[3][3];

    board() {
        for(int i = 1; i <= 3; i++)
            for(int j = 1; j <= 3; j++)
                boardcard[i-1][j-1] = ' ';
    }

    void display() {
        for(int i = 1; i <= 3; i++) {
            for(int j = 1; j <= 3; j++) {
                cout << " " << boardcard[i-1][j-1] << " ";
                if(j < 3) cout << "|";
            }
            cout << endl;
            if(i < 3) cout << "---|---|---" << endl;
        }
        cout << endl;
    }

    bool isEmpty(int row, int col) {
        return boardcard[row-1][col-1] == ' ';
    }

    void placeMark(char symbol, int row, int col) {
        boardcard[row-1][col-1] = symbol;
    }

    bool isFull() {
        for(int i = 1; i <= 3; i++)
            for(int j = 1; j <= 3; j++)
                if(boardcard[i-1][j-1] == ' ')
                    return false;
        return true;
    }
};

class player {
private:
    string name;
    board& bobj;
    char symbol;

public:
    player(string p, char s, board& ref)
        : name(p), symbol(s), bobj(ref) {}

    void makemove() {
        int row, col;

        while(true) {
            cout << name << " (" << symbol << ") enter row (1-3): ";
            cin >> row;
            cout << name << " (" << symbol << ") enter col (1-3): ";
            cin >> col;

            if(row >= 1 && row <= 3 && col >= 1 && col <= 3) {
                if(bobj.isEmpty(row, col)) {
                    bobj.placeMark(symbol, row, col);
                    break;
                } else {
                    cout << "Cell already occupied. Try again.\n";
                }
            } else {
                cout << "Invalid position. Try again.\n";
            }
        }
    }

    string getName() {
        return name;
    }
};

class game {
private:
    player player1;
    player player2;
    board& b;
    bool player1turn;

public:
    game(player p1, player p2, board& Board)
        : player1(p1), player2(p2), b(Board), player1turn(true) {}

    void run() {
        while(true) {
            b.display();

            if(player1turn)
                player1.makemove();
            else
                player2.makemove();

            if(checkwin()) {
                b.display();
                cout << (player1turn ? player1.getName() : player2.getName())
                     << " WINS!\n";
                break;
            }

            if(b.isFull()) {
                b.display();
                cout << "Game is a DRAW!\n";
                break;
            }

            player1turn = !player1turn;
        }
    }

    bool checkwin() {

        // Rows
        for(int i = 1; i <= 3; i++) {
            if(b.boardcard[i-1][0] == b.boardcard[i-1][1] &&
               b.boardcard[i-1][1] == b.boardcard[i-1][2] &&
               b.boardcard[i-1][0] != ' ')
                return true;
        }

        // Columns
        for(int j = 1; j <= 3; j++) {
            if(b.boardcard[0][j-1] == b.boardcard[1][j-1] &&
               b.boardcard[1][j-1] == b.boardcard[2][j-1] &&
               b.boardcard[0][j-1] != ' ')
                return true;
        }
        // Diagonals
        if(b.boardcard[0][0] == b.boardcard[1][1] &&
           b.boardcard[1][1] == b.boardcard[2][2] &&
           b.boardcard[0][0] != ' ')
            return true;

        if(b.boardcard[0][2] == b.boardcard[1][1] &&
           b.boardcard[1][1] == b.boardcard[2][0] &&
           b.boardcard[0][2] != ' ')
            return true;

        return false;
    }
};

int main() {
    board boardgame;
    player p1("player 1", 'X', boardgame);
    player p2("player 2", 'O', boardgame);

    game g(p1, p2, boardgame);

    g.run();

    return 0;
}