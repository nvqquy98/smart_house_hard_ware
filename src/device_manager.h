#include <model/device_data.h>
#include <ArduinoJson.h>

class DeviceManager
{
public:
	std::vector<DeviceData>
			deviceDatas;
	DeviceManager(){};
	bool getAllDevice(FirebaseData &fbdo, String projectId, String userId);
	void initDevices(String data);
	DeviceData getDevice(int output);
};

void DeviceManager::initDevices(String data)
{
	deviceDatas.clear();
	DynamicJsonDocument doc(1024);
	deserializeJson(doc, data);
	for (unsigned int i = 0; i < doc.size(); i++)
	{
		DeviceData deviceData = DeviceData::mapFromJson(doc[i]);
		deviceDatas.push_back(deviceData);
	}
}

DeviceData DeviceManager::getDevice(int output)
{
	for (unsigned int i = 0; i < deviceDatas.size(); i++)
	{
		if (deviceDatas.at(i).pinOutput == output)
		{
			return deviceDatas.at(i);
		}
	}
	return DeviceData();
}