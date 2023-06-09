
#include <Arduino.h>
#define _T_SAMPLE_AVERAGE 20   // количество чтений для усреднения

class NTC {
public:
    NTC(uint8_t pin, uint32_t resistance, uint16_t beta, uint8_t tempBase = 25, uint32_t base = 10000) :
    _pin(pin), _beta(beta), _tempBase(tempBase), _baseDivRes((float)base / resistance) {}
    
    // прочитать температуру с пина
    float getTemp() {
        return computeTemp(analogRead(_pin));
    }
    
    // прочитать усреднённую температуру с пина
    float getTempAverage() {
        uint16_t aver = 0;
        for (uint8_t i = 0; i < _T_SAMPLE_AVERAGE; i++) aver += analogRead(_pin);
        return computeTemp((float)aver / _T_SAMPLE_AVERAGE);
    }
    
    // получить температуру из сигнала АЦП (10 бит, float)
    float computeTemp(float analog) {
      //  analog = _baseDivRes / (1023.0f / analog - 1.0);
        analog = _baseDivRes / (4095.0f / analog - 1.0);
        analog = (log(analog) / _beta) + 1.0 / (_tempBase + 273.15);
        return (1.0 / analog - 273.15);
    }
    
private:    
    const uint8_t _pin = 0;
    const uint16_t _beta = 0;
    const uint8_t _tempBase = 25;
    const float _baseDivRes;
};
