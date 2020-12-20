#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
class Arduino
{
public:
  Arduino();
  int connect_arduino();
  int close_arduino();
  int write_to_arduino(QByteArray b);
  QByteArray read_from_arduino();
  QSerialPort* getSerial();
private:
  QSerialPort *serial=new QSerialPort();
  static const quint16 arduino_uno_vendor_id=9025;
  static const quint16 arduino_uno_product_id=67;
  QString arduino_port_name;
  bool arduion_is_available;
  QByteArray data;
};

#endif // ARDUINO_H
