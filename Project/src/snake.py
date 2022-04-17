import pygame
from config.game_settings import *
from constants.directions import *

import time


class Snake:
    def __init__(self, init_dir, init_body):
        self.body = init_body
        self.head = init_body[0]
        # In the direction the snake is facing
        self.direction = init_dir

    def get_head(self):
        return self.head

    def get_body(self):
        return self.body

    def get_direction(self):
        return self.direction

    def move(self, change_direction_to):

        # Stop snake to move in the opposite direction
        if self.direction != UP and change_direction_to == DOWN:
            self.direction = DOWN
        elif self.direction != DOWN and change_direction_to == UP:
            self.direction = UP
        elif self.direction != RIGHT and change_direction_to == LEFT:
            self.direction = LEFT
        elif self.direction != LEFT and change_direction_to == RIGHT:
            self.direction = RIGHT

        if self.direction == RIGHT:
            self.head = (self.head[0] + TILE_SIZE, self.head[1])
        elif self.direction == LEFT:
            self.head = (self.head[0] - TILE_SIZE, self.head[1])
        elif self.direction == UP:
            self.head = (self.head[0], self.head[1] - TILE_SIZE)
        elif self.direction == DOWN:
            self.head = (self.head[0], self.head[1] + TILE_SIZE)

        self.body.insert(0, list(self.head))
        self.body.pop()

    def grow(self):
        self.body.insert(0, list(self.head))

    def isAlive(self):
        if self.head[0] < 0 or self.head[0] > WINDOW_WIDTH - TILE_SIZE:
            return False
        if self.head[1] < 0 or self.head[1] > WINDOW_HEIGHT - TILE_SIZE:
            return False
        for body_block in self.body[1:]:
            if self.head == body_block:
                return False
        return True

    # def auto_move(self, direction_list):
    #     direction_list_copy = direction_list
    #     for direction in direction_list_copy:
    #         print("move", direction)
    #         # self.move(direction)
    #         # direction_list.remove(direction)
    #         # time.sleep(5)
    #     time.sleep(10)
