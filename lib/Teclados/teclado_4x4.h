#ifndef TECLADO_4X4_H
#define TECLADO_4X4_H

#include <Arduino.h>

#define ROW0 digitalRead(30) //y1
#define ROW1 digitalRead(32) //y2
#define ROW2 digitalRead(34) //y3
#define ROW3 digitalRead(36) //y4

typedef struct
{
    unsigned teclado_completo : 1;
    unsigned : 7;
} Bits_Teclado_4;

Bits_Teclado_4 bits_t_4x4 = {0};

char row;
char repeticiones_tecla;
char contador_tecla_sin_tocar = 2;
char tecla = 'N';
char tecla_actual = 'N';
char tecla_anterior = 'N';

// Keypad layout:
char const KEYS[4][4] = {
    {'1', '4', '7', '*'},
    {'2', '5', '8', '0'},
    {'3', '6', '9', '#'},
    {'A', 'B', 'C', 'D'}};

void kbd_init();
void buscarTeclaAgm();
char get_row();
char kbd_getc();
char letra_teclado_completo();
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void kbd_init()
{
    //las x como salida
    pinMode(22, OUTPUT); //x1
    pinMode(24, OUTPUT); //x2
    pinMode(26, OUTPUT); //x3
    pinMode(28, OUTPUT); //x4
    digitalWrite(30, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(22, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(28, HIGH);
    bits_t_4x4.teclado_completo = 0;
    repeticiones_tecla = 0;
    //led_teclado = 1;
}

char get_row()
{
    if (ROW0 == 0)
    {
        row = 0;
        return 1;
    }
    if (ROW1 == 0)
    {
        row = 1;
        return 1;
    }
    if (ROW2 == 0)
    {
        row = 2;
        return 1;
    }
    if (ROW3 == 0)
    {
        row = 3;
        return 1;
    }
    return 0;
}

char kbd_getc()
{
    // PORTB = 0X0F | PORTB;
    // digitalRead(8) = 0x0F | digitalRead(8);
    // digitalRead(9) = 0x0F | digitalRead(9);
    // digitalRead(10) = 0x0F | digitalRead(10);
    // digitalRead(13) = 0x0F | digitalRead(13);
    digitalWrite(22, LOW);
    digitalWrite(24, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(28, HIGH);
    if (get_row())
    {
        digitalWrite(22, HIGH);
        digitalWrite(24, HIGH);
        digitalWrite(26, HIGH);
        digitalWrite(28, HIGH);
        return KEYS[row][0];
    }
    digitalWrite(22, HIGH);
    digitalWrite(24, LOW);
    digitalWrite(26, HIGH);
    digitalWrite(28, HIGH);
    if (get_row())
    {
        digitalWrite(22, HIGH);
        digitalWrite(24, HIGH);
        digitalWrite(26, HIGH);
        digitalWrite(28, HIGH);
        return KEYS[row][1];
    }
    digitalWrite(22, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(26, LOW);
    digitalWrite(28, HIGH);
    if (get_row())
    {
        digitalWrite(22, HIGH);
        digitalWrite(24, HIGH);
        digitalWrite(26, HIGH);
        digitalWrite(28, HIGH);
        return KEYS[row][2];
    }
    digitalWrite(22, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(28, LOW);
    if (get_row())
    {
        digitalWrite(22, HIGH);
        digitalWrite(24, HIGH);
        digitalWrite(26, HIGH);
        digitalWrite(28, HIGH);
        return KEYS[row][3];
    }
    digitalWrite(22, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(28, HIGH);
    return 'N';
}

char letra_teclado_completo()
{
    repeticiones_tecla++;
    switch (tecla)
    {
    case '-':
        repeticiones_tecla = 0;
    case '+':
    case 'M':
    case 'E':
    case 'V':
        return tecla;
    case '0':
        if (repeticiones_tecla > 2)
            repeticiones_tecla = 1;
        switch (repeticiones_tecla)
        {
        case 1:
            return '0';
        case 2:
            return ' ';
        }
    case '1':
        if (repeticiones_tecla > 4)
            repeticiones_tecla = 1;
        switch (repeticiones_tecla)
        {
        case 1:
            return '1';
        case 2:
            return '_';
        case 3:
            return '.';
        case 4:
            return ',';
        }
        return 'N';
    case '2':
        if (repeticiones_tecla > 4)
            repeticiones_tecla = 1;
        switch (repeticiones_tecla)
        {
        case 1:
            return '2';
        case 2:
            return 'a';
        case 3:
            return 'b';
        case 4:
            return 'c';
        }
        return 'N';
    case '3':
        if (repeticiones_tecla > 4)
            repeticiones_tecla = 1;
        switch (repeticiones_tecla)
        {
        case 1:
            return '3';
        case 2:
            return 'd';
        case 3:
            return 'e';
        case 4:
            return 'f';
        }
        return 'N';
    case '4':
        if (repeticiones_tecla > 4)
            repeticiones_tecla = 1;
        switch (repeticiones_tecla)
        {
        case 1:
            return '4';
        case 2:
            return 'g';
        case 3:
            return 'h';
        case 4:
            return 'i';
        }
        return 'N';
    case '5':
        if (repeticiones_tecla > 4)
            repeticiones_tecla = 1;
        switch (repeticiones_tecla)
        {
        case 1:
            return '5';
        case 2:
            return 'j';
        case 3:
            return 'k';
        case 4:
            return 'l';
        }
        return 'N';
    case '6':
        if (repeticiones_tecla > 4)
            repeticiones_tecla = 1;
        switch (repeticiones_tecla)
        {
        case 1:
            return '6';
        case 2:
            return 'm';
        case 3:
            return 'n';
        case 4:
            return 'o';
        }
        return 'N';
    case '7':
        if (repeticiones_tecla > 5)
            repeticiones_tecla = 1;
        switch (repeticiones_tecla)
        {
        case 1:
            return '7';
        case 2:
            return 'p';
        case 3:
            return 'q';
        case 4:
            return 'r';
        case 5:
            return 's';
        }
        return 'N';
    case '8':
        if (repeticiones_tecla > 4)
            repeticiones_tecla = 1;
        switch (repeticiones_tecla)
        {
        case 1:
            return '8';
        case 2:
            return 't';
        case 3:
            return 'u';
        case 4:
            return 'v';
        }
        return 'N';
    case '9':
        if (repeticiones_tecla > 5)
            repeticiones_tecla = 1;
        switch (repeticiones_tecla)
        {
        case 1:
            return '9';
        case 2:
            return 'w';
        case 3:
            return 'x';
        case 4:
            return 'y';
        case 5:
            return 'z';
        }
        return 'N';
    }
    return 'N';
}

void buscarTeclaAgm()
{
    tecla = kbd_getc();
    contador_tecla_sin_tocar++;
    if (tecla_anterior == 'N')
        contador_tecla_sin_tocar = 2;
    tecla_anterior = tecla;
    if (contador_tecla_sin_tocar > 1)
    {
        contador_tecla_sin_tocar = 0;
        if (tecla != 'N')
        {
            //bocina = !bocina;
            if (tecla_anterior == tecla && bits_t_4x4.teclado_completo)
            {
                tecla = letra_teclado_completo();
            }
            //if(tecla=='E') led_automatico=!led_automatico;
        }
    }
}
#endif
