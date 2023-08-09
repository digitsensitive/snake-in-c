#pragma once

enum LANGUAGE { DE = 1, EN = 2 };

struct localized_text {
    int language;
    const char* identifier;
    const char* text;
};

extern struct localized_text LOCALES[];

void set_language(int language);
const char* get_localized_text(const char* identifier);