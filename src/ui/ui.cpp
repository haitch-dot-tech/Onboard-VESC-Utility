/**
 * ui.cpp
 * - Has all of the functions for controlling the display and LVGL
 */

#include "ui.hpp"

/* LVGL display */
lv_display_t *disp;

/* LVGL variables */
lv_obj_t *statusScreen;
lv_obj_t *rpmScreen;
lv_obj_t *speedScreen;
lv_obj_t *tempScreen;
lv_obj_t *dutyScreen;
lv_obj_t *ampScreen;
lv_obj_t *wattScreen;

lv_obj_t *status;
lv_obj_t *id;
lv_obj_t *voltage;
lv_obj_t *rpm;
lv_obj_t *speed;
lv_obj_t *tempFET;
lv_obj_t *tempMotor;
lv_obj_t *duty;
lv_obj_t *tacho;
lv_obj_t *ampHours;
lv_obj_t *ampHoursCharged;
lv_obj_t *wattHours;
lv_obj_t *wattHoursCharged;

uint32_t draw_buf[(WIDTH * HEIGHT / 10 * (LV_COLOR_DEPTH / 8)) / 4];

TFT_eSPI tft = TFT_eSPI();

static uint32_t lv_tick(void)
{
    return millis();
}

void ui_hardware_init()
{
    tft.begin();
    tft.setRotation(0);
}

