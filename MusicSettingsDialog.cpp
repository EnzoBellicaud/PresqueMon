#include "MusicSettingsDialog.h"
#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>

MusicSettingsDialog::MusicSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Music Settings"));

    musicCheckBox = new QCheckBox(tr("Enable Music"));
    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(musicCheckBox);
    layout->addWidget(volumeSlider);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Apply | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &MusicSettingsDialog::applySettings);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &MusicSettingsDialog::reject);
    layout->addWidget(buttonBox);
}

void MusicSettingsDialog::applySettings()
{
    bool musicEnabled = musicCheckBox->isChecked();
    int volume = volumeSlider->value();
    emit musicSettingsChanged(musicEnabled, volume);
    accept();
}