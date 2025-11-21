# include <iostream>
# include <vector>
#include <queue>
#include <deque>
#include <string>
using namespace std;

class IObserver {
public:
    virtual void update(string message) = 0;
    virtual ~IObserver() {}
};

class ConsoleNotifier : public IObserver {
public:
    void update(string message) override {
        cout << "[Notification] " << message << endl;
    }
};

class Symbol {
private:
    char mark;
public:
    Symbol(char m) {
        mark = m;
    }
    
    char getMark() {
        return mark;
    }
};

class Board {
private:
    vector<vector<Symbol*>> grid;
    int size;
    Symbol* emptycell;
public:
    Board(int s) {
        size = s;
        emptycell = new Symbol('_');
        grid = vector<vector<Symbol*>>(size, vector<Symbol*>(size, emptycell));
    }

    bool isCellEmpty(int r, int c) {
        if(r < 0 || r >= size || c < 0 || c>=size) {
            return false;
        }
        return grid[r][c] == emptycell;
    }

    bool placeMark(int row, int col, Symbol* mark) {
        if(row < 0 || row >= size || col < 0 || col >= size) {
            return false;
        }
        if(!isCellEmpty(row, col)) {
            return false;
        }
        grid[row][col] = mark;
        return true;
    }

    Symbol* getCell(int r, int c) {
        if(r<0 || r>=size || c<0 || c>=size) {
            return emptycell;
        }
        return grid[r][c];
    }

    int getSize() {
        return size;
    }
    
    Symbol* getEmptyCell() {
        return emptycell;
    }
    
    void display() {
        cout << "\n  ";
        for(int i = 0; i < size; i++) {
            cout << i << " ";
        }
        cout << endl;
        
        for(int i = 0; i < size; i++) {
            cout << i << " ";
            for(int j = 0; j < size; j++) {
                cout << grid[i][j]->getMark() << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

class Player {
private:
    int id;
    string name;
    Symbol* symbol;
    int score;
public:
    Player(int id, string name, Symbol* symbol) {
        this->id = id;
        this->name = name;
        this->symbol = symbol;
        this->score = 0;
    }

    string getName() { 
        return name; 
    }

    Symbol* getSymbol() { 
        return symbol; 
    }

    int getScore() { 
        return score; 
    }

    void incrementScore() { 
        score++;
    }
    
    ~Player() {
        delete symbol;
    }
};

class Rules {
public:
    virtual bool isValidMove(Board* board, int row, int col) = 0;
    virtual bool checkWinCondition(Board* board, Symbol* symbol) = 0;
    virtual bool checkDrawCondition(Board* board) = 0;
    virtual ~Rules() {}
};

class StandardRules : public Rules {
public:
    bool isValidMove(Board* board, int row, int col) override {
        return board->isCellEmpty(row,col);
    }

    bool checkWinCondition(Board* board, Symbol* symbol) override {
        int size = board->getSize();
        
        // Check rows
        for(int i = 0; i < size; i++) {
            bool win = true;
            for(int j = 0; j < size; j++) {
                if(board->getCell(i, j) != symbol) {
                    win = false;
                    break;
                }
            }
            if(win) return true;
        }
        
        // Check columns
        for(int j = 0; j < size; j++) {
            bool win = true;
            for(int i = 0; i < size; i++) {
                if(board->getCell(i, j) != symbol) {
                    win = false;
                    break;
                }
            }
            if(win) return true;
        }
        
        // Check main diagonal
        bool win = true;
        for(int i = 0; i < size; i++) {
            if(board->getCell(i, i) != symbol) {
                win = false;
                break;
            }
        }
        if(win) return true;
        
        // Check anti-diagonal
        win = true;
        for(int i = 0; i < size; i++) {
            if(board->getCell(i, size-1-i) != symbol) {
                win = false;
                break;
            }
        }
        return win;
    }
    
    // If all cells are filled and no winner
    bool checkDrawCondition(Board* board) override {
        int size = board->getSize();
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if(board->getCell(i, j) == board->getEmptyCell()) {
                    return false;
                }
            }
        }
        return true;
    }
};

class TicTacToe {
private:
    Board* board;
    deque<Player*> players;
    Rules* rules;
    vector<IObserver*> observers;
    bool gameOver;
public:
    TicTacToe(int size) {
        board = new Board(size);
        rules = new StandardRules();
        gameOver = false;
    }

    void addPlayer(Player* player) {
        players.push_back(player);
    }
    
    void addObserver(IObserver* observer) {
        observers.push_back(observer);
    }

    void notify(string msg) {
        for(auto observer : observers) {
            observer->update(msg);
        }
    }

    void play() {
        if(players.size() < 2) {
            cout << "Need at least 2 players!" << endl;
            return;
        }
        
        notify("Tic Tac Toe Game Started!");
        
        while(!gameOver) {
            board->display();
            
            // Take out the current player from dequeue
            Player* currentPlayer = players.front();
            cout << currentPlayer->getName() << " (" << currentPlayer->getSymbol()->getMark() << ") - Enter row and column: ";
            
            int row, col;
            cin >> row >> col;
            
            // check if move is valid
            if(rules->isValidMove(board, row, col)) {
                board->placeMark(row, col, currentPlayer->getSymbol());
                notify(currentPlayer->getName() + " played (" + to_string(row) + "," + to_string(col) + ")");
                
                if(rules->checkWinCondition(board, currentPlayer->getSymbol())) {
                    board->display();
                    cout << currentPlayer->getName() << " wins!" << endl;
                    currentPlayer->incrementScore();

                    notify(currentPlayer->getName() + " wins!");

                    gameOver = true;
                }
                else if(rules->checkDrawCondition(board)) {
                    board->display();
                    
                    cout << "It's a draw!" << endl;
                    notify("Game is Draw!");

                    gameOver = true;
                }
                else {
                    // Move player to back of queue
                    players.pop_front();
                    players.push_back(currentPlayer);
                }
            }
            else {
                cout << "Invalid move! Try again." << endl;
            }
        }
    }
    
    ~TicTacToe() {
        delete board;
        delete rules;
    }
};

enum GameType {
    STANDARD
};

class TicTacToeGameFactory {
public:
    static TicTacToe* createGame(GameType gt, int boardSize) {
        if(GameType::STANDARD == gt) {
            return new TicTacToe(boardSize);
        }
        return nullptr;
    }
};

int main() {
    
    cout << "=== TIC TAC TOE GAME ===" << endl;
    
    // Create game with custom board size
    int boardSize;
    cout << "Enter board size (e.g., 3 for 3x3): ";
    cin >> boardSize;
    
    TicTacToe* game = TicTacToeGameFactory::createGame(GameType::STANDARD, boardSize);
    
    // Add observer
    IObserver* notifier = new ConsoleNotifier();
    game->addObserver(notifier);
    
    // Create players with custom symbols
    Player* player1 = new Player(1, "gautam", new Symbol('X'));
    Player* player2 = new Player(2, "garima", new Symbol('O'));
    
    game->addPlayer(player1);
    game->addPlayer(player2);
    
    // Play the game
    game->play();
    
    // Cleanup
    delete game;
    delete player1;
    delete player2;
    delete notifier;
}
