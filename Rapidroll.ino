#include <RTClib.h>

//#include <IRremote.h>
bool rmtErr=false;bool rmtIsEnable=false;
#include <avr/pgmspace.h>
#include <SPI.h>

#include <Adafruit_GFX.h>

#include <Adafruit_ST7735.h>

#include <PlayRtttl.h>

#include <Otto.h>
Otto Otto;


int y_stick0 = 130;
int x_stick0 = 80;
boolean stick_status_1 = 0;
int y_stick1 = 160;
int x_stick1 = 80;
boolean stick_status_2 = 0;
int score = 0;
int random_stick = 0;
boolean FREE = 0;
boolean DIE = 0;
int speed = 3;
int ball_x = 80;
int ball_y = 15;
boolean stick_status_3 = 0;
boolean stick_status_4 = 0;
int x_stick2 = 80;
int x_stick3 = 80;
int y_stick2 = 190;
int y_stick3 = 210;
int thanh_gan_nhat;

double random_int(int a,int b) {
  if (a > b) {
    int c = a;
    a = b;
    b = c;
  }
  return (double) random(a,b+1);
}
RTC_DS3231 rtc;
DateTime t;

String daysOfTheWeek[7]={"Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado"};
String monthsNames[12]={"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};

bool gmp=false;

#define TFT_DC	A2
#define TFT_RST	A3
#define TFT_CS	A1
#define TFT_MOSI	A4
#define TFT_SCLK	A5
Adafruit_ST7735 TFT = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
unsigned int BCKGRDCOL = TFT.color565(255, 255, 255);
    #define btnB1 7
  #define btnB2 A1
  #define btnA1 8
  #define btnA2 9
  void initbtnGamePad() {
    pinMode(btnA1, INPUT);
    pinMode(btnA2, INPUT);
    pinMode(btnB1, INPUT);
    pinMode(btnB2, INPUT);
  }
  bool readbtnGamePad(byte btn) {
    byte A_State = digitalRead(btnA1) * 2 + digitalRead(btnA2);
    byte B_State = digitalRead(btnB1) * 2 + digitalRead(btnB2);
    if (btn < 3) {
      return (B_State == btn);
    }
    else {
      return (A_State == (btn-3));
    }
  }
#define redPin 6
#define greenPin 10
#define bluePin 11
#define LeftLeg 2 // left leg pin, servo[0]
#define RightLeg 3 // right leg pin, servo[1]
#define LeftFoot 4 // left foot pin, servo[2]
#define RightFoot 5 // right foot pin, servo[3]
#define Buzzer 13 //buzzer pin


void stick1() {
  TFT.fillRect(x_stick0,y_stick0,20,4,BCKGRDCOL);
  y_stick0 = y_stick0 - speed;
  if (stick_status_1 == 0) {
    TFT.fillRect(x_stick0,y_stick0,20,4,ST7735_BLACK);
  } else {
    TFT.fillRect(x_stick0,y_stick0,20,4,ST7735_RED);
  }
  if (y_stick0 < 15 + speed) {
    TFT.fillRect(x_stick0,y_stick0,20,4,BCKGRDCOL);
    y_stick0 = 130;
    x_stick0 = random_int(1, 6) * 20;
    if (random_int(1, 100) <= 25) {
      stick_status_1 = 1;
    } else {
      stick_status_1 = 0;
    }
  }
}

void stick2() {
  TFT.fillRect(x_stick1,y_stick1,20,4,BCKGRDCOL);
  y_stick1 = y_stick1 - speed;
  if (stick_status_2 == 0) {
    TFT.fillRect(x_stick1,y_stick1,20,4,ST7735_BLACK);
  } else {
    TFT.fillRect(x_stick1,y_stick1,20,4,ST7735_RED);
  }
  if (y_stick1 < 15 + speed) {
    TFT.fillRect(x_stick1,y_stick1,20,4,BCKGRDCOL);
    y_stick1 = y_stick0 + 30;
    x_stick1 = random_int(1, 6) * 20;
    if (random_int(1, 100) <= 25) {
      stick_status_2 = 1;
    } else {
      stick_status_2 = 0;
    }
  }
}

void stick_3() {
  TFT.fillRect(x_stick2,y_stick2,20,4,BCKGRDCOL);
  y_stick2 = y_stick2 - speed;
  if (stick_status_3 == 0) {
    TFT.fillRect(x_stick2,y_stick2,20,4,ST7735_BLACK);
  } else {
    TFT.fillRect(x_stick2,y_stick2,20,4,ST7735_RED);
  }
  if (y_stick2 < 15 + speed) {
    TFT.fillRect(x_stick2,y_stick2,20,4,BCKGRDCOL);
    y_stick2 = y_stick1 + 30;
    x_stick2 = random_int(1, 6) * 20;
    if (random_int(1, 100) <= 25) {
      stick_status_3 = 1;
    } else {
      stick_status_3 = 0;
    }
  }
}

void stick4() {
  TFT.fillRect(x_stick3,y_stick3,20,4,BCKGRDCOL);
  y_stick3 = y_stick3 - speed;
  if (stick_status_4 == 0) {
    TFT.fillRect(x_stick3,y_stick3,20,4,ST7735_BLACK);
  } else {
    TFT.fillRect(x_stick3,y_stick3,20,4,ST7735_RED);
  }
  if (y_stick3 < 15 + speed) {
    TFT.fillRect(x_stick3,y_stick3,20,4,BCKGRDCOL);
    y_stick3 = y_stick2 + 30;
    x_stick3 = random_int(1, 6) * 20;
    if (random_int(1, 100) <= 25) {
      stick_status_4 = 1;
    } else {
      stick_status_4 = 0;
    }
  }
}

void tim_thanh() {
  if (thanh_gan_nhat == 0) {
    if (ball_y > y_stick0 + 2) {
      thanh_gan_nhat = 1;
      score = score + 1;
    } else {
      check_thanh();
    }
  }
  if (thanh_gan_nhat == 1) {
    if (ball_y > y_stick1 + 2) {
      thanh_gan_nhat = 2;
      score = score + 1;
    } else {
      check_thanh2();
    }
  }
  if (thanh_gan_nhat == 2) {
    if (ball_y > y_stick2 + 2) {
      thanh_gan_nhat = 3;
      score = score + 1;
    } else {
      check_thanh3();
    }
  }
  if (thanh_gan_nhat == 3) {
    if (ball_y > y_stick3 + 2) {
      thanh_gan_nhat = 0;
      score = score + 1;
    } else {
      check_thanh4();
    }
  }
}

void check_thanh() {
  if ((ball_y >= y_stick0 - 8 & ball_y <= y_stick0 + 4) & (ball_x >= x_stick0 & ball_x <= x_stick0 + 20)) {
    if (stick_status_1 == 0) {
      FREE = 1;
    } else {
      DIE = 1;
    }
  } else {
    FREE = 0;
  }
}

void check_thanh4() {
  if ((ball_y >= y_stick3 - 8 & ball_y <= y_stick3 + 4) & (ball_x >= x_stick3 & ball_x <= x_stick3 + 20)) {
    if (stick_status_4 == 0) {
      FREE = 1;
    } else {
      DIE = 1;
    }
  } else {
    FREE = 0;
  }
}

void score2() {
  TFT.fillRect(0,0,80,7,BCKGRDCOL);
  TFT.setCursor(20,0);
  TFT.setTextColor(ST7735_BLACK);
  TFT.setTextSize(1);
  TFT.println(score);
}

void check_thanh3() {
  if ((ball_y >= y_stick2 - 8 & ball_y <= y_stick2 + 4) & (ball_x >= x_stick2 & ball_x <= x_stick2 + 20)) {
    if (stick_status_3 == 0) {
      FREE = 1;
    } else {
      DIE = 1;
    }
  } else {
    FREE = 0;
  }
}

void check_thanh2() {
  if ((ball_y >= y_stick1 - 8 & ball_y <= y_stick1 + 4) & (ball_x >= x_stick1 & ball_x <= x_stick1 + 20)) {
    if (stick_status_2 == 0) {
      FREE = 1;
    } else {
      DIE = 1;
    }
  } else {
    FREE = 0;
  }
}

void setColor(int redValue, int greenValue, int blueValue) {
 analogWrite(redPin,(255 - redValue));
  analogWrite(greenPin,(255 - greenValue));
if (rmtIsEnable){if(blueValue<100){analogWrite(bluePin,255);}else {analogWrite(bluePin,0);}}else{analogWrite(bluePin, (255 -blueValue));
}
}

void setup() {

  	TFT.initR(INITR_BLACKTAB);
	TFT.fillScreen(BCKGRDCOL);
	TFT.setRotation(3);
  	initbtnGamePad();

  pinMode(greenPin, OUTPUT);
pinMode(redPin, OUTPUT);
pinMode(bluePin, OUTPUT);
setColor(0,0,0);

  pinMode(A6,INPUT);

  pinMode(13,OUTPUT);
Otto.initBuzzer(Buzzer);

    x_stick0 = random_int(1, 6) * 20;
  x_stick1 = random_int(1, 6) * 20;
  x_stick2 = random_int(1, 6) * 20;
  x_stick3 = random_int(1, 6) * 20;
  random_stick = random_int(1, 4);
  TFT.fillRect(0,10,160,5,ST7735_BLACK);
  TFT.fillRect(0,10,20,128,ST7735_BLACK);
  TFT.fillRect(140,10,20,128,ST7735_BLACK);

}

void loop() {
    if (DIE == 0) {
      score2();
      TFT.drawCircle(ball_x,ball_y,4,BCKGRDCOL);
      if (FREE == 1) {
        switch (thanh_gan_nhat) {
        case 0:
          ball_y = y_stick0 - 8;
          break;
         case 1:
          ball_y = y_stick1 - 8;
          break;
         case 2:
          ball_y = y_stick2 - 8;
          break;
         case 3:
          ball_y = y_stick3 - 8;
          break;
        }
      } else {
        ball_y = ball_y + 2;
      }
      TFT.drawCircle(ball_x,ball_y,4,ST7735_BLACK);
      if (readbtnGamePad(0)) {
        if (ball_x == 0) {
          ball_x = ball_x - 0;
        } else {
          TFT.drawCircle(ball_x,ball_y,4,BCKGRDCOL);
          ball_x = ball_x - 4;
          TFT.drawCircle(ball_x,ball_y,4,ST7735_BLACK);
        }
      }
      if (readbtnGamePad(4)) {
        if (ball_x == 160) {
          ball_x = ball_x + 0;
          TFT.drawCircle(ball_x,ball_y,4,ST7735_BLACK);
        } else {
          TFT.drawCircle(ball_x,ball_y,4,BCKGRDCOL);
          ball_x = ball_x + 4;
          TFT.drawCircle(ball_x,ball_y,4,ST7735_BLACK);
        }
      }
      check_thanh();
      stick1();
      stick2();
      stick_3();
      stick4();
      delay(30);
      tim_thanh();
    }

}