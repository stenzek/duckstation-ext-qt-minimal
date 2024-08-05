/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQml module of the Qt Toolkit.
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

#ifndef QQMLPROPERTYCACHE_P_H
#define QQMLPROPERTYCACHE_P_H

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

#include <private/qqmlrefcount_p.h>
#include <private/qflagpointer_p.h>
#include "qqmlnotifier_p.h"
#include <private/qqmlpropertyindex_p.h>

#include <private/qlinkedstringhash_p.h>
#include <QtCore/qvarlengtharray.h>
#include <QtCore/qvector.h>
#include <QtCore/qversionnumber.h>

#include <private/qv4value_p.h>
#include <private/qqmlpropertydata_p.h>
#include <private/qqmlenumdata_p.h>
#include <private/qqmlenumvalue_p.h>

#include <limits>

QT_BEGIN_NAMESPACE

class QCryptographicHash;
class QJSEngine;
class QMetaObjectBuilder;
class QQmlVMEMetaObject;
class QQmlPropertyCacheMethodArguments;

class RefCountedMetaObject {
public:
    enum OwnershipMode {
        StaticMetaObject,
        SharedMetaObject
    };

    struct Data {
        ~Data() { if (mode == SharedMetaObject) ::free(const_cast<QMetaObject *>(mo)); }
        const QMetaObject *mo = nullptr;
        int ref = 1;
        OwnershipMode mode;
    } *d;

    RefCountedMetaObject()
        : d(nullptr)
    {}

    RefCountedMetaObject(const QMetaObject *mo, OwnershipMode mode)
        : d(new Data) {
        d->mo = mo;
        d->mode = mode;
    }
    ~RefCountedMetaObject() {
        if (d && !--d->ref)
            delete d;
    }
    RefCountedMetaObject(const RefCountedMetaObject &other)
        : d(other.d)
    {
        if (d && d->ref > 0)
            ++d->ref;
    }
    RefCountedMetaObject &operator =(const RefCountedMetaObject &other)
    {
        if (d == other.d)
            return *this;
        if (d && !--d->ref)
            delete d;
        d = other.d;
        if (d && d->ref > 0)
            ++d->ref;
        return *this;
    }
    operator const QMetaObject *() const { return d ? d->mo : nullptr; }
    const QMetaObject * operator ->() const { return d ? d->mo : nullptr; }
    bool isShared() const { return d && d->mode == SharedMetaObject; }
};

class Q_QML_PRIVATE_EXPORT QQmlPropertyCache : public QQmlRefCount
{
public:
    QQmlPropertyCache();
    QQmlPropertyCache(const QMetaObject *, QTypeRevision metaObjectRevision = QTypeRevision::zero());
    ~QQmlPropertyCache() override;

    void update(const QMetaObject *);
    void invalidate(const QMetaObject *);

    QQmlPropertyCache *copy();

    QQmlPropertyCache *copyAndAppend(
                const QMetaObject *, QTypeRevision typeVersion,
                QQmlPropertyData::Flags propertyFlags = QQmlPropertyData::Flags(),
                QQmlPropertyData::Flags methodFlags = QQmlPropertyData::Flags(),
                QQmlPropertyData::Flags signalFlags = QQmlPropertyData::Flags());

    QQmlPropertyCache *copyAndReserve(int propertyCount,
                                      int methodCount, int signalCount, int enumCount);
    void appendProperty(const QString &, QQmlPropertyData::Flags flags, int coreIndex,
                        QMetaType propType, QTypeRevision revision, int notifyIndex);
    void appendSignal(const QString &, QQmlPropertyData::Flags, int coreIndex,
                      const QMetaType *types = nullptr,
                      const QList<QByteArray> &names = QList<QByteArray>());
    void appendMethod(const QString &, QQmlPropertyData::Flags flags, int coreIndex,
                      QMetaType returnType, const QList<QByteArray> &names,
                      const QVector<QMetaType> &parameterTypes);
    void appendEnum(const QString &, const QVector<QQmlEnumValue> &);

    const QMetaObject *metaObject() const;
    const QMetaObject *createMetaObject();
    const QMetaObject *firstCppMetaObject() const;

    template<typename K>
    QQmlPropertyData *property(const K &key, QObject *object,
                               const QQmlRefPointer<QQmlContextData> &context) const
    {
        return findProperty(stringCache.find(key), object, context);
    }

    QQmlPropertyData *property(int) const;
    QQmlPropertyData *maybeUnresolvedProperty(int) const;
    QQmlPropertyData *method(int) const;
    QQmlPropertyData *signal(int index) const;
    QQmlEnumData *qmlEnum(int) const;
    int methodIndexToSignalIndex(int) const;

    QString defaultPropertyName() const;
    QQmlPropertyData *defaultProperty() const;
    inline QQmlPropertyCache *parent() const;
    // is used by the Qml Designer
    void setParent(QQmlPropertyCache *newParent);

    inline QQmlPropertyData *overrideData(QQmlPropertyData *) const;
    inline bool isAllowedInRevision(QQmlPropertyData *) const;

