/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
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

#ifndef QPLATFORMSURFACE_H
#define QPLATFORMSURFACE_H

//
//  W A R N I N G
//  -------------
//
// This file is part of the QPA API and is not meant to be used
// in applications. Usage of this API may make your code
// source and binary incompatible with future versions of Qt.
//

#include <QtGui/qtguiglobal.h>
#include <QtCore/qnamespace.h>
#include <QtGui/qsurface.h>
#include <QtGui/qsurfaceformat.h>

QT_BEGIN_NAMESPACE

class QPlatformScreen;

#ifndef QT_NO_DEBUG_STREAM
class QDebug;
#endif

class Q_GUI_EXPORT QPlatformSurface
{
public:
    Q_DISABLE_COPY_MOVE(QPlatformSurface)

    virtual ~QPlatformSurface();
    virtual QSurfaceFormat format() const = 0;

    QSurface *surface() const;
    virtual QPlatformScreen *screen() const = 0;

    static bool isRasterSurface(QSurface *surface);

private:
    explicit QPlatformSurface(QSurface *surface);

    QSurface *m_surface;

    friend class QPlatformWindow;
    friend class QPlatformOffscreenSurface;
};


#ifndef QT_NO_DEBUG_STREAM
Q_GUI_EXPORT QDebug operator<<(QDebug debug, const QPlatformSurface *surface);
#endif

QT_END_NAMESPACE

#endif //QPLATFORMSURFACE_H
