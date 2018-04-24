#include "profile.h"


#include <QFile>
#include <QTextStream>
#include <QJsonParseError>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>



#define PROFILE_BUFFER_SiZE	1024





//------------- vars

static const char* profile_file_name = "profiles.json";	// Список профилей

static JSON_Array *root_array;
static JSON_Value *root_value;
static JSON_Object *root_object;


const char* templ_root_path = "profiles";
const char* templ_field_profile = "profile";
const char* templ_name = "name";
const char* templ_description = "description";
const char* templ_file = "file";
const char* templ_default = "default";

const char* filename_extention = "json";

static char buffer[PROFILE_BUFFER_SiZE];


static prfl_StringArray _pprfl_names;// = {0,PRFL_NAMES_NUMBER,{{0,{"as"}},{0,{"sds"}},{0,{"sdsa"}},{0,{"sdsa"}},{0,{"sdsa"}},{0,{"sdsa"}}
                                     //,{0,{"sdsa"}},{0,{"sdsa"}},{0,{"sdsa"}},{0,{"sdsa"}}}};


prfl_StringArray * prfl_names = &_pprfl_names;


//------------------- functions

Profile::Profile()
{
    pprofile_file_name = profile_file_name;	// Список профилей


    _pprfl_names.index = 0;
    _pprfl_names.length = 10;
    _pprfl_names.data[0].isDefault = false;
}


// формирование строки пути к значению JSON-объекта.



char*
Profile::_dotnamebuffer(const char *root, const char* name){
/*    strcpy(buffer,root);
    strcat(buffer,dot);
    strcat(buffer,name);*/
    return buffer;
}


size_t
Profile::prfl_add_element(prfl_StringArray* array, char* name,size_t isdefs)
{
    size_t result = 0;
    size_t length = strlen(name);

    if((array->index<array->length)
            &&(length<PRFL_NAME_SIZE)){
        result = 1;
        strcpy(array->data[array->index].string,name);
        array->data[array->index].length = length;
        array->data[array->index].isDefault = isdefs;
        array->index++;
    }
    return (result);
}


/**
 * load prfl_names
 */
void
Profile::_fill_prfl_names(JSON_Array* array)
{
    size_t i, isdef;

    char* name;
//	char buffer[128];

    char* str_isdef;

    JSON_Object *object;
/*
    for(i=0;i<json_array_get_count(array);i++){

        object = json_array_get_object(array, i);

        name = (char*)json_object_dotget_string(object,_dotnamebuffer(templ_field_profile,templ_name));

        str_isdef = (char*)json_object_dotget_string(object,_dotnamebuffer(templ_field_profile,templ_default));
        if(strcmp(templ_false,str_isdef)==0){
            isdef = false;
        }else {
            isdef = true;
        }
        prfl_add_element(prfl_names, name, isdef);
    }
*/
}



QString readFile(const QString &filename) {
    QFile f(filename);
    if(f.exists()){
        if (!f.open(QFile::ReadOnly | QFile::Text)) {
            return QString();
        } else {
            QTextStream in(&f);
            return in.readAll();
        }
    }

    return QString();
}


// Загрузка профиля из файла
bool
Profile::loadProfile()
{
/*    root_value = json_parse_file_with_comments(pprofile_file_name);

    root_object = json_value_get_object(root_value);

    root_array = json_object_get_array(root_object,templ_root_path);

//	_check_root_value();

    //---------- load prfl_names
    _fill_prfl_names(root_array);

    return (root_value==NULL?0:1);
*/
//  QFile loadFile(QString("profile/profiles.json"));
//  if(!loadFile.open(QIODevice::ReadOnly)){
//      qWarning("Couldn't open save file.");
//      return false;
//  }

    QString json1 = readFile(":/profile/profiles.json");

//  QTextStream in(&loadFile);

//  QString json = in.readAll();//loadFile.readAll();

  if (json1.isEmpty())
      qFatal("Could not read JSON file!");


//  QJsonObject a = QtJson::parse(json, ok).toMap();
  QByteArray arr1 = json1.toUtf8();

  QJsonParseError error ;

  QJsonDocument loadDoc = QJsonDocument::fromJson(arr1,&error);

   QJsonObject obj;
  if(loadDoc.isObject())
      obj = loadDoc.object();

int i = obj.count();

  qDebug() << "Debug info: count" << obj.count();


//  read(loadDoc.object());

  if(loadDoc.isEmpty())
  {
      qDebug() << "Empty \n";
  }

/*
   QJsonArray dataObject = obj["profiles"].toArray();
   QJsonArray::iterator it;
   for (it = obj.begin(); it != obj.end(); it++) {
       QString key = it->first;
       QString value = it->second;
       qDebug() << key;
   }
*/
  for(QJsonObject::Iterator iter = obj.begin();iter!=obj.end();  ++iter)
      {
//          ui->plainTextEdit->appendPlainText(iter.key());
        QString key = iter.key();
        QString value = iter.value().toString();
          qDebug() << key;
      }


}


/**
 * Создать переменные и загрузить файл Профилей.
 * Проверка наличия файла профиля и его правильность или
 * создать новый профиль профиль по-умолчанию.
 */
void
Profile::init_profile(void)
{
    quint8 i;

    if(loadProfile())
    {
        i = 1;
    }else{
        i = 1;
    }

}
