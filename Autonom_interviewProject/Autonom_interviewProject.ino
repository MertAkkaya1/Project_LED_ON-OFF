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

String Data;
String LedOn = "ledon=";
String LedOff = "ledoff=";
String Start = "start";
String Stop = "stop";
String Data_On;
String Data_Off;
String Data_Substring_On;
String Data_Substring_Off;

int Int_On_delay = -1;
int Int_Off_delay = -1;
int Data_Baud_Rate_Int = 0;

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

    if (Data.substring(0, 3) == "300" || Data.substring(0, 3) == "600" || Data.substring(0, 4) == "1200" || Data.substring(0, 4) == "2400" || Data.substring(0, 4) == "4800" || Data.substring(0, 4) == "9600" || Data.substring(0, 5) == "19200" || Data.substring(0, 5) == "18400" || Data.substring(0, 6) == "115200") {
      Data_Baud_Rate_Int = Data.toInt();
      Serial.end();
      Serial.begin(Data_Baud_Rate_Int);
      //Serial.print("New Baud Rate:");
      //Serial.println(Data_Baud_Rate_Int);
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
