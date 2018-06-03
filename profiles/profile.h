#ifndef PROFILE_H
#define PROFILE_H


/**
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>
*/

#include <../../../../../usr/include/stdio.h>
#include <../../../../../usr/include/stdlib.h>
#include <../../../../../usr/include/ctype.h>
#include <../../../../../usr/include/math.h>
#include <../../../../../usr/include/errno.h>

#include <QWidget>
#include <QTabWidget>
#include <QComboBox>
#include <QJsonArray>
#include <QJsonParseError>

//#include "profiles/profiledialog.h"

#include "links/json_sintax.h"
#include "links/parson.h"
#include <string>

//---------- defs

#define PRFL_NAMES_NUMBER		10
#define PRFL_NAME_SIZE			128
#define PRFL_DESCRIPTION_SIZE	1024

//#define     profiles_file_name  "profiles.json"
//;	// Список профилей



typedef struct _prfl_StringArray_t prfl_StringArray;
typedef  struct _prfl_String_t	prfl_String;

struct _prfl_String_t{
    size_t isDefault;	// признак текущего профиля.
    size_t length;	// длина строки.
    char string[PRFL_NAME_SIZE];
};


struct _prfl_StringArray_t{
    size_t index;	// текущее количество элементов.
    size_t length;	// максимальное количество элементов.
    prfl_String data[PRFL_NAMES_NUMBER];	// указатель на буфер данных.

};

//-- var


//------------- function
class Profile
{
public:

    static Profile* instance() {
//        if(!_instance){
//            _instance = new Profile();
//        }
//        return _instance;
        static Profile p;
        return &p;
    }


    bool profileSaved;

    bool profileAtive;     // profile's data loaded from file.

    bool loadProfile();

    bool isProfileActive(){ return profileAtive; }


    /**
     * Создать переменные и загрузить файл Профилей.
     * Проверка наличия файла профиля и его правильность или
     * создать новый профиль профиль по-умолчанию.
     */
    bool init_profile();

    void Profiles_increment(int idx);

    QString getProfileName(int index);

    int getProfileNameCount() { return (profileNamesArray.count()); }

    QString getProfileDescription(int index);

    QString getProfileFileName(int index);

    bool isDefaultProfile(int index);

//----------- Generic
//----------------------- getters
    QString getX_STEPS();

    QString getY_STEPS();

    QString getZ_STEPS();

    QString getX_MAX_RATE();

    //DEFAULT_Y_MAX_RATE
    QString getY_MAX_RATE();

    //DEFAULT_Z_MAX_RATE
    QString getZ_MAX_RATE();

    //DEFAULT_X_ACCELERATION
    QString getX_ACCELERATION();

    //DEFAULT_Y_ACCELERATION
    QString getY_ACCELERATION();

    //DEFAULT_Z_ACCELERATION
    QString getZ_ACCELERATION();

    //DEFAULT_X_MAX_TRAVEL
    QString getX_MAX_TRAVEL();

    //DEFAULT_Y_MAX_TRAVEL
    QString getY_MAX_TRAVEL();

    //DEFAULT_Z_MAX_TRAVEL
    QString getZ_MAX_TRAVEL();

    //DEFAULT_STEP_PULSE_MICROSECONDS
    QString getSTEP_PULSE_MICROSECONDS();

    //DEFAULT_STEPPING_INVERT_MASK
    QString getSTEPPING_INVERT_MASK();

    //DEFAULT_DIRECTION_INVERT_MASK
    QString getDIRECTION_INVERT_MASK();

    //DEFAULT_STEPPER_IDLE_LOCK_TIME
    QString getSTEPPER_IDLE_LOCK_TIME();

    //DEFAULT_STATUS_REPORT_MASK
    QString getSTATUS_REPORT_MASK();

    //DEFAULT_JUNCTION_DEVIATION
    QString getJUNCTION_DEVIATION();

    //DEFAULT_ARC_TOLERANCE
    QString getARC_TOLERANCE();

    //DEFAULT_FLAGS
    QString getFLAGS();

    //DEFAULT_HOMING_DIR_MASK
    QString getHOMING_DIR_MASK();

    //DEFAULT_HOMING_FEED_RATE
    QString getHOMING_FEED_RATE();

    //DEFAULT_HOMING_SEEK_RATE
    QString getHOMING_SEEK_RATE();

    //DEFAULT_HOMING_DEBOUNCE_DELAY
    QString getHOMING_DEBOUNCE_DELAY();

    //DEFAULT_HOMING_PULLOFF
    QString getHOMING_PULLOFF();

