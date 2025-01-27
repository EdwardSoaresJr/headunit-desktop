#ifndef PLUGINOBJECT_H
#define PLUGINOBJECT_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>
#include <QLoggingCategory>

#include <QPluginLoader>

#include <plugininterface.h>
#include <mediainterface.h>
#include <hud-common.h>
#include "settingsloader.h"

class PluginObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool loaded READ getLoaded NOTIFY loadedChanged)
    Q_PROPERTY(QVariant qmlSource READ getSource NOTIFY sourceChanged)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString label READ getLabel CONSTANT)
    Q_PROPERTY(QString icon READ getLabel CONSTANT)
    Q_PROPERTY(QVariant settings READ getSettings CONSTANT)
    Q_PROPERTY(QObject * contextProperty READ getContextProperty CONSTANT)
public:
    explicit PluginObject(QString fileName, QObject *parent = nullptr);
    explicit PluginObject(QString name,
                          QString label,
                          QObject *parent = nullptr,
                          QString icon = "",
                          QString qmlSource = "",
                          QVariantMap settingsMenu = QVariantMap(),
                          QVariant settings = QVariant(),
                          QVariantList bottomBarItems = QVariantList());
    ~PluginObject();

    void setSource(QString source);

    bool getLoaded();
    QString getSource();
    QString getName();
    QString getLabel();
    QString getIcon();

    QObject * getContextProperty();
    QQuickImageProvider *getImageProvider();

    QObject *getPlugin();
    QVariant getSettings();
    QVariantMap getSettingsItems();
    QList<PanelItem> getBottomBarItems();
    MediaInterface *getMediaInterface();
    void connectToPropertySignal(QString propertyName, QString slotName);
    QVariant getPropertyValue(QString propertyName);

    Q_INVOKABLE void callSlot(QString slot);

    void init();
public slots:
    void handleMessage(QString id, QVariant message);
    void callAction(QString id, QVariant message);
    void updateBottomBarItems();

signals:
    void loadedChanged();
    void sourceChanged();

    void message(QString sender, QString message, QVariant parameter);
    void action(QString sender, QString action, QVariant parameter);
    void bottomBarItemsUpdated();
private slots:
    void messageHandler(QString messageId, QVariant parameter);
    void actionHandler(QString actionId, QVariant parameter);
private:
    void loadBottomBarItems(QVariantList bottomBarItems);
    bool m_loaded;
    QVariant m_pluginFileName;

    QString m_name;
    QString m_label;
    QString m_icon;
    QString m_source;
    QVariant m_config;
    QList<PanelItem> m_bottomBarItems;

    QPluginLoader m_pluginLoader;
    QObject *m_plugin = nullptr;
    PluginInterface *m_pluginInterface = nullptr;

    QVariant m_settings;
    QVariantMap m_settingsMenu;
    MediaInterface * m_mediaInterface = nullptr;
};

#endif // PLUGINOBJECT_H
