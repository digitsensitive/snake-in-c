#include "languages.h"

#include <string.h>

// english is the default language
int current_language = EN;

struct localized_text LOCALES[] = {
    {DE, "snake_description", "Snake programmiert in C für das Terminal."},
    {EN, "snake_description", "Snake written in C for the terminal."},
    {DE, "score_text", "Punktzahl:"},
    {EN, "score_text", "Score:"},
};

// set new language
void set_language(int language) { current_language = language; }

const char* get_localized_text(const char* identifier) {
    // calculate length of text elements
    const int LOCALES_LENGTH = sizeof(LOCALES) / sizeof(LOCALES[0]);

    // go through text elements
    for (int i = 0; i < LOCALES_LENGTH; i++) {
        if (LOCALES[i].language != current_language) {
            // text element is not current language
            continue;
        }
        if (strcmp(LOCALES[i].identifier, identifier) == 0) {
            // text element found
            return LOCALES[i].text;
        }
    }

    // text element does not exist
    return "Translation not available";
}