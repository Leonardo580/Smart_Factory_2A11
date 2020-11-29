#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addemployee.h"
#include "search.h"
#include <QLabel>
#include <QList>
#include <QLayout>
#include <QPushButton>
#include "addemployee.h"
#include "email.h"
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


  db.setDatabaseName(QString("Source_Projet2A"));
  db.setUserName("Anas");
  db.setPassword("esprit20");
  if(!db.open()) {
    qDebug() << QString("Unable to open database");
    QMessageBox::warning(this, tr("MFactory"), tr("Unable to open database"), QMessageBox::Ok);
    }
  else {
  ui->label_7->setText("Status: Connected");
    }
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
  ui->CIN_Posts_text->setValidator(new QRegExpValidator(QRegExp("(\\d)*")));
  ui->CIN_Posts_text->setMaxLength(8);
  ui->Salary_POsts_text->setValidator(new QRegExpValidator(QRegExp("(\\d)*")));
  ui->Benefits_Posts_text->setValidator(new QRegExpValidator(QRegExp("(\\d)*")));
  ui->Job_Posts_text->setValidator(new QRegExpValidator(QRegExp("(\\d|\\s|\\w)*")));
  ui->Hours_Posts_text_2->setValidator(new QRegExpValidator(QRegExp("(\\d)*")));


}

void MainWindow::animation_button(QPushButton *b)
{
  int a=-20;
    {
      QPropertyAnimation *p = new QPropertyAnimation(b, "geometry");
      p->setDuration(500);
      p->setStartValue(b->geometry());
      // a*=-1;
      p->setEndValue(QRect(b->geometry().x()-a, b->geometry().y(), b->width(), b->height()));
      p->setLoopCount(3);
      p->start();
      p->deleteLater();

    }

}




MainWindow::~MainWindow()
{
  db.close();
  delete ui;
}





void MainWindow::on_search_clicked()
{
  Search s;
  s.exec();
}




void MainWindow::on_DeleteEmployee_clicked()
{
  QString cin=ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0).data().toString();
  if (QMessageBox::warning(this, "Warning", "Are you sure you want to delete", QMessageBox::Ok|QMessageBox::Cancel)==0)
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
  query.prepare("select Age from Employees;");
  QVector<int> v;
  if(query.exec()){
      while(query.next()){
      v.push_back(query.value(0).toInt());
        }
  int twenty=0, thirty=0, forty=0;
  for (QVector<int>::const_iterator it=v.begin(); it!=v.end();it++){
      if (*it>=40) forty++;
      else if (*it>=30) thirty++;
      else twenty++;
    }
  int all=twenty+thirty+forty;
  qDebug()  << float(twenty/all)*100 << " " << (thirty/all)*100 << " "<< (forty/all)*100 << "\n";
  series->append("Above 20", (qreal)((qreal)twenty/(qreal)all)*100.0);
  series->append("Above 30",(qreal)((qreal)thirty/(qreal)all)*100);
  series->append("Above 40",(qreal)((qreal)forty/(qreal)all)*100);
  //for (int i=0;i<3;i++)
    {
      QPieSlice *s=series->slices().at(0);
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
  ch->setTitle(QString("Age"));
  ch->legend()->show();
  ch->setAnimationOptions(QChart::AllAnimations);
  ch->setTheme(QChart::ChartThemeDark);
  QChartView *chart=new QChartView(ch);
  chart->setRenderHint(QPainter::Antialiasing);
  chart->setGeometry(ui->tab_2->geometry());
  chart->setBackgroundBrush(QBrush(QColor(0x202020)));
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
  QRegExp regex("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$");
  regex.setPatternSyntax(QRegExp::RegExp);
  bool areEmpty=e.getAddress().isEmpty() || e.getEmail().isEmpty() || e.getCin().isEmpty() || e.getCin().size()<8;
  if (areEmpty || !regex.exactMatch(e.getEmail()) || e.getAge()>=100){
      animation_button(ui->pushButton);

    }
  else if (!ui->tableView_2->currentIndex().isValid()){
      (ui->CIN_Employee_text->setText(""));
      ui->Name_Employee_text->setText("");
      ui->Age_Employee_text->setText("");
      ui->Address_Employee_text->setText("");
      (ui->Email_Employee_text->setText(""));

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
  int id=ui->tableViewPost->model()->index(ui->tableView_2->currentIndex().row(),0).data().toInt();
  if (QMessageBox::warning(this, "Warning", "Are you sure you want to delete", QMessageBox::Ok|QMessageBox::Cancel)==0)
    po.remove_Posts(id);
 ui->tableView_2->setModel(em.display_Employee());
}

void MainWindow::on_pushButton_3_clicked()
{
  Posts p;
  sound->play();
  p.setid(ui->ID_Posts_text->text().toInt());
  p.setCIN(ui->CIN_Posts_text->text());
  p.setSalary(ui->Salary_POsts_text->text().toDouble());
  p.setBenefits(ui->Benefits_Posts_text->text().toDouble());
  p.setJob_Desc(ui->Job_Posts_text->text());
  p.setHours_Worked(ui->Hours_Posts_text_2->text().toDouble());
  bool areEmpty=p.getid()<0 || p.getCIN()=="";
  if (areEmpty){
      animation_button(ui->pushButton_3);

    }
  else if (!ui->tableViewPost->currentIndex().isValid()){
     ui->ID_Posts_text->setText("");
     ui->CIN_Posts_text->setText("");
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
}

void MainWindow::on_tableViewPost_activated(const QModelIndex &index)
{
    QString data[6];
    for (int i=0;i<6;i++)
      data[i]=ui->tableViewPost->model()->index(ui->tableViewPost->currentIndex().row(),i).data().toString();
    ui->ID_Posts_text->setText(data[0]);
    ui->CIN_Posts_text->setText(data[1]);
    ui->Salary_POsts_text->setText(data[2]);
    ui->Benefits_Posts_text->setText(data[3]);
    ui->Hours_Posts_text_2->setText(data[4]);
    ui->Job_Posts_text->setText(data[5]);
    qDebug()<< index;

}

void MainWindow::on_pushButton_2_clicked()
{
    QString to=ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),4).data().toString();
    qDebug() << to;
    Email e("smtp.gmail.com",465, "anas.benbrahim@esprit.tn","191JMT4743", to, this);
    e.show();
    e.exec();
}
