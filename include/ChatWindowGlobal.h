#ifndef CHAT_WINDOW_GLOBAL_H
#define CHAT_WINDOW_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CHAT_WINDOW_LIBRARY)
#define CHAT_WINDOW_EXPORT Q_DECL_EXPORT
#else
#define CHAT_WINDOW_EXPORT Q_DECL_IMPORT
#endif

#endif // CHAT_WINDOW_GLOBAL_H
