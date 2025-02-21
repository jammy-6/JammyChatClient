#ifndef CHAT_MGR_GLOBAL_H
#define CHAT_MGR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CHAT_MGR_LIBRARY)
#define CHAT_MGR_EXPORT Q_DECL_EXPORT
#else
#define CHAT_MGR_EXPORT Q_DECL_IMPORT
#endif

#endif // CHAT_MGR_GLOBAL_H
