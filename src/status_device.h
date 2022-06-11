#include <Firebase_ESP_Client.h>
#include <ArduinoJson.h>

class StatusDevice
{
	const String keyJsonTurnOnLed = "\"turn_on_led\":";
	const String keyJsonTurnOnSOS = "\"turn_on_SOS\":";

public:
	String userId;
	bool turnOnLed;
	bool turnOnSOS;
	StatusDevice()
	{
	}
	StatusDevice(String userId, bool turnOnLed, bool turnOnSOS)
	{
		StatusDevice::turnOnLed = turnOnLed;
		StatusDevice::userId = userId;
		StatusDevice::turnOnSOS = turnOnSOS;
	};
	String mapToJson();
	void clone(StatusDevice statusDevice)
	{
		turnOnLed = statusDevice.turnOnLed;
		turnOnSOS = statusDevice.turnOnSOS;
		userId = statusDevice.userId;
	}
	static StatusDevice mapFromJson(String data)
	{
		DynamicJsonDocument doc(1024);
		deserializeJson(doc, data);
		JsonObject obj = doc.as<JsonObject>();
		String userId = obj["user_Id"];
		bool turnOnLed = obj["turn_on_led"].as<bool>();
		bool turnOnSOS = obj["turn_on_SOS"].as<bool>();
		return StatusDevice(userId, turnOnLed, turnOnSOS);
	};
};

String boolToString(bool result)
{
	return result ? "true" : "false";
}

String StatusDevice::mapToJson()
{
	return "{\"status_device\":{" +
				 keyJsonTurnOnLed + boolToString(turnOnLed) + "," +
				 keyJsonTurnOnSOS + boolToString(turnOnSOS) + "}" +
				 "}";
}

bool updateFirebase(StatusDevice statusDevice, FirebaseData &fbdo, String projectId)
{
	String documentPath = "user/" + statusDevice.userId;
	FirebaseJson content;
	content.set("fields/turnOnLed/booleanValue", statusDevice.turnOnLed);
	content.set("fields/turnOnSOS/booleanValue", statusDevice.turnOnSOS);
	Serial.print("Update a document... ");
	if (Firebase.Firestore.patchDocument(&fbdo, projectId, "", documentPath.c_str(), content.raw(), "turnOnLed,turnOnSOS"))
	{
		Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
		return true;
	}
	else
	{
		Serial.println(fbdo.errorReason());
		return false;
	}
}