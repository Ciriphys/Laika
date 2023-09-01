#include <string.h>

#include "application.h"
#include "converter.h"

int main(int argc, char** argv)
{
    application_t* context = create_application_context(argv[0], (u32_t)strlen(argv[0]));
    application_run(context);
    destroy_application_context(context);

    return 0;
}
