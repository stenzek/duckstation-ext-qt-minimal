/****************************************************************************
**
** Copyright (C) 2013 David Faure <faure+bluesystems@kde.org>
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

#ifndef QLOCKFILE_H
#define QLOCKFILE_H

#include <QtCore/qstring.h>
#include <QtCore/qscopedpointer.h>

#if __has_include(<chrono>)
#    include <chrono>
#endif

QT_BEGIN_NAMESPACE

class QLockFilePrivate;

class Q_CORE_EXPORT QLockFile
{
public:
    QLockFile(const QString &fileName);
    ~QLockFile();

    QString fileName() const;

    bool lock();
    bool tryLock(int timeout = 0);
    void unlock();

    void setStaleLockTime(int);
    int staleLockTime() const;

#if __has_include(<chrono>)
    bool tryLock(std::chrono::milliseconds timeout) { return tryLock(int(timeout.count())); }

    void setStaleLockTime(std::chrono::milliseconds value) { setStaleLockTime(int(value.count())); }

    std::chrono::milliseconds staleLockTimeAsDuration() const
    {
        return std::chrono::milliseconds(staleLockTime());
    }
#endif

    bool isLocked() const;
    bool getLockInfo(qint64 *pid, QString *hostname, QString *appname) const;
    bool removeStaleLockFile();

    enum LockError {
        NoError = 0,
        LockFailedError = 1,
        PermissionError = 2,
        UnknownError = 3
    };
    LockError error() const;

protected:
    QScopedPointer<QLockFilePrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(QLockFile)
    Q_DISABLE_COPY(QLockFile)
};

QT_END_NAMESPACE

#endif // QLOCKFILE_H
