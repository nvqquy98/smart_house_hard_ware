#include <Firebase_ESP_Client.h>
#include <ArduinoJson.h>
#include <string_util.h>
#include <model/device_type.h>

#pragma once

#ifdef __cplusplus
class DeviceStatusData
{
public:
	bool isTurnOn;
	String deviceId;
	DeviceType deviceType;
	long createAt;
	int pinOutput;
	/* Constructor */
	DeviceStatusData()
	{
	}
	DeviceStatusData(String deviceId, bool isTurnOn, int pinOutput, DeviceType deviceType)
	{
		DeviceStatusData::isTurnOn = isTurnOn;
		DeviceStatusData::deviceId = deviceId;
		DeviceStatusData::pinOutput = pinOutput;
		DeviceStatusData::deviceType = deviceType;
	};
	DeviceStatusData(String deviceId, bool isTurnOn, int pinOutput, int deviceType)
	{
		DeviceStatusData::isTurnOn = isTurnOn;
		DeviceStatusData::deviceId = deviceId;
		DeviceStatusData::pinOutput = pinOutput;
		DeviceStatusData::deviceType = static_cast<DeviceType>(deviceType);
	};
	/* function */
	String mapToJson();
	void clone(DeviceStatusData deviceStatus)
	{
		deviceId = deviceStatus.deviceId;
		isTurnOn = deviceStatus.isTurnOn;
		pinOutput = deviceStatus.pinOutput;
		deviceType = deviceStatus.deviceType;
	}

	bool createDeviceStatusDataFirebase(String userId, FirebaseData &fbdo, String projectId);

	static DeviceStatusData mapFromJson(String data)
	{
		DynamicJsonDocument doc(1024);
		deserializeJson(doc, data);
		JsonObject obj = doc.as<JsonObject>();
		return DeviceStatusData(
				obj[KEY_DEVICE_ID],
				obj[KEY_IS_TURN_ON].as<bool>(),
				obj[KEY_PIN_OUT_PUT].as<int>(),
				obj[KEY_DEVICE_TYPE].as<int>());
	};
};

String DeviceStatusData::mapToJson()
{
	return "{\"device_status\":{" +
				 convertStringToJson(KEY_DEVICE_ID) + ":" + convertStringToJson(deviceId) + "," +
				 convertStringToJson(KEY_IS_TURN_ON) + ":" + boolToString(isTurnOn) +
				 "}" + "}";
}

bool updateFieldTurnOnInDeviceData(String documentPath, bool isTurnOn, FirebaseData &fbdo, String projectId)
{

	FirebaseJson content;
	content.set("fields/" + KEY_IS_TURN_ON + "/booleanValue", isTurnOn);
	if (Firebase.Firestore.patchDocument(&fbdo, projectId, "", documentPath.c_str(), content.raw(), KEY_IS_TURN_ON))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DeviceStatusData::createDeviceStatusDataFirebase(String userId, FirebaseData &fbdo, String projectId)
{

	String deviceDocumentPath = "user/" + userId + "/devices/" + deviceId;
	String deviceStatusCollectionPath = deviceDocumentPath + "/status/";
	FirebaseJson content;
	content.set("fields/" + KEY_DEVICE_ID + "/stringValue", deviceId);
	content.set("fields/" + KEY_IS_TURN_ON + "/booleanValue", isTurnOn);
	content.set("fields/create_at/integerValue", createAt);
	if (Firebase.Firestore.createDocument(&fbdo, projectId, "", deviceStatusCollectionPath, "", content.raw(), ""))
	{
		if (updateFieldTurnOnInDeviceData(deviceDocumentPath, isTurnOn, fbdo, projectId))
		{
			return true;
		}
		else
		{
			Serial.println(fbdo.errorReason());
			return false;
		}
	}
	else
	{
		Serial.println(fbdo.errorReason());
		return false;
	}
}
#endif