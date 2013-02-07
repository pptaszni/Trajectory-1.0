
#include "TrajectoryBuilder.hh"



using namespace std;




Point::Point( ){ x=0; y=0; }
Point::Point( double x, double y ){

  this->x = x;
  this->y = y;

}
Point::~Point( ){ }


Obstacle::Obstacle( ){ x=0; y=0; radius = 0; }
Obstacle::Obstacle( double x, double y, double radius ){

  this->x = x;
  this->y = y;
  this->radius = radius;

}
Obstacle::~Obstacle( ){ }


TrajectoryBuilder::TrajectoryBuilder( ){

  Target = NULL;
  cout << "TrajectoryBuilder initiated \n";

}

TrajectoryBuilder::TrajectoryBuilder( string PositionFileName,
				      string ObstaclesFileName,
				      string TargetFileName ){

  FILE *PositionFile, *ObstaclesFile, *TargetFile;
  double x,y,radius;

  PositionFile = fopen( PositionFileName.c_str(), "r" );

  if(PositionFile){

    while ( !feof(PositionFile)){
      fscanf(PositionFile, "%lf", &x);
      fscanf(PositionFile, "%lf", &y);
      Position.push_back( new Point(x,y) );
    }

  }

  fclose( PositionFile );

  ObstaclesFile = fopen( ObstaclesFileName.c_str(), "r" );

  if(ObstaclesFile){

    while(!feof(ObstaclesFile)){
      fscanf(ObstaclesFile, "%lf", &x);
      fscanf(ObstaclesFile, "%lf", &y);
      fscanf(ObstaclesFile, "%lf", &radius);
      Obstacles.push_back( new Obstacle(x,y,radius) );
    }

  }

  fclose( ObstaclesFile );

  TargetFile = fopen( TargetFileName.c_str(), "r" );

  if(TargetFile){

    while ( !feof(TargetFile)){
      fscanf(TargetFile, "%lf", &x);
      fscanf(TargetFile, "%lf", &y);
      Target = new Point(x,y);
    }

  }

  fclose( ObstaclesFile );



}


TrajectoryBuilder::~TrajectoryBuilder( ){

  if( Target != NULL ) delete Target;

  for( list<Obstacle*>::iterator it = Obstacles.begin(); 
       it != Obstacles.end(); it++ ){
    if( *it != NULL ) delete *it;
  }

  for( list<Point*>::iterator it = Position.begin(); 
       it != Position.end(); it++ ){
    if( *it != NULL ) delete *it;
  }

}
