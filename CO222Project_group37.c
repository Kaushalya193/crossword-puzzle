//adding libraries.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//functions are defined here.
void crosscheck();
void checkvertically();
void checkhorizontaly();


char puzzle[1000][1000];  // multidimentional array for store puzzle.
char w[1000][1000]; //multidementional array for store words.

char puzzlecopy[1000][1000];
char newpuz[1000][1000]; //final puzzle will be stored here.

int col,row=0,isvalid=1,isPrint=1,isPrinth=1,fillcount=0;
int wordcount=0;
char block[1000];

int main(){
    char puzzleline[100],word[100];  // puzzle and words will be stored line by line here.
    int a=0;
    //loop to get puzzle.
    while (scanf("%[^\n]%*c",puzzleline)==1){

            int i;

            for ( i=0;puzzleline[i]!='\0';i++){

                //checking for find invalid input.
                if ((puzzleline[i]!='#') && (puzzleline[i]!='*') && ((puzzleline[i]<65) || ((puzzleline[i]>91) && (puzzleline[i]<97)) || (puzzleline[i]>122)) ){
                isvalid=0;
                break;     //if invalid input is found,then loop is breaked.
                }

                puzzle[row][i]=puzzleline[i];  // input puzzle is stored line by line to array.
            }


            if (row==0)
                    col=i;  //length of the first line stored to col.


            if ((i!=col) || (isvalid==0)) { //check whether length of the line is equal to length of the first line.
                isvalid=0;
                printf("INVALID INPUT");
                a=1;
                break;
                }


        row++;

    }

    //getting words to w[1000][1000] array.
    if (isvalid==1){
            scanf("\n");

            while (scanf("%[^\n]%*c",word)==1){
                int wordlen;
                for ( wordlen=0;word[wordlen]!='\0';wordlen++){
                    w[wordcount][wordlen]=word[wordlen];

                }
                wordcount++;

            
            }
            crosscheck();

            if(fillcount!=wordcount){
                printf("IMPOSSIBLE\n");
                return 0;
            }


            for(int r=0;r<row;++r){
                for(int c=0;c<col;++c){
                    printf("%c",newpuz[r][c]);
                }
                printf("\n");
            }




    }else{ if(a==0){
        printf("INVALID INPUT");}
        return 0;
        }



    return 0;
}


