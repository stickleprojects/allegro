# Code for transparent images
var img = al_load_image("myimage.bmp");
var transparentRgb = al_map_rgb(200,2,2);
al_convert_mask_to_alpha (img, transparentRgb);

# display background and move a sprite
