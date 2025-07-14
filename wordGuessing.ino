#include <LiquidCrystal.h>
#include "words.h"

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int selector_pin = A0;
int selector_value;

const int button_pin = 8;
int button_state;

int word_index;

uint32_t letters_bitmap = 0;

int tries = 0;
int max_tries = 10;

enum b_state {
    PRESSED,
    RELEASED
};

enum g_state {
    PLAYING,
    WIN,
    LOSE
};

int game_state;

int ascii_to_index(char letter) {
    return (int)( letter - 65);
}

char index_to_ascii(int index) {
    return (char)( index + 65 );
}

void load_letter() {
    selector_value = 25 - (int)analogRead(selector_pin)/40;
}

void select_word() {
    word_index = (int)random(word_length);
    tries = 0;
    letters_bitmap = 0;
}

bool check_letter(char letter) {
    return ( ( (uint32_t)((uint32_t)1 << ascii_to_index(letter)) & letters_bitmap) != 0 );
}

int get_good_letter_count() {
    int good_letter = 0;
    int word_length = strlen(words[word_index]);
    for (int i = 0; i < word_length; i++) {
        if ( check_letter(words[word_index][i])) {
            good_letter++;
        }
    }
    return good_letter;
}

int check_win_lose() {
    if (tries > max_tries) return LOSE;
    int word_length = strlen(words[word_index]);
    for (int i = 0; i < word_length; i++) {
        if ( check_letter(words[word_index][i]) == 0) {
            return PLAYING;
        }
    }
    return WIN;
}

void print_obfuscated_word() {
    lcd.setCursor(5, 0);
    int word_length = strlen(words[word_index]);
    for (int i = 0; i < word_length; i++) {
        if ( check_letter(words[word_index][i]) ) {
            lcd.print(words[word_index][i]);
        } else {
            lcd.print('_');
        }
    }
}

void set_letter() {
    if ( check_letter(index_to_ascii(selector_value)) == false) {
        int old_count = get_good_letter_count();
        letters_bitmap |= (uint32_t)1 << (uint32_t)selector_value;
        if (get_good_letter_count() == old_count) {
            tries++;
        }
    }
    /* char charVal[10];
    sprintf(charVal, "%08lX", letters_bitmap);
    Serial.println( charVal ); */
}

void check_button() {
    if ( digitalRead(button_pin) ) {
        if ( button_state == RELEASED) {
            button_state = PRESSED;
            set_letter();
        }
    } else {
        button_state = RELEASED;
    }
}

void setup() {
    Serial.begin(9600);
    // select a random seed
    randomSeed(analogRead(0));
    // select a random word
    select_word();
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
}

void print_screen() {
    // print word as '_' and tried letters
    print_obfuscated_word();
    // print selected letter
    load_letter();
    lcd.setCursor(1, 1);
    lcd.print('<');
    lcd.print( index_to_ascii(selector_value) );
    lcd.print('>');
    lcd.setCursor(5, 1);
    if (check_letter(index_to_ascii(selector_value))) lcd.print('X');
    else lcd.print(' ');
    // print number of tries
    lcd.setCursor(10, 1);
    lcd.print(tries);
    lcd.print('/');
    lcd.print(max_tries);
}

void win_screen() {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("You Win!");
    delay(2000);
    lcd.clear();
    return;
}

void lose_screen() {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("You Lost :(");
    lcd.setCursor(5, 1);
    lcd.print(words[word_index]);
    delay(2000);
    lcd.clear();
    return;
}

void loop() {
    print_screen();
    // check for button press
    check_button();
    game_state = check_win_lose();
    switch (game_state) {
        case PLAYING:
            break;
        case WIN:
            win_screen();
            select_word();
            break;
        case LOSE:
            lose_screen();
            select_word();
            break;
    }
}
