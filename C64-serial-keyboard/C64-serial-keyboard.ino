#include <Keypad.h>

#include "lut_shifted.h"

#define COMMODORE 127
#define CONTROL   126 
#define KEY_0     '0'
#define KEY_1     '1'
#define KEY_2     '2'
#define KEY_3     '3'
#define KEY_4     '4'
#define KEY_5     '5'
#define KEY_6     '6'
#define KEY_7     '7'
#define KEY_8     '8'
#define KEY_9     '9'
#define KEY_A     'a'
#define KEY_B     'b'
#define KEY_BACKSLASH '\\'
#define KEY_BACKTICK  '`'
#define KEY_C         'c'
#define KEY_COLON     ':'
#define KEY_COMMA     ','
#define KEY_D         'd'
#define KEY_DELETE    '\b'
#define KEY_DOWNARROW 125
#define KEY_E         'e'
#define KEY_ENTER     '\n'
#define KEY_EQUAL     '='
#define KEY_ESCAPE    27
#define KEY_F         'f'
#define KEY_F1        124
#define KEY_F3        123
#define KEY_F5        122
#define KEY_F7        121
#define KEY_G         'g'
#define KEY_H         'h'
#define KEY_HOME      '\r'
#define KEY_I         'i'
#define KEY_J         'j'
#define KEY_K         'k'
#define KEY_L         'l'
#define KEY_M         'm'
#define KEY_MINUS     '-'
#define KEY_N         'n'
#define KEY_O         'o'
#define KEY_P         'p'
#define KEY_PAGEDOWN  120
#define KEY_PERIOD    '.'
#define KEY_PLUS      '+'
#define KEY_Q         'q'
#define KEY_R         'r'
#define KEY_RIGHTARROW 119
#define KEY_S         's'
#define KEY_SEMICOLON ';'
#define KEY_SLASH     '/'
#define KEY_SPACE     ' '
#define KEY_STAR      '*' 
#define KEY_T         't'
#define KEY_AT        '@'
#define KEY_U         'u'
#define KEY_V         'v'
#define KEY_W         'w'
#define KEY_X         'x'
#define KEY_Y         'y'
#define KEY_Z         'z'
#define LEFT_SHIFT    '['
#define RIGHT_SHIFT   118
#define KEY_POUND     '#'
#define KEY_UP        117
#define KEY_LEFT      116
#define KEY_STOP      115
#define KEY_TAB       '\t'

const byte ROWS = 8;
const byte COLS = 8;

char keys_normal[ROWS][COLS] = {
 {KEY_1, KEY_BACKTICK, CONTROL, KEY_2, KEY_SPACE, COMMODORE, KEY_Q, KEY_STOP},
 {KEY_3, KEY_W, KEY_A, KEY_4, KEY_Z, KEY_S, KEY_E, LEFT_SHIFT},
 {KEY_5, KEY_R, KEY_D, KEY_6, KEY_C, KEY_F, KEY_T, KEY_X},
 {KEY_7, KEY_Y, KEY_G, KEY_8, KEY_B, KEY_H, KEY_U, KEY_V},
 {KEY_9, KEY_I, KEY_J, KEY_0, KEY_M, KEY_K, KEY_O, KEY_N},
 {KEY_PLUS, KEY_P, KEY_L, KEY_MINUS, KEY_PERIOD, KEY_COLON, KEY_AT, KEY_COMMA},
 {KEY_PAGEDOWN, KEY_STAR, KEY_SEMICOLON, KEY_HOME, RIGHT_SHIFT, KEY_EQUAL, KEY_BACKSLASH, KEY_SLASH},
 {KEY_DELETE, KEY_ENTER, KEY_RIGHTARROW, KEY_F7, KEY_F1, KEY_F3, KEY_F5, KEY_DOWNARROW}
};

byte colPins[COLS] = {2,3,4,9,6,7,8,5};
byte rowPins[ROWS] = {10,11,12,13,A0,A1,A2,A3};

Keypad kp_normal( makeKeymap(keys_normal), rowPins, colPins, sizeof(rowPins), sizeof(colPins) );

bool shifted = false;

char to_shifted(char ch){
  return lut_shifted[ch];
}

void setup()
{
    Serial.begin(19200);
}

void loop()
{
    if (kp_normal.getKeys()){
        for (int i=0; i<LIST_MAX; i++){
            if ( kp_normal.key[i].stateChanged ){
                switch (kp_normal.key[i].kstate){
                    case PRESSED:
                      if (kp_normal.key[i].kchar == LEFT_SHIFT){
                        shifted = true;
                      }
                      break;
                    case RELEASED:
                      if (kp_normal.key[i].kchar == LEFT_SHIFT){
                        shifted = false;  
                      } else { 
                        if(!shifted){              
                          Serial.print(kp_normal.key[i].kchar);  
                        } else {
                          Serial.print(to_shifted(kp_normal.key[i].kchar));;
                        }
                      }
                      break;
                    case HOLD:
                      break;
                    case IDLE:
                      break;
                }
            }
        }
    } 
}
