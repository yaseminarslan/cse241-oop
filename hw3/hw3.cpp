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
#include <cmath>
#include <fstream>

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
    int getScore();


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
    p1.setSize(3,3);
    //p1.move('l');
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
    int min = 100000;
    char m;
    int s = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0;

    Board bUp = b1;
    s = bUp.move('u');
    if (s == 1) {
        s1 = bUp.getScore();
        min = s1;
        m = 'u';
    }
    Board bDown = b1;
    s = bDown.move('d');
    if (s == 1) {
        s2 = bDown.getScore();
        if (s2 < min) {
            min = s2;
            m = 'd';
        }
    }

    Board bLeft = b1;
    s = bLeft.move('l'); 
    if (s == 1) {
        s3 = bLeft.getScore();
        if (s3 < min) {
            min = s3;
            m = 'l';
        }
    }

    Board bRight = b1;
    s = bRight.move('r');
    if (s == 1) {
        s4 = bRight.getScore();
        if (s4 < min) {
            min = s4;
            m = 'r';
        }
    }

    b1.move(m);
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
    int c = 0;
    while(!b1.isSolved()) {
        if (c == 4) {
            c = 0;
            moveRandom(); 
        } else {
            moveIntelligent();
        }
        c++;
        b1.print();
    }
    printReport();
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
                if (brd[i][j] < 10){
                    cout << '0';
                }
                cout << brd[i][j] << " " ;
            }
        }
        cout << endl;
    }
    cout << endl;
}

// reads board from file
void Board::readFromFile(string fname){
    char c;
    ifstream fin(fname);
    int i = 1;
    int j = 1;
    
    while(fin.get(c)) {
        if (c == ' ')
        {
            j++;
        }
        else if (c == '\n')
        {   
            i++;
            column = j;
            j = 1;
        }
        else if (c == 'b')
        {
            fin.get(c);
            brd[i][j] = -1;
            gi = i;
            gj = j;
        }
        else 
        {
            int x = int(c-48);
            fin.get(c);
            x = x*10 + int(c-48);
            brd[i][j] = x;
        }
    }
    row = i;
    fin.close();
}

// writes board to file
void Board::writeToFile(string fname){

    ofstream fout(fname);
    
    for(int i=1; i<=row; i++) {
        for(int j=1; j<=column; j++) {
            if(brd[i][j] == -1) {
                fout << "bb" << " ";
            }
            else{
                if (brd[i][j] < 10) 
                    fout << '0';
                fout << brd[i][j] << " " ;
            }
        }
        fout << endl;
    }
    fout << endl;
    fout.close();
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
    for(int i=1; i<=row; i++) {
        for(int j=1; j<=column; j++) {
            if ( brd[i][j] != x) {
                if (!((i == row) && (j == column))) {
                    return false;
                }
            }
            x++;
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

// compare current board to solution
int Board::getScore(){
    int sum = 0;
    int idx = 1;
    for(int i=1; i<=row; i++){
        for(int j=1; j<=column; j++){
            sum = sum + (int)(abs(brd[i][j] - idx) * ((float)row*column/idx));
            idx++;
        }
    }
    return sum;
}
