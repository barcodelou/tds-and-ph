#ifndef PH_H
#define PH_H



class Ph{
  int _pin;
  const int sample=10;
  int _adcResolution;
 

  public:Ph(int pin,int adcResolution){
    _pin=pin;
    _adcResolution=adcResolution;
    pinMode(_pin,INPUT);
    }


    float ph (float voltage) {
        return 7 + ((2.5 - voltage) / 0.18);
    }

    

    float counterMean(){
      int measurings=0;
      for (int i = 0; i < sample; i++)
      {
          measurings += analogRead(_pin);
          delay(10);
      }
      float voltage = 5 /_adcResolution * measurings/sample;
      return (ph(voltage));
      }

  
  
  };

  #endif
