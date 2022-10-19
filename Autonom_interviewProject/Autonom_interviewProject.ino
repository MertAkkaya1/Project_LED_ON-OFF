/*
   Hazırlayan: Mert Akkaya
   m.mertakkaya.a@gmail.com

   Asagidaki kod blogu seri port ekranindan alinan verilere gore Led ON/OFF sürelerini ayarlamak icin yazilmistir.

   Seri porttan girilen 'stop' komutu Led'in 1sn araliklarla yanip sonmesini saglar
   Seri porttan girilen 'start' komutu Led'in bir onceki on/off surelerine gore yanip sonmesini saglar. Sonrasında bu on/off sureleri 'ledon=ON time' ve 'ledoff=OFF time' degerleri ile seri port uzerinden degistirilebilmektedir.

   Seri haberlesme Serial.begin(115200, SERIAL_8N1); olarak default baslayip sonrasinda yine seri port uzerinden ayarlanabilmektedir.
*/

/* Macro defines */
#define LEDPIN 2
#define LED_ON_TIME 1000
#define LED_OFF_TIME 1000

/* enumaration define */
enum Mode{
  STOP,
  START,
  NONE
};

/* Global variable definitions */
enum Mode Mode_Select = NONE;

String SeRIAL_5N1 = "SERIAL_5N1\n";
String SeRIAL_6N1 = "SERIAL_6N1\n";
String SeRIAL_7N1 = "SERIAL_7N1\n";
String SeRIAL_8N1 = "SERIAL_8N1\n";
String SeRIAL_5N2 = "SERIAL_5N2\n";
String SeRIAL_6N2 = "SERIAL_6N2\n";
String SeRIAL_7N2 = "SERIAL_7N2\n";
String SeRIAL_8N2 = "SERIAL_8N2\n";
String SeRIAL_5E1 = "SERIAL_5E1\n";
String SeRIAL_6E1 = "SERIAL_6E1\n";
String SeRIAL_7E1 = "SERIAL_7E1\n";
String SeRIAL_8E1 = "SERIAL_8E1\n";
String SeRIAL_5E2 = "SERIAL_5E2\n";
String SeRIAL_6E2 = "SERIAL_6E2\n";
String SeRIAL_7E2 = "SERIAL_7E2\n";
String SeRIAL_8E2 = "SERIAL_8E2\n";
String SeRIAL_5O1 = "SERIAL_5O1\n";
String SeRIAL_6O1 = "SERIAL_6O1\n";
String SeRIAL_7O1 = "SERIAL_7O1\n";
String SeRIAL_8O1 = "SERIAL_8O1\n";
String SeRIAL_5O2 = "SERIAL_5O2\n";
String SeRIAL_6O2 = "SERIAL_6O2\n";
String SeRIAL_7O2 = "SERIAL_7O2\n";
String SeRIAL_8O2 = "SERIAL_8O2\n";

String Data;
String LedOn = "ledon=";
String LedOff = "ledoff=";
String Start = "start";
String Stop = "stop";
String Data_On;
String Data_Off;
String Data_Substring_On;
String Data_Substring_Off;
String Data_Baud_Rate_Str;

int Int_On_delay = -1;
int Int_Off_delay = -1;
int Data_Baud_Rate_Int = 0;
int Date_Baud_Rate_StrToInt = -1;

bool start_flag = false;

/* setup function */
void setup() {
  Serial.begin(115200);
  Serial.println("**INFORMATION**");
  Serial.print("stop");
  Serial.println(" -> Led ON/OFF time = 1 sn");
  Serial.print("start");
  Serial.println(" -> Echo Function activated");
  Serial.println("ledon=ON time");
  Serial.println("ledoff=OFF time");
  pinMode(LEDPIN, OUTPUT);
}

