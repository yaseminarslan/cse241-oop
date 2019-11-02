/* 
 * Yasemin Arslan
 * CSE241 - hw3
 * 
 * Description: // N-puzzle using c++ with classes
 * 
 */
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

class Board
{
public:
    Board();
    void print();
    void readFromFile(string fname);
    void writeToFile(string fname);
    void reset();
    void setSize(int r, int c);
    int move(char m);
    bool isSolved();
    int swap_loc(int n);

private:
    int brd[11][11];
    int gi, gj;
    int row, column;
};

class NPuzzle
{
public:
    NPuzzle();
    void print();
    void printReport();
    void readFromFile(string fname);
    void writeToFile(string fname);
    void shuffle(int n);
    void reset();
    void setSize(int r);
    void setSize(int r, int c);
    void moveRandom();
    void moveIntelligent();
    void move(char m);
    void solvePuzzle();

private:
    Board b1;
    int row, column;
    long long int counter;
};

int main()
{
    NPuzzle p1;
    p1.setSize(3,5);
    p1.move('l');
    p1.print();
    cout << "Puzzle report: ";
    p1.printReport(); 
  
    char m;
    while(1){
        cout << "Next move:";
        cin >> m;
        cout << endl;
        p1.move(m);
        p1.print();
    }
}

// NPuzzle member functions

// constructor
NPuzzle::NPuzzle() 
{
    srand(time(NULL));
    counter = 0;
}

// print current configuration
void NPuzzle::print()
{
    b1.print();
}

// print report about moves and solution
void NPuzzle::printReport()
{
    cout << counter << " moves passed since reset" << endl;
    if (b1.isSolved()) {
        cout << "Board is solved" << endl;
    } else {
        cout << "Board is not solved" << endl;
    }
    cout << endl;
}

// reads board from file
void NPuzzle::readFromFile(string fname){
    b1.readFromFile(fname);
}

// writes board to file
void NPuzzle::writeToFile(string fname){
    b1.writeToFile(fname);
}

// make n random moves 
void NPuzzle::shuffle(int n){
    int nmoves = n;
    while(nmoves) {
        int x = 1 + (rand() % 4);
        if (b1.swap_loc(x)) {
            nmoves--;
        }
    }
}

void NPuzzle::reset(){
    b1.reset();
    counter = 0;
}

// set board to r x r
void NPuzzle::setSize(int r)
{
    row = r;
    column = r;
    b1.setSize(r, r);
}

// set board to r x c (overload)
void NPuzzle::setSize(int r, int c)
{
    row = r;
    column = c;
    b1.setSize(r, c);
}

// make a random move
void NPuzzle::moveRandom(){
    shuffle(1);
    counter++;
}

// make an intelligent move
// not complete
void NPuzzle::moveIntelligent(){
    shuffle(1);
    counter++;
}

// make a move
void NPuzzle::move(char m){
    int st;

    if (m == 'V' || m == 'v') {
        solvePuzzle();
    }
    else if (m == 'T' || m == 't') {
        printReport();
    }
    else if (m == 'I' || (m == 'i')) {
        moveIntelligent();
    }
    else if (m == 'S' || (m == 's')) {
        reset(); 
        shuffle(row*column);
        counter = 0;
    }
    else {
        st = b1.move(m);
        if (st == 1)
        {
            counter++;
        }
    }

}

// solve puzzle
// not complete
void NPuzzle::solvePuzzle(){
}

// Board member functions

// constructor
Board::Board()
{
    srand(time(NULL));
}

// prints board to cout
void Board::print()
{
    for(int i=1; i<=row; i++) {
        for(int j=1; j<=column; j++) {
            if(brd[i][j] == -1) {
                cout << "bb" << " ";
            }
            else{
                cout << setw(2) << brd[i][j] << " " ;
            }
        }
        cout << endl;
    }
    cout << endl;
}

// reads board from file
// not complete
void Board::readFromFile(string fname){
    cout << fname << endl ;
}

// writes board to file
// not complete
void Board::writeToFile(string fname){
    cout << fname << endl ;
}

// resets board to solution
void Board::reset()
{
    int x = 1;
    for(int i=1; i<=row; i++) {
        for(int j=1; j<=column; j++) {
            brd[i][j] = x++;
        }
    }
    brd[row][column] = -1;
    gi = row;
    gj = column;
}

// sets board size to given values. max 9
// reset board
void Board::setSize(int r, int c)
{
    if(r<3 || r>9) {
        cout << "WRONG SIZE";
    }
    else {
        row = r;
        column = c;
    }
    reset();
}

// make a move according to given char parameter
int Board::move(char m){
    string fname;
    int st = 0;

    switch(m){
        case 'l':
        case 'L':
            st = swap_loc(1);
            break; 

        case 'r':
        case 'R':
            st = swap_loc(2);
            break;

        case 'u':
        case 'U':
            st = swap_loc(3);
            break;

        case 'd':
        case 'D':
            st = swap_loc(4);
            break;

        case 'e':
        case 'E':
            cout << "Enter filename to save board:";
            cin >> fname;
            writeToFile(fname);
            break;

        case 'o':
        case 'O':
            cout << "Enter filename to read board:";
            cin >> fname;
            readFromFile(fname);
            break;
    }

    return st;
}

// check board is solved, return true
bool Board::isSolved()
{
    int x = 1;
    if(brd[row][column] != -1) {
        return false;
    }
    for(int i=1; i<=row; i++) {
        for(int j=1; j<=column; j++) {
            if ( brd[i][j] != x++) {
                if ((i != row) && (j != column)) {
                    return false;
                }
            }
        }
    }
    return true;
}

int Board::swap_loc(int n) {
    if(n == 1) { // swap left   
        if(brd[gi][gj-1] != 0) {
            brd[gi][gj] = brd[gi][gj-1];
            brd[gi][--gj] = -1;
            return 1;
        }
    }
    else if (n == 2) { // swap right
        if(brd[gi][gj+1] != 0){
            brd[gi][gj] = brd[gi][gj+1];
            brd[gi][++gj] = -1;
            return 1;
        }        
    }
    else if (n == 3) { // swap up    
        if(brd[gi-1][gj] != 0){
            brd[gi][gj] = brd[gi-1][gj];
            brd[--gi][gj] = -1;
            return 1;
        }
    }
    else if (n == 4) { // swap down
        if(brd[gi+1][gj] != 0){
            brd[gi][gj] = brd[gi+1][gj];
            brd[++gi][gj] = -1;
            return 1;
        }
    }
    return 0;
}
