class StepSwing{
  public:
    StepSwing(int pin1, int pin2, int pin3, int pin4){
    _pin1 = pin1;
    _pin2 = pin2;
    _pin3 = pin3;
    _pin4 = pin4;
    initPin();
    last_time  = millis();
    parking();
    }

    void set_speed_8_step(int speed){
      speed_8_step = speed;
    }

    void set_speed_4_step(int speed){
      speed_4_step = speed;
    }

/*
    void run_swing(){

        if ( millis() - last_time > 1000/speed_4_step){
              last_time  = millis();
              take_step_4();
              num_step_4 += up_down;
              if (num_step_4>3) num_step_4=0; 
              if (num_step_4<0) num_step_4=3;
              _current_position +=up_down;
              if (_current_position >=_up_position || _current_position<=_down_position){
                up_down *= -1;
              }

            }
    }

*/
    void run_swing(){

        if ( millis() - last_time > 1000/speed_8_step){
              last_time  = millis();
              take_step_8();
              num_step_8 += up_down;
              if (num_step_8>7) num_step_8=0; 
              if (num_step_8<0) num_step_8=7;
              _current_position +=up_down;
              if (_current_position >=_up_position || _current_position<=_down_position){
                up_down *= -1;
              }

            }
    }  
    
    void parking (){
        digitalWrite(_pin1, 0);  
        digitalWrite(_pin2, 0); 
        digitalWrite(_pin3, 0); 
        digitalWrite(_pin4, 0); 
  }

  private:
    int _pin1; 
    int _pin2;
    int _pin3;
    int _pin4;

    int _up_position = 850;
    int _center_position = 500;
    int _down_position = 0;
    int _current_position = 0;
    int up_down = 1;

    int pole1_8_step[9] ={0,0,0,0, 0,1,1,1, 0};//pole1, 8 step values
    int pole2_8_step[9] ={0,0,0,1, 1,1,0,0, 0};//pole2, 8 step values
    int pole3_8_step[9] ={0,1,1,1, 0,0,0,0, 0};//pole3, 8 step values
    int pole4_8_step[9] ={1,1,0,0, 0,0,0,1, 0};//pole4, 8 step values
    int num_step_8 = 0;

    int pole1_4_step[5] ={1,0,1,0, 0};//pole1, 4 step values
    int pole2_4_step[5] ={0,1,1,0, 0};//pole2, 4 step values
    int pole3_4_step[5] ={0,1,0,1, 0};//pole3, 4 step values
    int pole4_4_step[5] ={1,0,0,1, 0};//pole4, 4 step values
    int num_step_4 = 0;

    unsigned long last_time;
    int speed_8_step = 200; //шагов в секунду
    int speed_4_step = 60; //шагов в секунду

  void initPin(){
      pinMode(_pin1, OUTPUT);//define pin for ULN2003 in1 
      pinMode(_pin2, OUTPUT);//define pin for ULN2003 in2   
      pinMode(_pin3, OUTPUT);//define pin for ULN2003 in3   
      pinMode(_pin4, OUTPUT);//define pin for ULN2003 in4 
   } 

  void take_step_8(){
     digitalWrite(_pin1, pole1_8_step[num_step_8]);  
     digitalWrite(_pin2, pole2_8_step[num_step_8]); 
     digitalWrite(_pin3, pole3_8_step[num_step_8]); 
     digitalWrite(_pin4, pole4_8_step[num_step_8]); 

  }
  
  void take_step_4(){
    digitalWrite(_pin1, pole1_4_step[num_step_4]);  
    digitalWrite(_pin2, pole2_4_step[num_step_4]); 
    digitalWrite(_pin3, pole3_4_step[num_step_4]); 
    digitalWrite(_pin4, pole4_4_step[num_step_4]); 
  }


};