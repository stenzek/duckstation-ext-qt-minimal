// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QREADWRITELOCK_H
#define QREADWRITELOCK_H

#include <QtCore/qglobal.h>

QT_BEGIN_NAMESPACE


#if QT_CONFIG(thread)

class QReadWriteLockPrivate;

class Q_CORE_EXPORT QReadWriteLock
{
public:
    enum RecursionMode { NonRecursive, Recursive };

    explicit QReadWriteLock(RecursionMode recursionMode = NonRecursive);
    ~QReadWriteLock();

    void lockForRead();
    bool tryLockForRead();
    bool tryLockForRead(int timeout);

    void lockForWrite();
    bool tryLockForWrite();
    bool tryLockForWrite(int timeout);

    void unlock();

private:
    Q_DISABLE_COPY(QReadWriteLock)
    QAtomicPointer<QReadWriteLockPrivate> d_ptr;

    enum StateForWaitCondition { LockedForRead, LockedForWrite, Unlocked, RecursivelyLocked };
    StateForWaitCondition stateForWaitCondition() const;
    friend class QWaitCondition;
};

#if defined(Q_CC_MSVC)
#pragma warning( push )
#pragma warning( disable : 4312 ) // ignoring the warning from /Wp64
#endif

class Q_CORE_EXPORT QReadLocker
{
public:
    inline QReadLocker(QReadWriteLock *readWriteLock);

    inline ~QReadLocker()
    { unlock(); }

    inline void unlock()
    {
        if (q_val) {
            if ((q_val & quintptr(1u)) == quintptr(1u)) {
                q_val &= ~quintptr(1u);
                readWriteLock()->unlock();
            }
        }
    }

    inline void relock()
    {
        if (q_val) {
            if ((q_val & quintptr(1u)) == quintptr(0u)) {
                readWriteLock()->lockForRead();
                q_val |= quintptr(1u);
            }
        }
    }

    inline QReadWriteLock *readWriteLock() const
    { return reinterpret_cast<QReadWriteLock *>(q_val & ~quintptr(1u)); }

private:
    Q_DISABLE_COPY(QReadLocker)
    quintptr q_val;
};

inline QReadLocker::QReadLocker(QReadWriteLock *areadWriteLock)
    : q_val(reinterpret_cast<quintptr>(areadWriteLock))
{
    Q_ASSERT_X((q_val & quintptr(1u)) == quintptr(0),
               "QReadLocker", "QReadWriteLock pointer is misaligned");
    relock();
}

class Q_CORE_EXPORT QWriteLocker
{
public:
    inline QWriteLocker(QReadWriteLock *readWriteLock);

    inline ~QWriteLocker()
    { unlock(); }

    inline void unlock()
    {
        if (q_val) {
            if ((q_val & quintptr(1u)) == quintptr(1u)) {
                q_val &= ~quintptr(1u);
                readWriteLock()->unlock();
            }
        }
    }

    inline void relock()
    {
        if (q_val) {
            if ((q_val & quintptr(1u)) == quintptr(0u)) {
                readWriteLock()->lockForWrite();
                q_val |= quintptr(1u);
            }
        }
    }

    inline QReadWriteLock *readWriteLock() const
    { return reinterpret_cast<QReadWriteLock *>(q_val & ~quintptr(1u)); }


private:
    Q_DISABLE_COPY(QWriteLocker)
    quintptr q_val;
};

inline QWriteLocker::QWriteLocker(QReadWriteLock *areadWriteLock)
    : q_val(reinterpret_cast<quintptr>(areadWriteLock))
{
    Q_ASSERT_X((q_val & quintptr(1u)) == quintptr(0),
               "QWriteLocker", "QReadWriteLock pointer is misaligned");
    relock();
}

#if defined(Q_CC_MSVC)
#pragma warning( pop )
#endif

#else // QT_CONFIG(thread)

class Q_CORE_EXPORT QReadWriteLock
{
public:
    enum RecursionMode { NonRecursive, Recursive };
    inline explicit QReadWriteLock(RecursionMode = NonRecursive) noexcept { }
    inline ~QReadWriteLock() { }

    void lockForRead() noexcept { }
    bool tryLockForRead() noexcept { return true; }
    bool tryLockForRead(int timeout) noexcept { Q_UNUSED(timeout); return true; }

    void lockForWrite() noexcept { }
    bool tryLockForWrite() noexcept { return true; }
    bool tryLockForWrite(int timeout) noexcept { Q_UNUSED(timeout); return true; }

    void unlock() noexcept { }

private:
    Q_DISABLE_COPY(QReadWriteLock)
};

class Q_CORE_EXPORT QReadLocker
{
public:
    inline explicit QReadLocker(QReadWriteLock *) noexcept { }
    inline ~QReadLocker() noexcept { }

    void unlock() noexcept { }
    void relock() noexcept { }
    QReadWriteLock *readWriteLock() noexcept { return nullptr; }

private:
    Q_DISABLE_COPY(QReadLocker)
};

class Q_CORE_EXPORT QWriteLocker
{
public:
    inline explicit QWriteLocker(QReadWriteLock *) noexcept { }
    inline ~QWriteLocker() noexcept { }

    void unlock() noexcept { }
    void relock() noexcept { }
    QReadWriteLock *readWriteLock() noexcept { return nullptr; }

private:
    Q_DISABLE_COPY(QWriteLocker)
};

#endif // QT_CONFIG(thread)

QT_END_NAMESPACE

#endif // QREADWRITELOCK_H
