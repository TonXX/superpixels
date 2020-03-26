from PIL import Image
img = Image.open('2_result.ppm')
img.save('2_result.bmp')
img.show()