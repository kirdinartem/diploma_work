#include <tests.h>
#include <lld_encoder.h>

/***************************************************/

static const SerialConfig sdcfg = {
  .speed = 115200,
  .cr1 = 0, .cr2 = 0, .cr3 = 0
};

void testEncoderCommonRoutine( void )
{
    sdStart( &SD7, &sdcfg );
    palSetPadMode( GPIOE, 8, PAL_MODE_ALTERNATE(8) );   // TX
    palSetPadMode( GPIOE, 7, PAL_MODE_ALTERNATE(8) );   // RX

    lldEncoderInit( );


    rawEncoderValue_t   enc_test_ticks       = 0;
    rawEncoderValue_t   enc_test_revs        = 0;
#ifdef ABSOLUTE_ENCODER
    rawEncoderValue_t   enc_test_abs_revs    = 0;
#endif
    bool                enc_test_dir         = 0;


    chprintf( (BaseSequentialStream *)&SD7, "TEST ENCODER\n\r" );

    while( 1 )
    {

        enc_test_ticks      = lldGetEncoderRawTicks( );
        enc_test_revs       = lldGetEncoderRawRevs( );
#ifdef ABSOLUTE_ENCODER
        enc_test_abs_revs   = lldGetAbsoluteEncoderRawRevs( );
#endif
        enc_test_dir        = lldGetEncoderDirection( );

#ifdef ABSOLUTE_ENCODER
        chprintf( (BaseSequentialStream *)&SD7, "Ticks:(%d)\tRevs:(%d)\tAbs_Revs:(%d)\tDir:(%d)\n\r",
                  enc_test_ticks, enc_test_revs, enc_test_abs_revs, enc_test_dir);
#else
        chprintf( (BaseSequentialStream *)&SD7, "Ticks:(%d)\tRevs:(%d)\tDir:(%d)\n\r",
                         enc_test_ticks, enc_test_revs, enc_test_dir);
#endif

        chThdSleepMilliseconds( 200 );

    }

}
