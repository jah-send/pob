/** 
 * @brief Robot sapien order
 *
 * @file 
 *
 * This file contains all the order supported by the robot sapien.
 *
 * @author Pierre SEGUIN. POB-Technology
 *
 */
#ifndef robotsapien_order_h
#define robotsapien_order_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Sapien movement : forward,backward and stop
 */
/*@{*/
#define SAPIEN_WALK_FORWARD     0x86
#define SAPIEN_WALK_BACKWARD    0x87
#define SAPIEN_WALK_STOP        0x8E
/*@}*/


/**
 * @name Sapien turn order
 */
/*@{*/
#define SAPIEN_TURN_RIGHT       0x80
#define SAPIEN_TURN_LEFT        0x88
/*@}*/


/**
 * @name Sapien right arm order (up,down) an (out,in)
 */
/*@{*/
#define SAPIEN_RIGHT_ARM_UP     0x81
#define SAPIEN_RIGHT_ARM_DOWN   0x84

#define SAPIEN_RIGHT_ARM_OUT    0x82
#define SAPIEN_RIGHT_ARM_IN     0x85
/*@}*/


/**
 * @name Sapien left arm order (up,down) an (out,in)
 */
/*@{*/
#define SAPIEN_LEFT_ARM_UP      0x89
#define SAPIEN_LEFT_ARM_DOWN    0x8C

#define SAPIEN_LEFT_ARM_OUT     0x8A
#define SAPIEN_LEFT_ARM_IN      0x8D
/*@}*/


/**
 * @name Sapien body movement
 */
/*@{*/
#define SAPIEN_TILT_BODY_LEFT   0x8B
#define SAPIEN_TILT_BODY_RIGHT  0x83
/*@}*/

#ifdef __cplusplus
 }
#endif

#endif
