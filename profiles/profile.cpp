#include "profile.h"


#include <QFile>
#include <QTextStream>

#include <QDebug>
#include <QJsonObject>

#include <QList>
#include <QComboBox>

#define PROFILE_BUFFER_SiZE	1024


//#define PROFILE_PATH    ":/profile/"
#define PROFILE_PATH    "profile/"



//------------- vars

static const char* profiles_file_name = "profiles.json";	// Список профилей

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
    pprofile_file_name = profiles_file_name;	// Список профилей


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


QString
Profile::readFile(const QString &filename)
{
    QString str = PROFILE_PATH + filename;

    QFile f(str);

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


QJsonDocument
Profile::loadDocument(QString filename)
{
    QJsonDocument doc;
//    QJsonParseError error ;

    QString str = readFile(filename);

    if (str.isEmpty())
        qFatal("Could not read JSON file!");
    QByteArray arr = str.toUtf8();

    doc = QJsonDocument::fromJson(arr,&parseError);

    return doc;
}

// Загрузка списка профилей из файла
bool
Profile::loadProfile()
{

//    QString path = PROFILE_PATH+QString("profiles.json");

    QString json1 = readFile("profiles.json");

//  QTextStream in(&loadFile);
//  QString json = in.readAll();//loadFile.readAll();

  if (json1.isEmpty())
      qFatal("Could not read JSON file!");

//  QJsonObject a = QtJson::parse(json, ok).toMap();
  QByteArray arr1 = json1.toUtf8();

  QJsonParseError error ;

  QJsonDocument loadDoc = QJsonDocument::fromJson(arr1,&error);

   QJsonObject obj;
   QJsonArray list;

  if(loadDoc.isObject())
      obj = loadDoc.object();

  qDebug() << "189 Debug info: count" << obj.count();

  if(loadDoc.isEmpty())
  {
      qDebug() << "Empty \n";
  }

  profileNamesArray = obj["profiles"].toArray();

  if(list.count()>0){
      qDebug() << "211 List count:" << profileNamesArray.count();
  }


  for(int i=0;i<list.count();i++)
  {
      QJsonObject prof = profileNamesArray[i].toObject()["profile"].toObject();

      qDebug() << prof["name"].toString() << "212"; // QJsonValue(string, "Profile1")

      QString str = prof["name"].toString();
//      profiles->addItem(str);
  }
}

QString
Profile::getProfileName(int index)
{

    QJsonObject prof = profileNamesArray[index].toObject()["profile"].toObject();

     QString str = prof["name"].toString();

    return str;
}

QString
Profile::getProfileDescription(int index)
{
    QString str;

    QJsonObject prof = profileNamesArray[index].toObject()["profile"].toObject();

    str = prof["description"].toString();

    return str;
}

QString
Profile::getProfileFileName(int index)
{
    QString str;

    QJsonObject prof = profileNamesArray[index].toObject()["profile"].toObject();

    str =  prof["file"].toString();

    return str;
}

bool
Profile::isDefaultProfile(int index)
{
    bool check;

    QString str;

    QJsonObject prof = profileNamesArray[index].toObject()["profile"].toObject();

    str =  prof["default"].toString();

    if(str == "true"){
        check = true;
    }else{
        check = false;
    }

    return check;
}

//----------------- Profile document


#define GENERIC_GET_VALUE(gen,field) obj = profile_doc.object();\
    generic_obj = obj[gen].toObject();\
    result = generic_obj[field].toString()


// DEFAULT_X_STEPS_PER_MM"
QString
Profile::getX_STEPS()
{

    QString result;

    QJsonObject obj;
    QJsonObject generic_obj;

//    profile_doc
//    obj = profile_doc.object();
//    generic_obj = obj["generic"].toObject();
//    result = generic_obj["DEFAULT_X_STEPS_PER_MM"].toString();


    GENERIC_GET_VALUE("generic","DEFAULT_X_STEPS_PER_MM");

//    qDebug() << generic_obj.count() << "getX_STEPS 290";
//    qDebug() << result << "getX_STEPS 294";

    return result;
}

//DEFAULT_Y_STEPS_PER_MM
QString
Profile::getY_STEPS()
{
    QString result;

    QJsonObject obj;
    QJsonObject generic_obj;

    GENERIC_GET_VALUE("generic","DEFAULT_Y_STEPS_PER_MM");

    return result;
}

//DEFAULT_Z_STEPS_PER_MM
QString
Profile::getZ_STEPS()
{
    QString result;

    QJsonObject obj;
    QJsonObject generic_obj;

    GENERIC_GET_VALUE("generic","DEFAULT_Z_STEPS_PER_MM");

    return result;
}

//DEFAULT_X_MAX_RATE
QString
Profile::getX_MAX_RATE()
{
    QString result;

    QJsonObject obj;
    QJsonObject generic_obj;

    GENERIC_GET_VALUE("generic","DEFAULT_X_MAX_RATE");

    return result;
}

//DEFAULT_Y_MAX_RATE

//DEFAULT_Z_MAX_RATE

//DEFAULT_X_ACCELERATION

//DEFAULT_Y_ACCELERATION

//DEFAULT_Z_ACCELERATION

//DEFAULT_X_MAX_TRAVEL

//DEFAULT_Y_MAX_TRAVEL

//DEFAULT_Z_MAX_TRAVEL

//DEFAULT_STEP_PULSE_MICROSECONDS

//DEFAULT_STEPPING_INVERT_MASK

//DEFAULT_DIRECTION_INVERT_MASK

//DEFAULT_STEPPER_IDLE_LOCK_TIME

//DEFAULT_STATUS_REPORT_MASK

//DEFAULT_JUNCTION_DEVIATION

//DEFAULT_ARC_TOLERANCE

//DEFAULT_FLAGS

//DEFAULT_HOMING_DIR_MASK

//DEFAULT_HOMING_FEED_RATE

//DEFAULT_HOMING_SEEK_RATE

//DEFAULT_HOMING_DEBOUNCE_DELAY

//DEFAULT_HOMING_PULLOFF

//TEMPERATURE
QString
Profile::get_TEMPERATURE()
{
    QString result;

    QJsonObject obj;
    QJsonObject generic_obj;

    GENERIC_GET_VALUE("generic","TEMPERATURE");

    return result;
}


//PROPTIONAL
QString
Profile::get_PROPTIONAL()
{
    QString result;

    QJsonObject obj;
    QJsonObject generic_obj;

    GENERIC_GET_VALUE("generic","PROPTIONAL");

    return result;
}


//INTEGRAL
QString
Profile::get_INTEGRAL()
{
    QString result;

    QJsonObject obj;
    QJsonObject generic_obj;

    GENERIC_GET_VALUE("generic","INTEGRAL");

    return result;
}

//DERIVATIVE
QString
Profile::get_DERIVATIVE()
{
    QString result;

    QJsonObject obj;
    QJsonObject generic_obj;

    GENERIC_GET_VALUE("generic","DERIVATIVE");

    return result;
}

//-----------------

void
Profile::Profiles_increment(int idx)
{
    int id;

    id = idx + 1;
//    ReadTables(idx + 1);

    qDebug() << idx << "Profile::on_profileComboBox_currentIndexChanged 205";

}


/**
 * Создать переменные и загрузить файл Профилей.
 * Проверка наличия файла профиля и его правильность или
 * создать новый профиль профиль по-умолчанию.
 */
bool
Profile::init_profile()
{
    bool result = false;


    quint8 i;

    if(loadProfile())
    {

        profile_filename = getProfileFileName(0); // TODO Найти профиль по-умолчанию.
        profile_doc = loadDocument(profile_filename);
        qDebug() << parseError.errorString() << "init_profile:302";

        if(profile_doc.isEmpty())
        {
            qDebug() << "Empty init_profile 335 \n";
        }


//       QString str = getX_STEPS();

        result = true;

        i = 1;
    }

    return result;
}
