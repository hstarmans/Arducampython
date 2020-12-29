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
        cls.close()

    def test_takeimage(self):
        img = cam.capture(1200)
        height, width, channels = img.shape
        self.assertEqual((height, width), (1600, 1300))

    def preview(self):
        while cv2.waitKey(10) != 27:
            img = cam.capture(1200)
            cv2.imshow("preview image", img)