#include "AStar.hh"


using namespace std;


bool AStar::min(ExtendedPoint* p1, ExtendedPoint* p2){

  if( p1->f < p2->f ) return true;
  else return false;

}

AStar::AStar(): OpenList( &min ), Rows(0), Cols(0) { 

  Map = NULL;

}

AStar::AStar( string DataFileName ): OpenList( &min ), Rows(0), Cols(0), 
				     StartPoint(0,0,0,0){

  FILE* DataFile;
  int i,j;

  Map = NULL;

  DataFile = fopen( DataFileName.c_str(), "r" );

  if( DataFile ){

    fscanf(DataFile, "%i", &Rows);
    fscanf(DataFile, "%i", &Cols);
    Goal.x = Rows-1;
    Goal.y = Cols-1;

    Map = new unsigned char* [Rows];

    for( i=0; i < Rows; i++ ){
      Map[i] = new unsigned char [Cols];
    }

    for( i=0; i < Rows; i++ ){
      for( j=0; j < Cols; j++ ){

	fscanf(DataFile,"%hu",(Map[i]+j));

      }
    }

    fclose(DataFile);

  }
}

AStar::~AStar(){

  int i;

  if( Map != NULL ){

    for( i=0; i < Rows; i++ ){
      if( Map[i] != NULL ) delete Map[i];
    }

    delete Map;

  }

  OpenList.Erase();


}

void AStar::ShowMap(){

  int i,j;

  for( i=0; i < Rows; i++ ){
    for( j=0; j < Cols; j++ ){
      printf("%x\t",Map[i][j]);
    }
    printf("\n");
  }

}

int AStar::DetermineDir( int i, int j ){

  int sum = i+j+3;

  if( i <= j ) return sum;
  else return 10 - sum;

}

Point AStar::ReverseDir( int x ){

  Point p;

  switch( x ){
  case 1:{ p.x = 1; p.y = 1; break; }
  case 2:{ p.x = 1; p.y = 0; break; }
  case 3:{ p.x = 1; p.y = -1; break; }
  case 4:{ p.x = 0; p.y = -1; break; }
  case 5:{ p.x = -1; p.y = -1; break; }
  case 6:{ p.x = -1; p.y = 0; break; }
  case 7:{ p.x = -1; p.y = 1; break; }
  case 8:{ p.x = 0; p.y = 1; break; }
  default:{ p.x = 0; p.y = 0; break; }
  }

  return p;

}

double AStar::Heuristic( ExtendedPoint p ){

  Point dist = Goal - p;
  return (abs(dist.x) + abs(dist.y));

}

void AStar::AddNeighbours( ExtendedPoint p ){

  int i,j,x,y;
  ExtendedPoint neighbour;
  bool admisible;
  x = p.x;
  y = p.y;

  for( i=-1; i <= 1; i++ ){
    for( j=-1; j <= 1; j++ ){
      if( !((i==0)&&(j==0)) ){
	admisible = (x+i >= 0) && (y+j >= 0) && (x+i < Rows) && (y+j < Cols);
	if( admisible ){
	  if( Map[x+i][y+j] == 0 ){

	    Map[x+i][y+j] += (DetermineDir(i,j) << 4);
	    neighbour.x = x+i;
	    neighbour.y = y+j;
	    neighbour.g = p.g+1;
	    neighbour.f = neighbour.g + Heuristic( neighbour );
	    OpenList.Add(neighbour);

	  }

	}
      }
    }
  }

}

void AStar::Run(){

  ExtendedPoint actual( StartPoint );
  int x,y,iterations;
  Point ref;

  while( !(actual == Goal) ){

    x = static_cast<int>(actual.x);
    y = static_cast<int>(actual.y);

    //Map[x][y] = 0x20 + Map[x][y];
    AddNeighbours( actual );
    if( OpenList.Length() == 0 ){

      printf("No feasible solution!\n");
      break;

    }
    else{

      actual = OpenList.Root();
      OpenList.Rmv(0);

    }

  }

  cout << "Znaleziono koniec, rekonstrukcja sciezki ... " << endl;

  ref = static_cast<Point>(actual);

  while( !(ref == StartPoint) ){

    x = static_cast<int>(ref.x);
    y = static_cast<int>(ref.y);
    printf("(%d %d)\n",x,y);
    ref = ref + ReverseDir( Map[x][y] >> 4);

  }


}



