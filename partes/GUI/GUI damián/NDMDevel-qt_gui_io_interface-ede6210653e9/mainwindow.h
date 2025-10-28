#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QRadioButton>
#include <QVector>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

//---------------------------------------------
public slots:
    void slider_an0(int value);
    void slider_an1(int value);
    void spin_out_an0(double value);
    void spin_out_an1(double value);
    void update_progress_an0(int value);
    void update_progress_an1(int value);
    void autosend_an0_changed(int value);
    void autosend_an1_changed(int value);
    void btn_connect();
    void on_rx();
    void update_io_label();
    void update_analog_label();
    void on_updateAutoreadPeriod();
    void on_digitalOutputUpdate(bool value);
    void write_an0();
    void write_an1();
    void on_sampleUpdate();
    void on_maxAn0OutChanged();
    void on_maxAn1OutChanged();
    void on_maxAn0InChanged();
    void on_maxAn1InChanged();
    void on_refreshSerialPorts();
    void on_serialError(QSerialPort::SerialPortError error);
    void on_confQuiet();
    void on_confAutoread();
    void on_saveCsvRequested();
    void on_exitRequested();
    void close_serial_port();
    void update_plot_an0_label();
    void update_plot_an1_label();
private:
    void connect_an0_slider_spin();
    void connect_max_an_out_changed();
    void connect_max_an_in_changed();
    void connect_autosend_an();
    void connect_edit_io_labels();
    void connect_checkbox_out();
    void connect_send_an();
    void connect_autoread();
    void connect_serial_port();
    void connect_plot_samples();
    void connect_file_menu();

    void update_spin_an0_out(int value);
    void update_spin_an1_out(int value);
    void set_enable_analog_panel(bool state);
    void set_enable_digital_panel(bool state);
    void show_message(QString title,QString message);
    void send_serial_reset(bool report_error = true);
    void reset_and_close_serial_port();
    void update_radiobutton_label(QRadioButton* target);
    void send_serial_data(QString str,bool report_error = true);
    void update_all_io(QByteArray array);
    void update_plot(double new_an0,double new_an1);
    void update_plot_gui();
    void closeEvent(QCloseEvent *event) override;
    std::tuple<double,double,double,double> plot_min_ave_half_max(const QVector<double>& v,
                                                                 const QVector<double>& t);
private:
//    serialib _serial;

    QSerialPort _com;
    QVector<double> _plot_t;
    QVector<double> _plot_an0;
    QVector<double> _plot_an1;
    int             _plot_size;
    double          _an0_out_max;
    double          _an1_out_max;
    double          _an0_in_max;
    double          _an1_in_max;
    QTimer          _timer;
    bool            _serial_reopened;
};
#endif // MAINWINDOW_H
