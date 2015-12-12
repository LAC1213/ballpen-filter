#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>

#define PLUGIN_NAME "ballpen-filter"

typedef struct
{
    double density;
    double rnJesusFactor;
    int strokeLen;
    int strokeHardness;
} BallpenSettings;
static void query (void);

static void run (
    const gchar *name,
    gint nparams,
    const GimpParam *param,
    gint *nreturn_vals,
    GimpParam **return_vals
);

const GimpPlugInInfo PLUG_IN_INFO = {
    NULL,  /* init_proc  */
    NULL,  /* quit_proc  */
    query, /* query_proc */
    run,   /* run_proc   */
};

MAIN ()