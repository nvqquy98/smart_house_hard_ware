#include <Firebase_ESP_Client.h>
#include <ArduinoJson.h>
#include <model/device_status.h>
#include <model/device_type.h>
#include <string_util.h>
#pragma once

#ifdef __cplusplus

class DeviceData
{

public:
	String id;
	String name;
	DeviceType deviceType;
	double wattage;
	int pinOutput;
	int pinInput;
	bool isTurnOn;
	DeviceData()
	{
	}
	DeviceData(String id)
	{
		DeviceData::id = id;
	};
	DeviceData(String id, String name, float wattage, bool isTurnOn, int pinOutput, int pinInput, int deviceType)
	{
		DeviceData::id = id;
		DeviceData::name = name;
		DeviceData::wattage = wattage;
		DeviceData::isTurnOn = isTurnOn;
		DeviceData::pinInput = pinInput;
		DeviceData::pinOutput = pinOutput;
		DeviceData::deviceType = static_cast<DeviceType>(deviceType);
	};
	DeviceData(String name, float wattage, bool isTurnOn, int pinOutPut, int pinInput, int deviceType)
	{
		DeviceData::name = name;
		DeviceData::wattage = wattage;
		DeviceData::isTurnOn = isTurnOn;
		DeviceData::pinInput = pinInput;
		DeviceData::pinOutput = pinOutput;
		DeviceData::deviceType = static_cast<DeviceType>(deviceType);
	};
	void clone(DeviceData deviceData)
	{
		id = deviceData.id;
		name = deviceData.name;
		wattage = deviceData.wattage;
		isTurnOn = deviceData.isTurnOn;
		pinInput = deviceData.pinInput;
		pinOutput = deviceData.pinOutput;
		deviceType = deviceData.deviceType;
	}
	String mapToJson();
	bool createDeviceFirebase(String userId, FirebaseData &fbdo, String projectId);
	static DeviceData mapFromJson(String data)
	{
		DynamicJsonDocument doc(1024);
		deserializeJson(doc, data);
		JsonObject obj = doc.as<JsonObject>();
		return DeviceData(
				obj[KEY_ID],
				obj[KEY_NAME],
				obj[KEY_WATTAGE].as<float>(),
				obj[KEY_IS_TURN_ON].as<bool>(),
				obj[KEY_PIN_OUT_PUT].as<int>(),
				obj[KEY_PIN_IN_PUT].as<int>(),
				obj[KEY_DEVICE_TYPE].as<int>());
	};
};

String DeviceData::mapToJson()
{
	return "{\"device\":{" +
				 convertStringToJson(KEY_ID) + ":" + convertStringToJson(id) + "," +
				 convertStringToJson(KEY_NAME) + ":" + convertStringToJson(name) + "," +
				 convertStringToJson(KEY_WATTAGE) + ":" + wattage + "," +
				 convertStringToJson(KEY_PIN_IN_PUT) + ":" + pinInput + "," +
				 convertStringToJson(KEY_PIN_OUT_PUT) + ":" + pinOutput + "," +
				 convertStringToJson(KEY_DEVICE_TYPE) + ":" + deviceType + "," +
				 convertStringToJson(KEY_IS_TURN_ON) + ":" + isTurnOn +
				 "}" + "}";
}
bool DeviceData::createDeviceFirebase(String userId, FirebaseData &fbdo, String projectId)
{
	String collectionPath = "user/" + userId + "/devices";
	FirebaseJson content;
	content.set("fields/" + KEY_NAME + "/stringValue", name);
	content.set("fields/" + KEY_WATTAGE + "/doubleValue", wattage);
	content.set("fields/" + KEY_IS_TURN_ON + "/booleanValue", isTurnOn);
	content.set("fields/" + KEY_PIN_IN_PUT + "/integerValue", pinInput);
	content.set("fields/" + KEY_PIN_OUT_PUT + "/integerValue", pinOutput);
	content.set("fields/" + KEY_DEVICE_TYPE + "/integerValue", static_cast<int>(deviceType));

	if (Firebase.Firestore.createDocument(&fbdo, projectId, "", collectionPath.c_str(), "", content.raw(), "name"))
	{
		return true;
	}
	else
	{
		return false;
	}
}
#endif