/* loop function */
void loop() {
  if (Serial.available()) {
    Data = Serial.readString();

    if (Data.substring(0, 3) == "300" || Data.substring(0, 3) == "600" || Data.substring(0, 4) == "1200" || Data.substring(0, 4) == "2400" || Data.substring(0, 15) == "4800" || Data.substring(0, 15) == "9600" || Data.substring(0, 5) == "19200" || Data.substring(0, 5) == "18400" || Data.substring(0, 6) == "115200") {
      for (int i = 0; i < Data.length(); i++) {
        if (Data.substring(i, i + 1) == " ") {
          Data_Baud_Rate_Int = Data.substring(0, i).toInt(); // example: 9600
          Data_Baud_Rate_Str = Data.substring(i + 1);       // example: SERIAL_8N1
          //Serial.println(Data_Baud_Rate_Int);
          //Serial.println(Data_Baud_Rate_Int);
          //Serial.println(Data_Baud_Rate_Str);
          Date_Baud_Rate_StrToInt = Baud_Rate_Str_Argument(Data_Baud_Rate_Str);
          Echo_Mode(String(Data_Baud_Rate_Int), Data_Baud_Rate_Str);
          //Serial.print("Baud Rate Function: ");
          //Serial.println(Date_Baud_Rate_StrToInt);;
        }        
      }
      Serial.end();
      Serial.begin(Data_Baud_Rate_Int, Date_Baud_Rate_StrToInt);
    }
    
    if (Data.substring(0, 4) == Stop) {
      Mode_Select = STOP;
      start_flag = false;
    }

    else if (Data.substring(0, 5) == Start) {
      start_flag = true;
    }

    if (start_flag) {
      if (Data.substring(0, 6) == LedOn) {
        Data_On = Data;
        Data_Substring_On = Data.substring(6, Data.length());
        Int_On_delay = Data_Substring_On.toInt();
      }
      else if (Data.substring(0, 7) == LedOff) {
        Data_Off = Data;
        Data_Substring_Off = Data.substring(7, Data.length());
        Int_Off_delay = Data_Substring_Off.toInt();
      }
      if (Int_On_delay != -1 && Int_Off_delay != -1)
      {
        Mode_Select = START;
        Echo_Mode(Data_On, Data_Off);
        start_flag = false;
      }
    }
  }

  /* switch case control mechanism to determine the required state */
  switch (Mode_Select) {
    case STOP:
      //Serial.println("STOP");
      Led_On_Off(LED_ON_TIME, LED_OFF_TIME);
      break;

    case START:
      //Serial.println("START");
      Led_On_Off(Int_On_delay, Int_Off_delay);
      break;

    default:
      /* Do nothing */
      break;
  }
}

/* Led_On_Off function is defined for task 1 to ON/OFF LED with the required ON/OFF time */
void Led_On_Off(int Ontime, int Offtime)
{
  //Serial.println("Task1 Active");
  digitalWrite(LEDPIN, HIGH);
  delay(Ontime);
  digitalWrite(LEDPIN, LOW);
  delay(Offtime);
}

/* Echo_Mode function that allows us to echo ON/OFF time through UART */
void Echo_Mode(String On_time_string, String Off_time_string)
{
  //Serial.println("Task2 Active");
  Serial.println(On_time_string);
  Serial.println(Off_time_string);
}

int Baud_Rate_Str_Argument(String argument) {
  //Serial.println("Baud_Rate_Str_Argument");
  if (argument == SeRIAL_5N1) {
    return 0x00;
  }
  else if (argument == SeRIAL_6N1) {
    return 0x02;
  }
  else if (argument == SeRIAL_7N1) {
    return 0x04;
  }
  else if (argument == SeRIAL_8N1) {
    return 0x06;
  }
  else if (argument == SeRIAL_5N2) {
    return 0x08;
  }
  else if (argument == SeRIAL_6N2) {
    return 0x0A;
  }
  else if (argument == SeRIAL_7N2) {
    return 0x0C;
  }
  else if (argument == SeRIAL_8N2) {
    return 0x0E;
  }
  else if (argument == SeRIAL_5E1) {
    return 0x20;
  }
  else if (argument == SeRIAL_6E1) {
    return 0x22;
  }
  else if (argument == SeRIAL_7E1) {
    return 0x24;
  }
  else if (argument == SeRIAL_8E1) {
    return 0x26;
  }
  else if (argument == SeRIAL_5E2) {
    return 0x28;
  }
  else if (argument == SeRIAL_6E2) {
    return 0x2A;
  }
  else if (argument == SeRIAL_7E2) {
    return 0x2C;
  }
  else if (argument == SeRIAL_8E2) {
    return 0x2E;
  }
  else if (argument == SeRIAL_5O1) {
    return 0x30;
  }
  else if (argument == SeRIAL_6O1) {
    return 0x32;
  }
  else if (argument == SeRIAL_7O1) {
    return 0x34;
  }
  else if (argument == SeRIAL_8O1) {
    return 0x36;
  }
  else if (argument == SeRIAL_5O2) {
    return 0x38;
  }
  else if (argument == SeRIAL_6O2) {
    return 0x3A;
  }
  else if (argument == SeRIAL_7O2) {
    return 0x3C;
  }
  else if (argument == SeRIAL_8O2) {
    return 0x3E;
  }
}