    static QQmlPropertyData *property(QJSEngine *, QObject *, QStringView,
                                      const QQmlRefPointer<QQmlContextData> &, QQmlPropertyData *);
    static QQmlPropertyData *property(QJSEngine *, QObject *, const QLatin1String &,
                                      const QQmlRefPointer<QQmlContextData> &, QQmlPropertyData *);
    static QQmlPropertyData *property(QJSEngine *, QObject *, const QV4::String *,
                                      const QQmlRefPointer<QQmlContextData> &, QQmlPropertyData *);

    //see QMetaObjectPrivate::originalClone
    int originalClone(int index);
    static int originalClone(const QObject *, int index);

    QList<QByteArray> signalParameterNames(int index) const;
    static QString signalParameterStringForJS(QV4::ExecutionEngine *engine, const QList<QByteArray> &parameterNameList, QString *errorString = nullptr);

    const char *className() const;

    inline int propertyCount() const;
    inline int propertyOffset() const;
    inline int methodCount() const;
    inline int methodOffset() const;
    inline int signalCount() const;
    inline int signalOffset() const;
    inline int qmlEnumCount() const;

    static bool isDynamicMetaObject(const QMetaObject *);

    void toMetaObjectBuilder(QMetaObjectBuilder &);

    inline bool callJSFactoryMethod(QObject *object, void **args) const;

    static bool determineMetaObjectSizes(const QMetaObject &mo, int *fieldCount, int *stringCount);
    static bool addToHash(QCryptographicHash &hash, const QMetaObject &mo);

    QByteArray checksum(bool *ok);

    QTypeRevision allowedRevision(int index) const { return allowedRevisionCache[index]; }
    void setAllowedRevision(int index, QTypeRevision allowed) { allowedRevisionCache[index] = allowed; }

private:
    friend class QQmlEnginePrivate;
    friend class QQmlCompiler;
    template <typename T> friend class QQmlPropertyCacheCreator;
    template <typename T> friend class QQmlPropertyCacheAliasCreator;
    friend class QQmlComponentAndAliasResolver;
    friend class QQmlMetaObject;

    inline QQmlPropertyCache *copy(int reserve);

    void append(const QMetaObject *, QTypeRevision typeVersion,
                QQmlPropertyData::Flags propertyFlags = QQmlPropertyData::Flags(),
                QQmlPropertyData::Flags methodFlags = QQmlPropertyData::Flags(),
                QQmlPropertyData::Flags signalFlags = QQmlPropertyData::Flags());

    QQmlPropertyCacheMethodArguments *createArgumentsObject(int count, const QList<QByteArray> &names);

    typedef QVector<QQmlPropertyData> IndexCache;
    typedef QLinkedStringMultiHash<QPair<int, QQmlPropertyData *> > StringCache;
    typedef QVector<QTypeRevision> AllowedRevisionCache;

    QQmlPropertyData *findProperty(StringCache::ConstIterator it, QObject *,
                                   const QQmlRefPointer<QQmlContextData> &) const;
    QQmlPropertyData *findProperty(StringCache::ConstIterator it, const QQmlVMEMetaObject *,
                                   const QQmlRefPointer<QQmlContextData> &) const;

    void updateRecur(const QMetaObject *);

    template<typename K>
    QQmlPropertyData *findNamedProperty(const K &key) const
    {
        StringCache::mapped_type *it = stringCache.value(key);
        return it ? it->second : 0;
    }

    template<typename K>
    void setNamedProperty(const K &key, int index, QQmlPropertyData *data, bool isOverride)
    {
        stringCache.insert(key, qMakePair(index, data));
        _hasPropertyOverrides |= isOverride;
    }

private:
    enum OverrideResult { NoOverride, InvalidOverride, ValidOverride };

    template<typename String>
    OverrideResult handleOverride(const String &name, QQmlPropertyData *data, QQmlPropertyData *old)
    {
        if (!old)
            return NoOverride;

        if (data->markAsOverrideOf(old))
            return ValidOverride;

        qWarning("Final member %s is overridden in class %s. The override won't be used.",
                 qPrintable(name), className());
        return InvalidOverride;
    }

    template<typename String>
    OverrideResult handleOverride(const String &name, QQmlPropertyData *data)
    {
        return handleOverride(name, data, findNamedProperty(name));
    }

    int propertyIndexCacheStart; // placed here to avoid gap between QQmlRefCount and _parent
    QQmlPropertyCache *_parent;

    IndexCache propertyIndexCache;
    IndexCache methodIndexCache;
    IndexCache signalHandlerIndexCache;
    StringCache stringCache;
    AllowedRevisionCache allowedRevisionCache;
    QVector<QQmlEnumData> enumCache;

    RefCountedMetaObject _metaObject;
    QByteArray _dynamicClassName;
    QByteArray _dynamicStringData;
    QString _defaultPropertyName;
    QQmlPropertyCacheMethodArguments *argumentsCache;
    QByteArray _checksum;
    int methodIndexCacheStart;
    int signalHandlerIndexCacheStart;
    int _jsFactoryMethodIndex;
    bool _hasPropertyOverrides;
    bool _ownMetaObject;
};

