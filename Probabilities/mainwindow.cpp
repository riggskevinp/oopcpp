#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include <QGraphicsScene>

#include "probabilities.h"

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , A(0)
    , B(0)
{

    ui->setupUi(this);

    QStringList cBoxOptions = {"A and B", "A or B", "A xor B", "A and not B", "not A"};
    ui->comboBox->addItems(cBoxOptions);

    QPieSeries *series1 = new QPieSeries();
    series1->append("Probability of A",.5);
    series1->append("", .5);

    QChart *chart1 = new QChart();
    chart1->addSeries(series1);
    chart1->setTitle("Probability of A");
    chart1->legend()->hide();


    QChartView *chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView1,1,0);

    QPieSeries *series2 = new QPieSeries();
    series2->append("Probability of B",.5);
    series2->append("", .5);

    QChart *chart2 = new QChart();
    chart2->addSeries(series2);
    chart2->setTitle("Probability of B");
    chart2->legend()->hide();


    QChartView *chartView2 = new QChartView(chart2);
    chartView1->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView2,1,1);

    series3 = new QPieSeries();
    series3->append("",0.25);
    series3->append("", 0.75);

    chart3 = new QChart();
    chart3->addSeries(series3);
    chart3->setTitle("P(A ∩ B) = P(A) · P(B)");
    chart3->legend()->hide();


    QChartView *chartView3 = new QChartView(chart3);
    chartView3->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView3,1,2);

    connect(ui->doubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        [=](double d){
            series1->slices().at(0)->setValue(d);
            series1->slices().at(1)->setValue(1-d);
            updateProbabilities();
        });

    connect(ui->doubleSpinBox_2, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        [=](double d){
            series2->slices().at(0)->setValue(d);
            series2->slices().at(1)->setValue(1-d);
            updateProbabilities();
        });

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](){
            updateProbabilities();
        });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateProbabilities()
{
    A = ui->doubleSpinBox->value();
    B = ui->doubleSpinBox_2->value();

    switch(ui->comboBox->currentIndex()){
        case 0:{
            double val = A & B;
            series3->slices().at(0)->setValue(val);
            series3->slices().at(1)->setValue(1 - val);
            chart3->setTitle("P(A ∩ B) = P(A) · P(B)");
            break;
        }
            case 1:{
            double val = A | B;
            series3->slices().at(0)->setValue(val);
            series3->slices().at(1)->setValue(1 - val);
            chart3->setTitle("P(A ∪ B) = P(A) + P(B) - P(A∩B)");
        break;
        }
        case 2:{
            double val = A ^ B;
            series3->slices().at(0)->setValue(val);
            series3->slices().at(1)->setValue(1 - val);
            chart3->setTitle("P(A ⊕ B) = (A ∪ B) - P(A∩B)");
            break;
        }
        case 3:{
            double val = A - B;
            series3->slices().at(0)->setValue(val);
            series3->slices().at(1)->setValue(1 - val);
            chart3->setTitle("P(A ∩ !B) = P(A) · P(!B)");
            break;
        }
        case 4:{
            double val = ~A;
            series3->slices().at(0)->setValue(val);
            series3->slices().at(1)->setValue(1 - val);
            chart3->setTitle("P(!A) = 1 - P(A)");
            break;
        }
    }
}

