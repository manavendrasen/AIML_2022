from config.game_settings import *
import constants.directions as direction


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

    def move(self, change_direction_to):
        if self.direction != direction.UP and change_direction_to == direction.DOWN:
            self.direction = direction.DOWN
        elif self.direction != direction.DOWN and change_direction_to == direction.UP:
            self.direction = direction.UP
        elif self.direction != direction.RIGHT and change_direction_to == direction.LEFT:
            self.direction = direction.LEFT
        elif self.direction != direction.LEFT and change_direction_to == direction.RIGHT:
            self.direction = direction.RIGHT

        if self.direction == direction.RIGHT:
            self.head = (self.head[0] + TILE_SIZE, self.head[1])
        elif self.direction == direction.LEFT:
            self.head = (self.head[0] - TILE_SIZE, self.head[1])
        elif self.direction == direction.UP:
            self.head = (self.head[0], self.head[1] - TILE_SIZE)
        elif self.direction == direction.DOWN:
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
