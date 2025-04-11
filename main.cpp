#include "mbed.h"
#include "TextLCD.h"

TextLCD LCD_display(PTE20, PTE21, PTE22, PTE23, PTE29, PTE30, TextLCD::LCD16x2);
AnalogIn moisture_sensor1(A0);
AnalogIn moisture_sensor2(A1);
AnalogIn moisture_sensor3(A2);
PwmOut water_pump1(D0);
PwmOut water_pump2(D1);
PwmOut water_pump3(D2);

int translate_percentage(int air_reading, int water_reading, int soil_value){
// y = ax + b
float b =  water_reading;
float a = (air_reading - water_reading) / 100;
int y = 100 - ((soil_value - b) / a);
if (0 > y){
//y = 0
return 0;
} 
if(y > 100){
//y =100
return 100;
} 
//y = y for: if((0 <= y) and (y <= 100))
return y;
}


int air_reading1 = 57930; //measured air value for sensor 1
int water_reading1 = 23650; //measured water value for sensor 1
int percentage1;
int count_irrigation1 = 0;

int air_reading2 = 55342; //measured air value for sensor 2
int water_reading2 = 22132; //measured water value for sensor 2
int percentage2;
int count_irrigation2 = 0;


int air_reading3 = 59726; //measured air value for sensor 3
int water_reading3 = 25252; //measured water value for sensor 3
int percentage3;
int count_irrigation3 = 0;

int main() {
    water_pump1 = 1; //initially pump 1 does not work.  
    water_pump2 = 1; //initially pump 2 does not work.
    water_pump3 = 1; //initially pump 3 does not work.
       while(1) {
    int soil_value1 = moisture_sensor1.read_u16();
    LCD_display.cls();
    LCD_display.printf("%d",soil_value1);  
    wait(4);
    }   

    while(1) {   
    for (int i = 0; i < 45; i++) {
      
    // for pot 1
    int soil_value1 = moisture_sensor1.read_u16();
    LCD_display.cls();
    LCD_display.printf("    POT 1");
    LCD_display.locate(0,1);
    LCD_display.printf("HUMIDITY: ");
    percentage1 = translate_percentage(air_reading1, water_reading1, soil_value1);
    LCD_display.printf("%d", percentage1);
    LCD_display.printf("%s", " %");
    wait(3);
    LCD_display.cls();
    LCD_display.printf("TIMES WATERED: ");
    LCD_display.printf("%d", count_irrigation1);
    
    if (75 > percentage1){
    wait(6);
    int soil_value1 = moisture_sensor1.read_u16();
    percentage1 = translate_percentage(air_reading1, water_reading1, soil_value1);
    }
    if (75 > percentage1){
    count_irrigation1++;
    LCD_display.cls();
    LCD_display.printf("WATERING....");
    wait(2);
    water_pump1 = 0;
    wait(10);
    water_pump1 = 1;
    }
    else{
    water_pump1 = 1;  
    }
    wait(1.5);
    // kaç l sulandığını da alt satırda belirtebilir
    
    //for pot 2
    int soil_value2 = moisture_sensor2.read_u16();
    LCD_display.cls();
    LCD_display.printf("    POT 2");
    LCD_display.locate(0,1);
    LCD_display.printf("HUMIDITY: ");
    percentage2 = translate_percentage(air_reading2, water_reading2, soil_value2);
    LCD_display.printf("%d", percentage2);
    LCD_display.printf("%s", " %");
    wait(3);
    LCD_display.cls();
    LCD_display.printf("TIMES WATERED: ");
    LCD_display.printf("%d", count_irrigation2);
    
    if (75 > percentage2){
    wait(6);
    int soil_value2 = moisture_sensor2.read_u16();
    percentage2 = translate_percentage(air_reading2, water_reading2, soil_value2);
    }
    if (75 > percentage2){
    count_irrigation2++;
    LCD_display.cls();
    LCD_display.printf("WATERING....");
    wait(2);
    water_pump2 = 0;
    wait(10);
    water_pump2 = 1;
    }
    else{
    water_pump2 = 1;  
    }
    wait(1.5);
    
    
    //for pot 3
    int soil_value3 = moisture_sensor3.read_u16();
    LCD_display.cls();
    LCD_display.printf("    POT 3");
    LCD_display.locate(0,1);
    LCD_display.printf("HUMIDITY: ");
    LCD_display.printf("%d", percentage3);
    LCD_display.printf("%s", " %");
    wait(3);
    LCD_display.cls();
    LCD_display.printf("TIMES WATERED: ");
    LCD_display.printf("%d", count_irrigation3);
    
    if (75 > percentage3){
    wait(6);
    int soil_value3 = moisture_sensor3.read_u16();
    percentage3 = translate_percentage(air_reading3, water_reading3, soil_value3);
    }
    if (75 > percentage3){
    count_irrigation3++;
    LCD_display.cls();
    LCD_display.printf("WATERING....");
    wait(2);
    water_pump3 = 0;
    wait(10);
    water_pump3 = 1;
    }
    else{
    water_pump3 = 1;  
    }
    wait(1.5);
    }

    wait(10800);
    //for 3 hours    
    }
}