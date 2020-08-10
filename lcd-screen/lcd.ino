#include <CheapLCD.h>
#define GROUND 1
#define JUMP 0
CheapLCD lcd;

void setup() {
    Serial.begin(9600);
    lcd.begin();
    lcd.setCursor(3, 1);
    lcd.print("p");
}

int enemyPosition = 16;
int player_position = 3;
int player_state = GROUND;
int player_state_drawn_on_screen = GROUND;
unsigned long last_jump = 0;
unsigned long JUMP_TIME = 1000;
unsigned long JUMP_COOLDOWN = 100;

void jump() {
    if (millis() - last_jump > JUMP_TIME + JUMP_COOLDOWN) {
        player_state = JUMP;
        last_jump = millis();
    }
}

void check_jump() {
    unsigned long current_time = millis();
    if (current_time - last_jump > JUMP_TIME) {
        player_state = GROUND;
    }
}
void draw_player() {
    if (player_state != player_state_drawn_on_screen) {
        lcd.clear();
        switch (player_state) {
        case GROUND:
            lcd.setCursor(player_position, GROUND);
            break;
        case JUMP:
            lcd.setCursor(player_position, JUMP);
        }
        lcd.print("p");
        player_state_drawn_on_screen = player_state;
    }
}

void loop() {
    CLCD_Button_t pressed_button = lcd.readButton();
    switch (pressed_button) {
    case BTN_UP:
        jump();
        break;
    }
    if (player_state == JUMP) {
        check_jump();
    }
    draw_player();
}
