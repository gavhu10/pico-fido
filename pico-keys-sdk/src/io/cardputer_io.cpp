#include <M5Unified.h>

#include "cardputer_io.h"
#include "keyboard.h"
#include "keyboard.h"
#include "display.h"
extern "C"
{
#ifdef SD_SAVE
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdspi_host.h"
#include "fs/file.h"
#endif // SD_SAVE
}

#ifdef SD_SAVE
#define PIN_NUM_MISO (gpio_num_t)39
#define PIN_NUM_MOSI (gpio_num_t)14
#define PIN_NUM_CLK (gpio_num_t)40
#define PIN_NUM_CS (gpio_num_t)12
#endif // SD_SAVE

extern "C" void init_cardputer_hw()
{
    auto cfg = M5.config();
    M5.begin(cfg);
    begin();

    show_logo();

#ifdef SD_SAVE
    esp_err_t ret;

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024};

    sdmmc_card_t *card;
    const char mount_point[] = "/sdcard";

    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };

    ret = spi_bus_initialize(SPI2_HOST, &bus_cfg, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK)
        return;

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = SPI2_HOST;

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;
    slot_config.host_id = SPI2_HOST;

    // Mount the filesystem
    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret == ESP_OK)
    {
        M5.Display.drawString("SD mounted!", 0, 20);
    }
#endif // SD_SAVE
}

extern "C" bool confirm_auth()
{
    bool choice = (!confirm("Authenticate?"));
    displayClearMainView();
    show_logo();
    return choice;
}
