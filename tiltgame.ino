#include <Adafruit_CircuitPlayground.h>

int xacc, yacc, victorycount = 0;
bool win = false;
int xtarget, ytarget;
uint32_t magenta = CircuitPlayground.strip.Color(255, 0, 255);
uint32_t red = CircuitPlayground.strip.Color(255, 0, 0);
uint32_t green = CircuitPlayground.strip.Color(0, 255, 0);
uint32_t blue = CircuitPlayground.strip.Color(0, 0, 255);

void resetGame() {
  victorycount = 0;
  win = false;
  xtarget = random(-8, 8);
  ytarget = random(-8, 8);
}

void setXcolor(uint32_t color) {
  for (int i = 0; i < 5; i++) {
    CircuitPlayground.strip.setPixelColor(i, color);
  }
}
void setYcolor(uint32_t color) {
  for (int i = 5; i < 10; i++) {
    CircuitPlayground.strip.setPixelColor(i, color);
  }
}

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(10);
  
  resetGame();
}

void loop() {
  xacc = CircuitPlayground.motionX();
  yacc = CircuitPlayground.motionY();

  if (win) {
    setXcolor(red);
    setYcolor(red);

    victorycount++;
    if (victorycount > 500) {
      resetGame();
    }
    
    
  } else {
    if (xacc == xtarget) {
      setXcolor(magenta);
    } else {
      setXcolor(blue);
      victorycount = 0;
    }

    if (yacc == ytarget) {
      setYcolor(magenta);
    } else {
      setYcolor(blue);
      victorycount = 0;
    }

    if (xacc == xtarget && yacc == ytarget) {
      victorycount++;
      setXcolor(green);
      setYcolor(green);

      if (victorycount > 200) {
        win = true;
      }
    }
  }

  CircuitPlayground.strip.show();
  delay(10);
}
