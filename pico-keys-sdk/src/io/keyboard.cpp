#include "keyboard.h"
#include <memory>
#include <M5Unified.h>

#define delay(n) vTaskDelay(pdMS_TO_TICKS((n)))

Keyboard_Class board;

void begin()
{
    board = Keyboard_Class();
    board.begin();
}

char configInputHandler()
{
    // Update keyboard state
    M5.update();
    board.updateKeyList();
    board.updateKeysState();

    if (board.isChange())
    {

        if (board.isPressed())
        {
            Keyboard_Class::KeysState status = board.keysState();

            if (status.enter)
            {
                return KEY_OK;
            }
            if (board.isKeyPressed(KEY_ARROW_LEFT))
            {
                return KEY_ARROW_LEFT;
            }
            if (board.isKeyPressed(KEY_ARROW_RIGHT))
            {
                return KEY_ARROW_RIGHT;
            }
            if (board.isKeyPressed(KEY_ARROW_UP))
            {
                return KEY_ARROW_UP;
            }
            if (board.isKeyPressed(KEY_ARROW_DOWN))
            {
                return KEY_ARROW_DOWN;
            }
        }
        delay(10); // debounce
    }
    return KEY_NONE;
}

char promptInputHandler()
{
    // Update keyboard state
    M5.update();
    board.updateKeyList();
    board.updateKeysState();

    // Bouton G0
    if (M5.BtnA.isPressed())
    {
        delay(100); // debounce
        return KEY_RETURN;
    }

    if (board.isChange())
    {

        if (board.isPressed())
        {
            Keyboard_Class::KeysState status = board.keysState();

            if (status.enter)
            {
                return KEY_OK;
            }
            else if (status.del)
            {
                return KEY_DEL;
            }

            for (auto c : status.word)
            {
                return c; // retourner le premier char saisi
            }
        }
        delay(10); // debounce
    }
    return KEY_NONE;
}