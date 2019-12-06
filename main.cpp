#include <QCoreApplication>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString inPath = "E:\\toothpick\\program\\mff\\build-mff-Desktop_Qt_5_13_0_MinGW_32_bit-Debug\\debug\\MaficDefinition_regionbox_2.mff";
    QFile fileIn( inPath);
    fileIn.open( QFile::ReadOnly|QFile::Text);
    QTextStream fileInQTS( &fileIn);

    QString outPath = "E:\\toothpick\\program\\mff\\build-mff-Desktop_Qt_5_13_0_MinGW_32_bit-Debug\\debug\\MaficDefinition_regionbox_2_1.mff";
    QFile fileOut( outPath);
    fileOut.open( QFile::WriteOnly|QFile::Text);
    QTextStream fileOutQTS( &fileOut);
    QStringList in, oneLine, initiative, passive;
    while (!fileInQTS.atEnd())
        in.append(fileInQTS.readLine());

    int row;

    for (int i=0; i<in.count()-3; i++)
    {
        oneLine = (in[i].simplified().split(" "));
        if (oneLine[0] == "FracElem")
            row = i;
    }
    for (int i=row+1; i<in.count()-3; i++)
    {
        initiative = (in[i].simplified().split(" "));
        for (int j=i+1; j<in.count(); j++)
        {
            passive = (in[j].simplified().split(" "));
            if (initiative[1] == passive[1] &&
                    initiative[2] == passive[2] &&
                    initiative[3] == passive[3])
            {
                qDebug()<<initiative;
                qDebug()<<passive;
                in.removeAt(j);
                j--;
            }
        }
    }

    for (int i=0; i<=row; i++)
    {
        fileOutQTS << in[i] << endl;
    }
    int k=1;
    for (int i=row+1; i<in.count()-3; i++)
    {
        oneLine = (in[i].simplified().split(" "));
        oneLine[0].setNum(k);
        for (int j=0; j<oneLine.count(); j++)
        {
            fileOutQTS << '\t' << oneLine[j];
        }
        fileOutQTS << endl;
        k++;
    }
    for (int i=in.count()-3; i<in.count(); i++)
    {
        fileOutQTS << in[i] << endl;
    }


    return a.exec();
}
