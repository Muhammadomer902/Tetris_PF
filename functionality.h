/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float& timer, float& delay, int& colorNum){
    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
        if (!anamoly()){
            for(int i = 0;i<4;i++)
              gameGrid[point_2[i][1]][point_2[i][0]] =colorNum;
             colorNum=1+rand()%7;
            int n=rand()%7;
            //--- Un-Comment this Part When You Make BLOCKS array---//

                for (int i=0;i<4;i++){
                    point_1[i][0] = BLOCKS[n][i] % 2;
                    point_1[i][1] = BLOCKS[n][i] / 2;
                }

        }
        timer=0;
    }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
//<--Game ending automaticaly if any block reaches the maximum hieght(M) or more once it is placed on an other block-->//

bool Gameover(int M,int N)
{
 bool linefull= false;
 for(int i = 0;i<N;i+=1)
 {
  if(gameGrid[0][i])
  linefull = true;
 }
 return linefull;
}

//<--Movement of block using arrow keys(left and right) but not moving out of bound-->//

void movementofblocks(int& delta_x)
{ 
 for (int i=0;i<4;i++)
 {
  point_2[i][0]=point_1[i][0];
  point_1[i][0]+=delta_x;
 }
 delta_x=0;
 if(!anamoly())
 for (int i=0;i<4;i++)
 {
  point_1[i][0]=point_2[i][0];
 }
}

//<--the block falls faster until the down key is pressed-->//

void fastfalle(float& delay)
{
 delay = 0.3;
}
void fastfallh(float& delay)
{
 delay = 0.1;
}

//<--for the rotation of block using the up key-->//

void rotationofblock(bool& rotate)
{
 if(rotate)
 {
  int centerxaxis=point_1[2][0];
  int centeryaxis=point_1[2][1];
  for(int i = 0;i<4;i+=1)
  {
   point_2[i][0]=point_1[i][0];
   point_2[i][1]=point_1[i][1];
   int rotationaroundxaxis=0;
   int rotationaroundyaxis=0;
   rotationaroundxaxis=point_1[i][1]-centeryaxis;
   rotationaroundyaxis=point_1[i][0]-centerxaxis;
   point_1[i][0]=centerxaxis-rotationaroundxaxis;
   point_1[i][1]=centeryaxis+rotationaroundyaxis;
  }
  if(!anamoly())
  for (int i=0;i<4;i++)
  {
   point_1[i][0]=point_2[i][0];
   point_1[i][1]=point_2[i][1];
  }
 }
 rotate = 0;
}

//<--Once a row is filled up it is deleted and the blocks above it take there place-->//

void deleteline(int M, int N, int& lineduring1fall)
{
 for (int i = M-1; i>0;i-=1)
 {
  int count = 0 ;
  for(int j = 0; j<N;j+=1)
  {
   if(gameGrid[i][j])
   count+=1;
   if(count==N)
   {
    lineduring1fall+=1;
    for(int r = i; r>0;r-=1)
    { 
     for(int c = 0;c<N;c+=1)
     gameGrid[r][c]=gameGrid[r-1][c];
    }
   }
  }
 }
}

//<--space for imidiately fall-->//

void spacefall (bool& space, float& delay)
{
 while(space)
 {
  for (int i=0;i<4;i++)
  { 
   point_2[i][1]=point_1[i][1];
   point_1[i][1]+=1;
  }
  if(!anamoly())
  for (int i=0;i<4;i++)
  {
   point_1[i][1]=point_2[i][1];
     space = 0;
  }
 }
}

//<--to maintain score-->//

void scorecounting (int& lineduring1fall, int& score)
{
 switch(lineduring1fall)
 {
  case(1):score+=10;
          std::cout<<"score now is: "<<score<<std::endl;
  break;
  case(2):score+=30;
          std::cout<<"score now is: "<<score<<std::endl;
  break;
  case(3):score+=60;
          std::cout<<"score now is: "<<score<<std::endl;
  break;
  case(4):score+=100;
          std::cout<<"score now is: "<<score<<std::endl;
 }
  lineduring1fall=0;
}
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////























/*void deleteline(int M, int N)
{
 int verticalmax = M-1;
 for(int i = verticalmax;i>0;i-=1)
 {
  int count = 0;
  for(int c = 0;c<N;c+=1)
  {
   if(gameGrid[i][c])
   count+=1;
   gameGrid[verticalmax][c]=gameGrid[i][c];
  }
  if(count<N)
  verticalmax-=1;
 }
}*/
