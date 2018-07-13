/*
 *
 *
*/




#include "usbexchange.h"

//uint rIndex;

//------------- defs
#define MaxPacketSize	64

#define DEBUG_M_NO

#define STDFILE

//------------- vars
static const char* fname = "/dev/cnccontrol";

const struct sControl default_block = {
   X_AXIS, 2, 0, 3, 10, 3, 7,  50132, 5370, 50132, 0, {1, 2, 3}, forward, 0, 0
};

static const struct sHead default_segment_head = {
   N_AXIS, (X_FLAG|Y_FLAG|Z_FLAG|E_FLAG), 0xFFFF, 1
};



//--------- functions

/**
 * @brief UsbExchange::sendRequest
 * @param request
 * @return
 */
int
UsbExchange::sendRequest(ComDataReq_t* request)
{
    quint8* rdata = (quint8*)request;
    int result, size, length;
#ifndef STDFILE
    QString line;
    QTextStream print(stdout, QIODevice::WriteOnly); // stdin
#endif
#ifdef STDFILE
    std::FILE* pFile;

    pFile = std::fopen(fname,"r+");
    if (pFile!=NULL)
    {
        //  fputs ("fopen example",pFile);
//        line = QString("File opened. %1 \n").arg(fname);
//        print<<line<<"sendRequest 48";
#ifdef DEBUG_M
        qDebug() << "File opened :"<< fname << "sendRequest 48";
#endif
        if(sendBuffer(rdata,sizeof(ComDataReq_t),pFile) ==  EXIT_SUCCESS)
        {
            size = sizeof(struct Status_t);
            length = fread(buffer2,1,size,pFile);

            if(length < 0){
#ifdef DEBUG_M
                qDebug()<< "Can't read file %1 \n" << fname ;
#endif
            }else{

                //printf("Recieved:%u\n",result);
#ifdef DEBUG_M
                qDebug() << "Recieved :" << length;
#endif
                c_status = (struct Status_t*)buffer2;
#ifdef DEBUG_M
                print_status(c_status);
#endif
            }

        }
        result = EXIT_SUCCESS;
        fclose (pFile);
    }else{
        //        printf("Can't open device. maybe module not loaded. Use: $sudo insmod ./eclipse-workspace/usbtest/test1.ko \n"
        //               "or device dosn't connected.\n");
        result = EXIT_FAILURE;
//        qDebug() << "Can't open device. maybe module not loaded. \n \t Use: $sudo insmod ./eclipse-workspace/usbtest/test1.ko \n \t or device dosn't connected.";

//        QMessageBox msgbox;
//        msgbox.setText("Can't open device. maybe module not loaded. Use: $sudo insmod ./eclipse-workspace/usbtest/test1.ko \n \t or device dosn't connected.");
//        msgbox.exec();

    }

#else

    QFile data(fname);



    if(data.open(QIODevice::WriteOnly))
    {
        //         result = sendBuffer(rdata,sizeof(ComDataReq_t),&data);
        if(sendBuffer(rdata,sizeof(ComDataReq_t),&data) ==  EXIT_SUCCESS)
        {
            data.close();

            if(data.open(QIODevice::ReadOnly))
            {
                size = sizeof(struct Status_t);

                length = data.read(buffer2,size);

                if(length < 0){
                    line = QString("Can't read file %1 \n").arg(fname);
                }else{
                    //printf("Recieved:%u\n",result);
                    line = QString("Recieved %1 \n").arg(length);

                    c_status = (struct Status_t*)buffer2;

                    print_status(c_status);
                }
            }
         }

         data.close();
    }else{
        result = EXIT_FAILURE;
    }
#endif
    return result;
}

// Формирование запросов в конструкторе.
#define EXCHANGE_IN_CONST_NO
#define SINGLETON_NO

#ifndef SINGLETON

/**
 * @brief UsbExchange::UsbExchange
 */
