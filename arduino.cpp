#include "arduino.h"

Arduino::Arduino()
{
  arduion_is_available=false;

}

int Arduino::connect_arduino()
{
  foreach(const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
      if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
          if (serial_port_info.vendorIdentifier()==arduino_uno_vendor_id &&
              serial_port_info.productIdentifier()==arduino_uno_product_id){
              arduion_is_available=true;
              arduino_port_name=serial_port_info.portName();
            }
        }
    }
  qDebug() << "arduino port name :" << arduino_port_name;
  if (arduion_is_available){
      serial->setPortName(arduino_port_name);
      if (serial->open(QSerialPort::ReadWrite)){
          serial->setBaudRate(QSerialPort::Baud9600);
          serial->setDataBits(QSerialPort::Data8);
          serial->setParity(QSerialPort::NoParity);
          serial->setStopBits(QSerialPort::OneStop);
          serial->setFlowControl(QSerialPort::NoFlowControl);
          return 1;
        }
    }
  return 0;
}

int Arduino::close_arduino()
{
  if (serial->isOpen()){
      serial->close();
      return 0;
    }
  return 1;
}

int Arduino::write_to_arduino(QByteArray b)
{
  if (serial->isWritable())
    serial->write(b);
  else
    qDebug() << "couldn't write to arduino\n";
  return 0;
}

QByteArray Arduino::read_from_arduino()
{
  if (serial->isReadable())
    data=serial->readAll();
  return data;
}

QSerialPort *Arduino::getSerial()
{
  return serial;
}

