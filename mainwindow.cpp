#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
   QIcon deletes(":/Resources/minus.png");
   ui->DeleteEmployee->setIcon(deletes);

   ui->DeletePosts->setIcon(deletes);


   ui->DeleteEmployee->setIconSize(ui->DeleteEmployee->size());
   ui->DeletePosts->setIconSize(ui->DeletePosts->size());



   ui->Search_line->setPlaceholderText("Type Here");


   ui->CIN_Employee_text->setMaxLength(8);
   ui->CIN_Employee_text->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
   ui->Age_Employee_text->setMaxLength(3);
   ui->Age_Employee_text->setValidator(new QRegExpValidator(QRegExp("\\d*")));
   ui->Name_Employee_text->setValidator(new QRegExpValidator(QRegExp("(\\w|\\s)*")));
   ui->Address_Employee_text->setValidator(new QRegExpValidator(QRegExp("(\\w|\\b|\\s)*")));
   ui->Email_Employee_text->setValidator(new QRegExpValidator(QRegExp("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$")));
   ui->stackedWidget->setCurrentIndex(0);

   ui->ID_Posts_text->setValidator(new QRegExpValidator(QRegExp("(\\d)*")));

   ui->Salary_POsts_text->setValidator(new QRegExpValidator(QRegExp("(\\d)*")));
   ui->Benefits_Posts_text->setValidator(new QRegExpValidator(QRegExp("(\\d)*")));
   ui->Job_Posts_text->setValidator(new QRegExpValidator(QRegExp("(\\d|\\s|\\w)*")));
   ui->Hours_Posts_text_2->setValidator(new QRegExpValidator(QRegExp("(\\d)*")));

   db.setDatabaseName(QString("Source_Projet2A"));
     db.setUserName("Anas");
     db.setPassword("esprit20");
     if(!db.open()) {
       qDebug() << QString("Unable to open database");
       QMessageBox::warning(this, tr("MFactory"), tr("Unable to open database"), QMessageBox::Ok);
       }
     ui->tableView_2->setModel(em.display_Employee());
     ui->tableViewPost->setModel(po.display_Posts());
   if (ar.connect_arduino()==0)
     QMessageBox::warning(this, "Error", "Unable to connect to arduino");

   connect(ar.getSerial(), SIGNAL(readyRead()), this , SLOT(arduino_output()));

   ui->comboBox_2->setInsertPolicy(QComboBox::InsertAlphabetically);
   on_comboBox_2_activated();
   ui->tableViewPost->setContextMenuPolicy(Qt::CustomContextMenu);
     connect(ui->tableViewPost,SIGNAL(customContextMenuRequested(const QPoint &)),
             this,SLOT(ProvideContextMenu(const QPoint &)));
}

void MainWindow::animation_button(QPushButton *b)
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

void MainWindow::arduino_output()
{
  QByteArray b=ar.read_from_arduino();
   qDebug()<<b;
   if (b.toStdString()=="y")
     {
       //if (QMessageBox::question(this, "Warning", "fire in the factory has been detected \n"
         // "would you like to sound the alram",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){

          QSystemTrayIcon *n = new QSystemTrayIcon(this);
          QMenu *menu = new QMenu(this);
          menu->addAction("ok", this, SLOT(fire()));
          n->setContextMenu(menu);
          n->setVisible(true);
          n->setToolTip("Warning");
          //connect(act, SIGNAL(QAction::triggered()),this, ar.write_to_arduino(QByteArray::fromStdString("1")));
          n->show();
         // n->connect(act, SIGNAL(QAction::triggered()),this, ar.write_to_arduino(QByteArray::fromStdString("1")));
          n->showMessage("Fire", "there is a fire in the building", QSystemTrayIcon::Warning);
          ar.write_to_arduino(QByteArray::fromStdString("1"));


     }


}




MainWindow::~MainWindow()
{
  db.close();
  ar.close_arduino();
  delete ui;
}






void MainWindow::on_DeleteEmployee_clicked()
{
  QString cin=ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toString();

   if (QMessageBox::question(this, "Warning", "Are you sure you want to delete")==QMessageBox::Yes)
    em.remove_employee(cin);
 ui->tableView_2->setModel(em.display_Employee());
}

void MainWindow::display_Employee()
{
  //m->setQuery("Select * from Employees");
  //ui->tableView->setModel(m);
}

void MainWindow::on_AddEmployeeButton_clicked()
{



}






void MainWindow::on_UpdateEmployee_clicked()
{

}

