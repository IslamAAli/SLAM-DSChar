# Importing Image class from PIL module
from PIL import Image
import glob
import os

dirname = os.path.dirname(__file__)+'/..'

# Opens a image in RGB mode
for file in glob.glob(dirname+"/../out_data/manual_figs_cropped/*.png"):
    file_name = os.path.basename(file)
    print('--> Cropping: '+ file_name)
    im = Image.open(file)

    width, height = im.size

    # Setting the points for cropped image
    left = 150
    top = 100
    right = width-175
    bottom = height-55
    
    # Cropped image of above dimension
    # (It will not change original image)
    im1 = im.crop((left, top, right, bottom))
    
    im1.save(dirname+"/../out_data/manual_figs/"+file_name)

    # Shows the image in image viewer
    # im1.show()

print('\n## DONE !! ##')