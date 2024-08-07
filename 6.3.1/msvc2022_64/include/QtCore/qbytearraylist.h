/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Copyright (C) 2016 Intel Corporation.
** Copyright (C) 2014 by Southwest Research Institute (R)
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#include <QtCore/qlist.h>

#ifndef QBYTEARRAYLIST_H
#define QBYTEARRAYLIST_H

#include <QtCore/qbytearray.h>

#include <limits>

QT_BEGIN_NAMESPACE

#if !defined(QT_NO_JAVA_STYLE_ITERATORS)
typedef QListIterator<QByteArray> QByteArrayListIterator;
typedef QMutableListIterator<QByteArray> QMutableByteArrayListIterator;
#endif

#ifndef Q_CLANG_QDOC

namespace QtPrivate {
#if QT_CORE_REMOVED_SINCE(6, 3) && QT_POINTER_SIZE != 4
    QByteArray Q_CORE_EXPORT QByteArrayList_join(const QByteArrayList *that, const char *separator, int separatorLength);
#endif
    QByteArray Q_CORE_EXPORT QByteArrayList_join(const QByteArrayList *that, const char *sep, qsizetype len);
}
#endif

#ifdef Q_CLANG_QDOC
class QByteArrayList : public QList<QByteArray>
#else
template <> struct QListSpecialMethods<QByteArray> : QListSpecialMethodsBase<QByteArray>
#endif
{
#ifndef Q_CLANG_QDOC
protected:
    ~QListSpecialMethods() = default;
#endif
public:
    using QListSpecialMethodsBase<QByteArray>::indexOf;
    using QListSpecialMethodsBase<QByteArray>::lastIndexOf;
    using QListSpecialMethodsBase<QByteArray>::contains;

    QByteArray join(QByteArrayView sep = {}) const
    {
        return QtPrivate::QByteArrayList_join(self(), sep.data(), sep.size());
    }
    Q_WEAK_OVERLOAD
    inline QByteArray join(const QByteArray &sep) const
    { return join(qToByteArrayViewIgnoringNull(sep)); }
    inline QByteArray join(char sep) const
    { return join({&sep, 1}); }
};

QT_END_NAMESPACE

#endif // QBYTEARRAYLIST_H
