#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>

#define BACKGROUND_COLOR TFT_BLACK
#define PRIMARY_COLOR 0x04df
#define RECT_COLOR_DARK 0x0841
#define RECT_COLOR_LIGHT 0xd69a
#define TEXT_COLOR 0xef7d
#define TEXT_COLOR_ALT TFT_DARKGRAY

#define DEFAULT_MARGIN 5
#define DEFAULT_ROUND_RECT 5

void displayInit();
void displayClearMainView(uint8_t offsetY = 0);
extern "C" void showMessage(const char *message);
extern "C" void show_logo(void);
unsigned int selectFromList(std::vector<std::string> items, unsigned int startIndex = 0);
std::string getInput(std::string);
bool confirm(std::string prompt);

// Utility Function (forward declaration if needed)
void drawRect(bool selected, uint8_t margin, uint16_t startY, uint16_t sizeX, uint16_t sizeY);

#endif // DISPLAY_CONFIG_H
