void loop() {
  if (flag_button_wake_up == false) {  //если кнопка прерывания не была нажата, то...
    count_sleepss_period = 0;          // обнулим количество периодов долгого сна
    update_history();                  // обновим историю
    long_sleep();                      // и опять уйдём в сон
  } else {                                  // если кнопка прерывания была нажата, то
    if (millis() - last_times_1 > 5000) {  // каждые пять секунд меняем информацию
      last_times_1 = millis();             // на экране
      view_weather();
    }
    if (millis() - last_times_2 > 60000) {  //через минуту уходим в сон (60000)
      myOLED.clrScr();              // почистим экран
      flag_button_wake_up = false;  //сбросим флаг кнопки прерывания
      long_sleep();                 //уйдём в догий сон
      last_times_2 = millis();
      measure();                    // как только вышли из сна, опросим датчики
    }
  }
  // по короткому нажатию кнопки меняем инф на экране
  // длинное нажатие (3 секунды) переведёт нас на одну минуту в режим графиков
  button_plus.check(&view_weather, &history_measuring_as_graf);  
  button_set.check(&settings, &history_measuring_as_data);
}

//-----------долгий сон-----------------
void long_sleep() {
  // когда ардуина выходит из сна она проверяет сколько
  // прошло периодов и уходит обратно в сон или дальше
  // на выполнение
  while (count_sleepss_period < period_sleep) {
    sleep(SLEEP_8192MS);
    //отладка
    myOLED.setCursor(0, 1);
    myOLED.print(count_sleepss_period);
    myOLED.setCursor(0, 3);
    myOLED.print(count_wake_up);
    //
    count_sleepss_period++;
    if (flag_button_wake_up == true) {
      break;
    }
  }
  count_wake_up++;
  // тут надо что-то придумать с включением датчиков заранее перед снятием
  // показаний
}

//-------функция для прерывания которая возводит флаг
//-------и по этому флагу ардуина выходит из долгого сна-------------
void empty_func() {
  flag_button_wake_up = true;
  last_times_2 = millis();
}

// старый вариант loop
/*
  void loop() {
  if (millis() - last_times_1 > 5000) {  // каждые пять секунд меняем инф
    last_times_1 = millis();           // на экране
    view_weather();
  }
  if (millis() - last_times_2 > 60000) {  //через минуту уходим в сон (60000)
    myOLED.clrScr();              // почистим экран
    flag_button_wake_up = false;  //сбросим флаг кнопки прерывания
    long_sleep();                 //уйдём в догий сон
    last_times_2 = millis();
    measure();                    // как только вышли из сна, опросим датчики
    if (flag_button_wake_up == false) {  //если кнопка прерывания не была нажата, то...
      count_sleepss_period = 0;     // обнулим количество периодов долгого сна
      update_history();             // обновим историю
    }
  }
  button_plus.check(&view_weather, &history_measuring);  // по нажатию кнопки меняем инф на экране
  }
*/
