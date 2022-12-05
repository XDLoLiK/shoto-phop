#ifndef MAIN_HPP
#define MAIN_HPP

/* App */
#include "app.hpp"

/* Widgets */
#include "button.hpp"
#include "frame.hpp"
#include "canvas.hpp"
#include "drop_list.hpp"
#include "context_button.hpp"
#include "dynamic_window.hpp"
#include "color_chooser.hpp"

/* Tools */
#include "brush.hpp"
#include "bucket.hpp"
#include "eraser.hpp"
#include "revealer.hpp"

/* Other */
#include "plugin_manager.hpp"

/* Context functions */
void showWin(DynamicWindow* win);
void pickColor(ColorPicker* picker);
void closeApp(App* app);

#endif // MAIN_HPP