    QString get_TEMPERATURE();

    QString get_INTEGRAL();

    QString get_PROPTIONAL();

    QString get_DERIVATIVE();

    //DEFAULT_E_MAX_RATE
    QString getE_MAX_RATE();

    //E_ACCELERATION
    QString getE_ACCELERATION();


//---------------------------------- setters
    //DEFAULT_X_STEPS_PER_MM
    void set_X_STEPS_PER_MM(QString num);

    //DEFAULT_Y_STEPS_PER_MM
    void setY_STEPS_PER_MM(QString num);

    //DEFAULT_Z_STEPS_PER_MM
    void setZ_STEPS_PER_MM(QString num);

    //DEFAULT_X_MAX_RATE
    void setX_MAX_RATE(QString num);

    //DEFAULT_Y_MAX_RATE
    void setY_MAX_RATE(QString num);

    //DEFAULT_Z_MAX_RATE
    void setZ_MAX_RATE(QString num);

    //DEFAULT_X_ACCELERATION
    void setX_ACCELERATION(QString num);

    //DEFAULT_Y_ACCELERATION
    void setY_ACCELERATION(QString num);

    //DEFAULT_Z_ACCELERATION
    void setZ_ACCELERATION(QString num);

    //DEFAULT_X_MAX_TRAVEL
    void setX_MAX_TRAVEL(QString num);

    //DEFAULT_Y_MAX_TRAVEL
    void setY_MAX_TRAVEL(QString num);

    //DEFAULT_Z_MAX_TRAVEL
    void setZ_MAX_TRAVEL(QString num);

    //DEFAULT_STEP_PULSE_MICROSECONDS
    void setSTEP_PULSE_MICROSECONDS(QString num);

    //DEFAULT_STEPPING_INVERT_MASK
    void setSTEPPING_INVERT_MASK(QString num);

    //DEFAULT_DIRECTION_INVERT_MASK
    void setDIRECTION_INVERT_MASK(QString num);

    //DEFAULT_STEPPER_IDLE_LOCK_TIME
    void setSTEPPER_IDLE_LOCK_TIME(QString num);

    //DEFAULT_STATUS_REPORT_MASK
    void setSTATUS_REPORT_MASK(QString num);

    //DEFAULT_JUNCTION_DEVIATION
    void setJUNCTION_DEVIATION(QString num);

    //DEFAULT_ARC_TOLERANCE
    void setARC_TOLERANCE(QString num);

    //DEFAULT_FLAGS
    void setFLAGS(QString num);

    //DEFAULT_HOMING_DIR_MASK
    void setHOMING_DIR_MASK(QString num);

    //DEFAULT_HOMING_FEED_RATE
    void setHOMING_FEED_RATE(QString num);

    //DEFAULT_HOMING_SEEK_RATE
    void setHOMING_SEEK_RATE(QString num);

    //DEFAULT_HOMING_DEBOUNCE_DELAY
    void setHOMING_DEBOUNCE_DELAY(QString num);

    //DEFAULT_HOMING_PULLOFF
    void setHOMING_PULLOFF(QString num);

    //DEFAULT_E_MAX_RATE
    void setE_MAX_RATE(QString num);

    //E_ACCELERATION
    void setE_ACCELERATION(QString num);

    void  set_TEMPERATURE(QString num);
    void  set_INTEGRAL(QString num);
    void  set_PROPTIONAL(QString num);
    void  set_DERIVATIVE(QString num);




    void saveProfileDocument();

private:

    QWidget *profPage;// pfofile page

    const char* pprofile_file_name;// = "profiles.json";	// Список профилей

    void _fill_prfl_names(JSON_Array* array);

    size_t prfl_add_element(prfl_StringArray* array, char* name,size_t isdefs);

    char*  _dotnamebuffer(const char *root, const char* name);

    QJsonDocument loadDocument(QString filename);

    QString readFile(const QString &filename);

    void writeObject(QJsonObject &json, QString key, QJsonObject newobj);

//--------- vars

    QJsonArray profileNamesArray;   // Список профилей

//    QComboBox *profiles;

    QString profile_filename;

    QJsonDocument profile_doc; // Документ текущего профиля.

    QJsonParseError parseError;


    int profileIndex;

    static Profile* _instance;

    Profile() {
        pprofile_file_name = "profiles.json";	// Список профилей
        profileSaved = true;
        profileIndex = 0;
        profileAtive = false;
    }

    ~Profile() {}
    Profile(Profile const&) = delete;
    void operator = (Profile const&) = delete;

};

#endif // PROFILE_H
