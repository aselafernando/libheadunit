#pragma once
#include "defs.h"
#include "protocol/AndroidAuto.pb.h"

namespace AndroidAuto {

class IHUConnectionThreadInterface;
class HeadunitEventCallbacks {
protected:
    ~HeadunitEventCallbacks() {
    }
    HeadunitEventCallbacks() {
    }

public:
    // return > 0 if handled < 0 for error
    virtual int MessageFilter(__attribute__((unused)) IHUConnectionThreadInterface &stream, __attribute__((unused)) HU_STATE state, __attribute__((unused)) ServiceChannels chan,
                              __attribute__((unused)) uint16_t msg_type, __attribute__((unused)) const byte *buf, __attribute__((unused)) int len) {
        return 0;
    }

    // return -1 for error
    virtual int MediaPacket(__attribute__((unused)) ServiceChannels chan, __attribute__((unused)) uint64_t timestamp, __attribute__((unused)) const byte *buf, __attribute__((unused)) int len) = 0;
    virtual int MediaStart(__attribute__((unused)) ServiceChannels chan) = 0;
    virtual int MediaStop(__attribute__((unused)) ServiceChannels chan) = 0;
    virtual void MediaSetupComplete(__attribute__((unused)) ServiceChannels chan) = 0;

    virtual void DisconnectionOrError() = 0;
    virtual void Connected() = 0;

    virtual void CustomizeCarInfo(__attribute__((unused)) HU::ServiceDiscoveryResponse &carInfo) {
    }
    virtual void CustomizeInputConfig(__attribute__((unused)) HU::ChannelDescriptor::InputEventChannel &inputChannel) {
    }
    virtual void CustomizeSensorConfig(__attribute__((unused)) HU::ChannelDescriptor::SensorChannel &sensorChannel) {
    }
    virtual void CustomizeOutputChannel(__attribute__((unused)) ServiceChannels chan, __attribute__((unused)) HU::ChannelDescriptor::OutputStreamChannel &streamChannel) {
    }
    virtual void CustomizeInputChannel(__attribute__((unused)) ServiceChannels chan, __attribute__((unused)) HU::ChannelDescriptor::InputStreamChannel &streamChannel) {
    }
    virtual void CustomizeBluetoothService(__attribute__((unused)) ServiceChannels chan, __attribute__((unused)) HU::ChannelDescriptor::BluetoothService &bluetoothService) {
    }

    // returning a empty string means no bluetooth
    virtual std::string GetCarBluetoothAddress() {
        return std::string();
    }
    virtual void PhoneBluetoothReceived(__attribute__((unused)) std::string address) {
    }

    virtual void AudioFocusRequest(__attribute__((unused)) ServiceChannels chan, __attribute__((unused)) const HU::AudioFocusRequest &request) = 0;
    virtual void VideoFocusRequest(__attribute__((unused)) ServiceChannels chan, __attribute__((unused)) const HU::VideoFocusRequest &request) = 0;

    virtual void HandlePhoneStatus(__attribute__((unused)) IHUConnectionThreadInterface &stream, __attribute__((unused)) const HU::PhoneStatus &phoneStatus) {
    }

    virtual void HandleGenericNotificationResponse(__attribute__((unused)) IHUConnectionThreadInterface &stream, __attribute__((unused)) const HU::GenericNotificationResponse &response) {
    }

    virtual void ShowingGenericNotifications(__attribute__((unused)) IHUConnectionThreadInterface &stream, __attribute__((unused)) bool bIsShowing) {
    }
    virtual void HandleNaviStatus(__attribute__((unused)) IHUConnectionThreadInterface &stream, __attribute__((unused)) const HU::NAVMessagesStatus &request) {
    }
    virtual void HandleNaviTurn(__attribute__((unused)) IHUConnectionThreadInterface &stream, __attribute__((unused)) const HU::NAVTurnMessage &request) {
    }
    virtual void HandleNaviTurnDistance(__attribute__((unused)) IHUConnectionThreadInterface &stream, __attribute__((unused)) const HU::NAVDistanceMessage &request) {
    }
};
}
