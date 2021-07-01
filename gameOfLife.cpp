#include<bits/stdc++.h>
#define N 25
using namespace std;
int neighbourX[8]={0,1,1,1,0,-1,-1,-1};
int neighbourY[8]={1,1,0,-1,-1,-1,0,1};
fstream outputFile;
void generateInitialGlider(int universe[N][N]){
    int mid=N/2;
    universe[mid-1][mid]=1;
    universe[mid][mid+1]=1;
    universe[mid+1][mid+1]=1;
    universe[mid+1][mid]=1;
    universe[mid+1][mid-1]=1;
}
void printState(int universe[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            outputFile<<universe[i][j];
        }
        outputFile<<"\n";
    }
}
void generateNextState(int universe[N][N]){   
    int universeCopy[N][N];
    memset(universeCopy,0,sizeof(universeCopy));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            //Count live neighbours
            int liveNeighbours=0;
            for(int k=0;k<8;k++){
                if(!(i+neighbourX[k]<0||i+neighbourX[k]>=N||j+neighbourY[k]<0||j+neighbourY[k]>=N))
                    liveNeighbours+=universe[i+neighbourX[k]][j+neighbourY[k]];
            }
            //1. Any live cell with fewer than two live neighbors dies as if caused by underpopulation.
            if(universe[i][j]&&liveNeighbours<2)
                universeCopy[i][j]=0;
            //2. Any live cell with two or three live neighbors lives on to the next generation.
            else if(universe[i][j]&&liveNeighbours<=3)
                universeCopy[i][j]=1;
            //3. Any live cell with more than three live neighbors dies, as if by overcrowding.
            else if(universe[i][j]&&liveNeighbours>3)
                universeCopy[i][j]=0;
            //4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
            else if(!universe[i][j]&&liveNeighbours==3)
                universeCopy[i][j]=1;
        }
    }
    memcpy (universe, universeCopy, 25*25*sizeof(int));
}
int main()
{
    //NxN universe initially with all dead cells     
    int universe[N][N];
    //0 => dead, 1 => live
    memset(universe,0,sizeof(universe));
    //File where the output is stored
    outputFile.open("outputOfGame.txt",ios::out);
    //generate initial state with glider pattern
    outputFile<<"Initial state:\n";
    generateInitialGlider(universe);
    //print initial state
    printState(universe);
    //Generating and printing next states till the glider reaches the end
    while(!universe[N-1][N-1]){
        outputFile<<"\nNext State:\n";
        generateNextState(universe);
        printState(universe);
    }
    outputFile.close();
	return 0;
}