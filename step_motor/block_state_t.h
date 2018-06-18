#ifndef BLOCK_STATE_T
#define BLOCK_STATE_T

//#include <stdint.h>
#include "Recalculate_flag.h"
//#define byte uint8_t

#define word uint32_t

//  Описатель состояний обработки фаз движения по оси Y.
//  Три состояния: разгон, движение, торможение.
//
//  Функция перерегулирования. При разгоне будет отставание, при торможении - опережение.
typedef struct block_state_t {
//public:
    //  Индикатор текущего и начального состояния автомата обработки прерываний по оси X.
    byte state;
    uint8_t  direction_bits;            // The direction bit set for this block (refers to *_DIRECTION_BIT in config.h)
    uint8_t axis_mask;          // маска активности оси
    uint8_t microstep;
    word steps;
    double_t path;
    word accelerate_until;
    word decelerate_after;
    word initial_rate;
    word initial_speedLevel;
    word nominal_rate;
    word speedLevel; //  ступень скорости   разгона
    word final_rate;
    word final_speedLevel;
    word step_event_count;
    double_t tan_theta;		//  Значение тангенса угла наклона отрезка траектории.
//	double_t tangent_inv; //  Обратное значение тангенса. Для подпрограммы обработки прерываний.
    double_t nominal_speed; //Максимальное значение для это оси из Профиля.
    double_t acceleration; // Максимальное значение для оси из Профиля.

    double_t	entry_speed;
    double_t	max_entry_speed;
    double_t	millimeters;
    byte	recalculate_flag;	// Recaculate_flag:Набор флагов: для консольной или пограммной обработки;
    byte	nominal_length_flag;

    /**	  Схема описывает порядок переходов состояний."
     *
        Значения состояний:
        1 - разгон на начальном участке
        2 - линейное движение
        3 - торможение на конечном участке

        4 - торможение на начальном участке
        5 - линейное движение
        6 - разгон на конечном участке

        7 - разгон на начальном участке
        8 - линейное движение
        9 - разгон на конечном участке

        10 - торможение на начальном участке
        11 - линейное движение
        12 — торможение на конечном участке

        13 - разгон на начальном участке
        14 - торможение на конечном участке

        16 - торможение на начальном участке
        17 - разгон на конечном участке

        24 - Разгон на начальном участке   SEEK
        25 - линейное движение     SEEK
        26 - торможение на конечном участке SEEK



        Условия перехода определяются значениями
        accelerate_until - это значения по оси X до которого
        автомат находится в состоянии [0], посде чего
        перехдит в состояние с индексом [1].
        По достижении значения decelerate_afetr,
        автомат переходит в состояние с индексом [2].
        Схема обработки начального и конечного участков сегмента.
      * варианты схем движения: разгон, линейно, разгон
      * || торможение, линейно, торможение
      * || разгон, торможение.
      * и т.д.
     */
    byte schem[3];
}block_state;

/*
// This struct is used when buffering the setup for each linear movement "nominal" values are as specified in
// the source g-code and may never actually be reached if acceleration management is active.
typedef struct {

  // Fields used by the bresenham algorithm for tracing the line
  uint8_t  direction_bits;            // The direction bit set for this block (refers to *_DIRECTION_BIT in config.h)
  uint32_t steps; // Step count along each axis << steps_x, steps_y, steps_z
  int32_t  step_event_count;          // The number of step events required to complete this block

  // Fields used by the motion planner to manage acceleration
  float nominal_speed;               // The nominal speed for this block in mm/sec
  float entry_speed;                 // Entry speed at previous-current block junction in mm/sec
  float max_entry_speed;             // Maximum allowable junction entry speed in mm/sec
  float millimeters;                 // The total travel of this block in mm
//  float tan_theta;					//  Тангенс угла наклона отрезка к оси X
  uint8_t recalculate_flag;           // Planner flag to recalculate trapezoids on entry junction
  uint8_t nominal_length_flag;        // Planner flag for nominal speed always reached

  // Settings for the trapezoid generator
  uint16_t initial_rate;              // The step rate at start of block
  uint16_t final_rate;                // The step rate at end of block
//  	int16 rate_delta;                 // The steps/minute to add or subtract when changing speed (must be positive)
  uint32_t accelerate_until;          // The index of the step event on which to stop acceleration
  uint32_t decelerate_after;          // The index of the step event on which to start decelerating
  uint16_t nominal_rate;              // The nominal step rate for this block in step_events/minute

} block_state;
*/


#endif // BLOCK_STATE_T

