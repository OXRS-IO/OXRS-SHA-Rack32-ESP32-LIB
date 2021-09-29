/*
 * OXRS_Rack32.h
 */

#ifndef OXRS_RACK32_H
#define OXRS_RACK32_H

#include <ArduinoJson.h>
#include <OXRS_MQTT.h>                // For MQTT
#include <OXRS_LCD.h>                 // For LCD runtime displays

/* Serial */
#define       SERIAL_BAUD_RATE          115200

/* Ethernet */
#define       ETHERNET_CS_PIN           26
#define       WIZNET_RESET_PIN          13
#define       DHCP_TIMEOUT_MS           15000
#define       DHCP_RESPONSE_TIMEOUT_MS  4000

/* MCP9808 temp sensor */
#define       MCP9808_INTERVAL_MS       60000
#define       MCP9808_I2C_ADDRESS       0x18
#define       MCP9808_MODE              0
//  Mode Resolution  SampleTime
//  0    0.5°C       30 ms
//  1    0.25°C      65 ms
//  2    0.125°C     130 ms
//  3    0.0625°C    250 ms

// Callback type for onConfig() and onCommand()
typedef void (*jsonCallback)(JsonObject);

class OXRS_Rack32
{
  public:
    OXRS_Rack32(const char * fwName, const char * fwShortName, const char * fwMakerCode, const char * fwVersion, const char * fwCode);
    
    void setMqttBroker(const char * broker, uint16_t port);
    void setMqttAuth(const char * username, const char * password);
    void setMqttTopicPrefix(const char * prefix);
    void setMqttTopicSuffix(const char * suffix);

    void setDisplayPorts(uint8_t mcp23017s, int layout);
    void updateDisplayPorts(uint8_t mcp23017, uint16_t ioValue);

    void begin(jsonCallback config, jsonCallback command);
    void loop(void);

    boolean publishStatus(JsonObject json);
    boolean publishTelemetry(JsonObject json);

  private:
    const char * _fwName;
    const char * _fwShortName;
    const char * _fwMakerCode;
    const char * _fwVersion;
    const char * _fwCode;
    
    jsonCallback _onConfig;
    jsonCallback _onCommand;

    void _initialiseEthernet(byte * ethernetMac);

    void _initialiseTempSensor(void);    
    void _updateTempSensor(void);
    
    uint32_t _lastTempUpdate = -MCP9808_INTERVAL_MS;
};

#endif
