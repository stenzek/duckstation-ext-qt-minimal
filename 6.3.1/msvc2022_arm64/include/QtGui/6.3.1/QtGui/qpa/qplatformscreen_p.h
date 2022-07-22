/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QPLATFORMSCREEN_P_H
#define QPLATFORMSCREEN_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/private/qtguiglobal_p.h>

#include <QtCore/qpointer.h>
#include <QtCore/qnativeinterface.h>

QT_BEGIN_NAMESPACE

class QScreen;

class QPlatformScreenPrivate
{
public:
    QPointer<QScreen> screen;
};

// ----------------- QNativeInterface -----------------

namespace QNativeInterface::Private {

#if QT_CONFIG(xcb) || defined(Q_CLANG_QDOC)
struct Q_GUI_EXPORT QXcbScreen
{
    QT_DECLARE_NATIVE_INTERFACE(QXcbScreen, 1, QScreen)
    virtual int virtualDesktopNumber() const = 0;
};
#endif

#if QT_CONFIG(vsp2) || defined(Q_CLANG_QDOC)
struct Q_GUI_EXPORT QVsp2Screen
{
    QT_DECLARE_NATIVE_INTERFACE(QVsp2Screen, 1, QScreen)
    virtual int addLayer(int dmabufFd, const QSize &size, const QPoint &position, uint drmPixelFormat, uint bytesPerLine) = 0;
    virtual void setLayerBuffer(int id, int dmabufFd) = 0;
    virtual void setLayerPosition(int id, const QPoint &position) = 0;
    virtual void setLayerAlpha(int id, qreal alpha) = 0;
    virtual bool removeLayer(int id) = 0;
    virtual void addBlendListener(void (*callback)()) = 0;
};
#endif

#if defined(Q_OS_WEBOS) || defined(Q_CLANG_QDOC)
struct Q_GUI_EXPORT QWebOSScreen
{
    QT_DECLARE_NATIVE_INTERFACE(QWebOSScreen, 1, QScreen)
    virtual int addLayer(void *gbm_bo, const QRectF &geometry) = 0;
    virtual void setLayerBuffer(int id, void *gbm_bo) = 0;
    virtual void setLayerGeometry(int id, const QRectF &geometry) = 0;
    virtual void setLayerAlpha(int id, qreal alpha) = 0;
    virtual bool removeLayer(int id) = 0;
    virtual void addFlipListener(void (*callback)()) = 0;
};
#endif

} // QNativeInterface::Private

QT_END_NAMESPACE

#endif // QPLATFORMSCREEN_P_H
