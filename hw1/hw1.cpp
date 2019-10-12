#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

void print_puzzle();
int getmove();
void shuffle(int number);
int check_puzzle();
int intelligent();

using namespace std;

int *puzzle;
int *puzzlecopy;
int col;
int gidx, gjdx;

int main()
{
    int cont = 1;
    int i, j;
    srand(time( NULL ));
    cout << "Choose your puzzle size (3-9): ";
    cin >> col;
    cout << endl;

    puzzle = new int[col*col];
    puzzlecopy = new int[col*col];

    for(i=0; i<col; i++) {
        for(j=0; j<col; j++) {
            puzzle[col*i + j] = col*i + j+1;
        }
    }
    puzzle[col*col-1] = 0;
    //kaldir
    // puzzle[col*col-1] = 8;
    // puzzle[col*col-2] = 7;
    // puzzle[col*col-3] = 0;

    print_puzzle();
    // ac
    shuffle(col*col);
    while(!check_puzzle() && cont) {
        print_puzzle();
        cont = getmove();
    }
    print_puzzle();
}

void print_puzzle(){
    for(int i=0; i<col; i++) {
        for(int j=0; j<col; j++) {
            if (puzzle[i*col + j] == 0) {
                gidx = i;
                gjdx = j;
                cout << setw(5) << " ";
            } else {
                cout << setw(5) << puzzle[i*col + j];
            }
        }
        cout << endl ;
    }
    cout << endl ;
}


void shuffle(int number ){
    int size = col*col;
    for(int i=0; i<number; i++){
        int v1= rand()% size;
        int v2= rand()% size;
    
        int temp = puzzle[v1];
        puzzle[v1] = puzzle[v2];
        puzzle[v2] = temp;

    }     
}

int getmove(){
    char move;
    cout << "Next move: ";
    cin >> move;
    cout << endl;
    //cout << gidx << " " << gjdx << endl;

    switch(move){
        case 'l':
        case 'L':
            if (gjdx > 0){
                int temp = puzzle[gidx*col + gjdx];
                puzzle[gidx*col + gjdx] = puzzle[gidx*col + gjdx-1];
                puzzle[gidx*col + gjdx-1] = temp;
            } else {
                cout << "cant moves the empty cell to left" << endl;
            }
            break;
        case 'r':
        case 'R':
            if (gjdx < col-1){
                int temp = puzzle[gidx*col + gjdx];
                puzzle[gidx*col + gjdx] = puzzle[gidx*col + gjdx+1];
                puzzle[gidx*col + gjdx+1] = temp;
            } else {
                cout << "cant moves the empty cell to right" << endl;
            }
            break;
        case 'u':
        case 'U':
            if (gidx > 0){
                int temp = puzzle[gidx*col + gjdx];
                puzzle[gidx*col + gjdx] = puzzle[(gidx-1)*col + gjdx];
                puzzle[(gidx-1)*col + gjdx] = temp;
            } else {
                cout << "cant moves the empty cell to up" << endl;
            }
            break;
        case 'd':
        case 'D':
            if (gidx < col-1){
                int temp = puzzle[gidx*col + gjdx];
                puzzle[gidx*col + gjdx] = puzzle[(gidx+1)*col + gjdx];
                puzzle[(gidx+1)*col + gjdx] = temp;
            } else {
                cout << "cant moves the empty cell to down" << endl;
            }
            break;

        case 'i':
        case 'I':
            intelligent();
            break;

        case 's':
        case 'S':
            shuffle(col*col);
            break;

        case 'q':
        case 'Q':
            return 0;
            break;    
    }

    return 1;
}


int check_puzzle(){
    for(int i=1; i<(col*col); i++){
        if(i != puzzle[i-1]){
            return 0;
        }
    }
    return 1;
}

int intelligent() {
    int temp, min;
    int  sum = 0, sum1 = 10000, sum2 = 10000, sum3 = 10000, sum4 = 10000;
    for(int i=1; i<(col*col); i++){
        sum = sum + abs(i - puzzle[i-1]);
    }
    for (int i=0; i<col*col; i++) {
        puzzlecopy[i] = puzzle[i];
    }
    if (gjdx > 0){
        int temp = puzzlecopy[gidx*col + gjdx];
        puzzlecopy[gidx*col + gjdx] = puzzlecopy[gidx*col + gjdx-1];
        puzzlecopy[gidx*col + gjdx-1] = temp;
        sum1 = 0;
        for(int i=1; i<(col*col); i++){
            sum1 = sum1 + abs(i - puzzlecopy[i-1]);
        }
    }
    for (int i=0; i<col*col; i++) {
        puzzlecopy[i] = puzzle[i];
    }
    if (gjdx < col-1){
        int temp = puzzlecopy[gidx*col + gjdx];
        puzzlecopy[gidx*col + gjdx] = puzzlecopy[gidx*col + gjdx+1];
        puzzlecopy[gidx*col + gjdx+1] = temp;
        sum2 = 0;
        for(int i=1; i<(col*col); i++){
            sum2 = sum2 + abs(i - puzzlecopy[i-1]);
        }
    }
    for (int i=0; i<col*col; i++) {
        puzzlecopy[i] = puzzle[i];
    }    
    if (gidx > 0){
        int temp = puzzlecopy[gidx*col + gjdx];
        puzzlecopy[gidx*col + gjdx] = puzzlecopy[(gidx-1)*col + gjdx];
        puzzlecopy[(gidx-1)*col + gjdx] = temp;
        sum3 = 0;
        for(int i=1; i<(col*col); i++){
            sum3 = sum3 + abs(i - puzzlecopy[i-1]);
        }
    }
    for (int i=0; i<col*col; i++) {
        puzzlecopy[i] = puzzle[i];
    }
    if (gidx < col-1){
        int temp = puzzlecopy[gidx*col + gjdx];
        puzzlecopy[gidx*col + gjdx] = puzzlecopy[(gidx+1)*col + gjdx];
        puzzlecopy[(gidx+1)*col + gjdx] = temp;
        sum4 = 0;
        for(int i=1; i<(col*col); i++){
            sum4 = sum4 + abs(i - puzzlecopy[i-1]);
        }
    }
    //cout << sum1 << endl << sum2 << endl << sum3 << endl << sum4 << endl;
    
    min = 10000;
    if(sum1 < min) {min = sum1;}
    if(sum2 < min) {min = sum2;}
    if(sum3 < min) {min = sum3;}
    if(sum4 < min) {min = sum4;}

    if (min == sum1){
        int temp = puzzle[gidx*col + gjdx];
        puzzle[gidx*col + gjdx] = puzzle[gidx*col + gjdx-1];
        puzzle[gidx*col + gjdx-1] = temp;
    }
    else if (min == sum2){
        int temp = puzzle[gidx*col + gjdx];
        puzzle[gidx*col + gjdx] = puzzle[gidx*col + gjdx+1];
        puzzle[gidx*col + gjdx+1] = temp;
    }
    else if (min == sum3){
        int temp = puzzle[gidx*col + gjdx];
        puzzle[gidx*col + gjdx] = puzzle[(gidx-1)*col + gjdx];
        puzzle[(gidx-1)*col + gjdx] = temp;
    }
    else if (min == sum4){
        int temp = puzzle[gidx*col + gjdx];
        puzzle[gidx*col + gjdx] = puzzle[(gidx+1)*col + gjdx];
        puzzle[(gidx+1)*col + gjdx] = temp;
    }   
    return 1;
}