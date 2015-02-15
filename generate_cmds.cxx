#include <cstdio>
#include <ctime>

#define HRES 768
#define VRES 1366

int depth = 8;
int border = 3;
int children = 4;

int color[ 3 ] = { 255,255,255 };

const char* output = "/home/philip/Projects/Rechteckschoner/";
const char* temp = "/home/philip/Projects/Rechteckschoner/.tmp";

int main() {
    FILE* config = fopen( ".config", "w" );
    
    fprintf( config, "-h %d", HRES ); 
    fprintf( config," -w %d", VRES );

    time_t utime = time( 0 );
    tm* tStruct = gmtime( (const time_t*) &utime );

    int hours = tStruct->tm_hour;
    int minutes = tStruct->tm_min;
    int day = tStruct->tm_mday;

    printf( "%d %d %d\n", hours, minutes, day );

    children = day / 4;
    depth = int( day / 2.5 );

    if( hours >= 6 && hours <= 9 
        || hours >= 16 && hours <= 18 ) {
        color[ 0 ] = 1;
    } else if( hours == 5 || hours == 15 )
        color[ 0 ] = 241 - 4 * minutes;
    else if( hours == 10 || hours == 19 )
        color[ 0 ] = 4 * minutes;

    if( hours >= 9 && hours <= 15 ) {
        color[ 1 ] = 1;
    } else if( hours == 8 )
        color[ 1 ] = 241 - 4 * minutes;
    else if( hours == 16 )
        color[ 1 ] = 4 * minutes;

    if( hours >= 18 || hours <= 7 ) {
        color[ 2 ] = 4;
    } else if( hours == 17 )
        color[ 2 ] = 241 - 4 * minutes;
    else if( hours == 8 )
        color[ 2 ] = 4 * minutes;

    fprintf( config," -d %d -b %d -c %d",10,3,4); //depth, border, children );
    fprintf( config," -e %d -g %d -u %d",color[ 0 ], color[ 1 ], color[ 2 ] );
}