// Returns this property cache's metaObject.  May be null if it hasn't been created yet.
inline const QMetaObject *QQmlPropertyCache::metaObject() const
{
    return _metaObject;
}

// Returns the first C++ type's QMetaObject - that is, the first QMetaObject not created by
// QML
inline const QMetaObject *QQmlPropertyCache::firstCppMetaObject() const
{
    const QQmlPropertyCache *p = this;
    while (!p->_metaObject || p->_metaObject.isShared())
        p = p->parent();
    return p->_metaObject;
}

inline QQmlPropertyData *QQmlPropertyCache::property(int index) const
{
    if (index < 0 || index >= (propertyIndexCacheStart + propertyIndexCache.count()))
        return nullptr;

    if (index < propertyIndexCacheStart)
        return _parent->property(index);

    return const_cast<QQmlPropertyData *>(&propertyIndexCache.at(index - propertyIndexCacheStart));
}

inline QQmlPropertyData *QQmlPropertyCache::method(int index) const
{
    if (index < 0 || index >= (methodIndexCacheStart + methodIndexCache.count()))
        return nullptr;

    if (index < methodIndexCacheStart)
        return _parent->method(index);

    return const_cast<QQmlPropertyData *>(&methodIndexCache.at(index - methodIndexCacheStart));
}

/*! \internal
    \a index MUST be in the signal index range (see QObjectPrivate::signalIndex()).
    This is different from QMetaMethod::methodIndex().
*/
inline QQmlPropertyData *QQmlPropertyCache::signal(int index) const
{
    if (index < 0 || index >= (signalHandlerIndexCacheStart + signalHandlerIndexCache.count()))
        return nullptr;

    if (index < signalHandlerIndexCacheStart)
        return _parent->signal(index);

    QQmlPropertyData *rv = const_cast<QQmlPropertyData *>(&methodIndexCache.at(index - signalHandlerIndexCacheStart));
    Q_ASSERT(rv->isSignal() || rv->coreIndex() == -1);
    return rv;
}

inline QQmlEnumData *QQmlPropertyCache::qmlEnum(int index) const
{
    if (index < 0 || index >= enumCache.count())
        return nullptr;

    return const_cast<QQmlEnumData *>(&enumCache.at(index));
}

inline int QQmlPropertyCache::methodIndexToSignalIndex(int index) const
{
    if (index < 0 || index >= (methodIndexCacheStart + methodIndexCache.count()))
        return index;

    if (index < methodIndexCacheStart)
        return _parent->methodIndexToSignalIndex(index);

    return index - methodIndexCacheStart + signalHandlerIndexCacheStart;
}

// Returns the name of the default property for this cache
inline QString QQmlPropertyCache::defaultPropertyName() const
{
    return _defaultPropertyName;
}

inline QQmlPropertyCache *QQmlPropertyCache::parent() const
{
    return _parent;
}

QQmlPropertyData *
QQmlPropertyCache::overrideData(QQmlPropertyData *data) const
{
    if (!data->hasOverride())
        return nullptr;

    if (data->overrideIndexIsProperty())
        return property(data->overrideIndex());
    else
        return method(data->overrideIndex());
}

bool QQmlPropertyCache::isAllowedInRevision(QQmlPropertyData *data) const
{
    const QTypeRevision requested = data->revision();
    const int offset = data->metaObjectOffset();
    if (offset == -1 && requested == QTypeRevision::zero())
        return true;

    Q_ASSERT(offset >= 0);
    Q_ASSERT(offset < allowedRevisionCache.length());
    const QTypeRevision allowed = allowedRevisionCache[offset];

    if (requested.hasMajorVersion()) {
        if (requested.majorVersion() > allowed.majorVersion())
            return false;
        if (requested.majorVersion() < allowed.majorVersion())
            return true;
    }

    return !requested.hasMinorVersion() || requested.minorVersion() <= allowed.minorVersion();
}

int QQmlPropertyCache::propertyCount() const
{
    return propertyIndexCacheStart + propertyIndexCache.count();
}

int QQmlPropertyCache::propertyOffset() const
{
    return propertyIndexCacheStart;
}

int QQmlPropertyCache::methodCount() const
{
    return methodIndexCacheStart + methodIndexCache.count();
}

int QQmlPropertyCache::methodOffset() const
{
    return methodIndexCacheStart;
}

int QQmlPropertyCache::signalCount() const
{
    return signalHandlerIndexCacheStart + signalHandlerIndexCache.count();
}

int QQmlPropertyCache::signalOffset() const
{
    return signalHandlerIndexCacheStart;
}

int QQmlPropertyCache::qmlEnumCount() const
{
    return enumCache.count();
}

bool QQmlPropertyCache::callJSFactoryMethod(QObject *object, void **args) const
{
    if (_jsFactoryMethodIndex != -1) {
        _metaObject->d.static_metacall(object, QMetaObject::InvokeMetaMethod, _jsFactoryMethodIndex, args);
        return true;
    }
    if (_parent)
        return _parent->callJSFactoryMethod(object, args);
    return false;
}

QT_END_NAMESPACE

#endif // QQMLPROPERTYCACHE_P_H
