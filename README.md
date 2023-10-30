# OpenCV Tone Remover

> Makes an image have X tones 

| Input image |  Output image |
:-------------------------:|:-------------------------:
![](https://github.com/MintzyG/ToneRemover-OpenCV/blob/master/InputImage.jpg)  |  ![](https://github.com/MintzyG/ToneRemover-OpenCV/blob/master/ToneChangerOutput.png)

## How to use
  - Download and install [OpenCV](https://opencv.org/get-started/) library
  - Clone this Repo and compile it
  - Drag and Drop any image file on the .exe
  - The resulting image will be saved to the folder where it originally came from as a png

## How it works
  - The programs choses N random colors from the image (N specified by user)
  - It then tones down the image to those N colors using distance between points in space
  - The resulting image is compared to the original one using K-Means Clustering, if close looking enough, the program saves and exits
  - If the image is not close looking enough it keeps using K-Means Clustering until it closely resmembles the original, but now with N colors

## Downfalls of this project
  - I failed to learn how to use CMake to statically compile OpenCV libraries into the my binary, therefor the user has to download the libraries if they desire to use the application
  - The method used is far from fast or good for the effect desired, however the method was chosen by my professor so I had no say in that
  - No pre-compiled binary was made available to the end user, making them have to link and compile the project, which is a confusing process

## I intend to:
  - I atleast intend to comeback to this project and make available a pre-compiled binary but without the library still
