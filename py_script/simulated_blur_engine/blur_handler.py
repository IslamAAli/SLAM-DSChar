import sys
import os
import cv2 

sys.path.insert(0, os.path.dirname(__file__)+'/../tools/')
import sys_utils 
import blur_detector 


# read files and filenames for testing
files, file_names = sys_utils.read_files_from_path('/../../in_data/sample_images/blur_out/', "*.png")

files, file_names = zip(*sorted(zip(files, file_names)))
# loop over files and filenames and apply the blurring detection engine
for f, fn in zip(files, file_names):
    img = cv2.imread(f)
    img_gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)

    img_heatmap, img_BW, image_blur_score, blur_percentage, blur_result = blur_detector.segmented_blur_detector(img_gray, 50)
    blur_score_global = blur_detector.blur_detector_laplacian(img_gray)

    line_new = '%60s  \t%.6g  \t%.6g  \t%.3g  \t%.3g' % (fn, blur_score_global, image_blur_score, blur_percentage, blur_result)
    print(line_new)
