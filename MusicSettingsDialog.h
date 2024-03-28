#ifndef MUSICSETTINGSDIALOG_H
#define MUSICSETTINGSDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QSlider>

class MainWindow;

class MusicSettingsDialog : public QDialog
{
    Q_OBJECT

signals:
    void musicSettingsChanged(bool musicEnabled, int volume);

public:
    MusicSettingsDialog(QWidget *parent = nullptr);

public slots:
    void applySettings();

private:
    QCheckBox *musicCheckBox;
    QSlider *volumeSlider;
};

#endif // MUSICSETTINGSDIALOG_H
