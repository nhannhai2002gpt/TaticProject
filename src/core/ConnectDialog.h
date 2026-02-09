#pragma once

#include <QDialog>
#include <QString>

class QComboBox;
class QSpinBox;
class QLineEdit;
class QRadioButton;

struct NmeaConnectConfig {
    enum class Mode { Serial, Tcp } mode{Mode::Serial};
    QString portName;
    int baudRate{4800};
    QString host{"127.0.0.1"};
    int tcpPort{10110};
};

class ConnectDialog : public QDialog {
    Q_OBJECT
public:
    explicit ConnectDialog(QWidget* parent = nullptr);
    NmeaConnectConfig config() const;

private:
    void buildUi();
    void refreshPorts();

    QRadioButton* serialRadio_{nullptr};
    QRadioButton* tcpRadio_{nullptr};
    QComboBox* portBox_{nullptr};
    QSpinBox* baudSpin_{nullptr};
    QLineEdit* hostEdit_{nullptr};
    QSpinBox* tcpPortSpin_{nullptr};
};

