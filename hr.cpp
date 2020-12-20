#include "hr.h"
#include "ui_hr.h"
#include <QLabel>
#include <QList>
#include <QLayout>
#include <QPushButton>
#include "email.h"
HR::HR(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::HR)
{
  ui->setupUi(this);

    QIcon deletes(":/Resources/minus.png");
    ui->DeleteEmployee->setIcon(deletes);

    ui->DeletePosts->setIcon(deletes);


    ui->DeleteEmployee->setIconSize(ui->DeleteEmployee->size());
    ui->DeletePosts->setIconSize(ui->DeletePosts->size());



    ui->tableView_2->setModel(em.display_Employee());
    ui->tableViewPost->setModel(po.display_Posts());

    ui->Search_line->setPlaceholderText("Type Here");

    ui->CIN_Employee_text->setMaxLength(8);
    ui->CIN_Employee_text->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
    ui->Age_Employee_text->setMaxLength(3);
    ui->Age_Employee_text->setValidator(new QRegExpValidator(QRegExp("\\d*")));
    ui->Name_Employee_text->setValidator(new QRegExpValidator(QRegExp("(\\w|\\s)*")));
    ui->Address_Employee_text->setValidator(new QRegExpValidator(QRegExp("(\\w|\\b|\\s)*")));
    ui->Email_Employee_text->setValidator(new QRegExpValidator(QRegExp("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$")));




    ui->ID_Posts_text->setValidator(new QRegExpValidator(QRegExp("(\\d)*")));

    ui->Salary_POsts_text->setValidator(new QRegExpValidator(QRegExp("(\\d)*")));
    ui->Benefits_Posts_text->setValidator(new QRegExpValidator(QRegExp("(\\d)*")));
    ui->Job_Posts_text->setValidator(new QRegExpValidator(QRegExp("(\\d|\\s|\\w)*")));
    ui->Hours_Posts_text_2->setValidator(new QRegExpValidator(QRegExp("(\\d)*")));

    if (ar.connect_arduino()==0)
      QMessageBox::warning(this, "Error", "Unable to connect to arduino");

    connect(ar.getSerial(), SIGNAL(readyRead()), this , SLOT(arduino_output()));

    ui->comboBox_2->setInsertPolicy(QComboBox::InsertAlphabetically);
    on_comboBox_2_activated();
}

HR::~HR()
{
  delete ui;
}
void HR::animation_button(QPushButton *b)
{
  int a=20;
  QRect location=b->geometry();
    {
      QPropertyAnimation *p = new QPropertyAnimation(b, "geometry");
      p->setDuration(1000);
      //p->setStartValue(QRect(b->geometry().x()+a, b->geometry().y(), b->width(), b->height()));
     // p->setEndValue(QRect(b->geometry().x()-a, b->geometry().y(), b->width(), b->height()));
      p->setKeyValueAt(0, location);
      p->setKeyValueAt(0.25, QRect(b->geometry().x()+a, b->geometry().y(), b->width(), b->height()));
      p->setKeyValueAt(0.5, QRect(location.x()-a, b->geometry().y(), b->width(), b->height()));
      p->setKeyValueAt(0.75, QRect(location.x()+a, b->geometry().y(), b->width(), b->height()));
      p->setKeyValueAt(1, location);
      p->start();
      //b->setGeometry(location);
    }

}

