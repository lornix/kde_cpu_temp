// cpu-temperature applet for KDE

#include <QGraphicsLinearLayout>
#include <QTimer>

#include <plasma/applet.h>
#include <plasma/theme.h>
#include <plasma/widgets/label.h>

const char* temppath="/sys/class/thermal/thermal_zone%d/temp";
const int numcpus=2;

const int LIMIT_YELLOW=79;
const int LIMIT_RED=94;

const char* GREEN="green";
const char* YELLOW="yellow";
const char* RED="red";

class cpu_temp : public Plasma::Applet
{
    Q_OBJECT
 public:
        cpu_temp(QObject* parent,const QVariantList &args);
        ~cpu_temp();
        void init();
 private:
        Plasma::Label* label;
        QTimer* timer;
        QGraphicsLinearLayout* layout;
 private slots:
        void updateLabel();
};

    cpu_temp::cpu_temp(QObject* parent,const QVariantList &args)
: Plasma::Applet(parent,args)
{
    setBackgroundHints(DefaultBackground);
    resize(60,30);
}
cpu_temp::~cpu_temp()
{
    if (hasFailedToLaunch()) {
        // do cleanup here
    } else {
        QObject::disconnect(timer,SIGNAL(timeout()));
        // save settings
    }
}
void cpu_temp::init()
{
    layout=new QGraphicsLinearLayout(this);
    layout->setOrientation(Qt::Horizontal);
    label=new Plasma::Label(this);
    label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    label->setText("Init<br>Init");
    layout->addItem(label);
    timer=new QTimer();
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),SLOT(updateLabel()));
    timer->start(1000);
}
void cpu_temp::updateLabel()
{
#define BUFSIZE 200
    static char buf[BUFSIZE];
    long int temp0=-1;
    long int temp1=-1;
    const char* color0;
    const char* color1;
    snprintf(buf,BUFSIZE,temppath,0);
    FILE* fp=fopen(buf,"r");
    if (fp) {
        fgets(buf,BUFSIZE,fp);
        temp0=strtol(buf,NULL,0)/1000;
        fclose(fp);
    }
    snprintf(buf,BUFSIZE,temppath,1);
    fp=fopen(buf,"r");
    if (fp) {
        fgets(buf,BUFSIZE,fp);
        temp1=strtol(buf,NULL,0)/1000;
        fclose(fp);
    }
    color0=GREEN;
    if ((temp0>LIMIT_RED)||(temp0<0)) {
        color0=RED;
    } else if (temp0>LIMIT_YELLOW) {
        color0=YELLOW;
    }
    color1=GREEN;
    if ((temp1>LIMIT_RED)||(temp1<0)) {
        color1=RED;
    } else if (temp1>LIMIT_YELLOW) {
        color1=YELLOW;
    }
    snprintf(buf,BUFSIZE,"<b><font color=\"%s\">%ld&deg;</font></b><br>"
                         "<b><font color=\"%s\">%ld&deg;</font></b>",
                        color0,temp0,
                        color1,temp1);

    label->setText(buf);
}

K_EXPORT_PLASMA_APPLET(cputemp,cpu_temp)

#include "cpu_temp.moc"
