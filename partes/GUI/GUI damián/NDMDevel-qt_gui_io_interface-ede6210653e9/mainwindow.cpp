#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QByteArray>
#include <QSerialPortInfo>
#include <cstdio>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //var init
    _an0_in_max     = ui->max_an0_in->text().toDouble();
    _an1_in_max     = ui->max_an1_in->text().toDouble();
    _an0_out_max    = ui->max_an0_out->text().toDouble();
    _an1_out_max    = ui->max_an1_out->text().toDouble();

    //plot init
    ui->plot->xAxis->setLabel("time [s]");
    _plot_size      = ui->plot_samples->text().toInt();

    on_refreshSerialPorts();

    //slider <-> spinbox an0
    connect_an0_slider_spin();

    //update scale factor an0/an1
    connect_max_an_out_changed();
    connect_max_an_in_changed();
    //auto send/read
    connect_autosend_an();


    //edit io's labels
    //  digital in
    connect_edit_io_labels();

    //checkbox digital out
    connect_checkbox_out();

    //write analog
    connect_send_an();
    //autosend out an
    connect_autoread();

    //plot sample update
    connect_plot_samples();

    //serial port
    connect_serial_port();

    //save menu
    connect_file_menu();

    //serial test
    connect(&_com,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),
            this,SLOT(on_serialError(QSerialPort::SerialPortError)));

}
MainWindow::~MainWindow()
{
    delete ui;
}
//SLOTS BEGIN
void MainWindow::slider_an0(int value)
{
    double slider_max = ui->slider_an0->maximum();
    double slider_val = double(value)/slider_max;
    update_spin_an0_out(value);
    if( ui->autosend_an0->isChecked() )
        send_serial_data(QString("write an0 ")+QString::number(slider_val*100.0));
}
void MainWindow::slider_an1(int value)
{
    double slider_max = ui->slider_an1->maximum();
    double slider_val = double(value)/slider_max;
    update_spin_an1_out(value);
    if( ui->autosend_an1->isChecked() )
        send_serial_data(QString("write an1 ")+QString::number(slider_val*100.0));
}
void MainWindow::spin_out_an0(double value)
{
    double spin_max = ui->spin_out_an0->maximum();
    double slider_max = ui->slider_an0->maximum();
    double slider_val = double(value)/spin_max*slider_max;
    ui->slider_an0->setValue(slider_val);
}
void MainWindow::spin_out_an1(double value)
{
    double spin_max = ui->spin_out_an1->maximum();
    double slider_max = ui->slider_an1->maximum();
    double slider_val = double(value)/spin_max*slider_max;
    ui->slider_an1->setValue(slider_val);
}
void MainWindow::update_progress_an0(int value)
{
    ui->bar_an0->setValue(value);
    ui->spin_in_an0->setValue(_an0_in_max * double(value)/100.0);
}
void MainWindow::update_progress_an1(int value)
{
    ui->bar_an1->setValue(value);
    ui->spin_in_an1->setValue(_an1_in_max * double(value)/100.0);
}
void MainWindow::autosend_an0_changed(int value)
{
    ui->send_an0->setEnabled(!value);
}
void MainWindow::autosend_an1_changed(int value)
{
    ui->send_an1->setEnabled(!value);
}
void MainWindow::btn_connect()
{
    if( !_com.isOpen() )
    {
        QString port  = ui->combo_port_list->currentText();//ui->port_address->text();
        if( port.contains(':') )
            port = port.left(port.indexOf(':'));
        uint32_t baud = ui->combo_baud->currentText().toUInt();
        _com.setPortName(port);
        _com.setBaudRate(baud);
        _com.setDataBits(QSerialPort::DataBits::Data8);
        _com.setStopBits(QSerialPort::StopBits::OneStop);
        _com.setParity(QSerialPort::Parity::NoParity);
        if( _com.open(QIODevice::ReadWrite) )
        {
            ui->port_connect->setText("Close");
            bool state = false;
            ui->combo_port_list->setEnabled(state);
            ui->combo_baud->setEnabled(state);
            ui->port_refresh->setEnabled(state);
            set_enable_analog_panel(true);
            set_enable_digital_panel(true);
            _serial_reopened = true;
            QMetaObject::invokeMethod(this,"on_confQuiet",Qt::ConnectionType::AutoConnection);
            QMetaObject::invokeMethod(this,"on_confAutoread",Qt::ConnectionType::AutoConnection);

        }
        else
            show_message("Error Serial Port","Error opening serial port (may be already in use)");
    }
    else
    {
        reset_and_close_serial_port();
        ui->port_connect->setText("Open");
        bool state = true;
        ui->combo_port_list->setEnabled(state);
        ui->combo_baud->setEnabled(state);
        ui->port_refresh->setEnabled(state);
        set_enable_analog_panel(false);
        set_enable_digital_panel(false);
    }
}
void MainWindow::on_rx()
{
    while( _com.canReadLine() )
    {
        auto array = _com.peek(_com.bytesAvailable());
        update_all_io(array);
        _com.readLine();
    }
}
void MainWindow::update_io_label()
{
    update_radiobutton_label(reinterpret_cast<QRadioButton*>(QObject::sender()));
}
void MainWindow::update_analog_label()
{
    auto target = reinterpret_cast<QLabel*>(QObject::sender());
    QString title = target->toolTip();
    auto label = QInputDialog::getText(this,"Edit label",target->toolTip()+" label:",QLineEdit::EchoMode::Normal,target->text());
    if( !label.isEmpty() )
        target->setText(label);
}
void MainWindow::on_updateAutoreadPeriod()
{
    QString str = "conf autoread ";
    str += QString::number(ui->autoread_period->value());
    send_serial_data(str,false);
}
void MainWindow::on_digitalOutputUpdate(bool value)
{
    auto radio_btn = reinterpret_cast<QRadioButton*>(QObject::sender());
    auto val = QString::number(value);
    if( radio_btn->toolTip() == "out0" )
        send_serial_data("write do0 " + val);
    if( radio_btn->toolTip() == "out1" )
        send_serial_data("write do1 " + val);
    if( radio_btn->toolTip() == "out2" )
        send_serial_data("write do2 " + val);
    if( radio_btn->toolTip() == "out3" )
        send_serial_data("write do3 " + val);
    if( radio_btn->toolTip() == "out4" )
        send_serial_data("write do4 " + val);
    if( radio_btn->toolTip() == "io_out0" )
        send_serial_data("write dio0 " + val);
    if( radio_btn->toolTip() == "io_out1" )
        send_serial_data("write dio1 " + val);
    if( radio_btn->toolTip() == "io_out2" )
        send_serial_data("write dio2 " + val);
    if( radio_btn->toolTip() == "io_out3" )
        send_serial_data("write dio3 " + val);
}
void MainWindow::write_an0()
{
    send_serial_data("write an0 " + QString::number(ui->slider_an0->value()));
}
void MainWindow::write_an1()
{
    send_serial_data("write an1 " + QString::number(ui->slider_an1->value()));
}
void MainWindow::on_sampleUpdate()
{
    bool ok;
    if( int val = ui->plot_samples->text().toInt(&ok); ok && val > 0 )
        _plot_size = val;
    else
    {
        ui->statusbar->showMessage("Invalid sample count",5000);
        ui->plot_samples->setText(QString::number(_plot_size));
    }
}
void MainWindow::on_maxAn0OutChanged()
{
    bool ok;
    double max = ui->max_an0_out->text().toDouble(&ok);

    if( ok && max >= 0.0 )
    {
        _an0_out_max = max;
        ui->autosend_an0->setChecked(false);
        ui->spin_out_an0->setMaximum(_an0_out_max);
        ui->slider_an0->setValue(0);
        send_serial_data(QString("write an0 0.0"));
    }
    else
    {
        show_message("Error","Max value not valid (keeping the previous one)");
        ui->max_an0_out->setText(QString::number(_an0_out_max));
    }
}
void MainWindow::on_maxAn1OutChanged()
{
    bool ok;
    double max = ui->max_an1_out->text().toDouble(&ok);
    if( ok && max >= 0.0 )
    {
        _an1_out_max = max;
        ui->autosend_an1->setChecked(false);
        ui->spin_out_an1->setMaximum(_an1_out_max);
        ui->slider_an1->setValue(0);
        send_serial_data(QString("write an1 0.0"));
    }
    else
    {
        show_message("Error","Max value not valid (keeping the previous one)");
        ui->max_an1_out->setText(QString::number(_an1_out_max));
    }
}
void MainWindow::on_maxAn0InChanged()
{
    bool ok;
    double max = ui->max_an0_in->text().toDouble(&ok);
    if( ok && max >= 0.0 )
    {
        _an0_in_max = max;
        ui->spin_in_an0->setMaximum(_an0_in_max);
        double value = double(ui->bar_an0->value())/100.0;
        ui->spin_in_an0->setValue(_an0_in_max * value);
    }
    else
    {
        show_message("Error","Max value not valid (keeping the previous one)");
        ui->max_an0_in->setText(QString::number(_an0_in_max));
    }
}
void MainWindow::on_maxAn1InChanged()
{
    bool ok;
    double max = ui->max_an1_in->text().toDouble(&ok);
    if( ok && max >= 0.0 )
    {
        _an1_in_max = max;
        ui->spin_in_an1->setMaximum(_an1_in_max);
        double value = double(ui->bar_an1->value())/100.0;
        ui->spin_in_an1->setValue(_an1_in_max * value);
    }
    else
    {
        show_message("Error","Max value not valid (keeping the previous one)");
        ui->max_an1_in->setText(QString::number(_an1_in_max));
    }
}
void MainWindow::on_refreshSerialPorts()
{
    ui->combo_port_list->clear();
    auto ports = QSerialPortInfo::availablePorts();
    for( auto port : ports )
    {
        if( ui->checkbox_only_usb->isChecked() )
        {
            if( port.description().contains("USB") )
                ui->combo_port_list->addItem(port.portName() + ": " + port.description());
        }
        else
            ui->combo_port_list->addItem(port.portName() + ": " + port.description());
    }
}
void MainWindow::on_serialError(QSerialPort::SerialPortError error)
{
    if( error == QSerialPort::SerialPortError::ResourceError )
    {
        //device disconnected:
        ui->port_connect->setText("Open");
        bool state = true;
        ui->combo_port_list->setEnabled(state);
        ui->combo_baud->setEnabled(state);
        ui->port_refresh->setEnabled(state);
        ui->analog_panel->setEnabled(false);
        set_enable_digital_panel(false);
        show_message("Error","Serial port disconnected.");
    }
}
void MainWindow::on_confQuiet()
{
    QString str = "conf quiet";
    str += QString::number(ui->autoread_period->value());
    send_serial_data(str,false);
}
void MainWindow::on_confAutoread()
{
    on_updateAutoreadPeriod();
}
void MainWindow::on_saveCsvRequested()
{
    auto filename = QFileDialog::getSaveFileName(this,
                       tr("Save as CSV"),
                       "./",
                       tr("CSV (*.csv)"));
    while( filename.contains('/') )
        filename = filename.replace('/',"\\\\");
    FILE* csv = fopen(filename.toUtf8(),"wb");
    fprintf(csv,"time[s],%s,%s\n",
            ui->label_in_an0->text().toStdString().c_str(),
            ui->label_in_an1->text().toStdString().c_str());
    for( int i=0 ; i<_plot_t.size() ; i++ )
        fprintf(csv,"%lf,%lf,%lf\n",_plot_t[i],_plot_an0[i],_plot_an1[i]);
    fclose(csv);
}
void MainWindow::on_exitRequested()
{
    close();
}
//SLOTS ENDS

