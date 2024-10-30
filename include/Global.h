
#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include <iostream>
#include "Config.h"

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
const QString errorUserNameEmpty = "用户名称栏为空！";
const QString errorUserEmailEmpty = "用户邮箱栏为空！";
const QString errorUserPasswordEmpty = "用户密码栏为空！";
const QString errorUserConfirmPasswordEmpty = "用户确认密码栏为空！";
const QString errorUserValidateCodeEmpty = "用户验证码为空！";
const QString errorUserPasswordNotEqual = "用户两次输入的密码不一致！";
const QString errorMailFormat = "邮箱格式错误！";
const QString errorJsonParse = "Json解析错误！";
const QString hintGetValidateCodeSuccess = "获取验证码成功！";
const QString hintRegisterProcess = "正在为您注册中，请稍后...";
const QString hintRegisterSuccess = "注册成功！";
#endif // ! 