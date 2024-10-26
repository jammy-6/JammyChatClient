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
	ERROR_NETWORK,///�������
	ERROR_JSON_PARSE_FAILED,///JSON����ʧ��
};

const QString errorMailFormat = "�����ʽ����";
const QString errorJsonParse = "Json��������";
#endif // ! 