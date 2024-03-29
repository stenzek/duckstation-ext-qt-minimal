/****************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
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

#ifndef QPLATFORMOFFSCREENSURFACE_H
#define QPLATFORMOFFSCREENSURFACE_H

//
//  W A R N I N G
//  -------------
//
// This file is part of the QPA API and is not meant to be used
// in applications. Usage of this API may make your code
// source and binary incompatible with future versions of Qt.
//

#include "qplatformsurface.h"

#include <QtGui/qoffscreensurface.h>
#include <QtCore/qscopedpointer.h>

#include <QtCore/qnativeinterface.h>

QT_BEGIN_NAMESPACE

class QOffscreenSurface;
class QPlatformScreen;
class QPlatformOffscreenSurfacePrivate;

class Q_GUI_EXPORT QPlatformOffscreenSurface : public QPlatformSurface
{
    Q_DECLARE_PRIVATE(QPlatformOffscreenSurface)
public:
    explicit QPlatformOffscreenSurface(QOffscreenSurface *offscreenSurface);
    ~QPlatformOffscreenSurface() override;

    QOffscreenSurface *offscreenSurface() const;

    QPlatformScreen *screen() const override;

    virtual QSurfaceFormat format() const override;
    virtual bool isValid() const;

protected:
    QScopedPointer<QPlatformOffscreenSurfacePrivate> d_ptr;
    friend class QOffscreenSurfacePrivate;
private:
    Q_DISABLE_COPY(QPlatformOffscreenSurface)
};

namespace QNativeInterface::Private {

#if defined(Q_OS_ANDROID)
struct Q_GUI_EXPORT QAndroidOffScreenIntegration
{
    QT_DECLARE_NATIVE_INTERFACE(QAndroidOffScreenIntegration)
    virtual QOffscreenSurface *createOffscreenSurface(ANativeWindow *nativeSurface) const = 0;
};
#endif

} // QNativeInterface::Private


QT_END_NAMESPACE

#endif // QPLATFORMOFFSCREENSURFACE_H
