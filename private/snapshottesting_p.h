#pragma once
#include <QQmlContext>
#include <QJSValue>
#include <functional>
#include <QFuture>
#include <QQuickItem>

namespace SnapshotTesting {

    namespace Private {

        class SignalProxy : public QObject {
            Q_OBJECT
        public:
            inline SignalProxy(QObject* parent) : QObject(parent) {
            }
        signals:
            void proxy();
        };

        class EnumString {
        public:
            QString componentName;
            QString key;
        };

        class QmlType {
        public:
            inline QmlType() {
                isNull = true;
            }
            QString elementName;
            const QMetaObject* meta;
            bool isNull;
            QString module;
            int majorVersion;
            int minorVersion;
            QString className;
            bool isCreatable;
        };

        QString classNameToComponentName(const QString &className);

        /// Obtain the context of the input object which should it be belonged to, but not its parent's scope
        QQmlContext* obtainCurrentScopeContext(QObject* object);

        QQmlContext* obtainCreationContext(QObject* object);

        QString obtainComponentNameByBaseUrl(const QUrl& baseUrl);

        /// Obtain the name of the component by the creation context (the bottom most component)
        QString obtainComponentNameByBaseContext(QObject* object);

        QString obtainComponentNameByInheritedContext(QObject * object);

        QString obtainComponentNameByClass(QObject* object);

        QString obtainComponentNameByInheritedClass(QObject* object);

        QString obtainComponentNameByQuickClass(QObject* object);

        QString obtainComponentNameByCurrentScopeContext(QObject* object);

        QString obtainRootComponentName(QObject* object, bool expandAll = false);

        QStringList listContextUrls(QObject* object);

        QString stringify(QJSEngine*engine, QJSValue value);

        QString stringify(QVariant v);

        QString leftpad(QString text, int pad);

        QString indentText(QString text, int pad);

        QObjectList obtainChildrenObjectList(QObject * object);

        /// Walk on a QML tree structure
        void walk(QObject* object, std::function<bool(QObject*, QObject*)> predicate);

        /// Wait for a object loaded completely
        bool subscribeOnReady(QObject* object, int timeout = 10000);

        QString obtainQmlPackage(QObject* object);

        /// Obtain the default values of the object. The result is not hard coded from database. It will create a new default instance and read its default values
        QVariantMap obtainDynamicDefaultValues(const QMetaObject* meta);

        QVariantMap obtainDynamicDefaultValues(QObject* object);

        QObject* createQmlComponent(QQmlEngine* engine, QString componentName, QString package, int major, int minor);

        QFuture<QImage> grabImage(QQuickItem* item);

        QFuture<QImage> render(const QString& source);

        QByteArray toBase64(const QImage& image);

    }
}

Q_DECLARE_METATYPE(SnapshotTesting::Private::EnumString)
