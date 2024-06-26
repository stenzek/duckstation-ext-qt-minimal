/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
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

#ifndef QCOLORTRANSFORM_H
#define QCOLORTRANSFORM_H

#include <QtGui/qtguiglobal.h>
#include <QtGui/qrgb.h>
#include <QtCore/qshareddata.h>

QT_BEGIN_NAMESPACE

class QColor;
class QRgba64;
class QColorSpacePrivate;
class QColorTransformPrivate;
QT_DECLARE_QESDP_SPECIALIZATION_DTOR_WITH_EXPORT(QColorTransformPrivate, Q_GUI_EXPORT)

class QColorTransform
{
public:
    QColorTransform() noexcept = default;
    Q_GUI_EXPORT ~QColorTransform();
    Q_GUI_EXPORT QColorTransform(const QColorTransform &colorTransform) noexcept;
    QColorTransform(QColorTransform &&colorTransform) = default;
    QColorTransform &operator=(const QColorTransform &other) noexcept
    {
        QColorTransform{other}.swap(*this);
        return *this;
    }
    QT_MOVE_ASSIGNMENT_OPERATOR_IMPL_VIA_MOVE_AND_SWAP(QColorTransform)

    void swap(QColorTransform &other) noexcept { d.swap(other.d); }

    Q_GUI_EXPORT QRgb map(QRgb argb) const;
    Q_GUI_EXPORT QRgba64 map(QRgba64 rgba64) const;
    Q_GUI_EXPORT QColor map(const QColor &color) const;

private:
    friend class QColorSpace;
    friend class QColorSpacePrivate;
    friend class QColorTransformPrivate;
    friend class QImage;

    QExplicitlySharedDataPointer<QColorTransformPrivate> d;
};

Q_DECLARE_SHARED(QColorTransform)

QT_END_NAMESPACE

#endif // QCOLORTRANSFORM_H
