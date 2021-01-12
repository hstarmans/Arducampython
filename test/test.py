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
        img = self.cam.capture(1200)
        height, width, channels = img.shape
        # retrievd image not equal to expected
        self.assertEqual((height, width), (1312, 1600))
        if save: cv2.imwrite('test.png', img)

    def testspeed(self):
        tstart = time()
        loops = 30
        for _ in range(loops):
            img = self.cam.capture(100)
        print(f"Capturing {loops/(time()-tstart):.2f} frames per second")


    def pythonpreview(self):
        while cv2.waitKey(30) != 27: # 27 is ascii value of esc
            img = self.cam.capture(3000)
            try:
                if img.shape[0] == 0:
                    continue
            except AttributeError:
                continue
            cv2.imshow("preview image", img)

    def preview(self):
        self.cam.live_view(3000)

if __name__ == '__main__':
    unittest.main()
