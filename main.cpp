#include "webserviceclient.h"
#include <QApplication>
#include <QSettings>

extern void MySleep(unsigned int msec);

QString g_sFilePath = "";
QString g_sMinTime,g_sMaxTime = "";

void MyGetAuxParam()
{
	// 获取记录文件路径
	QSettings *configIniRead = new QSettings("Config.ini", QSettings::IniFormat); 
	//将读取到的ini文件保存在QString中，先取值  
	g_sFilePath = configIniRead->value("/Config/FilePath").toString();  
	g_sMinTime = configIniRead->value("/Config/MinimumTime").toString();
	g_sMaxTime = configIniRead->value("/Config/MaximumTime").toString();
	return;
}

bool isDirExist(QString fullPath)
{
	QDir dir(fullPath);
	QFileInfoList fileList;
	QFileInfo curFile;
	if(dir.exists())
	{
		fileList=dir.entryInfoList(QDir::Dirs|QDir::Files|QDir::Readable|QDir::Writable|QDir::Hidden|QDir::NoDotAndDotDot,QDir::Name);
		while(fileList.size()>0)
		{
			int infoNum=fileList.size();
			for(int i=infoNum-1;i>=0;i--)
			{
				curFile=fileList[i];
				if(curFile.isFile())//如果是文件，删除文件
				{
					QFile fileTemp(curFile.filePath());
					fileTemp.remove();
					fileList.removeAt(i);
				}
				if(curFile.isDir())//如果是文件夹
				{
					QDir dirTemp(curFile.filePath());
					QFileInfoList fileList1=dirTemp.entryInfoList(QDir::Dirs|QDir::Files|QDir::Readable|QDir::Writable|QDir::Hidden|QDir::NoDotAndDotDot,QDir::Name);
					if(fileList1.size()==0)//下层没有文件或文件夹
					{
						dirTemp.rmdir(".");
						fileList.removeAt(i);
					}
					else//下层有文件夹或文件
					{
						for(int j=0;j<fileList1.size();j++)
						{
							if(!(fileList.contains(fileList1[j])))
								fileList.append(fileList1[j]);
						}
					}
				}
			}
		}
		return true;
	}
	else
	{
		bool ok = dir.mkpath(fullPath);//创建多级目录
		return ok;
	}
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	MyGetAuxParam();
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);
	isDirExist(g_sFilePath);
    WebServiceClient w;
    w.show();
	MySleep(1000);
	w.AutoReq();
    return a.exec();
}
