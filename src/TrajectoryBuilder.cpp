
#include "TrajectoryBuilder.hh"



using namespace std;




Point::Point( ){ x=0; y=0; }
Point::Point( double x, double y ){

  this->x = x;
  this->y = y;

}

Point::Point( const Point& obj ){

  this->x = obj.x;
  this->y = obj.y;

}

Point::~Point( ){ }

double Point::Module(){

  return sqrt(x*x + y*y);

}

Point Point::Normalize(){

  Point a;
  if( this->Module() != 0 ){
    a.x = this->x/this->Module();
    a.y = this->y/this->Module();
  }
  return a;

}

Point operator-(Point a, Point b){

  Point c;
  c.x = a.x - b.x;
  c.y = a.y - b.y;
  return c;

}

Point operator+(Point a, Point b){

  Point c;
  c.x = a.x + b.x;
  c.y = a.y + b.y;
  return c;

}

Point operator*(Point a, double m){

  Point b;
  b.x = a.x*m;
  b.y = a.y*m;
  return b;

}


Obstacle::Obstacle( ){ x=0; y=0; radius = 0; }
Obstacle::Obstacle( double x, double y, double radius ){

  this->x = x;
  this->y = y;
  this->radius = radius;

}
Obstacle::~Obstacle( ){ }

Point Obstacle::ToPoint( ){

  Point a;
  a.x = this->x;
  a.y = this->y;
  return a;

}



TrajectoryBuilder::TrajectoryBuilder( ){

  Target = NULL;
  cout << "TrajectoryBuilder initiated \n";

}

TrajectoryBuilder::TrajectoryBuilder( string DataFileName ){

  FILE *DataFile;
  double x,y,r;
  int s;

  Target = NULL;

  DataFile = fopen( DataFileName.c_str(), "r" );

  if( DataFile ){

    fscanf(DataFile, "%i", &s);
    State = static_cast<bool>(s);

    fscanf(DataFile, "%lf", &StepSize);
    fscanf(DataFile, "%lf", &Speed);

    fscanf(DataFile, "%lf", &x);
    fscanf(DataFile, "%lf", &y);
    Target = new Point(x,y);

    if( State == 0 ){

      while ( !feof(DataFile) ){
	fscanf(DataFile, "%lf", &x);
	fscanf(DataFile, "%lf", &y);
	TrajectoryReference.push_back( new Point(x,y) );
      //cout << feof(DataFile) << endl;
      }
      TrajectoryReference.pop_back(); // becouse last element is double readed
    }
    else if( State == 1 ){

      while ( !feof(DataFile) ){
	fscanf(DataFile, "%lf", &x);
	fscanf(DataFile, "%lf", &y);
	fscanf(DataFile, "%lf", &r);
	Obstacles.push_back( new Obstacle(x,y,r) );
      }
      Obstacles.pop_back(); // same situation
    }
    fclose(DataFile);

  }
  /*
  list<Point *>::iterator it = TrajectoryReference.begin();
  while( it != TrajectoryReference.end() ){

    printf("(%lf %lf) \n",(*it)->x,(*it)->y);
    it++;

  }
  */
}

TrajectoryBuilder::~TrajectoryBuilder( ){


  if( Target != NULL ) delete Target;

  for( list<Obstacle*>::iterator it = Obstacles.begin(); 
       it != Obstacles.end(); it++ ){
    if( *it != NULL ) delete *it;
  }

  for( list<Point*>::iterator it = TrajectoryReference.begin(); 
       it != TrajectoryReference.end(); it++ ){
    if( *it != NULL ) delete *it;
  }

  for( list<Point*>::iterator it = Trajectory.begin(); 
       it != Trajectory.end(); it++ ){
    if( *it != NULL ) delete *it;
  }

}

void TrajectoryBuilder::Run(){

  if( State == 0 ) RunStreet();
  else if ( State == 1 ) RunParking();
  else cerr << "Unrecignized parameter State = " << State << endl;

}

void TrajectoryBuilder::RunStreet(){

  list<Point*>::iterator itRef = TrajectoryReference.begin();
  Point *first, *second;
  Point diff;
  double distance;
  int steps,i;
  //Point direction = *Target - *first;

  distance = Speed*StepSize;

  while( itRef != (--TrajectoryReference.end()) ){

    first = *itRef;
    itRef++;
    second = *itRef;
    diff = *second - *first;
    steps = diff.Module()/distance;
    diff = diff.Normalize();

    //printf("first: (%lf %lf), second: (%lf %lf)\n",first->x,first->y,second->x,second->y);

    for( i=0; i < steps; i++ ){

      Trajectory.push_back( new Point(*first + diff*distance*(i+1)) );
      //printf("(%lf %lf) \n",(*(--Trajectory.end()))->x,(*(--Trajectory.end()))->y);

    }
    if( itRef != TrajectoryReference.end() ){
      (*itRef)->x = (*(--(Trajectory.end())))->x;
      (*itRef)->y = (*(--(Trajectory.end())))->y;
    }

  }


}

void TrajectoryBuilder::RunParking(){

  double distance;
  Point dir;
  Point force(0,0);
  Point position(0,0); // we assume, that starting point is (0,0)
  list<Obstacle*>::iterator itObs;
  double mass = 100; // we adjust target mass to 100
  double epsilon = 1;

  distance = Speed*StepSize;

  while( (*Target - position).Module() > epsilon ){

    itObs = Obstacles.begin();

    while( itObs != Obstacles.end() ){

      dir = position - (*itObs)->ToPoint();
      force = force +
	dir*((*itObs)->radius)*(1/pow(dir.Module(),3));
      itObs++;

    }

    dir = *Target - position;
    force = force + dir*mass*(1/pow(dir.Module(),3));
    force = force.Normalize();
    position = position + force*distance;
    Trajectory.push_back( new Point(position) );
    //printf("(%lf %lf) \n",(*(--Trajectory.end()))->x,(*(--Trajectory.end()))->y);
  }

}

void TrajectoryBuilder::Save( string DataFileName ){

  FILE *DataFile;
  list<Point*>::iterator itRef = Trajectory.begin();




  DataFile = fopen( DataFileName.c_str(), "w" );

  if( DataFile ){

    while( itRef != Trajectory.end() ){

      fprintf(DataFile, "%lf %lf\n", (*itRef)->x, (*itRef)->y);
      itRef++;

    }

    fclose( DataFile );

  }


}
