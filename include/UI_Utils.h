#ifndef UI_UTILS_H
#define UI_UTILS_H

#include "common.h"

namespace UI_Utils
{
    void user_intro_display(vector<string> m_props, vector<string> m_vals);
    char user_menu_display();
    bool module_selector(char user_choice, Dataset* ds);
}

#endif