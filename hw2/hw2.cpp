/* 
 * Yasemin Arslan
 * 1901042263
 * CSE241 - hw2
 * 
 * Description: // N-puzzle using c++
 * 
 */
#include <iostream>

void get_board(char *file_name);
void print_board(int a[11][11], int row, int col);
void get_move();
void calculate_solution();
int intelligent();


using namespace std;
int counter=0;
int brd[11][11] = {0};
int brdcopy[11][11] = {0};
int gidx = 1;
int gjdx = 3;
int col = 4, row = 3;
int solution[11][11] = {0};
char currmove = 'X';
char prevmove = 'X';

int main(int argc, char *argv[]){
    if(argc == 2){
        get_board(argv[1]);
    }
    else{
        get_board(NULL);
        }

    calculate_solution();
    print_board(solution, 3, 4);
    print_board(brd, 3, 4);
    while(1){
        get_move();
        print_board(brd, 3, 4);
    }

}

void get_board(char *file_name){
    brd[1][1] = 0;
    brd[1][2] = 9;
    brd[1][3] = -1;
    brd[1][4] = 7;
    brd[2][1] = 1;
    brd[2][2] = 3;
    brd[2][3] = 5;
    brd[2][4] = 8;
    brd[3][1] = 2;
    brd[3][2] = 4;
    brd[3][3] = 6;
    brd[3][4] = 0;
}

void calculate_solution(){
    // create final board position based on input board
    int x = 1;
    for(int i=1; i<=row; i++){
        for(int j=1; j<=col; j++){
            if(brd[i][j] != 0){ 
                solution[i][j] = x++;
            }
        }
    }
    // replace the max value with bb = (-1)
    for(int i=1; i<=row; i++){
        for(int j=1; j<=col; j++){
            if(solution[i][j] == x-1){
                solution[i][j] = -1;
            }

        }
    }
}

void print_board(int a[11][11], int row, int col){
    for(int i=1; i<=row; i++){
        for(int j=1; j<=col; j++){
            if (a[i][j] == -1){
                cout << "bb";
                cout << " ";
            }
            else{
                cout << a[i][j];
                cout << "  ";
            }
        }  
        cout << endl ;
    }
    cout << endl ;
}

void get_move(){
    char move;
    cout << "Next move:";
    cin >> move;
    counter++;
    cout << endl;

    switch(move){
        case 'l':
        case 'L':
            if(brd[gidx][gjdx-1] != 0){
                int temp = brd[gidx][gjdx];
                brd[gidx][gjdx] = brd[gidx][gjdx-1];
                brd[gidx][gjdx-1] = temp;  
                gjdx--;   
            }
        break; 

        case 'r':
        case 'R':
            if (brd[gidx][gjdx+1] != 0){
                int temp = brd[gidx][gjdx];
                brd[gidx][gjdx] = brd[gidx][gjdx+1];
                brd[gidx][gjdx+1] = temp;
                gjdx++;
            }
            break;

        case 'u':
        case 'U':
            if (brd[gidx-1][gjdx] != 0){
                int temp = brd[gidx][gjdx];
                brd[gidx][gjdx] = brd[gidx-1][gjdx];
                brd[gidx-1][gjdx]= temp;
                gidx--;
            }
            break;

        case 'd':
        case 'D':
            if (brd[gidx+1][gjdx] != 0){
                int temp = brd[gidx][gjdx];
                brd[gidx][gjdx] = brd[gidx+1][gjdx];
                brd[gidx+1][gjdx] = temp;
                gidx++; 
            }
            break;

        case 'i':
        case 'I':
            intelligent();
            break;
        case 't':
        case 'T':
            cout << "Total number of moves : " << counter << endl ;
        
    }
}

