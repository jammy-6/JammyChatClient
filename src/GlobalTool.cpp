#include "GlobalTool.h"
#include "ConfigMgr.h"
#include <memory>
#include <qapplication.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <string>
void reloadQss() {
	QString path = RESOURCE_DIR + QString("/style.qss");
	QFile file(path);
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	qApp->setStyleSheet(styleSheet);
}

void initSpdlog() {
	// 控制台logger
	spdlog::level::level_enum log_level =
		static_cast<spdlog::level::level_enum>(
			std::stoi(gConfigMgr["LogSystem"]["Level"]));
	std::string log_path = gConfigMgr["LogSystem"]["Path"] + "/" +
						   gConfigMgr["LogSystem"]["Suffix"];
	try {
		// 创建一个输出到控制台的彩色日志接收器
		auto console_sink =
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_level(spdlog::level::trace);
		console_sink->set_pattern(
			"[%Y年%m月%d日 %H:%M:%S] [%n] [-%L-] [t:%t] %v");
		// 创建一个输出到文件的日志接收器
		auto file_sink =
			std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_path, true);
		file_sink->set_level(spdlog::level::trace);
		file_sink->set_pattern("[%Y年%m月%d日 %H:%M:%S] [%n] [%l] [t:%t] %v");
		// 创建一个组合的日志记录器，把控制台和文件接收器都加进去
		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(console_sink);
		sinks.push_back(file_sink);

		std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>(
			"multi_sink", begin(sinks), end(sinks));

		logger->set_level(log_level);
		logger->flush_on(log_level);
		// 设置全局日志记录器
		spdlog::register_logger(logger);
		spdlog::set_level(log_level);
		spdlog::set_default_logger(logger);

	} catch (const spdlog::spdlog_ex &ex) {
		std::cout << "Log init failed: " << ex.what() << std::endl;
	}
}

unsigned char ToHex(unsigned char x) { return x > 9 ? x + 55 : x + 48; }

unsigned char FromHex(unsigned char x) {
	unsigned char y;
	if (x >= 'A' && x <= 'Z')
		y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z')
		y = x - 'a' + 10;
	else if (x >= '0' && x <= '9')
		y = x - '0';
	else
		assert(0);
	return y;
}
std::string UrlEncode(const std::string &str) {
	std::string strTemp;
	size_t length = str.length();
	for (size_t i = 0; i < length; i++) {
		// 判断是否仅有数字和字母构成
		if (isalnum((unsigned char)str[i]) || (str[i] == '-') ||
			(str[i] == '_') || (str[i] == '.') || (str[i] == '~'))
			strTemp += str[i];
		else if (str[i] == ' ') // 为空字符
			strTemp += "+";
		else {
			// 其他字符需要提前加%并且高四位和低四位分别转为16进制
			strTemp += '%';
			strTemp += ToHex((unsigned char)str[i] >> 4);
			strTemp += ToHex((unsigned char)str[i] & 0x0F);
		}
	}
	return strTemp;
}