void ui_init()
{
    lv_init();
    lv_tick_set_cb(lv_tick);

    disp = lv_tft_espi_create(HEIGHT, WIDTH, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);
    lv_display_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, &lv_font_montserrat_14);
    lv_display_set_theme(dispp, theme);

    statusScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(statusScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(statusScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_flag(statusScreen, LV_OBJ_FLAG_SCROLLABLE);

    rpmScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(rpmScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(rpmScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_flag(rpmScreen, LV_OBJ_FLAG_SCROLLABLE);

    speedScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(speedScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(speedScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_flag(speedScreen, LV_OBJ_FLAG_SCROLLABLE);

    tempScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(tempScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(tempScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_flag(tempScreen, LV_OBJ_FLAG_SCROLLABLE);

    dutyScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(dutyScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(dutyScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_flag(dutyScreen, LV_OBJ_FLAG_SCROLLABLE);

    ampScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(ampScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ampScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_flag(ampScreen, LV_OBJ_FLAG_SCROLLABLE);

    wattScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(wattScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(wattScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_flag(wattScreen, LV_OBJ_FLAG_SCROLLABLE);

    status = lv_label_create(statusScreen);
    lv_obj_align(status, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_text_font(status, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(status, "Disconnected");

    id = lv_label_create(statusScreen);
    lv_obj_align(id, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_text_font(id, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(id, "ID: 0");

    voltage = lv_label_create(statusScreen);
    lv_obj_align(voltage, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_set_style_text_font(voltage, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(voltage, "49.84V");

    rpm = lv_label_create(rpmScreen);
    lv_obj_align(rpm, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_font(rpm, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(rpm, "9652 RPM");

    speed = lv_label_create(speedScreen);
    lv_obj_align(speed, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_font(speed, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(speed, "61.2km/h");

    tempFET = lv_label_create(tempScreen);
    lv_obj_align(tempFET, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_text_font(tempFET, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(tempFET, "FET: 34.08°C");

    tempMotor = lv_label_create(tempScreen);
    lv_obj_align(tempMotor, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_text_font(tempMotor, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(tempMotor, "MTR: 52.17°C");

    duty = lv_label_create(dutyScreen);
    lv_obj_align(duty, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_text_font(duty, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(duty, "50.00%");

    tacho = lv_label_create(dutyScreen);
    lv_obj_align(tacho, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_text_font(tacho, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(tacho, "36329");

    ampHours = lv_label_create(ampScreen);
    lv_obj_align(ampHours, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_text_font(ampHours, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ampHours, "0.20Ah");

    ampHoursCharged = lv_label_create(ampScreen);
    lv_obj_align(ampHoursCharged, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_text_font(ampHoursCharged, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ampHoursCharged, "0.00AhC");

    wattHours = lv_label_create(wattScreen);
    lv_obj_align(wattHours, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_text_font(wattHours, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(wattHours, "6.00Wh");

    wattHoursCharged = lv_label_create(wattScreen);
    lv_obj_align(wattHoursCharged, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_text_font(wattHoursCharged, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(wattHoursCharged, "0.03WhC");
}

void ui_load_screen(int scr)
{
    switch (scr)
    {
        case 1: lv_screen_load_anim(statusScreen,  LV_SCR_LOAD_ANIM_MOVE_LEFT, SCREEN_LOAD_DELEAY, 0, false); break;
        case 2: lv_screen_load_anim(rpmScreen,     LV_SCR_LOAD_ANIM_MOVE_LEFT, SCREEN_LOAD_DELEAY, 0, false); break;
        case 3: lv_screen_load_anim(speedScreen,   LV_SCR_LOAD_ANIM_MOVE_LEFT, SCREEN_LOAD_DELEAY, 0, false); break;
        case 4: lv_screen_load_anim(tempScreen,    LV_SCR_LOAD_ANIM_MOVE_LEFT, SCREEN_LOAD_DELEAY, 0, false); break;
        case 5: lv_screen_load_anim(dutyScreen,    LV_SCR_LOAD_ANIM_MOVE_LEFT, SCREEN_LOAD_DELEAY, 0, false); break;
        case 6: lv_screen_load_anim(ampScreen,     LV_SCR_LOAD_ANIM_MOVE_LEFT, SCREEN_LOAD_DELEAY, 0, false); break;
        case 7: lv_screen_load_anim(wattScreen,    LV_SCR_LOAD_ANIM_MOVE_LEFT, SCREEN_LOAD_DELEAY, 0, false); break;
        default: lv_screen_load_anim(statusScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, SCREEN_LOAD_DELEAY, 0, false);
    }
}

void ui_update()
{
    lv_timer_handler();
}

void ui_update(struct update_data d)
{
    lv_label_set_text_fmt(status, "%s", (d.connected) ? "Connected" : "Disconnected");
    lv_label_set_text_fmt(id, "ID: %d", d.id);
    lv_label_set_text_fmt(voltage, "%02d.%02dV", (int)d.voltage, (int)((d.voltage - (int)d.voltage) * 100.0));
    lv_label_set_text_fmt(rpm, "%d RPM", d.rpm);
    lv_label_set_text_fmt(speed, "%02dkm/h", (int)(d.speed + 0.5));
    lv_label_set_text_fmt(tempFET, "FET: %02d.%02d°C", (int)d.tempFET, (int)((d.tempFET - (int)d.tempFET) * 100.0));
    lv_label_set_text_fmt(tempMotor, "MTR: %02d.%02d°C", (int)d.tempMTR, (int)((d.tempMTR - (int)d.tempMTR) * 100.0));
    lv_label_set_text_fmt(duty, "%02d%%", (int)(d.duty * 100.0 + 0.5));
    lv_label_set_text_fmt(tacho, "%d", (int)d.tacho, (int)((d.tacho - (int)d.tacho) * 100.0));
    lv_label_set_text_fmt(ampHours, "%02d.%02dAh", (int)d.ampHours, (int)((d.ampHours - (int)d.ampHours) * 100.0));
    lv_label_set_text_fmt(ampHoursCharged, "%02d.%02dAhC", (int)d.ampHoursCharged, (int)((d.ampHoursCharged - (int)d.ampHoursCharged) * 100.0));
    lv_label_set_text_fmt(wattHours, "%02d.%02dWh", (int)d.wattHours, (int)((d.wattHours - (int)d.wattHours) * 100.0));
    lv_label_set_text_fmt(wattHoursCharged, "%02d.%02dWhC", (int)d.wattHoursCharged, (int)((d.wattHoursCharged - (int)d.wattHoursCharged) * 100.0));

    lv_timer_handler();
}
