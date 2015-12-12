#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ballpenfilter.h"

static gboolean ballpen_dialog( GimpDrawable * drawable, BallpenSettings * settings )
{
    GtkWidget *dialog;
    GtkWidget *main_vbox;
    GtkWidget *main_hbox;
    GtkWidget *frame;
    GtkWidget *strokeLen_label;
    GtkWidget *strokeHardness_label;
    GtkWidget *density_label;
    GtkWidget *rnJesus_label;
    GtkWidget *alignment;
    GtkWidget *strokeLen_spinbutton;
    GtkWidget *strokeHardness_spinbutton;
    GtkObject *strokeLen_spinbutton_adj;
    GtkObject *strokeHardness_spinbutton_adj;
    GtkWidget *density_spinbutton;
    GtkWidget *rnJesus_spinbutton;
    GtkObject *density_spinbutton_adj;
    GtkObject *rnJesus_spinbutton_adj;
    GtkWidget *frame_label;
    gboolean   run;
    
    gimp_ui_init ("ballpen", FALSE);
    
    dialog = gimp_dialog_new ("Ballpen Filter", "ballpen",
                              NULL, 0,
                              gimp_standard_help_func, PLUGIN_NAME,
                              
                              GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                              GTK_STOCK_OK,     GTK_RESPONSE_OK,
                              
                              NULL);
    
    main_vbox = gtk_vbox_new (FALSE, 6);
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG (dialog)->vbox), main_vbox);
    gtk_widget_show (main_vbox);
    
    frame = gtk_frame_new (NULL);
    gtk_widget_show (frame);
    gtk_box_pack_start (GTK_BOX (main_vbox), frame, TRUE, TRUE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (frame), 6);
    
    alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
    gtk_widget_show (alignment);
    gtk_container_add (GTK_CONTAINER (frame), alignment);
    gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 6, 6, 6, 6);
    
    main_hbox = gtk_hbox_new (FALSE, 0);
    gtk_widget_show (main_hbox);
    gtk_container_add (GTK_CONTAINER (alignment), main_hbox);
    
    density_label = gtk_label_new_with_mnemonic ("_Density:");
    gtk_widget_show (density_label);
    gtk_box_pack_start (GTK_BOX (main_hbox), density_label, FALSE, FALSE, 6);
    gtk_label_set_justify (GTK_LABEL (density_label), GTK_JUSTIFY_RIGHT);
    
    density_spinbutton_adj = gtk_adjustment_new (settings->density, 0.05, 10, 0.01, 0.1, 0);
    density_spinbutton = gtk_spin_button_new (GTK_ADJUSTMENT (density_spinbutton_adj), 0.01, 2);
    gtk_widget_show (density_spinbutton);
    gtk_box_pack_start (GTK_BOX (main_hbox), density_spinbutton, FALSE, FALSE, 6);
    gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (density_spinbutton), TRUE);
    
    rnJesus_label = gtk_label_new_with_mnemonic ("_RNJesus:");
    gtk_widget_show (rnJesus_label);
    gtk_box_pack_start (GTK_BOX (main_hbox), rnJesus_label, FALSE, FALSE, 6);
    gtk_label_set_justify (GTK_LABEL (rnJesus_label), GTK_JUSTIFY_RIGHT);
    
    rnJesus_spinbutton_adj = gtk_adjustment_new (settings->rnJesusFactor, 0.05, 10, 0.01, 0.1, 0);
    rnJesus_spinbutton = gtk_spin_button_new (GTK_ADJUSTMENT (rnJesus_spinbutton_adj), 0.01, 2);
    gtk_widget_show (rnJesus_spinbutton);
    gtk_box_pack_start (GTK_BOX (main_hbox), rnJesus_spinbutton, FALSE, FALSE, 6);
    gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (rnJesus_spinbutton), TRUE);
    
    strokeLen_label = gtk_label_new_with_mnemonic ("_StrokeLen:");
    gtk_widget_show (strokeLen_label);
    gtk_box_pack_start (GTK_BOX (main_hbox), strokeLen_label, FALSE, FALSE, 6);
    gtk_label_set_justify (GTK_LABEL (strokeLen_label), GTK_JUSTIFY_RIGHT);
    
    strokeLen_spinbutton_adj = gtk_adjustment_new (settings->strokeLen, 1, 50, 1, 5, 0);
    strokeLen_spinbutton = gtk_spin_button_new (GTK_ADJUSTMENT (strokeLen_spinbutton_adj), 1, 0);
    gtk_widget_show (strokeLen_spinbutton);
    gtk_box_pack_start (GTK_BOX (main_hbox), strokeLen_spinbutton, FALSE, FALSE, 6);
    gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (strokeLen_spinbutton), TRUE);
    
    strokeHardness_label = gtk_label_new_with_mnemonic ("_StrokeHardness:");
    gtk_widget_show (strokeHardness_label);
    gtk_box_pack_start (GTK_BOX (main_hbox), strokeHardness_label, FALSE, FALSE, 6);
    gtk_label_set_justify (GTK_LABEL (strokeHardness_label), GTK_JUSTIFY_RIGHT);
    
    strokeHardness_spinbutton_adj = gtk_adjustment_new (settings->strokeHardness, 1, 255, 1, 10, 0);
    strokeHardness_spinbutton = gtk_spin_button_new (GTK_ADJUSTMENT (strokeHardness_spinbutton_adj), 1, 0);
    gtk_widget_show (strokeHardness_spinbutton);
    gtk_box_pack_start (GTK_BOX (main_hbox), strokeHardness_spinbutton, FALSE, FALSE, 6);
    gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (strokeHardness_spinbutton), TRUE);
    
    frame_label = gtk_label_new ("Modify Ballpen Settings");
    gtk_widget_show (frame_label);
    gtk_frame_set_label_widget (GTK_FRAME (frame), frame_label);
    gtk_label_set_use_markup (GTK_LABEL (frame_label), TRUE);
    
    g_signal_connect (strokeLen_spinbutton_adj, "value_changed",
                      G_CALLBACK (gimp_int_adjustment_update),
                      &settings->strokeLen);
    
    g_signal_connect (strokeHardness_spinbutton_adj, "value_changed",
                      G_CALLBACK (gimp_int_adjustment_update),
                      &settings->strokeHardness);
    
    g_signal_connect (density_spinbutton_adj, "value_changed",
                      G_CALLBACK (gimp_double_adjustment_update),
                      &settings->density);
    
    g_signal_connect (rnJesus_spinbutton_adj, "value_changed",
                      G_CALLBACK (gimp_double_adjustment_update),
                      &settings->rnJesusFactor);
    
    gtk_widget_show (dialog);
    
    run = (gimp_dialog_run (GIMP_DIALOG (dialog)) == GTK_RESPONSE_OK);
    
    gtk_widget_destroy (dialog);
    
    return run;
}

