
#include "Parser.h"

class Process
{
public:
  void init_process()
  {

    status.power = off;
    status.mode = Cool;
    status.temp = 25;
    status.fan = Quiet;
    status.swing_v = Auto_swing;

    new_status.power = off;
    new_status.mode = Cool;
    new_status.temp = 25;
    new_status.fan = Quiet;
    new_status.swing_v = Auto_swing;
    
    db.init_db();
    db.db_get_status();
   
  };

  // обработка тактов
  void tick(String input_string)
  {
    if (!input_string.isEmpty())
    {
      if (input_string == "no")
      {
        Serial.println("no");
        // todo
        // вывести на дисплей сообщени об ошибке пульта
      }
      else
      {

        new_data = true;
        new_status = parser.get_status(input_string, status);
      }
    }

    if (new_data)
    {
      new_data = false;
      processing();
    }
  }

  void display_ststus(){
    output_status(status);
  }

private:
  Parser parser;
  ACStatus status;
  ACStatus new_status;
  Db db;

  bool new_data;

  void processing()
  {

    if (status.power != new_status.power)
    {
      status.power = new_status.power;
    }

    if (status.mode != new_status.mode)
    {
      status.mode = new_status.mode;
    }

    if (status.temp != new_status.temp)
    {
      status.temp = new_status.temp;
    }

    if (status.fan != new_status.fan)
    {
      status.fan = new_status.fan;
    }

    if (status.swing_v != new_status.swing_v)
    {
      status.swing_v = new_status.swing_v;
    }
    output_status(status);
    
  };

  void print_stat()
  {

    Serial.print("status.power ");
    Serial.println(status.power);
    Serial.print("status.mode ");
    Serial.println(status.mode);
    Serial.print("status.temp ");
    Serial.println(status.temp);
    Serial.print("status.fan ");
    Serial.println(status.fan);
    Serial.print("status.swing_v ");
    Serial.println(status.swing_v);

    Serial.print("new_status.power ");
    Serial.println(new_status.power);
    Serial.print("new_status.mode ");
    Serial.println(new_status.mode);
    Serial.print("new_status.temp ");
    Serial.println(new_status.temp);
    Serial.print("new_status.fan ");
    Serial.println(new_status.fan);
    Serial.print("new_status.swing_v ");
    Serial.println(new_status.swing_v);
  }
};