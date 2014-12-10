#include "ui.c"

void print_welcome_message()
{

}

/**
 * Prints to both file and console.
 *
 * @param file a pointer to the file to print to
 * @param format format options
 *
 */
void print(FILE *file, const char *format, ...)
{
    va_list file_va, console_va;

    va_start(console_va, format);

    //print to console
    vprintf(format, console_va);

    //if the pointer to the file object isn't null
    if(file)
    {
        va_copy(file_va, console_va);

        vfprintf(file, file_va);

        va_end(file_va);
    }

    va_end(console_va);
}
