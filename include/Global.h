#ifndef GLOBAL_H
#define GLOBAL_H
#include "Config.h"
#include <QString>
#include <iostream>
#include <unordered_map>
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
	ID_CHAT_LOGIN = 5,
};

enum MSG_IDS {
	MSG_HELLO_WORD = 1001,
	MSG_LOGIN = 1002,
	MSG_CHAT_LOGIN_RSP = 1003,
};

enum ERRORCODE {
	SUCCESS = 0,
	Error_Json = 1001,				   // Json解析错误
	RPCFailed = 1002,				   // RPC请求错误
	Password_Not_Equal = 1003,		   // 密码不一致
	Varify_Code_Expired = 1004,		   // 验证码失效
	Varify_Code_Not_Equal = 1005,	   // 验证码不一致
	Error_User_Exist = 1006,		   /// 用户已存在
	Error_User_Not_Exist = 1007,	   // 用户不存在
	Error_Update_Password = 1008,	   /// 更新数据库失败
	ERROR_PASSWORD_NOT_CORRECT = 1009, /// 密码不正确
	ERROR_USER_EMAIL_NOT_MATCH = 1010, // 用户名与邮箱不匹配
	ERROR_NETWORK = 1030,			   /// 网络错误
};

const std::unordered_map<ERRORCODE, std::string> ErrorMap = {
	{ERRORCODE::Error_Json, "服务端JSON解析错误"},
	{ERRORCODE::RPCFailed, "服务端RPC请求错误"},
	{ERRORCODE::Password_Not_Equal, "两次密码不一致"},
	{ERRORCODE::Varify_Code_Expired, "验证码失效"},
	{ERRORCODE::Varify_Code_Not_Equal, "验证码不一致"},
	{ERRORCODE::Error_User_Exist, "用户名或邮箱已存在"},
	{ERRORCODE::Error_User_Not_Exist, "用户名或邮箱不存在"},
	{ERRORCODE::Error_Update_Password, "更新数据库失败"},
	{ERRORCODE::ERROR_PASSWORD_NOT_CORRECT, "密码不正确"},
	{ERRORCODE::ERROR_NETWORK, "网络错误！"},
	{ERRORCODE::ERROR_USER_EMAIL_NOT_MATCH, "用户名与邮箱不匹配！"},
};

typedef struct ServerInfo {
	QString Host;
	QString Port;
	QString Uid;
	QString Token;
} ServerInfo;

const QString errorUserEmailExists = "用户邮箱已存在！";
const QString errorUserEmailNotExists = "用户名或邮箱不存在！";
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
const QString hintResetPasswordImformationNotComplete = "所填入信息不完整...";
const QString hintResetPasswordProcess = "正在为您重置密码中，请稍后...";
const QString hintResetPasswordSuccessReturn = "重置成功，3s后将自动返回至登录界面...";
const QString hintResetPasswordFailedReturn = "重置密码失败!";
const QString hintGetChatServerFailed = "获取聊天服务器IP及PORT失败";
const QString hintGetChatServerSuccess = "获取聊天服务器IP及PORT成功，正在连接服务器...";
const QString hintConnectChatServerSuccess = "聊天服务连接成功，正在登录...";
const QString hintConnectChatServerFailed = "聊天服务连接失败";
#endif // !