int intelligent() {
    int temp;
    int min = 1000;
    int sum[4] = {1000, 1000, 1000, 1000};
    char moves[4] = {'L', 'R', 'U', 'D'};
    // create a temporary board
    for (int i=1; i<=row; i++) {
        for(int j=1; j<=col; j++){
            brdcopy[i][j] = brd[i][j];
        }
    }
    //test if left
    if(brdcopy[gidx][gjdx-1] != 0){
        int temp = brdcopy[gidx][gjdx];
        brdcopy[gidx][gjdx] = brdcopy[gidx][gjdx-1];
        brdcopy[gidx][gjdx-1] = temp;  
        sum[0] = 0;
        for (int i=1; i<=row; i++) {
            for(int j=1; j<=col; j++){ 
                sum[0] = sum[0] + abs(solution[i][j] - brdcopy[i][j]);
                brdcopy[i][j] = brd[i][j];
            }
        }
        //bring original board back
        for (int i=1; i<=row; i++) {
            for(int j=1; j<=col; j++){
                brdcopy[i][j] = brd[i][j];
            }
        }
    }
    //test if right
    if(brdcopy[gidx][gjdx+1] != 0){
        int temp = brdcopy[gidx][gjdx];
        brdcopy[gidx][gjdx] = brdcopy[gidx][gjdx+1];
        brdcopy[gidx][gjdx+1] = temp;  
        sum[1] = 0;
        for (int i=1; i<=row; i++) {
            for(int j=1; j<=col; j++){ 
                sum[1] = sum[1] + abs(solution[i][j] - brdcopy[i][j]);
                brdcopy[i][j] = brd[i][j];
            }
        }
        //bring original board back
        for (int i=1; i<=row; i++) {
            for(int j=1; j<=col; j++){
                brdcopy[i][j] = brd[i][j];
            }
        }
    }
    //test if up
    if(brdcopy[gidx-1][gjdx] != 0){
        int temp = brdcopy[gidx][gjdx];
        brdcopy[gidx][gjdx] = brdcopy[gidx-1][gjdx];
        brdcopy[gidx-1][gjdx] = temp;  
        sum[2] = 0;
        for (int i=1; i<=row; i++) {
            for(int j=1; j<=col; j++){ 
                sum[2] = sum[2] + abs(solution[i][j] - brdcopy[i][j]);
                brdcopy[i][j] = brd[i][j];
            }
        }
        //bring original board back
        for (int i=1; i<=row; i++) {
            for(int j=1; j<=col; j++){
                brdcopy[i][j] = brd[i][j];
            }
        }
    }
    //test if down
    if(brdcopy[gidx+1][gjdx] != 0){
        int temp = brdcopy[gidx][gjdx];
        brdcopy[gidx][gjdx] = brdcopy[gidx+1][gjdx];
        brdcopy[gidx+1][gjdx] = temp;  
        sum[3] = 0;
        for (int i=1; i<=row; i++) {
            for(int j=1; j<=col; j++){ 
                sum[3] = sum[3] + abs(solution[i][j] - brdcopy[i][j]);
                brdcopy[i][j] = brd[i][j];
            }
        }
        //bring original board back
        for (int i=1; i<=row; i++) {
            for(int j=1; j<=col; j++){
                brdcopy[i][j] = brd[i][j];
            }
        }
    }



    if (currmove == moves[0]){
        int temp = brd[gidx][gjdx];
        brd[gidx][gjdx] = brd[gidx][gjdx-1];
        brd[gidx][gjdx-1] = temp;
        gjdx--;

    }
    else if (currmove == moves[1]){
        int temp = brd[gidx][gjdx];
        brd[gidx][gjdx] = brd[gidx][gjdx+1];
        brd[gidx][gjdx+1] = temp;
        gjdx++;
    }
    else if (currmove == moves[2]){
        int temp = brd[gidx][gjdx];
        brd[gidx][gjdx] = brd[gidx-1][gjdx];
        brd[gidx-1][gjdx] = temp;
        gidx--;
    }
    else if (currmove == moves[3]){
        int temp = brd[gidx][gjdx];
        brd[gidx][gjdx] = brd[gidx+1][gjdx];
        brd[gidx+1][gjdx] = temp;
        gidx++;
    }   
    return 1;
}