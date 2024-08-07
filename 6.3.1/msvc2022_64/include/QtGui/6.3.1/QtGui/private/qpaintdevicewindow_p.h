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

#ifndef QPAINTDEVICEWINDOW_P_H
#define QPAINTDEVICEWINDOW_P_H

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
#include <QtGui/QPaintDeviceWindow>
#include <QtCore/QCoreApplication>
#include <QtGui/private/qwindow_p.h>
#include <QtGui/QPaintEvent>

QT_BEGIN_NAMESPACE

class Q_GUI_EXPORT QPaintDeviceWindowPrivate : public QWindowPrivate
{
    Q_DECLARE_PUBLIC(QPaintDeviceWindow)

public:
    QPaintDeviceWindowPrivate();
    ~QPaintDeviceWindowPrivate() override;

    virtual void beginPaint(const QRegion &region)
    {
        Q_UNUSED(region);
    }

    virtual void endPaint()
    {
    }

    virtual void flush(const QRegion &region)
    {
        Q_UNUSED(region);
    }

    bool paint(const QRegion &region)
    {
        Q_Q(QPaintDeviceWindow);
        QRegion toPaint = region & dirtyRegion;
        if (toPaint.isEmpty())
            return false;

        // Clear the region now. The overridden functions may call update().
        dirtyRegion -= toPaint;

        beginPaint(toPaint);

        QPaintEvent paintEvent(toPaint);
        q->paintEvent(&paintEvent);

        endPaint();

        return true;
    }

    void doFlush(const QRegion &region)
    {
        QRegion toFlush = region;
        if (paint(toFlush))
            flush(toFlush);
    }

    void handleUpdateEvent()
    {
        if (dirtyRegion.isEmpty())
            return;
        doFlush(dirtyRegion);
    }

    void markWindowAsDirty()
    {
        Q_Q(QPaintDeviceWindow);
        dirtyRegion += QRect(QPoint(0, 0), q->size());
    }

private:
    QRegion dirtyRegion;
};


QT_END_NAMESPACE

#endif //QPAINTDEVICEWINDOW_P_H
