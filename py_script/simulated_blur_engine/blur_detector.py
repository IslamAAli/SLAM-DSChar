from imutils import paths
import cv2
import numpy as np
import matplotlib.pyplot as plt
from scipy.ndimage.filters import gaussian_filter

VISUALIZE_BLURRING = 1
threshold_scroe = 50

# assuming image is in grayscale
def blur_detector_laplacian(img):
    img_laplacian = cv2.Laplacian(img, cv2.CV_64F, ksize=1)
    return img_laplacian.var()


def segmented_blur_detector(img, segment_dimension=50):
    total_subscore = 0
    sub_images_count = 0
    blurred_sub_images_count = 0
    img_2 = np.zeros(img.shape)
    img_3 = np.zeros(img.shape)
    # if VISUALIZE_BLURRING == 1:
    #     img_vis = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
    #     # draw vertical line
    #     for i in range(0, img_vis.shape[1], segment_dimension):
    #         cv2.line(img_vis, (i, 0), (i, img_vis.shape[0]), (0, 255, 0), 2)
    #     # draw horizontal lines
    #     for j in range(0, img_vis.shape[0], segment_dimension):
    #         cv2.line(img_vis, (0, j), (img_vis.shape[1], j), (0, 255, 0), 2)

    for r in range(0, img.shape[0], segment_dimension):
        for c in range(0, img.shape[1], segment_dimension):
            # adjust rows boundaries
            rows_start = r
            rows_end = r+segment_dimension
            if rows_end >= img.shape[0]:
                rows_end = img.shape[0]

            # adjust cols boundaries
            cols_start = c
            cols_end = c+segment_dimension
            if cols_end >= img.shape[1]:
                cols_end = img.shape[1]

            
            sub_score = blur_detector_laplacian(img[rows_start:rows_end, cols_start:cols_end])
            print(sub_score)
            total_subscore += sub_score
            sub_images_count += 1

            img_2[rows_start:rows_end, cols_start:cols_end] = sub_score
            img_3[rows_start:rows_end, cols_start:cols_end] = 255 if sub_score < threshold_scroe else 0
            blurred_sub_images_count += 1 if sub_score < threshold_scroe else 0
            # if VISUALIZE_BLURRING == 1:
            #     cv2.putText(img_vis, "{:.2f}".format(sub_score), (cols_start+5, rows_end-5),
            #                 cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 255), 2)

    # printing the image blurring score
    image_blur_score = total_subscore / sub_images_count
    blur_percentage = (blurred_sub_images_count/sub_images_count)*100

    blur_result = 1 if blur_percentage > 50 else 0

    # print('Image Score: ', image_blur_score)
    # print('Blur Percentage: ', blur_percentage)
    # print('Blurred? ', blur_result)
    # if VISUALIZE_BLURRING == 1:
    #     # show the image in hand
    #     # print(img_2)
    #     # cv2.imshow("Image", img_vis)
    #     # cv2.waitKey()
    #     # blurred = gaussian_filter(img_2, sigma=15)
    #     # f, axarr = plt.subplots(2,2)

    #     # axarr[0,0].imshow(img)
    #     # axarr[0,1].imshow(img_2, cmap='hot', interpolation='nearest')
    #     # axarr[1,0].imshow(img_3, cmap='hot', interpolation='nearest')
    #     # plt.show()

    return img_2, img_3, image_blur_score, blur_percentage, blur_result
