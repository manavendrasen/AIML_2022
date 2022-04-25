import enum
from this import d
import pygame
import sys

from config.game_settings import *

import constants.colors as colors
import constants.directions as direction

from src.tile import Tile
from src.snake import Snake
from src.food import Food

from bfs_search import *
from dfs_search import *


class Game:
    def __init__(self) -> None:
        pygame.init()
        pygame.display.set_caption("Pygame Tiled Demo")
        self.window = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
        self.fps_controller = pygame.time.Clock()
        self.running = True
        self.tile_map = []
        self.score = 0

        for i in range(0, WINDOW_WIDTH, TILE_SIZE):
            tile_row = []
            for j in range(0, WINDOW_HEIGHT, TILE_SIZE):
                tile_row.append(Tile(i, j, WINDOW_WIDTH,
                                WINDOW_HEIGHT, TILE_SIZE))
            self.tile_map.append(tile_row)

        self.draw_background()

    def draw_background(self):
        self.window.fill(colors.WHITE)
        for tile_row in self.tile_map:
            for tile in tile_row:
                pygame.draw.rect(
                    self.window, tile.color, (tile.x, tile.y, tile.size, tile.size))

    def get_snake_color(self):
        if self.score < 1:
            return colors.BLUE
        elif self.score < 2:
            return colors.GREEN
        elif self.score < 3:
            return colors.RED
        elif self.score < 4:
            return colors.YELLOW
        elif self.score < 5:
            return colors.PURPLE
        elif self.score < 6:
            return colors.ORANGE
        else:
            return colors.BLACK

    def game_over(self):
        self.running = False
        pygame.quit()
        sys.exit()


def main():
    game = Game()

    # Create a new snake
    snake_direction = direction.RIGHT
    snake_body = [(100, 100), (100 - TILE_SIZE, 100),
                  (100 - (2*TILE_SIZE), 100)]

    snake = Snake(snake_direction, snake_body)

    # Create a new food
    food = Food()
    is_snake_moving = True
    while game.running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game.game_over()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    game.game_over()
                if event.key == pygame.K_UP or event.key == ord('w'):
                    snake_direction = direction.UP
                if event.key == pygame.K_DOWN or event.key == ord('s'):
                    snake_direction = direction.DOWN
                if event.key == pygame.K_LEFT or event.key == ord('a'):
                    snake_direction = direction.LEFT
                if event.key == pygame.K_RIGHT or event.key == ord('d'):
                    snake_direction = direction.RIGHT

        game.draw_background()

        pygame.draw.rect(game.window, colors.YELLOW, pygame.Rect(
            100, 100, TILE_SIZE, TILE_SIZE))

        for index, body_block in enumerate(snake.get_body()):
            if index == 0:
                pygame.draw.rect(game.window, colors.WHITE, pygame.Rect(
                    body_block[0], body_block[1], TILE_SIZE, TILE_SIZE))
            else:
                pygame.draw.rect(game.window, game.get_snake_color(), pygame.Rect(
                    body_block[0], body_block[1], TILE_SIZE, TILE_SIZE))

        pygame.draw.rect(game.window, colors.RED, pygame.Rect(
            food.x, food.y, TILE_SIZE, TILE_SIZE))

        if(is_snake_moving):
            # BFS SEARCH
            # directions = bfs_search(snake, food)

            # DFS SEARCH
            directions = dfs_search(snake, food)

            while(len(directions) > 0):
                dir = directions.pop(0)
                print(dir)
                snake.move(dir)
            # snake.move(direction.LEFT)
            print("Position of snake head after search", snake.get_head())
            is_snake_moving = False

        if(snake.isAlive() == False):
            snake_direction = direction.RIGHT
            snake_body = [(100, 100), (100 - TILE_SIZE, 100),
                          (100 - (2*TILE_SIZE), 100)]
            snake = Snake(snake_direction, snake_body)
            food = Food()
            game.score = 0

        # Check if the snake has eaten the food
        # if snake.get_head() == food.get_position():
        #     game.score += 1
        #     snake.grow()
        #     food.despawn()
        #     food.spawn()

        pygame.display.update()
        game.fps_controller.tick(FPS)


main()
