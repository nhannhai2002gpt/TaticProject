#include "ConnectDialog.h"
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSerialPortInfo>

ConnectDialog::ConnectDialog(QWidget* parent)
    : QDialog(parent) {
    buildUi();
    refreshPorts();
}

void ConnectDialog::buildUi() {
    setWindowTitle("Kết nối NMEA");
    auto* v = new QVBoxLayout(this);
    serialRadio_ = new QRadioButton("Serial (COM)", this);
    tcpRadio_ = new QRadioButton("TCP", this);
    serialRadio_->setChecked(true);
    auto* radios = new QHBoxLayout();
    radios->addWidget(serialRadio_);
    radios->addWidget(tcpRadio_);
    v->addLayout(radios);

    auto* serialRow = new QHBoxLayout();
    portBox_ = new QComboBox(this);
    baudSpin_ = new QSpinBox(this);
    baudSpin_->setRange(1200, 115200);
    baudSpin_->setValue(4800);
    serialRow->addWidget(new QLabel("Port:", this));
    serialRow->addWidget(portBox_);
    serialRow->addWidget(new QLabel("Baud:", this));
    serialRow->addWidget(baudSpin_);
    v->addLayout(serialRow);

    auto* tcpRow = new QHBoxLayout();
    hostEdit_ = new QLineEdit("127.0.0.1", this);
    tcpPortSpin_ = new QSpinBox(this);
    tcpPortSpin_->setRange(1, 65535);
    tcpPortSpin_->setValue(10110);
    tcpRow->addWidget(new QLabel("Host:", this));
    tcpRow->addWidget(hostEdit_);
    tcpRow->addWidget(new QLabel("Port:", this));
    tcpRow->addWidget(tcpPortSpin_);
    v->addLayout(tcpRow);

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &ConnectDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &ConnectDialog::reject);
    v->addWidget(buttons);
}

void ConnectDialog::refreshPorts() {
    portBox_->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const auto& info : infos) {
        portBox_->addItem(info.portName());
    }
}

NmeaConnectConfig ConnectDialog::config() const {
    NmeaConnectConfig c;
    c.mode = serialRadio_->isChecked() ? NmeaConnectConfig::Mode::Serial : NmeaConnectConfig::Mode::Tcp;
    c.portName = portBox_->currentText();
    c.baudRate = baudSpin_->value();
    c.host = hostEdit_->text();
    c.tcpPort = tcpPortSpin_->value();
    return c;
}

