#pragma once

#ifdef __cplusplus
String boolToString(bool result)
{
	return result ? "true" : "false";
}

String convertStringToJson(String result)
{
	return "\"" + result + "\"";
}

const String KEY_IS_TURN_ON = "is_turn_on";
const String KEY_DEVICE_ID = "device_id";
const String KEY_ID = "id";
const String KEY_NAME = "name";
const String KEY_WATTAGE = "wattage";
const String KEY_PIN_OUT_PUT = "pin_out_put";
const String KEY_PIN_IN_PUT = "pin_in_put";
const String KEY_DEVICE_TYPE = "device_type";

#else

#error ArduinoJson requires a C++ compiler, please change file extension to .cc or .cpp

#endif
