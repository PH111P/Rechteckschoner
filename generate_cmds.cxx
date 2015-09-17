#include <cstdio>
#include <ctime>

#define HRES 768
#define VRES 1366

int depth = 8;
int border = 3;
int children = 3;

int color[ 3 ] = { 180, 180, 180 };

const char* output = "/home/philip/Projects/Rechteckschoner/";
const char* temp = "/home/philip/Projects/Rechteckschoner/.tmp";

int main() {
    FILE* config = fopen( "/home/philip/Projects/Rechteckschoner/.config", "w" );
    
    if( config == 0 ) {
        printf( "fopen failed\n" );
        perror( ".config" );
        //fclose( config );
        return 0;
    }

    fprintf( config, "-h %d", HRES ); 
    fprintf( config," -w %d", VRES );

    time_t utime = time( 0 );
    tm* tStruct = gmtime( (const time_t*) &utime );

    int hours = tStruct->tm_hour;
    int minutes = tStruct->tm_min;
    int day = tStruct->tm_mday;

    printf( "\n%d. at %d:%d\n",day, hours, minutes );

    children = 2 + day % 3;
    depth = 36 / children;

    if( hours >= 6 && hours <= 9 
        || hours >= 16 && hours <= 18 ) {
        color[ 0 ] = 1;
    } else if( hours == 5 || hours == 15 )
        color[ 0 ] = 181 - 3 * minutes;
    else if( hours == 10 || hours == 19 )
        color[ 0 ] = 3 * minutes;

    if( hours >= 9 && hours <= 15 ) {
        color[ 1 ] = 1;
    } else if( hours == 8 )
        color[ 1 ] = 181 - 3 * minutes;
    else if( hours == 16 )
        color[ 1 ] = 3 * minutes;

    if( hours >= 18 || hours <= 7 ) {
        color[ 2 ] = 1;
    } else if( hours == 17 )
        color[ 2 ] = 181 - 3 * minutes;
    else if( hours == 8 )
        color[ 2 ] = 3 * minutes;

    printf( "Colors: %d %d %d\n", color[ 0 ], color[ 1 ], color[ 2 ] );
    fprintf( config," -d %d -b %d -c %d", depth, border, children );
    fprintf( config," -e %d -g %d -u %d",color[ 0 ], color[ 1 ], color[ 2 ] );
    fclose( config );
}