//PRIVATE METHODS
void MainWindow::connect_an0_slider_spin()
{
    connect(ui->slider_an0,SIGNAL(valueChanged(int)),
            this,SLOT(slider_an0(int)));
    connect(ui->spin_out_an0,SIGNAL(valueChanged(double)),
            this,SLOT(spin_out_an0(double)));
    //slider <-> spinbox an1
    connect(ui->slider_an1,SIGNAL(valueChanged(int)),
            this,SLOT(slider_an1(int)));
    connect(ui->spin_out_an1,SIGNAL(valueChanged(double)),
            this,SLOT(spin_out_an1(double)));
}
void MainWindow::connect_max_an_out_changed()
{
    connect(ui->max_an0_out,SIGNAL(editingFinished()),
            this,SLOT(on_maxAn0OutChanged()));
    connect(ui->max_an1_out,SIGNAL(editingFinished()),
            this,SLOT(on_maxAn1OutChanged()));
}
void MainWindow::connect_max_an_in_changed()
{
    connect(ui->max_an0_in,SIGNAL(editingFinished()),
            this,SLOT(on_maxAn0InChanged()));
    connect(ui->max_an1_in,SIGNAL(editingFinished()),
            this,SLOT(on_maxAn1InChanged()));
}
void MainWindow::connect_autosend_an()
{
    connect(ui->autosend_an0,SIGNAL(stateChanged(int)),
            this,SLOT(autosend_an0_changed(int)));
    connect(ui->autosend_an1,SIGNAL(stateChanged(int)),
            this,SLOT(autosend_an1_changed(int)));
}
void MainWindow::connect_edit_io_labels()
{
    connect(ui->check_in0,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_in1,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_in2,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_in3,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_io_in0,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_io_in1,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_io_in2,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_io_in3,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    //  digital out
    connect(ui->check_out0,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_out1,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_out2,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_out3,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_out4,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_io_out0,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_io_out1,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_io_out2,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    connect(ui->check_io_out3,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_io_label()));
    //  analog in
    //ui->plot->yAxis->setLabel(ui->label_in_an0->text());
    connect(ui->label_in_an0,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_analog_label()));
    connect(ui->label_in_an1,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_analog_label()));
    connect(ui->label_in_an0,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_plot_an0_label()));
    connect(ui->label_in_an1,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_plot_an1_label()));
    connect(ui->label_out_an0,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_analog_label()));
    connect(ui->label_out_an1,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(update_analog_label()));
}
void MainWindow::connect_checkbox_out()
{
    connect(ui->check_out0,SIGNAL(clicked(bool)),
            this,SLOT(on_digitalOutputUpdate(bool)));
    connect(ui->check_out1,SIGNAL(clicked(bool)),
            this,SLOT(on_digitalOutputUpdate(bool)));
    connect(ui->check_out2,SIGNAL(clicked(bool)),
            this,SLOT(on_digitalOutputUpdate(bool)));
    connect(ui->check_out3,SIGNAL(clicked(bool)),
            this,SLOT(on_digitalOutputUpdate(bool)));
    connect(ui->check_out4,SIGNAL(clicked(bool)),
            this,SLOT(on_digitalOutputUpdate(bool)));
    connect(ui->check_io_out0,SIGNAL(clicked(bool)),
            this,SLOT(on_digitalOutputUpdate(bool)));
    connect(ui->check_io_out1,SIGNAL(clicked(bool)),
            this,SLOT(on_digitalOutputUpdate(bool)));
    connect(ui->check_io_out2,SIGNAL(clicked(bool)),
            this,SLOT(on_digitalOutputUpdate(bool)));
    connect(ui->check_io_out3,SIGNAL(clicked(bool)),
            this,SLOT(on_digitalOutputUpdate(bool)));
}
void MainWindow::connect_send_an()
{
    connect(ui->send_an0,SIGNAL(clicked()),
            this,SLOT(write_an0()));
    connect(ui->send_an1,SIGNAL(clicked()),
            this,SLOT(write_an1()));
}
void MainWindow::connect_autoread()
{
    connect(ui->btn_update_autoread_period,SIGNAL(clicked()),
            this,SLOT(on_updateAutoreadPeriod()));
    connect(ui->autoread_period,SIGNAL(editingFinished()),
            this,SLOT(on_updateAutoreadPeriod()));
}
void MainWindow::connect_serial_port()
{
    connect(ui->port_connect,SIGNAL(clicked()),
            this,SLOT(btn_connect()));
    connect(&_com,SIGNAL(readyRead()),
            this,SLOT(on_rx()));
    connect(ui->port_refresh,SIGNAL(clicked()),
            this,SLOT(on_refreshSerialPorts()));
    connect(ui->checkbox_only_usb,SIGNAL(stateChanged(int)),
            this,SLOT(on_refreshSerialPorts()));
}
void MainWindow::connect_plot_samples()
{
    connect(ui->btn_apply,SIGNAL(clicked()),
            this,SLOT(on_sampleUpdate()));
    connect(ui->plot_samples,SIGNAL(editingFinished()),
            this,SLOT(on_sampleUpdate()));
}
void MainWindow::connect_file_menu()
{
    connect(ui->actionSave_Image_as_CSV,SIGNAL(triggered(bool)),
            this,SLOT(on_saveCsvRequested()));
    connect(ui->actionExit,SIGNAL(triggered(bool)),
            this,SLOT(on_exitRequested()));
}

