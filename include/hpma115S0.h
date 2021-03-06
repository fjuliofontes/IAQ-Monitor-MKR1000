/**
 *
 * @file HPMA115S0.h
 * @author Felix A. Galindo 
 * @date June 2017
 * @brief Arduino Library for Honeywell's Particle Sensor (HPMA115S0-XXX)
 *
 */

#ifndef HPMA115S0_H
#define HPMA115S0_H

#include "Arduino.h"
#include <stdint.h>

//#define DEBUG
#include "util.h"

#define HPMA115S0_DEBUG_LEVEL 1
#define HPM_CMD_RESP_HEAD 0x40
#define HPM_MAX_RESP_SIZE 8 // max command response size is 8 bytes
#define HPM_READ_PARTICLE_MEASUREMENT_LEN 5
#define HPMA115S0_ON  0x00
#define HPMA115S0_OFF 0x01

enum CMD_TYPE_T {
    READ_PARTICLE_MEASUREMENT = 0x04,
    START_PARTICLE_MEASUREMENT = 0x01,
    STOP_PARTICLE_MEASUREMENT = 0x02,
    SET_ADJUSTMENT_COEFFICIENT = 0x08,
    READ_ADJUSTMENT_COEFFICIENT = 0x08,
    STOP_AUTO_SEND = 0x20,
    ENABLE_AUTO_SEND = 0x40,
};

enum HPM_PACKET_T {
    HPM_HEAD_IDX,
    HPM_LEN_IDX,
    HPM_CMD_IDX,
    HPM_DATA_START_IDX
};

class HPMA115S0
{
public:
    /**
     * @brief Constructor for HPMA115S0 class
     * @param  a Stream ({Software/Hardware}Serial) object.
     * @note The serial stream should be already initialized
     * @return  void
     */
    HPMA115S0(Stream& serial);

    /**
     * @brief Function that initializes sensor
     * @return  a String containing sensor response
     */
    void Init();

    /**
     * @brief Function that sends a read command to sensor
     * @return  returns true if valid measurements were read from sensor
     */boolean ReadParticleMeasurement(uint16_t * pm2_5, uint16_t * pm10);

    /**
     * @brief Function that starts sensor measurement
     * @return  void
     */
    void StartParticleMeasurement();
    /**
     * @brief Function that stops sensor measurement
     * @return  void
     */
    void StopParticleMeasurement();

    /**
     * @brief Function that enables auto send
     * @return  void
     */
    void EnableAutoSend();

    /**
     * @brief Function that stops auto send
     * @return  void
     */
    void DisableAutoSend();

    /**
    * @brief Function that returns the latest PM 2.5 reading
    * @note Sensor reports new reading ~ every 1 sec.
    * @return  PM 2.5 reading (unsigned int)
    */
    uint16_t GetPM2_5();

    /**
    * @brief Function that returns the latest PM 10 reading
    * @note Sensor reports new reading ~ every 1 sec.
    * @return  PM 10 reading (unsigned int)
    */
    uint16_t GetPM10();

    uint8_t Status();

private:
    Stream& _serial;

    //Latest PM 2.5 reading
    uint16_t _pm2_5 = 0;

    //Latest PM 10 reading
    uint16_t _pm10 = 0;

    uint8_t _status = 1;

    /**
     * @brief Function that sends serial command to sensor
     * @param  a char * containing the command
     * @param size of buffer
     * @return  void
     */
    void SendCmd(uint8_t * cmdBuf, uint16_t cmdSize);

    /**
    * @brief Function that reads command response from sensor
    * @param Buffer to store data in
    * @param Buffer size
    * @param Expected command type
    * @return  returns number of bytes read from sensor
    */
    uint16_t ReadCmdResp(uint8_t * dataBuf, uint16_t dataBufSize, uint16_t cmdType);
};

#endif
