#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int x = 0;
int y = 0;
int counter = 0;

void clearScreen(){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void displayBoard(int **board, int height, int width){
    clearScreen();
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            printf("%c ", board[i][j] ? 'O' : '.');
        }
        printf("\n");
    }
}

int countNeighbors(int **board, int x, int y, int height, int width){
   int count = 0;
   for(int i = -1; i <= 1; i++){
       for(int j = -1; j <= 1; j++){
           if(i == 0 && j == 0) continue;
           int col = (x + i + height) % height;
           int row = (y + j + width) % width;
           count += board[col][row];
       }
   }
   return count;
}

void updateBoard(int **board, int height, int width){
    int **newBoard = (int **)malloc(height * sizeof(int *));
    for(int i = 0; i < height; i++){
        newBoard[i] = (int *)malloc(width * sizeof(int));
    }  

    int unchanged = 1;
    
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int liveNeighbors = countNeighbors(board, i, j, height, width);

            if(board[i][j] == 1 && (liveNeighbors < 2 || liveNeighbors > 3)){
                
                newBoard[i][j] = 0; // Die of underpopulation or overpopulation
                unchanged = 0;
            } 
            else if(board[i][j] == 0 && liveNeighbors == 3){
                newBoard[i][j] = 1; // Become alive through reproduction
                unchanged = 0;
            } 
            else{
                newBoard[i][j] = board[i][j]; // Remain in the current state
            }
        }
    }
    if(unchanged){
        counter++;
    } 
    else{
        counter = 0;
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            board[i][j] = newBoard[i][j];
        }
        free(newBoard[i]);
    }
    free(newBoard);
}



int readConfig(char* configPath, int* width, int* height){
    FILE *file = fopen(configPath, "r");
    if(file == NULL){
        printf("Error: Config file not found.\n");
        return 1;
    }

    fscanf(file, "x=%d\ny=%d\n", width, height);
    fclose(file);
    return 0;
}

int main(){
    readConfig("config.txt", &x, &y);

    int padding = (4 - (x * 3) % 4) % 4;

    FILE *file = fopen("game_grid.bmp", "rb");
    if(file == NULL){
        printf("Error: Game grid file not found.\n");
        return 1;
    }

    fseek(file, 54, SEEK_SET);

    int **board = malloc(y * sizeof(int*));
    for(int i = 0; i < y; i++){
        board[i] = malloc(x * sizeof(int));
    }

    for(int i = y - 1; i >= 0; i--){
        for(int j = 0; j < x; j++){
            unsigned char pixel[3];
            fread(pixel, 1, 3, file);
            board[i][j] = (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0) ? 0 : 1;
        }
        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);

        displayBoard(board, y, x);
        system("pause");

    while(counter < 2){
        displayBoard(board, y, x);
        updateBoard(board, y, x);
        printf("Generation: %d\n", counter);
        usleep(300000);
    }

    for(int i = 0; i < y; i++){
        free(board[i]);
    }
    
    free(board);

    return 0;
}