void MainWindow::on_Search_line_editingFinished()
{
    QString s=ui->Search_line->text();
    if (s.isEmpty()) ui->tableViewPost->setModel(po.display_Posts());
    else
      {
        ui->tableViewPost->setModel(po.search(s));
      }
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
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

void MainWindow::on_tableView_2_activated(const QModelIndex &index)
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

void MainWindow::on_pushButton_clicked()
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




void MainWindow::on_comboBox_activated(int index)
{
    ui->tableView_2->setModel(em.sort_employees(index));

}

void MainWindow::on_DeletePosts_clicked()
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

void MainWindow::on_pushButton_3_clicked()
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

void MainWindow::on_tableViewPost_activated(const QModelIndex &index)
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

void MainWindow::on_pushButton_2_clicked()
{
    //QString to=ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),4).data().toString();


   // e.show();
    //e.exec();

}

void MainWindow::on_pushButton_4_clicked()
{
  sound->play();
  ui->ID_Posts_text->setText("");
  ui->Salary_POsts_text->setText("");
  ui->Benefits_Posts_text->setText("");
  ui->Job_Posts_text->setText("");
  ui->Hours_Posts_text_2->setText("");

}

void MainWindow::on_pushButton_5_clicked()
{
  sound->play();
  (ui->CIN_Employee_text->setText(""));
  ui->Name_Employee_text->setText("");
  ui->Age_Employee_text->setText("");
  ui->Address_Employee_text->setText("");
  (ui->Email_Employee_text->setText(""));
     ui->comboBox_2->setCurrentText("");
}



void MainWindow::on_actionLight_triggered()
{
  //QFile file("/Resources/light.qss");
  //file.open(QFile::Text|QFile::ReadOnly);
 // QTextStream txt(&file);
  this->setStyleSheet("");
  //file.close();
}

void MainWindow::on_actionDark_triggered()
{
  QFile file(":/new/prefix1/Resources/style1.qss");
  file.open(QFile::Text|QFile::ReadOnly);
  QTextStream txt(&file);
  this->setStyleSheet(txt.readAll());
  file.close();
}

void MainWindow::on_comboBox_2_activated(int index)
{
   QSqlQuery query;
    ui->comboBox_2->clear();
    query.prepare("Select id, job_desc from posts");
    if (query.exec())
    while(query.next())
      ui->comboBox_2->addItem(query.value(1).toString(), query.value(0).toUInt());

}




void MainWindow::on_pushButton_6_clicked()
{
  qDebug() << "dfghdghdh";
  QSqlQuery query;
  QString html="<div align=right>"
               "City, 11/11/2015"
            "</div>"
            "<div align=left>"
               "Sender Name<br>"
               "street 34/56A<br>"
               "121-43 city"
            "</div>"
               "<img src=""Resources\\logo.JPG"" align=left>"
            "<h1 align=center>Employees Table</h1>"
            "<p align=justify style=""color:blue""><br/><br/>"
               "<table style=""width:100%"">"
               "<tr>"
               "<th>       CIN       </th>"
               "<th>       Full Name </th>"
               "<th>       Age       </th>"
               "<th>       Address   </th>"
               "<th>       Email     </th>"
               "<th>       job       </th>"
               "</tr>";

  query.prepare("select * from employees;");
  query.exec();
  query.first();
  do {
      html+="<tr>";
      for(int i=0;i<6;i++)
      html+="<th>"+query.value(i).toString()+" "+"</th>";
      html+="</tr>";
    }while (!query.next());
  html+="</p>";

 QTextDocument doc;
  doc.setHtml(html);
  QPrinter printer(QPrinter::PrinterResolution);
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setPageSize(QPrinter::A4);
  QString filename=QFileDialog::getSaveFileName(this, "Save As");
  printer.setOutputFileName(filename+".pdf");
  printer.setPageMargins(QMarginsF(15, 15,15,15));
  doc.print(&printer);
}

void MainWindow::on_actionChoose_font_triggered()
{
    bool ok;
    QFont font(QFontDialog::getFont(&ok,this));
    if (ok){
        QApplication::setFont(font);
      }
}



void MainWindow::on_pushButton_7_clicked()
{
  QTranslator *t = new QTranslator;
  t->load(":/french.qm");
  //QApplication::instance()->removeTranslator(&mtranslator);
  //QApplication::instance()->installTranslator(&t);
  //QCoreApplication::installTranslator(t);
  qApp->installTranslator(t);
  ui->retranslateUi(this);
}

MainWindow::ProvideContextMenu( const QPoint &pos)
{
  QPoint globalPos = ui->tableViewPost->mapToGlobal(pos);
     // for QAbstractScrollArea and derived classes you would use:
     // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

     QMenu myMenu;
     myMenu.addAction(tr("Average"),this, SLOT(avgPosts()));
     myMenu.addAction(tr("sum"),this, SLOT(sumPosts()));
     myMenu.addSeparator();
     myMenu.addAction(tr("Delete"),this, SLOT(on_DeletePosts_clicked()));
     // ...

     myMenu.exec(globalPos);

}

void MainWindow::avgPosts()
{
  //if (ui->tableViewPost->iss)
    {
      QSqlQuery q;
      q.prepare("select avg(salary), avg(benefits), avg(hours_worked) from posts;");
      q.exec();
      q.first();
      QMessageBox::information(this, tr("Avg"),tr("Salary avg: %1\n"
                                                  "Benefits avg: %2\n"
                                                  "Hours Worked avg: %3\n")
                               .arg(q.value(0).toFloat())
                               .arg(q.value(1).toFloat())
                               .arg(q.value(2).toFloat()));
      }
}

void MainWindow::sumPosts()
{
  QSqlQuery q;
  q.prepare("select sum(salary), sum(benefits), sum(hours_worked) from posts;");
  q.exec();
  q.first();
  QMessageBox::information(this, tr("Sum"),tr("Salary Sum: %1\n"
                                              "Benefits Sum: %2\n"
                                              "Hours Worked Sum: %3\n")
                           .arg(q.value(0).toFloat())
                           .arg(q.value(1).toFloat())
                           .arg(q.value(2).toFloat()));

}



void MainWindow::on_actionFalse_Alarm_triggered()
{
    ar.write_to_arduino(QByteArray::fromStdString("2"));
}

void MainWindow::on_HR_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionReturn_to_main_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}
