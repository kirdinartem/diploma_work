#include <common.h>
#include <chprintf.h>

int main(void)
{
    chSysInit();
    halInit();

    #if (MAIN_PROGRAM_ROUTINE != PROGRAM_ROUTINE_MASTER)
        testsRoutines();
    #else
        mainUnitsInit( );
        mainControlTask( );
    #endif
}