//ThermoPlot::ThermoPlot(QObject* parent) : QObject(parent)
UsbExchange::UsbExchange(QObject *parent) : QObject(parent)
{
#ifdef    EXCHANGE_IN_CONST
#ifdef STDFILE
    buildComData(&comdata);
    sendRequest(&comdata);
#else
    int length, size;

    QTextStream print(stdout, QIODevice::WriteOnly); // stdin
    QString line;

    line = "File opened.\n";
    QFile data(fname);
//    fp = fopen(fname, "r+");

    //    if(fp!=NULL){
    if( data.open(QIODevice::ReadWrite) )
    {

        print << line;

        print.flush();

        buildComData(&comdata);

        if(sendBuffer((uint8_t*)&comdata,sizeof(comdata),&data) == EXIT_SUCCESS)
        {
            //------------------------------------- readStatus
            size = sizeof(struct Status_t);

            length = data.read(buffer2,size);
            if(length < 0){
                line = QString("Can't read file %1 \n").arg(fname);
            }else{
                //printf("Recieved:%u\n",result);
                line = QString("Recieved %1 \n").arg(length);
                print <<line; print.flush();
                c_status = (struct Status_t*)buffer2;

                print_status(c_status);


            }
        }
        //        fclose(fp);
        data.close();
    }else{
//        printf("Can't open device. maybe module not loaded. Use: $sudo insmod ./eclipse-workspace/usbtest/test1.ko \n"
//               "or device dosn't connected.\n");
        line = QString("Can't open device. maybe module not loaded. Use: $sudo insmod ./eclipse-workspace/usbtest/test1.ko \n device dosn't connected.\n");
        print << line; print.flush();


        //        return EXIT_FAILURE;
    }
#endif
#endif
}
#endif

/**
 * @brief UsbExchange::print_status
 * @param c_status
 */
void
UsbExchange::print_status(Status_t * c_status)
{

    QString line;
    QTextStream print(stdout, QIODevice::WriteOnly); // stdin

//    printf("frameNumber: %u \n",c_status->frameNumber);
//	printf("freeSegments: %u \n",c_status->freeSegments);
//	printf("coordinatus X: %u \n",c_status->coordinatus[X_AXIS]);
//	printf("coordinatus Y: %u \n",c_status->coordinatus[Y_AXIS]);
//	printf("coordinatus Z: %u \n",c_status->coordinatus[Z_AXIS]);
//	printf("coordinatus E: %u \n",c_status->coordinatus[E_AXIS]);
//	printf("modelState: %u \n",c_status->modelState);
//	printf("currentSegmentNumber: %u \n",c_status->currentSegmentNumber);
//	printf("instrument2_parameter: %u \n",c_status->instrument2_parameter);
//	printf("instrument3_parameter: %u \n",c_status->instrument3_parameter);
//	printf("instrument4_parameter: %u \n",c_status->instrument4_parameter);
//	printf(" ======================= \n");

    line = QString("frameNumber: %1 \n").arg(c_status->frameNumber); print <<line; print.flush();
    line = QString("freeSegments: %1 \n").arg(c_status->freeSegments);print <<line; print.flush();
    line = QString("coordinatus X: %1 \n").arg(c_status->coordinatus[X_AXIS]);print <<line; print.flush();
    line = QString("coordinatus Y: %1 \n").arg(c_status->coordinatus[Y_AXIS]);print <<line; print.flush();
    line = QString("coordinatus Z: %1 \n").arg(c_status->coordinatus[Z_AXIS]);print <<line; print.flush();
    line = QString("coordinatus E: %1 \n").arg(c_status->coordinatus[E_AXIS]);print <<line; print.flush();
    line = QString("modelState: %1 \n").arg(c_status->modelState.modelState);print <<line; print.flush();
    line = QString("currentSegmentNumber: %1 \n").arg(c_status->currentSegmentNumber);print <<line; print.flush();
    line = QString("instrument2_parameter: %1 \n").arg(c_status->instrument2_parameter);print <<line; print.flush();
    line = QString("instrument3_parameter: %1 \n").arg(c_status->instrument3_parameter);print <<line; print.flush();
    line = QString("instrument4_parameter: %1 \n").arg(c_status->instrument4_parameter);print <<line; print.flush();
    line = QString("Temperaature: %1 \n").arg(c_status->temperature);print <<line; print.flush();
    line = QString(" ======================= \n");print <<line; print.flush();

}


/**
 * @brief UsbExchange::load_defaults
 * @param pctl
 */
void
UsbExchange::load_defaults(struct sControl* pctl)
{
    pctl->steps = default_block.steps;
    pctl->microsteps = default_block.microsteps;
    pctl->accelerate_until = default_block.accelerate_until;
    pctl->decelerate_after = default_block.decelerate_after;
    pctl->initial_rate = default_block.initial_rate;
    pctl->initial_speedLevel = default_block.initial_speedLevel;
    pctl->nominal_rate = default_block.nominal_rate;
    pctl->speedLevel = default_block.speedLevel;
    pctl->final_rate = default_block.final_rate;
    pctl->final_speedLevel = default_block.final_speedLevel;
    pctl->schem[0] = default_block.schem[0];
    pctl->schem[1] = default_block.schem[1];
    pctl->schem[2] = default_block.schem[2];
    pctl->direction = default_block.direction;
}

