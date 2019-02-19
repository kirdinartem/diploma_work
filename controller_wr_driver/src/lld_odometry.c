#include <tests.h>
#include <lld_encoder.h>
#include <lld_odometry.h>

/************************************/
/***    GPT Configuration Zone    ***/
/************************************/
#define gptFreq     10000
static  GPTDriver   *gptDriver = &GPTD2;
/************************************/

/************************************/
/***     Coefficient variables    ***/
/************************************/

float    dist_k_mm      = 0;
float    dist_k_cm      = 0;
float    dist_k_m       = 0;
/* need checking, maybe should 0.105 / 6 */
float    obj_gain       = 0.105;

float    tetta_k_rad    = 0;
float    tetta_k_deg    = 0;

float    m_2_mm         = 0;
float    m_2_cm         = 0;


#define  MS_2_SEC       100; // 10 ms - > 1 s
#define  CM_2_M         (float)0.01;

/************************************/


/**
 * @brief   Get distance that object has passed
 * @return  Distance in specified units
 * @note    units = 1   -> mm
 *          units = 10  -> cm
 *          units = 100 -> m
 */
odometryValue_t lldGetOdometryObjDistance( uint8_t units )
{
    rawEncoderValue_t   revs            = lldGetEncoderRawRevs( );

    if      ( units == 1 )   return ( revs * dist_k_mm ); // [ mm ]
    else if ( units == 10 )  return ( revs * dist_k_cm ); // [ cm ]
    else if ( units == 100 ) return ( revs * dist_k_m );  // [ m  ]
    else                     return (-255);               // Error
}

/************************************/
/***     Variables for speed      ***/
/************************************/

rawEncoderValue_t           prev_revs               = 0;
odometryRawSpeedValue_t     revs_per_sec            = 0;

odometryValue_t             prev_distance           = 0;
odometrySpeedValue_t        speed_cm_per_sec        = 0;
odometrySpeedValue_t        speed_m_per_sec         = 0;

/************************************/
/***     Variables for odometry   ***/
/************************************/

odometryValue_t             tetta_deg_angle_per_sec = 0;
odometryValue_t             tetta_rad_angle_per_sec = 0;
odometryValue_t             x_pos_m                 = 0;
odometryValue_t             y_pos_m                 = 0;




static void gptcb (GPTDriver *gptd)
{
    gptd = gptd;

    /***         Speed calculation                         ***/

    /***         Get speed of encoder in revolutions       ***/
    rawEncoderValue_t   cur_revs   = lldGetEncoderRawRevs( );
    revs_per_sec    = (cur_revs - prev_revs) * MS_2_SEC;
    prev_revs       = cur_revs;
    /*********************************************/

    /***    Get speed of object in cm/s and m/s          ***/
    odometryValue_t cur_distance  = lldGetOdometryObjDistance( 10 );

    /*  [cm/10ms] * 1000 = [cm/c]   */
    speed_cm_per_sec    = (cur_distance - prev_distance ) * MS_2_SEC;
    /*  [cm/s] * 0.01 = [m/s]       */
    speed_m_per_sec     = speed_cm_per_sec * CM_2_M;

    prev_distance       = cur_distance;
    /*********************************************/

    /***        Tetta calculation              ***/
    /* steer_angle = getSteerAngleRadValue() !!!!! need to add !!!*/
    odometryValue_t steer_angl_rad = 0; // just to avoid errors!!!
    /*** It is tetta angle, not changing speed of tetta! ***/
    tetta_rad_angle_per_sec +=  ( speed_m_per_sec * tan( steer_angl_rad ) * tetta_k_rad );

    /*** Reset tetta integral ***/
    if(tetta_rad_angle_per_sec == ( 2 * M_PI ) ) tetta_rad_angle_per_sec = 0;
    /**********************************************/

    /***        X calculation                  ***/
    x_pos_m += (speed_m_per_sec * cos(tetta_rad_angle_per_sec)) * MS_2_SEC;
    /*********************************************/

    /***        Y calculation                  ***/
    y_pos_m += (speed_m_per_sec * sin(tetta_rad_angle_per_sec)) * MS_2_SEC;
    /*********************************************/

}

