#include<stdbool.h>
#include<stdint.h>
#include<strings.h>
#include<stdio.h>
#include<stdlib.h>


#define BOARD_SIZE 8
#define EMPTY      0
#define QUEEN      1


static int board[BOARD_SIZE][BOARD_SIZE];

void init_board() {
    bzero(board, BOARD_SIZE*BOARD_SIZE*sizeof(int));
}

bool on_board(const uint8_t x, const uint8_t y) {
    return (x < BOARD_SIZE) && (y < BOARD_SIZE);
}

bool set(const uint8_t x, const uint8_t y, const bool what) {
    if( ! on_board(x,y) ) return false;
    board[x][y] = what ? QUEEN : EMPTY;
    return true;
}

bool unset_queen(const uint8_t x, const uint8_t y) {
    return set(x,y,false);
}

bool set_queen(const uint8_t x, const uint8_t y) {
    return set(x,y,true);
}

bool valid_diagonals(const uint8_t d) {
    if(d >= BOARD_SIZE) return false;
    const uint8_t l = BOARD_SIZE-1;
    uint8_t qw = 0;
    uint8_t qe = 0;
    uint8_t qn = 0;
    uint8_t qs = 0;
    for(uint8_t i=0; i<BOARD_SIZE; i++) {
        if( on_board(d-i,i) )   qw += board[d-i][i];
        if( on_board(l-i,d+i) ) qs += board[l-i][d+i];
        if( on_board(d-i,l-i) ) qe += board[d-i][l-i];
        if( on_board(l-i,d-i) ) qn += board[l-i][d-i];
    }
    return (qw <= 1) && (qe <= 1) && (qn <= 1) && (qs <= 1);
}

bool valid_column(const uint8_t c) {
    if(c >= BOARD_SIZE) return false;

    uint8_t queens = 0;
    for(uint8_t r=0; r<BOARD_SIZE; r++) queens += board[r][c];
    return queens <= 1;
}

bool valid_row(const uint8_t r) {
    if(r >= BOARD_SIZE) return false;

    uint8_t queens = 0;
    for(uint8_t c=0; c<BOARD_SIZE; c++) queens += board[r][c];
    return queens <= 1;
}

bool is_valid() {
    for(int i=0; i<BOARD_SIZE; i++) {
        if( valid_diagonals(i) && valid_column(i) && valid_row(i) ) continue;
        return false;
    }
    return true;
}


void print_board() {
    for(int r=0; r<BOARD_SIZE; r++) {
        fputs("+---+---+---+---+---+---+---+---+\n|",stdout);
        for(int c=0; c<BOARD_SIZE; c++) {
            printf(" %c |", board[r][c] == QUEEN ? 'Q' : ' ');
        }
        puts("");
    }
    puts("+---+---+---+---+---+---+---+---+");
}


bool recursive_solve(uint8_t queens, int r) {
    if(!queens) return true;

    for(int c=0; c<BOARD_SIZE; c++) {
        if(board[r][c] == QUEEN) break;
        set_queen(r,c);
        if( !is_valid() || !recursive_solve(queens-1,r+1)) unset_queen(r,c);
        else return true;
    }
    return false;
}

bool solve_queen_problem(const uint8_t queens) {
    if(queens > BOARD_SIZE) return false;
    init_board();
    return recursive_solve(queens,0);
}


int main() {
    solve_queen_problem(BOARD_SIZE);
    print_board();
}