/**
 * @brief UsbExchange::build_segment_default
 * @param psc
 * @param i
 */
void
UsbExchange::build_segment_default(struct sSegment* psc, uint32_t i)
{
    uint32_t j;

    struct sControl* pctl;

    psc->head.axis_number = default_segment_head.axis_number; //N_AXIS;
    psc->head.linenumber = i + default_segment_head.linenumber;
    psc->head.axis_mask = default_segment_head.axis_mask;
    for(j=0;j<psc->head.axis_number;j++)
    {
        pctl = &psc->axis[j];
        switch(j){
        case 0:
            load_defaults(pctl);
            pctl->axis = X_AXIS;
            break;
        case 1:
            load_defaults(pctl);
            pctl->axis = Y_AXIS;
            break;
        case 2:
            load_defaults(pctl);
            pctl->axis = Z_AXIS;
            break;
        case 3:
            load_defaults(pctl);
            pctl->axis = E_AXIS;
            break;
        }
    }
}

/**
 * @brief UsbExchange::sendBuffer
 * @param buffer
 * @param size
 * @param fp
 * @return
 */
int
UsbExchange::sendBuffer(uint8_t* buffer, uint32_t size, std::FILE* fp)
{
    uint8_t* cursor = buffer;
    uint32_t packet_size, counter = 0;
    qint64 length=0;

    packet_size = MaxPacketSize;
#ifdef DEBUG_M
    qDebug() << "Write packet #1 of size:" << MaxPacketSize;
#endif
    length = fwrite(cursor,sizeof(char),MaxPacketSize,fp);// #1 packet

    if(length < 0){
        qDebug() << "Error Writing to " << fname;
        return (EXIT_FAILURE);
    }
#ifdef DEBUG_M
    qDebug() << "Sended:"<<length<< "\t to be send: "<< size-counter;
#endif
    counter += length;
    cursor += length;
#ifdef DEBUG_M
    qDebug() << "Write packet #2 of size:" << MaxPacketSize;
#endif
    length = fwrite(cursor,sizeof(char),MaxPacketSize,fp);// #2 packet

    if(length < 0){
        qDebug() << "Error Writing to " << fname;
        return (EXIT_FAILURE);
    }
#ifdef DEBUG_M
    qDebug() << "Sended:"<<length<< "\t to be send: "<< size-counter;
#endif
    counter += length;
    cursor += length;

    packet_size = sizeof(comdata) - counter;
#ifdef DEBUG_M
    qDebug() << "Write packet #2 of size:" << packet_size;
#endif
    length = fwrite(cursor,sizeof(char),packet_size,fp);// #3 packet

    if(length < 0){
        qDebug() << "Error Writing to " << fname;
        return (EXIT_FAILURE);
    }
#ifdef DEBUG_M
    qDebug() << "Sended:"<<length<< "\t to be send: "<< size-counter;
#endif

    return (EXIT_SUCCESS);
}

// TODO sendBuffer
/**
 * @brief UsbExchange::sendBuffer
 * @param buffer
 * @param size
 * @param fp
 * @return
 */