static const GPTConfig gpt2cfg = {
  .frequency =  gptFreq,
  .callback  =  gptcb,
  .cr2       =  0,
  .dier      =  0U
};

static bool         isInitialized       = false;

/**
 * @brief   Initialize periphery connected to odometry unit
 * @note    Stable for repeated calls
 *          lldEncoderInit is done in this function,
 *          do not initialize it again!
 */
void lldOdometryInit( void )
{
    if ( isInitialized )
            return;

    /*** Start working GPT driver in asynchronous mode ***/
    gptStart( gptDriver, &gpt2cfg );
    uint32_t gpt_period = gptFreq * 0.01;   // 10 ms
    gptStartContinuous( gptDriver, gpt_period );

    lldEncoderInit( );

    /***    Coefficient calculation     ***/
    dist_k_mm   = 2 * M_PI * WHEEL_RADIUS_CM * obj_gain * 10;
    dist_k_cm   = 2 * M_PI * WHEEL_RADIUS_CM * obj_gain;
    dist_k_m    = 2 * M_PI * WHEEL_RADIUS_CM * obj_gain / 100 ;

    tetta_k_rad = 100 / WHEEL_BASE_M;
    tetta_k_deg = 180 / M_PI;

    m_2_mm      = 0.01;
    m_2_cm       = 0.1;

    /***    Set initialization flag     ***/

    isInitialized = true;
}

/**
 * @brief   Get speed of encoder rotation
 * @return  Speed in revolutions per second [rps]
 */
odometryRawSpeedValue_t lldGetOdometryRawSpeedRPS( void )
{
    return revs_per_sec;
}

/**
 * @brief   Get speed of object
 * @return  Speed in cm per second [cmps]
 */
odometrySpeedValue_t lldGetOdometryObjSpeedCMPS( void )
{
    return speed_cm_per_sec;
}

/**
 * @brief   Get speed of object
 * @return  Speed in m per second [mps]
 */
odometrySpeedValue_t lldGetOdometryObjSpeedMPS( void )
{
    return speed_m_per_sec;
}


/**
 * @brief   Get tetta (orientation) of objects
 * @return  angle in radians [rad]
 */
odometryValue_t lldGetOdometryObjTettaRad( void )
{
    return tetta_rad_angle_per_sec;
}

/**
 * @brief   Get tetta (orientation) of objects
 * @return  angle in degrees [deg]
 */
odometryValue_t lldGetOdometryObjTettaDeg( void )
{
    return ( tetta_rad_angle_per_sec * tetta_k_deg );
}

/**
 * @brief   Get x-coordinate of objects
 * @return  object movement
 * @note    units = 1   -> [ mm ]
 *          units = 10  -> [ cm ]
 *          units = 100 -> [ m  ]
 */
odometryValue_t lldGetOdometryObjX( uint8_t units )
{
    if     ( units == 1 )     return ( x_pos_m * m_2_mm );  // [ mm ]
    else if( units == 10 )    return ( x_pos_m * m_2_cm );  // [ cm ]
    else if( units == 100 )   return ( x_pos_m );           // [ m  ]
    else                      return (-255);                // Error
}

/**
 * @brief   Get y-coordinate of objects
 * @return  object movement
 * @note    units = 1   -> [ mm ]
 *          units = 10  -> [ cm ]
 *          units = 100 -> [ m  ]
 */
odometryValue_t lldGetOdometryObjY( uint8_t units )
{
    if     ( units == 1 )     return ( y_pos_m * m_2_mm );  // [ mm ]
    else if( units == 10 )    return ( y_pos_m * m_2_cm );  // [ cm ]
    else if( units == 100 )   return ( y_pos_m );           // [ m  ]
    else                      return (-255);                // Error
}