static double sqrt1213( double a )
{
    double x = a;
    for( int i = 0 ; i < 10 ; ++i )
    {
        x = (x*x + a)/(2*x);
    }
    return x;
}

static void query()
{
    static GimpParamDef args[] = {
        {
            GIMP_PDB_INT32,
            "run-mode",
            "Run mode"
        },
        {
            GIMP_PDB_IMAGE,
            "image",
            "Input image"
        },
        {
            GIMP_PDB_DRAWABLE,
            "drawable",
            "Input drawable"
        }
    };
    
    gimp_install_procedure(
        PLUGIN_NAME,
        "Ballpen filter",
        "Turns an image into a ballpen drawing",
        "LAC1213",
        "Copyright LAC1213",
        "2015",
        "Ballpen filter...",
        "RGB*, GRAY*",
        GIMP_PLUGIN,
        G_N_ELEMENTS( args ), 
        0,
        args,
        NULL
    );
    
    gimp_plugin_menu_register (PLUGIN_NAME, "<Image>/Filters/Artistic" );
}

static void ballpenFilter( GimpDrawable * drawable, BallpenSettings * settings ) ;

static void run( const gchar *name, gint nparams, const GimpParam * param, gint * nreturnvals, GimpParam ** returnvals )
{
    static BallpenSettings currentSettings = {
        .density = 1.5,
        .rnJesusFactor = 0.5,
        .strokeLen = 10,
        .strokeHardness = 5
    };
    
    srand( time( 0 ) );
    static GimpParam  values[1];
    GimpPDBStatusType status = GIMP_PDB_SUCCESS;
    GimpRunMode       run_mode;
    GimpDrawable * drawable;
    
    /* Setting mandatory output values */
    *nreturnvals = 1;
    *returnvals  = values;

    values[0].type = GIMP_PDB_STATUS;
    values[0].data.d_status = status;
    
    /* Getting run_mode - we won't display a dialog if 
     * we are in NONINTERACTIVE mode */
    run_mode = param[0].data.d_int32;
    
    drawable = gimp_drawable_get( param[2].data.d_drawable );
    
    switch( run_mode )
    {
        case GIMP_RUN_INTERACTIVE:
            gimp_get_data( PLUGIN_NAME, &currentSettings );
            
            if( !ballpen_dialog( drawable, &currentSettings ) )
                return;
            break;
        case GIMP_RUN_NONINTERACTIVE:
            if( nparams != 7 )
                status = GIMP_PDB_CALLING_ERROR;
            if( status == GIMP_PDB_SUCCESS )
            {
                currentSettings.density = param[3].data.d_float;
                currentSettings.rnJesusFactor = param[4].data.d_float;
                currentSettings.strokeHardness = param[5].data.d_int32;
                currentSettings.strokeLen = param[6].data.d_int32;
            }
            break;
        case GIMP_RUN_WITH_LAST_VALS:
            gimp_get_data( PLUGIN_NAME, &currentSettings );
            break;
    }
    
    ballpenFilter( drawable, &currentSettings );
    
    gimp_displays_flush();
    gimp_drawable_detach( drawable );
    
    if( run_mode == GIMP_RUN_INTERACTIVE )
        gimp_set_data( PLUGIN_NAME, &currentSettings, sizeof(BallpenSettings) );
}