//function for filling crossing words.
void crosscheck(){
    for(int r=0;r<row;++r){
        for (int c=0;c<col;++c){
            if((puzzle[r][c]=='#') || ((puzzle[r][c]>='A') && (puzzle[r][c]<='Z')) || ((puzzle[r][c]>='a') && (puzzle[r][c]<='z')) ){


                //identify the crosspoint
                if(((/*r+1*/(puzzle[r+1][c]=='#') || ((puzzle[r+1][c]>='A') && (puzzle[r+1][c]<='Z')) || ((puzzle[r+1][c]>='a') && (puzzle[r+1][c]<='z')))||
                    (/*r-1*/(puzzle[r-1][c]=='#') || ((puzzle[r-1][c]>='A') && (puzzle[r-1][c]<='Z')) || ((puzzle[r-1][c]>='a') && (puzzle[r-1][c]<='z'))))&&
                   ((/*c+1*/(puzzle[r][c+1]=='#') || ((puzzle[r][c+1]>='A') && (puzzle[r][c+1]<='Z')) || ((puzzle[r][c+1]>='a') && (puzzle[r][c+1]<='z'))) ||
                   (/*c-1*/(puzzle[r][c-1]=='#') || ((puzzle[r][c-1]>='A') && (puzzle[r][c-1]<='Z')) || ((puzzle[r][c-1]>='a') && (puzzle[r][c-1]<='z'))))){

                    int c1,r1,hwlen=0,vwlen=0 ,hstart, vstart;

                    //take horizontal length of the space
                    for(c1=0;c1<col;++c1){
                        if((puzzle[r][c1]=='#') || ((puzzle[r][c1]>='A') && (puzzle[r][c1]<='Z')) || ((puzzle[r][c1]>='a') && (puzzle[r][c1]<='z')) ){
                            ++hwlen;

                            if(c1==0 || puzzle[r][c1-1]=='*'){
                                hstart=c1;
                                //column number of the starting point of the horizontal space that cross
                            }

                            if(puzzle[r][c1+1]=='*'){//counting stops at the end point of the space
                                break;
                            }
                        }


                    }


                    //take vertical length of the space
                    for(r1=0;r1<row;++r1){
                        if((puzzle[r1][c]=='#') || ((puzzle[r1][c]>='A') && (puzzle[r1][c]<='Z')) || ((puzzle[r1][c]>='a') && (puzzle[r1][c]<='z')) ){
                            vwlen++;
                            //
                            if(r1==0 || puzzle[r1-1][c]=='*'){
                                vstart=r1;
                                //row number of the starting point of the vertical space that cross

                            }
                            if(puzzle[r1+1][c]=='*'){
                                break;//counting stops at the end of the array
                            }
                        }


                    }


                    int lcount=0;

                    for(int hw=0;hw<wordcount;++hw){
                        if(strlen(w[hw])==hwlen){
                                for(int c2=0;c2<hwlen;++c2){
                                                if(puzzle[r][hstart+c2]=='#' ||(puzzle[r][hstart+c2]==w[hw][c2])){
                            //Check whether the space in the grid contains letters. if so letter matches to the letter at the particular position of the chosen word.
                                                    ++lcount;
                                                }
                                            }
                            if(lcount==hwlen){
                                    //if the space in the grid contains letters and if it is not the letter at that position in the word it won't fill
                                    //printf("%d\n",lcount);
                                    lcount=0;
                                    //lcount variable is set back to 0 to use it check whether letters match in the vertical space.

                            for(int vw=0;vw<wordcount;++vw){
                                    if(strlen(w[vw])==vwlen){
                                        for (int r2=0;r2<vwlen;++r2){
                                            if(puzzle[vstart+r2][c]=='#' ||(puzzle[vstart+r2][c]==w[hw][r2])){
                                                    ++lcount;
                                                }
                                            }
                                //again check if the grid space contains letters, then those match to letters in the selected word

                                if(lcount==vwlen){

                                        lcount=0;

                    //get the place where same letter should appear in the word or in other words, choose the matching word that have same length and similar letter in the same place.

                                        if((w[hw][c-hstart]==w[vw][r-vstart])&&(w[hw]!=w[vw])){

                                            //print horizontal word
                                            for(int c2=0;c2<hwlen;++c2){

                                                puzzle[r][hstart+c2]=w[hw][c2];
                                            }
                                            //print vertical word
                                            for(int r2=0;r2<vwlen;++r2){
                                                puzzle[vstart+r2][c]=w[vw][r2];
                                            }
                                            strcpy(w[hw],"\n");
                                            strcpy(w[vw],"\n");
                                            // remove the filled word from the w array. so, those words will not considered for next steps

                                            fillcount=fillcount+2;
                                            //fillcount is taken to get the count of how many words have been filled. after filling if fillcount = wordcount then, all the words are included in the grid
                                        }
                            }
                                    }

                            }
                        }

                        }
                    }

                    }


                }



            }
    }

    for(int r3=0;r3<row;++r3){
        for(int c3=0;c3<col;++c3){
            puzzlecopy[r3][c3]=puzzle[r3][c3];
            
        }
        
    }
    checkvertically();
}


