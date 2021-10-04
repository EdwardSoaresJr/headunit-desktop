#include "volumecontrol.h"

VolumeControl::VolumeControl(QObject *parent) : QObject (parent)
{
    qmlRegisterType<PulseAudioQt::CardModel>("HUDVolume", 1, 0, "CardModel");
    qmlRegisterType<PulseAudioQt::SinkModel>("HUDVolume", 1, 0, "SinkModel");
    qmlRegisterType<PulseAudioQt::SinkInputModel>("HUDVolume", 1, 0, "SinkInputModel");
    qmlRegisterType<PulseAudioQt::SourceModel>("HUDVolume", 1, 0, "SourceModel");
    qmlRegisterType<PulseAudioQt::SourceOutputModel>("HUDVolume", 1, 0, "SourceOutputModel");
    qmlRegisterType<PulseAudioQt::StreamRestoreModel>("HUDVolume", 1, 0, "StreamRestoreModel");
    qmlRegisterType<PulseAudioQt::ModuleModel>("HUDVolume", 1, 0, "ModuleModel");
}

void VolumeControl::init(){
    m_pluginSettings.actions = QStringList() << "VolumeUp" << "VolumeDown";

}
QObject *VolumeControl::getContextProperty(){
    return this;
}

void VolumeControl::actionMessage(QString id, QVariant message){
    PulseAudioQt::SinkModel sink;
    PulseAudioQt::Sink * defaultSink = sink.defaultSink();

    int volume = 0;
    if(id == "VolumeUp"){
        volume = defaultSink->volume() + 655;
    } else if(id == "VolumeDown") {
        volume = defaultSink->volume() - 655;
    }
    if(volume <= PulseAudioQt::maximumVolume() && volume >= PulseAudioQt::minimumVolume()){
        defaultSink->setVolume(volume);
    }
}
