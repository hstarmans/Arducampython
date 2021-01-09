import unittest

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

    def test_takeimage(self):
        img = self.cam.capture(1200)
        height, width, channels = img.shape
        # retrievd image not equal to expected
        self.assertEqual((height, width), (1312, 1600))

    def preview(self):
        while cv2.waitKey(10) != 27:
            img = self.cam.capture(1200)
            cv2.imshow("preview image", img)

if __name__ == '__main__':
    unittest.main()