static double sqrtApprox( double a )
{
    double x = a;
    for( int i = 0 ; i < 10 ; ++i )
        x = (x*x + a)/(2*x);
    return x;
}

static void ballpenFilter( GimpDrawable * drawable, BallpenSettings * settings )
{
    gimp_progress_init( "Ballpen Filter..." );
    
    gint x1, y1, x2, y2;
    gimp_drawable_mask_bounds( drawable->drawable_id, &x1, &y1, &x2, &y2 );
    
    gint w = x2 - x1;
    gint h = y2 - y1;
    
    GimpPixelRgn in, out;
    gimp_pixel_rgn_init( &in, drawable, x1, y1, w, h, false, false );
    gimp_pixel_rgn_init( &out, drawable, x1, y1, w, h, true, true );
    
    gint channels = gimp_drawable_bpp( drawable->drawable_id );
    
    uint8_t * srcPixels = malloc( w*h*channels );
    uint8_t * dstPixels = malloc( w*h*channels );
    
    gimp_pixel_rgn_get_rect( &in, srcPixels, x1, y1, w, h );
    
    /* process Pixels */
    double x = 0.5 * w;
    double y = 0.5 * h;
    double dx = 1;
    double dy = 0;
    
    memset( dstPixels, 0xff, w*h*channels );
    
    size_t strokes = settings->density*w*h;
    
    for( int i = 0 ; i < strokes ; ++i )
    {
        if( i % 100 == 0 )
            gimp_progress_update( (double) i / strokes );
        
        int idx = channels*(w*(int)y + (int)x);
        
        dx = 0;
        dy = 0;
        
        if( x + 1 < w )
            for( int j = 0 ; j < channels ; ++j )
                dx -= srcPixels[ idx + channels + j ];

        if( x >= 1 )
            for( int j = 0 ; j < channels ; ++j )
                dx += srcPixels[ idx - channels + j ];
        
        if( y + 1 < h )
            for( int j = 0 ; j < channels ; ++j )
                dy -= srcPixels[ idx + w*channels + j ];

        if( y >= 1 )
            for( int j = 0 ; j < channels ; ++j )
                dy += srcPixels[ idx - w*channels + j ];
        
        dx += settings->rnJesusFactor*channels*255*((double)rand() / RAND_MAX - 0.5);
        dy += settings->rnJesusFactor*channels*255*((double)rand() / RAND_MAX - 0.5);
        
        double l = sqrtApprox( dx*dx + dy*dy );
        dx /= l;
        dy /= l;
        
        for( int k = 0 ; k < settings->strokeLen ; ++k )
        {
            idx = channels*(w*(int)y + (int)x);
            for( int j = 0 ; j < channels ; ++j )
            {
                if(dstPixels[idx + j] >= settings->strokeHardness)
                    dstPixels[idx + j] -= settings->strokeHardness;
            }
            
            x += dx;
            if( x > w )
                x -= w;
            if( x < 0 )
                x += w;
            y += dy;
            if( y > h )
                y -= h;
            if( y < 0 )
                y += h;
        }
    }
    

    gimp_pixel_rgn_set_rect( &out, dstPixels, x1, y1, w, h );
    
    free( srcPixels );
    free( dstPixels );
    
    gimp_drawable_flush( drawable );
    gimp_drawable_merge_shadow( drawable->drawable_id, true );
    gimp_drawable_update( drawable->drawable_id, x1, y1, w, h );
}