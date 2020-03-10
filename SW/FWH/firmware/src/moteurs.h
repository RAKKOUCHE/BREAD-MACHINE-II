/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _MOTEURS_H    /* Guard against multiple inclusion */
#define _MOTEURS_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

#include <GenericTypeDefs.h>
#include <machine/types.h>
#include "FreeRTOS.h"
#include "task.h"
#include "delay_us.h"
#include "communDef.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C"
{
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    /**
     * \brief
     */
    typedef enum
    {
        REVERSE,
        FORWARD,
    } DIRECTION;

    /**
     * \brief
     */
    typedef enum
    {
        MOTORS_INIT,
        MOTORS_OFF,
        MOTORS_BREAK,
        MOTORS_FORWARD,
        MOTORS_REVERSE,
        MOTORS_IDLE,
    } MOTORS_SATE;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************

    /**
     * \brief
     * @param num
     * @return
     */
    DIRECTION getLastDir(const uint8_t num);

    /**
     * \brief
     * @param num
     * @param direction
     */
    void setLastDir(const uint8_t num, const DIRECTION direction);

    /**
     * \brief
     * @param
     * @param
     * @return
     */
    BOOL getIsMotorInUse(const uint8_t num);

    //    /**
    //     * \brief
    //     * @param num
    //     * @param isInUse
    //     */
    //    void setIsMotorInUse(const uint8_t num, const BOOL isInUse);

    /**
     * \brief
     * @param num
     * @param state
     */
    void setMotorState(const uint8_t num, const MOTORS_SATE state);

    /**
     * \brief
     * @param num
     * @return
     */
    MOTORS_SATE getMotorState(const uint8_t num);

    /**
     * \brief
     */
    void vMotorsInit(void);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MOTEURS_H */

/* *****************************************************************************
 End of File
 */
