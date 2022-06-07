#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
//#include <glib/gprintf.h>
#include <librsvg/rsvg.h>
//#include <librsvg/rsvg-cairo.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc,char* argv[])
{
    printf("Hello!\n");
    std::string input="tiger.svg";
    std::string output="outtiger.svg";
    if(argc>1){input=argv[1];}
    if(argc>2){output=argv[2];}

    GError *error = NULL;
    RsvgHandle *handle;
    //RsvgDimensionData dim;
    gdouble width, height;
    char *filename = const_cast<char*>(input.c_str());
    char *output_filename =const_cast<char*>(output.c_str());
    cairo_surface_t *surface;
    cairo_t *cr;
    cairo_status_t status;
    int mode = 1;
    char * memblock;
    streampos size;

    //g_type_init ();

    // RsvgHandle *rsvg_handle_new_from_data (const guint8 * data, gsize data_len, GError ** error);
    // read svg file
    ifstream file (filename, ios::in|ios::binary|ios::ate);
    printf("Try to read file!\n");
    if (file.is_open())
    {
      size = file.tellg();
      memblock = new char [size];
      file.seekg (0, ios::beg);
      file.read (memblock, size);
      file.close();
      printf("SVG File Content!\n");
      //printf(memblock);


    }

    //rsvg_set_default_dpi (72.0);
    handle = rsvg_handle_new_from_data((const guint8 *)memblock, (gsize)size, &error);
    //handle = rsvg_handle_new_from_file (filename, &error);
    if (error != NULL)
    {
        printf("rsvg_handle_new_from_file error!\n");
        printf (error->message);
        return 1;
    }

    //rsvg_handle_get_dimensions (handle, &dim);
    rsvg_handle_get_intrinsic_size_in_pixels(handle,&width,&height);
    //width = dim.width;
    //height = dim.height;

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);

    cr = cairo_create (surface);
    RsvgRectangle viewport;
    viewport.x=0;
    viewport.y=0;
    viewport.width=width;
    viewport.height=height;
    rsvg_handle_render_document (handle, cr,&viewport,NULL);

    status = cairo_status (cr);
    if (status)
    {
        printf("cairo_status!\n");
        printf (cairo_status_to_string (status));
        return 1;
    }

    // unsigned char * cairo_image_surface_get_data (cairo_surface_t *surface);
    cairo_surface_write_to_png (surface, output_filename);

    int raw_width = cairo_image_surface_get_width (surface);
    int raw_height = cairo_image_surface_get_height (surface);
    int row_byte_size = cairo_image_surface_get_stride (surface);
    printf("\nWIDTH: %d, HEIGHT: %d, row_bytes=%d\n", raw_width, raw_height, row_byte_size);

    unsigned char * raw_buffer = cairo_image_surface_get_data(surface);

    FILE * pFile;
    pFile = fopen ("myfile.bin", "wb");
    fwrite (raw_buffer , sizeof(char), raw_height*row_byte_size, pFile);
    fclose (pFile);

    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    delete[] memblock;

    return 0;
}
