class Parser
{
public:
    Status get_status(String data, Status stat)
    {
        _status = stat;

        int len = data.length() + 1; // Преобразуем строку в массив символов
        char buf[len];
        data.toCharArray(buf, len);

        int start = 0;
        int cursor = 0;
        bool flag_key = true;
        char *key = NULL;
        // char* value = NULL;

        while (buf[cursor])
        {
            if (buf[cursor] == ':' & flag_key)
            {
                buf[cursor] = '\0';
                key = buf + start;
                start = cursor + 2;
                flag_key = false;
            }
            if (buf[cursor] == ',')
            {
                buf[cursor] = '\0';
                char *value = buf + start;
                set_values(key, value); // отправляем данные в процесс обработки
                start = cursor + 2;
                flag_key = true;
            }
            if (buf[cursor + 1] == '\0')
            {
                char *value = buf + start;
                set_values(key, value); // отправляем данные в процесс обработки
            }
            cursor++;
        }
        return _status;
    }

private:
    Status _status;

    char *get_in_bracket(char *value)
    {
        int cursor = 0;
        char *res = NULL;
        while (value[cursor])
        {
            if (value[cursor] == '(')
                res = value + cursor + 1;
            if (value[cursor] == ')')
            {
                value[cursor] = '\0';
                return res;
            }
            cursor++;
        }
        return res;
    }

    void set_values(char *key, char *value)
    {

        if (!strcmp(key, "Power"))
        {
            if (!strcmp(value, "On"))
                _status.power = on;
            else
                _status.power = off;
            return;
        }

        if (!strcmp(key, "Mode"))
        {
            char *mode = get_in_bracket(value);
            if (mode)
            {
                if (!strcmp(mode, "Auto"))
                {
                    _status.mode = Auto;
                    return;
                }

                if (!strcmp(mode, "UNKNOWN") || !strcmp(mode, "Fan"))
                {
                    _status.mode = Fun;
                    return;
                }

                if (!strcmp(mode, "Dry"))
                {
                    _status.mode = Dry;
                    return;
                }

                if (!strcmp(mode, "Cool"))
                {
                    _status.mode = Cool;
                    return;
                }

                if (!strcmp(mode, "Heat"))
                {
                    _status.mode = Heat;
                    return;
                }
            }
            else
                Serial.println("Ошибка определения режима работы");
            return;
        }

        if (!strcmp(key, "Temp"))
        {
            value[2] = '\0';
            int temp = atoi(value);
            _status.temp = temp;
            return;
        }

        if (!strcmp(key, "Fan"))
        {
            char *mode = get_in_bracket(value);
            if (mode)
            {
                if (!strcmp(mode, "Auto"))
                {
                    _status.fan = Auto_fun;
                    return;
                }
                if (!strcmp(mode, "Maximum") || !strcmp(mode, "Max"))
                {
                    _status.fan = Maximum;
                    return;
                }
                if (!strcmp(mode, "Medium") || !strcmp(mode, "Med"))
                {
                    _status.fan = Medium;
                    return;
                }
                if (!strcmp(mode, "Quiet") || !strcmp(mode, "Min"))
                {
                    _status.fan = Quiet;
                    return;
                }
            }
            else
                Serial.println("Ошибка определения скорости вентилятора");
            return;
        }

        if (!strcmp(key, "Swing(V)"))
        {
            char *mode = get_in_bracket(value);
            if (mode)
            {
                if (!strcmp(mode, "Auto"))
                {
                    _status.swing_v = Auto_swing;
                    return;
                }
                if (!strcmp(mode, "Highest"))
                {
                    _status.swing_v = Highest;
                    return;
                }
                if (!strcmp(mode, "High"))
                {
                    _status.swing_v = High;
                    return;
                }
                if (!strcmp(mode, "Middle"))
                {
                    _status.swing_v = Middle;
                    return;
                }
                if (!strcmp(mode, "Low"))
                {
                    _status.swing_v = Low;
                    return;
                }
            }
            else
                Serial.println("Ошибка определения качания");
            return;
        }
        /*
                                    if (!strcmp(key, "Quiet")){
                                      set_quiet(value);
                                      return;
                                    }

                                    if (!strcmp(key, "Powerful")){
                                      set_powerful(value);
                                      return;
                                    }

                                    if (!strcmp(key, "Clock")){
                                      set_clock(value);
                                      return;
                                    }

                                    if (!strcmp(key, "On Timer")){
                                      set_on_timer(value);
                                      return;
                                    }

                                    if (!strcmp(key, "Off Timer")){
                                      set_off_timer(value);
                                      return;
                                    }




                                    Serial.print("dont_recognize ");
                                    Serial.print(key);
                                    Serial.print(": ");
                                    Serial.println(value);

                                  */
    }
};

/*
  GParser data(str, ','); // оттправляем данные в парсер
  data.my_split();        //сплитим строку
  //int am = data.split();
  //for (byte i = 0; i < am; i++) pars_dictionary(data[i]);
  if (status_AC[4]==15){
    swing.start_swing();
  }
  else{
  swing.stop_swing();
  }*/