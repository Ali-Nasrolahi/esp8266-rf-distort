/**
 * @file config.h
 * @author Ali Nasrolahi (a.nasrolahi01@gmail.com)
 * @brief esp8266-rf-distortion.
 * @date 2023-05-19
 */

/* AS1000F data pin */
#define RF_DATA_PIN D3

/* Pulses */
#define PULSE_CNT 3

/* starts from 10khz */
#define BASE_FREQ 10

/* Sequences */
#define SEQ 50

/* Sleep macro */
#ifdef ESP8266
#define sleep os_delay_us
#else
/* modify according to your chip */
#define delay_us
#endif

#define WAVE_LENGTH (1000 * 1000 / BASE_FREQ * 2)

uint8_t seq;

void bring_up()
{
    digitalWrite(RF_DATA_PIN, HIGH);
    sleep(WAVE_LENGTH * seq);
}

void drag_down()
{
    digitalWrite(RF_DATA_PIN, LOW);
    sleep(WAVE_LENGTH * seq);
}

void setup()
{
    pinMode(RF_DATA_PIN, OUTPUT);
    digitalWrite(RF_DATA_PIN, LOW);
}

void loop()
{

    for (seq = 1; seq <= SEQ; seq++) {
        for (int pulse = 0; pulse < PULSE_CNT; pulse++) {
            bring_up();
            drag_down();
        };
    };
};