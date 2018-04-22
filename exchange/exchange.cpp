#include "exchange.h"


//#include from FeeRTOS project.


//------------- defs
#define MaxPacketSize	64


//------------- vars
const char* fname = "/dev/cnccontrol";

const struct sControl default_block = {
   X_AXIS, 2, 0, 3, 10, 3, 7,  50132, 5370, 50132, 0, {1, 2, 3}, forward, 0, 0
};

static const struct sHead default_segment_head = {
   N_AXIS, (X_FLAG|Y_FLAG|Z_FLAG|E_FLAG), 0xFFFF, 1
};

//--------- functions

Exchange::Exchange()
{

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

        sendBuffer((uint8_t*)&comdata,sizeof(comdata),&data);

//        fclose(fp);
        data.close();
    }else{
        printf("Can't open device. maybe module not loaded. Use: $sudo insmod ./eclipse-workspace/usbtest/test1.ko \n"
               "or device dosn't connected.\n");
//        return EXIT_FAILURE;
    }


}


void
Exchange::load_defaults(struct sControl* pctl)
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

void
Exchange::build_segment_default(struct sSegment* psc, uint32_t i)
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

// TODO sendBuffer
int
Exchange::sendBuffer(uint8_t* buffer, uint32_t size, QFile* fp)
{
    uint8_t* cursor = buffer;
    uint32_t result = 0, length=0, packet_size, counter = 0;

    packet_size = MaxPacketSize;

//    length = fwrite(cursor,sizeof(uint8_t),packet_size,fp);

//    printf("Write packet of size:%u\n", packet_size);
    QTextStream print(stdout, QIODevice::WriteOnly); // stdin
    QString line =  QString("Write packet of size: %1 \n").arg(QString::number(packet_size));
//    line.arg(QString::number(packet_size));
    print << line;

    print.flush();

    return result;
}

void
Exchange::buildComData(ComDataReq_t* comdata)
{
    uint32_t index = 3;
    static uint32_t requestIndex;

    struct sSegment* psc = &comdata->payload.instrument1_parameter; //&sc;

    build_segment_default(psc, index);

    comdata->size = sizeof(struct ComDataReq_t);
    comdata->requestNumber = ++requestIndex;
    comdata->instruments = N_AXIS;

    comdata->command.order = eoSegment;

}

void
Exchange::NoOperation()
{
    volatile static uint i;
    i++;
}
