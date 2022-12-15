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
#include "toolbar.hpp"

/* Plugin widgets */
#include "simple_slider.hpp"
#include "simple_canvas.hpp"
#include "simple_button.hpp"

/* Tools */
#include "brush.hpp"
#include "bucket.hpp"
#include "eraser.hpp"
#include "revealer.hpp"

/* Other */
#include "plugin_manager.hpp"

/* Context functions */
void showWin(DynamicWindow* win);
void showCanvas(DynamicWindow* win);
void pickForgroundColor(ColorPicker* picker);
void pickBackgroundColor(ColorPicker* picker);
void closeApp(App* app);
void canvasSave(Canvas* canvas);
void canvasSaveAs(Canvas* canvas);
void canvasOpen(Canvas* canvas);

#endif // MAIN_HPP
