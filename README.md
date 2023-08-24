# OpenCV Tone Remover

| Input image |  Output image |
:-------------------------:|:-------------------------:
![](https://github.com/MintzyG/ToneRemover-OpenCV/blob/master/InputImage.jpg)  |  ![](https://github.com/MintzyG/ToneRemover-OpenCV/blob/master/ToneChangerOutput.png)

## How to use (Doesn't work yet)
  - Download the .exe
  - Drag and Drop any image file on the .exe
  - The resulting image will be saved to the folder where it originally came from as a png

## How it works
  - The programs choses N random colors from the image (N specified by user)
  - It then tones down the image to those N colors using distance between points in space
  - The resulting image is compared to the original one using K-Means Clustering, if close looking enough, the program saves and exits
  - If the image is not close looking enough it keeps using K-Means Clustering until it closely resmembles the original, but now with N colors

## Plan to add
  - Packaging the program with OpenCVWorld480.lib

