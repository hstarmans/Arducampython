import unittest
from time import time, sleep


import cv2

import camera

class Tests(unittest.TestCase):
    @classmethod
    def setUpClass(cls, flash=True):
        cls.cam = camera.Cam()
        cls.cam.init()

    @classmethod
    def tearDownClass(cls):
        cls.cam.close()

    def test_takeimage(self, save=False):
        self.cam.set_exposure(1200)
        img = self.cam.capture()
        height, width, channels = img.shape
        # retrievd image not equal to expected
        self.assertEqual((height, width), (1280, 1600))
        if save: cv2.imwrite('test.png', img)

    def testspeed(self):
        tstart = time()
        loops = 30
        self.cam.set_exposure(100)
        for _ in range(loops):
            img = self.cam.capture()
        print(f"Capturing {loops/(time()-tstart):.2f} frames per second")


    def pythonpreview(self):
        while cv2.waitKey(30) != 27: # 27 is ascii value of esc
            self.cam.set_exposure(3000)
            img = self.cam.capture()
            try:
                if img.shape[0] == 0:
                    continue
            except AttributeError:
                continue
            cv2.imshow("preview image", img)

    def preview(self):
        self.cam.live_view(3000, 0.6)

if __name__ == '__main__':
    unittest.main()
