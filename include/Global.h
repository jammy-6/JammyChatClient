#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include "nlohmann/json.hpp"

enum MODULE {
	MOUDLE_REGISTER = 0,
};

enum ID {
	ID_GET_VALIDATE_CODE = 0,
	ID_USER_REGISTER = 1,
};

enum ERRORCODE {
	SUCCESS = 0,
	ERROR_NETWORK,///网络错误
	ERROR_JSON_PARSE_FAILED,///JSON解析失败
};

const QString errorMailFormat = "邮箱格式错误！";
const QString errorJsonParse = "Json解析错误！";
#endif // ! 