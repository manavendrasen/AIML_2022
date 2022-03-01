
import constants.colors as colors
import pygame


class Tile:
    def __init__(self, x, y, width, height, tile_size) -> None:
        self.x = x
        self.y = y
        self.size = tile_size
        if x == 0 or x == width - tile_size:
            self.color = colors.BROWN
        elif y == 0 or y == height - tile_size:
            self.color = colors.BROWN
        else:
            self.color = colors.BG