void HR::arduino_output()
{
  QByteArray b=ar.read_from_arduino();
  qDebug() << b;
  if (b.toStdString()=="yes")
    {
      if (QMessageBox::question(this, "Warning", "fire in the factory has been detected \n"
                                "would you like to sound the alram",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
        ar.write_to_arduino(QByteArray::fromStdString("1"));
      }
    }

}









void HR::on_DeleteEmployee_clicked()
{
  QString cin=ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toString();

   if (QMessageBox::question(this, "Warning", "Are you sure you want to delete")==QMessageBox::Yes)
    em.remove_employee(cin);
 ui->tableView_2->setModel(em.display_Employee());
}

void HR::display_Employee()
{
  //m->setQuery("Select * from Employees");
  //ui->tableView->setModel(m);
}

void HR::on_AddEmployeeButton_clicked()
{



}






void HR::on_UpdateEmployee_clicked()
{

}

void HR::on_Search_line_editingFinished()
{
    QString s=ui->Search_line->text();
    if (s.isEmpty()) ui->tableViewPost->setModel(po.display_Posts());
    else
      {
        ui->tableViewPost->setModel(po.search(s));
      }
}

void HR::on_tabWidget_tabBarClicked(int index)
{
  if (index!=3) return;
  QPieSeries *series= new QPieSeries();
  QSqlQuery query;
  query.prepare("select id ,Hours_worked from Posts;");
  QVector<int> v;
  QVector<QString> vectcin, vectname;
  if(query.exec()){
      while(query.next()){
      vectcin.push_back(query.value(0).toString());
      v.push_back(query.value(1).toInt());
        }
  for (QVector<QString>::iterator it=vectcin.begin(); it!=vectcin.end();it++){
      QSqlQuery query2;
      query2.prepare("Select Full_Name from Employees where (CIN=:cin);");
      query2.bindValue(":cin", QVariant(*it));
      query2.exec();
      query2.first();
      vectname.push_back(query2.value(0).toString());
    }

   int sum=0;
   for (int i=0;i<v.size();i++) sum+=v[i];
   int m=0,pos;
   for (int i=0;i<vectname.size();i++){
  series->append(vectname[i], (qreal)((qreal)v[i]/(qreal)sum)*100.0);
  if (m<v[i]){
    m=v[i];
    pos=i;
    }
     }
  //for (int i=0;i<3;i++)
    {
      QPieSlice *s=series->slices().at(pos);
      //if (s->event(new QEvent(QEvent::MouseButtonPress)))
        {
          s->setLabelVisible();
          s->setExploded();
          s->setPen(QPen(Qt::darkBlue,2));
        }
      //else
      {
         // s->setExploded(false);
        }
    }
  QChart *ch= new QChart();
  ch->addSeries(series);
  ch->setTitle(QString("Employee of the month"));
  ch->legend()->show();
  ch->setAnimationOptions(QChart::AllAnimations);
  ch->setTheme(QChart::ChartThemeDark);
  QChartView *chart=new QChartView(ch);
  chart->setRenderHint(QPainter::Antialiasing);
  chart->setFont(QFont("Times",20,QFont::Bold));
  chart->setGeometry(ui->tab_2->geometry());
  QGridLayout q;
  q.addWidget(chart);
  this->ui->tab_2->setLayout(&q);
    }
  else
    QMessageBox::warning(this,"Error","Unable to fetch values from the DataBase", QMessageBox::Ok);
}

void HR::on_tableView_2_activated(const QModelIndex &index)
{

    QString cin=ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toString();
    QString name=ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),1).data().toString();
    QString age=ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),2).data().toString();
    QString address=ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),3).data().toString();
    QString email=ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),4).data().toString();
    QString id=ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),5).data().toString();

    ui->CIN_Employee_text->setText(cin);
    ui->Name_Employee_text->setText(name);
    ui->Age_Employee_text->setText(age);
    ui->Address_Employee_text->setText(address);
    ui->Email_Employee_text->setText(email);
}

void HR::on_pushButton_clicked()
{
  Employees e;
  sound->play();
  e.setCin(ui->CIN_Employee_text->text());
  e.setFull_Name(ui->Name_Employee_text->text());
  e.setAge(ui->Age_Employee_text->text().toUInt());
  e.setAddress(ui->Address_Employee_text->text());
  e.setEmail(ui->Email_Employee_text->text());
  e.setId(ui->comboBox_2->currentData().toUInt());
  QRegExp regex("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$");
  regex.setPatternSyntax(QRegExp::RegExp);
  bool areEmpty=e.getAddress().isEmpty() || e.getEmail().isEmpty() || e.getCin().isEmpty() || e.getCin().size()<8;
  if (areEmpty || !regex.exactMatch(e.getEmail()) ||e.getAge()>=100 ){
      animation_button(ui->pushButton);

    }
  else if (!em.search_Employee(e.getCin())){
      (ui->CIN_Employee_text->setText(""));
      ui->Name_Employee_text->setText("");
      ui->Age_Employee_text->setText("");
      ui->Address_Employee_text->setText("");
      (ui->Email_Employee_text->setText(""));
      ui->comboBox_2->setCurrentText("");

      if (!e.add_employee())
        QMessageBox::warning(this, "Error", "An Unknown error", QMessageBox::Ok);
    }
  else {
      if (!e.update_employee())
        QMessageBox::warning(this, "Error", "An Unknown error", QMessageBox::Ok);
    }

  ui->tableView_2->setModel(em.display_Employee());
}




