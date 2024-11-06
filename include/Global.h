
#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include <iostream>
#include "Config.h"

enum MODULE {
	MODULE_REGISTER = 0,
	MODULE_RESET_PASSWORD = 1,
	MODULE_LOGIN = 2,

};

enum ID {
	ID_REGISTER_GET_VALIDATE_CODE = 0,
	ID_RESET_GET_VALIDATE_CODE = 1,
	ID_USER_REGISTER = 2,
	ID_RESET_PASSWORD = 3,
	ID_USER_LOGIN = 4,
};

enum ERRORCODE {
	SUCCESS = 0,
	ERROR_NETWORK,///网络错误
	ERROR_JSON_PARSE_FAILED,///JSON解析失败
};

typedef struct ServerInfo {
	QString Host;
	QString Port;
	QString Uid;
	QString Token;
} ServerInfo;

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
const QString registerSuccessHintWindow = "注册成功,5s后返回登录界面，\n可点击返回按钮直接返回登录界面";
const QString hintResetPasswordProcess = "正在为您重置密码中，请稍后...";
const QString hintResetPasswordSuccessReturn = "重置成功，3s后将自动返回至登录界面...";
#endif // ! 