void MainWindow::update_spin_an0_out(int value)
{
    double spin_max   = ui->spin_out_an0->maximum();
    double slider_max = ui->slider_an0->maximum();
    double slider_val = double(value)/slider_max;
    ui->spin_out_an0->setValue(slider_val * spin_max);
}
void MainWindow::update_spin_an1_out(int value)
{
    double spin_max   = ui->spin_out_an1->maximum();
    double slider_max = ui->slider_an1->maximum();
    double slider_val = double(value)/slider_max;
    ui->spin_out_an1->setValue(slider_val * spin_max);
}
void MainWindow::set_enable_analog_panel(bool state)
{
    ui->analog_panel->setEnabled(state);
    ui->autoread_period->setEnabled(state);
    ui->btn_update_autoread_period->setEnabled(state);
}
void MainWindow::set_enable_digital_panel(bool state)
{
    ui->digital_panel->setEnabled(state);
    //in
    ui->check_in0->setEnabled(state);
    ui->check_in1->setEnabled(state);
    ui->check_in2->setEnabled(state);
    ui->check_in3->setEnabled(state);
    ui->check_io_in0->setEnabled(state);
    ui->check_io_in1->setEnabled(state);
    ui->check_io_in2->setEnabled(state);
    ui->check_io_in3->setEnabled(state);
    //out
    ui->check_out0->setEnabled(state);
    ui->check_out1->setEnabled(state);
    ui->check_out2->setEnabled(state);
    ui->check_out3->setEnabled(state);
    ui->check_out4->setEnabled(state);
    ui->check_io_out0->setEnabled(state);
    ui->check_io_out1->setEnabled(state);
    ui->check_io_out2->setEnabled(state);
    ui->check_io_out3->setEnabled(state);
}
void MainWindow::show_message(QString title, QString message)
{
    QMessageBox msg;
    msg.setWindowTitle(title);
    msg.setText(message);
    msg.exec();
}
void MainWindow::send_serial_reset(bool report_error)
{
    send_serial_data("reset",report_error);
}
void MainWindow::close_serial_port()
{
    while( _com.bytesToWrite() != 0 )
    {
        _com.flush();
        _com.waitForBytesWritten(1000);
    }
    _com.close();
}
void MainWindow::update_plot_an0_label()
{
    ui->label_plot_in_an0->setText(ui->label_in_an0->text());
    update_plot_gui();
}
void MainWindow::update_plot_an1_label()
{
    ui->label_plot_in_an1->setText(ui->label_in_an1->text());
    update_plot_gui();
}
void MainWindow::reset_and_close_serial_port()
{
    send_serial_reset(false);
    close_serial_port();
}
void MainWindow::update_radiobutton_label(QRadioButton *target)
{
    QString title = target->toolTip();
    auto label = QInputDialog::getText(this,"Edit label",target->toolTip()+" label:",QLineEdit::EchoMode::Normal,target->text());
    if( !label.isEmpty() )
        target->setText(label);
}
void MainWindow::send_serial_data(QString str,bool report_error)
{
    if( _com.isOpen() )
    {
        str += '\r';
        _com.write(str.toUtf8());
    }
    else
        if( report_error )
            show_message("Error","Serial port must be open");
}
void MainWindow::update_all_io(QByteArray array)
{
    uint32_t i=0;
    uint32_t space=0;
    for( ; i<array.size() ; i++ )
    {
        if( array[i] == ' ' )
            space = i;
        if( array[i] == '\n' )
            break;
    }
    QString data = array;
    auto tokens = data.split(' ',QString::SplitBehavior::SkipEmptyParts);
    double an0_value_in  = tokens[0].toDouble();
    double an1_value_in  = tokens[1].toDouble();
    double an0_value_out = tokens[2].toDouble();
    double an1_value_out = tokens[3].toDouble();
    update_progress_an0(int(an0_value_in));
    update_progress_an1(int(an1_value_in));
    if( _serial_reopened )
    {
        _serial_reopened = false;
        ui->spin_out_an0->blockSignals(true);
        ui->spin_out_an1->blockSignals(true);

        double spin_max   = ui->spin_out_an0->maximum();
        ui->spin_out_an0->setValue(an0_value_out/100.0 * spin_max);
        spin_max = ui->spin_out_an1->maximum();
        ui->spin_out_an1->setValue(an1_value_out/100.0 * spin_max);

        ui->spin_out_an0->blockSignals(false);
        ui->spin_out_an1->blockSignals(false);


        double slider_an0_max = ui->slider_an0->maximum();
        double slider_an1_max = ui->slider_an1->maximum();
        ui->slider_an0->blockSignals(true);
        ui->slider_an1->blockSignals(true);
        ui->slider_an0->setValue(int(an0_value_out*slider_an0_max/100.0));
        ui->slider_an1->setValue(int(an1_value_out*slider_an1_max/100.0));
        ui->slider_an0->blockSignals(false);
        ui->slider_an1->blockSignals(false);
    }
    static union
    {
        struct
        {
            uint8_t in0 : 1;
            uint8_t in1 : 1;
            uint8_t in2 : 1;
            uint8_t in3 : 1;
            uint8_t rsv : 3;
            uint8_t msb : 1;
        };
        uint8_t raw;
    }digital_in;
    static union
    {
        struct
        {
            uint8_t io_in0 : 1;
            uint8_t io_in1 : 1;
            uint8_t io_in2 : 1;
            uint8_t io_in3 : 1;
            uint8_t rsv : 3;
            uint8_t msb : 1;
        };
        uint8_t raw;
    }digital_io_in;
    static union
    {
        struct
        {
            uint8_t out0 : 1;
            uint8_t out1 : 1;
            uint8_t out2 : 1;
            uint8_t out3 : 1;
            uint8_t out4 : 1;
            uint8_t rsv  : 2;
            uint8_t msb  : 1;
        };
        uint8_t raw;
    }digital_out;
    static union
    {
        struct
        {
            uint8_t io_out0 : 1;
            uint8_t io_out1 : 1;
            uint8_t io_out2 : 1;
            uint8_t io_out3 : 1;
            uint8_t rsv : 3;
            uint8_t msb : 1;
        };
        uint8_t raw;
    }digital_io_out;
    digital_in.raw      = uint8_t(array[space+1]);
    digital_io_in.raw   = uint8_t(array[space+2]);
    digital_out.raw     = uint8_t(array[space+3]);
    digital_io_out.raw  = uint8_t(array[space+4]);

    //in checkbox
    ui->check_in0->setChecked(digital_in.in0);
    ui->check_in1->setChecked(digital_in.in1);
    ui->check_in2->setChecked(digital_in.in2);
    ui->check_in3->setChecked(digital_in.in3);
    ui->check_io_in0->setChecked(digital_io_in.io_in0);
    ui->check_io_in1->setChecked(digital_io_in.io_in1);
    ui->check_io_in2->setChecked(digital_io_in.io_in2);
    ui->check_io_in3->setChecked(digital_io_in.io_in3);

    //out checkbox
    ui->check_out0->setChecked(digital_out.out0);
    ui->check_out1->setChecked(digital_out.out1);
    ui->check_out2->setChecked(digital_out.out2);
    ui->check_out3->setChecked(digital_out.out3);
    ui->check_out4->setChecked(digital_out.out4);
    ui->check_io_out0->setChecked(digital_io_out.io_out0);
    ui->check_io_out1->setChecked(digital_io_out.io_out1);
    ui->check_io_out2->setChecked(digital_io_out.io_out2);
    ui->check_io_out3->setChecked(digital_io_out.io_out3);

    if( !ui->check_freeze_plot->isChecked() )
        update_plot(an0_value_in/100.0 * _an0_in_max ,an1_value_in/100.0 * _an1_in_max);
}
void MainWindow::update_plot(double new_an0,double new_an1)
{
    double time = double(ui->autoread_period->value())*0.001;    //0.001 converts to ms
    if( _plot_t.size() != _plot_size )
    {
        _plot_t.resize(_plot_size);
        _plot_an0.resize(_plot_size);
        _plot_an1.resize(_plot_size);
        for( int i=0 ; i<_plot_t.size() ; i++ )
        {
            _plot_t  [i] = double(i)*time;
            _plot_an0[i] = 0;
            _plot_an1[i] = 0;
        }
    }
    else
    {
        for( int i=0 ; i<_plot_t.size()-1 ; i++ )
        {
            _plot_t  [i] = _plot_t[i+1];
            _plot_an0[i] = _plot_an0[i+1];
            _plot_an1[i] = _plot_an1[i+1];
        }
        _plot_t  [_plot_t.size()-1] = _plot_t[_plot_t.size()-2]+time;
        _plot_an0[_plot_t.size()-1] = new_an0;
        _plot_an1[_plot_t.size()-1] = new_an1;
    }

    if( ui->plot->graphCount() == 0 )
    {
        ui->plot->yAxis2->setVisible(true);
        ui->plot->addGraph(ui->plot->xAxis,ui->plot->yAxis);
        ui->plot->addGraph(ui->plot->xAxis,ui->plot->yAxis2);
        ui->plot->setInteractions(QCP::iRangeDrag |
                                  QCP::iRangeZoom );
    }
    update_plot_gui();
}
void MainWindow::update_plot_gui()
{
    ui->plot->yAxis->setLabelColor(Qt::blue);
    ui->plot->yAxis->setLabel(ui->label_in_an0->text());
    ui->plot->graph(0)->setData(_plot_t,_plot_an0);
    ui->plot->graph(0)->setPen(QPen(Qt::blue));
    ui->plot->graph(0)->setName(ui->label_in_an0->text());
    ui->plot->yAxis2->setLabelColor(Qt::red);
    ui->plot->yAxis2->setLabel(ui->label_in_an1->text());
    ui->plot->graph(1)->setData(_plot_t,_plot_an1);
    ui->plot->graph(1)->setPen(QPen(Qt::red));
    ui->plot->graph(1)->setName(ui->label_in_an1->text());
    ui->plot->legend->setVisible(true);
    //ui->plot->rescaleAxes();
    const auto getRange = [&](const QVector<double>& an)->QCPRange
    {
        auto[min,ave,half,max] = plot_min_ave_half_max(an,_plot_t);
        double stable = 1.0 - std::abs(ave-half)/half;
        double delta  = max - min;
        double factor = stable<0.9?0.9:stable;
        double H = half + delta/factor;
        double L = half - delta/factor;
        return QCPRange(L,H);
    };
    if( ui->check_an0_autorange->isChecked() )
        ui->plot->yAxis->setRange(getRange(_plot_an0));
    else
        ui->plot->yAxis->setRange(0,_an0_in_max);
    if( ui->check_an1_autorange->isChecked() )
        ui->plot->yAxis2->setRange(getRange(_plot_an1));
    else
        ui->plot->yAxis2->setRange(0,_an1_in_max);
    ui->plot->xAxis->rescale();
    ui->plot->replot();
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    reset_and_close_serial_port();
}
std::tuple<double,double,double,double>
MainWindow::plot_min_ave_half_max(const QVector<double>& v,
                                  const QVector<double>& t)
{
    double min = v[0];
    double ave = (v[0]+v[1])/2.0 * (t[1]-t[0]);
    double max = v[0];
    for( int i=1 ; i<_plot_t.size() ; i++ )
    {
        ave += (v[i-1]+v[i])/2.0 * (t[i]-t[i-1]);
        max = std::max(max,v[i]);
        min = std::min(min,v[i]);
    }
    ave /= (t[t.size()-1]-t[0]);
    double half = (max+min)/2.0;
    return {min,ave,half,max};
}