void HR::on_comboBox_activated(int index)
{
    ui->tableView_2->setModel(em.sort_employees(index));

}

void HR::on_DeletePosts_clicked()
{
  QString tmp=ui->tableViewPost->model()->index(ui->tableViewPost->currentIndex().row(),0).data().toString();
  if (tmp.isEmpty()) return;
  int id=tmp.toInt();
  QSqlQuery q;
  q.prepare("select * from employees where (id=?);");
  q.addBindValue(QVariant(tmp));
  q.exec();
  q.first();
  if (q.value(0).toString()!="") {
      QMessageBox::warning(this, "warning", "this row has foreign key tied to it");
      return;
    }
  if (QMessageBox::question(this, "Warning", "Are you sure you want to delete ?")==QMessageBox::Yes)
    po.remove_Posts(id);
 ui->tableViewPost->setModel(po.display_Posts());
 on_comboBox_2_activated();
}

void HR::on_pushButton_3_clicked()
{
  Posts p;
  sound->play();
  p.setid(ui->ID_Posts_text->text().toInt());
  p.setSalary(ui->Salary_POsts_text->text().toDouble());
  p.setBenefits(ui->Benefits_Posts_text->text().toDouble());
  p.setJob_Desc(ui->Job_Posts_text->text());
  p.setHours_Worked(ui->Hours_Posts_text_2->text().toDouble());
  bool areEmpty=p.getid()<0 ;
  if (areEmpty ){
      animation_button(ui->pushButton_3);
    }
  else if (!po.search_post(p.getid())){
     ui->ID_Posts_text->setText("");

     ui->Salary_POsts_text->setText("");
     ui->Benefits_Posts_text->setText("");
     ui->Job_Posts_text->setText("");
     ui->Hours_Posts_text_2->setText("");

      if (!p.add_Posts())
        QMessageBox::warning(this, "Error", "An Unknown error", QMessageBox::Ok);
    }
  else {
      if (!p.update_Posts())
        QMessageBox::warning(this, "Error", "An Unknown error", QMessageBox::Ok);
    }

  ui->tableViewPost->setModel(po.display_Posts());
  on_comboBox_2_activated();

}

void HR::on_tableViewPost_activated(const QModelIndex &index)
{
    QString data[5];
    for (int i=0;i<5;i++)
      data[i]=ui->tableViewPost->model()->index(ui->tableViewPost->currentIndex().row(),i).data().toString();
    ui->ID_Posts_text->setText(data[0]);

    ui->Job_Posts_text->setText(data[1]);
    ui->Salary_POsts_text->setText(data[2]);
    ui->Benefits_Posts_text->setText(data[3]);
    ui->Hours_Posts_text_2->setText(data[4]);

}

void HR::on_pushButton_2_clicked()
{
    QString to=ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),4).data().toString();


   // e.show();
    //e.exec();

}

void HR::on_pushButton_4_clicked()
{
  sound->play();
  ui->ID_Posts_text->setText("");
  ui->Salary_POsts_text->setText("");
  ui->Benefits_Posts_text->setText("");
  ui->Job_Posts_text->setText("");
  ui->Hours_Posts_text_2->setText("");

}

void HR::on_pushButton_5_clicked()
{
  sound->play();
  (ui->CIN_Employee_text->setText(""));
  ui->Name_Employee_text->setText("");
  ui->Age_Employee_text->setText("");
  ui->Address_Employee_text->setText("");
  (ui->Email_Employee_text->setText(""));
     ui->comboBox_2->setCurrentText("");
}



void HR::on_actionLight_triggered()
{
  QFile file("://Resources/aqua.qss");
  file.open(QFile::Text|QFile::ReadOnly);
  QTextStream txt(&file);
  this->setStyleSheet(txt.readAll());
}

void HR::on_actionDark_triggered()
{
  QFile file("C:\\Users\\Anas\\OneDrive\\Workload\\Project 2\\Smart Factory\\MFactory\\Style1.qss");
  file.open(QFile::Text|QFile::ReadOnly);
  QTextStream txt(&file);
  this->setStyleSheet(txt.readAll());
}

void HR::on_comboBox_2_activated(int index)
{
   QSqlQuery query;
    ui->comboBox_2->clear();
    query.prepare("Select id, job_desc from posts");
    if (query.exec())
    while(query.next())
      ui->comboBox_2->addItem(query.value(1).toString(), query.value(0).toUInt());
}