//function for filling vertical remaining words.
void checkvertically(){

    for (int i=0;i<row;i++){
        for(int j=0;j<col;j++){

            if ((puzzle[i][j]=='#') || ((puzzle[i][j]>='A') && (puzzle[i][j]<='Z')) || ((puzzle[i][j]>='a') && (puzzle[i][j]<='z'))){

                int point1=i,I=i;
                int k=0;

                //identify vertical word starting point.
                if ((puzzle[point1+1][j]=='#') || ((puzzle[point1+1][j]>='A') && (puzzle[point1+1][j]<='Z')) || ((puzzle[point1+1][j]>='a') && (puzzle[point1+1][j]<='z')) ){

                    //take the vertical word space to string variable named block.
                    while ((puzzle[I][j]=='#') || ((puzzle[I][j]>='A') && (puzzle[I][j]<='Z')) || ((puzzle[I][j]>='a') && (puzzle[I][j]<='z')) ){

                            block[k]=puzzle[I][j];
                            puzzle[I][j]='@';
                            k++;I++;

                    }
                    block[k]='\0';
                    

                    //iterate through words for find suitable word for space.
                    int x;
                    for ( x=0;x<wordcount;x++){

                        if (strlen(w[x])==strlen(block)){

                            int t;
                            for ( t=0;block[t]!='\0';t++){
                                if(block[t]!='#'){
                                    //checking the equality of charactors in block to the letter in the word.
                                    if (block[t]!=w[x][t]){
                                        break;
                                    }
                                }

                            }

                            //if all the conditions is matched, word is print to the space.
                            if ((block[t+1]=='\0')&&((block[t]==w[x][t]) ||(block[t]=='#'))){
                                    for(int k=0;block[k]!='\0';k++){
                                            puzzlecopy[point1][j]=w[x][k];
                                            point1++;
                                    }

                                    strcpy(w[x],"\n");    //remove the filled word by adding new line charactor to w[][].
                                    fillcount=fillcount+1;
                                    break;
                            }


                        }
                    }
                }
            }
        }
    }

    //final output of this function is copied to array named newpuz.
    for(int r3=0;r3<row;++r3){
        for(int c3=0;c3<col;++c3){
            newpuz[r3][c3]=puzzlecopy[r3][c3];

        }

    }
    //callling function here to fill remaining horizontal words.
    checkhorizontaly();

}


//function for filling horizontal words.
void checkhorizontaly(){
    for (int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if ((puzzlecopy[i][j]=='#') || ((puzzlecopy[i][j]>='A') && (puzzlecopy[i][j]<='Z')) || ((puzzlecopy[i][j]>='a') && (puzzlecopy[i][j]<='z'))){

                    int J=j,point2=j;
                    int k=0;
                    //identify horizontal word starting point.
                    if ((puzzlecopy[i][point2+1]=='#') || ((puzzlecopy[i][point2+1]>='A') && (puzzlecopy[i][point2+1]<='Z')) || ((puzzlecopy[i][point2+1]>='a') && (puzzlecopy[i][point2+1]<='z')) ){

                        //take the horizontal word space to string variable named block.
                        while ((puzzlecopy[i][J]=='#') || ((puzzlecopy[i][J]>='A') && (puzzlecopy[i][J]<='Z')) || ((puzzlecopy[i][J]>='a') && (puzzlecopy[i][J]<='z')) ){

                                block[k]=puzzlecopy[i][J];
                                puzzlecopy[i][J]='@';
                                k++;J++;

                        }
                        block[k]='\0';

                        
                        int x;
                        //iterate through words for find suitable word for space.
                        for ( x=0;x<wordcount;x++){

                            if (strlen(w[x])==strlen(block)){
                                
                                int t;
                                for ( t=0;block[t]!='\0';t++){
                                    //checking the equality of charactors in block to the letter in the word.
                                    if(block[t]!='#'){
                                        if (block[t]!=w[x][t])
                                        break;
                                    }

                                }

                                 //if all the conditions is matched, word is print to the space.
                                if ((block[t+1]=='\0')&&((block[t]==w[x][t]) ||(block[t]=='#'))){
                                    
                                    for(int k=0;block[k]!='\0';k++){
                                        newpuz[i][point2]=w[x][k];

                                        point2++;
                                        }

                                    strcpy(w[x],"\n");   //remove the filled word by adding new line charactor to w[][].
                                    fillcount=fillcount+1;
                                    break;


                                }
                            }
                        }
                    }
                }
            }

    }   
}