int
UsbExchange::sendBuffer(uint8_t* buffer, uint32_t size, QFile* fp)
{
    uint8_t* cursor = buffer;
    uint32_t packet_size, counter = 0;
    qint64 length=0;

    packet_size = MaxPacketSize;

    QString line;


//    length = fwrite(cursor,sizeof(uint8_t),packet_size,fp);
#ifdef DEBUG_M
//    printf("Write packet of size:%u\n", packet_size);
    QTextStream print(stdout, QIODevice::WriteOnly); // stdin

    line =  QString("Write packet of size: %1 \n").arg(QString::number(MaxPacketSize));
//    line.arg(QString::number(packet_size));
    print << line;
    print.flush();
#endif
    length = fp->write((const char*)cursor,MaxPacketSize);// #1 packet
    if(length < 0){
//        printf ("Error Writing to %s\n",fname);
//		fclose(fp);
//		return EXIT_FAILURE;
#ifdef DEBUG_M
        line = QString("Error Writing to %1 . \n").arg(fname);
        print << line;
        print.flush();
#endif
        fp->close();
        return (EXIT_FAILURE);
    }
#ifdef DEBUG_M
    line = QString("Sended %1 \t to be send: %2 \n").arg(length).arg(sizeof(struct ComDataReq_t)-counter);
    print << line;
    print.flush();
#endif
    counter += length;
    cursor += length;
#ifdef DEBUG_M
    line =  QString("Write packet of size: %1 \n").arg(QString::number(packet_size));
//    line.arg(QString::number(packet_size));
    print << line;
    print.flush();
#endif
    length = fp->write((const char*)cursor,MaxPacketSize);// #2 packet
    if(length < 0){
#ifdef DEBUG_M
        line = QString("Error Writing to %1 . \n").arg(fname);
        print << line;
        print.flush();
#endif
        fp->close();
        return (EXIT_FAILURE);
    }
#ifdef DEBUG_M
    line = QString("Sended %1 \t to be send: %2 \n").arg(length).arg(sizeof(struct ComDataReq_t)-counter);
    print << line;
    print.flush();
#endif
    counter += length;
    cursor += length;

    packet_size = sizeof(comdata) - counter;
#ifdef DEBUG_M
    line =  QString("Write packet of size: %1 \n").arg(QString::number(packet_size));
//    line.arg(QString::number(packet_size));
    print << line;
    print.flush();
#endif
    length = fp->write((const char*)cursor,packet_size);// #3 packet

    if(length < 0){
#ifdef DEBUG_M
        line = QString("Error Writing to %1 . \n").arg(fname);
        print << line;
        print.flush();
#endif
        fp->close();
        return (EXIT_FAILURE);
    }
    fp->flush();
#ifdef DEBUG_M
    line = QString("Sended %1 \t to be send: %2 \n").arg(length).arg(sizeof(struct ComDataReq_t)-counter);
    print << line;
    print.flush();
#endif


    return EXIT_SUCCESS;
//    return result;
}

/**
 * @brief UsbExchange::buildComData
 * @param comdata
 */
void
UsbExchange::buildComData(ComDataReq_t* comdata)
{
    uint32_t index = 3;

    struct sSegment* psc = &comdata->payload.instrument1_parameter; //&sc;

    build_segment_default(psc, index);

    comdata->size = sizeof(struct ComDataReq_t);
//    comdata->requestNumber = ++ MyGlobal::mglobal;
    comdata->instruments = N_AXIS;

    comdata->command.order = eoSegment;

}

/**
 * @brief UsbExchange::buildProfile
 * @param sprofile_dst
 */
void
UsbExchange::buildProfile(sProfile* sprofile_dst)
{
    bool ok_conversion;

  Profile* profile = Profile::instance();

  sprofile_dst->TEMPERATURE = profile->get_TEMPERATURE().toFloat(&ok_conversion);

  sprofile_dst->PROPTIONAL = profile->get_PROPTIONAL().toFloat(&ok_conversion);

  sprofile_dst->INTEGRAL = profile->get_INTEGRAL().toFloat(&ok_conversion);

  sprofile_dst->DERIVATIVE = profile->get_DERIVATIVE().toFloat(&ok_conversion);

}

/**
  Формирование запроса для определённой команды
 * @brief Exchange::buildComData
 * @param comdata
 * @param order
 */
void
UsbExchange::buildComData(ComDataReq_t *comdata, eOrder order)
{
    /*
     * eoState,            // Запрос состояния устройства.
     * eoHotendParams,    // Задание параметров Hotend
     *  eoSegment
     * */
    switch (order) {
    case eoState:
        //TODO request Status only
        comdata->size = sizeof(struct ComDataReq_t);
//        comdata->requestNumber = ++MyGlobal::requestIndex;
        comdata->command.order = eoState;
//        sendRequest(comdata);
        break;

    case eoProfile:
        buildProfile(&comdata->payload.profile);
        comdata->size = sizeof(struct ComDataReq_t);
//        comdata->requestNumber = ++MyGlobal::requestIndex;
        comdata->instruments = N_AXIS;

        comdata->command.order = eoProfile;

        sendRequest(comdata); // Get request in Controller.
        break;

    case eoSegment:
        buildComData(comdata);
        break;
    }

}


void
UsbExchange::NoOperation()
{
    volatile static uint i;
    i++;
}
