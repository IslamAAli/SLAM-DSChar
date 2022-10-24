from cv2 import cv2
import numpy as np
import os
import glob
import math

# ===============================================================================
# apply the masking on the image 
def img_masking(img, blur_img, mask, invert=False):
    if (invert):
        return np.where(mask!=np.array([255, 255, 255]), img, blur_img)
    else:
        return np.where(mask==np.array([255, 255, 255]), img, blur_img)

# ===============================================================================
# generate the blurred image for a given image
def blur_img(img):
    return cv2.GaussianBlur(img, (25, 25), 0)

# ===============================================================================
def create_mask(type, img_size):
    # create the mask
    mask = np.zeros(img_size, dtype=np.uint8)

    # define the mask coverage based on case
    if (type == 1):
        x1 = math.floor(img.shape[1]/2)
        y1 = math.floor(0)
        x2 = math.floor(img.shape[1]-1)
        y2 = math.floor(img.shape[0]-1)
        mask = cv2.rectangle(mask, (x1, y1), (x2, y2), (255, 255, 255), -1)
    elif(type == 2):
        x1 = math.floor(img.shape[1]/2)
        y1 = math.floor(0)
        x2 = math.floor((img.shape[1])-1)
        y2 = math.floor((img.shape[0]/2)-1)
        mask = cv2.rectangle(mask, (x1, y1), (x2, y2), (255, 255, 255), -1)
    elif(type == 3):   
        x1 = math.floor(0)
        y1 = math.floor(0)
        x2 = math.floor((img.shape[1])-1)
        y2 = math.floor((img.shape[0])-1)
        mask = cv2.rectangle(mask, (x1, y1), (x2, y2), (255, 255, 255), -1)

    return mask

def create_checker_board(img_size, block_size):
    print(img_size)
    h = math.floor(img_size[0]/10)
    w = math.floor(img_size[1]/10)
    checkerboard = 255.0 * np.kron([[1, 0] * (w//2), [0, 1] * (w//2)] * (h//2), np.ones((block_size, block_size)))
    print(checkerboard)
    return checkerboard

# ===============================================================================
def toplevel_blur(img, img_blur, mask_option, img_tag, invert = False):
    # applying a mask (half image blur)
    mask = create_mask(mask_option, img.shape)
    print(mask.shape)

    # apply the mask and get the output
    out_img = img_masking(img, img_blur, mask, invert)

    # save file to sample_images folder
    cv2.imwrite(dirname+'blur_out/'+os.path.splitext(name)[0]+img_tag, out_img)

    cv2.imshow("", out_img)
    cv2.waitKey(0)

# ===============================================================================
# base directory for the framework
dirname = os.path.dirname(__file__)+'/../../in_data/sample_images/'

# read the images from the input folder
png_files = []
file_names = []
for file in glob.glob(dirname+"*.png"):
    png_files.append(file)
    file_names.append(os.path.basename(file))

# loop over files and apply partial blurring
for img_file, name in zip(png_files, file_names):
    # read the image file
    img = cv2.imread(img_file)

    # get blurred image
    img_blur = blur_img(img)

    toplevel_blur(img, img_blur, 1, '_0p50_blur.png', True)
    toplevel_blur(img, img_blur, 2, '_0p75_blur.png', False)
    toplevel_blur(img, img_blur, 2, '_0p25_blur.png', True)
    toplevel_blur(img, img_blur, 3, '_0p00_blur.png', True)

    # toplevel_blur(img, img_blur, 3, '_checker_blur.png', True)

    # # visualization
    # cv2.imshow("", out_img)
    # cv2.waitKey(0)

